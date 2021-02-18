#include <gtest/gtest.h>

#include "com/variant.hpp"

using miu::com::variant;

TEST(ut_var_num, from_string) {
    EXPECT_EQ(123, variant { +"123" }.get<int32_t>().value());
    EXPECT_EQ(123, variant { +"123" }.get<uint32_t>().value());
    EXPECT_EQ(123, variant { std::string("123") }.get<int32_t>().value());
    EXPECT_EQ(-123, variant { +"-123" }.get<int32_t>().value());

    EXPECT_FALSE(variant { +"a" }.get<int32_t>());
    EXPECT_FALSE(variant { +"" }.get<int32_t>());
    EXPECT_FALSE(variant { +"-123" }.get<uint32_t>());
}
