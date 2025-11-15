#pragma once
#include "CollisionManager.h"
#include "GameObject.h"

/// <summary>
/// Always use shared_ptr to manage Collider instances.
/// </summary>
class CollisionManager::Collider : public std::enable_shared_from_this<Collider> {
public:
	virtual CollisionManager::Collision checkCollision(const Collider& other) const = 0;
	std::shared_ptr<GameObject> getMasterObject() const;
	Collider() = default;
	virtual ~Collider();

protected:
	friend class GameObject;
	void attachToObject(std::shared_ptr<GameObject> master);
private:
	static CollisionManager& manager;
	std::weak_ptr<GameObject> masterObject;
};