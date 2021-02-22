#include <gtest/gtest.h>

#include "com/variant.hpp"
#include "time/stamp.hpp"

using namespace std::chrono_literals;
using miu::com::type_id;
using miu::com::variant;
using miu::time::date;
using miu::time::days;
using miu::time::daytime;
using miu::time::delta;
using miu::time::stamp;

using pairs = testing::Types<std::pair<int8_t, days>,
                             std::pair<int16_t, days>,
                             std::pair<int32_t, days>,
                             std::pair<int64_t, days>,
                             std::pair<uint8_t, days>,
                             std::pair<uint16_t, days>,
                             std::pair<uint32_t, days>,
                             std::pair<uint64_t, days>,

                             std::pair<int8_t, delta>,
                             std::pair<int16_t, delta>,
                             std::pair<int32_t, delta>,
                             std::pair<int64_t, delta>,
                             std::pair<uint8_t, delta>,
                             std::pair<uint16_t, delta>,
                             std::pair<uint32_t, delta>,
                             std::pair<uint64_t, delta>,

                             std::pair<int8_t, date>,
                             std::pair<int16_t, date>,
                             std::pair<int32_t, date>,
                             std::pair<int64_t, date>,
                             std::pair<uint8_t, date>,
                             std::pair<uint16_t, date>,
                             std::pair<uint32_t, date>,
                             std::pair<uint64_t, date>,

                             std::pair<int8_t, daytime>,
                             std::pair<int16_t, daytime>,
                             std::pair<int32_t, daytime>,
                             std::pair<int64_t, daytime>,
                             std::pair<uint8_t, daytime>,
                             std::pair<uint16_t, daytime>,
                             std::pair<uint32_t, daytime>,
                             std::pair<uint64_t, daytime>,

                             std::pair<int8_t, stamp>,
                             std::pair<int16_t, stamp>,
                             std::pair<int32_t, stamp>,
                             std::pair<int64_t, stamp>,
                             std::pair<uint8_t, stamp>,
                             std::pair<uint16_t, stamp>,
                             std::pair<uint32_t, stamp>,
                             std::pair<uint64_t, stamp>>;

//////////////////////////////////////////////
template<typename>
struct ut_var_num_chrono : public testing::Test {};

TYPED_TEST_SUITE(ut_var_num_chrono, pairs);

TYPED_TEST(ut_var_num_chrono, num_to_chrono) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    auto val = source_type { 123 };
    auto var = variant { val };
    EXPECT_EQ(target_type(123), var.get<target_type>());
}

TYPED_TEST(ut_var_num_chrono, chrono_to_num) {
    using target_type = typename TypeParam::first_type;
    using source_type = typename TypeParam::second_type;

    auto val = source_type { 123 };
    auto var = variant { val };
    EXPECT_EQ(target_type(123), var.get<target_type>());
}

