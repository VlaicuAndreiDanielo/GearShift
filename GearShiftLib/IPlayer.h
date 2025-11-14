#pragma once

class IPlayer
{
public:
	virtual float getX() const = 0;
	virtual float getY() const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual bool isActive() const = 0;
	virtual ~IPlayer() = default;
};