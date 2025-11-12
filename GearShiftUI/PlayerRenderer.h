#pragma once
#include <SDL2/SDL.h>
#include "../GearShiftLib/Player.h"

class PlayerRenderer {
private:
    SDL_Color color;

public:
    PlayerRenderer();

    void render(SDL_Renderer* rend, const Player& player);

    void setColor(Uint8 r, Uint8 g, Uint8 b);
};