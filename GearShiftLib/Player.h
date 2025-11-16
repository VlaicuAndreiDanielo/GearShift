#pragma once
#include "GameObject.h"
#include "IInputState.h"
#include "BoxCollider.h"


class Player : public GameObject {
private:
    Player(float startX, float startY);
    //TODO: ADD RIGIDBODY
    float vx, vy;
    float speed;

    int width, height;

    // game state
    bool active;

    // boundaries
    int boundMaxX, boundMaxY;
	std::shared_ptr<BoxCollider> collider;

public:
    static std::shared_ptr<Player> create(float startX, float startY);
    // update using abstract input interface
    void handleInput(const IInputState& input);
    void update(float dt);

    // Query state (for rendering in UI layer) -> don't overlap 
    float getX() const;
    float getY() const { return this->transform.getY(); }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // game logic
    void setPosition(float newX, float newY);
    void setActive(bool isActive) { active = isActive; }
    bool isActive() const { return active; }

    // collision bounds-> reference
    void setBounds(int maxX, int maxY);
};