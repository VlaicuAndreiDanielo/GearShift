#include "FuelTimer.h"
#include <SDL2/SDL_image.h>

FuelTimer::FuelTimer(float duration, int x, int y, int w, int h, SDL_Renderer* renderer)
    : maxTime(duration), currentTime(duration)
{
    barRect = { x, y, w, h };
    bgColor = { 50, 50, 50, 255 };
    fillColor = { 200, 40, 40, 255 };

    squareSize = barRect.h;
    spacing = 10;
    fuelTexture = IMG_LoadTexture(renderer, fuelSpritePath);
    if (!fuelTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture '%s': %s", fuelSpritePath, IMG_GetError());
    }
}

FuelTimer::~FuelTimer() {
    if (fuelTexture) SDL_DestroyTexture(fuelTexture);
}

void FuelTimer::update(float dt) {
    if (currentTime > 0) {
        currentTime -= dt;
        if (currentTime < 0) currentTime = 0;
    }
}

bool FuelTimer::isFinished() const {
    return currentTime <= 0;
}

void FuelTimer::reset() {
    currentTime = maxTime;
}

void FuelTimer::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &barRect);

    float ratio = currentTime / maxTime;
    int fillWidth = static_cast<int>(barRect.w * ratio);

    SDL_Rect fillRect = { barRect.x, barRect.y, fillWidth, barRect.h };
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &barRect);

    spriteSquare.x = barRect.x + barRect.w + spacing;
    spriteSquare.y = barRect.y;
    spriteSquare.w = squareSize;
    spriteSquare.h = squareSize;

    if (fuelTexture) {
        SDL_RenderCopy(renderer, fuelTexture, nullptr, &spriteSquare);
    }
    else {
        std::cout << "Error loading Fuel Image!";
    }
}
