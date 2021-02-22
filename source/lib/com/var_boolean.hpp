#pragma once

#include "var_casting.hpp"

namespace miu::com {

class var_boolean : public var_casting<bool> {
  public:
    var_boolean() {
        accept<bool>();
        accept<int8_t>();
        accept<int16_t>();
        accept<int32_t>();
        accept<int64_t>();
        accept<uint8_t>();
        accept<uint16_t>();
        accept<uint32_t>();
        accept<uint64_t>();
    }

  private:
    template<typename source_type>
    void accept() {
        auto func = [](variant const* var) -> std::optional<bool> {
            return static_cast<bool>(*(source_type const*)var);
        };
        support(type_id<source_type>::value, func);
    }
};

}    // namespace miu::com
