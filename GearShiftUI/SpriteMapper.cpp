#include "SpriteMapper.h"

const std::unordered_map<SpriteType, std::string> SpriteMapper::spritePathMap {
	{ SpriteType::NONE, "" },
	{ SpriteType::PLAYER, "assets/images/Car_Red.png" },
	{ SpriteType::ROAD, "assets/images/road.png"},
	{ SpriteType::ROAD_GUARD, "assets/images/road_guard.png"},
	{ SpriteType::BASE_NPC_1, "assets/images/Car_Green.png"},
	{ SpriteType::BASE_NPC_2, "assets/images/Car_Blue.png"},
	{ SpriteType::BASE_NPC_3, "assets/images/Car_Orange.png"},
	{ SpriteType::BASE_NPC_4, "assets/images/Car_Yellow.png"},
	{ SpriteType::FUEL_CANISTER, "assets/images/FuelCanister.png"}
};
const std::string SpriteMapper::getSpritePath(SpriteType sprite)
{
	if (spritePathMap.find(sprite) == spritePathMap.end()) {
		return "";
	}
	return spritePathMap.at(sprite);
}