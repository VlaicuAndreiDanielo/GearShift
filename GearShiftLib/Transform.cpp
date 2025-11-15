#include "Transform.h"

Transform::Transform(float startX, float startY) : x(startX), y(startY) {}

Transform::Transform(std::array<float, 2> pos) : x(pos[0]), y(pos[1]) {}

std::array<float, 2> Transform::getPos() const { return std::array<float, 2>{x, y}; }

float Transform::getX() const { return x; }

float Transform::getY() const { return y; }


void Transform::setPosition(float newX, float newY) {
	x = newX;
	y = newY;
}

void Transform::setPosition(std::array<float, 2> pos) {
	x = pos[0];
	y = pos[1];
}

void Transform::setX(float newX)
{
	this->x = newX;
}

void Transform::setY(float newY)
{
	this->y = newY;
}
