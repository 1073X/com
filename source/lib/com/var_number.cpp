
#include "var_number.hpp"

DEF_VAR_SET(int64_t) {
    new (_value) int64_t { v };
}
DEF_VAR_GET(int64_t) {
    static var_number<int64_t> cast;
    return cast(this);
}

DEF_VAR_SET(int32_t) {
    new (_value) int32_t { v };
}
DEF_VAR_GET(int32_t) {
    static var_number<int32_t> cast;
    return cast(this);
}

DEF_VAR_SET(int16_t) {
    new (_value) int16_t { v };
}
DEF_VAR_GET(int16_t) {
    static var_number<int16_t> cast;
    return cast(this);
}

DEF_VAR_SET(int8_t) {
    new (_value) int8_t { v };
}
DEF_VAR_GET(int8_t) {
    static var_number<int8_t> cast;
    return cast(this);
}

DEF_VAR_SET(uint64_t) {
    new (_value) uint64_t { v };
}
DEF_VAR_GET(uint64_t) {
    static var_number<uint64_t> cast;
    return cast(this);
}

DEF_VAR_SET(uint32_t) {
    new (_value) uint32_t { v };
}
DEF_VAR_GET(uint32_t) {
    static var_number<uint32_t> cast;
    return cast(this);
}

DEF_VAR_SET(uint16_t) {
    new (_value) uint16_t { v };
}
DEF_VAR_GET(uint16_t) {
    static var_number<uint16_t> cast;
    return cast(this);
}

DEF_VAR_SET(uint8_t) {
    new (_value) uint8_t { v };
}
DEF_VAR_GET(uint8_t) {
    static var_number<uint8_t> cast;
    return cast(this);
}
