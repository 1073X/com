#include <gtest/gtest.h>

#include "com/time_offset.hpp"

using namespace std::chrono_literals;
using miu::com::microseconds;
using miu::com::time_offset;

TEST(ut_time_offset, set_and_get) {
    EXPECT_EQ(microseconds(0), time_offset::get());

    time_offset::set(1h);
    EXPECT_EQ(1h, time_offset::get());
}
