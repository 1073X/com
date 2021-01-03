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

TEST(ut_microseconds, create_from_components) {
    auto val = microseconds::create(1, 2, 3, 123);
    EXPECT_EQ(3600 * 1000000LL + 2 * 60 * 1000000LL + 3 * 1000000LL + 123, val.count());
}

TEST(ut_microseconds, create_from_string) {
    auto val = microseconds::create("01:02:03.999999");
    EXPECT_EQ(3600 * 1000000LL + 2 * 60 * 1000000LL + 3 * 1000000LL + 999999, val.count());
}
