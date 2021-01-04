
#include "com/daytime.hpp"

#include <iomanip>
#include <sstream>

#include "com/fatal_error.hpp"
#include "com/time_offset.hpp"

using namespace std::chrono_literals;

namespace miu::com {

static_assert(sizeof(int64_t) == sizeof(daytime));

static microseconds const MIN_VAL {};
static microseconds const MAX_VAL { 24h - 1us };

daytime::daytime(duration v)
    : daytime_base(v.count()) {
    if (v < MIN_VAL || v > MAX_VAL) {
        FATAL_ERROR("daytime overflow. duration =", v.count());
    }
}

daytime::daytime(rep hours, rep minutes, rep seconds, rep microsec)
    : daytime((3600 * hours + 60 * minutes + seconds) * 1000000LL + microsec) {}

daytime::daytime(std::string_view v)
    : daytime(duration { v }) {}

daytime
daytime::now() {
    using namespace std::chrono_literals;
    auto time = std::chrono::system_clock::now() + time_offset::get();
    return { time.time_since_epoch() % 24h };
}

daytime
daytime::zero() {
    return MIN_VAL;
}

daytime
daytime::min() {
    return MIN_VAL;
}

daytime
daytime::max() {
    return MAX_VAL;
}

}    // namespace miu::com

namespace std {

string
to_string(miu::com::daytime time) {
    return to_string(time.time_since_epoch());
}

}    // namespace std
