#include "Player.h"
#include <algorithm>

Player::Player(float startX, float startY)
    : x(startX), y(startY), vx(0), vy(0), speed(300.0f),
    width(50), height(50), active(true),
    boundMaxX(1920), boundMaxY(1080) {
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

    x += vx * dt;
    y += vy * dt;

    // boundary checking 
    x = std::max(0.0f, std::min(x, (float)(boundMaxX - width)));
    y = std::max(0.0f, std::min(y, (float)(boundMaxY - height)));
}

void Player::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

void Player::setBounds(int maxX, int maxY) {
    boundMaxX = maxX;
    boundMaxY = maxY;
}