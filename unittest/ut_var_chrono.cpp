#include <gtest/gtest.h>

#include "com/variant.hpp"

using namespace std::chrono_literals;
using miu::com::date;
using miu::com::datetime;
using miu::com::days;
using miu::com::daytime;
using miu::com::microseconds;
using miu::com::type_id;
using miu::com::variant;

struct ut_var_chrono : public testing::Test {};

TEST_F(ut_var_chrono, days) {
    days val { 1 };
    variant var { val };
    EXPECT_EQ(type_id<days>::value, var.id());
    EXPECT_EQ(val, var.get<days>().value());
    EXPECT_EQ("1d", var.get<std::string>().value());
}

TEST_F(ut_var_chrono, microseconds) {
    microseconds val { 1 };
    variant var { val };
    EXPECT_EQ(type_id<microseconds>::value, var.id());
    EXPECT_EQ(val, var.get<microseconds>().value());
    EXPECT_EQ("1us", var.get<std::string>().value());

    auto str = +"24:01:01.000001";
    auto exp = microseconds(24h + 1min + 1s + 1us);
    EXPECT_EQ(exp, variant { str }.get<microseconds>());
    EXPECT_EQ(exp, variant { std::string(str) }.get<microseconds>());
    EXPECT_EQ(exp, variant { exp.count() }.get<microseconds>());

    EXPECT_FALSE(variant { true }.get<microseconds>());
}

TEST_F(ut_var_chrono, date) {
    date val { 2021, 1, 7 };
    variant var { val };
    EXPECT_EQ(type_id<date>::value, var.id());
    EXPECT_EQ(val, var.get<date>().value());
    EXPECT_EQ("20210107", var.get<std::string>().value());

    auto str = +"20210113";
    EXPECT_EQ(date(2021, 1, 13), variant { str }.get<date>().value());
    EXPECT_EQ(date(2021, 1, 13), variant { std::string(str) }.get<date>().value());

    EXPECT_FALSE(variant { 1.2 }.get<date>());
}

TEST_F(ut_var_chrono, daytime) {
    daytime val { 13, 49, 30, 999 };
    variant var { val };
    EXPECT_EQ(type_id<daytime>::value, var.id());
    EXPECT_EQ(val, var.get<daytime>().value());
    EXPECT_EQ("13:49:30.000999", var.get<std::string>().value());

    auto str = +"23:01:01.000001";
    auto exp = daytime { str };
    EXPECT_EQ(exp, variant { str }.get<daytime>());
    EXPECT_EQ(exp, variant { std::string(str) }.get<daytime>());

    EXPECT_FALSE(variant { 1.2 }.get<daytime>());
}

TEST_F(ut_var_chrono, datetime) {
    datetime val { 2021, 1, 7, 13, 49, 30, 999 };
    variant var { val };
    EXPECT_EQ(type_id<datetime>::value, var.id());
    EXPECT_EQ(val, var.get<datetime>().value());
    EXPECT_EQ("20210107 13:49:30.000999", var.get<std::string>().value());

    auto str = +"20210113 23:01:01.000001";
    auto exp = datetime { str };
    EXPECT_EQ(exp, variant { str }.get<datetime>());
}

//////////////////////////////////////////////////
using pairs = testing::Types<std::pair<int8_t, days>,
                             std::pair<int16_t, days>,
                             std::pair<int32_t, days>,
                             std::pair<int64_t, days>,
                             std::pair<uint8_t, days>,
                             std::pair<uint16_t, days>,
                             std::pair<uint32_t, days>,
                             std::pair<uint64_t, days>,

                             std::pair<int8_t, microseconds>,
                             std::pair<int16_t, microseconds>,
                             std::pair<int32_t, microseconds>,
                             std::pair<int64_t, microseconds>,
                             std::pair<uint8_t, microseconds>,
                             std::pair<uint16_t, microseconds>,
                             std::pair<uint32_t, microseconds>,
                             std::pair<uint64_t, microseconds>,

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

                             std::pair<int8_t, datetime>,
                             std::pair<int16_t, datetime>,
                             std::pair<int32_t, datetime>,
                             std::pair<int64_t, datetime>,
                             std::pair<uint8_t, datetime>,
                             std::pair<uint16_t, datetime>,
                             std::pair<uint32_t, datetime>,
                             std::pair<uint64_t, datetime>>;

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

