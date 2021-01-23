

#include "com/days.hpp"

DEF_TO_STRING(miu::com::days) {
    return std::to_string(v.count()) + "d";
}
