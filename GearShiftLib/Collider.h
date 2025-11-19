#pragma once
#include <functional>
#include <optional>
#include "CollisionManager.h"
#include "Collision.h"
#include "GameObject.h"

/// <summary>
/// Always use shared_ptr to manage Collider instances.
/// </summary>
class CollisionManager::Collider : public std::enable_shared_from_this<Collider> {
public:
	Collider(std::weak_ptr<CollisionManager> manager);
	virtual ~Collider();
	std::shared_ptr<GameObject> getMasterObject() const;
	void notifyCollision(std::shared_ptr<Collider> other);
	virtual std::optional<Collision> checkCollisionWith(const Collider& other) const = 0;
	virtual std::optional<Collision> checkCollisionWith(const class BoxCollider& other) const = 0;

protected:
	friend class CollisionManager;
	void attachToGameObject(std::shared_ptr<GameObject> master);
private:
	std::weak_ptr<CollisionManager> manager;
	std::weak_ptr<GameObject> masterObject;
};