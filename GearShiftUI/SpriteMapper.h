#pragma once
#include <string>
#include <unordered_map>
#include "SpriteType.h"

static class SpriteMapper {
public:
	static const std::string getSpritePath(SpriteType sprite);
private:
	static const std::unordered_map<SpriteType, std::string> spritePathMap;
};