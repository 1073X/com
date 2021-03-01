
#include "var_string.hpp"

#include <cstring>    // std::memcpy

namespace miu::com {

variant::variant(std::string const& v)
    : _id { type_id<std::string>::value } {
    auto size = std::min(15UL, v.size());
    std::memcpy(_value, v.data(), size);
}

variant::variant(std::string_view const& v)
    : variant(std::string { v }) {    // treat string_view as string
}

var_string::var_string() {
    auto func = [](auto var) -> std::optional<std::string> { return (const char*)var; };
    support(type_id<std::string>::value, func);
    support(type_id<std::string_view>::value, func);

    accept<bool>();

    accept<int8_t>();
    accept<int16_t>();
    accept<int32_t>();
    accept<int64_t>();
    accept<uint8_t>();
    accept<uint16_t>();
    accept<uint32_t>();
    accept<uint64_t>();
    accept<float>();
    accept<double>();

    accept<char>();
    accept<const char*>();

    accept<time::days>();
    accept<time::delta>();
    accept<time::date>();
    accept<time::daytime>();
    accept<time::stamp>();
}

bool var_string::enroll(uint8_t type_id, var_str_func const& func) {
    support(type_id, [func](auto var) -> std::optional<std::string> { return func(var); });
    return true;
}

var_string var_string::_instance;

bool reg_var_str(uint8_t type_id, var_str_func const& func) {
    return var_string::instance()->enroll(type_id, func);
}

}    // namespace miu::com

DEF_VAR_GET(std::string) {
    return var_string::instance()->operator()(this);
}

DEF_VAR_SET(char) {
    new (_value) char { v };
}
DEF_VAR_GET(char) {
    if (UNLIKELY(type_id<char>::value != _id)) {
        SYSTEM_WARN("variant(", _id, ") is not", type_id<char>::name());
        return std::nullopt;
    }
    return *(char const*)_value;
}

DEF_VAR_SET(const char*) {
    new (_value) const char* { v };
}
DEF_VAR_GET(const char*) {
    switch (_id) {
    case type_id<const char*>::value:
        return (const char*)(*_value);
    case type_id<std::string>::value:
        return (const char*)_value;
    default:
        return std::nullopt;
    }
}

DEF_VAR_SET(wchar_t) {
    new (_value) wchar_t { v };
}
DEF_VAR_GET(wchar_t) {
    if (UNLIKELY(type_id<wchar_t>::value != _id)) {
        SYSTEM_WARN("variant(", _id, ") is not", type_id<wchar_t>::name());
        return std::nullopt;
    }
    return *(wchar_t const*)_value;
}

DEF_VAR_SET(wchar_t const*) {
    new (_value) wchar_t const* { v };
}
DEF_VAR_GET(wchar_t const*) {
    if (UNLIKELY(type_id<wchar_t const*>::value != _id)) {
        SYSTEM_WARN("variant(", _id, ") is not", type_id<wchar_t const*>::name());
        return std::nullopt;
    }
    return *(wchar_t const* const*)_value;
}
