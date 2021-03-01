#include <gtest/gtest.h>

#include "time/offset.hpp"
#include "time/stamp.hpp"

using namespace std::chrono_literals;
using miu::time::stamp;

TEST(ut_time_stamp, default) {
    stamp val;
    EXPECT_EQ(0, val.time_since_epoch().count());

    EXPECT_EQ(miu::time::date(1970, 1, 1), val.date());
    EXPECT_EQ(miu::time::daytime(0, 0, 0, 0), val.time());
}

TEST(ut_time_stamp, from_rep) {
    auto val = stamp { 2021, 2, 22, 19, 15, 30, 123 };

    std::cout << miu::com::to_string(val.date()) << std::endl;
    std::cout << miu::com::to_string(val.time()) << std::endl;

    EXPECT_EQ(miu::time::date(2021, 2, 22), val.date());
    EXPECT_EQ(miu::time::daytime(19, 15, 30, 123), val.time());
}

TEST(ut_time_stamp, to_string) {
    auto val = stamp { 2021, 2, 22, 19, 15, 30, 123 };
    EXPECT_EQ("20210222 19:15:30.123", miu::com::to_string(val));
}

TEST(ut_time_stamp, from_str) {
    auto val = stamp { "20210222 19:15:30.123" };
    EXPECT_EQ(miu::time::date(2021, 2, 22), val.date());
    EXPECT_EQ(miu::time::daytime(19, 15, 30, 123), val.time());
}

TEST(ut_time_stamp, variant) {
    using miu::com::type_id;
    using miu::com::variant;

    stamp val { 2021, 2, 22, 13, 49, 30, 999 };
    variant var { val };
    EXPECT_EQ(type_id<stamp>::value, var.id());
    EXPECT_EQ(val, var.get<stamp>().value());
    EXPECT_EQ("20210222 13:49:30.999", var.get<std::string>().value());

    auto str = +"20210222 23:01:01.001";
    auto exp = stamp { str };
    EXPECT_EQ(exp, variant { str }.get<stamp>());
}
