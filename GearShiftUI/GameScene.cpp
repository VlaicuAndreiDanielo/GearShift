#include "GameScene.h"

GameScene::GameScene(Renderer* rend, SceneMgr* mgr, std::weak_ptr<IGame> logic, InputHandler* input)
    : renderer(rend), sceneMgr(mgr), game(logic), inputHandler(input) {
}

void GameScene::onEnter() {
    if (!renderer || game.expired()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameScene: Missing renderer or gameLogic");
        return;
    }

    objectRenderer = std::make_unique<ObjectRenderer>(renderer->getSDLRenderer());
    fuelTimer = std::make_unique<FuelTimer>(10.0f, 850, 20, 300, 20, renderer->getSDLRenderer());
    scoreManager = std::make_unique<ScoreManager>(renderer->getSDLRenderer());

    SDL_Log("GameScene: Entered and initialized rendering components");
}

void GameScene::onExit() {
    objectRenderer.reset();

    if (auto gameShared = game.lock()) {
        gameShared->endGame();
    }

    SDL_Log("GameScene: Exited and cleaned up rendering components");
}

void GameScene::handleEvent(SDL_Event& e) {
    if (inputHandler) {
        inputHandler->update(e);
    }

    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        SDL_Log("GameScene: ESC ? Back to Menu");
        if (sceneMgr) sceneMgr->change("Menu");
    }
}

void GameScene::update(float dt) {
    if (inputHandler) {
        inputHandler->updateKeyboard();

        if (auto gameShared = game.lock()) {
            gameShared->update(dt, *inputHandler);
        }
    }

    if (scoreManager) scoreManager->update(dt);
    if (fuelTimer) fuelTimer->update(dt);

    if (fuelTimer && fuelTimer->isFinished()) {
        if (auto gameShared = game.lock()) {
            gameShared->onFuelEmpty();
        }
    }
    if (auto gameShared = game.lock()) {
        if (gameShared->getState() == GameState::GameOver) {
            SDL_Log("GameScene: Switching to GameOver scene");
            sceneMgr->change("GameOver");
            return;
        }
    }
}

void GameScene::render() {
    if (!renderer) return;

    SDL_Renderer* sdlRend = renderer->getSDLRenderer();

    renderer->clear(20, 20, 30);

    if (auto gameShared = game.lock()) {
        auto objs = gameShared->getGameObjects();
        for (const auto& obj : objs) {
            if (obj && obj->isActive() && objectRenderer) {
                objectRenderer->render(obj);
            }
        }
    }

    if (scoreManager) scoreManager->render();
    if (fuelTimer) fuelTimer->render(sdlRend);

    renderer->present();
}

bool GameScene::isFuelFinished() const {
    return fuelTimer ? fuelTimer->isFinished() : false;
}
