#pragma once

#include <optional>

#include "date.hpp"
#include "datetime.hpp"
#include "daytime.hpp"
#include "predict.hpp"
#include "system_warn.hpp"
#include "to_string.hpp"

namespace miu::com {

template<typename T = void>
struct type_id {
    static uint8_t constexpr value { 255 };
    inline static const char* name { "255:void" };
};

static const uint8_t CUSTOM_TYPE_ID = 32;

class variant {
  public:
    variant()
        : _id { type_id<void>::value } {}

    variant(std::string_view const&);
    variant(std::string const&);

    bool operator!=(variant) const;
    auto operator==(variant rhs) const { return !operator!=(rhs); }

    template<typename T>
    variant(T const& v)
        : _id { type_id<T>::value } {
        set(v);
    }

    template<typename T>
    std::optional<T> get() const;
    auto id() const { return _id; }

  private:
    template<typename T>
    void set(T const& v);

    auto extra() const { return _extra; }

  private:
    uint64_t _value[1] {};
    uint8_t _extra[7] {};
    uint8_t _id { 0 };
};
static_assert(sizeof(variant) == 16);

}    // namespace miu::com

DEF_TO_STRING(miu::com::variant);

#define DEF_VARIANT(TYPE, ID)                             \
    template<>                                            \
    struct miu::com::type_id<TYPE> {                      \
        static uint8_t constexpr value { ID };            \
        inline static const char* name { #ID ":" #TYPE }; \
    };                                                    \
    template<>                                            \
    void miu::com::variant::set<TYPE>(TYPE const&);       \
    template<>                                            \
    std::optional<TYPE> miu::com::variant::get<TYPE>() const

DEF_VARIANT(std::string, 0);
DEF_VARIANT(std::string_view, 0);

DEF_VARIANT(bool, 1);

DEF_VARIANT(int8_t, 2);
DEF_VARIANT(int16_t, 3);
DEF_VARIANT(int32_t, 4);
DEF_VARIANT(int64_t, 5);

DEF_VARIANT(uint8_t, 6);
DEF_VARIANT(uint16_t, 7);
DEF_VARIANT(uint32_t, 8);
DEF_VARIANT(uint64_t, 9);

DEF_VARIANT(float, 10);
DEF_VARIANT(double, 11);

DEF_VARIANT(char, 12);
DEF_VARIANT(const char*, 13);

DEF_VARIANT(wchar_t, 14);
DEF_VARIANT(const wchar_t*, 15);

DEF_VARIANT(miu::com::microseconds, 16);
DEF_VARIANT(miu::com::days, 17);
DEF_VARIANT(miu::com::date, 18);
DEF_VARIANT(miu::com::daytime, 19);
DEF_VARIANT(miu::com::datetime, 20);
