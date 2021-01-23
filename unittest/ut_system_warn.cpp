#include <gtest/gtest.h>

#include "com/system_warn.hpp"

TEST(ut_system_warn, warn) {
    SYSTEM_WARN(1, "a", 'b');
}
