#pragma once
#include <memory>
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
	Transform& getTransform();
	virtual ObjectType getType() const;
	SpriteType getSprite() const;
	void setSprite(SpriteType sprite);
	virtual void handleInput(const IInputState& input);
	void setActive(bool isActive);
	bool isActive() const;
	float getWidth() const;
	float getHeight() const;
	void setSize(float w, float h);

protected:
	Transform transform;
	bool active = true;
	float width = 0.0f;
	float height = 0.0f;
	SpriteType sprite = SpriteType::NONE;
private:
};