#include <gtest/gtest.h>

#include "com/fatal_error.hpp"

TEST(ut_fatal_error, empty) {
    miu::com::fatal_error err;
    EXPECT_STREQ("FATAL", err.what());
}

TEST(ut_fatal_error, what) {
    miu::com::fatal_error err { "message" };
    EXPECT_STREQ("message", err.what());
}

TEST(ut_fatal_error, shortcut) {
    EXPECT_THROW(FATAL_ERROR("message"), miu::com::fatal_error);
    EXPECT_THROW(FATAL_ERROR("message"), std::runtime_error);
}

TEST(ut_fatal_error, concat) {
    try {
        FATAL_ERROR(1, "xyz");
    } catch (miu::com::fatal_error const& err) {
        EXPECT_STREQ("1 xyz", err.what());
    }
}

