#pragma once

#include <chrono>
#include <string_view>

#include "to_string.hpp"

namespace miu::com {

class microseconds : public std::chrono::microseconds {
  public:
    microseconds(rep val = 0)
        : std::chrono::microseconds(val) {}

    template<typename R, typename P>
    microseconds(std::chrono::duration<R, P> const& du)
        : microseconds(std::chrono::duration_cast<std::chrono::microseconds>(du).count()) {}

    microseconds(std::string_view);    // HH:MM:SS.ffffff
};

}    // namespace miu::com

DEF_TO_STRING(miu::com::microseconds);
