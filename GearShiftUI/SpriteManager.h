#pragma once
#include <memory>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unordered_map>

class SpriteManager
{
public:
	void drawTextureOverRect(SDL_Rect rect, SDL_Texture* texture);
	void drawTextureOverRect(const SDL_Rect& rect, SDL_Texture* texture, double angleRadians);
	SDL_Texture* getTexture(const std::string& path);
	SpriteManager(SDL_Renderer* renderer);
	~SpriteManager();
private:
	std::unordered_map<std::string, SDL_Texture*> textureCache;
	SDL_Renderer* renderer;
};