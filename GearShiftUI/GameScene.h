#pragma once
#include "FuelRenderer.h"
#include "ScoreRenderer.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "ObjectRenderer.h"
#include "IGame.h"
#include "../GearShiftLib/CommandManager.h"
#include <memory>
#include <SDL2/SDL_ttf.h>

class GameScene : public IScene {
private:
    Renderer* renderer;
    SceneMgr* sceneMgr;
    std::weak_ptr<IGame> game;        
    InputHandler* inputHandler;  

    // Command manager for game scene actions
    std::shared_ptr<CommandManager> commandMgr;
    
    std::unique_ptr<ObjectRenderer> objectRenderer;
    std::unique_ptr<FuelRenderer> fuelRenderer;
	std::unique_ptr<ScoreRenderer> scoreRenderer;
    TTF_Font* font;

private:
    // Helper method to setup commands
    void setupCommands();

public:
    GameScene(Renderer* rend, SceneMgr* mgr, std::weak_ptr<IGame> logic, InputHandler* input, std::shared_ptr<CommandManager> globalCommandMgr);
    ~GameScene() override = default;

    void update(float dt) override;
    void render() override;
    void handleEvent(SDL_Event& e) override;
    std::string getName() const override { return "Game"; }

    void onEnter() override;
    void onExit() override;

private:
    void renderPausedText();
};