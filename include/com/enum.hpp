#pragma once

#include <magic_enum.hpp>

namespace miu::com {

template<typename ENUM, typename T>
ENUM val_to_enum(T val) {
    auto opt = magic_enum::enum_cast<ENUM>(val);
    if (!opt.has_value()) {
        return ENUM::MAX;
    }
    return opt.value();
}

template<typename T>
const char* enum_to_str(T val) {
    static auto constexpr names = magic_enum::enum_names<T>();

    auto idx = magic_enum::enum_integer(val);
    auto str = names.back().data();
    if (idx < names.size() - 1) {
        str = names[idx].data();
    }
    return str;
}

}    // namespace miu::com
