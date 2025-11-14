#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include "Renderer.h"
#include "SceneManager.h"
#include "InputHandler.h"
#include "GameLogic.h"

class Application {
private:
    static constexpr int WINDOW_WIDTH = 1920;
    static constexpr int WINDOW_HEIGHT = 1080;
    static constexpr float MAX_DELTA_TIME = 0.1f;

    // Core components
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<GameLogic> gameLogic;
    std::unique_ptr<InputHandler> inputHandler;
    SceneMgr sceneMgr;

    // Main loop state
 bool running;
    Uint32 lastTime;

    // Initialization methods
    void initializeComponents();
    void initializeScenes();

    // Main loop methods
    void handleEvents();
    void update(float dt);
    void render();

public:
    Application();
    ~Application();

  // Delete copy semantics
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    // Main entry point
    void run();
};
