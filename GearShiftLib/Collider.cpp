#include "Collider.h"
#include <memory>

CollisionManager& CollisionManager::Collider::manager = CollisionManager::getInstance();

CollisionManager::Collider::~Collider()
{
	manager.unregisterCollider(this);
}
void CollisionManager::Collider::attachToGameObject(std::shared_ptr<GameObject> master)
{
	this->masterObject = master;
	this->manager.registerCollider(shared_from_this());
}
std::shared_ptr<GameObject> CollisionManager::Collider::getMasterObject() const
{
	return masterObject.lock();
}

void CollisionManager::Collider::setOnCollisionCallback(std::function<void(std::shared_ptr<Collider>)> callback) {
	onCollision = std::move(callback);
}

void CollisionManager::Collider::notifyCollision(std::shared_ptr<Collider> other) {
	if (onCollision) {
		onCollision(other);
	}
}
