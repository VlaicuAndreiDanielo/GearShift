#include "Collider.h"
#include <memory>

CollisionManager& CollisionManager::Collider::manager = CollisionManager::getInstance();

CollisionManager::Collider::~Collider()
{
	manager.unregisterCollider(this);
}
void CollisionManager::Collider::attachToObject(std::shared_ptr<GameObject> master)
{
	this->masterObject = master;
	this->manager.registerCollider(shared_from_this());
}
std::shared_ptr<GameObject> CollisionManager::Collider::getMasterObject() const
{
	return masterObject.lock();
}