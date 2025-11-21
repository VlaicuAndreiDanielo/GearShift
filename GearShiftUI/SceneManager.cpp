#include "SceneManager.h"
#include <SDL2/SDL.h>

SceneMgr::SceneMgr() : shouldChange(false) {}

void SceneMgr::add(const std::string& name, std::shared_ptr<IScene> scene) {
    if (!scene) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SceneManager: Cannot add null scene '%s'", name.c_str());
        return;
    }

    if (scenes.find(name) != scenes.end()) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "SceneManager: Scene '%s' already exists, replacing", name.c_str());
    }

    scenes[name] = scene;
    
    // Initialize first scene automatically
    if (!current) {
        current = scene;
        current->onEnter();
        SDL_Log("SceneManager: Initial scene '%s' loaded", name.c_str());
    }
}

void SceneMgr::change(const std::string& name) {
    if (scenes.find(name) == scenes.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SceneManager: Scene '%s' not found", name.c_str());
        return;
    }

    if (current && current->getName() == name) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "SceneManager: Already on scene '%s'", name.c_str());
        return;
    }

    nextName = name;
    shouldChange = true;
}

void SceneMgr::performSceneTransition() {
    if (!shouldChange || scenes.find(nextName) == scenes.end()) {
        return;
    }

    // Exit current scene
    if (current) {
        SDL_Log("SceneManager: Exiting scene '%s'", current->getName().c_str());
        current->onExit();
    }

    // Enter new scene
    current = scenes[nextName];
    SDL_Log("SceneManager: Entering scene '%s'", current->getName().c_str());
    current->onEnter();

    shouldChange = false;
}

void SceneMgr::update(float dt) {
    // Handle pending scene transition
    performSceneTransition();

    // Update current scene
    if (current) {
        current->update(dt);
    }
}

void SceneMgr::render() {
    if (current) {
        current->render();
    }
}

void SceneMgr::handleEvent(SDL_Event& e) {
    if (current) {
        current->handleEvent(e);
    }
}

bool SceneMgr::has(const std::string& name) const {
    return scenes.find(name) != scenes.end();
}