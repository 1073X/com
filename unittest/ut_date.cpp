#include <gtest/gtest.h>

#include "com/date.hpp"

using miu::com::date;

TEST(ut_date, default) {
    date val;
    EXPECT_EQ(std::make_tuple(1970, 1, 1), val.civil_from_days());
}

TEST(ut_date, create_from_components) {
    auto val = date { 2021, 1, 3 };
    EXPECT_EQ(std::make_tuple(2021, 1, 3), val.civil_from_days());
}

TEST(ut_date, create_from_string) {
    auto val = date { "20210103" };
    EXPECT_EQ(std::make_tuple(2021, 1, 3), val.civil_from_days());
}

TEST(ut_date, to_string) {
    auto val = date { 2021, 1, 3 };
    EXPECT_EQ("20210103", std::to_string(val));
}

TEST(ut_date, today) {
    auto val = date::today();

    auto now = std::chrono::system_clock::now();
    auto today = std::chrono::duration_cast<miu::com::days_base>(now.time_since_epoch());

    EXPECT_EQ(today, val.time_since_epoch());
}

TEST(ut_date, extreme) {
    EXPECT_EQ(date(1970, 1, 1), date::min());
    EXPECT_EQ(std::numeric_limits<int32_t>::max(), date::max().time_since_epoch().count());
    EXPECT_EQ(date(1970, 1, 1), date::zero());
}
