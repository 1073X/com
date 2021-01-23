#pragma once

#include <utility>    // std::forward

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
        push(to_string(t));
    }

    std::string str() const;

  private:
    void push(std::string_view);

  private:
    delimiter _delimiter;
    std::string _str;
};

}    // namespace miu::com
