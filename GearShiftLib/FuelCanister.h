#pragma once
#include "GameObject.h"
#include "GameLogic.h"
#include "CollisionManager.h"
#include <memory>
#include <vector>

class FuelCanister : public GameObject {
public:
    FuelCanister(float startX, float startY, float width, float height, GameLogic* gameLogic);

    void update(float dt, const IInputState& input) override;
    void onCollision(std::shared_ptr<CollisionManager::Collider> other) override;
	GameLogic* gameLogic = nullptr;

    static std::vector<std::shared_ptr<GameObject>> create(
        std::weak_ptr<CollisionManager> collisionManager,
        float startX, float startY, GameLogic* gameLogic
    );

private:
};
