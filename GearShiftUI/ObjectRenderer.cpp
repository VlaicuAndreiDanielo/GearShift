#include "ObjectRenderer.h"
#include "IGameObject.h"
#include "SpriteManager.h"
#include "SpriteMapper.h"
#include <memory>
#include <SDL2/SDL_image.h>
#include <iostream>

ObjectRenderer::ObjectRenderer(SDL_Renderer* renderer) : renderer{ renderer }, spriteManager{ renderer }
{
	color = { 0, 0, 0, 0 };  // black
}

ObjectRenderer::~ObjectRenderer() {
	
}

void ObjectRenderer::render(const std::shared_ptr<IGameObject> object) {
	SDL_Rect rect = {
		static_cast<int>(object->getX()),
		static_cast<int>(object->getY()),
		object->getWidth(),
		object->getHeight()
	};

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); //black outline
	SDL_RenderDrawRect(renderer, &rect);

	std::string path = SpriteMapper::getSpritePath(object->getSprite());
	SDL_Texture* texture = spriteManager.getTexture(path);

	double angle = object->getRotation();
	spriteManager.drawTextureOverRect(rect, texture, angle);
}

void ObjectRenderer::setColor(Uint8 r, Uint8 g, Uint8 b) {
	color = { r, g, b, 255 };
}
