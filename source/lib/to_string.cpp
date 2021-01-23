
#include "com/to_string.hpp"

namespace std {

std::string to_string(char v) {
    return { v };
}

std::string to_string(std::string_view v) {
    return v.data();
}

}    // namespace std
