#pragma once
#include <SDL2/SDL.h>
#include "IPlayer.h"
#include <memory>

class PlayerRenderer {
private:
    SDL_Color color;

public:
    PlayerRenderer();

    void render(SDL_Renderer* rend, const std::shared_ptr<IPlayer> player);

    void setColor(Uint8 r, Uint8 g, Uint8 b);
};