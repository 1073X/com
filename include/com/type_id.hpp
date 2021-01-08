#pragma once

#include <string>

#include "date.hpp"
#include "datetime.hpp"
#include "daytime.hpp"

#define DEF_TYPE_ID(TYPE, ID)                                     \
    template<>                                                    \
    struct miu::com::type_id<TYPE> {                              \
        static uint8_t constexpr value { ID };                    \
        static std::string_view constexpr name { #ID ":" #TYPE }; \
    }

namespace miu::com {

template<typename>
struct type_id;

DEF_TYPE_ID(std::string, 0);
DEF_TYPE_ID(std::string_view, 0);

DEF_TYPE_ID(bool, 1);

DEF_TYPE_ID(int8_t, 2);
DEF_TYPE_ID(int16_t, 3);
DEF_TYPE_ID(int32_t, 4);
DEF_TYPE_ID(int64_t, 5);

DEF_TYPE_ID(uint8_t, 6);
DEF_TYPE_ID(uint16_t, 7);
DEF_TYPE_ID(uint32_t, 8);
DEF_TYPE_ID(uint64_t, 9);

DEF_TYPE_ID(float, 10);
DEF_TYPE_ID(double, 11);

DEF_TYPE_ID(char, 12);
DEF_TYPE_ID(const char*, 13);

DEF_TYPE_ID(wchar_t, 14);
DEF_TYPE_ID(const wchar_t*, 15);

DEF_TYPE_ID(microseconds, 16);
DEF_TYPE_ID(days, 17);
DEF_TYPE_ID(date, 18);
DEF_TYPE_ID(daytime, 19);
DEF_TYPE_ID(datetime, 20);

static const uint8_t CUSTOM_TYPE_ID = 32;

DEF_TYPE_ID(void, 255);

}    // namespace miu::com

