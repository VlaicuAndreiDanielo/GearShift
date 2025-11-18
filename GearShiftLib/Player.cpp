#include "Player.h"
#include "CollisionManager.h"
#include <algorithm>

Player::Player(float startX, float startY)
	: GameObject{ startX, startY, 150, 170, true }, vx{ 0 }, vy{ 0 }, speed{ 300.0f },
	boundMaxX{ 1920 }, boundMaxY{ 1080 }
{
	this->sprite = SpriteType::PLAYER;
}

ObjectType Player::getType() const { return ObjectType::PLAYER; }

std::shared_ptr<Player> Player::create(std::weak_ptr<CollisionManager> collisionManager, float startX, float startY)
{
	std::shared_ptr<Player> player(new Player(startX, startY));
	if (auto collisionManagerSharedPtr = collisionManager.lock()) {
		player->collider = collisionManagerSharedPtr->addCollider<BoxCollider>(player, static_cast<float>(player->width), static_cast<float>(player->height));
		player->collider->setOnCollisionCallback([&](auto collider) {
			// Handle collision event (currently empty)
			});
	}
	return player;
}

void Player::handleInput(const IInputState& input) {
	vx = 0;
	vy = 0;

	if (!active) return;

	// use abstract input interface
	if (input.isUpPressed()) {
		vy = -speed;
	}
	if (input.isDownPressed()) {
		vy = speed;
	}
	if (input.isLeftPressed()) {
		vx = -speed;
	}
	if (input.isRightPressed()) {
		vx = speed;
	}

	// normalize diagonal movement no longer 2x speed on vertices 
	if (vx != 0 && vy != 0) {
		vx *= 0.707f;  // 1/sqrt(2)
		vy *= 0.707f;
	}
}

void Player::update(float dt) {
	if (!active) return;

	this->transform.setPosition({
		this->transform.getX() + vx * dt,
		this->transform.getY() + vy * dt
		});

	// boundary checking 
	this->transform.setPosition({
		std::max(0.0f, std::min(this->transform.getX(), (float)(boundMaxX - width))),
		std::max(0.0f, std::min(this->transform.getY(), (float)(boundMaxY - height)))
		});
}

// Query state (for rendering in UI layer) -> dont overlap 
float Player::getX() const { return this->transform.getX(); }

void Player::setPosition(float newX, float newY) {
	this->transform.setPosition({ newX, newY });
}

void Player::setBounds(int maxX, int maxY) {
	boundMaxX = maxX;
	boundMaxY = maxY;
}