
#include "time/offset.hpp"

namespace miu::time {

static delta g_value = []() {
    auto utc = std::time(nullptr);
    return std::chrono::seconds { std::localtime(&utc)->tm_gmtoff };
}();

delta offset::get() {
    return g_value;
}

void offset::set(delta v) {
    g_value = v;
}

}    // namespace miu::time
