#pragma once
#include <cmath>

struct Vec2 {
	float x = 0.0f, y = 0.0f;

	Vec2 operator+(const Vec2& other) const {
		return Vec2{ x + other.x, y + other.y };
	}
	Vec2 operator-(const Vec2& other) const {
		return Vec2{ x - other.x, y - other.y };
	}
	Vec2 operator*(float scalar) const {
		return Vec2{ x * scalar, y * scalar };
	}
};

inline float dot(const Vec2& a, const Vec2& b) {
	return a.x * b.x + a.y * b.y;
}

inline Vec2 normalize(const Vec2& v) {
	float length = std::sqrt(v.x * v.x + v.y * v.y);
	if (length == 0.0f) return { 0,0 };
	return Vec2{ v.x / length, v.y / length };
}