#pragma once

#include "delta.hpp"

namespace miu::time {

struct offset {
    static delta get();
    static void set(delta);
};

}    // namespace miu::time
