
#include "com/to_string.hpp"

namespace miu::com {

template<>
std::string to_string<char>(char const& v) {
    return { v };
}

template<>
std::string to_string<const char*>(const char* const& v) {
    return v;
}

template<>
std::string to_string<char*>(char* const& v) {
    return v;
}

template<>
std::string to_string<std::string>(std::string const& v) {
    return v;
}

template<>
std::string to_string<std::string_view>(std::string_view const& v) {
    return { v.data(), v.size() };
}

}    // namespace miu::com
