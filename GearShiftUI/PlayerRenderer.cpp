#include "PlayerRenderer.h"
#include "IPlayer.h"
#include "SpriteManager.h"
#include <memory>
#include <SDL2/SDL_image.h>
#include <iostream>

PlayerRenderer::PlayerRenderer(SDL_Renderer* renderer) {
    color = { 0, 0, 0, 0 };  // black

    //change player model here
    const char* filePath = "assets/images/PlayerCar.png";

    playerTexture = IMG_LoadTexture(renderer, filePath);
    if (!playerTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture '%s': %s", filePath, IMG_GetError());
    } else {
        SDL_Log("Texture '%s' loaded successfully.", filePath);
    }
}

PlayerRenderer::~PlayerRenderer() {
    if (playerTexture) SDL_DestroyTexture(playerTexture);
}

void PlayerRenderer::render(SDL_Renderer* rend, const std::shared_ptr<IPlayer> player) {
    SDL_Rect rect = {
        static_cast<int>(player->getX()),
        static_cast<int>(player->getY()),
        player->getWidth(),
        player->getHeight()
    };

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &rect);

    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0); //black outline
    SDL_RenderDrawRect(rend, &rect);

    sprite.drawTextureOverRect(rend, rect, playerTexture);
}

void PlayerRenderer::setColor(Uint8 r, Uint8 g, Uint8 b) {
    color = { r, g, b, 255 };
}
