#pragma once

#include <tuple>

#include "clock.hpp"
#include "delta.hpp"

namespace miu::time {

namespace details {
    using daytime = std::chrono::time_point<clock, delta>;
}    // namespace details

class daytime : public details::daytime {
  public:
    daytime(delta = 0);
    daytime(rep hrs, rep min, rep sec, rep ms);
    daytime(std::string_view);    // HH:MM:SS.fff
};
static_assert(sizeof(int32_t) == sizeof(daytime));

}    // namespace miu::time

DEF_VARIANT(miu::time::daytime, 19);
DEF_TO_STRING(miu::time::daytime);
