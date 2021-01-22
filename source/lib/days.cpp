

#include "com/days.hpp"

namespace miu::com {

static_assert(sizeof(int32_t) == sizeof(days));

}

namespace std {

std::string
to_string(miu::com::days val) {
    return std::to_string(val.count()) + "d";
}

}    // namespace std
