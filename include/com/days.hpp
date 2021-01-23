#pragma once

#include <chrono>
#include <string>

#include "to_string.hpp"

namespace miu::com {

using days_base = std::chrono::duration<int32_t, std::ratio<86400, 1>>;
class days : public days_base {
  public:
    days(rep v = 0)
        : days_base(v) {}

    template<typename R, typename P>
    days(std::chrono::duration<R, P> const& du)
        : days(std::chrono::duration_cast<days_base>(du).count()) {}
};

template<>
std::string to_string<days>(days const&);

}    // namespace miu::com
