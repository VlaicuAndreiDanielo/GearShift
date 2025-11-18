#pragma once
#include <SDL2/SDL.h>
#include "IGameObject.h"
#include "SpriteManager.h"
#include <memory>

class ObjectRenderer {
public:
    ObjectRenderer(SDL_Renderer* renderer);
    ~ObjectRenderer();

    void render(const std::shared_ptr<IGameObject> object);

    void setColor(Uint8 r, Uint8 g, Uint8 b);

private:
    SDL_Color color;
    SpriteManager spriteManager;
    SDL_Renderer* renderer;
};
