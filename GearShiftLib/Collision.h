#pragma once
#include "CollisionManager.h"
#include "Vec2.h"

class CollisionManager::Collision {
	public:
	Collision(std::shared_ptr<const Collider> a, std::shared_ptr<const Collider> b);
	~Collision() = default;
	std::shared_ptr<const Collider> getColliderA() const;
	std::shared_ptr<const Collider> getColliderB() const;
	void setCollisionNormal(const Vec2& normal);
	Vec2 getCollisionNormal() const;
	void setPenetrationDepth(float depth);
	float getPenetrationDepth() const;
	void resolve() const;
private:
	std::shared_ptr<const Collider> colliderA;
	std::shared_ptr<const Collider> colliderB;
	Vec2 collisionNormal = Vec2{};
	float penetrationDepth = 0.0f;
};