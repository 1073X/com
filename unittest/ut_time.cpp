#include <gtest/gtest.h>

#include "time/offset.hpp"
#include "time/time.hpp"

using namespace std::chrono_literals;
using miu::time::offset;
using namespace std::chrono;

TEST(ut_time, now) {
    auto t1 = duration_cast<milliseconds>(miu::time::now().time_since_epoch());
    auto t2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch() + offset::get());
    EXPECT_GE(2ms, t2 - t1);
}

TEST(ut_time, today) {
    auto t1 = miu::time::today();
    auto t2 = system_clock::now() + offset::get();
    EXPECT_EQ(t2.time_since_epoch() / 24h, t1.time_since_epoch().count());
}

TEST(ut_time, yesterday) {
    auto t1 = miu::time::yesterday();
    auto t2 = system_clock::now() + offset::get() - 24h;
    EXPECT_EQ(t2.time_since_epoch() / 24h, t1.time_since_epoch().count());
}

TEST(ut_time, tomorrow) {
    auto t1 = miu::time::tomorrow();
    auto t2 = system_clock::now() + offset::get() + 24h;
    EXPECT_EQ(t2.time_since_epoch() / 24h, t1.time_since_epoch().count());
}

TEST(ut_time, time_of_day) {
    auto t1 = miu::time::time_of_day().time_since_epoch();
    auto t2 = (system_clock::now() + offset::get()).time_since_epoch() % 24h;
    EXPECT_GE(2ms, duration_cast<milliseconds>(t2) - t1);
}
