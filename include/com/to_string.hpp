#pragma once

#include <string>

namespace miu::com {

template<typename T>
std::string to_string(T const& v) {
    return std::to_string(v);
}

template<>
std::string to_string<char>(char const&);
template<>
std::string to_string<const char*>(const char* const&);
template<>
std::string to_string<char*>(char* const&);
template<>
std::string to_string<std::string>(std::string const&);
template<>
std::string to_string<std::string_view>(std::string_view const&);

template<size_t N>
auto to_string(const char (&v)[N]) {
    return to_string<std::string_view>({ v, N });
}

}    // namespace miu::com
