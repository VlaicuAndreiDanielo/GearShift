/**
 * \file Vec2Tests.cpp
 * \brief Unit tests pentru Vec2 (operații de bază, dot, normalize).
 */

#include <gtest/gtest.h>
#include "Vec2.h"
#include <cmath>

 // constructors
TEST(Vec2Test, DefaultConstructor) {
    Vec2 v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
}

TEST(Vec2Test, ParameterizedConstructor) {
    Vec2 v{ 3.0f, 4.0f };
    EXPECT_FLOAT_EQ(v.x, 3.0f);
    EXPECT_FLOAT_EQ(v.y, 4.0f);
}

// addition
TEST(Vec2Test, Addition) {
    Vec2 v1{ 1.0f, 2.0f };
    Vec2 v2{ 3.0f, 4.0f };
    Vec2 result = v1 + v2;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}

// subtraction
TEST(Vec2Test, Subtraction) {
    Vec2 v1{ 5.0f, 7.0f };
    Vec2 v2{ 2.0f, 3.0f };
    Vec2 result = v1 - v2;
    EXPECT_FLOAT_EQ(result.x, 3.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
}

// multiply
TEST(Vec2Test, Multiply) {
    Vec2 v{ 2.0f, 3.0f };
    Vec2 result = v * 3.0f;
    EXPECT_FLOAT_EQ(result.x, 6.0f);
    EXPECT_FLOAT_EQ(result.y, 9.0f);
}

// dot product
TEST(Vec2Test, DotProduct) {
    Vec2 v1{ 3.0f, 4.0f };
    Vec2 v2{ 2.0f, 1.0f };
    float result = dot(v1, v2);
    EXPECT_FLOAT_EQ(result, 10.0f);
}

// normalize
TEST(Vec2Test, Normalize) {
    Vec2 v{ 3.0f, 4.0f };
    Vec2 result = normalize(v);
    EXPECT_FLOAT_EQ(result.x, 0.6f);
    EXPECT_FLOAT_EQ(result.y, 0.8f);
}

TEST(Vec2Test, NormalizeZero) {
    Vec2 v{ 0.0f, 0.0f };
    Vec2 result = normalize(v);
    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, 0.0f);
}
