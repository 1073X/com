
#include "com/to_string.hpp"

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
    return { v.data(), v.size() };
}

