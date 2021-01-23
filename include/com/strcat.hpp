#pragma once

#include <sstream>
#include <string>    // std::to_string
#include <utility>

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
        _str = std::to_string(t) + _delimiter.val + _str;
    }

    std::string str() const;

  private:
    delimiter _delimiter;
    std::string _str;
};

}    // namespace miu::com
