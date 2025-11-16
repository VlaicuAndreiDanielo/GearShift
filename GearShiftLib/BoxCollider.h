#pragma once
#include "Collider.h"
#include <array>

class BoxCollider : public Collider {
public:
	BoxCollider(float width, float height);
	std::optional<Collision> checkCollisionWith(const Collider& other) const override;
	std::optional<Collision> checkCollisionWith(const BoxCollider& other) const override;
	float getWidth() const { return width; }
	float getHeight() const { return height; }
private:
	std::array<Vec2, 4> getCorners() const;
	static std::pair<float, float> projectOntoAxis(const std::array<Vec2, 4>& corners, const Vec2& axis);
	float width;
	float height;
};