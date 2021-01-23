#include <gtest/gtest.h>

#include "com/datetime.hpp"
#include "com/time_offset.hpp"

using namespace std::chrono_literals;
using miu::com::datetime;
using miu::com::microseconds;
using miu::com::time_offset;

TEST(ut_datetime, default_ctor) {
    datetime val;
    EXPECT_EQ(microseconds(0), val.time_since_epoch());

    EXPECT_EQ(miu::com::date(1970, 1, 1), val.date());
    EXPECT_EQ(miu::com::daytime(0, 0, 0, 0), val.time());
}

TEST(ut_datetime, create_from_components) {
    auto val = datetime { 2021, 1, 3, 19, 15, 30, 123 };
    EXPECT_EQ(miu::com::date(2021, 1, 3), val.date());
    EXPECT_EQ(miu::com::daytime(19, 15, 30, 123), val.time());
}

TEST(ut_datetime, to_string) {
    auto val = datetime { 2021, 1, 3, 19, 15, 30, 123 };
    EXPECT_EQ("20210103 19:15:30.000123", miu::com::to_string(val));
}

TEST(ut_datetime, create_from_string) {
    auto val = datetime { "20210103 19:15:30.000123" };
    EXPECT_EQ(miu::com::date(2021, 1, 3), val.date());
    EXPECT_EQ(miu::com::daytime(19, 15, 30, 123), val.time());
}

TEST(ut_datetime, now) {
    auto t1 = std::chrono::system_clock::now().time_since_epoch();
    auto t2 = datetime::now().time_since_epoch();
    EXPECT_GT(1ms, t2 - t1);
}

TEST(ut_datetime, time_offset) {
    time_offset::set(8h);

    microseconds t1 = std::chrono::system_clock::now().time_since_epoch();
    microseconds t2 = datetime::now().time_since_epoch();
    EXPECT_LE(8h, t2 - t1);

    time_offset::set(0);
}

TEST(ut_datetime, extreme) {
    EXPECT_EQ(datetime(1970, 1, 1, 0, 0, 0, 0), datetime::zero());
    EXPECT_EQ(datetime(1970, 1, 1, 0, 0, 0, 0), datetime::min());
    EXPECT_EQ(std::numeric_limits<int64_t>::max(), datetime::max().time_since_epoch().count());
}
