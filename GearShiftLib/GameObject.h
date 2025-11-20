#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "CollisionManager.h"
#include "Transform.h"
#include "ObjectType.h"
#include "SpriteType.h"
#include "IInputState.h"

/// <summary>
/// Always use shared_ptr to manage GameObject instances.
/// </summary>
class GameObject : public std::enable_shared_from_this<GameObject> {
public:
	GameObject() = default;
	GameObject(float startX, float startY, float width, float height, bool active);
	virtual ~GameObject() = default;
	void handleUpdate(float dt, const IInputState& input);
	void setParent(std::shared_ptr<GameObject> parentObj);
	Transform& getWorldTransform();
	void setWorldTransform(Vec2 pos, float rotation);
	virtual ObjectType getType() const;
	SpriteType getSprite() const;
	void setSprite(SpriteType sprite);
	void setActive(bool isActive);
	bool isActive() const;
	float getWidth() const;
	float getHeight() const;
	void setSize(float w, float h);

protected:
	virtual void update(float dt, const IInputState& input);

	friend class CollisionManager::Collider;
	Transform worldTransform;
	Transform localTransform;
	std::shared_ptr<Collider> collider;
	bool active = true;
	float width = 0.0f;
	float height = 0.0f;
	SpriteType sprite = SpriteType::NONE;
	virtual void onCollision(std::shared_ptr<Collider> other);
	void parentUpdate(Vec2 deltaPos, float deltaRotation);
private:
	std::optional<std::weak_ptr<GameObject>> parent = std::nullopt;
	std::vector<std::weak_ptr<GameObject>> children;
};