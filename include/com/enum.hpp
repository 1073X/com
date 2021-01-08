#pragma once

#include <magic_enum.hpp>

namespace miu::com {

template<typename T>
T
to_enum(std::string_view str) {
    auto opt = magic_enum::enum_cast<T>(str);
    if (!opt.has_value()) {
        return T::MAX;
    }
    return opt.value();
}

}    // namespace miu::com

namespace std {

template<typename T>
const char*
to_string(T val) {
    static auto constexpr names = magic_enum::enum_names<T>();

    auto idx = magic_enum::enum_integer(val);
    auto str = names.back().data();
    if (idx < names.size() - 1) {
        str = names[idx].data();
    }
    return str;
}

}    // namespace std
