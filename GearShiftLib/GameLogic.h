#pragma once
#include <memory>
#include "Player.h"
#include "FabricPhysics.h"
#include "IInputState.h"
#include "IGameObject.h"
#include "CollisionManager.h"


enum class GameState {
	Menu,
	Playing,
	Paused,
	GameOver
};

class GameLogic {
public:
	GameLogic(int screenW, int screenH);

	// core update loop
	void update(float dt, const IInputState& input);

	// state management
	void startGame();
	void pauseGame();
	void resumeGame();
	void endGame();

	const std::vector<std::shared_ptr<IGameObject>>& getGameObjects() const;


	// Fabric access - safe with null checks
	Fabric* getFabric() { return fabric.get(); }
	const Fabric* getFabric() const { return fabric.get(); }

	GameState getState() const { return currentState; }
	float getTime() const { return gameTime; }
	float getSpeed() const { return speed; }
	int getScore() const { return score; }
	float getLapTime() const { return lapTime; }

	// game logic
	void applyMouseForce(int x, int y, bool pressed);

private:
	void scaleToCamera();

	std::unique_ptr<Fabric> fabric;
	std::shared_ptr<class Camera> mainCamera;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<std::shared_ptr<IGameObject>> objectAdapters;


	std::shared_ptr<CollisionManager> collisionManager;

	// game state
	GameState currentState;
	float gameTime;
	int screenWidth, screenHeight;

	// game stats -> reference 
	float speed;
	int score;
	float lapTime;

};