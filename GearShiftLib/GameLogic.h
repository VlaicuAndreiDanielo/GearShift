#pragma once
#include <memory>
#include <random>
#include "IGame.h"
#include "Player.h"
#include "IInputState.h"
#include "IGameObject.h"
#include "CollisionManager.h"
#include "GameScene.h"

class GameLogic : public IGame, public IPlayerListener, public std::enable_shared_from_this<GameLogic> {
public:

	static std::shared_ptr<IGame> create(int screenW, int screenH);

	// core update loop
	void update(float dt, const IInputState& input) override;

	// state management
	void startGame() override;
	void pauseGame() override;
	void resumeGame() override;
	void endGame() override;

	const std::vector<std::shared_ptr<IGameObject>>& getGameObjects() const override;


	// Fabric access - safe with null checks
	std::shared_ptr<class IFabric> getFabric() override;
	const std::shared_ptr<class IFabric> getFabric() const override;
	void onFuelEmpty() override;

	GameState getState() const override { return currentState; }
	float getTime() const override { return gameTime; }
	int getScore() const override { return score; }
	bool isGameOver() const{ return currentState == GameState::GameOver; }
	void spawnFuelCanister();

	// game logic
	void applyMouseForce(int x, int y, bool pressed) override;
	bool isFuelRecharged = false;
	void setFuelRecharged();
	bool getIsFuelRecharged() const { return isFuelRecharged; }

	void onPlayerEliminated() override;

private:
	GameLogic(int screenW, int screenH);
	void scaleToCamera();
	void createRoadSegments();
	void createNPCs();

	std::shared_ptr<class IFabric> fabric;
	std::shared_ptr<class Camera> mainCamera;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<std::shared_ptr<IGameObject>> objectAdapters;


	std::shared_ptr<CollisionManager> collisionManager;

	// game state
	GameState currentState;
	float gameTime;
	int screenWidth, screenHeight;

	// game stats -> reference 
	int score;

	std::mt19937 rng;

};