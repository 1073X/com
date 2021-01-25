
#include "com/to_string.hpp"

#include <cstring>    // std::strlen

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
