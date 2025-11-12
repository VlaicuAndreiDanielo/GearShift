#include "SceneManager.h"

SceneMgr::SceneMgr() : shouldChange(false) {}

void SceneMgr::add(const std::string& name, std::shared_ptr<Scene> scene) {
    scenes[name] = scene;
    if (!current) {
        current = scene;
        current->onEnter();  // initialize first scene
    }
}

void SceneMgr::change(const std::string& name) {
    nextName = name;
    shouldChange = true;
}

void SceneMgr::update(float dt) {
    // handle scene transition
    if (shouldChange && scenes.find(nextName) != scenes.end()) {
        if (current) {
            current->onExit();  // cleanup old scene
        }

        current = scenes[nextName];
        current->onEnter();  //initialize new scene

        shouldChange = false;
    }

    // update current scene
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