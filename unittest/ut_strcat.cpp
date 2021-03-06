#include <gtest/gtest.h>

#include "com/strcat.hpp"

TEST(ut_strcat, initializer) {
    char array[] = "array";
    std::string str { "string" };
    std::string_view view { "view" };
    miu::com::strcat cat { array, 'b', 1, view, &array[0], str };
    EXPECT_EQ("array.b.1.view.array.string", cat.str());
    EXPECT_EQ(cat.str(), miu::com::to_string(cat));
}

TEST(ut_strcat, push_back) {
    miu::com::strcat cat {};
    EXPECT_EQ("", cat.str());

    cat.push_back(1);
    EXPECT_EQ("1", cat.str());

    cat += 2;
    EXPECT_EQ("1.2", cat.str());

    auto cat2 = cat + 3;
    EXPECT_EQ("1.2", cat.str());
    EXPECT_EQ("1.2.3", cat2.str());
}

TEST(ut_strcat, merge) {
    miu::com::strcat cat0 { 1, 2, 3 };

    miu::com::strcat cat { cat0, cat0 };
    EXPECT_EQ(6U, cat.size());
    EXPECT_EQ("1.2.3.1.2.3", cat.str());

    cat.push_back(cat0);
    EXPECT_EQ(9U, cat.size());
    EXPECT_EQ("1.2.3.1.2.3.1.2.3", cat.str());
}

TEST(ut_strcat, concat) {
    miu::com::strcat::delimiter del { "-" };
    miu::com::strcat cat0 { 1, 2, 3, del };

    miu::com::strcat cat { 0, cat0 };
    EXPECT_EQ(2U, cat.size());
    EXPECT_EQ("0.1-2-3", cat.str());

    cat.push_back(cat0);
    EXPECT_EQ(3U, cat.size());
    EXPECT_EQ("0.1-2-3.1-2-3", cat.str());
}

TEST(ut_strcat, vector) {
    std::vector vec { 1, 2, 3 };
    miu::com::strcat cat { vec };
    EXPECT_EQ("1.2.3", cat.str());

    cat += std::vector { "a", "b" };
    EXPECT_EQ("1.2.3.a.b", cat.str());
}

TEST(ut_strcat, delimiter) {
    miu::com::strcat cat { 1, 2, miu::com::strcat::delimiter { "---" } };
    EXPECT_EQ("1---2", cat.str());
}

struct st {
    int32_t value;
};

DEF_TO_STRING(st) {
    return std::to_string(v.value);
}

TEST(ut_strcat, custom_type) {
    st s { 123 };
    EXPECT_EQ("1.123", miu::com::strcat(1, s).str());
}

TEST(ut_strcat, as_container) {
    miu::com::strcat cat { 1, 2, 3 };
    EXPECT_EQ(3U, cat.size());

    auto it = cat.begin();
    EXPECT_EQ("1", *it);
    it++;
    EXPECT_EQ("2", *it);
    it++;
    EXPECT_EQ("3", *it);
    it++;
    EXPECT_EQ(cat.end(), it);
}
