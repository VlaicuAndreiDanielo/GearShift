#pragma once

class IGameObject
{
public:
	virtual float getX() const = 0;
	virtual float getY() const = 0;
	virtual float getWidth() const = 0;
	virtual float getHeight() const = 0;
	virtual bool isActive() const = 0;
	virtual ~IGameObject() = default;
};