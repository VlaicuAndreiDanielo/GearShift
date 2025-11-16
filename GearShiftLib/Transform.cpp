#include "Transform.h"

Transform::Transform(Vec2 startPos) : position{ startPos } {}

Vec2 Transform::getPos() const { return this->position; }

float Transform::getX() const { return this->position.x; }

float Transform::getY() const { return this->position.y; }

void Transform::setPosition(Vec2 pos)
{
	this->position = pos;
}

void Transform::setX(float newX)
{
	this->position.x = newX;
}

void Transform::setY(float newY)
{
	this->position.y = newY;
}

void Transform::setRotation(float radians)
{
	this->rotation = radians;
}

float Transform::getRotation() const
{
	return this->rotation;
}

void Transform::setFixed(bool fixed)
{
	this->isFixed = fixed;
}

bool Transform::getFixed() const
{
	return this->isFixed;
}
