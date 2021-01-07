
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

// boolean
template<>
std::optional<bool>
variant::get<bool>() const {
    static var_boolean cast;
    return cast(this);
}

// integer
template<>
std::optional<int64_t>
variant::get<int64_t>() const {
    static var_number<int64_t> cast;
    return cast(this);
}

template<>
std::optional<int32_t>
variant::get<int32_t>() const {
    static var_number<int32_t> cast;
    return cast(this);
}

template<>
std::optional<int16_t>
variant::get<int16_t>() const {
    static var_number<int16_t> cast;
    return cast(this);
}

template<>
std::optional<int8_t>
variant::get<int8_t>() const {
    static var_number<int8_t> cast;
    return cast(this);
}

template<>
std::optional<uint64_t>
variant::get<uint64_t>() const {
    static var_number<uint64_t> cast;
    return cast(this);
}

template<>
std::optional<uint32_t>
variant::get<uint32_t>() const {
    static var_number<uint32_t> cast;
    return cast(this);
}

template<>
std::optional<uint16_t>
variant::get<uint16_t>() const {
    static var_number<uint16_t> cast;
    return cast(this);
}

template<>
std::optional<uint8_t>
variant::get<uint8_t>() const {
    static var_number<uint8_t> cast;
    return cast(this);
}

// decimal
template<>
std::optional<float>
variant::get<float>() const {
    static var_decimal<float> cast;
    return cast(this);
}

template<>
std::optional<double>
variant::get<double>() const {
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
    : variant(std::string_view { v }) {}
template<>
std::optional<std::string>
variant::get<std::string>() const {
    static var_string cast;
    return cast(this);
}

template<>
std::optional<const char*>
variant::get<const char*>() const {
    switch (_id) {
    case type_id<const char*>::value:
        return (const char*)(*_value);
    case type_id<std::string>::value:
        return (const char*)_value;
    default:
        return std::nullopt;
    }
}

}    // namespace miu::com
