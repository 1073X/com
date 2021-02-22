
#include "time/time.hpp"

#include "time/clock.hpp"

namespace miu::time {

stamp now() {
    return clock::now();
}

date today() {
    return now().date();
}

daytime now_of_day() {
    return now().time();
}

}    // namespace miu::time
