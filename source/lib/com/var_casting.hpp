#pragma once

#include <array>
#include <functional>
#include <optional>

#include "com/variant.hpp"

namespace miu::com {

template<typename target_type>
class var_casting {
  public:
    var_casting() {
        for (auto& func : _vec) {
            func = &unsupport;
        }
    }

    std::optional<target_type> operator()(variant const* var) const { return _vec[var->id()](var); }

  protected:
    using func_type = std::function<std::optional<target_type>(variant const*)>;

    void support(uint8_t id, func_type func) { _vec[id] = func; }

  private:
    static std::optional<target_type> unsupport(variant const* var) {
        SYSTEM_WARN("variant(", var->id(), ") is not", type_id<target_type>::name());
        return std::nullopt;
    }

  private:
    std::array<func_type, 256> _vec;
};

}    // namespace miu::com
