#include "SpriteMapper.h"

const std::unordered_map<SpriteType, std::string> SpriteMapper::spritePathMap {
	{ SpriteType::NONE, "assets/images/car_menu.png" },
	{ SpriteType::PLAYER, "assets/images/PlayerCar.png" }
};
const std::string SpriteMapper::getSpritePath(SpriteType sprite)
{
	if (spritePathMap.find(sprite) == spritePathMap.end()) {
		return "";
	}
	return spritePathMap.at(sprite);
}