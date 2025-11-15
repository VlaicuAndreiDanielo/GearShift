#pragma once
#include <memory>
#include "CollisionManager.h"
#include "Transform.h"

class GameObject : public std::enable_shared_from_this<GameObject> {
public:
	GameObject() = default;
	GameObject(float startX, float startY);
	virtual ~GameObject() = default;
	Transform& getTransform();

	template<typename T, typename... Args>
	std::shared_ptr<T> addCollider(Args&&... args) {
		static_assert(std::is_base_of_v<CollisionManager::Collider, T>);
		CollisionManager::Collider collider = std::make_shared<T>(std::forward<Args>(args)...);
		collider->attachToGameObject(shared_from_this());
		return collider;
	}
protected:
	Transform transform;
private:
};