#pragma once
#include "FuelTimer.h"
#include "SceneManager.h"
#include "../GearShiftUI/Renderer.h"
#include "../GearShiftUI/InputHandler.h"
#include "../GearShiftUI/PlayerRenderer.h"
#include "../GearShiftLib/GameLogic.h"
#include <memory>

class GameScene : public Scene {
private:
    Renderer* renderer;
    SceneMgr* sceneMgr;
    GameLogic* gameLogic;        
    InputHandler* inputHandler;  

    
    std::unique_ptr<PlayerRenderer> playerRenderer;
    std::unique_ptr<FuelTimer> fuelTimer;

public:
    GameScene(Renderer* rend, SceneMgr* mgr, GameLogic* logic, InputHandler* input);
    ~GameScene() override = default;

    void update(float dt) override;
    void render() override;
    void handleEvent(SDL_Event& e) override;
    std::string getName() const override { return "Game"; }

    void onEnter() override;
    void onExit() override;
};