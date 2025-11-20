#pragma once
#include "GameObject.h"

class Camera : public GameObject {
public:
	ObjectType getType() const override;
	static std::shared_ptr<Camera> create(float startX = 0, float startY = 0, float width = 1920, float height = 1080);
private:
	Camera(float startX = 0, float startY = 0, float width = 1920, float height = 1080);
};