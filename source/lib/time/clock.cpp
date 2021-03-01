
#include "time/clock.hpp"

#include <time.h>

#include "time/offset.hpp"

namespace miu::time {

bool clock::is_steady { false };

clock::time_point clock::now() {
    timespec tp;
    ::clock_gettime(CLOCK_REALTIME_COARSE, &tp);
    auto sec  = tp.tv_sec * 1000;
    auto nsec = static_cast<rep>(tp.tv_nsec) / 1'000'000;
    // TBD: optimize, return time offset in milliseconds
    return time_point { duration(sec + nsec) + offset::get() };
}

}    // namespace miu::time
