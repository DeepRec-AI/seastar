/*
 * Copyright (C) 2014 Cloudius Systems, Ltd.
 */

#include "native-stack.hh"
#include "net.hh"
#include "ip.hh"
#include "tcp.hh"
#include "udp.hh"
#include "virtio.hh"
#include "proxy.hh"
#include <memory>
#include <queue>

namespace net {

template <typename Protocol>
class native_server_socket_impl;

template <typename Protocol>
class native_connected_socket_impl;

class native_network_stack;

// native_server_socket_impl
template <typename Protocol>
class native_server_socket_impl : public server_socket_impl {
    typename Protocol::listener _listener;
public:
    native_server_socket_impl(Protocol& proto, uint16_t port, listen_options opt);
    virtual future<connected_socket, socket_address> accept() override;
};

template <typename Protocol>
native_server_socket_impl<Protocol>::native_server_socket_impl(Protocol& proto, uint16_t port, listen_options opt)
    : _listener(proto.listen(port)) {
}

template <typename Protocol>
future<connected_socket, socket_address>
native_server_socket_impl<Protocol>::accept() {
    return _listener.accept().then([this] (typename Protocol::connection conn) {
        return make_ready_future<connected_socket, socket_address>(
                connected_socket(std::make_unique<native_connected_socket_impl<Protocol>>(std::move(conn))),
                socket_address()); // FIXME: don't fake it
    });
}

// native_connected_socket_impl
template <typename Protocol>
class native_connected_socket_impl : public connected_socket_impl {
    typename Protocol::connection _conn;
    class native_data_source_impl;
    class native_data_sink_impl;
public:
    explicit native_connected_socket_impl(typename Protocol::connection conn)
        : _conn(std::move(conn)) {}
    virtual input_stream<char> input() override;
    virtual output_stream<char> output() override;
};

template <typename Protocol>
class native_connected_socket_impl<Protocol>::native_data_source_impl final
    : public data_source_impl {
    typename Protocol::connection& _conn;
    size_t _cur_frag = 0;
    bool _eof = false;
    packet _buf;
public:
    explicit native_data_source_impl(typename Protocol::connection& conn)
        : _conn(conn) {}
    virtual future<temporary_buffer<char>> get() override {
        if (_eof) {
            return make_ready_future<temporary_buffer<char>>(temporary_buffer<char>(0));
        }
        if (_cur_frag != _buf.nr_frags()) {
            auto& f = _buf.fragments()[_cur_frag++];
            return make_ready_future<temporary_buffer<char>>(
                    temporary_buffer<char>(f.base, f.size,
                            make_deleter(deleter(), [p = _buf.share()] () mutable {})));
        }
        return _conn.wait_for_data().then([this] {
            _buf = _conn.read();
            _cur_frag = 0;
            _eof = !_buf.len();
            return get();
        });
    }
};

template <typename Protocol>
class native_connected_socket_impl<Protocol>::native_data_sink_impl final
    : public data_sink_impl {
    typename Protocol::connection& _conn;
public:
    explicit native_data_sink_impl(typename Protocol::connection& conn)
        : _conn(conn) {}
    virtual future<> put(std::vector<temporary_buffer<char>> data) override {
        std::vector<fragment> frags;
        frags.reserve(data.size());
        for (auto& e : data) {
            frags.push_back(fragment{e.get_write(), e.size()});
        }
        return _conn.send(packet(std::move(frags), [tmp = std::move(data)] () mutable {}));
    }
    virtual future<> put(temporary_buffer<char> data) override {
        return _conn.send(packet({data.get_write(), data.size()}, data.release()));
    }
    virtual future<> close() override {
        _conn.close_write();
        return make_ready_future<>();
    }
};

template <typename Protocol>
input_stream<char>
native_connected_socket_impl<Protocol>::input() {
    data_source ds(std::make_unique<native_data_source_impl>(_conn));
    return input_stream<char>(std::move(ds));
}

template <typename Protocol>
output_stream<char>
native_connected_socket_impl<Protocol>::output() {
    data_sink ds(std::make_unique<native_data_sink_impl>(_conn));
    return output_stream<char>(std::move(ds), 8192);
}

// native_network_stack
class native_network_stack : public network_stack {
    static std::unique_ptr<native_network_stack> _s;
    interface _netif;
    ipv4 _inet;
    udp_v4 _udp;
    using tcp4 = tcp<ipv4_traits>;
public:
    explicit native_network_stack(boost::program_options::variables_map opts);
    virtual server_socket listen(socket_address sa, listen_options opt) override;
    virtual udp_channel make_udp_channel(ipv4_addr addr) override;
    static std::unique_ptr<network_stack> create(boost::program_options::variables_map opts) {
        return std::make_unique<native_network_stack>(opts);
    }
    friend class native_server_socket_impl<tcp4>;
};

udp_channel
native_network_stack::make_udp_channel(ipv4_addr addr) {
    return _udp.make_channel(addr);
}

native_network_stack::native_network_stack(boost::program_options::variables_map opts)
    : _netif(smp::main_thread() ? create_virtio_net_device(opts["tap-device"].as<std::string>(), opts) : create_proxy_net_device(opts))
    , _inet(&_netif)
    , _udp(_inet) {
    _inet.set_host_address(ipv4_address(opts["host-ipv4-addr"].as<std::string>()));
    _inet.set_gw_address(ipv4_address(opts["gw-ipv4-addr"].as<std::string>()));
    _inet.set_netmask_address(ipv4_address(opts["netmask-ipv4-addr"].as<std::string>()));
    _udp.set_queue_size(opts["udpv4-queue-size"].as<int>());
}

server_socket
native_network_stack::listen(socket_address sa, listen_options opts) {
    assert(sa.as_posix_sockaddr().sa_family == AF_INET);
    return server_socket(std::make_unique<native_server_socket_impl<tcp4>>(
            _inet.get_tcp(), ntohs(sa.as_posix_sockaddr_in().sin_port), opts));
}

std::unique_ptr<native_network_stack> native_network_stack::_s;

boost::program_options::options_description nns_options() {
    boost::program_options::options_description opts(
            "Native networking stack options");
    opts.add_options()
        ("tap-device",
                boost::program_options::value<std::string>()->default_value("tap0"),
                "tap device to connect to")
        ("host-ipv4-addr",
                boost::program_options::value<std::string>()->default_value("192.168.122.2"),
                "static IPv4 address to use")
        ("gw-ipv4-addr",
                boost::program_options::value<std::string>()->default_value("192.168.122.1"),
                "static IPv4 gateway to use")
        ("netmask-ipv4-addr",
                boost::program_options::value<std::string>()->default_value("255.255.255.0"),
                "static IPv4 netmask to use")
        ("udpv4-queue-size",
                boost::program_options::value<int>()->default_value(udp_v4::default_queue_size),
                "Default size of the UDPv4 per-channel packet queue")
        ;
    opts.add(get_virtio_net_options_description());
    return opts;
}

network_stack_registrator nns_registrator{
    "native", nns_options(), native_network_stack::create
};

}