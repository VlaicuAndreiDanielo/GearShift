#pragma once
#include <memory>
#include "CollisionManager.h"
#include "Transform.h"

/// <summary>
/// Always use shared_ptr to manage GameObject instances.
/// </summary>
class GameObject : public std::enable_shared_from_this<GameObject> {
public:
	GameObject() = default;
	GameObject(float startX, float startY);
	virtual ~GameObject() = default;
	Transform& getTransform();

	template<typename T, typename... Args>
	std::shared_ptr<T> addCollider(Args&&... args) {
		static_assert(std::is_base_of_v<Collider, T>);
		std::shared_ptr<T> collider = std::make_shared<T>(std::forward<Args>(args)...);
		collider->attachToGameObject(shared_from_this());
		return collider;
	}
protected:
	Transform transform;
private:
};