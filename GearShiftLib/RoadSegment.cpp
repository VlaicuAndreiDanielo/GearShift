#include "RoadSegment.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "TrafficBaseNPC.h"

RoadSegment::RoadSegment(float startX, float startY, float width, float height, int totalRoadCount) :
	GameObject{ startX, startY, width, height, true },
	roadCount{ totalRoadCount }
{
	this->sprite = SpriteType::ROAD;
	this->type = ObjectType::ROAD;
}

void RoadSegment::createTrigger(std::weak_ptr<CollisionManager> collisionManager)
{
	trigger = PlayerTrigger::create(collisionManager, this->worldTransform.getX(), this->worldTransform.getY() - 3 * height, 2 * width, height);
	trigger->setParent(shared_from_this());
}

std::vector<std::shared_ptr<GameObject>> RoadSegment::create(std::weak_ptr<CollisionManager> collisionManager, float startX, float startY, float width, float height, int totalRoadCount) {
	std::vector<std::shared_ptr<GameObject>> objects;
	auto road = std::shared_ptr<RoadSegment>(new RoadSegment(startX, startY, width, height, totalRoadCount));
	objects.push_back(road);
	road->createTrigger(collisionManager);
	objects.push_back(road->getTrigger());
	if (auto collisionManagerSharedPtr = collisionManager.lock()) {

		float widthScale = width / 1400.0f;
		float heightScale = height / 720.0f;

		for (int i = 0; i < 3; i++) {
			auto roadGuard = std::make_shared<GameObject>(startX - widthScale * 405.0f, startY - heightScale * 640.0f + i * heightScale * 240.0f, widthScale * 30.0f, heightScale * 240.0f, true);
			roadGuard->setSprite(SpriteType::ROAD_GUARD);
			roadGuard->getWorldTransform().setFixed(true);
			collisionManagerSharedPtr->addCollider<BoxCollider>(roadGuard, widthScale * 30.0f, heightScale * 240.0f);
			roadGuard->setParent(road);
			objects.push_back(roadGuard);
		}
		for (int i = 0; i < 3; i++) {
			auto roadGuard = std::make_shared<GameObject>(startX + widthScale * 405.0f, startY - heightScale * 640.0f + i * heightScale * 240.0f, widthScale *  30.0f, heightScale * 240.0f, true);
			roadGuard->setWorldTransform(roadGuard->getWorldTransform().getPos(), 3.14f);
			roadGuard->setSprite(SpriteType::ROAD_GUARD);
			roadGuard->getWorldTransform().setFixed(true);
			collisionManagerSharedPtr->addCollider<BoxCollider>(roadGuard, widthScale * 30.0f, heightScale * 240.0f);
			roadGuard->setParent(road);
			objects.push_back(roadGuard);
		}

	}
	return objects;
}

void RoadSegment::playerTriggered()
{
	Vec2 distance = Vec2{ 0, -roadCount * height };
	localTransform.setPosition(localTransform.getPos() + distance);
	parentUpdate(distance, 0.0f);
}
