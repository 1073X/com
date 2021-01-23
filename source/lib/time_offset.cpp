
#include "com/time_offset.hpp"

namespace miu::com {

static microseconds g_time_offset;

microseconds time_offset::get() {
    return g_time_offset;
}

void time_offset::set(microseconds val) {
    g_time_offset = val;
}

}    // namespace miu::com
