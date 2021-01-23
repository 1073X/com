#pragma once

#include <iostream>

#include "datetime.hpp"
#include "strcat.hpp"

template<typename... ARGS>
void SYSTEM_WARN(ARGS&&... args) {    // NOLINT
    auto time = miu::com::datetime::now();
    auto del  = miu::com::strcat::delimiter { " " };
    auto msg  = miu::com::strcat { "WARN", time, std::forward<ARGS>(args)..., del };
    std::cerr << msg.str() << std::endl;
}
