#pragma once

#include <chrono>
#include <string_view>

namespace miu::com {

using microseconds_base = std::chrono::duration<int64_t, std::ratio<1, 1000000>>;
class microseconds : public microseconds_base {
  public:
    microseconds(rep val = 0)
        : microseconds_base(val) {}

    template<typename R, typename P>
    microseconds(std::chrono::duration<R, P> const& du)
        : microseconds(std::chrono::duration_cast<microseconds_base>(du).count()) {}

    static microseconds create(rep hours, rep minutes, rep seconds, rep microsec);
    static microseconds create(std::string_view);    // HH:MM:SS.ffffff
};

}    // namespace miu::com
