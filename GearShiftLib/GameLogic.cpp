#include "GameLogic.h"

GameLogic::GameLogic(int screenW, int screenH)
    : screenWidth(screenW), screenHeight(screenH),
    currentState(GameState::Menu),
    gameTime(0), speed(0), score(0), lapTime(0) {

    // create fabric for background effect
    fabric = std::make_unique<Fabric>(130, 75, 16.0f);

    // player created when game starts (not in menu)
    player = nullptr;
}

void GameLogic::update(float dt, const IInputState& input) {
  
    gameTime += dt;

    // update fabric 
    fabric->update(dt);

    // update based on game state
    switch (currentState) {
    case GameState::Menu:
        // menu logic here (minimal for now) TODO:maybe implement other options in the menu 
        break;

    case GameState::Playing:
        if (player) {
            player->handleInput(input);
            player->update(dt);

            // update game stats
            // TODO: Aad game logic (lap counting, collision, etc.)
        }

        // check for pause ->ESC conflict for now the esc button is used for scene change 
        if (input.isPausePressed()) {
            pauseGame();
        }
        break;

    case GameState::Paused: 
        // check for resume
        if (input.isPausePressed()) {
            resumeGame();
        }
        break;

    case GameState::GameOver:
        // game over logic TODO:make one 
        break;
    }
}

void GameLogic::startGame() {
    currentState = GameState::Playing;

    // create player at center
    float centerX = screenWidth / 2.0f - 25;
    float centerY = screenHeight / 2.0f - 25;
    player = std::make_unique<Player>(centerX, centerY);
    player->setBounds(screenWidth, screenHeight);

    // reset game stats
    speed = 0;
    score = 0;
    lapTime = 0;
    gameTime = 0;
}

void GameLogic::pauseGame() {
    if (currentState == GameState::Playing) {
        currentState = GameState::Paused;
    }
}

void GameLogic::resumeGame() {
    if (currentState == GameState::Paused) {
        currentState = GameState::Playing;
    }
}

void GameLogic::endGame() {
    currentState = GameState::GameOver;
    // player stays in memory for showing final position the nes game did that when it resumed on button 
}

void GameLogic::applyMouseForce(int x, int y, bool pressed) {
    if (pressed && fabric) {
        fabric->applyForce((float)x, (float)y, 100.0f, 800.0f);
    }
}