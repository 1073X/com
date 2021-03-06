#pragma once

#include <cmath>     // std::round
#include <string>    // std::strtoll

#include "time/stamp.hpp"

#include "var_casting.hpp"

namespace miu::com {

template<typename target_type>
class var_number : public var_casting<target_type> {
  public:
    var_number() {
        accept<bool>();
        accept<char>();
        accept<int8_t>();
        accept<int16_t>();
        accept<uint8_t>();
        accept<int32_t>();
        accept<int64_t>();
        accept<uint16_t>();
        accept<uint32_t>();
        accept<uint64_t>();

        accept_chrono<time::days>();
        accept_chrono<time::delta>();
        accept_chrono<time::date>();
        accept_chrono<time::daytime>();
        accept_chrono<time::stamp>();

        accept_string<const char*>();
        accept_string<std::string>();

        accept_decimal<double>();
        accept_decimal<float>();
    }

  private:
    // int promote to int
    // uint promote to int
    // uint promote to uint
    template<bool is_source_signed, bool is_target_signed, bool is_promoted, typename source_type>
    struct action {
        static std::optional<target_type> cast(variant const* var) {
            return *(source_type const*)var;
        }
    };

    // int promote to uint
    template<typename source_type>
    struct action<true, false, true, source_type> {
        static std::optional<target_type> cast(variant const* var) {
            auto val = *(source_type const*)var;
            if (val < 0) {
                SYSTEM_WARN("NEGATIVE",
                            type_id<source_type>::name(),
                            (int64_t)val,
                            "cannot be",
                            type_id<target_type>::name());
                return std::nullopt;
            }
            return val;
        }
    };

    // uint demote to int
    // uint demote to uint
    template<bool is_target_signed, typename source_type>
    struct action<false, is_target_signed, false, source_type> {
        static std::optional<target_type> cast(variant const* var) {
            auto val = *(source_type const*)var;
            if (val > std::numeric_limits<target_type>::max()) {
                SYSTEM_WARN("OVERFLOW",
                            type_id<source_type>::name(),
                            (uint64_t)val,
                            "cannot be",
                            type_id<target_type>::name());
                return std::nullopt;
            }
            return val;
        }
    };

    // int demote to int
    template<typename source_type>
    struct action<true, true, false, source_type> {
        static std::optional<target_type> cast(variant const* var) {
            std::optional<target_type> opt = std::nullopt;
            auto val                       = *(source_type const*)var;
            if (val > std::numeric_limits<target_type>::max()) {
                SYSTEM_WARN("OVERFLOW",
                            type_id<source_type>::name(),
                            (int64_t)val,
                            "cannot be",
                            type_id<target_type>::name());
            } else if (val < std::numeric_limits<target_type>::min()) {
                SYSTEM_WARN("UNDERFLOW",
                            type_id<source_type>::name(),
                            (int64_t)val,
                            "cannot be",
                            type_id<target_type>::name());
            } else {
                opt = val;
            }
            return opt;
        }
    };

    // int demote to uint
    template<typename source_type>
    struct action<true, false, false, source_type> {
        static std::optional<target_type> cast(variant const* var) {
            std::optional<target_type> opt = std::nullopt;
            auto val                       = *(source_type const*)var;
            if (val > std::numeric_limits<target_type>::max()) {
                SYSTEM_WARN("OVERFLOW",
                            type_id<source_type>::name(),
                            (int64_t)val,
                            "cannot be",
                            type_id<target_type>::name());
            } else if (val < 0) {
                SYSTEM_WARN("NEGATIVE",
                            type_id<source_type>::name(),
                            (int64_t)val,
                            "cannot be",
                            type_id<target_type>::name());
            } else {
                opt = val;
            }
            return opt;
        }
    };

    template<typename source_type>
    void accept() {
        auto constexpr is_source_signed = std::is_signed<source_type>::value;
        auto constexpr is_target_signed = std::is_signed<target_type>::value;
        auto constexpr is_promoted      = std::numeric_limits<source_type>::digits
                                  <= std::numeric_limits<target_type>::digits;
        auto func = &action<is_source_signed, is_target_signed, is_promoted, source_type>::cast;
        this->support(type_id<source_type>::value, func);
    }

    template<typename chrono_type>
    void accept_chrono() {
        using source_type = typename chrono_type::rep;

        auto constexpr is_source_signed = std::is_signed<source_type>::value;
        auto constexpr is_target_signed = std::is_signed<target_type>::value;
        auto constexpr is_promoted      = std::numeric_limits<source_type>::digits
                                  <= std::numeric_limits<target_type>::digits;
        auto func = &action<is_source_signed, is_target_signed, is_promoted, source_type>::cast;
        this->support(type_id<chrono_type>::value, [func](auto var) -> std::optional<target_type> {
            auto val = func(var);
            if (val) {
                return target_type { val.value() };
            }
            return std::nullopt;
        });
    }

    template<typename string_type>
    void accept_string() {
        using source_type = int64_t;

        auto constexpr is_source_signed = std::is_signed<source_type>::value;
        auto constexpr is_target_signed = std::is_signed<target_type>::value;
        auto constexpr is_promoted      = std::numeric_limits<source_type>::digits
                                  <= std::numeric_limits<target_type>::digits;
        auto func = &action<is_source_signed, is_target_signed, is_promoted, source_type>::cast;
        this->support(type_id<string_type>::value, [func](auto var) -> std::optional<target_type> {
            try {
                auto str = var->template get<const char*>().value();
                auto tmp = variant { static_cast<source_type>(std::stoll(str, 0)) };
                auto val = func(&tmp);
                if (val) {
                    return target_type { val.value() };
                }
                return std::nullopt;
            } catch (std::invalid_argument const& err) {
                SYSTEM_WARN(err.what());
                return std::nullopt;
            } catch (std::out_of_range const& err) {
                SYSTEM_WARN(err.what());
                return std::nullopt;
            }
        });
    }

    template<typename decimal_type>
    void accept_decimal() {
        // TBD: cannot convert extreme value of 64 bytes signed/unsigned integer
        this->support(type_id<decimal_type>::value, [](auto var) -> std::optional<target_type> {
            constexpr auto tag_min = decimal_type { std::numeric_limits<target_type>::lowest() };
            constexpr auto tag_max = decimal_type { std::numeric_limits<target_type>::max() };

            decimal_type dec_val = *(decimal_type const*)var;
            decimal_type int_val = std::round(dec_val);
            if (std::fabs(dec_val - int_val) < 0.000000001 && int_val <= tag_max
                && int_val >= tag_min) {
                return static_cast<target_type>(int_val);
            }
            return std::nullopt;
        });
    }
};

}    // namespace miu::com
