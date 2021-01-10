#pragma once

#include <sstream>
#include <string>    // std::to_string
#include <utility>

namespace miu::com {

class strcat {
  private:
    template<typename T>
    std::string cast(T const& t) {
        return std::to_string(t);
    }

    template<size_t N>
    const char* cast(const char (&v)[N]) {
        return +v;
    }

    const char* cast(const char* v) { return v; }
    std::string cast(char v) { return { v }; }
    std::string cast(std::string_view v) { return { v.data(), v.size() }; }

  public:
    struct delimiter {
        std::string val;
    };

  public:
    explicit strcat(delimiter del = { "." })
        : _delimiter { std::move(del) } {}

    template<typename T, typename... ARGS>
    strcat(T const& t, ARGS&&... args)
        : strcat(std::forward<ARGS>(args)...) {
        _str = cast(t) + _delimiter.val + _str;
    }

    std::string str() const {
        auto it = _str.begin();
        return { it, it + _str.size() - _delimiter.val.size() };
    }

  private:
    delimiter _delimiter;
    std::string _str;
};

}    // namespace miu::com
