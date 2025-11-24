#include "FuelCanister.h"
#include "BoxCollider.h"
#include "Player.h"

FuelCanister::FuelCanister(float startX, float startY, float width, float height, GameLogic* gameLogic)
    : GameObject(startX, startY, width, height, true), gameLogic(gameLogic)
{
    this->type = ObjectType::FUEL;
    this->sprite = SpriteType::FUEL_CANISTER;
}

void FuelCanister::update(float dt, const IInputState& input) {
}

void FuelCanister::onCollision(std::shared_ptr<CollisionManager::Collider> other)
{
    if (!active) return;

    if (other->getMasterObject()->getType() == ObjectType::PLAYER) {
        active = false;

        if (gameLogic) {
            gameLogic->setFuelRecharged();
        }
    }
}


std::vector<std::shared_ptr<GameObject>> FuelCanister::create(
    std::weak_ptr<CollisionManager> collisionManager,
    float startX, float startY, GameLogic* gameLogic
) {
    std::vector<std::shared_ptr<GameObject>> objects;
    auto fuel = std::make_shared<FuelCanister>(startX, startY, 50.0f, 50.0f, gameLogic);
    objects.push_back(fuel);

    if (auto collisionManagerShared = collisionManager.lock()) {
        collisionManagerShared->addCollider<BoxCollider>(fuel, 50.0f, 50.0f);
    }

    return objects;
}
