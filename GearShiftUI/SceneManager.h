#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include "IScene.h"

class SceneMgr {
private:
    std::unordered_map<std::string, std::shared_ptr<IScene>> scenes;
    std::shared_ptr<IScene> current;
    std::string nextName;
    bool shouldChange;

    // Helper method to safely transition between scenes
    void performSceneTransition();

public:
    SceneMgr();

    // Add a scene to the manager
    void add(const std::string& name, std::shared_ptr<IScene> scene);
    
    // Request a scene change (happens on next update)
    void change(const std::string& name);
    
    // Core loop methods
    void update(float dt);
    void render();
    void handleEvent(SDL_Event& e);

    // Getters
    std::shared_ptr<IScene> getCurrent() const { return current; }
    bool has(const std::string& name) const;
};