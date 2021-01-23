#pragma once

#include <string>

namespace std {

string to_string(char);
string to_string(string_view);

template<size_t N>
auto to_string(const char (&v)[N]) {
    return to_string(string_view { v, N });
}

}    // namespace std
