#pragma once
#include <array>

class Transform {
public:
	Transform() = default;
	Transform(float startX, float startY);
	Transform(std::array<float, 2> pos);
	Transform(Transform&&) = default;
	Transform(const Transform&) = default;
	Transform& operator=(Transform&&) = default;
	Transform& operator=(const Transform&) = default;
	virtual ~Transform() = default;
	std::array<float, 2> getPos() const;
	float getX() const;
	float getY() const;
	void setPosition(float newX, float newY);
	void setPosition(std::array<float, 2> pos);
	void setX(float newX);
	void setY(float newY);
private:
	float x = 0.0f;
	float y = 0.0f;
};