#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>

class Scene {
public:
    virtual ~Scene() = default;
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

class SceneMgr {
private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> current;
    std::string nextName;
    bool shouldChange;

    // Helper method to safely transition between scenes
    void performSceneTransition();

public:
    SceneMgr();

    // Add a scene to the manager
    void add(const std::string& name, std::shared_ptr<Scene> scene);
    
    // Request a scene change (happens on next update)
    void change(const std::string& name);
    
    // Core loop methods
    void update(float dt);
    void render();
    void handleEvent(SDL_Event& e);

    // Getters
    std::shared_ptr<Scene> getCurrent() const { return current; }
    bool has(const std::string& name) const;
};