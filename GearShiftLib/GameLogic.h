#pragma once
#include "Player.h"
#include "FabricPhysics.h"
#include "IInputState.h"
#include <memory>


enum class GameState {
    Menu,
    Playing,
    Paused,
    GameOver
};

class GameLogic {
private:
    // game entities for now
    std::unique_ptr<Player> player;
    std::unique_ptr<Fabric> fabric;

    // game state
    GameState currentState;
    float gameTime;
    int screenWidth, screenHeight;

    // game stats -> reference 
    float speed;
    int score;
    float lapTime;

public:
    GameLogic(int screenW, int screenH);

    // core update loop
    void update(float dt, const IInputState& input);

    // state management
    void startGame();
    void pauseGame();
    void resumeGame();
    void endGame();

    // getters
    Player* getPlayer() { return player.get(); }
    const Player* getPlayer() const { return player.get(); }
    Fabric& getFabric() { return *fabric; }
    const Fabric& getFabric() const { return *fabric; }

    GameState getState() const { return currentState; }
    float getTime() const { return gameTime; }
    float getSpeed() const { return speed; }
    int getScore() const { return score; }
    float getLapTime() const { return lapTime; }

    // game logic
    void applyMouseForce(int x, int y, bool pressed);
};