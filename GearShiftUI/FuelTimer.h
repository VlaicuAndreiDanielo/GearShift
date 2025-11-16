#pragma once
#include <SDL2/SDL.h>
#include "SpriteManager.h"

class FuelTimer : public SpriteManager {
private:
    float maxTime;
    float currentTime;
    SDL_Rect barRect;

    SDL_Color bgColor;
    SDL_Color fillColor;

    int squareSize;
    int spacing;
    SDL_Rect spriteSquare;

    const char* fuelSpritePath = "assets/images/FuelCanister.png";
    SDL_Texture* fuelTexture = nullptr;

public:
    FuelTimer(float duration, int x, int y, int w, int h, SDL_Renderer* renderer);

    ~FuelTimer();

    void update(float dt);
    void reset();
    bool isFinished() const;

    void render(SDL_Renderer* renderer);
};
