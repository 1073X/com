#pragma once

#include <tuple>

#include "microseconds.hpp"

namespace miu::com {

struct daytime_clock {
    using duration = microseconds;
    using rep      = duration::rep;
    using period   = duration::period;
    // using time_point = std::chrono::time_point<std::chrono::system_clock, duration>;
    // inline static bool is_steady = true;
    // static time_point now();
};

using daytime_base = std::chrono::time_point<daytime_clock>;
class daytime : public daytime_base {
  public:
    daytime(daytime_base::duration = { 0 });
    daytime(rep hrs, rep min, rep sec, rep us);
    daytime(std::string_view);    // HH:MM:SS.ffffff

    static daytime now();
    static daytime min();
    static daytime max();
    static daytime zero();
};

template<>
std::string to_string<daytime>(daytime const&);

}    // namespace miu::com
