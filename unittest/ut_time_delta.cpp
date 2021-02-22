#include <gtest/gtest.h>

#include "time/delta.hpp"

using namespace std::chrono_literals;
using miu::time::delta;

TEST(ut_time_delta, default) {
    delta val;
    EXPECT_EQ(0, val.count());
}

TEST(ut_time_delta, ctor) {
    auto val = delta { 1 };
    EXPECT_EQ(1ms, val);
}

TEST(ut_time_delta, cast) {
    std::chrono::seconds sec { 1 };
    auto val = delta { sec };
    EXPECT_EQ(1000, val.count());
}

TEST(ut_time_delta, to_string) {
    EXPECT_EQ("999999ms", miu::com::to_string(delta { 999999 }));
}

TEST(ut_time_delta, extreme) {
    EXPECT_EQ(std::numeric_limits<int32_t>::lowest(), delta::min().count());
    EXPECT_EQ(std::numeric_limits<int32_t>::max(), delta::max().count());
    EXPECT_EQ(0, delta::zero().count());
}

TEST(ut_time_delta, variant) {
    using miu::com::type_id;
    using miu::com::variant;

    delta val { 1 };
    variant var { val };
    EXPECT_EQ(type_id<delta>::value, var.id());
    EXPECT_EQ(val, var.get<delta>().value());
    EXPECT_EQ("1ms", var.get<std::string>().value());

    EXPECT_EQ(delta(5), variant(5).get<delta>().value());

    EXPECT_FALSE(variant { true }.get<delta>());
}
