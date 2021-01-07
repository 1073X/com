#pragma once

#include "com/date.hpp"

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
                            type_id<source_type>::name,
                            (int64_t)val,
                            "cannot be",
                            type_id<target_type>::name);
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
                            type_id<source_type>::name,
                            (uint64_t)val,
                            "cannot be",
                            type_id<target_type>::name);
                return std::nullopt;
            }
            return val;
        }
    };

    // int demote to int
    template<typename source_type>
    struct action<true, true, false, source_type> {
        static std::optional<target_type> cast(variant const* var) {
            auto val = *(source_type const*)var;
            if (val > std::numeric_limits<target_type>::max()) {
                SYSTEM_WARN("OVERFLOW",
                            type_id<source_type>::name,
                            (int64_t)val,
                            "cannot be",
                            type_id<target_type>::name);
                return std::nullopt;
            } else if (val < std::numeric_limits<target_type>::min()) {
                SYSTEM_WARN("UNDERFLOW",
                            type_id<source_type>::name,
                            (int64_t)val,
                            "cannot be",
                            type_id<target_type>::name);
                return std::nullopt;
            }
            return val;
        }
    };

    // int demote to uint
    template<typename source_type>
    struct action<true, false, false, source_type> {
        static std::optional<target_type> cast(variant const* var) {
            auto val = *(source_type const*)var;
            if (val > std::numeric_limits<target_type>::max()) {
                SYSTEM_WARN("OVERFLOW",
                            type_id<source_type>::name,
                            (int64_t)val,
                            "cannot be",
                            type_id<target_type>::name);
                return std::nullopt;
            } else if (val < 0) {
                SYSTEM_WARN("NEGATIVE",
                            type_id<source_type>::name,
                            (int64_t)val,
                            "cannot be",
                            type_id<target_type>::name);
                return std::nullopt;
            }
            return val;
        }
    };

    template<typename source_type>
    void accept() {
        auto constexpr is_source_signed = std::is_signed<source_type>::value;
        auto constexpr is_target_signed = std::is_signed<target_type>::value;
        auto constexpr is_promoted = std::numeric_limits<source_type>::digits
                                     <= std::numeric_limits<target_type>::digits;
        auto func = &action<is_source_signed, is_target_signed, is_promoted, source_type>::cast;
        this->support(type_id<source_type>::value, func);
    }
};

}    // namespace miu::com
