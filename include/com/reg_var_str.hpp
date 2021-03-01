#pragma once

#include "variant.hpp"

namespace miu::com {

extern void reg_var_str(uint8_t type_id, std::function<std::string(variant const*)> const&);

}    // namespace miu::com
