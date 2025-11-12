#include "PlayerRenderer.h"

PlayerRenderer::PlayerRenderer() {
    color = { 50, 100, 255, 255 };  // blue TODO: make the actual player as a car 
}

void PlayerRenderer::render(SDL_Renderer* rend, const Player& player) {
    SDL_Rect rect = {
        (int)player.getX(),
        (int)player.getY(),
        player.getWidth(),
        player.getHeight()
    };

    // draw filled square
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &rect);

    // draw white border
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderDrawRect(rend, &rect);
}

void PlayerRenderer::setColor(Uint8 r, Uint8 g, Uint8 b) {
    color = { r, g, b, 255 };
}