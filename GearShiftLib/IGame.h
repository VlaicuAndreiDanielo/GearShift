#pragma once
#include <vector>
#include <memory>
#include "IInputState.h"
#include "IGameObject.h"
#include "GameState.h"

#include "IFabric.h"

class IGame {
public:
	virtual void update(float dt, IInputState& input) = 0;
	virtual void startGame() = 0;
	virtual void pauseGame() = 0;
	virtual void resumeGame() = 0;
	virtual void endGame() = 0;
	virtual const std::vector<std::shared_ptr<IGameObject>>& getGameObjects() const = 0;
	virtual std::shared_ptr<IFabric> getFabric() = 0;
	virtual const std::shared_ptr<IFabric> getFabric() const = 0;
	virtual GameState getState() const = 0;
	virtual float getTime() const = 0;
	virtual int getScore() const = 0;
	virtual void onFuelEmpty() = 0;
	virtual bool getIsFuelRecharged() const = 0;
	virtual void setFuelRecharged() = 0;
	virtual void applyMouseForce(int x, int y, bool pressed) = 0;

	virtual ~IGame() = default;
};