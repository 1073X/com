#include <gtest/gtest.h>

#include "com/strcat.hpp"

TEST(ut_strcat, concat) {
    char array[] = "array";
    std::string_view view { "view" };
    miu::com::strcat cat { array, 'b', 1, view };
    EXPECT_EQ("array.b.1.view", cat.str());
}

TEST(ut_strcat, delimiter) {
    miu::com::strcat cat { 1, 2, miu::com::strcat::delimiter { "---" } };
    EXPECT_EQ("1---2", cat.str());
}
