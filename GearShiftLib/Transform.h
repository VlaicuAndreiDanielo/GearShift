#pragma once
#include "Vec2.h"

class Transform {
public:
	Transform() = default;
	Transform(Vec2 startPos);
	Transform(Transform&&) = default;
	Transform(const Transform&) = default;
	Transform& operator=(Transform&&) = default;
	Transform& operator=(const Transform&) = default;
	virtual ~Transform() = default;
	Vec2 getPos() const;
	float getX() const;
	float getY() const;
	void setPosition(Vec2 pos);
	void setX(float newX);
	void setY(float newY);
	void setRotation(float radians);
	float getRotation() const;
	void setFixed(bool fixed);
	bool getFixed() const;
	void setLockX(bool lockX);
	void setLockY(bool lockY);
	void setLockRotation(bool lockRotation);
	bool isXLocked() const;
	bool isYLocked() const;
	bool isRotationLocked() const;
private:
	Vec2 position;
	float rotation = 0.0f; // radians
	bool isFixed = false;
	bool xLocked = false;
	bool yLocked = false;
	bool rotationLocked = false;
};