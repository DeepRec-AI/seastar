#include "channel.hh"
#include "packet_queue.hh"

namespace seastar {
  channel::channel(const std::string& addr)
    : _packet_queue(nullptr), _addr(addr),
      _reconnect_func(nullptr), _is_channel_broken(false), _init(false) {
  }
  
  void channel::init(seastar::packet_queue* pq,
      output_stream<char>&& output_stream) {
    _packet_queue = pq;
    _output_stream = std::move(output_stream);
    _init = true;
  }

  void channel::put(user_packet* p) {
    p->_channel = this;
    _packet_queue->enqueue(p);
  }

  void channel::put(const std::vector<user_packet*>& v) {
    for (auto p : v) {
      p->_channel = this;
      _packet_queue->enqueue(p);
    }
  }

  const std::atomic_bool& channel::is_init() {
    return _init;
  }

  output_stream<char>* channel::get_output_stream() {
    return &this->_output_stream;
  }

  bool channel::is_channel_broken() const {
    return _is_channel_broken;
  }

  void channel::set_channel_broken() {
    _is_channel_broken = true;
  }

  const std::string& channel::get_addr() const {
    return _addr;
  }

  void channel::reconnect_done() {
    _is_channel_broken = false;
    _is_reconnecting.clear(std::memory_order_release);
  }

  void channel::reconnect() {
    if (_reconnect_func != nullptr && !_is_reconnecting.test_and_set(std::memory_order_acquire)) {
      if (_is_channel_broken) {
        _reconnect_func(&channel::reconnect_done);
      }      
      else {
        reconnect_done();
      }
    }
  }

  void channel::set_channel_reconnect_func(std::function<void ( void (channel::*func)())> fn) {
    _reconnect_func = fn;
  }
}
