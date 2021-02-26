#pragma once

#include <cmath>
#include <string>    // std::strtod

#include "time/stamp.hpp"

#include "var_casting.hpp"

namespace miu::com {

template<typename target_type>
class var_decimal : public var_casting<target_type> {
  public:
    var_decimal() {
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

        accept_time<time::days>();
        accept_time<time::delta>();
        accept_time<time::date>();
        accept_time<time::daytime>();
        accept_time<time::stamp>();

        accept_str<const char*>();
        accept_str<std::string>();
    }

  private:
    template<typename source_type>
    static std::optional<target_type> to_decimal(variant const* var) {
        auto src_val = *(source_type const*)var;
        auto tag_val = static_cast<target_type>(src_val);
        if (std::fabs(tag_val - src_val) > 0.0000001) {
            SYSTEM_WARN("PRECISION",
                        type_id<source_type>::name,
                        src_val,
                        "cannot be",
                        type_id<target_type>::name);
            return std::nullopt;
        }
        return tag_val;
    }

    template<typename source_type>
    void accept() {
        this->support(type_id<source_type>::value, &to_decimal<source_type>);
    }

    template<typename source_type>
    void accept_time() {
        this->support(type_id<source_type>::value, [](auto var) {
            auto src_val = *(typename source_type::rep const*)var;
            return std::optional<target_type> { src_val };
        });
    }

    template<typename source_type>
    void accept_str() {
        this->support(type_id<source_type>::value, [](auto var) -> std::optional<target_type> {
            try {
                auto str = var->template get<const char*>().value();
                return std::strtod(str, 0);
            } catch (std::invalid_argument const& err) {
                SYSTEM_WARN(err.what());
                return std::nullopt;
            } catch (std::out_of_range const& err) {
                SYSTEM_WARN(err.what());
                return std::nullopt;
            }
        });
    }
};

}    // namespace miu::com
