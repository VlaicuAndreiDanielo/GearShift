#pragma once
#include "SpriteManager.h"
#include <memory>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>

void SpriteManager::drawTextureOverRect(SDL_Rect rect, SDL_Texture* texture) {
	if (!texture) return;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void SpriteManager::drawTextureOverRect(const SDL_Rect& rect, SDL_Texture* texture, double angleRadians = 0)
{
	if (!texture) return;

	double angleDegrees = angleRadians * (180.0 / M_PI);

	SDL_RenderCopyEx(renderer,
		texture,
		nullptr,   // use whole texture
		&rect,
		angleDegrees,
		nullptr,   // rotation center (nullptr = center of dest rect)
		SDL_FLIP_NONE);
}

SpriteManager::~SpriteManager() {
	for (auto& pair : textureCache) {
		if (pair.second) {
			SDL_DestroyTexture(pair.second);
		}
	}
	textureCache.clear();
}

SDL_Texture* SpriteManager::getTexture(const std::string& path) {
	if (path.empty()) return nullptr;

	auto it = textureCache.find(path);
	if (it != textureCache.end())
		return it->second;

	SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
	if (!tex) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Failed to load texture '%s': %s",
			path.c_str(), IMG_GetError());
		return nullptr;
	}

	textureCache[path] = tex;
	return tex;
}

SpriteManager::SpriteManager(SDL_Renderer* renderer) : renderer{ renderer }
{
}
