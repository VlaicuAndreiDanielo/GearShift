#pragma once
#include <memory>
#include <vector>

class CollisionManager : public std::enable_shared_from_this<CollisionManager> {
public:
	class Collider;
	class Collision;
	void update();
	void registerCollider(std::weak_ptr<Collider> collider);
	void unregisterCollider(Collider* collider);
	~CollisionManager() = default;

	template<typename T, typename... Args>
	std::shared_ptr<T> addCollider(std::shared_ptr<class GameObject> obj, Args&&... args) {
		static_assert(std::is_base_of_v<Collider, T>);
		std::shared_ptr<T> collider = std::make_shared<T>(shared_from_this(), std::forward<Args>(args)...);
		collider->attachToGameObject(obj);
		return collider;
	}

private:
	std::vector<std::weak_ptr<Collider>> colliderList;
};

using Collider = CollisionManager::Collider;
using Collision = CollisionManager::Collision;