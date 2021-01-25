#pragma once

#include <vector>

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
        _vec.push_back(to_string(t));
    }

    std::string str() const;

  private:
    delimiter _delimiter;
    std::vector<std::string> _vec;
};

}    // namespace miu::com
