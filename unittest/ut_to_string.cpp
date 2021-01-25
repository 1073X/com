#include <gtest/gtest.h>

#include "com/to_string.hpp"

TEST(ut_to_string, string_view) {
    char buf[8] = "abc";
    EXPECT_EQ("abc", miu::com::to_string(std::string_view(buf, sizeof(buf))));
}
