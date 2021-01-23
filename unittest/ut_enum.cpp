#include <gtest/gtest.h>

#include "com/enum.hpp"
#include "com/to_string.hpp"

using miu::com::enum_to_str;
using miu::com::val_to_enum;

struct ut_enum : public testing::Test {
    enum struct enumeration { VAL1, VAL2, MAX };
};

TEST_F(ut_enum, to_string) {
    EXPECT_STREQ("VAL1", enum_to_str(enumeration::VAL1));
    EXPECT_STREQ("VAL2", enum_to_str(enumeration::VAL2));
    EXPECT_STREQ("MAX", enum_to_str(enumeration::MAX));

    EXPECT_STREQ("MAX", miu::com::enum_to_str(enumeration(99)));
}

TEST_F(ut_enum, str_val_to_enum) {
    EXPECT_EQ(enumeration::VAL1, val_to_enum<enumeration>("VAL1"));
    EXPECT_EQ(enumeration::VAL2, val_to_enum<enumeration>("VAL2"));
    EXPECT_EQ(enumeration::MAX, val_to_enum<enumeration>("MAX"));

    EXPECT_EQ(enumeration::MAX, val_to_enum<enumeration>("not_exists"));
}

TEST_F(ut_enum, num_val_to_enum) {
    EXPECT_EQ(enumeration::VAL1, val_to_enum<enumeration>(0));
    EXPECT_EQ(enumeration::VAL2, val_to_enum<enumeration>(1U));
    EXPECT_EQ(enumeration::MAX, val_to_enum<enumeration>(2U));

    EXPECT_EQ(enumeration::MAX, val_to_enum<enumeration>(99U));
}
