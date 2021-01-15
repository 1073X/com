#include <gtest/gtest.h>

#include <fstream>

#include "com/directory.hpp"

namespace fs = std::filesystem;

struct ut_directory : public testing::Test {
    void TearDown() override { fs::remove_all(dir.path()); }
    miu::com::directory dir { ".", "ut_directory", "subdir" };
};

TEST_F(ut_directory, ctor) {
    ASSERT_TRUE(fs::is_directory("./ut_directory/subdir"));
    EXPECT_TRUE(fs::equivalent("./ut_directory/subdir", dir.path()));
    std::cout << dir.path() << std::endl;
}

TEST_F(ut_directory, make_file) {
    auto file = dir.make_file("xyz", 1, "abc");
    EXPECT_EQ("ut_directory/subdir/xyz.1.abc", fs::relative(file).generic_string());
    EXPECT_ANY_THROW(dir.make_file());
    EXPECT_ANY_THROW(dir.make_file(""));
}

TEST_F(ut_directory, exists_and_remove) {
    EXPECT_FALSE(dir.exists("ut_directory", 1));
    std::ofstream { dir.make_file("ut_directory", 1) };
    EXPECT_TRUE(dir.exists("ut_directory", 1));
    EXPECT_EQ(0, dir.file_size("ut_directory", 1));
    dir.remove("ut_directory", 1);
    EXPECT_FALSE(dir.exists("ut_directory", 1));
}
