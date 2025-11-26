#pragma once
#include "SceneManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "CRTEffect.h"
#include "WaveEffect.h"
#include "Button.h"
#include "IGame.h"
#include <SDL2/SDL_ttf.h>
#include <memory>

class MenuScene : public IScene {
private:
    Renderer* renderer;
    SceneMgr* sceneMgr;
    std::weak_ptr<IGame> game;        
    InputHandler* inputHandler;  

  
    std::unique_ptr<CRT> crt;
    std::unique_ptr<Wave> wave;
    std::unique_ptr<Btn> playBtn;
    std::unique_ptr<Btn> exitBtn;

    TTF_Font* font;
    SDL_Texture* carTexture;
    SDL_Rect carRect;

public:
    MenuScene(Renderer* rend, SceneMgr* mgr, std::weak_ptr<IGame> logic, InputHandler* input);
    ~MenuScene() override;

    void update(float dt) override;
    void render() override;
    void handleEvent(SDL_Event& e) override;
    std::string getName() const override { return "Menu"; }

    void onEnter() override;
    void onExit() override;
};