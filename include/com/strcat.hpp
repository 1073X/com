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

    auto size() const { return _vec.size(); }
    auto operator[](uint32_t i) const { return _vec[_vec.size() - i - 1]; }

    auto begin() const { return _vec.rbegin(); }
    auto end() const { return _vec.rend(); }

  private:
    delimiter _delimiter;
    std::vector<std::string> _vec;
};

}    // namespace miu::com

DEF_TO_STRING(miu::com::strcat);
