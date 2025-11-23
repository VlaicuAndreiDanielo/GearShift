#include "GameOverScene.h"
#include <SDL2/SDL.h>

GameOverScene::GameOverScene(Renderer* rend, SceneMgr* mgr)
    : renderer(rend), sceneMgr(mgr), timeAlive(0.0f), autoReturnTime(3.0f) {
	font = TTF_OpenFont("assets/fonts/VipnagorgiallaBd.otf", 48);
    if (!font) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot load font: %s", TTF_GetError());
    }
}

GameOverScene::~GameOverScene() {
    if (font) TTF_CloseFont(font);
}

void GameOverScene::onEnter() {
    timeAlive = 0;
    SDL_Log("Entered GameOver Scene");
}

void GameOverScene::onExit() {
    SDL_Log("Exited GameOver Scene");
}

void GameOverScene::update(float dt) {
    timeAlive += dt;
    if (timeAlive >= autoReturnTime) {
        if (sceneMgr) sceneMgr->change("Menu");
    }
}

void GameOverScene::render() {
    if (!renderer) return;

    SDL_Renderer* sdl = renderer->getSDLRenderer();

    renderer->clear(120, 0, 0);

    // chenar exterior
    SDL_Rect box{ 600, 400, 720, 150 };
    SDL_SetRenderDrawColor(sdl, 255, 255, 255, 255);
    SDL_RenderDrawRect(sdl, &box);

    // interior semi-transparent
    SDL_Rect inner{ 610, 410, 700, 130 };
    SDL_SetRenderDrawColor(sdl, 255, 255, 255, 80);
    SDL_RenderFillRect(sdl, &inner);

    if (font) {
        SDL_Color white{ 255, 255, 255, 255 };

        SDL_Surface* surf = TTF_RenderText_Blended(font, "GAME OVER", white);
        if (!surf) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render text failed: %s", TTF_GetError());
        }
        else {

            SDL_Texture* tex = SDL_CreateTextureFromSurface(sdl, surf);
            if (!tex) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "CreateTexture failed: %s", SDL_GetError());
            }
            else {

                int w, h;
                SDL_QueryTexture(tex, NULL, NULL, &w, &h);

                SDL_Rect dst{
                    600 + (720 - w) / 2,
                    400 + (150 - h) / 2, 
                    w, h
                };

                SDL_RenderCopy(sdl, tex, NULL, &dst);
                SDL_DestroyTexture(tex);
            }

            SDL_FreeSurface(surf);
        }
        if (font) {
            SDL_Color yellow{ 255, 230, 0, 255 };

            std::string scoreText = "Final Score: " + std::to_string(finalScore);

            SDL_Surface* surf2 = TTF_RenderText_Blended(font, scoreText.c_str(), yellow);
            if (surf2) {
                SDL_Texture* tex2 = SDL_CreateTextureFromSurface(sdl, surf2);

                int w2, h2;
                SDL_QueryTexture(tex2, NULL, NULL, &w2, &h2);

                SDL_Rect dst2{600 + (720 - w2) / 2, 400 + 150 + 10, w2, h2};

                SDL_RenderCopy(sdl, tex2, NULL, &dst2);

                SDL_DestroyTexture(tex2);
                SDL_FreeSurface(surf2);
            }
        }
    }
    else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font is null in render()");
    }

    renderer->present();
}


void GameOverScene::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_ESCAPE) {
            if (sceneMgr) sceneMgr->change("Menu");
        }
    }
}
