#include <gtest/gtest.h>

#include "com/microseconds.hpp"

using miu::com::microseconds;

TEST(ut_microseconds, default_zero) {
    microseconds val;
    EXPECT_EQ(0, val.count());
}

TEST(ut_microseconds, create_from_rep) {
    auto val = microseconds { 1 };
    EXPECT_EQ(1, val.count());
}

TEST(ut_microseconds, create_from_other_duration) {
    std::chrono::seconds sec { 1 };
    auto val = microseconds { sec };
    EXPECT_EQ(1000000, val.count());
}

TEST(ut_microseconds, create_from_string) {
    auto val = microseconds { "25:02:03.999999" };
    EXPECT_EQ((25 * 3600 + 2 * 60 + 3) * 1000000LL + 999999, val.count());

    // illegal strings
    EXPECT_ANY_THROW(microseconds("1:02:03.999999"));
    EXPECT_ANY_THROW(microseconds("01:02:03.99999"));
    // illegal value
    EXPECT_ANY_THROW(microseconds("01:60:11.000123"));
    EXPECT_ANY_THROW(microseconds("12:10:60.000123"));
}

TEST(ut_microseconds, to_string) {
    auto str = "01:02:03.999999";
    EXPECT_EQ(str, miu::com::to_string(microseconds { str }));
}

TEST(ut_microseconds, extreme) {
    EXPECT_EQ(std::numeric_limits<int64_t>::lowest(), microseconds::min().count());
    EXPECT_EQ(std::numeric_limits<int64_t>::max(), microseconds::max().count());
    EXPECT_EQ(0, microseconds::zero().count());
}
