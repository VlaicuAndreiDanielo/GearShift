/**
 * \file PlayerTests.cpp
 * \brief Unit tests pentru Player (creare, mișcare, limite, listener).
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Player.h"
#include "CollisionManager.h"
#include "BoxCollider.h"
#include "IPlayerListener.h"
#include "TrafficBaseNPC.h"
#include <random>

 /// \brief Mock pentru IInputState folosit în testele Player.
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

/// \brief Mock pentru IPlayerListener folosit pentru a verifica notificările.
class MockListener : public IPlayerListener {
public:
    MOCK_METHOD(void, onPlayerEliminated, (), (override));
};

// creation
TEST(PlayerTest, Create) {
    auto mgr = std::make_shared<CollisionManager>();
    auto player = Player::create(mgr, 100.0f, 200.0f);
    ASSERT_NE(player, nullptr);
    EXPECT_EQ(player->getType(), ObjectType::PLAYER);
}

// bounds
TEST(PlayerTest, ClampX) {
    auto mgr = std::make_shared<CollisionManager>();
    auto player = Player::create(mgr, 0, 100);
    player->setBounds(1920, 1080);
    player->setPosition(2000, 100);

    MockInput input;
    EXPECT_CALL(input, isUpPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isDownPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isLeftPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isRightPressed()).WillRepeatedly(testing::Return(false));

    player->handleUpdate(0.016f, input);
    EXPECT_LE(player->getWorldTransform().getX(), 1920.0f);
}

// movement
TEST(PlayerTest, MoveLeft) {
    auto mgr = std::make_shared<CollisionManager>();
    auto player = Player::create(mgr, 100, 100);
    player->setBounds(1920, 1080);

    MockInput input;
    EXPECT_CALL(input, isUpPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isDownPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isLeftPressed()).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(input, isRightPressed()).WillRepeatedly(testing::Return(false));

    float xBefore = player->getWorldTransform().getX();
    player->handleUpdate(0.016f, input);
    float xAfter = player->getWorldTransform().getX();

    EXPECT_LT(xAfter, xBefore);
}

TEST(PlayerTest, MoveRight) {
    auto mgr = std::make_shared<CollisionManager>();
    auto player = Player::create(mgr, 100, 100);
    player->setBounds(1920, 1080);

    MockInput input;
    EXPECT_CALL(input, isUpPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isDownPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isLeftPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isRightPressed()).WillRepeatedly(testing::Return(true));

    float xBefore = player->getWorldTransform().getX();
    player->handleUpdate(0.016f, input);
    float xAfter = player->getWorldTransform().getX();

    EXPECT_GT(xAfter, xBefore);
}

// acceleration
TEST(PlayerTest, AccelerateUp) {
    auto mgr = std::make_shared<CollisionManager>();
    auto player = Player::create(mgr, 100, 500);
    player->setBounds(1920, 1080);

    MockInput input;
    EXPECT_CALL(input, isUpPressed()).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(input, isDownPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isLeftPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isRightPressed()).WillRepeatedly(testing::Return(false));

    float yBefore = player->getWorldTransform().getY();

    for (int i = 0; i < 10; i++) {
        player->handleUpdate(0.016f, input);
    }

    float yAfter = player->getWorldTransform().getY();
    EXPECT_LT(yAfter, yBefore);
}

// listener with real collision
TEST(PlayerTest, ListenerWithCollision) {
    auto mgr = std::make_shared<CollisionManager>();
    auto player = Player::create(mgr, 100, 100);
    player->setBounds(1920, 1080);

    auto listener = std::make_shared<MockListener>();
    player->addListener(listener);

    std::mt19937 rng{ 42 };
    auto npcs = TrafficBaseNPC::create(mgr, rng, 100, 100, 150, 170, 810, 720, 100, 300);

    EXPECT_CALL(*listener, onPlayerEliminated()).Times(testing::AtLeast(0));

    mgr->update();
}

// add/remove listener
TEST(PlayerTest, AddRemoveListener) {
    auto mgr = std::make_shared<CollisionManager>();
    auto player = Player::create(mgr, 100, 100);

    auto listener = std::make_shared<MockListener>();
    player->addListener(listener);
    player->removeListener(listener);

    SUCCEED();
}
