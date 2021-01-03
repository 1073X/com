#include <gtest/gtest.h>

#include "com/fatal_error.hpp"

TEST(ut_fatal_error, throw_runtime_error) {
    EXPECT_THROW(FATAL_ERROR("message"), std::runtime_error);
    try {
        FATAL_ERROR(1, "xyz");
    } catch (std::runtime_error const& err) {
        auto msg = err.what() + 31;    // skip the timestamp
        EXPECT_STREQ("1 xyz", msg);
    }
}
