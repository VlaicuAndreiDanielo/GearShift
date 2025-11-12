#pragma once
#include "IInputState.h"


class Player {
private:
  
    float x, y;
    float vx, vy;
    float speed;

    int width, height;

    // game state
    bool active;

    // boundaries
    int boundMaxX, boundMaxY;

public:
    Player(float startX, float startY);

    // update using abstract input interface
    void handleInput(const IInputState& input);
    void update(float dt);

    // Query state (for rendering in UI layer) -> dont overlap 
    float getX() const { return x; }
    float getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // game logic
    void setPosition(float newX, float newY);
    void setActive(bool isActive) { active = isActive; }
    bool isActive() const { return active; }

    // collision bounds-> reference
    void setBounds(int maxX, int maxY);
};