/*
 * This file is open source software, licensed to you under the terms
 * of the Apache License, Version 2.0 (the "License").  See the NOTICE file
 * distributed with this work for additional information regarding copyright
 * ownership.  You may not use this file except in compliance with the License.
 *
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (C) 2015 Cloudius Systems, Ltd.
 */


#pragma once

#include "future-util.hh"
#include "net/packet.hh"
#include "core/future-util.hh"

namespace seastar {

inline future<temporary_buffer<char>> data_source_impl::skip(uint64_t n)
{
    return do_with(uint64_t(n), [this] (uint64_t& n) {
        return repeat_until_value([&] {
            return get().then([&] (temporary_buffer<char> buffer) -> std::experimental::optional<temporary_buffer<char>> {
                if (buffer.size() >= n) {
                    buffer.trim_front(n);
                    return std::move(buffer);
                }
                n -= buffer.size();
                return { };
            });
        });
    });
}

template<typename CharType>
inline
future<> output_stream<CharType>::write(const char_type* buf) {
    return write(buf, strlen(buf));
}

template<typename CharType>
template<typename StringChar, typename SizeType, SizeType MaxSize>
inline
future<> output_stream<CharType>::write(const basic_sstring<StringChar, SizeType, MaxSize>& s) {
    return write(reinterpret_cast<const CharType *>(s.c_str()), s.size());
}

template<typename CharType>
inline
future<> output_stream<CharType>::write(const std::basic_string<CharType>& s) {
    return write(s.c_str(), s.size());
}

template<typename CharType>
future<> output_stream<CharType>::write(scattered_message<CharType> msg) {
    return write(std::move(msg).release());
}

template<typename CharType>
int output_stream<CharType>::get_fd() {
    return _fd.get_fd();
}

template<typename CharType>
future<>
output_stream<CharType>::zero_copy_put(net::packet p) {
    // if flush is scheduled, disable it, so it will not try to write in parallel
    _flush = false;
    if (_flushing) {
        // flush in progress, wait for it to end before continuing
        return _in_batch.value().get_future().then([this, p = std::move(p)] () mutable {
            return _fd.put(std::move(p));
        });
    } else {
        return _fd.put(std::move(p));
    }
}

// Writes @p in chunks of _size length. The last chunk is buffered if smaller.
template <typename CharType>
future<>
output_stream<CharType>::zero_copy_split_and_put(net::packet p) {
    return repeat([this, p = std::move(p)] () mutable {
        if (p.len() < _size) {
            if (p.len()) {
                _zc_bufs = std::move(p);
            } else {
                _zc_bufs = net::packet::make_null_packet();
            }
            return make_ready_future<stop_iteration>(stop_iteration::yes);
        }
        auto chunk = p.share(0, _size);
        p.trim_front(_size);
        return zero_copy_put(std::move(chunk)).then([] {
            return stop_iteration::no;
        });
    });
}

template<typename CharType>
future<> output_stream<CharType>::write(net::packet p) {
    static_assert(std::is_same<CharType, char>::value, "packet works on char");

    if (p.len() != 0) {
        assert(!_end && "Mixing buffered writes and zero-copy writes not supported yet");

        if (_zc_bufs) {
            _zc_bufs.append(std::move(p));
        } else {
            _zc_bufs = std::move(p);
        }

        if (_zc_bufs.len() >= _size) {
            //if (_trim_to_size) {
            //    return zero_copy_split_and_put(std::move(_zc_bufs));
            //} else {
            //    return zero_copy_put(std::move(_zc_bufs));
            //}
            auto bufs = std::move(_zc_bufs);
            return zero_copy_put(std::move(bufs));
            //return _lock.write_lock().then([this, bufs = std::move(bufs)] () mutable {
            //  return zero_copy_put(std::move(bufs)).then([this] () mutable {
            //    _lock.write_unlock();
            //    return make_ready_future<>();
            //  });
            //});
        }
    }
    return make_ready_future<>();
}

template<typename CharType>
future<> output_stream<CharType>::write(temporary_buffer<CharType> p) {
    if (p.empty()) {
        return make_ready_future<>();
    }
    assert(!_end && "Mixing buffered writes and zero-copy writes not supported yet");

    return write(net::packet(std::move(p)));
}

template <typename CharType>
future<temporary_buffer<CharType>>
input_stream<CharType>::read_exactly_part(size_t n, tmp_buf out, size_t completed) {
    if (available()) {
        auto now = std::min(n - completed, available());
        std::copy(_buf.get(), _buf.get() + now, out.get_write() + completed);
        _buf.trim_front(now);
        completed += now;
    } else {
        completed += _fd.get_read_data_size();
        _fd.reset_read_data_size();
    }
    if (completed == n) {
        return make_ready_future<tmp_buf>(std::move(out));
    }

    char* write_buf = out.get_write() + completed;
    return _fd.get(n - completed, write_buf)
              .then([this, n, out = std::move(out), completed] (auto buf) mutable {
        // connection is disconnect
        if (_fd.get_read_data_size() == 0) {
            _eof = true;
            return make_ready_future<tmp_buf>(std::move(buf));
        }

        // If buf.size() == 0,
        // data was read to 'out' directly,
        // and now, _buf is not available.
        if (buf.size() > 0) {
            _buf = std::move(buf);
        }
        return this->read_exactly_part(n, std::move(out), completed);
    });

    /*
    // _buf is now empty
    return _fd.get().then([this, n, out = std::move(out), completed] (auto buf) mutable {
        if (buf.size() == 0) {
            _eof = true;
            return make_ready_future<tmp_buf>(std::move(buf));
        }
        _buf = std::move(buf);
        return this->read_exactly_part(n, std::move(out), completed);
    });*/
}

template <typename CharType>
future<temporary_buffer<CharType>>
input_stream<CharType>::read_exactly(size_t n) {
    if (_buf.size() == n) {
        // easy case: steal buffer, return to caller
        return make_ready_future<tmp_buf>(std::move(_buf));
    } else if (_buf.size() > n) {
        // buffer large enough, share it with caller
        auto front = _buf.share(0, n);
        _buf.trim_front(n);
        return make_ready_future<tmp_buf>(std::move(front));
    } else if (_buf.size() == 0) {
        // buffer is empty: grab one and retry
        return _fd.get().then([this, n] (auto buf) mutable {
            if (buf.size() == 0) {
                _eof = true;
                return make_ready_future<tmp_buf>(std::move(buf));
            }
            _buf = std::move(buf);
            return this->read_exactly(n);
        });
    } else {
        // buffer too small: start copy/read loop
        tmp_buf b(n);
        _fd.reset_read_data_size();
        return read_exactly_part(n, std::move(b), 0);
    }
}

// TODO: user_buf should be allocated before read_exactly
template <typename CharType>
future<size_t>
input_stream<CharType>::read_exactly(CharType* user_buf, size_t n) {
    if (_buf.size() >= n) {
        std::copy(_buf.get(), _buf.get() + n, user_buf);
        _buf.trim_front(n);
        return make_ready_future<size_t>(n);
    } else {
        _fd.reset_read_data_size();
        // wrap to tmp_buf, but the deleter must be empty,
        // it's owned by user.
        tmp_buf b(user_buf, n, deleter());
        return read_exactly_part(n, std::move(b), 0).then([] (auto&& buf) {
            return make_ready_future<size_t>(buf.size());
        });
    }
}

template <typename CharType>
future<size_t> input_stream<CharType>::read_exactly_into(CharType* user_buf, size_t n) {
    static_assert(sizeof(CharType) == 1, "must buffer stream of bytes");

    return _fd.get(user_buf, n).then([this, user_buf, n] (auto size) mutable {
        // if size == 0, then disconnect
        if (size == 0) {
           return make_ready_future<size_t>(0);
        }

        if (size < n) {
            return this->read_exactly_into(user_buf + size, n-size).then([size] (auto new_size) {
                return make_ready_future<size_t>(size + new_size);
            });
        }

        return make_ready_future<size_t>(size);
    });
}

template <typename CharType>
template <typename Consumer>
future<>
input_stream<CharType>::consume(Consumer&& consumer) {
    return repeat([consumer = std::move(consumer), this] () mutable {
        if (_buf.empty() && !_eof) {
            return _fd.get().then([this] (tmp_buf buf) {
                _buf = std::move(buf);
                _eof = _buf.empty();
                return make_ready_future<stop_iteration>(stop_iteration::no);
            });
        }
        future<unconsumed_remainder> unconsumed = consumer(std::move(_buf));
        if (unconsumed.available()) {
            unconsumed_remainder u = std::get<0>(unconsumed.get());
            if (u) {
                // consumer is done
                _buf = std::move(u.value());
                return make_ready_future<stop_iteration>(stop_iteration::yes);
            }
            if (_eof) {
                return make_ready_future<stop_iteration>(stop_iteration::yes);
            }
            // If we're here, consumer consumed entire buffer and is ready for
            // more now. So we do not return, and rather continue the loop.
            // TODO: if we did too many iterations, schedule a call to
            // consume() instead of continuing the loop.
            return make_ready_future<stop_iteration>(stop_iteration::no);
        } else {
            // TODO: here we wait for the consumer to finish the previous
            // buffer (fulfilling "unconsumed") before starting to read the
            // next one. Consider reading ahead.
            return unconsumed.then([this] (unconsumed_remainder u) {
                if (u) {
                    // consumer is done
                    _buf = std::move(u.value());
                    return make_ready_future<stop_iteration>(stop_iteration::yes);
                } else {
                    // consumer consumed entire buffer, and is ready for more
                    return make_ready_future<stop_iteration>(stop_iteration::no);
                }
            });
        }
    });
}

template <typename CharType>
template <typename Consumer>
future<>
input_stream<CharType>::consume(Consumer& consumer) {
    return consume(std::ref(consumer));
}

template <typename CharType>
future<temporary_buffer<CharType>>
input_stream<CharType>::read_up_to(size_t n) {
    using tmp_buf = temporary_buffer<CharType>;
    if (_buf.empty()) {
        if (_eof) {
            return make_ready_future<tmp_buf>();
        } else {
            return _fd.get().then([this, n] (tmp_buf buf) {
                _eof = buf.empty();
                _buf = std::move(buf);
                return read_up_to(n);
            });
        }
    } else if (_buf.size() <= n) {
        // easy case: steal buffer, return to caller
        return make_ready_future<tmp_buf>(std::move(_buf));
    } else {
        // buffer is larger than n, so share its head with a caller
        auto front = _buf.share(0, n);
        _buf.trim_front(n);
        return make_ready_future<tmp_buf>(std::move(front));
    }
}

template <typename CharType>
future<temporary_buffer<CharType>>
input_stream<CharType>::read() {
    using tmp_buf = temporary_buffer<CharType>;
    if (_eof) {
        return make_ready_future<tmp_buf>();
    }
    if (_buf.empty()) {
        return _fd.get().then([this] (tmp_buf buf) {
            _eof = buf.empty();
            return make_ready_future<tmp_buf>(std::move(buf));
        });
    } else {
        return make_ready_future<tmp_buf>(std::move(_buf));
    }
}

template <typename CharType>
future<>
input_stream<CharType>::skip(uint64_t n) {
    auto skip_buf = std::min(n, _buf.size());
    _buf.trim_front(skip_buf);
    n -= skip_buf;
    if (!n) {
        return make_ready_future<>();
    }
    return _fd.skip(n).then([this] (temporary_buffer<CharType> buffer) {
        _buf = std::move(buffer);
    });
}

template <typename CharType>
data_source
input_stream<CharType>::detach() && {
    if (_buf) {
        throw std::logic_error("detach() called on a used input_stream");
    }

    return std::move(_fd);
}

// Writes @buf in chunks of _size length. The last chunk is buffered if smaller.
template <typename CharType>
future<>
output_stream<CharType>::split_and_put(temporary_buffer<CharType> buf) {
    assert(_end == 0);

    return repeat([this, buf = std::move(buf)] () mutable {
        if (buf.size() < _size) {
            if (!_buf) {
                _buf = _fd.allocate_buffer(_size);
            }
            std::copy(buf.get(), buf.get() + buf.size(), _buf.get_write());
            _end = buf.size();
            return make_ready_future<stop_iteration>(stop_iteration::yes);
        }
        auto chunk = buf.share(0, _size);
        buf.trim_front(_size);
        return put(std::move(chunk)).then([] {
            return stop_iteration::no;
        });
    });
}

template <typename CharType>
future<>
output_stream<CharType>::write(const char_type* buf, size_t n) {
    assert(!_zc_bufs && "Mixing buffered writes and zero-copy writes not supported yet");
    auto bulk_threshold = _end ? (2 * _size - _end) : _size;
    if (n >= bulk_threshold) {
        if (_end) {
            auto now = _size - _end;
            std::copy(buf, buf + now, _buf.get_write() + _end);
            _end = _size;
            temporary_buffer<char> tmp = _fd.allocate_buffer(n - now);
            std::copy(buf + now, buf + n, tmp.get_write());
            _buf.trim(_end);
            _end = 0;
            return put(std::move(_buf)).then([this, tmp = std::move(tmp)]() mutable {
                if (_trim_to_size) {
                    return split_and_put(std::move(tmp));
                } else {
                    return put(std::move(tmp));
                }
            });
        } else {
            temporary_buffer<char> tmp = _fd.allocate_buffer(n);
            std::copy(buf, buf + n, tmp.get_write());
            if (_trim_to_size) {
                return split_and_put(std::move(tmp));
            } else {
                return put(std::move(tmp));
            }
        }
    }

    if (!_buf) {
        _buf = _fd.allocate_buffer(_size);
    }

    auto now = std::min(n, _size - _end);
    std::copy(buf, buf + now, _buf.get_write() + _end);
    _end += now;
    if (now == n) {
        return make_ready_future<>();
    } else {
        temporary_buffer<char> next = _fd.allocate_buffer(_size);
        std::copy(buf + now, buf + n, next.get_write());
        _end = n - now;
        std::swap(next, _buf);
        return put(std::move(next));
    }
}

template <typename CharType>
future<>
output_stream<CharType>::flush() {
    if (!_batch_flushes) {
        if (_end) {
            _buf.trim(_end);
            _end = 0;
            return put(std::move(_buf)).then([this] {
                return _fd.flush();
            });
        } else if (_zc_bufs) {
            //return zero_copy_put(std::move(_zc_bufs)).then([this] {
            //    return _fd.flush();
            //});
            auto bufs = std::move(_zc_bufs);
            return zero_copy_put(std::move(bufs)).then([this] () mutable { return _fd.flush(); });
            //return _lock.write_lock().then([this, bufs = std::move(bufs)] () mutable {
            //    return zero_copy_put(std::move(bufs)).then([this] () mutable {
            //      return _fd.flush().then([this] {
            //        _lock.write_unlock();
            //        return make_ready_future<>();
            //      });
            //    });
            // });
        }
    } else {
        if (_ex) {
            // flush is a good time to deliver outstanding errors
            return make_exception_future<>(std::move(_ex));
        } else {
            _flush = true;
            if (!_in_batch) {
                add_to_flush_poller(this);
                _in_batch = promise<>();
            }
        }
    }
    return make_ready_future<>();
}

void add_to_flush_poller(output_stream<char>* x);

template <typename CharType>
future<>
output_stream<CharType>::put(temporary_buffer<CharType> buf) {
    // if flush is scheduled, disable it, so it will not try to write in parallel
    _flush = false;
    if (_flushing) {
        // flush in progress, wait for it to end before continuing
        return _in_batch.value().get_future().then([this, buf = std::move(buf)] () mutable {
            return _fd.put(std::move(buf));
        });
    } else {
        return _fd.put(std::move(buf));
    }
}

template <typename CharType>
void
output_stream<CharType>::poll_flush(bool one_more_flush) {
    if (!_flush) {
        // flush was canceled, do nothing
        _flushing = false;
        //_in_batch.value().set_value();
        //_in_batch = std::experimental::nullopt;
        if (_in_batch) {
          _in_batch.value().set_value();
          _in_batch = std::experimental::nullopt;
        }
        return;
    }

    auto f = make_ready_future();
    _flush = false;
    //_flushing = true; // make whoever wants to write into the fd to wait for flush to complete

    if (_end) {
        // send whatever is in the buffer right now
        _buf.trim(_end);
        _end = 0;
        //f = _fd.put(std::move(_buf));
        if (one_more_flush) {
          _flushing = true;
          f = _fd.put(std::move(_buf));
        } else {
          auto bufs = std::move(_buf);
          _flushing = true;
          f = _fd.put(std::move(bufs));
          //f = _lock.write_lock().then([this, bufs = std::move(bufs)] () mutable {
          //    _flushing = true;
          //    return _fd.put(std::move(bufs)).then([this] () mutable {
          //      _lock.write_unlock();
          //      return make_ready_future<>();
          //   });
          //});
        }
    } else if(_zc_bufs) {
        //f = _fd.put(std::move(_zc_bufs));
        if (one_more_flush) {
          _flushing = true;
          f = _fd.put(std::move(_zc_bufs));
        } else {
          auto bufs = std::move(_zc_bufs);
          _flushing = true;
          f = _fd.put(std::move(bufs));
          //f = _lock.write_lock().then([this, bufs = std::move(bufs)] () mutable {
          //     _flushing = true;
          //    return _fd.put(std::move(bufs)).then([this] () mutable {
          //      _lock.write_unlock();
          //      return make_ready_future<>();
          //    });
          //});
        }
    }

    f.then([this] {
        return _fd.flush();
    }).then_wrapped([this] (future<> f) {
        try {
            f.get();
        } catch (...) {
            _ex = std::current_exception();
        }
        // if flush() was called while flushing flush once more
        poll_flush(true);
    });
}

template <typename CharType>
future<>
output_stream<CharType>::close() {
    return flush().finally([this] {
        if (_in_batch) {
            return _in_batch.value().get_future();
        } else {
            return make_ready_future();
        }
    }).then([this] {
        // report final exception as close error
        if (_ex) {
            std::rethrow_exception(_ex);
        }
    }).finally([this] {
        return _fd.close();
    });
}

template <typename CharType>
data_sink
output_stream<CharType>::detach() && {
    if (_buf) {
        throw std::logic_error("detach() called on a used output_stream");
    }

    return std::move(_fd);
}

}
