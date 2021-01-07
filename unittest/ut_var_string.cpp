#include <gtest/gtest.h>

#include "com/variant.hpp"

using miu::com::type_id;
using miu::com::variant;

template<typename>
struct ut_var_string : public testing::Test {};

using pairs = testing::Types<std::pair<std::string, std::string>,
                             std::pair<const char*, std::string>,
                             std::pair<std::string_view, std::string>,

                             std::pair<const char*, const char*>,
                             std::pair<std::string, const char*>,
                             std::pair<std::string_view, const char*>>;

TYPED_TEST_SUITE(ut_var_string, pairs);

TYPED_TEST(ut_var_string, test) {
    using source_type = typename TypeParam::first_type;
    using target_type = typename TypeParam::second_type;

    source_type val = +"abcdefg";
    variant var { val };
    EXPECT_EQ(type_id<source_type>::value, var.id());
    EXPECT_EQ(std::string_view("abcdefg"), var.get<target_type>());
}

