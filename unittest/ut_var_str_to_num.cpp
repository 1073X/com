#include <gtest/gtest.h>

#include "com/variant.hpp"

using miu::com::variant;

TEST(ut_var_str, to_integer) {
    EXPECT_EQ(123, variant { +"123" }.get<int32_t>().value());
    EXPECT_EQ(123, variant { +"123" }.get<uint32_t>().value());
    EXPECT_EQ(123, variant { std::string("123") }.get<int32_t>().value());
    EXPECT_EQ(-123, variant { +"-123" }.get<int32_t>().value());
}

TEST(ut_var_str, to_decimal) {
    EXPECT_DOUBLE_EQ(1.2, variant { std::string("1.2") }.get<double>().value());
    EXPECT_DOUBLE_EQ(999.888999, variant { +"999.888999" }.get<double>().value());
    EXPECT_DOUBLE_EQ(100.0, variant { +"100" }.get<float>().value());
    EXPECT_DOUBLE_EQ(.6, variant { +".6" }.get<double>().value());
    EXPECT_DOUBLE_EQ(-2.3, variant { +"-2.3" }.get<double>().value());

    EXPECT_DOUBLE_EQ(0, variant { +"a" }.get<double>().value());
    EXPECT_DOUBLE_EQ(1, variant { +"1.a" }.get<double>().value());
}
