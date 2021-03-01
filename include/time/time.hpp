#pragma once

#include "stamp.hpp"

namespace miu::time {

extern stamp now();

extern daytime time_of_day();

extern date yesterday();
extern date today();
extern date tomorrow();

}    // namespace miu::time
