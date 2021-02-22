#include <gtest/gtest.h>

#include "time/days.hpp"

using namespace std::chrono_literals;
using miu::time::days;

TEST(ut_time_days, init) {
    days d { 2 };
    EXPECT_EQ(48h, d);
}

TEST(ut_time_days, cast) {
    days d { std::chrono::hours(36) };
    EXPECT_EQ(1, d.count());
}

TEST(ut_time_days, to_string) {
    days d { 30 };
    EXPECT_EQ("30d", miu::com::to_string(d));
}

TEST(ut_time_days, extreme) {
    EXPECT_EQ(std::numeric_limits<int32_t>::lowest(), days::min().count());
    EXPECT_EQ(std::numeric_limits<int32_t>::max(), days::max().count());
    EXPECT_EQ(0, days::zero().count());
}

TEST(ut_time_days, variant) {
    using miu::com::type_id;
    using miu::com::variant;

    auto var = variant { days(2) };
    EXPECT_EQ(type_id<days>::value, var.id());
    EXPECT_EQ(days(2), var.get<days>().value());
    EXPECT_EQ("2d", var.get<std::string>().value());
    EXPECT_EQ(2, var.get<int32_t>().value());

    EXPECT_EQ(days(5), variant(5).get<days>().value());
}
