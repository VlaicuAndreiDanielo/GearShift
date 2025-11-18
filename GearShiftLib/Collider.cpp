#include "Collider.h"
#include <memory>

CollisionManager::Collider::Collider(std::weak_ptr<CollisionManager> manager) : manager{ manager } {}

CollisionManager::Collider::~Collider()
{
	if (auto managerSharedPtr = this->manager.lock()) {
		managerSharedPtr->unregisterCollider(this);
	}
}
void CollisionManager::Collider::attachToGameObject(std::shared_ptr<GameObject> master)
{
	this->masterObject = master;
	if (auto managerSharedPtr = this->manager.lock()) {
		managerSharedPtr->registerCollider(shared_from_this());
	}
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
