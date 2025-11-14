#include "PlayerAdapter.h"
#include "Player.h"

float PlayerAdapter::getX() const
{
    return this->player->getX();
}

float PlayerAdapter::getY() const
{
    return this->player->getY();
}

int PlayerAdapter::getWidth() const
{
    return this->player->getWidth();
}

int PlayerAdapter::getHeight() const
{
    return this->player->getHeight();
}

bool PlayerAdapter::isActive() const
{
    return this->player->isActive();
}

PlayerAdapter::PlayerAdapter(std::shared_ptr<class Player> p) : player(p)
{

}
