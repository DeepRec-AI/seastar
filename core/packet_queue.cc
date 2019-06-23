#include "packet_queue.hh"
#include "core/reactor.hh"

namespace seastar {

static const size_t TLS_QUEUE_SIZE = 128;
packet_queue::packet_queue(reactor* r)
  : _index(0), _reactor(r) {
  pthread_key_create(&tls_queue_key, NULL);
  _queues.resize(TLS_QUEUE_SIZE, nullptr);
}

packet_queue::~packet_queue() {
  for (auto it = _queues.begin(); it != _queues.end(); ++it)
    delete *it;
  pthread_key_delete(tls_queue_key);
}

tls_queue* packet_queue::impl() {
  auto tls_queue_impl = (tls_queue*)pthread_getspecific(tls_queue_key);
  if (tls_queue_impl == nullptr) {
    tls_queue_impl = new tls_queue();
    auto index = _index.fetch_add(1); 
    _queues[index] = tls_queue_impl;
    pthread_setspecific(tls_queue_key, tls_queue_impl);
  }
  return tls_queue_impl;
}

bool packet_queue::enqueue(user_packet* pack) {
  bool ret = impl()->enqueue(pack);
  if (ret) {
    _reactor->maybe_wakeup();
  }
  return ret;
}

bool packet_queue::try_enqueue(user_packet* pack) {
  bool ret = impl()->try_enqueue(pack);
  if (ret) {
    _reactor->maybe_wakeup();
  }
  return ret;
}

bool packet_queue::try_dequeue_bulk(user_packet** pack) {
  for (auto it = _queues.begin(); it != _queues.end(); ++it) {
    if (*it == nullptr)
      return false;
    user_packet* item = nullptr;
    while ((*it)->try_dequeue(item)) {
      if (item == nullptr)
        continue;
      *pack = item;
      return true;
    }
  }
  return false;
}

}
