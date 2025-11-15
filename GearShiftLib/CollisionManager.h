#pragma once
#include <unordered_map>
#include <memory>
#include <vector>

class CollisionManager {
public:
	class Collider;
	class Collision;
	static CollisionManager& getInstance();
	void detectCollisions();
	void registerCollider(std::weak_ptr<Collider> collider);
	void unregisterCollider(Collider* collider);
	~CollisionManager() = default;

private:
	std::unordered_map<int, std::vector<std::weak_ptr<Collider>>> collisionSpace;
	std::vector<std::weak_ptr<Collider>> colliderList;
};