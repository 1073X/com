#pragma once

#include <stdexcept>

#include "datetime.hpp"
#include "strcat.hpp"

template<typename... ARGS>
void
FATAL_ERROR(ARGS&&... args) {    // NOLINT
    auto time = miu::com::datetime::now();
    auto delimiter = miu::com::strcat::delimiter { " " };
    auto msg = miu::com::strcat { "FATAL", time, args..., delimiter };
    throw std::runtime_error { msg.str() };
}
