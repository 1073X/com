#pragma once

#include <chrono>

namespace miu::time {

struct clock {
    using duration   = std::chrono::milliseconds;
    using rep        = duration::rep;
    using period     = duration::period;
    using time_point = std::chrono::time_point<clock>;
    enum { is_steady = false };
    static time_point now();
};

}    // namespace miu::time
