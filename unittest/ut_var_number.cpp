#include <gtest/gtest.h>

#include "com/variant.hpp"

using miu::com::type_id;
using miu::com::variant;

template<typename>
struct ut_var_promote : public testing::Test {};

using pairs = testing::Types<std::pair<bool, int64_t>,
                             std::pair<bool, int32_t>,
                             std::pair<bool, int16_t>,
                             std::pair<bool, int8_t>,
                             std::pair<bool, uint64_t>,
                             std::pair<bool, uint32_t>,
                             std::pair<bool, uint16_t>,
                             std::pair<bool, uint8_t>,

                             std::pair<char, int64_t>,
                             std::pair<char, int32_t>,
                             std::pair<char, int16_t>,
                             std::pair<char, int8_t>,

                             std::pair<int8_t, int64_t>,
                             std::pair<int8_t, int32_t>,
                             std::pair<int8_t, int16_t>,
                             std::pair<int8_t, int8_t>,
                             std::pair<int8_t, float>,
                             std::pair<int8_t, double>,

                             std::pair<int16_t, int64_t>,
                             std::pair<int16_t, int32_t>,
                             std::pair<int16_t, int16_t>,
                             std::pair<int16_t, float>,
                             std::pair<int16_t, double>,

                             std::pair<int32_t, int64_t>,
                             std::pair<int32_t, int32_t>,
                             std::pair<int32_t, float>,
                             std::pair<int32_t, double>,

                             std::pair<int64_t, int64_t>,
                             std::pair<int64_t, float>,
                             std::pair<int64_t, double>,

                             std::pair<uint8_t, int64_t>,
                             std::pair<uint8_t, int32_t>,
                             std::pair<uint8_t, int16_t>,
                             std::pair<uint8_t, uint64_t>,
                             std::pair<uint8_t, uint32_t>,
                             std::pair<uint8_t, uint16_t>,
                             std::pair<uint8_t, uint8_t>,
                             std::pair<uint8_t, float>,
                             std::pair<uint8_t, double>,

                             std::pair<uint16_t, int64_t>,
                             std::pair<uint16_t, int32_t>,
                             std::pair<uint16_t, uint64_t>,
                             std::pair<uint16_t, uint32_t>,
                             std::pair<uint16_t, uint16_t>,
                             std::pair<uint16_t, float>,
                             std::pair<uint16_t, double>,

                             std::pair<uint32_t, int64_t>,
                             std::pair<uint32_t, uint64_t>,
                             std::pair<uint32_t, uint32_t>,
                             std::pair<uint32_t, float>,
                             std::pair<uint32_t, double>,

                             std::pair<uint64_t, uint64_t>,
                             std::pair<uint64_t, float>,
                             std::pair<uint64_t, double>,

                             std::pair<float, float>,

                             std::pair<float, double>,
                             std::pair<double, double>>;

TYPED_TEST_SUITE(ut_var_promote, pairs);

TYPED_TEST(ut_var_promote, can_cover_source_max) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = std::numeric_limits<source_type>::max();
    auto var        = variant { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_DOUBLE_EQ((target_type)val, var.get<target_type>().value());
}

TYPED_TEST(ut_var_promote, can_cover_source_lowest) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = std::numeric_limits<source_type>::lowest();
    auto var        = variant { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_DOUBLE_EQ((target_type)val, var.get<target_type>().value());
}

//////////////////////////////////////////////////////////

template<typename>
struct ut_var_num_str : public testing::Test {};

using str_pairs = testing::
    Types<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float, double>;

TYPED_TEST_SUITE(ut_var_num_str, str_pairs);

TYPED_TEST(ut_var_num_str, test) {
    TypeParam val = 123;
    variant var { val };
    EXPECT_EQ(miu::com::to_string(val), var.get<std::string>());
}

//////////////////////////////////////////////////////////

TEST(ut_var_num, from_string) {
    EXPECT_EQ(123, variant { +"123" }.get<int32_t>().value());
    EXPECT_EQ(123, variant { +"123" }.get<uint32_t>().value());
    EXPECT_EQ(123, variant { std::string("123") }.get<int32_t>().value());
    EXPECT_EQ(-123, variant { +"-123" }.get<int32_t>().value());

    EXPECT_FALSE(variant { +"a" }.get<int32_t>());
    EXPECT_FALSE(variant { +"" }.get<int32_t>());
    EXPECT_FALSE(variant { +"-123" }.get<uint32_t>());
}
