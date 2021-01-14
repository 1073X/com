#include <gtest/gtest.h>

#include "com/strcat.hpp"

TEST(ut_strcat, concat) {
    char array[] = "array";
    std::string_view view { "view" };
    miu::com::strcat cat { array, 'b', 1, view, &array[0] };
    EXPECT_EQ("array.b.1.view.array", cat.str());
}

TEST(ut_strcat, delimiter) {
    miu::com::strcat cat { 1, 2, miu::com::strcat::delimiter { "---" } };
    EXPECT_EQ("1---2", cat.str());
}

struct st {
    int32_t value;
};

namespace miu::com {
template<>
struct strcat::cast<st> {
    auto operator()(st const& v) { return std::to_string(v.value); }
};
}    // namespace miu::com

TEST(ut_strcat, custom_type) {
    st s { 123 };
    EXPECT_EQ("1.123", miu::com::strcat(1, s).str());
}
