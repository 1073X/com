#pragma once

#include <chrono>

#include "com/to_string.hpp"
#include "com/variant.hpp"

namespace miu::time {

namespace details {
    using delta = std::chrono::duration<int32_t, std::milli>;
}

class delta : public details::delta {
  public:
    delta(rep val = 0)
        : details::delta(val) {}

    template<typename R, typename P>
    delta(std::chrono::duration<R, P> const& du)
        : delta(std::chrono::duration_cast<details::delta>(du).count()) {}
};
static_assert(sizeof(int32_t) == sizeof(delta));

}    // namespace miu::time

DEF_VARIANT(miu::time::delta, 17);
DEF_TO_STRING(miu::time::delta);
