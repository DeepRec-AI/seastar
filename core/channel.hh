#pragma once
#include "iostream.hh"
#include <string>
#include <functional>
#include <atomic>

namespace seastar {
class packet_queue;
struct user_packet;

class channel {
public:
  channel(const std::string&);
  virtual ~channel(){}

  void init(seastar::packet_queue* pq,
      output_stream<char>&& output_stream);
  const std::atomic_bool& is_init();

  void put(user_packet* p);
  void put(const std::vector<user_packet*>& v);

  output_stream<char>* get_output_stream();

  bool is_channel_broken() const;
  void set_channel_broken();
  void set_channel_reconnect_func(std::function<void ( void (channel::*done)())> fn);
  void reconnect(void);
  void reconnect_done();

  const std::string& get_addr() const;
private:
  seastar::packet_queue* volatile _packet_queue;
  output_stream<char> _output_stream;
  std::string _addr;
  bool volatile _is_channel_broken;
  std::function<void ( void (channel::*func)())> _reconnect_func;
  std::atomic_flag _is_reconnecting = ATOMIC_FLAG_INIT;
  std::atomic_bool _init;
};
}
