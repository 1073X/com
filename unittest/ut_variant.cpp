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
    auto var = variant { ch };
    EXPECT_EQ(type_id<wchar_t>::value, var.id());
    EXPECT_EQ(ch, var.get<wchar_t>());
}

TEST(ut_variant, wcstr) {
    auto str = +L"你好,world";
    auto val = variant { str };
    EXPECT_EQ(type_id<const wchar_t*>::value, val.id());
    EXPECT_EQ(str, val.get<const wchar_t*>());
}
