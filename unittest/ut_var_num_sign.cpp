#include <gtest/gtest.h>

#include "com/variant.hpp"

using miu::com::type_id;
using miu::com::variant;

template<typename>
struct ut_var_try_unsigned : public testing::Test {};

using pairs = testing::Types<std::pair<int8_t, uint64_t>,
                             std::pair<int8_t, uint32_t>,
                             std::pair<int8_t, uint16_t>,
                             std::pair<int8_t, uint8_t>,

                             std::pair<int16_t, uint64_t>,
                             std::pair<int16_t, uint32_t>,
                             std::pair<int16_t, uint16_t>,

                             std::pair<int32_t, uint64_t>,
                             std::pair<int32_t, uint32_t>,

                             std::pair<int64_t, uint64_t>>;

TYPED_TEST_SUITE(ut_var_try_unsigned, pairs);

TYPED_TEST(ut_var_try_unsigned, can_cover_source_max) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = std::numeric_limits<source_type>::max();
    auto var = variant { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_EQ(val, var.get<target_type>());
}

TYPED_TEST(ut_var_try_unsigned, underflow) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = -1;
    auto var = variant { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_FALSE(var.get<target_type>().has_value());
}

///////////////////////////////////////////////////////////////

template<typename>
struct ut_var_try_unsigned_demote : public testing::Test {};

using demote_pairs = testing::Types<std::pair<int16_t, uint8_t>,

                                    std::pair<int32_t, uint16_t>,
                                    std::pair<int32_t, uint8_t>,

                                    std::pair<int64_t, uint32_t>,
                                    std::pair<int64_t, uint16_t>,
                                    std::pair<int64_t, uint8_t>>;

TYPED_TEST_SUITE(ut_var_try_unsigned_demote, demote_pairs);

TYPED_TEST(ut_var_try_unsigned_demote, can_cover_target_max) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = std::numeric_limits<target_type>::max();
    auto var = variant { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_EQ((target_type)val, var.get<target_type>());
}

TYPED_TEST(ut_var_try_unsigned_demote, underflow) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = -1;
    auto var = variant { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_FALSE(var.get<target_type>().has_value());
}

TYPED_TEST(ut_var_try_unsigned_demote, overflow) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = std::numeric_limits<target_type>::max();
    auto var = variant { source_type(val + 1) };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_FALSE(var.get<target_type>().has_value());
}
