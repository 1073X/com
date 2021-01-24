
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

#define DEFAULT_SET(TYPE)                    \
    template<>                               \
    void variant::set<TYPE>(TYPE const& v) { \
        new (_value)(TYPE) { v };            \
    }

#define DEFAULT_GET(TYPE)                                                                 \
    template<>                                                                            \
    std::optional<TYPE> variant::get<TYPE>() const {                                      \
        if (UNLIKELY(type_id<TYPE>::value != _id)) {                                      \
            SYSTEM_WARN("UNSUPPORTED", _id, ":some_type cannot be", type_id<TYPE>::name); \
            return std::nullopt;                                                          \
        }                                                                                 \
        return *(TYPE const*)_value;                                                      \
    }

namespace miu::com {

bool variant::operator!=(variant another) const {
    auto lhs = &_value[0];
    auto rhs = &another._value[0];
    return lhs[1] != rhs[1] || lhs[0] != rhs[0];
}

// boolean
DEFAULT_SET(bool);
template<>
std::optional<bool> variant::get<bool>() const {
    static var_boolean cast;
    return cast(this);
}

// integer
DEFAULT_SET(int64_t);
template<>
std::optional<int64_t> variant::get<int64_t>() const {
    static var_number<int64_t> cast;
    return cast(this);
}

DEFAULT_SET(int32_t);
template<>
std::optional<int32_t> variant::get<int32_t>() const {
    static var_number<int32_t> cast;
    return cast(this);
}

DEFAULT_SET(int16_t);
template<>
std::optional<int16_t> variant::get<int16_t>() const {
    static var_number<int16_t> cast;
    return cast(this);
}

DEFAULT_SET(int8_t);
template<>
std::optional<int8_t> variant::get<int8_t>() const {
    static var_number<int8_t> cast;
    return cast(this);
}

DEFAULT_SET(uint64_t);
template<>
std::optional<uint64_t> variant::get<uint64_t>() const {
    static var_number<uint64_t> cast;
    return cast(this);
}

DEFAULT_SET(uint32_t);
template<>
std::optional<uint32_t> variant::get<uint32_t>() const {
    static var_number<uint32_t> cast;
    return cast(this);
}

DEFAULT_SET(uint16_t);
template<>
std::optional<uint16_t> variant::get<uint16_t>() const {
    static var_number<uint16_t> cast;
    return cast(this);
}

DEFAULT_SET(uint8_t);
template<>
std::optional<uint8_t> variant::get<uint8_t>() const {
    static var_number<uint8_t> cast;
    return cast(this);
}

// decimal
DEFAULT_SET(float);
template<>
std::optional<float> variant::get<float>() const {
    static var_decimal<float> cast;
    return cast(this);
}

DEFAULT_SET(double);
template<>
std::optional<double> variant::get<double>() const {
    static var_decimal<double> cast;
    return cast(this);
}

// string
variant::variant(std::string_view const& v)
    : _id { type_id<std::string_view>::value } {
    auto size = std::min(15UL, v.size());
    std::memcpy(_value, v.data(), size);
}

variant::variant(std::string const& v)
    : variant(std::string_view { v }) {
}
template<>
std::optional<std::string> variant::get<std::string>() const {
    static var_string cast;
    return cast(this);
}

DEFAULT_SET(char);
DEFAULT_GET(char);

DEFAULT_SET(const char*);
template<>
std::optional<const char*> variant::get<const char*>() const {
    switch (_id) {
    case type_id<const char*>::value:
        return (const char*)(*_value);
    case type_id<std::string>::value:
        return (const char*)_value;
    default:
        return std::nullopt;
    }
}

DEFAULT_SET(wchar_t);
DEFAULT_GET(wchar_t);

DEFAULT_SET(wchar_t const*);
DEFAULT_GET(wchar_t const*);

// chrono
DEFAULT_SET(microseconds);
template<>
std::optional<microseconds> variant::get<microseconds>() const {
    switch (_id) {
    case type_id<microseconds>::value:
        return *(microseconds const*)_value;
    case type_id<const char*>::value:
        return microseconds { (const char*)*_value };
    case type_id<std::string>::value:
        return microseconds { (const char*)_value };
    case type_id<int64_t>::value:
        return microseconds { *(int64_t const*)_value };
    // TBD: map other integer type ...
    default:
        return std::nullopt;
    }
}

DEFAULT_SET(days);
DEFAULT_GET(days);

DEFAULT_SET(date);
template<>
std::optional<date> variant::get<date>() const {
    switch (_id) {
    case type_id<date>::value:
        return *(date const*)_value;
    case type_id<const char*>::value:
        return date { (const char*)*_value };
    case type_id<std::string>::value:
        return date { (const char*)_value };
    default:
        return std::nullopt;
    }
}

DEFAULT_SET(daytime);
template<>
std::optional<daytime> variant::get<daytime>() const {
    switch (_id) {
    case type_id<daytime>::value:
        return *(daytime const*)_value;
    case type_id<const char*>::value:
        return daytime { (const char*)*_value };
    case type_id<std::string>::value:
        return daytime { (const char*)_value };
    default:
        return std::nullopt;
    }
}

DEFAULT_SET(datetime);
template<>
std::optional<datetime> variant::get<datetime>() const {
    switch (_id) {
    case type_id<datetime>::value:
        return *(datetime const*)_value;
    case type_id<const char*>::value:
        return datetime { (const char*)*_value };
    default:
        return std::nullopt;
    }
}

}    // namespace miu::com
