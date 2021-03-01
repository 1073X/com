#include <gtest/gtest.h>

#include <cmath>    // std::floor

#include "com/variant.hpp"

using miu::com::type_id;
using miu::com::variant;

template<typename>
struct ut_var_dec_to_int : public testing::Test {};

using pairs = testing::Types<std::pair<double, int8_t>,
                             std::pair<double, int16_t>,
                             std::pair<double, int32_t>,

                             std::pair<double, uint8_t>,
                             std::pair<double, uint16_t>,
                             std::pair<double, uint32_t>,

                             std::pair<float, int8_t>,
                             std::pair<float, int16_t>,

                             std::pair<float, uint8_t>,
                             std::pair<float, uint16_t>>;

TYPED_TEST_SUITE(ut_var_dec_to_int, pairs);

TYPED_TEST(ut_var_dec_to_int, can_cover_target_min) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    target_type val = std::numeric_limits<target_type>::lowest();
    variant var { (source_type)val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_DOUBLE_EQ(val, var.get<target_type>().value());
}

TYPED_TEST(ut_var_dec_to_int, can_cover_target_max) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    target_type val = std::numeric_limits<target_type>::max();
    variant var { (source_type)val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_DOUBLE_EQ(val, var.get<target_type>().value());
}

TYPED_TEST(ut_var_dec_to_int, overflow) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    auto val = static_cast<source_type>(std::numeric_limits<target_type>::max()) + 1;
    variant var { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_FALSE(var.get<target_type>().has_value());
}

TYPED_TEST(ut_var_dec_to_int, underflow) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    auto val = static_cast<source_type>(std::numeric_limits<target_type>::lowest()) - 1;
    variant var { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_FALSE(var.get<target_type>().has_value());
}

TYPED_TEST(ut_var_dec_to_int, precision) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = 1.2;
    variant var { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_FALSE(var.get<target_type>().has_value());
}
