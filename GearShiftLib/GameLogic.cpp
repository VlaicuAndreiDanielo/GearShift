#include "GameLogic.h"
#include <SDL2/SDL.h>
#include "GameObjectAdapter.h"
#include "Camera.h"
#include "BoxCollider.h"
#include "FabricPhysics.h"
#include "RoadSegment.h"
#include "TrafficBaseNPC.h"
#include "FuelCanister.h"

GameLogic::GameLogic(int screenW, int screenH)
	: collisionManager{ std::make_shared<CollisionManager>() },
	fabric{ Fabric::create(130,75,16.0f) },
	screenWidth(screenW), screenHeight(screenH),
	currentState(GameState::Menu),
	gameTime(0), score(0),
	rng{ std::random_device{}() } {
	// player created when game starts (not in menu)
}

std::shared_ptr<IGame> GameLogic::create(int screenW, int screenH) {
	return std::shared_ptr<IGame>(new GameLogic(screenW, screenH));
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
	if (RoadSegment::segmentPassCounter >= 3)
	{
		RoadSegment::segmentPassCounter = 0;
		spawnFuelCanister();
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
		return;
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

	createRoadSegments();
	createNPCs();

	auto player = Player::create(collisionManager, centerX, centerY + 300.0f);
	player->addListener(shared_from_this());
	player->setBounds(screenWidth, screenHeight);
	gameObjects.push_back(player);
	objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(player));

	this->mainCamera->setParent(player);

	// reset game stats
	score = 0;
	gameTime = 0;

}

void GameLogic::createRoadSegments()
{
	float centerX = screenWidth / 2.0f;
	float centerY = screenHeight / 2.0f;

	int roadCount = 5;
	float offsetY = 500.0f;
	std::vector<std::shared_ptr<GameObject>> roadGuards;
	for (int i = 0; i < roadCount; i++) {
		auto roadObjectsList = RoadSegment::create(collisionManager, centerX, centerY + offsetY - i * 720.0f, 1400.0f, 720.0f, roadCount);
		gameObjects.push_back(roadObjectsList[0]);
		objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(roadObjectsList[0]));
		gameObjects.push_back(roadObjectsList[1]);
		objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(roadObjectsList[1]));

		for (int i = 2; i < roadObjectsList.size(); i++) {
			roadGuards.push_back(roadObjectsList[i]);
		}
	}
	for (auto& obj : roadGuards) {
		gameObjects.push_back(obj);
		objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(obj));
	}
}

void GameLogic::createNPCs()
{
	float centerX = screenWidth / 2.0f;
	float centerY = screenHeight / 2.0f;

	int npcCount = 10;

	for (int i = 0; i < npcCount; i++) {
		auto npcObjectsList = TrafficBaseNPC::create(collisionManager, rng, centerX, centerY, 95.0f, 170.0f, 810.0f, 720.0f, 100.0f, 300.0f);
		for (auto& obj : npcObjectsList) {
			gameObjects.push_back(obj);
			objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(obj));
		}
	}
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

// Fabric access - safe with null checks
std::shared_ptr<class IFabric> GameLogic::getFabric() { return fabric; }
const std::shared_ptr<class IFabric> GameLogic::getFabric() const { return fabric; }

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



void GameLogic::onFuelEmpty() {
	SDL_Log("GameLogic: Fuel empty ? GAME OVER");
	currentState = GameState::GameOver;
}

void GameLogic::spawnFuelCanister()
{
	float centerX = screenWidth / 2.0f;

	float highestY = 999999999.0f;
	for (auto& obj : gameObjects) {
		if (obj->getType() == ObjectType::ROAD) {
			float y = obj->getWorldTransform().getY();
			if (y < highestY)
				highestY = y;
		}
	}

	float w = 80.0f;
	float h = 80.0f;

	auto fuel = std::make_shared<FuelCanister>(centerX, highestY, w, h, this);

	if (collisionManager)
		collisionManager->addCollider<BoxCollider>(fuel, w, h);

	gameObjects.push_back(fuel);
	objectAdapters.emplace_back(std::make_shared<GameObjectAdapter>(fuel));
}

void GameLogic::setFuelRecharged()
{
	isFuelRecharged = !isFuelRecharged;
}

void GameLogic::onPlayerEliminated()
{
	currentState = GameState::GameOver;
}







