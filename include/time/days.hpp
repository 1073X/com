#pragma once

#include <chrono>

#include "com/to_string.hpp"
#include "com/variant.hpp"

namespace miu::time {

namespace details {
    using days = std::chrono::duration<int32_t, std::ratio<86400, 1>>;
}

class days : public details::days {
  public:
    days(rep v = 0)
        : details::days(v) {}

    template<typename R, typename P>
    days(std::chrono::duration<R, P> duration)
        : days(std::chrono::duration_cast<details::days>(duration).count()) {}
};
static_assert(sizeof(int32_t) == sizeof(days));

}    // namespace miu::time

DEF_VARIANT(miu::time::days, 17);
