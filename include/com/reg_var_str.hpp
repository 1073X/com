#pragma once

#include <functional>

#include "variant.hpp"

namespace miu::com {

/*
 *** Supporting custom type in log system ***
 */

using var_str_func = std::function<std::string(variant const*)>;
extern bool reg_var_str(uint8_t type_id, var_str_func const&);

template<typename T>
auto reg_var_str() {
    reg_var_str(type_id<T>::value, [](auto var) -> std::string {
        auto val = var->template get<T>().value();
        return to_string(val);
    });
}

}    // namespace miu::com

