#include <gtest/gtest.h>

#include "com/variant.hpp"

using miu::com::type_id;
using miu::com::variant;

TEST(ut_variant, void) {
    auto var = variant {};
    EXPECT_EQ(type_id<void>::value, var.id());

    EXPECT_FALSE(var.get<int8_t>().has_value());
    EXPECT_FALSE(var.get<std::string>().has_value());
    EXPECT_FALSE(var.get<bool>().has_value());
    EXPECT_FALSE(var.get<double>().has_value());
}

TEST(ut_variant, wchar) {
    wchar_t ch = L'害';
    auto var   = variant { ch };
    EXPECT_EQ(type_id<wchar_t>::value, var.id());
    EXPECT_EQ(ch, var.get<wchar_t>());
}

TEST(ut_variant, wcstr) {
    auto str = +L"你好,world";
    auto val = variant { str };
    EXPECT_EQ(type_id<const wchar_t*>::value, val.id());
    EXPECT_EQ(str, val.get<const wchar_t*>());
}

TEST(ut_variant, equility) {
    auto var1 = variant { 1 };
    auto var2 = variant { 1 };
    EXPECT_EQ(var1, var2);

    // different value
    auto var3 = variant { 2 };
    EXPECT_NE(var1, var3);

    // different type
    auto var4 = variant { +"abc" };
    EXPECT_NE(var1, var4);
}

TEST(ut_variant, to_string) {
    using miu::com::to_string;

    EXPECT_EQ("[bool:true]", to_string(variant(true)));
    EXPECT_EQ("[char:a]", to_string(variant('a')));
    EXPECT_EQ("[int8_t:1]", to_string(variant((int8_t)1)));
    EXPECT_EQ("[int16_t:1]", to_string(variant((int16_t)1)));
    EXPECT_EQ("[int32_t:1]", to_string(variant((int32_t)1)));
    EXPECT_EQ("[int64_t:1]", to_string(variant((int64_t)1)));
    EXPECT_EQ("[uint8_t:1]", to_string(variant((uint8_t)1)));
    EXPECT_EQ("[uint16_t:1]", to_string(variant((uint16_t)1)));
    EXPECT_EQ("[uint32_t:1]", to_string(variant((uint32_t)1)));
    EXPECT_EQ("[uint64_t:1]", to_string(variant((uint64_t)1)));
    EXPECT_EQ("[float:1.200000]", to_string(variant((float)1.2)));
    EXPECT_EQ("[double:1.200000]", to_string(variant(1.2)));
    EXPECT_EQ("[const char*:a b c]", to_string(variant(+"a b c")));
    EXPECT_EQ("[std::string:a b c]", to_string(variant(std::string("a b c"))));

    EXPECT_EQ("[microseconds:100us]", to_string(variant(miu::com::microseconds(100))));
    EXPECT_EQ("[days:1d]", to_string(variant(miu::com::days(1))));
    EXPECT_EQ("[date:20210129]", to_string(variant(miu::com::date(2021, 1, 29))));
    EXPECT_EQ("[daytime:12:10:30.000001]", to_string(variant(miu::com::daytime(12, 10, 30, 1))));
    EXPECT_EQ("[datetime:20210129 12:10:30.000001]",
              to_string(variant(miu::com::datetime(2021, 1, 29, 12, 10, 30, 1))));
}
