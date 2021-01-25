#pragma once

#include <list>

#include "to_string.hpp"

namespace miu::com {

class strcat {
  public:
    struct delimiter {
        std::string val;
    };

  public:
    explicit strcat(delimiter = { "." });

    template<typename T, typename... ARGS>
    strcat(T const& t, ARGS&&... args)
        : strcat(std::forward<ARGS>(args)...) {
        push_front(t);
    }

    std::string str() const;
    uint32_t size() const;

    template<typename T>
    auto& push_front(T const& t) {
        _items.push_front(to_string(t));
        return *this;
    }

    template<typename T>
    auto& push_back(T const& t) {
        _items.push_back(to_string(t));
        return *this;
    }

    template<typename T>
    auto& operator+=(T const& t) {
        return push_back(t);
    }

    template<typename T>
    auto operator+(T const& t) {
        auto val = *this;
        val.push_back(t);
        return val;
    }

    auto begin() const { return _items.begin(); }
    auto end() const { return _items.end(); }

  private:
    delimiter _delimiter;
    std::list<std::string> _items;
};

}    // namespace miu::com

DEF_TO_STRING(miu::com::strcat);
