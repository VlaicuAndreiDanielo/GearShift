#pragma once
#include "SceneManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "CRTEffect.h"
#include "WaveEffect.h"
#include "Button.h"
#include "IGame.h"
#include "../GearShiftLib/CommandManager.h"
#include <SDL2/SDL_ttf.h>
#include <memory>

class MenuScene : public IScene {
private:
    Renderer* renderer;
    SceneMgr* sceneMgr;
    std::weak_ptr<IGame> game;        
    InputHandler* inputHandler;  

    // Command manager for handling menu actions
    std::shared_ptr<CommandManager> commandMgr;
  
    std::unique_ptr<CRT> crt;
    std::unique_ptr<Wave> wave;
    std::unique_ptr<Btn> playBtn;
    std::unique_ptr<Btn> exitBtn;

    TTF_Font* font;
    SDL_Texture* carTexture;
    SDL_Rect carRect;
    
    // Cleanup flag to prevent double-cleanup
    bool cleanedUp;

private:
    // Helper method to setup commands
    void setupCommands();

public:
    MenuScene(Renderer* rend, SceneMgr* mgr, std::weak_ptr<IGame> logic, InputHandler* input, std::shared_ptr<CommandManager> globalCommandMgr);
    ~MenuScene() override;

    void update(float dt) override;
    void render() override;
    void handleEvent(SDL_Event& e) override;
    std::string getName() const override { return "Menu"; }

    void onEnter() override;
    void onExit() override;
};