#pragma once

#include <stdexcept>

#include "meta/info.hpp"

#include "strcat.hpp"

namespace miu::com {
std::string make_message(std::string_view);
}

template<typename T = std::runtime_error, typename... ARGS>
void FATAL_ERROR(ARGS&&... args) {    // NOLINT
    auto prefix = miu::com::make_message("ERROR");
    auto del    = miu::com::strcat::delimiter { " " };
    auto msg    = miu::com::strcat { prefix, std::forward<ARGS>(args)..., del };
    throw T { msg.str() };
}
