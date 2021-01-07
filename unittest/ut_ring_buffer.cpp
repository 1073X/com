#include <gtest/gtest.h>

#include "com/ring_buffer.hpp"

struct ut_ring_buffer : public testing::Test {
    miu::com::ring_buffer<int32_t> ring { 16, 1 };
};

TEST_F(ut_ring_buffer, capacity_must_be_pow_of_2) {
    EXPECT_ANY_THROW(miu::com::ring_buffer<int32_t>(15));
}

TEST_F(ut_ring_buffer, properties) {
    EXPECT_EQ(16U, ring.capacity());
    EXPECT_EQ(0U, ring.size());
    EXPECT_TRUE(ring.empty());
}

TEST_F(ut_ring_buffer, push) {
    EXPECT_TRUE(ring.push(1));
    EXPECT_TRUE(ring.push(2));
    EXPECT_EQ(2U, ring.size());
    EXPECT_FALSE(ring.empty());

    EXPECT_EQ(1, ring[0]);
    EXPECT_EQ(2, ring[1]);

    while (ring.size() < ring.capacity()) {
        ring.push(99);
    }

    EXPECT_FALSE(ring.push(100));
}

TEST_F(ut_ring_buffer, dump) {
    ring.emplace(1);
    ring.emplace(2);
    ring.emplace(3);

    ring.dump(2);
    EXPECT_EQ(1U, ring.size());
}

TEST_F(ut_ring_buffer, wrap) {
    while (ring.size() < ring.capacity()) {
        ring.push(2);
    }

    ring.dump(2);
    EXPECT_TRUE(ring.push(3));
    EXPECT_TRUE(ring.push(3));
    EXPECT_FALSE(ring.push(3));
}

