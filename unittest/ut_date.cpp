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
    std::cout << std::to_string(val) << std::endl;
}
