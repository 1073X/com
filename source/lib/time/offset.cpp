
#include "time/offset.hpp"

namespace miu::time {

static clock::duration g_value = []() {
    auto utc = std::time(nullptr);
    return std::chrono::seconds { std::localtime(&utc)->tm_gmtoff };
}();

clock::duration offset::get() {
    return g_value;
}

void offset::set(clock::duration v) {
    g_value = v;
}

}    // namespace miu::time
