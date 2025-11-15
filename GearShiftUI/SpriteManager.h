#pragma once
#include <memory>
#include <SDL2/SDL_image.h>
#include <iostream>

class SpriteManager
{
private:

public:
	void drawTextureOverRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Texture* texture);
};