#pragma once

#include <string>

namespace miu::com {

template<typename T>
std::string to_string(T const& v) {
    return std::to_string(v);
}

template<size_t N>
auto to_string(const char (&v)[N]) {
    return to_string<std::string_view>({ v, N });
}

}    // namespace miu::com

#define DEF_TO_STRING(TYPE) \
    template<>              \
    std::string miu::com::to_string<TYPE>(TYPE const& v)

DEF_TO_STRING(char);
DEF_TO_STRING(const char*);
DEF_TO_STRING(char*);
DEF_TO_STRING(std::string);
DEF_TO_STRING(std::string_view);
