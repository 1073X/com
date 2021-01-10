#pragma once

#include <sstream>
#include <string>    // std::to_string
#include <utility>

namespace miu::com {

class strcat {
  public:
    template<typename T>
    struct cast {
        auto operator()(T const& t) { return std::to_string(t); }
    };

    struct delimiter {
        std::string val;
    };

  public:
    explicit strcat(delimiter del = { "." })
        : _delimiter { std::move(del) } {}

    template<typename T, typename... ARGS>
    strcat(T const& t, ARGS&&... args)
        : strcat(std::forward<ARGS>(args)...) {
        _str = cast<T>()(t) + _delimiter.val + _str;
    }

    std::string str() const {
        auto it = _str.begin();
        return { it, it + _str.size() - _delimiter.val.size() };
    }

  private:
    delimiter _delimiter;
    std::string _str;
};

template<>
struct strcat::cast<char> {
    auto operator()(char v) const { return std::string { v }; }
};

template<std::size_t N>
struct strcat::cast<char[N]> {
    auto operator()(const char (&v)[N]) const { return +v; }
};

template<>
struct strcat::cast<const char*> {
    auto operator()(const char* v) const { return v; }
};

template<>
struct strcat::cast<std::string> {
    auto operator()(std::string const& v) { return v; }
};

template<>
struct strcat::cast<std::string_view> {
    auto operator()(std::string_view v) { return v.data(); }
};

}    // namespace miu::com
