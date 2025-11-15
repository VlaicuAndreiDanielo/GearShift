#pragma once
#include "SpriteManager.h"
#include <memory>
#include <SDL2/SDL_image.h>
#include <iostream>

void SpriteManager::drawTextureOverRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Texture* texture) {
    if (!texture) return;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
