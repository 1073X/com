#include <gtest/gtest.h>

#include "time/date.hpp"

using miu::time::date;

TEST(ut_time_date, from_rep) {
    EXPECT_EQ(std::make_tuple(1970, 1, 1), date {}.ytd());
    EXPECT_EQ(std::make_tuple(1970, 1, 6), date { 5 }.ytd());
}

TEST(ut_time_date, from_ytd) {
    auto val = date { 2021, 2, 22 };
    EXPECT_EQ(std::make_tuple(2021, 2, 22), val.ytd());

    // illegal value
    EXPECT_ANY_THROW(date(1969, 1, 3));
    EXPECT_ANY_THROW(date(10000, 1, 3));
    EXPECT_ANY_THROW(date(2021, 0, 3));
    EXPECT_ANY_THROW(date(2021, 13, 3));
    EXPECT_ANY_THROW(date(2021, 1, 0));
    EXPECT_ANY_THROW(date(2021, 1, 32));
}

TEST(ut_time_date, from_str) {
    auto val = date { "20210222" };
    EXPECT_EQ(std::make_tuple(2021, 2, 22), val.ytd());

    // illegal string
    EXPECT_ANY_THROW(date("2020123"));
    EXPECT_ANY_THROW(date("202a1231"));
}

TEST(ut_time_date, to_string) {
    auto val = date { 2021, 2, 22 };
    EXPECT_EQ("20210222", miu::com::to_string(val));
}

TEST(ut_time_date, variant) {
    using miu::com::type_id;
    using miu::com::variant;

    date val { 2021, 2, 22 };
    variant var { val };
    EXPECT_EQ(type_id<date>::value, var.id());
    EXPECT_EQ(val, var.get<date>().value());
    EXPECT_EQ("20210222", var.get<std::string>().value());

    auto str = +"20210222";
    EXPECT_EQ(date(2021, 2, 22), variant { str }.get<date>().value());
    EXPECT_EQ(date(2021, 2, 22), variant { std::string(str) }.get<date>().value());

    EXPECT_FALSE(variant { 1.2 }.get<date>());
}
