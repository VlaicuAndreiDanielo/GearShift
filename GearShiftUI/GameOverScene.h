#pragma once
#include "IScene.h"
#include "Renderer.h"
#include "SceneManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

class GameOverScene : public IScene {
private:
    Renderer* renderer;
    SceneMgr* sceneMgr;

    float timeAlive;
    float autoReturnTime;
    int finalScore;

    TTF_Font* font = nullptr;

public:
    GameOverScene(Renderer* rend, SceneMgr* mgr);
    ~GameOverScene();

    void update(float dt) override;
    void render() override;
    void handleEvent(SDL_Event& e) override;

    std::string getName() const override { return "GameOver"; }
    void setFinalScore(int score) { finalScore = score; }

    void onEnter() override;
    void onExit() override;
};
