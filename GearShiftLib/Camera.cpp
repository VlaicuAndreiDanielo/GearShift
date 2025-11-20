#include "Camera.h"

ObjectType Camera::getType() const { return ObjectType::CAMERA; }

std::shared_ptr<Camera> Camera::create(float startX, float startY, float width, float height) {
	return std::shared_ptr<Camera>(new Camera{ startX, startY, width, height });
}

Camera::Camera(float startX, float startY, float width, float height)
	: GameObject(startX, startY, width, height, true) {
}
