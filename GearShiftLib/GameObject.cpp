#include "GameObject.h"

GameObject::GameObject(float startX = 0, float startY = 0, float width = 0, float height = 0, bool active = true) : transform({ startX, startY }), width{ width }, height{ height }, active{ active } {}

Transform& GameObject::getTransform() {
	return transform;
}

ObjectType GameObject::getType() const { return ObjectType::NONE; }

SpriteType GameObject::getSprite() const { return this->sprite; }

void GameObject::setSprite(SpriteType sprite)
{
	this->sprite = sprite;
}

void GameObject::handleInput(const IInputState& input) {}

void GameObject::setActive(bool isActive) { active = isActive; }

bool GameObject::isActive() const { return active; }

float GameObject::getWidth() const { return width; }

float GameObject::getHeight() const { return height; }

void GameObject::setSize(float w, float h) { width = w; height = h; }
