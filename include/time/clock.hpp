#pragma once

#include <chrono>

namespace miu::time {

struct clock {
    using duration   = std::chrono::milliseconds;
    using rep        = duration::rep;
    using period     = duration::period;
    using time_point = std::chrono::time_point<clock>;
    static bool is_steady;
    static time_point now();
};

}    // namespace miu::time
