#include "CollisionManager.h"

void CollisionManager::detectCollisions()
{
}

void CollisionManager::registerCollider(std::weak_ptr<Collider> collider)
{
	colliderList.push_back(collider);
}

void CollisionManager::unregisterCollider(Collider* collider)
{
	colliderList.erase(
		std::remove_if(
			colliderList.begin(),
			colliderList.end(),
			[collider](const std::weak_ptr<Collider>& ptr) {
				auto sharedPtr = ptr.lock();
				return !sharedPtr || sharedPtr.get() == collider;
			}
		),
		colliderList.end()
	);
}


CollisionManager& CollisionManager::getInstance() {
	static CollisionManager instance;
	return instance;
}