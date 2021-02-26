#include <gtest/gtest.h>

#include "time/time.hpp"

using namespace std::chrono_literals;

TEST(ut_time, now) {
    auto t1 = miu::time::now();
    auto t2 = std::chrono::system_clock::now();
    EXPECT_GE(1ms, t2.time_since_epoch() - t1.time_since_epoch());
}

TEST(ut_time, today) {
    auto t1 = miu::time::today();
    auto t2 = std::chrono::system_clock::now();
    EXPECT_EQ(t2.time_since_epoch() / 24h, t1.time_since_epoch().count());
}

TEST(ut_time, yesterday) {
    auto t1 = miu::time::yesterday();
    auto t2 = std::chrono::system_clock::now() - 24h;
    EXPECT_EQ(t2.time_since_epoch() / 24h, t1.time_since_epoch().count());
}

TEST(ut_time, tomorrow) {
    auto t1 = miu::time::tomorrow();
    auto t2 = std::chrono::system_clock::now() + 24h;
    EXPECT_EQ(t2.time_since_epoch() / 24h, t1.time_since_epoch().count());
}

TEST(ut_time, now_of_day) {
    auto t1 = miu::time::now_of_day();
    auto t2 = std::chrono::system_clock::now().time_since_epoch() % 24h;
    EXPECT_GE(1ms, t2 - t1.time_since_epoch());
}
