
#include "com/variant.hpp"

#include <algorithm>    // min
#include <cassert>
#include <cmath>      // round
#include <cstring>    // memcpy
#include <iostream>

#include "var_boolean.hpp"
#include "var_decimal.hpp"
#include "var_number.hpp"
#include "var_string.hpp"

namespace miu::com {

bool variant::operator!=(variant another) const {
    auto lhs = &_value[0];
    auto rhs = &another._value[0];
    return lhs[1] != rhs[1] || lhs[0] != rhs[0];
}

#define CASE_TO_STRING(TYPE)   \
    case type_id<TYPE>::value: \
        return "[" #TYPE ":" + to_string(v.get<TYPE>().value()) + "]";

template<>
std::string to_string<variant>(variant const& v) {
    switch (v.id()) {
    case type_id<void>::value:
        return "[void:N/A]";

    case type_id<bool>::value:
        return "[bool:" + to_string(v.get<bool>().value()) + "]";

        CASE_TO_STRING(int8_t);
        CASE_TO_STRING(int16_t);
        CASE_TO_STRING(int32_t);
        CASE_TO_STRING(int64_t);
        CASE_TO_STRING(uint8_t);
        CASE_TO_STRING(uint16_t);
        CASE_TO_STRING(uint32_t);
        CASE_TO_STRING(uint64_t);
        CASE_TO_STRING(float);
        CASE_TO_STRING(double);
        CASE_TO_STRING(std::string);

        CASE_TO_STRING(char);
        CASE_TO_STRING(const char*);

        CASE_TO_STRING(time::delta);
        CASE_TO_STRING(time::days);
        CASE_TO_STRING(time::date);
        CASE_TO_STRING(time::daytime);
        CASE_TO_STRING(time::stamp);

    default:
        return "[UNK_VAR:" + std::to_string(v.id()) + "]";
    }
}

}    // namespace miu::com
