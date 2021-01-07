#pragma once

#include <optional>
#include <vector>

#include "com/variant.hpp"

namespace miu::com {

template<typename target_type>
class var_casting {
  public:
    std::optional<target_type> operator()(variant const* var) const {
        if (var->id() < _vec.size()) {
            return _vec[var->id()](var);
        }
        return std::nullopt;
    }

  protected:
    using func_type = std::optional<target_type> (*)(variant const*);

    void support(uint8_t id, func_type func) { _vec[id] = func; }

  private:
    static std::optional<target_type> unsupport(variant const* var) {
        SYSTEM_WARN("UNSUPPORTED", var->id(), ":some_type cannot be", type_id<target_type>::name);
        return std::nullopt;
    }

  private:
    std::vector<func_type> _vec { CUSTOM_TYPE_ID, &unsupport };
};

}    // namespace miu::com
