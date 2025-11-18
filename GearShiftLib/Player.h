#pragma once
#include "GameObject.h"
#include "BoxCollider.h"


class Player : public GameObject {
private:
    Player(float startX, float startY);
    float vx, vy;
    float speed;


    // boundaries
    int boundMaxX, boundMaxY;
	std::shared_ptr<BoxCollider> collider;

public:
	ObjectType getType() const override;
    static std::shared_ptr<Player> create(std::weak_ptr<CollisionManager> colisionManager, float startX, float startY);
    // update using abstract input interface
    void handleInput(const struct IInputState& input) override;
    void update(float dt);

    // Query state (for rendering in UI layer) -> don't overlap 
    float getX() const;
    float getY() const { return this->transform.getY(); }

    // game logic
    void setPosition(float newX, float newY);

    // collision bounds-> reference
    void setBounds(int maxX, int maxY);
};