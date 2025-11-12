#include "GameScene.h"

GameScene::GameScene(Renderer* rend, SceneMgr* mgr, GameLogic* logic, InputHandler* input)
    : renderer(rend), sceneMgr(mgr), gameLogic(logic), inputHandler(input) {
}

void GameScene::onEnter() {

    playerRenderer = std::make_unique<PlayerRenderer>();

    // game state winitialized by MenuScene calling gameLogic->startGame() if you are looking for it 
    SDL_Log("GameScene: Initialized");
}

void GameScene::onExit() {
    // clean up rendering components
    playerRenderer.reset();

    SDL_Log("GameScene: Cleaned up");
}

void GameScene::handleEvent(SDL_Event& e) {
    
    inputHandler->update(e);

    // check for ESC to return to menu from the game 
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        sceneMgr->change("Menu");
    }
}

void GameScene::update(float dt) {
    // update input handler 
    inputHandler->updateKeyboard();

    // update game logic (player movement, game state,later it needs to have the scores, etc...)
    gameLogic->update(dt, *inputHandler);
}

void GameScene::render() {
    SDL_Renderer* sdlRend = renderer->getSDLRenderer();

    // simple dark background  -> working on the background 
    renderer->clear(20, 20, 30);

    // render player if exists 
    const Player* player = gameLogic->getPlayer();
    if (player && player->isActive()) {
        playerRenderer->render(sdlRend, *player);
    }

    // TODO: render game HUD (speed, lap time, score,fuel lives?)

    
    renderer->present();
}