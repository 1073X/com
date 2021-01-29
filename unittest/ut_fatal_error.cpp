#include <gtest/gtest.h>

#include "com/fatal_error.hpp"

TEST(ut_fatal_error, throw_runtime_error) {
    EXPECT_THROW(FATAL_ERROR("message"), std::runtime_error);
}

TEST(ut_fatal_error, throw_logic_error) {
    EXPECT_THROW(FATAL_ERROR<std::logic_error>("message"), std::logic_error);
}
