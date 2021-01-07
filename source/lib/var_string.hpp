#pragma once

#include "var_casting.hpp"

namespace miu::com {

class var_string : public var_casting<std::string> {
  public:
    var_string() {
        support(type_id<std::string>::value,
                [](auto var) -> std::optional<std::string> { return (const char*)var; });

        support(type_id<const char*>::value, [](auto var) -> std::optional<std::string> {
            return (const char*)*(uint64_t const*)var;
        });

        accept<int8_t>();
        accept<int16_t>();
        accept<int32_t>();
        accept<int64_t>();
        accept<uint8_t>();
        accept<uint16_t>();
        accept<uint32_t>();
        accept<uint64_t>();
        accept<float>();
        accept<double>();
    }

  private:
    template<typename source_type>
    void accept() {
        support(type_id<source_type>::value, [](auto var) -> std::optional<std::string> {
            return std::to_string(*(source_type const*)var);
        });
    }
};

}    // namespace miu::com