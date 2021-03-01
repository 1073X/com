#pragma once

#include <optional>

#include "predict.hpp"
#include "system_warn.hpp"
#include "to_string.hpp"
#include "type_id.hpp"

namespace miu::com {

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
    void set(T const&);

    auto extra() const { return _extra; }

  private:
    uint64_t _value[1] {};
    uint8_t _extra[7] {};
    uint8_t _id { 0 };
};
static_assert(sizeof(variant) == 16);

}    // namespace miu::com

DEF_TO_STRING(miu::com::variant);

#define DEF_VAR_SET(TYPE) \
    template<>            \
    void miu::com::variant::set<TYPE>(TYPE const& v)
#define DEF_VAR_GET(TYPE) \
    template<>            \
    std::optional<TYPE> miu::com::variant::get<TYPE>() const
#define DEF_VARIANT(TYPE, ID) \
    DEF_VAR_SET(TYPE);        \
    DEF_VAR_GET(TYPE);        \
    DEF_TYPE_ID(TYPE, ID);    \
    DEF_TO_STRING(TYPE)

DEF_VARIANT(std::string, 0);
DEF_VARIANT(std::string_view, 1);

DEF_VARIANT(bool, 2);

DEF_VARIANT(int8_t, 3);
DEF_VARIANT(int16_t, 4);
DEF_VARIANT(int32_t, 5);
DEF_VARIANT(int64_t, 6);

DEF_VARIANT(uint8_t, 7);
DEF_VARIANT(uint16_t, 8);
DEF_VARIANT(uint32_t, 9);
DEF_VARIANT(uint64_t, 10);

DEF_VARIANT(float, 11);
DEF_VARIANT(double, 12);

DEF_VARIANT(char, 13);
DEF_VARIANT(const char*, 14);

DEF_VARIANT(wchar_t, 15);
DEF_VARIANT(const wchar_t*, 16);
