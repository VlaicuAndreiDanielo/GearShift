#include "PlayerTrigger.h"
#include "BoxCollider.h"
#include "RoadSegment.h"
#include "TrafficBaseNPC.h"

std::shared_ptr<PlayerTrigger> PlayerTrigger::create(std::weak_ptr<CollisionManager> collisionManager, float startX, float startY, float width, float height) {
	auto trigger = std::shared_ptr<PlayerTrigger>(new PlayerTrigger{ startX, startY, width, height });
	if (auto collisionManagerSharedPtr = collisionManager.lock()) {
		auto collider = collisionManagerSharedPtr->addCollider<BoxCollider>(trigger, width, height);
		collider->setTrigger(true);
	}
	return trigger;
}

PlayerTrigger::PlayerTrigger(float startX, float startY, float width, float height)
	: GameObject{ startX, startY, width, height, true }
{
	this->type = ObjectType::TRIGGER;
	this->sprite = SpriteType::NONE;
	this->worldTransform.setFixed(true);
	this->localTransform.setFixed(true);
}

void PlayerTrigger::onCollision(std::shared_ptr<CollisionManager::Collider> other)
{
	if (other->getMasterObject()->getType() != ObjectType::PLAYER) {
		return;
	}

	if (this->parent.has_value()) {
		if (auto parentShared = this->parent.value().lock()) {
			if (auto roadShared = std::dynamic_pointer_cast<RoadSegment>(parentShared)) {
				roadShared->playerTriggered();
			}
			else if (auto npcShared = std::dynamic_pointer_cast<TrafficBaseNPC>(parentShared)) {
				npcShared->playerTriggered();
			}
		}
	}
}
