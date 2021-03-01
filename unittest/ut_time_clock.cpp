#include <gtest/gtest.h>
#include <time.h>

#include <ctime>

#include "time/clock.hpp"
#include "time/offset.hpp"

using namespace std::chrono_literals;
using namespace std::chrono;

TEST(ut_time_clock, res) {
    timespec tp;

    ::clock_getres(CLOCK_REALTIME, &tp);
    std::cout << "CLOCK_REALTIME: " << tp.tv_sec << ' ' << tp.tv_nsec << std::endl;

    ::clock_getres(CLOCK_REALTIME_ALARM, &tp);
    std::cout << "CLOCK_REALTIME_ALARM: " << tp.tv_sec << ' ' << tp.tv_nsec << std::endl;

    ::clock_getres(CLOCK_REALTIME_COARSE, &tp);
    std::cout << "CLOCK_REALTIME_COARSE: " << tp.tv_sec << ' ' << tp.tv_nsec << std::endl;
}

TEST(ut_time_clock, now) {
    auto t1 = std::chrono::seconds { std::time(nullptr) };
    auto t2 = miu::time::clock::now().time_since_epoch();
    EXPECT_LE(miu::time::offset::get(), t2 - t1);
}
