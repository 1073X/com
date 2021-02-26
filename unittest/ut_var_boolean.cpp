#include <gtest/gtest.h>

#include "com/variant.hpp"

using miu::com::type_id;
using miu::com::variant;

template<typename>
struct ut_var_boolean : public testing::Test {};

using pairs = testing::Types<std::pair<bool, bool>,
                             std::pair<int8_t, bool>,
                             std::pair<int16_t, bool>,
                             std::pair<int32_t, bool>,
                             std::pair<int64_t, bool>,
                             std::pair<uint8_t, bool>,
                             std::pair<uint16_t, bool>,
                             std::pair<uint32_t, bool>,
                             std::pair<uint64_t, bool>>;

TYPED_TEST_SUITE(ut_var_boolean, pairs);

TYPED_TEST(ut_var_boolean, true) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = static_cast<source_type>(true);
    variant var { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_TRUE(var.get<target_type>().value());
}

TYPED_TEST(ut_var_boolean, false) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = static_cast<source_type>(false);
    variant var { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_FALSE(var.get<target_type>().value());
}

TEST(ut_var_boolean, from_string) {
    EXPECT_TRUE(variant { std::string("true") }.get<bool>().value());
    EXPECT_FALSE(variant { +"False" }.get<bool>().value());
    EXPECT_ANY_THROW(variant { std::string("xxx") }.get<bool>().value());
}
