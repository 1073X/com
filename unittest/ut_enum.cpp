#include <gtest/gtest.h>

#include "com/enum.hpp"

using miu::com::to_enum;

struct ut_enum : public testing::Test {
    enum struct enumeration { VAL1, VAL2, MAX };
};

TEST_F(ut_enum, to_string) {
    EXPECT_STREQ("VAL1", miu::com::to_string(enumeration::VAL1));
    EXPECT_STREQ("VAL2", miu::com::to_string(enumeration::VAL2));
    EXPECT_STREQ("MAX", miu::com::to_string(enumeration::MAX));

    EXPECT_STREQ("MAX", miu::com::to_string(enumeration(99)));
}

TEST_F(ut_enum, str_to_enum) {
    EXPECT_EQ(enumeration::VAL1, to_enum<enumeration>("VAL1"));
    EXPECT_EQ(enumeration::VAL2, to_enum<enumeration>("VAL2"));
    EXPECT_EQ(enumeration::MAX, to_enum<enumeration>("MAX"));

    EXPECT_EQ(enumeration::MAX, to_enum<enumeration>("not_exists"));
}

TEST_F(ut_enum, num_to_enum) {
    EXPECT_EQ(enumeration::VAL1, to_enum<enumeration>(0));
    EXPECT_EQ(enumeration::VAL2, to_enum<enumeration>(1U));
    EXPECT_EQ(enumeration::MAX, to_enum<enumeration>(2U));

    EXPECT_EQ(enumeration::MAX, to_enum<enumeration>(99U));
}
