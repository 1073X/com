
#include "com/daytime.hpp"

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "com/fatal_error.hpp"
#include "com/time_offset.hpp"

using namespace std::chrono_literals;

namespace miu::com {

static_assert(sizeof(int64_t) == sizeof(daytime));

daytime::daytime(duration v)
    : daytime_base(v.count()) {
}

daytime::daytime(rep hrs, rep min, rep sec, rep us)
    : daytime((3600 * hrs + 60 * min + sec) * 1000000LL + us) {
    if (hrs < 0 || min < 0 || sec < 0 || us < 0) {
        FATAL_ERROR<std::underflow_error>(hrs, min, sec, us);
    }
    if (hrs > 23 || min > 59 || sec > 59 || us > 999999) {
        FATAL_ERROR<std::overflow_error>(hrs, min, sec, us);
    }
}

daytime::daytime(std::string_view v)
    : daytime(duration { v }) {
    if (*this > max()) {
        FATAL_ERROR<std::overflow_error>(v);
    }
}

daytime daytime::now() {
    using namespace std::chrono_literals;
    auto time = std::chrono::system_clock::now() + time_offset::get();
    return { time.time_since_epoch() % 24h };
}

daytime daytime::zero() {
    static daytime const MIN_VAL { 0us };
    return MIN_VAL;
}

daytime daytime::min() {
    return zero();
}

daytime daytime::max() {
    static daytime const MAX_VAL { 24h - 1us };
    return MAX_VAL;
}

template<>
std::string to_string<daytime>(daytime const& v) {
    return to_string(v.time_since_epoch());
}

}    // namespace miu::com
