#pragma once

#include "source/lib/com/var_casting.hpp"

namespace miu::time {

template<typename target_type>
class var_casting : public com::var_casting<target_type> {
  public:
    var_casting() {
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
    static std::optional<target_type> to_chrono(com::variant const* var) {
        auto val = var->get<typename target_type::rep>();
        if (val) {
            return target_type { val.value() };
        }
        return std::nullopt;
    }

    template<typename source_type>
    void accept() {
        this->support(com::type_id<source_type>::value, &to_chrono);
    }
};

}    // namespace miu::time
