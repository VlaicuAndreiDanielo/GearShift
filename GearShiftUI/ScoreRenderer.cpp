#include "ScoreRenderer.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include "IScoreManager.h"



ScoreRenderer::ScoreRenderer(SDL_Renderer* rend)
    : renderer(rend), texture(nullptr), cleanedUp(false)
{
    color = { 255, 255, 255, 255 };

    if (TTF_WasInit() == 0) {
        if (TTF_Init() == -1) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed: %s", TTF_GetError());
        }
    }
    font = TTF_OpenFont("assets/fonts/VipnagorgiallaBd.otf", 24);
    if (!font) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s", TTF_GetError());
    }

    updateTexture(0);
}

ScoreRenderer::~ScoreRenderer() {
    if (cleanedUp) {
        return; // Already cleaned up
    }
    
    cleanedUp = true;
    SDL_Log("ScoreRenderer: Cleaning up resources");
    
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    
    if (font) {
        SDL_Log("ScoreRenderer: Setting font pointer to null (avoiding TTF_CloseFont crash)");
        // Don't call TTF_CloseFont to avoid access violation
        // SDL will clean up TTF resources automatically at program exit
        font = nullptr;
    }
}

void ScoreRenderer::render(std::shared_ptr<IScoreManager> scoreManager) {
	updateTexture(scoreManager->getScore());
    if (texture && renderer) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}

void ScoreRenderer::updateTexture(int score) {
    if (!font || !renderer) return;

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    std::string text = "Score: " + std::to_string(score);
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) return;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = 1920 - rect.w - 20;    rect.y = 20;

    SDL_FreeSurface(surface);
}