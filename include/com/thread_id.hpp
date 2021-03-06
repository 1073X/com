#pragma once

#include <cstdint>    // int32_t

namespace miu::com {

class thread_id {
  public:
    static constexpr int32_t max() { return 15; }
    static int32_t get();
    static void reset();
};

}    // namespace miu::com
