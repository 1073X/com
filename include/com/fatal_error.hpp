#pragma once

#include <stdexcept>

#include "datetime.hpp"
#include "strcat.hpp"

namespace miu::com {

class fatal_error : public std::runtime_error {
  public:
    fatal_error() = delete;
    template<typename... ARGS>
    fatal_error(ARGS&&... args)
        : std::runtime_error(
            strcat { std::forward<ARGS>(args)..., strcat::delimiter { " " } }.str()) {}
};

}    // namespace miu::com

template<typename... ARGS>
void
FATAL_ERROR(ARGS&&... args) {
    auto time = miu::com::datetime::now();
    throw miu::com::fatal_error { "FATAL", time, std::forward<ARGS>(args)... };
}
