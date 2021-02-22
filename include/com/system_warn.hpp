#pragma once

#include <iostream>

#include "meta/info.hpp"

#include "strcat.hpp"

namespace miu::com {
std::string make_message(std::string_view);
}

template<typename... ARGS>
void SYSTEM_WARN(ARGS&&... args) {    // NOLINT
    auto prefix = miu::com::make_message("WARN");
    auto del    = miu::com::strcat::delimiter { " " };
    auto msg    = miu::com::strcat { prefix, std::forward<ARGS>(args)..., del };
    std::cerr << msg.str() << std::endl;
}
