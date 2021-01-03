#include <gtest/gtest.h>

#include "com/daytime.hpp"
#include "com/time_offset.hpp"

using namespace std::chrono_literals;
using miu::com::daytime;
using miu::com::microseconds;
using miu::com::time_offset;

TEST(ut_daytime, defalut_zero) {
    daytime time;
    EXPECT_EQ(microseconds(0), time.time_since_epoch());
}

TEST(ut_daytime, create_from_duration) {
    auto time = daytime { microseconds(1) };
    EXPECT_EQ(microseconds(1), time.time_since_epoch());

    auto time2 = daytime { std::chrono::seconds(1) };
    EXPECT_EQ(microseconds(1000000), time2.time_since_epoch());
}

TEST(ut_daytime, create_from_components) {
    auto time = daytime { 12, 10, 11, 123 };
    EXPECT_EQ((12 * 3600 + 10 * 60 + 11) * 1000000LL + 123, time.time_since_epoch().count());
}

TEST(ut_daytime, create_from_string) {
    auto time = daytime { "12:10:11.000123" };
    EXPECT_EQ((12 * 3600 + 10 * 60 + 11) * 1000000LL + 123, time.time_since_epoch().count());
}

TEST(ut_daytime, to_string) {
    auto time = daytime { 6, 12, 33, 99999 };
    EXPECT_EQ("06:12:33.099999", std::to_string(time));

    EXPECT_EQ("00:00:00.000000", std::to_string(daytime()));
}

TEST(ut_daytime, now) {
    auto t1 = daytime::now().time_since_epoch();
    auto t2 = std::chrono::system_clock::now().time_since_epoch();
    EXPECT_GT(1ms, t2 % 24h - t1);
}

TEST(ut_daytime, time_offset) {
    time_offset::set(-8h);

    microseconds t1 = daytime::now().time_since_epoch();
    microseconds t2 = std::chrono::system_clock::now().time_since_epoch() - 8h;
    EXPECT_EQ(t1.count() / 1000, (t2 % 24h).count() / 1000);

    time_offset::set(0);
}
