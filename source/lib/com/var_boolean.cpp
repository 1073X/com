
#include "var_boolean.hpp"

DEF_VAR_SET(bool) {
    new (_value) bool { v };
}

DEF_VAR_GET(bool) {
    static var_boolean cast;
    return cast(this);
}
