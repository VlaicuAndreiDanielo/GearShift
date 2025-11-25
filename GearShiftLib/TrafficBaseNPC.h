#pragma once
#include <random>
#include "GameObject.h"
#include "PlayerTrigger.h"

class TrafficBaseNPC : public GameObject {
public:
	static std::vector<std::shared_ptr<GameObject>> create(std::weak_ptr<CollisionManager> collisionManager, std::mt19937& gameRng, float startX, float startY, float width, float height, float roadWidth, float roadHeight, float minSpeed, float maxSpeed);
	std::shared_ptr<PlayerTrigger> getRespawnTrigger() const;
	class SlowDownTrigger : public GameObject {
	public:
		static std::shared_ptr<SlowDownTrigger> create(std::weak_ptr<CollisionManager> collisionManager, float startX, float startY, float width, float height);
	protected:
		SlowDownTrigger(float startX, float startY, float width, float height);
		void onCollision(std::shared_ptr<CollisionManager::Collider> other) override;
	};
	std::shared_ptr<TrafficBaseNPC::SlowDownTrigger> getSlowDownTrigger() const;
protected:
	friend class PlayerTrigger;
	friend class SlowDownTrigger;
	void stop();
	void playerTriggered();
	void update(float dt, const IInputState& input) override;

private:
	TrafficBaseNPC(std::mt19937& gameRng, float startX, float startY, float width, float height, float roadWidth, float roadHeight, float minSpeed, float maxSpeed);
	void createRespawnTrigger(std::weak_ptr<CollisionManager> collisionManager);
	void createSlowDownTrigger(std::weak_ptr<CollisionManager> collisionManager);
	void respawn();
	std::shared_ptr<PlayerTrigger> respawnTrigger;
	std::shared_ptr<TrafficBaseNPC::SlowDownTrigger> slowDownTrigger;
	float roadWidth = 100.0f;
	float roadHeight = 100.0f;
	float roadCenterX = 50.0f;
	float speed = 5.0f;
	float desiredSpeed = 5.0f;
	float minSpeed = 0.0f;
	float maxSpeed = 50.0f;
	bool isStopping = false;
	std::mt19937& rng;
	std::uniform_real_distribution<float> speedDist;
	std::uniform_real_distribution<float> xPosDist;
	std::uniform_real_distribution<float> yPosDist;
	std::uniform_int_distribution<int> spriteDist;
};