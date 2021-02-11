#include <gtest/gtest.h>

#include "meta/info.hpp"

TEST(ut_meta_info, info) {
    EXPECT_STREQ("UKN_CATE.UKN_TYPE.UKN_NAME", miu::meta::info());

    miu::meta::set_category("test");
    miu::meta::set_type("unittest");
    miu::meta::set_name("ut_com");

    EXPECT_STREQ("test.unittest.ut_com", miu::meta::info());
}

TEST(ut_meta_info, overflow) {
    EXPECT_ANY_THROW(miu::meta::set_category("0123456789abcdef"));
    EXPECT_ANY_THROW(miu::meta::set_type("0123456789abcdef"));
    EXPECT_ANY_THROW(miu::meta::set_name("0123456789abcdef"));
}
