#pragma once
#include <unordered_map>
#include <memory>
#include <vector>

class CollisionManager {
public:
	class Collider;
	class Collision;
	static CollisionManager& getInstance();
	void update();
	void registerCollider(std::weak_ptr<Collider> collider);
	void unregisterCollider(Collider* collider);
	~CollisionManager() = default;

private:
	std::vector<std::weak_ptr<Collider>> colliderList;
};

using Collider = CollisionManager::Collider;
using Collision = CollisionManager::Collision;