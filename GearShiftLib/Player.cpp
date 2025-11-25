#include "Player.h"
#include "BoxCollider.h"
#include <algorithm>

Player::Player(float startX, float startY)
	: GameObject{ startX, startY, 95.0f, 170.0f, true },
	vx(0), vy(0),
	currentSpeed(0.0f),
	maxSpeed(1000.0f),
	acceleration(200.0f),
	deceleration(100.0f),
	baseSpeed(600.0f),
	boundMaxX(1920), boundMaxY(1080)
{
	this->sprite = SpriteType::PLAYER;
	this->type = ObjectType::PLAYER;
}

void Player::notifyPlayerEliminated()
{
	cleanupExpiredListeners();
	for (const auto& weakListener : m_listeners) {
		if (auto listener = weakListener.lock()) {
			listener->onPlayerEliminated();
		}
	}
}

void Player::cleanupExpiredListeners()
{
	m_listeners.erase(
		std::remove_if(m_listeners.begin(), m_listeners.end(),
			[](const PlayerListenerWeakPtr& weakPtr) {
				return weakPtr.expired();
			}),
		m_listeners.end());
}


std::shared_ptr<Player> Player::create(std::weak_ptr<CollisionManager> collisionManager, float startX, float startY)
{
	std::shared_ptr<Player> player(new Player(startX, startY));
	if (auto collisionManagerSharedPtr = collisionManager.lock()) {
		collisionManagerSharedPtr->addCollider<BoxCollider>(player, static_cast<float>(player->width), static_cast<float>(player->height));
	}
	return player;
}

void Player::update(float dt, const IInputState& input)
{
	if (!active) return;

	handleInput(input);

	this->localTransform.setPosition({
		this->localTransform.getX() + vx * dt,
		this->localTransform.getY() + vy * dt
		});

	// boundary checking 
	this->worldTransform.setPosition({
		std::max(0.0f, std::min(this->worldTransform.getX(), (float)(boundMaxX - width))),
		std::max(0.0f, std::min(this->worldTransform.getY(), (float)(boundMaxY - height)))
		});
}


void Player::handleInput(const IInputState& input)
{
	vx = 0;

	float dt = 1.0f / 60.0f;

	if (input.isUpPressed()) {
		currentSpeed += acceleration * dt;
		if (currentSpeed > maxSpeed)
			currentSpeed = maxSpeed;
	}
	else {
		currentSpeed -= deceleration * dt;
		if (currentSpeed < 0)
			currentSpeed = 0;
	}

	if (input.isDownPressed()) {
		currentSpeed -= 2 * deceleration * dt;
		if (currentSpeed < 0)
			currentSpeed = 0;
	}

	vy = -currentSpeed;

	if (input.isLeftPressed())  vx = -baseSpeed;
	if (input.isRightPressed()) vx = baseSpeed;
}

// Query state (for rendering in UI layer) -> dont overlap 

void Player::setPosition(float newX, float newY) {
	this->worldTransform.setPosition({ newX, newY });
}

void Player::setBounds(int maxX, int maxY) {
	boundMaxX = maxX;
	boundMaxY = maxY;
}

void Player::addListener(PlayerListenerPtr listener)
{
	cleanupExpiredListeners();
	m_listeners.push_back(listener);
}

void Player::removeListener(PlayerListenerPtr listener)
{
	cleanupExpiredListeners();
	m_listeners.erase(
		std::remove_if(m_listeners.begin(), m_listeners.end(),
			[listener](const PlayerListenerWeakPtr& weakPtr) {
				auto ptr = weakPtr.lock();
				return !ptr || ptr == listener;
			}),
		m_listeners.end());
}

void Player::onCollision(std::shared_ptr<Collider> other)
{
	if (other->getMasterObject() && other->getMasterObject()->getType() == ObjectType::NPC) {
		this->notifyPlayerEliminated();
	}
}
