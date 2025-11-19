#include "CollisionManager.h"
#include "Collider.h"
#include "Collision.h"

void CollisionManager::update()
{
	// Clean up expired colliders
	colliderList.erase(
		std::remove_if(
			colliderList.begin(),
			colliderList.end(),
			[](const std::weak_ptr<Collider>& ptr) { return ptr.expired(); }
		),
		colliderList.end()
	);
	// Check for collisions
	for (size_t i = 0; i < colliderList.size(); ++i) {
		auto colliderA = colliderList[i].lock();
		if (!colliderA) continue;
		for (size_t j = i + 1; j < colliderList.size(); ++j) {
			auto colliderB = colliderList[j].lock();
			if (!colliderB) continue;
			if (colliderA->getMasterObject()->getWorldTransform().getFixed() && colliderB->getMasterObject()->getWorldTransform().getFixed()) continue;
			auto collisionOpt = colliderA->checkCollisionWith(*colliderB);
			if (collisionOpt) {
				Collision& collision = *collisionOpt;
				collision.resolve();
				colliderA->notifyCollision(colliderB);
				colliderB->notifyCollision(colliderA);
			}
		}
	}
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


