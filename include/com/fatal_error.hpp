#pragma once

#include <stdexcept>

#include "strcat.hpp"

namespace miu::com {

class fatal_error : public std::runtime_error {
  public:
    template<typename... ARGS>
    fatal_error(ARGS&&... args)
        : std::runtime_error(
            strcat { std::forward<ARGS>(args)..., strcat::delimiter { " " } }.str()) {}
};

}    // namespace miu::com

template<typename... ARGS>
void
FATAL_ERROR(ARGS&&... args) {
    throw miu::com::fatal_error { std::forward<ARGS>(args)... };
}
