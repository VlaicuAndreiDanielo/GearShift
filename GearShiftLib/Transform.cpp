#include "Transform.h"

Transform::Transform(Vec2 startPos) : position{ startPos } {}

Vec2 Transform::getPos() const { return this->position; }

float Transform::getX() const { return this->position.x; }

float Transform::getY() const { return this->position.y; }

void Transform::setPosition(Vec2 pos)
{
	if (xLocked) pos.x = this->position.x;
	if (yLocked) pos.y = this->position.y;
	this->position = pos;
}

void Transform::setX(float newX)
{
	if (xLocked) return;
	this->position.x = newX;
}

void Transform::setY(float newY)
{
	if (yLocked) return;
	this->position.y = newY;
}

void Transform::setRotation(float radians)
{
	if (rotationLocked) return;
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

void Transform::setLockX(bool lockX) { xLocked = lockX; }

void Transform::setLockY(bool lockY) { yLocked = lockY; }

void Transform::setLockRotation(bool lockRotation) { rotationLocked = lockRotation; }

bool Transform::isXLocked() const { return xLocked; }

bool Transform::isYLocked() const { return yLocked; }

bool Transform::isRotationLocked() const { return rotationLocked; }
