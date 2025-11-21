#pragma once
#include <string>
#include <SDL2/SDL.h>

class IScene {
public:
    virtual ~IScene() = default;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual void handleEvent(SDL_Event& e) = 0;
    virtual std::string getName() const = 0;

    // Lifecycle methods - called when scene becomes active/inactive
    // Implement to initialize/load resources when entering
    virtual void onEnter() = 0;

    // Implement to cleanup/save state when exiting
    virtual void onExit() = 0;
};
