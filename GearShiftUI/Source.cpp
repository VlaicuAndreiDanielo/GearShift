#define SDL_MAIN_HANDLED
#include "Renderer.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "InputHandler.h"
#include "GameLogic.h"
#include <memory>

extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#include <SDL2/SDL.h>


int main(int argc, char* argv[]) {
    const int W = 1920;
    const int H = 1080;

    // creates renderer the presentation layer (UI)
    auto renderer = std::make_unique<Renderer>(W, H);

    // creates game logic the core logic layer (from lib) - SHARED!!!
    auto gameLogic = std::make_unique<GameLogic>(W, H);

    // create input handler the presentation layer (UI) - SHARED!!!
    auto inputHandler = std::make_unique<InputHandler>();

    // create scene manager
    SceneMgr sceneMgr;

    // create scenes ->pass shared resources
    auto menuScene = std::make_shared<MenuScene>(
        renderer.get(), &sceneMgr, gameLogic.get(), inputHandler.get()
    );
    auto gameScene = std::make_shared<GameScene>(
        renderer.get(), &sceneMgr, gameLogic.get(), inputHandler.get()
    );

    // add scenes to manager 
    sceneMgr.add("Menu", menuScene);
    sceneMgr.add("Game", gameScene);

    // start with menu scene 
    sceneMgr.change("Menu");

    // main loop
    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        // handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F11) {
                // TODO: Toggle fullscreen to see the logs 
            }

            // forward events to current scene
            sceneMgr.handleEvent(event);
        }

        // calculate delta time 
        Uint32 currentTime = SDL_GetTicks();
        float dt = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // limit delta time to prevent huge jumps -> aparently its a practice when something goes wrong 
        if (dt > 0.1f) dt = 0.1f;

        // update current scene
        sceneMgr.update(dt);

        // render current scene
        sceneMgr.render();
    }

    return 0;
}