#include <gtest/gtest.h>

#include "time/daytime.hpp"

using namespace std::chrono_literals;
using miu::time::daytime;
using std::chrono::milliseconds;

TEST(ut_time_daytime, defalut) {
    EXPECT_EQ(0, daytime {}.time_since_epoch().count());
    EXPECT_EQ(100ms, daytime { 100 }.time_since_epoch());
}

TEST(ut_time_daytime, from_duration) {
    auto time = daytime { 1000ms };
    EXPECT_EQ(1s, time.time_since_epoch());

    auto time2 = daytime { 1s };
    EXPECT_EQ(1000ms, time2.time_since_epoch());
}

TEST(ut_time_daytime, from_hms) {
    auto time = daytime { 12, 10, 11, 123 };
    EXPECT_EQ((12 * 3600 + 10 * 60 + 11) * 1000 + 123, time.time_since_epoch().count());

    // illegal value
    EXPECT_THROW(daytime(24, 0, 0, 0), std::overflow_error);
    EXPECT_THROW(daytime(-1, 0, 0, 0), std::underflow_error);
    EXPECT_THROW(daytime(1, 60, 0, 0), std::overflow_error);
    EXPECT_THROW(daytime(1, -1, 0, 0), std::underflow_error);
    EXPECT_THROW(daytime(1, 0, 60, 0), std::overflow_error);
    EXPECT_THROW(daytime(1, 0, -1, 0), std::underflow_error);
    EXPECT_THROW(daytime(1, 0, 0, 1000), std::overflow_error);
    EXPECT_THROW(daytime(1, 0, 0, -1), std::underflow_error);
}

TEST(ut_time_daytime, from_str) {
    auto time = daytime { "12:10:11.123" };
    EXPECT_EQ((12 * 3600 + 10 * 60 + 11) * 1000 + 123, time.time_since_epoch().count());

    // illegal hours
    EXPECT_ANY_THROW(daytime("24:00:00.000"));
}

TEST(ut_time_daytime, to_string) {
    auto time = daytime { 6, 12, 33, 99 };
    EXPECT_EQ("06:12:33.099", miu::com::to_string(time));

    EXPECT_EQ("00:00:00.000", miu::com::to_string(daytime()));
}

TEST(ut_time_daytime, variant) {
    using miu::com::type_id;
    using miu::com::variant;

    daytime val { 13, 49, 30, 999 };
    variant var { val };
    EXPECT_EQ(type_id<daytime>::value, var.id());
    EXPECT_EQ(val, var.get<daytime>().value());
    EXPECT_EQ("13:49:30.999", var.get<std::string>().value());

    auto str = +"23:01:01.001";
    auto exp = daytime { str };
    EXPECT_EQ(exp, variant { str }.get<daytime>());
    EXPECT_EQ(exp, variant { std::string(str) }.get<daytime>());

    EXPECT_FALSE(variant { 1.2 }.get<daytime>());
}

