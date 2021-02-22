#include <gtest/gtest.h>

#include <ctime>    // time, gmtime, localtime

#include "time/offset.hpp"

using namespace std::chrono_literals;

TEST(ut_time_offset, init) {
    using miu::time::offset;

    auto utc = std::time(nullptr);
    auto loc = std::localtime(&utc);
    auto off = std::chrono::seconds(loc->tm_gmtoff);
    EXPECT_EQ(off, offset::get());

    offset::set(4h);
    EXPECT_EQ(4h, offset::get());
    offset::set(off);    // restore
}
