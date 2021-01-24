#pragma once

#include "var_casting.hpp"

namespace miu::com {

template<typename target_type>
class var_chrono : public var_casting<target_type> {
  public:
    var_chrono() {
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
    static std::optional<target_type> to_chrono(variant const* var) {
        auto val = var->get<typename target_type::rep>();
        if (val) {
            return target_type { val.value() };
        }
        return std::nullopt;
    }

    template<typename source_type>
    void accept() {
        this->support(type_id<source_type>::value, &to_chrono);
    }
};

}    // namespace miu::com
