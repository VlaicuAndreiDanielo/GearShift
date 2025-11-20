#include "GameLogic.h"
#include <SDL2/SDL.h>
#include "GameObjectAdapter.h"
#include "Camera.h"
#include "BoxCollider.h"

GameLogic::GameLogic(int screenW, int screenH)
	: collisionManager{ std::make_shared<CollisionManager>() }, 
	fabric{ std::make_unique<Fabric>(130, 75, 16.0f) },
	screenWidth(screenW), screenHeight(screenH),
	currentState(GameState::Menu),
	gameTime(0), speed(0), score(0), lapTime(0) {

	// player created when game starts (not in menu)
}

void GameLogic::update(float dt, const IInputState& input) {
	gameTime += dt;

	// update fabric if it exists
	if (fabric) {
		fabric->update(dt);
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameLogic: Fabric is null in update");
		return;
	}

	// update based on game state
	switch (currentState) {
	case GameState::Menu:
		// menu logic here (minimal for now)
		break;

	case GameState::Playing:
		for (auto& obj : gameObjects) {
			obj->handleUpdate(dt, input);
		}
		collisionManager->update();

		scaleToCamera();

		// update game stats
		// TODO: Add game logic (lap counting, collision, etc.)

		// check for pause input
		if (input.isPausePressed()) {
			pauseGame();
		}
		break;

	case GameState::Paused:
		// check for resume
		if (input.isPausePressed()) {
			resumeGame();
		}
		break;

	case GameState::GameOver:
		// game over logic
		break;
	}
}

void GameLogic::startGame() {
	currentState = GameState::Playing;

	// create player at center
	float centerX = screenWidth / 2.0f;
	float centerY = screenHeight / 2.0f;

	mainCamera = Camera::create(0, 0, screenWidth, screenHeight);
	mainCamera->getWorldTransform().setLockX(true);
	gameObjects.push_back(mainCamera);

	auto road1 = std::make_shared<GameObject>(centerX, centerY-400, 1400.0f, 720.0f, true);
	road1->setSprite(SpriteType::ROAD);
	gameObjects.push_back(road1);
	objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(road1));


	for (int i = 0; i < 3; i++) {
		auto roadGuard = std::make_shared<GameObject>(centerX - 405.0f, centerY - 640.0f + i * 240.0f, 30.0f, 240.0f, true);
		roadGuard->setSprite(SpriteType::ROAD_GUARD);
		roadGuard->getWorldTransform().setFixed(true);
		collisionManager->addCollider<BoxCollider>(roadGuard, 30.0f, 240.0f);
		gameObjects.push_back(roadGuard);
		objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(roadGuard));
	}
	for (int i = 0; i < 3; i++) {
		auto roadGuard = std::make_shared<GameObject>(centerX + 405.0f, centerY - 640.0f + i * 240.0f, 30.0f, 240.0f, true);
		roadGuard->setWorldTransform(roadGuard->getWorldTransform().getPos(), 3.14f);
		roadGuard->setSprite(SpriteType::ROAD_GUARD);
		roadGuard->getWorldTransform().setFixed(true);
		collisionManager->addCollider<BoxCollider>(roadGuard, 30.0f, 240.0f);
		gameObjects.push_back(roadGuard);
		objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(roadGuard));
	}

	auto road2 = std::make_shared<GameObject>(centerX, centerY+300, 1400.0f, 720.0f, true);
	road2->setSprite(SpriteType::ROAD);
	gameObjects.push_back(road2);
	objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(road2));

	auto player = Player::create(collisionManager, centerX, centerY + 300.0f);
	player->setBounds(screenWidth, screenHeight);
	gameObjects.push_back(player);
	objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(player));

	this->mainCamera->setParent(player);

	// reset game stats
	speed = 0;
	score = 0;
	lapTime = 0;
	gameTime = 0;
}

void GameLogic::pauseGame() {
	if (currentState == GameState::Playing) {
		currentState = GameState::Paused;
	}
}

void GameLogic::resumeGame() {
	if (currentState == GameState::Paused) {
		currentState = GameState::Playing;
	}
}

void GameLogic::endGame() {
	currentState = GameState::GameOver;
	// player stays in memory for showing final position the nes game did that when it resumed on button 
	gameObjects.clear();
	objectAdapters.clear();
}


const std::vector<std::shared_ptr<IGameObject>>& GameLogic::getGameObjects() const { return objectAdapters; }

void GameLogic::applyMouseForce(int x, int y, bool pressed) {
	if (!fabric) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "GameLogic: Cannot apply force, fabric is null");
		return;
	}

	if (pressed) {
		fabric->applyForce((float)x, (float)y, 100.0f, 800.0f);
	}
}

void GameLogic::scaleToCamera()
{
	if (mainCamera) {
		Vec2 camPos = mainCamera->getWorldTransform().getPos();
		float cameraRotation = mainCamera->getWorldTransform().getRotation();
		//Vec2 screenCenter{ static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) };
		for (auto& obj : gameObjects) {
			Vec2 currentPos = obj->getWorldTransform().getPos();
			float currentRotation = obj->getWorldTransform().getRotation();
			obj->setWorldTransform(currentPos - camPos, currentRotation - cameraRotation);
			auto x = 1;
		}
	}
	else {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "GameLogic: Cannot scale to camera, mainCamera is null");
	}
}
