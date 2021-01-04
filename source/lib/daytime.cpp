
#include "com/daytime.hpp"

#include <iomanip>
#include <sstream>

#include "com/time_offset.hpp"

namespace miu::com {

static_assert(sizeof(int64_t) == sizeof(daytime));

daytime::daytime(duration v)
    : daytime_base(v.count()) {}

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
    return daytime();
}

daytime
daytime::min() {
    return zero();
}

daytime
daytime::max() {
    return { 24, 0, 0, 0 };
}

}    // namespace miu::com

namespace std {

string
to_string(miu::com::daytime time) {
    return to_string(time.time_since_epoch());
}

}    // namespace std
