#include <gtest/gtest.h>

#include <sstream>

#include "com/json.hpp"

TEST(ut_json, fifo_dump) {
    auto json = miu::com::json();
    json["b"] = 2;
    json["a"] = 1;

    std::ostringstream ss;
    ss << json;
    EXPECT_EQ(R"({"b":2,"a":1})", ss.str());
}

TEST(ut_json, fifo_load) {
    auto str  = R"({"b":2,"a":1})";
    auto json = miu::com::json::parse(str);

    std::ostringstream ss;
    ss << json;
    EXPECT_EQ(str, ss.str());
}

TEST(ut_json, ordered_dump) {
    auto json = miu::com::ordered_json();
    json["b"] = 2;
    json["a"] = 1;

    std::ostringstream ss;
    ss << json;
    EXPECT_EQ(R"({"a":1,"b":2})", ss.str());
}

TEST(ut_json, ordered_load) {
    auto json = miu::com::ordered_json::parse(R"({"b":2,"a":1})");

    std::ostringstream ss;
    ss << json;
    EXPECT_EQ(R"({"a":1,"b":2})", ss.str());
}

