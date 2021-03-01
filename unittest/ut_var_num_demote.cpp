#include <gtest/gtest.h>

#include "com/variant.hpp"

using miu::com::type_id;
using miu::com::variant;

template<typename>
struct ut_var_num_demote : public testing::Test {};

using uint_pairs = testing::Types<std::pair<uint64_t, uint8_t>,
                                  std::pair<uint64_t, uint16_t>,
                                  std::pair<uint64_t, uint32_t>,
                                  std::pair<uint64_t, int64_t>,
                                  std::pair<uint64_t, int32_t>,
                                  std::pair<uint64_t, int16_t>,
                                  std::pair<uint64_t, int8_t>,

                                  std::pair<uint32_t, uint8_t>,
                                  std::pair<uint32_t, uint16_t>,
                                  std::pair<uint32_t, int8_t>,
                                  std::pair<uint32_t, int16_t>,
                                  std::pair<uint32_t, int32_t>,

                                  std::pair<uint16_t, uint8_t>,
                                  std::pair<uint16_t, int8_t>,
                                  std::pair<uint16_t, int16_t>,

                                  std::pair<uint8_t, int8_t>,

                                  std::pair<int64_t, int32_t>,
                                  std::pair<int64_t, int16_t>,
                                  std::pair<int64_t, int8_t>,

                                  std::pair<int32_t, int16_t>,
                                  std::pair<int32_t, int8_t>,

                                  std::pair<int16_t, int8_t>,

                                  std::pair<double, float>>;

TYPED_TEST_SUITE(ut_var_num_demote, uint_pairs);

TYPED_TEST(ut_var_num_demote, can_cover_target_max) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    target_type val = std::numeric_limits<target_type>::max();
    variant var { (source_type)val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_DOUBLE_EQ((target_type)val, var.get<target_type>().value());
}

TYPED_TEST(ut_var_num_demote, overflow) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    variant var { std::numeric_limits<source_type>::max() };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_FALSE(var.get<target_type>().has_value());
}
