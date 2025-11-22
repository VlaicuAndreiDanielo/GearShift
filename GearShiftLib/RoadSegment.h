#pragma once
#include "GameObject.h"

class RoadSegment : public GameObject {
public:
	static std::vector<std::shared_ptr<GameObject>> create(std::weak_ptr<CollisionManager> colisionManager, float startX, float startY, float width, float height, int totalRoadCount);

	class RoadTrigger : public GameObject {
	public:
		RoadTrigger(float startX, float startY, float width, float height);
	protected:
		void onCollision(std::shared_ptr<CollisionManager::Collider> other) override;
	};

	std::shared_ptr<RoadTrigger> getTrigger() const { return trigger; }
protected:
	friend class RoadTrigger;
	void playerTriggered();

private:
	RoadSegment(float startX, float startY, float width, float height, int totalRoadCount);
	void createTrigger();
	std::shared_ptr<RoadTrigger> trigger;
	int roadCount;
};