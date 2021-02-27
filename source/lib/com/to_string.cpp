
#include "com/to_string.hpp"

#include <cstring>    // std::strlen
#include <sstream>

DEF_TO_STRING(char) {
    return { v };
}

DEF_TO_STRING(const char*) {
    return v;
}

DEF_TO_STRING(char*) {
    return v;
}

DEF_TO_STRING(std::string) {
    return v;
}

DEF_TO_STRING(std::string_view) {
    auto size = std::min(v.size(), std::strlen(v.data()));
    return { v.data(), size };
}

DEF_TO_STRING(double) {
    std::ostringstream ss;
    ss.precision(16);
    ss << v;
    return ss.str();
}
