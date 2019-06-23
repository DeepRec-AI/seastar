#pragma once
#include "readerwriterqueue.h"
#include "concurrentqueue.h"
#include "circular_buffer.hh"
#include "iostream.hh"
#include <functional>
#include <pthread.h>
#include <atomic>
#include <map>
#include <list>

namespace seastar {

class reactor;
class channel;

struct user_packet {
  std::vector<net::fragment> _fragments;
  std::function<void()> _done;
  channel* _channel;
};

using tls_queue =  moodycamel::ReaderWriterQueue<user_packet*>;
using tls_queue_list = std::vector<tls_queue*>; 

class packet_queue {
public:
  explicit packet_queue(reactor* r);
  virtual ~packet_queue();

  bool enqueue(user_packet* pack);
  bool try_enqueue(user_packet* pack);
  bool try_dequeue_bulk(user_packet** p);

private:
  tls_queue* impl();
  void dequeue_tls_queues();

private:
  pthread_key_t tls_queue_key;
  tls_queue_list _queues;
  std::atomic<size_t> _index;
  reactor* _reactor;
};
}
