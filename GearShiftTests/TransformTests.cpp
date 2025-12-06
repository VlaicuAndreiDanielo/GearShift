/**
 * \file TransformTests.cpp
 * \brief Unit tests pentru Transform (poziție, rotație, lock-uri).
 */

#include <gtest/gtest.h>
#include "Transform.h"
#include "Vec2.h"

 // constructors
TEST(TransformTest, DefaultConstructor) {
    Transform t;
    EXPECT_FLOAT_EQ(t.getX(), 0.0f);
    EXPECT_FLOAT_EQ(t.getY(), 0.0f);
}

TEST(TransformTest, WithPosition) {
    Transform t({ 10.0f, 20.0f });
    EXPECT_FLOAT_EQ(t.getX(), 10.0f);
    EXPECT_FLOAT_EQ(t.getY(), 20.0f);
}

// position
TEST(TransformTest, SetPosition) {
    Transform t;
    t.setPosition({ 5.0f, 15.0f });
    EXPECT_FLOAT_EQ(t.getX(), 5.0f);
    EXPECT_FLOAT_EQ(t.getY(), 15.0f);
}

TEST(TransformTest, SetX) {
    Transform t;
    t.setX(25.0f);
    EXPECT_FLOAT_EQ(t.getX(), 25.0f);
}

TEST(TransformTest, SetY) {
    Transform t;
    t.setY(35.0f);
    EXPECT_FLOAT_EQ(t.getY(), 35.0f);
}

// rotation
TEST(TransformTest, SetRotation) {
    Transform t;
    t.setRotation(1.5f);
    EXPECT_FLOAT_EQ(t.getRotation(), 1.5f);
}

// fixed
TEST(TransformTest, SetFixed) {
    Transform t;
    t.setFixed(true);
    EXPECT_TRUE(t.getFixed());
}

// lock x
TEST(TransformTest, LockX) {
    Transform t;
    t.setPosition({ 10.0f, 20.0f });
    t.setLockX(true);
    t.setPosition({ 100.0f, 200.0f });
    EXPECT_FLOAT_EQ(t.getX(), 10.0f);
    EXPECT_FLOAT_EQ(t.getY(), 200.0f);
}

// lock y
TEST(TransformTest, LockY) {
    Transform t;
    t.setPosition({ 10.0f, 20.0f });
    t.setLockY(true);
    t.setPosition({ 100.0f, 200.0f });
    EXPECT_FLOAT_EQ(t.getX(), 100.0f);
    EXPECT_FLOAT_EQ(t.getY(), 20.0f);
}

// lock rotation
TEST(TransformTest, LockRotation) {
    Transform t;
    t.setRotation(1.0f);
    t.setLockRotation(true);
    t.setRotation(2.0f);
    EXPECT_FLOAT_EQ(t.getRotation(), 1.0f);
}
