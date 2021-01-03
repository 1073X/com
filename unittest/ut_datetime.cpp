#include <gtest/gtest.h>

#include "com/datetime.hpp"

using miu::com::datetime;
using miu::com::microseconds;

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
    EXPECT_EQ("20210103 19:15:30.000123", std::to_string(val));
}

TEST(ut_datetime, create_from_string) {
    auto val = datetime { "20210103 19:15:30.000123" };
    EXPECT_EQ(miu::com::date(2021, 1, 3), val.date());
    EXPECT_EQ(miu::com::daytime(19, 15, 30, 123), val.time());
}
