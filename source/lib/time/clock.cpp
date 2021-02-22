
#include "time/clock.hpp"

#include <time.h>

#include "time/offset.hpp"

namespace miu::time {

clock::time_point clock::now() {
    timespec tp;
    ::clock_gettime(CLOCK_REALTIME_COARSE, &tp);
    auto sec  = tp.tv_sec * 1000;
    auto nsec = static_cast<rep>(tp.tv_nsec) / 1'000'000;
    return time_point { duration(sec + nsec) + offset::get() };
}

}    // namespace miu::time
