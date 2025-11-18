#include "GameObjectAdapter.h"
#include "GameObject.h"

float GameObjectAdapter::getX() const
{
	return this->object->getTransform().getX();
}

float GameObjectAdapter::getY() const
{
	return this->object->getTransform().getY();
}

float GameObjectAdapter::getRotation() const
{
	return this->object->getTransform().getRotation();
}

float GameObjectAdapter::getWidth() const
{
	return this->object->getWidth();
}

float GameObjectAdapter::getHeight() const
{
	return this->object->getHeight();
}

SpriteType GameObjectAdapter::getSprite() const
{
	return this->object->getSprite();
}

bool GameObjectAdapter::isActive() const
{
	return this->object->isActive();
}

GameObjectAdapter::GameObjectAdapter(std::shared_ptr<GameObject> obj) : object(obj)
{

}
