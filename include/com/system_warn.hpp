#pragma once

#include <iostream>

#include "datetime.hpp"
#include "strcat.hpp"

template<typename... ARGS>
void SYSTEM_WARN(ARGS&&... args) {    // NOLINT
    auto time      = miu::com::datetime::now();
    auto delimiter = miu::com::strcat::delimiter { " " };
    auto msg       = miu::com::strcat { "WARN", time, args..., delimiter };
    std::cerr << msg.str() << std::endl;
}
