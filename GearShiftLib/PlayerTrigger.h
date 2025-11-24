#pragma once
#include "GameObject.h"

class PlayerTrigger : public GameObject {
public:
	static std::shared_ptr<PlayerTrigger> create(std::weak_ptr<CollisionManager> collisionManager, float startX, float startY, float width, float height);
protected:
	PlayerTrigger(float startX, float startY, float width, float height);
	void onCollision(std::shared_ptr<CollisionManager::Collider> other) override;
};