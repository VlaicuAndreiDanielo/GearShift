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
	master->collider = shared_from_this();
	this->masterObject = master;
	if (auto managerSharedPtr = this->manager.lock()) {
		managerSharedPtr->registerCollider(shared_from_this());
	}
}
std::shared_ptr<GameObject> CollisionManager::Collider::getMasterObject() const
{
	return masterObject.lock();
}


void CollisionManager::Collider::notifyCollision(std::shared_ptr<Collider> other) {
	if (auto masterShared = this->masterObject.lock()) {
		masterShared->onCollision(other);
	}
}
