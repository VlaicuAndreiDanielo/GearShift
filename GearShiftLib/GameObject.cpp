#include "GameObject.h"

GameObject::GameObject(float startX, float startY) : transform(startX, startY) {}

Transform& GameObject::getTransform() {
	return transform;
}
