#include <gtest/gtest.h>

#include "com/type_id.hpp"

using miu::com::type_id;

TEST(ut_type_id, primitive_type) {
    EXPECT_EQ(0xFF, type_id<void>::value);
    EXPECT_EQ("255:void", type_id<void>::name);

    EXPECT_EQ(1U, type_id<bool>::value);

    EXPECT_EQ(2U, type_id<int8_t>::value);
    EXPECT_EQ(3U, type_id<int16_t>::value);
    EXPECT_EQ(4U, type_id<int32_t>::value);
    EXPECT_EQ(5U, type_id<int64_t>::value);

    EXPECT_EQ(6U, type_id<uint8_t>::value);
    EXPECT_EQ(7U, type_id<uint16_t>::value);
    EXPECT_EQ(8U, type_id<uint32_t>::value);
    EXPECT_EQ(9U, type_id<uint64_t>::value);

    EXPECT_EQ(10U, type_id<float>::value);
    EXPECT_EQ(11U, type_id<double>::value);

    EXPECT_EQ(12U, type_id<char>::value);
    EXPECT_EQ(13U, type_id<const char*>::value);
    EXPECT_EQ(0U, type_id<std::string>::value);
    EXPECT_EQ(0U, type_id<std::string_view>::value);

    EXPECT_EQ(14U, type_id<wchar_t>::value);
    EXPECT_EQ(15U, type_id<const wchar_t*>::value);

    EXPECT_EQ(16U, type_id<miu::com::microseconds>::value);
    EXPECT_EQ(17U, type_id<miu::com::days>::value);
    EXPECT_EQ(18U, type_id<miu::com::date>::value);
    EXPECT_EQ(19U, type_id<miu::com::daytime>::value);
    EXPECT_EQ(20U, type_id<miu::com::datetime>::value);
}

struct custom {};
DEF_TYPE_ID(custom, 132);

TEST(ut_type_id, custom_type) {
    EXPECT_EQ(132, type_id<custom>::value);
    EXPECT_EQ("132:custom", type_id<custom>::name);
}
