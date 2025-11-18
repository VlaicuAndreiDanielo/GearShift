#pragma once
#include "IGameObject.h"
#include <memory>


class GameObjectAdapter : public IGameObject {
public:
	float getX() const override;
	float getY() const override;
	float getWidth() const override;
	float getHeight() const override;
	float getRotation() const override;
	SpriteType getSprite() const override;
	bool isActive() const override;
	GameObjectAdapter(std::shared_ptr<class GameObject> obj);


private:
	std::shared_ptr<class GameObject> object;



};