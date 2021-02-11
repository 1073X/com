#include <gtest/gtest.h>

#include "meta/info.hpp"

TEST(ut_meta_info, info) {
    EXPECT_EQ("UKN_CATE.UKN_TYPE.UKN_NAME", miu::meta::info());

    miu::meta::set_category("test");
    miu::meta::set_type("unittest");
    miu::meta::set_name("ut_com");

    EXPECT_EQ("test.unittest.ut_com", miu::meta::info());
}

