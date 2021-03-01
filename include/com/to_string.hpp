#pragma once

#include <string>

namespace miu::com {

template<typename T>
std::string to_string(T const&);

template<size_t N>
auto to_string(const char (&v)[N]) {
    return to_string<std::string_view>({ v, N });
}

}    // namespace miu::com

#define DEF_TO_STRING(TYPE) \
    template<>              \
    std::string miu::com::to_string<TYPE>(TYPE const& v)
