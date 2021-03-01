#pragma once

#include "time/stamp.hpp"

#include "var_casting.hpp"

namespace miu::com {

class var_string : public var_casting<std::string> {
  public:
    var_string() {
        auto func = [](auto var) -> std::optional<std::string> { return (const char*)var; };
        support(type_id<std::string>::value, func);
        support(type_id<std::string_view>::value, func);

        accept<bool>();

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

        accept<char>();
        accept<const char*>();

        accept<time::days>();
        accept<time::delta>();
        accept<time::date>();
        accept<time::daytime>();
        accept<time::stamp>();
    }

  private:
    template<typename source_type>
    void accept() {
        support(type_id<source_type>::value, [](auto var) -> std::optional<std::string> {
            return to_string(*(source_type const*)var);
        });
    }
};

}    // namespace miu::com
