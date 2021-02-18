#include <gtest/gtest.h>

#include "com/variant.hpp"

using miu::com::variant;

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

