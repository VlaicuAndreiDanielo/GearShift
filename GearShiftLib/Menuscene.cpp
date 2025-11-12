#include "MenuScene.h"


MenuScene::MenuScene(Renderer* rend, SceneMgr* mgr, GameLogic* logic, InputHandler* input)
    : renderer(rend), sceneMgr(mgr), gameLogic(logic), inputHandler(input),
    font(nullptr), carTexture(nullptr) {
}

MenuScene::~MenuScene() {
    if (carTexture) SDL_DestroyTexture(carTexture);
    if (font) TTF_CloseFont(font);
}

void MenuScene::onEnter() {
    SDL_Renderer* sdlRend = renderer->getSDLRenderer();
    int w = renderer->getWidth();
    int h = renderer->getHeight();

    // create effects
    crt = std::make_unique<CRT>(sdlRend, w, h);
    wave = std::make_unique<Wave>(w, h, 32);

    // load font TODO: change from the windows to a font downloaded and put into the project i dont know what will happen if the font 
    //is missing in both of them TODO:save it in the project when you have time 
    font = TTF_OpenFont("arial.ttf", 32);
    if (!font) {
        font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 32);
    }

    // create play button
    playBtn = std::make_unique<Btn>(sdlRend, font, "PLAY",
        w / 2 - 120, h / 2 + 200, 240, 70);

    // set button callback to start game
    playBtn->setClick([this]() {
        gameLogic->startGame();  
        sceneMgr->change("Game");
        });

    // load car texture -> we need to find another model or how we put things in menu screen cuz i dislike it 
    SDL_Surface* carSurf = nullptr;
    const char* paths[] = {
        "assets/images/car_menu.png",
        "../assets/images/car_menu.png",
        "../../assets/images/car_menu.png"
    };

    for (const char* path : paths) {
        carSurf = IMG_Load(path);
        if (carSurf) break;
    }

    if (carSurf) {
        carTexture = SDL_CreateTextureFromSurface(sdlRend, carSurf);
        SDL_FreeSurface(carSurf);
    }

    // position car sprite 
    carRect = { w / 2 - 200, h / 2 - 100, 400, 180 };

    SDL_Log("MenuScene: Initialized");
}

void MenuScene::onExit() {
    // clean up menu resources
    crt.reset();
    wave.reset();
    playBtn.reset();

    if (carTexture) {
        SDL_DestroyTexture(carTexture);
        carTexture = nullptr;
    }

    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    SDL_Log("MenuScene: Cleaned up");
}

void MenuScene::handleEvent(SDL_Event& e) {
    // update input handler
    inputHandler->update(e);

    // handle button events
    if (e.type == SDL_MOUSEMOTION) {
        playBtn->update(e.motion.x, e.motion.y);
    }
    else if (e.type == SDL_MOUSEBUTTONUP) {
        playBtn->handleClick(e.motion.x, e.motion.y);
    }
}

void MenuScene::update(float dt) {
    // update input handler (refresh keyboard state)
    inputHandler->updateKeyboard();

    // update game logic the fabric physics
    gameLogic->update(dt, *inputHandler);

    // apply mouse force for the effect 
    if (inputHandler->isMousePressed()) {
        gameLogic->applyMouseForce(
            inputHandler->getMouseX(),
            inputHandler->getMouseY(),
            true
        );
    }

    crt->update(dt);
}

void MenuScene::render() {
    SDL_Renderer* sdlRend = renderer->getSDLRenderer();

    // begin CRT rendering
    crt->begin(sdlRend);

    // dark background -> can be changed but i dont think it needs another collor or a static png immage cuz it will break the retro style
    SDL_SetRenderDrawColor(sdlRend, 15, 8, 8, 255);
    SDL_RenderClear(sdlRend);

    // render wave background
    wave->update(0.016f, gameLogic->getTime());
    wave->render(sdlRend, gameLogic->getFabric().getPts(),
        gameLogic->getFabric().getW(), gameLogic->getFabric().getH());

    // render car
    if (carTexture) {
        SDL_RenderCopy(sdlRend, carTexture, nullptr, &carRect);
    }
    else {
        SDL_SetRenderDrawColor(sdlRend, 255, 0, 0, 255);
        SDL_RenderFillRect(sdlRend, &carRect);
    }

    // render button
    playBtn->render(sdlRend);

    crt->end(sdlRend);
    renderer->present();
}