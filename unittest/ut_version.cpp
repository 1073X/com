#include <gtest/gtest.h>

#include <iostream>

namespace miu::com {
extern std::string_view version();
extern std::string_view build_info();
}    // namespace miu::com

TEST(ut_version, version) {
    std::cout << miu::com::version() << std::endl;
    std::cout << miu::com::build_info() << std::endl;
}
