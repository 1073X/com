

#include "com/days.hpp"

namespace miu::com {

static_assert(sizeof(int32_t) == sizeof(days));

template<>
std::string to_string<days>(days const& val) {
    return std::to_string(val.count()) + "d";
}

}    // namespace miu::com
