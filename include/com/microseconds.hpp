#pragma once

#include <chrono>
#include <string_view>

namespace miu::com {

class microseconds : public std::chrono::microseconds {
  public:
    microseconds(rep val = 0)
        : std::chrono::microseconds(val) {}

    template<typename R, typename P>
    microseconds(std::chrono::duration<R, P> const& du)
        : microseconds(std::chrono::duration_cast<std::chrono::microseconds>(du).count()) {}

    microseconds(rep hours, rep minutes, rep seconds, rep microsec);
    microseconds(std::string_view);    // HH:MM:SS.ffffff
};

}    // namespace miu::com
