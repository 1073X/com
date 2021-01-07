#include <gtest/gtest.h>

#include "com/variant.hpp"

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
}

TEST_F(ut_var_chrono, date) {
    date val { 2021, 1, 7 };
    variant var { val };
    EXPECT_EQ(type_id<date>::value, var.id());
    EXPECT_EQ(val, var.get<date>().value());
}

TEST_F(ut_var_chrono, daytime) {
    daytime val { 13, 49, 30, 999 };
    variant var { val };
    EXPECT_EQ(type_id<daytime>::value, var.id());
    EXPECT_EQ(val, var.get<daytime>().value());
}

TEST_F(ut_var_chrono, datetime) {
    datetime val { 2021, 1, 7, 13, 49, 30, 999 };
    variant var { val };
    EXPECT_EQ(type_id<datetime>::value, var.id());
    EXPECT_EQ(val, var.get<datetime>().value());
}
