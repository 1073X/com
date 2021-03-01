
#include "time/time.hpp"

#include "time/clock.hpp"
#include "time/days.hpp"

using namespace std::chrono_literals;

namespace miu::time {

stamp now() {
    return clock::now();
}

date yesterday() {
    return { today().time_since_epoch().count() - 1 };
}

date today() {
    return now().date();
}

date tomorrow() {
    return { today().time_since_epoch().count() + 1 };
}

daytime time_of_day() {
    return now().time();
}

}    // namespace miu::time
