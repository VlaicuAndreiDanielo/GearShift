#include "BoxCollider.h"
#include "Collision.h"
#include <cmath>

BoxCollider::BoxCollider(std::weak_ptr<CollisionManager> manager, float width, float height)
	: Collider{ manager }, width{ width }, height{ height } {
}

std::optional<Collision> BoxCollider::checkCollisionWith(const Collider& other) const
{
	return other.checkCollisionWith(*this);
}

std::optional<Collision> BoxCollider::checkCollisionWith(const BoxCollider& other) const
{
	std::array<Vec2, 4> cornersA = this->getCorners();
	std::array<Vec2, 4> cornersB = other.getCorners();
	Vec2 axes[4] = {
		normalize(cornersA[1] - cornersA[0]),
		normalize(cornersA[3] - cornersA[0]),
		normalize(cornersB[1] - cornersB[0]),
		normalize(cornersB[3] - cornersB[0])
	};

	float smallestOverlap = std::numeric_limits<float>::infinity();
	Vec2 smallestAxis{};

	for (int i = 0; i < 4; i++) {
		Vec2 axis = { -axes[i].y, axes[i].x }; // Perpendicular axis
		auto [minA, maxA] = projectOntoAxis(cornersA, axis);
		auto [minB, maxB] = projectOntoAxis(cornersB, axis);
		// Check for overlap
		if (maxA < minB || maxB < minA) {
			return std::nullopt; // No collision
		}

		float overlap = std::min(maxA, maxB) - std::max(minA, minB);

		if (overlap < smallestOverlap) {
			smallestOverlap = overlap;
			smallestAxis = axis;
		}
	}
	smallestAxis = normalize(smallestAxis);

	Vec2 centerA = this->getMasterObject()->getTransform().getPos();
	Vec2 centerB = other.getMasterObject()->getTransform().getPos();
	if (dot(centerB - centerA, smallestAxis) < 0) {
		smallestAxis = smallestAxis * -1.0f;
	}

	Collision result(shared_from_this(), other.shared_from_this());

	result.setCollisionNormal(smallestAxis);
	result.setPenetrationDepth(smallestOverlap);

	return result;
}

std::array<Vec2, 4> BoxCollider::getCorners() const
{
	Transform& transform = this->getMasterObject()->getTransform();
	Vec2 position = transform.getPos();
	float rotation = transform.getRotation();
	float cos = std::cos(rotation);
	float sin = std::sin(rotation);

	float halfWidth = width * 0.5f;
	float halfHeight = height * 0.5f;

	Vec2 localCorners[4] = {
		{-halfWidth, -halfHeight},
		{ halfWidth, -halfHeight},
		{ halfWidth,  halfHeight},
		{-halfWidth,  halfHeight}
	};
	std::array<Vec2, 4> worldCorners;
	for (int i = 0; i < 4; i++) {
		worldCorners[i] = {
			position.x + localCorners[i].x * cos - localCorners[i].y * sin,
			position.y + localCorners[i].x * sin + localCorners[i].y * cos
		};
	}
	return worldCorners;
}

std::pair<float, float> BoxCollider::projectOntoAxis(const std::array<Vec2, 4>& corners, const Vec2& axis)
{
	float min, max;
	min = max = dot(corners[0], axis);
	for (int i = 1; i < 4; i++) {
		float projection = dot(corners[i], axis);
		if (projection < min) min = projection;
		if (projection > max) max = projection;
	}
	return { min,max };
}
