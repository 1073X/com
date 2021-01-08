#include <gtest/gtest.h>

#include "com/enum.hpp"

struct ut_enum : public testing::Test {
    enum struct enumeration { VAL1, VAL2, MAX };
};

TEST_F(ut_enum, to_string) {
    EXPECT_STREQ("VAL1", std::to_string(enumeration::VAL1));
    EXPECT_STREQ("VAL2", std::to_string(enumeration::VAL2));
    EXPECT_STREQ("MAX", std::to_string(enumeration::MAX));

    EXPECT_STREQ("MAX", std::to_string(enumeration(99)));
}

TEST_F(ut_enum, to_enum) {
    EXPECT_EQ(enumeration::VAL1, miu::com::to_enum<enumeration>("VAL1"));
    EXPECT_EQ(enumeration::VAL2, miu::com::to_enum<enumeration>("VAL2"));
    EXPECT_EQ(enumeration::MAX, miu::com::to_enum<enumeration>("MAX"));

    EXPECT_EQ(enumeration::MAX, miu::com::to_enum<enumeration>("not_exists"));
}
