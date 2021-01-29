#include <gtest/gtest.h>

#include "meta/info.hpp"

#if 0
namespace miu::meta {
std::string_view category() {
    return +"test";
}
std::string_view type() {
    return +"unittest";
}
std::string_view name() {
    return +"ut_com";
}
}    // namespace miu::meta
#endif

TEST(ut_meta_info, info) {
    EXPECT_EQ("miu.test.unittest.ut_com", miu::meta::info());
}

