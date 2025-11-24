#pragma once
#include "GameObject.h"
#include "IPlayerListener.h"


class Player : public GameObject {
public:
    static std::shared_ptr<Player> create(std::weak_ptr<CollisionManager> collisionManager, float startX, float startY);
    // update using abstract input interface
    void update(float dt, const IInputState& input) override;

    // Query state (for rendering in UI layer) -> don't overlap 

    // game logic
    void setPosition(float newX, float newY);

    // collision bounds-> reference
    void setBounds(int maxX, int maxY);

    void addListener(PlayerListenerPtr listener);
    void removeListener(PlayerListenerPtr listener);

protected:
	void onCollision(std::shared_ptr<Collider> other) override;

private:
    Player(float startX, float startY);
    void notifyPlayerEliminated();
    void cleanupExpiredListeners();
    std::vector<PlayerListenerWeakPtr> m_listeners;
    float vx, vy;

    float currentSpeed;
    float maxSpeed;
    float acceleration;
    float deceleration;
    float baseSpeed;


    // boundaries
    int boundMaxX, boundMaxY;
    void handleInput(const IInputState& input);


};