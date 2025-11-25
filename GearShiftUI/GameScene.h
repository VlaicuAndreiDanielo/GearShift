#pragma once
#include "FuelTimer.h"
#include "ScoreManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "ObjectRenderer.h"
#include "IGame.h"
#include <memory>
#include <SDL2/SDL_ttf.h>

class GameScene : public IScene {
private:
    Renderer* renderer;
    SceneMgr* sceneMgr;
    std::weak_ptr<IGame> game;        
    InputHandler* inputHandler;  

    
    std::unique_ptr<ObjectRenderer> objectRenderer;
    std::unique_ptr<FuelTimer> fuelTimer;
	std::unique_ptr<ScoreManager> scoreManager;
    TTF_Font* font;

public:
    GameScene(Renderer* rend, SceneMgr* mgr, std::weak_ptr<IGame> logic, InputHandler* input);
    ~GameScene() override = default;

    void update(float dt) override;
    void render() override;
    void handleEvent(SDL_Event& e) override;
    std::string getName() const override { return "Game"; }

    void onEnter() override;
    void onExit() override;

    bool isFuelFinished() const;
	void collectFuelCanister();
private:
    void renderPausedText();
};