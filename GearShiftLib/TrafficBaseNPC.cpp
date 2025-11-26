#include "TrafficBaseNPC.h"
#include "BoxCollider.h"

TrafficBaseNPC::TrafficBaseNPC(std::mt19937& gameRng, float startX, float startY, float width, float height, float roadWidth, float roadHeight, float minSpeed, float maxSpeed) :
	GameObject{ startX, startY, width, height, true },
	roadCenterX{ startX },
	roadWidth{ roadWidth },
	roadHeight{ roadHeight },
	minSpeed{ minSpeed },
	maxSpeed{ maxSpeed },
	isStopping{ false },
	rng{ gameRng },
	speedDist{ minSpeed, maxSpeed },
	xPosDist{ startX - roadWidth / 2 + width, startX + roadWidth / 2 - width },
	yPosDist{ 5 * roadHeight, 20 * roadHeight },
	spriteDist{ 1,4 }
{
	this->sprite = SpriteType::BASE_NPC_1;
	this->type = ObjectType::NPC;
}

std::shared_ptr<PlayerTrigger> TrafficBaseNPC::getRespawnTrigger() const { return respawnTrigger; }

void TrafficBaseNPC::playerTriggered()
{
	respawn();
}


void TrafficBaseNPC::update(float dt, const IInputState& input)
{
	if (!active) return;

	this->localTransform.setPosition(this->localTransform.getPos() - Vec2{ 0,speed * dt });

	if (isStopping) {
		if (speed < 5.0f) speed = 0.0f;
		this->speed -= this->speed * 1.2f * dt;
		this->isStopping = false;
	}
	else {
		if (speed < 5.0f) speed = 5.0f;
		this->speed = std::min(this->speed + this->speed * 1.15f * dt, this->desiredSpeed);
	}


}

void TrafficBaseNPC::createRespawnTrigger(std::weak_ptr<CollisionManager> collisionManager)
{
	respawnTrigger = PlayerTrigger::create(collisionManager, this->worldTransform.getX(), this->worldTransform.getY() - 10 * height, 20 * width, height);
	respawnTrigger->setParent(shared_from_this());
}

void TrafficBaseNPC::createSlowDownTrigger(std::weak_ptr<CollisionManager> collisionManager)
{
	slowDownTrigger = SlowDownTrigger::create(collisionManager, this->worldTransform.getX(), this->worldTransform.getY() - height - 10.0f, width/1.75f, height);
	slowDownTrigger->setParent(shared_from_this());
}

void TrafficBaseNPC::respawn()
{
	int newSprite = spriteDist(rng);
	this->sprite = static_cast<SpriteType>(static_cast<int>(SpriteType::BASE_NPC_1) + newSprite - 1);
	float newSpeed = speedDist(rng);
	float newXPos = xPosDist(rng);
	float newYPosDistance = yPosDist(rng);
	this->desiredSpeed = newSpeed;
	this->speed = this->desiredSpeed;

	const Vec2& localPos = localTransform.getPos();

	Vec2 distance = Vec2{ newXPos - localPos.x , -newYPosDistance };
	localTransform.setPosition(localTransform.getPos() + distance);
	parentUpdate(distance, 0.0f);
}

std::shared_ptr<TrafficBaseNPC::SlowDownTrigger> TrafficBaseNPC::getSlowDownTrigger() const
{
	return slowDownTrigger;
}

void TrafficBaseNPC::stop()
{
	this->isStopping = true;
}

std::vector<std::shared_ptr<GameObject>> TrafficBaseNPC::create(
	std::weak_ptr<CollisionManager> collisionManager, std::mt19937& gameRng, float startX, float startY, float width, float height,
	float roadWidth, float roadHeight, float minSpeed, float maxSpeed
) {
	std::vector<std::shared_ptr<GameObject>> objects;
	auto npc = std::shared_ptr<TrafficBaseNPC>(new TrafficBaseNPC(gameRng, startX, startY, width, height, roadWidth, roadHeight, minSpeed, maxSpeed));
	objects.push_back(npc);
	npc->createRespawnTrigger(collisionManager);
	objects.push_back(npc->getRespawnTrigger());
	npc->createSlowDownTrigger(collisionManager);
	objects.push_back(npc->getSlowDownTrigger());
	if (auto collisionManagerSharedPtr = collisionManager.lock()) {
		collisionManagerSharedPtr->addCollider<BoxCollider>(npc, width, height);
	}
	npc->respawn();
	return objects;
}

std::shared_ptr<TrafficBaseNPC::SlowDownTrigger> TrafficBaseNPC::SlowDownTrigger::create(std::weak_ptr<CollisionManager> collisionManager, float startX, float startY, float width, float height)
{
	auto trigger = std::shared_ptr<TrafficBaseNPC::SlowDownTrigger>(new TrafficBaseNPC::SlowDownTrigger{ startX, startY, width, height });
	if (auto collisionManagerSharedPtr = collisionManager.lock()) {
		auto collider = collisionManagerSharedPtr->addCollider<BoxCollider>(trigger, width, height);
		collider->setTrigger(true);
	}
	return trigger;
}

TrafficBaseNPC::SlowDownTrigger::SlowDownTrigger(float startX, float startY, float width, float height)
	: GameObject{ startX, startY, width, height, true }
{
	this->type = ObjectType::TRIGGER;
	this->sprite = SpriteType::NONE;
	this->worldTransform.setFixed(true);
	this->localTransform.setFixed(true);
}

void TrafficBaseNPC::SlowDownTrigger::onCollision(std::shared_ptr<CollisionManager::Collider> other)
{
	if (other->getMasterObject()->getType() != ObjectType::PLAYER && other->getMasterObject()->getType() != ObjectType::NPC) {
		return;
	}

	if (this->parent.has_value()) {
		if (auto parentShared = this->parent.value().lock()) {
			if (auto npcShared = std::dynamic_pointer_cast<TrafficBaseNPC>(parentShared)) {
				if (parentShared == other->getMasterObject()) return;
				npcShared->stop();
			}
		}
	}
}