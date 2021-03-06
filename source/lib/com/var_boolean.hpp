#pragma once

#include <algorithm>
#include <cctype>

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

        accept_string<std::string>();
        accept_string<const char*>();
    }

  private:
    template<typename source_type>
    void accept() {
        auto func = [](variant const* var) -> std::optional<bool> {
            return static_cast<bool>(*(source_type const*)var);
        };
        support(type_id<source_type>::value, func);
    }

    template<typename source_type>
    void accept_string() {
        auto func = [](variant const* var) -> std::optional<bool> {
            auto constexpr trans = [](auto ch) { return std::toupper(ch); };

            auto str = var->get<std::string>().value();
            std::transform(str.begin(), str.end(), str.begin(), trans);

            std::optional<bool> ret;
            if ("TRUE" == str) {
                ret = std::make_optional(true);
            } else if ("FALSE" == str) {
                ret = std::make_optional(false);
            }
            return ret;
        };
        support(type_id<source_type>::value, func);
    }
};

}    // namespace miu::com
