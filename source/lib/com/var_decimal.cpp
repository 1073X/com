
#include "var_decimal.hpp"

DEF_VAR_SET(float) {
    new (_value) float { v };
}
DEF_VAR_GET(float) {
    static var_decimal<float> cast;
    return cast(this);
}

DEF_VAR_SET(double) {
    new (_value) double { v };
}
DEF_VAR_GET(double) {
    static var_decimal<double> cast;
    return cast(this);
}
