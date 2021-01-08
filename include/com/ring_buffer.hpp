#pragma once

#include <atomic>
#include <cassert>
#include <vector>

#include "fatal_error.hpp"

namespace miu::com {

template<typename T>
class ring_buffer {
  public:
    template<typename... ARGS>
    explicit ring_buffer(uint32_t cap, ARGS&&... args)
        : MASK { cap - 1 }
        , _vec(cap, T { std::forward<ARGS>(args)... }) {
        if (!cap || cap & MASK) {
            FATAL_ERROR("ring_buffer size must be pow of 2");
        }
    }

    ring_buffer(ring_buffer const&) = delete;
    auto operator=(ring_buffer const&) = delete;

    auto capacity() const { return _vec.size(); }

    auto size() const {
        auto head = _head.load(std::memory_order_consume);
        auto tail = _tail.load(std::memory_order_consume);
        return tail - head;
    }

    auto empty() const { return !size(); }

    auto push(T const& val) {
        return try_add([&](T* t) { *t = val; });
    }

    template<typename... ARGS>
    auto emplace(ARGS... args) {
        return try_add([&](T* t) { new (t) T { std::forward<ARGS>(args)... }; });
    }

    auto dump(uint32_t cnt) {
        assert(cnt <= size() && "overflow");
        _head.fetch_add(cnt, std::memory_order_release);
    }

    T& operator[](uint32_t idx) {
        auto head = _head.load(std::memory_order_relaxed);
        assert(_tail - head >= idx && "overflow");
        return _vec[to_idx(head + idx)];
    }

  private:
    inline uint32_t to_idx(uint32_t val) const { return val & MASK; }

    template<typename CB>
    bool try_add(CB const& cb) {
        auto head = _head.load(std::memory_order_consume);
        auto tail = _tail.load(std::memory_order_relaxed);
        if (tail - head == capacity()) {
            return false;
        }

        cb(&_vec[to_idx(tail)]);

        _tail.fetch_add(1, std::memory_order_release);
        return true;
    }

  private:
    uint32_t const MASK;
    std::atomic_uint _head { 0 };
    std::atomic_uint _tail { 0 };
    std::vector<T> _vec;
};

}    // namespace miu::com
