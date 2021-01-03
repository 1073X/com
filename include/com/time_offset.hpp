#pragma once

#include "microseconds.hpp"

namespace miu::com {

class time_offset {
  public:
    static microseconds get();
    static void set(microseconds);
};

}    // namespace miu::com
