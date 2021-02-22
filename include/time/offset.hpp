#pragma once

#include "clock.hpp"

namespace miu::time {

struct offset {
    static clock::duration get();
    static void set(clock::duration);
};

}    // namespace miu::time
