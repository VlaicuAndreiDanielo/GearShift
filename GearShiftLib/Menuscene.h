#pragma once
#include "SceneManager.h"
#include "../GearShiftUI/Renderer.h"
#include "../GearShiftUI/InputHandler.h"
#include "../GearShiftUI/CRTEffect.h"
#include "../GearShiftUI/WaveEffect.h"
#include "../GearShiftUI/Button.h"
#include "../GearShiftLib/GameLogic.h"
#include <SDL2/SDL_ttf.h>
#include <memory>

class MenuScene : public Scene {
private:
    Renderer* renderer;
    SceneMgr* sceneMgr;
    GameLogic* gameLogic;        
    InputHandler* inputHandler;  

  
    std::unique_ptr<CRT> crt;
    std::unique_ptr<Wave> wave;
    std::unique_ptr<Btn> playBtn;

    TTF_Font* font;
    SDL_Texture* carTexture;
    SDL_Rect carRect;

public:
    MenuScene(Renderer* rend, SceneMgr* mgr, GameLogic* logic, InputHandler* input);
    ~MenuScene() override;

    void update(float dt) override;
    void render() override;
    void handleEvent(SDL_Event& e) override;
    std::string getName() const override { return "Menu"; }

    void onEnter() override;
    void onExit() override;
};