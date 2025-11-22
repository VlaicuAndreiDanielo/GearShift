#include "GameObject.h"

GameObject::GameObject(float startX = 0, float startY = 0, float width = 0, float height = 0, bool active = true) : worldTransform({ startX, startY }), localTransform({ startX, startY }), width{ width }, height{ height }, active{ active } {}

Transform& GameObject::getWorldTransform() {
	return worldTransform;
}

void GameObject::setWorldTransform(Vec2 pos, float rotation)
{
	worldTransform.setPosition(pos);
	worldTransform.setRotation(rotation);
	if (parent.has_value() && parent.value().expired()) {
		parent = std::nullopt;
	}
	if (!parent.has_value() || parent.value().expired()) {
		localTransform.setPosition(pos);
		localTransform.setRotation(rotation);
	}
}

ObjectType GameObject::getType() const { return this->type; }

SpriteType GameObject::getSprite() const { return this->sprite; }

void GameObject::setSprite(SpriteType sprite)
{
	this->sprite = sprite;
}

void GameObject::update(float dt, const IInputState& input) {}


void GameObject::setActive(bool isActive) { active = isActive; }

bool GameObject::isActive() const { return active; }

float GameObject::getWidth() const { return width; }

float GameObject::getHeight() const { return height; }

void GameObject::setSize(float w, float h) { width = w; height = h; }

void GameObject::onCollision(std::shared_ptr<Collider> other) {}

void GameObject::parentUpdate(Vec2 deltaPos, float deltaRotation)
{
	children.erase(
		std::remove_if(
			children.begin(),
			children.end(),
			[](const std::weak_ptr<GameObject>& ptr) { return ptr.expired(); }
		),
		children.end()
	);
	worldTransform.setPosition(worldTransform.getPos() + deltaPos);
	worldTransform.setRotation(worldTransform.getRotation() + deltaRotation);
	for (auto& weakChild : children) {
		if (auto child = weakChild.lock()) {
			child->parentUpdate(deltaPos, deltaRotation);
		}
	}
}

void GameObject::setParent(std::shared_ptr<GameObject> parentObj)
{
	this->parent = parentObj;
	localTransform.setPosition(parentObj->worldTransform.getPos() - worldTransform.getPos());
	localTransform.setRotation(parentObj->worldTransform.getRotation() - worldTransform.getRotation());
	parentObj->children.push_back(shared_from_this());
}

void GameObject::handleUpdate(float dt, const IInputState& input)
{
	Vec2 previousWorldPos = worldTransform.getPos();
	float previousWorldRotation = worldTransform.getRotation();
	Vec2 previousLocalPos = localTransform.getPos();
	float previousLocalRotation = localTransform.getRotation();
	update(dt, input);
	Vec2 deltaWorldPos = worldTransform.getPos() - previousWorldPos;
	float deltaWorldRotation = worldTransform.getRotation() - previousWorldRotation;
	localTransform.setPosition(localTransform.getPos() + deltaWorldPos);
	localTransform.setRotation(localTransform.getRotation() + deltaWorldRotation);
	Vec2 deltaPos = localTransform.getPos() - previousLocalPos;
	float deltaRotation = localTransform.getRotation() - previousLocalRotation;
	if(deltaPos.x == 0 && deltaPos.y == 0 && deltaRotation == 0) {
		return;
	}
	if (parent.has_value() && parent.value().expired()) {
		parent = std::nullopt;
	}
	parentUpdate(deltaPos, deltaRotation);
}
