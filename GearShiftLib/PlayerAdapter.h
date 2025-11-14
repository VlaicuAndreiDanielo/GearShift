#pragma once
#include "IPlayer.h"
#include <memory>


class PlayerAdapter : public IPlayer {
public:
	float getX() const override;
	float getY() const override;
	int getWidth() const override;
	int getHeight() const override;
	bool isActive() const override;
	PlayerAdapter(std::shared_ptr<class Player> p);


private:
	std::shared_ptr<class Player> player;



};