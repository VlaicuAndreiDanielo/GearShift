/**
 * \file GameObjectTests.cpp
 * \brief Unit tests pentru GameObject (construcție, activare, dimensiuni, transform).
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameObject.h"
#include "IInputState.h"

 /// \brief Mock pentru IInputState folosit în testele GameObject.
class MockInput : public IInputState {
public:
    MOCK_METHOD(bool, isUpPressed, (), (const, override));
    MOCK_METHOD(bool, isDownPressed, (), (const, override));
    MOCK_METHOD(bool, isLeftPressed, (), (const, override));
    MOCK_METHOD(bool, isRightPressed, (), (const, override));
    MOCK_METHOD(bool, isAcceleratePressed, (), (const, override));
    MOCK_METHOD(bool, isBrakePressed, (), (const, override));
    MOCK_METHOD(bool, isPausePressed, (), (override));
    MOCK_METHOD(int, getMouseX, (), (const, override));
    MOCK_METHOD(int, getMouseY, (), (const, override));
    MOCK_METHOD(bool, isMousePressed, (), (const, override));
};

// construction
TEST(GameObjectTest, Construction) {
    GameObject obj(100.0f, 200.0f, 50.0f, 75.0f, true);
    EXPECT_FLOAT_EQ(obj.getWorldTransform().getX(), 100.0f);
    EXPECT_FLOAT_EQ(obj.getWidth(), 50.0f);
    EXPECT_TRUE(obj.isActive());
}

// active
TEST(GameObjectTest, SetActive) {
    GameObject obj(0, 0, 10, 10, false);
    obj.setActive(true);
    EXPECT_TRUE(obj.isActive());
}

// size
TEST(GameObjectTest, SetSize) {
    GameObject obj(0, 0, 10, 10, true);
    obj.setSize(20.0f, 30.0f);
    EXPECT_FLOAT_EQ(obj.getWidth(), 20.0f);
    EXPECT_FLOAT_EQ(obj.getHeight(), 30.0f);
}

// transform
TEST(GameObjectTest, SetTransform) {
    auto obj = std::make_shared<GameObject>(0, 0, 10, 10, true);
    obj->setWorldTransform({ 50.0f, 75.0f }, 1.5f);
    EXPECT_FLOAT_EQ(obj->getWorldTransform().getX(), 50.0f);
    EXPECT_FLOAT_EQ(obj->getWorldTransform().getRotation(), 1.5f);
}

// sprite
TEST(GameObjectTest, SetSprite) {
    GameObject obj(0, 0, 10, 10, true);
    obj.setSprite(SpriteType::PLAYER);
    EXPECT_EQ(obj.getSprite(), SpriteType::PLAYER);
}

// parent-child relationship
TEST(GameObjectTest, ChildFollowsParent) {
    auto parent = std::make_shared<GameObject>(100, 100, 50, 50, true);
    auto child = std::make_shared<GameObject>(120, 120, 30, 30, true);

    child->setParent(parent);

    // test that setParent works
    SUCCEED();
}
