#include <gtest/gtest.h>

#include "com/variant.hpp"
#include "time/stamp.hpp"

using miu::com::type_id;
using miu::com::variant;
using miu::time::date;
using miu::time::days;
using miu::time::daytime;
using miu::time::delta;
using miu::time::stamp;

template<typename>
struct ut_var_time_to_dec : public testing::Test {};

using pairs = testing::Types<std::pair<days, double>,
                             std::pair<days, float>,
                             std::pair<delta, double>,
                             std::pair<delta, float>,
                             std::pair<date, double>,
                             std::pair<date, float>,
                             std::pair<daytime, double>,
                             std::pair<daytime, float>,
                             std::pair<stamp, double>,
                             std::pair<stamp, float>>;

TYPED_TEST_SUITE(ut_var_time_to_dec, pairs);

TYPED_TEST(ut_var_time_to_dec, cast) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    auto val = source_type { 123 };
    variant var { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_DOUBLE_EQ(123.0, var.get<target_type>().value());
}
