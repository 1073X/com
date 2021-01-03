#include <gtest/gtest.h>

#include "com/days.hpp"

using miu::com::days;

TEST(ut_days, default_zero) {
    days val;
    EXPECT_EQ(0, val.count());
}

TEST(ut_days, create_from_rep) {
    auto val = days { 88 };
    EXPECT_EQ(88, val.count());
}

TEST(ut_days, create_from_other_duration) {
    auto val = days { std::chrono::hours(49) };
    EXPECT_EQ(2, val.count());
}
