#pragma once
#include "GameObject.h"
#include "PlayerTrigger.h"

class RoadSegment : public GameObject {
public:
	static std::vector<std::shared_ptr<GameObject>> create(std::weak_ptr<CollisionManager> collisionManager, float startX, float startY, float width, float height, int totalRoadCount);
	static int segmentPassCounter;

	std::shared_ptr<PlayerTrigger> getTrigger() const { return trigger; }
protected:
	friend class PlayerTrigger;
	void playerTriggered();

private:
	RoadSegment(float startX, float startY, float width, float height, int totalRoadCount);
	void createTrigger(std::weak_ptr<CollisionManager> collisionManager);
	std::shared_ptr<PlayerTrigger> trigger;
	int roadCount;
	
};