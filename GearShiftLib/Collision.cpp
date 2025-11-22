#include "Collision.h"
#include "Collider.h"

CollisionManager::Collision::Collision(std::shared_ptr<const Collider> a, std::shared_ptr<const Collider> b)
	: colliderA{ a }, colliderB{ b } {
}

std::shared_ptr<const Collider> CollisionManager::Collision::getColliderA() const { return colliderA; }

std::shared_ptr<const Collider> CollisionManager::Collision::getColliderB() const { return colliderB; }

void CollisionManager::Collision::setCollisionNormal(const Vec2& normal) { collisionNormal = normal; }

Vec2 CollisionManager::Collision::getCollisionNormal() const { return collisionNormal; }

void CollisionManager::Collision::setPenetrationDepth(float depth) { penetrationDepth = depth; }

float CollisionManager::Collision::getPenetrationDepth() const { return penetrationDepth; }

void CollisionManager::Collision::resolve() const
{
	if (colliderA->isTrigger() || colliderB->isTrigger()) return; //If trigger, do not resolve collision 
	// Simple resolution: move objects apart along collision normal by penetration depth
	auto objA = colliderA->getMasterObject();
	auto objB = colliderB->getMasterObject();
	if (objA && objB) {
		Transform& transformA = objA->getWorldTransform();
		Transform& transformB = objB->getWorldTransform();
		if (transformA.getFixed() && transformB.getFixed()) {
			// Both objects are fixed; do nothing
			return;
		}
		else if (transformA.getFixed()) {
			// Only A is fixed; move B fully
			Vec2 correction = collisionNormal * penetrationDepth;
			transformB.setPosition(transformB.getPos() + correction);
			return;
		}
		else if (transformB.getFixed()) {
			// Only B is fixed; move A fully
			Vec2 correction = collisionNormal * penetrationDepth;
			transformA.setPosition(transformA.getPos() - correction);
			return;
		}
		Vec2 correction = collisionNormal * (penetrationDepth * 0.5f);
		transformA.setPosition(transformA.getPos() - correction);
		transformB.setPosition(transformB.getPos() + correction);
	}
}
