/**
 * \file GameLogicTests.cpp
 * \brief Unit tests pentru GameLogic (stări, timp, fabric, obiecte).
 *
 * Folosește GoogleMock pentru a simula IInputState și verifică:
 *  - crearea jocului și starea inițială;
 *  - existența și dimensiunea pânzei (IFabric);
 *  - tranzițiile de stare (start/pause/resume/end);
 *  - incrementarea timpului de joc în update().
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameLogic.h"
#include "IInputState.h"

 /// \brief Mock pentru interfața IInputState folosită în testele GameLogic.
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

// creation
TEST(GameLogicTest, Create) {
    auto game = GameLogic::create(1920, 1080);
    ASSERT_NE(game, nullptr);
    EXPECT_EQ(game->getState(), GameState::Menu);
}

// fabric
TEST(GameLogicTest, HasFabric) {
    auto game = GameLogic::create(1920, 1080);
    auto fabric = game->getFabric();
    ASSERT_NE(fabric, nullptr);
    EXPECT_GT(fabric->getW(), 0);
}

// state
TEST(GameLogicTest, StartGame) {
    auto game = GameLogic::create(1920, 1080);
    game->startGame();
    EXPECT_EQ(game->getState(), GameState::Playing);
    EXPECT_GT(game->getGameObjects().size(), 0);
}

TEST(GameLogicTest, PauseGame) {
    auto game = GameLogic::create(1920, 1080);
    game->startGame();
    game->pauseGame();
    EXPECT_EQ(game->getState(), GameState::Paused);
}

TEST(GameLogicTest, ResumeGame) {
    auto game = GameLogic::create(1920, 1080);
    game->startGame();
    game->pauseGame();
    game->resumeGame();
    EXPECT_EQ(game->getState(), GameState::Playing);
}

TEST(GameLogicTest, EndGame) {
    auto game = GameLogic::create(1920, 1080);
    game->startGame();
    game->endGame();
    EXPECT_EQ(game->getState(), GameState::GameOver);
}

// update
TEST(GameLogicTest, UpdateTime) {
    auto game = GameLogic::create(1920, 1080);
    game->startGame();

    MockInput input;
    EXPECT_CALL(input, isUpPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isDownPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isLeftPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isRightPressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isPausePressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isAcceleratePressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, isBrakePressed()).WillRepeatedly(testing::Return(false));
    EXPECT_CALL(input, getMouseX()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(input, getMouseY()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(input, isMousePressed()).WillRepeatedly(testing::Return(false));

    float time = game->getTime();
    game->update(0.5f, input);
    EXPECT_GT(game->getTime(), time);
}
