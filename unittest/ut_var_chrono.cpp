#include <gtest/gtest.h>

#include "com/variant.hpp"

using namespace std::chrono_literals;
using miu::com::date;
using miu::com::datetime;
using miu::com::days;
using miu::com::daytime;
using miu::com::microseconds;
using miu::com::type_id;
using miu::com::variant;

struct ut_var_chrono : public testing::Test {};

TEST_F(ut_var_chrono, days) {
    days val { 1 };
    variant var { val };
    EXPECT_EQ(type_id<days>::value, var.id());
    EXPECT_EQ(val, var.get<days>().value());
}

TEST_F(ut_var_chrono, microseconds) {
    microseconds val { 1 };
    variant var { val };
    EXPECT_EQ(type_id<microseconds>::value, var.id());
    EXPECT_EQ(val, var.get<microseconds>().value());

    auto str = +"24:01:01.000001";
    auto exp = microseconds(24h + 1min + 1s + 1us);
    EXPECT_EQ(exp, variant { str }.get<microseconds>());
    EXPECT_EQ(exp, variant { std::string(str) }.get<microseconds>());
    EXPECT_EQ(exp, variant { exp.count() }.get<microseconds>());

    EXPECT_FALSE(variant { true }.get<microseconds>());
}

TEST_F(ut_var_chrono, date) {
    date val { 2021, 1, 7 };
    variant var { val };
    EXPECT_EQ(type_id<date>::value, var.id());
    EXPECT_EQ(val, var.get<date>().value());

    auto str = +"20210113";
    EXPECT_EQ(date(2021, 1, 13), variant { str }.get<date>().value());
    EXPECT_EQ(date(2021, 1, 13), variant { std::string(str) }.get<date>().value());

    EXPECT_FALSE(variant { 1.2 }.get<date>());
}

TEST_F(ut_var_chrono, daytime) {
    daytime val { 13, 49, 30, 999 };
    variant var { val };
    EXPECT_EQ(type_id<daytime>::value, var.id());
    EXPECT_EQ(val, var.get<daytime>().value());

    auto str = +"23:01:01.000001";
    auto exp = daytime { str };
    EXPECT_EQ(exp, variant { str }.get<daytime>());
    EXPECT_EQ(exp, variant { std::string(str) }.get<daytime>());

    EXPECT_FALSE(variant { 1.2 }.get<daytime>());
}

TEST_F(ut_var_chrono, datetime) {
    datetime val { 2021, 1, 7, 13, 49, 30, 999 };
    variant var { val };
    EXPECT_EQ(type_id<datetime>::value, var.id());
    EXPECT_EQ(val, var.get<datetime>().value());
}
