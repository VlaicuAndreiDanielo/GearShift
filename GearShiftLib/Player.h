#pragma once
#include "GameObject.h"


class Player : public GameObject {
public:
	ObjectType getType() const override;
    static std::shared_ptr<Player> create(std::weak_ptr<CollisionManager> colisionManager, float startX, float startY);
    // update using abstract input interface
    void update(float dt, const IInputState& input) override;

    // Query state (for rendering in UI layer) -> don't overlap 
    float getX() const;
    float getY() const { return this->transform.getY(); }

    // game logic
    void setPosition(float newX, float newY);

    // collision bounds-> reference
    void setBounds(int maxX, int maxY);

protected:
	void onCollision(std::shared_ptr<Collider> other) override;

private:
    Player(float startX, float startY);
    float vx, vy;
    float speed;


    // boundaries
    int boundMaxX, boundMaxY;
    void handleInput(const IInputState& input);


};