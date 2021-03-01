#include <gtest/gtest.h>

#include "com/reg_var_str.hpp"
#include "com/variant.hpp"
#include "time/stamp.hpp"

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
    EXPECT_EQ("[bool:false]", to_string(variant(false)));

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
    EXPECT_EQ("[double:1.2]", to_string(variant(1.2)));
    EXPECT_EQ("[const char*:a b c]", to_string(variant(+"a b c")));
    EXPECT_EQ("[std::string:a b c]", to_string(variant(std::string("a b c"))));

    EXPECT_EQ("[time::delta:100ms]", to_string(variant(miu::time::delta(100))));
    EXPECT_EQ("[time::days:1d]", to_string(variant(miu::time::days(1))));
    EXPECT_EQ("[time::date:20210129]", to_string(variant(miu::time::date(2021, 1, 29))));
    EXPECT_EQ(
        "[time::daytime:12:10:30.001]", to_string(variant(miu::time::daytime(12, 10, 30, 1))));
    EXPECT_EQ("[time::stamp:20210129 12:10:30.001]",
              to_string(variant(miu::time::stamp(2021, 1, 29, 12, 10, 30, 1))));

    EXPECT_EQ("[UNK_VAR:15]", to_string(variant(L'害')));

    EXPECT_EQ("[void:N/A]", to_string(variant()));
}

struct custom {};
DEF_VARIANT(custom, 132);

DEF_VAR_SET(custom) {
    new (_value) custom { v };
}

DEF_VAR_GET(custom) {
    return *(custom const*)_value;
}

DEF_TO_STRING(custom) {
    return "custom";
}

TEST(ut_variant, custom_type) {
    miu::com::reg_var_str<custom>();

    EXPECT_EQ(132, type_id<custom>::value);
    EXPECT_EQ("132:custom", type_id<custom>::name());

    auto var = variant { custom() };
    EXPECT_EQ(132, var.id());
    EXPECT_EQ("custom", var.get<std::string>());
}
