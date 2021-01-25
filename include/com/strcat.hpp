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

    strcat(strcat const& another, delimiter del = { "." })
        : strcat(del) {
        push_front(another);
    }

    template<typename T, typename... ARGS>
    strcat(T const& t, ARGS&&... args)
        : strcat(std::forward<ARGS>(args)...) {
        push_front(t);
    }

    template<typename... ARGS>
    strcat(strcat const& another, ARGS&&... args)
        : strcat(std::forward<ARGS>(args)...) {
        push_front(another);
    }

    std::string str() const;
    uint32_t size() const;

    template<typename T>
    auto& push_front(T const& t) {
        _items.push_front(to_string(t));
        return *this;
    }

    strcat& push_front(strcat const&);

    template<typename T>
    auto& push_back(T const& t) {
        _items.push_back(to_string(t));
        return *this;
    }

    strcat& push_back(strcat const&);

    template<typename T>
    auto& operator+=(T const& t) {
        return push_back(t);
    }

    template<typename T>
    auto operator+(T const& t) {
        return strcat { *this, t };
    }

    auto begin() const { return _items.begin(); }
    auto end() const { return _items.end(); }

  private:
    delimiter _delimiter;
    std::list<std::string> _items;
};

}    // namespace miu::com

DEF_TO_STRING(miu::com::strcat);
