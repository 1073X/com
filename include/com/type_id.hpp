#pragma once

#include <string>

#include "date.hpp"
#include "datetime.hpp"
#include "daytime.hpp"

namespace miu::com {

template<typename>
struct type_id;

#define DEF_PRIMITIVE_ID(TYPE, ID)                                \
    template<>                                                    \
    struct type_id<TYPE> {                                        \
        static uint8_t constexpr value { ID };                    \
        static std::string_view constexpr name { #ID ":" #TYPE }; \
    }

DEF_PRIMITIVE_ID(std::string, 0);
DEF_PRIMITIVE_ID(std::string_view, 0);

DEF_PRIMITIVE_ID(bool, 1);

DEF_PRIMITIVE_ID(int8_t, 2);
DEF_PRIMITIVE_ID(int16_t, 3);
DEF_PRIMITIVE_ID(int32_t, 4);
DEF_PRIMITIVE_ID(int64_t, 5);

DEF_PRIMITIVE_ID(uint8_t, 6);
DEF_PRIMITIVE_ID(uint16_t, 7);
DEF_PRIMITIVE_ID(uint32_t, 8);
DEF_PRIMITIVE_ID(uint64_t, 9);

DEF_PRIMITIVE_ID(float, 10);
DEF_PRIMITIVE_ID(double, 11);

DEF_PRIMITIVE_ID(char, 12);
DEF_PRIMITIVE_ID(const char*, 13);

DEF_PRIMITIVE_ID(wchar_t, 14);
DEF_PRIMITIVE_ID(const wchar_t*, 15);

DEF_PRIMITIVE_ID(microseconds, 16);
DEF_PRIMITIVE_ID(days, 17);
DEF_PRIMITIVE_ID(date, 18);
DEF_PRIMITIVE_ID(daytime, 19);
DEF_PRIMITIVE_ID(datetime, 20);

static const uint8_t CUSTOM_TYPE_ID = 64;

DEF_PRIMITIVE_ID(void, 255);

}    // namespace miu::com

#define DEF_TYPE_ID(TYPE, ID)                                     \
    template<>                                                    \
    struct type_id<TYPE> {                                        \
        static_assert((ID) > miu::com::CUSTOM_TYPE_ID);           \
        static_assert((ID) < miu::com::type_id<void>::value);     \
        static uint8_t constexpr value { ID };                    \
        static std::string_view constexpr name { #ID ":" #TYPE }; \
    }
