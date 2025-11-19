#include "GameScene.h"

GameScene::GameScene(Renderer* rend, SceneMgr* mgr, GameLogic* logic, InputHandler* input)
	: renderer(rend), sceneMgr(mgr), gameLogic(logic), inputHandler(input) {
}

void GameScene::onEnter() {
	// Validate required components
	if (!renderer || !gameLogic) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameScene: Missing required component (renderer or gameLogic)");
		return;
	}

	// Initialize rendering components for gameplay
	objectRenderer = std::make_unique<ObjectRenderer>(renderer->getSDLRenderer());
	fuelTimer = std::make_unique<FuelTimer>(10.0f, 850, 20, 300, 20, renderer->getSDLRenderer());

	if (!objectRenderer) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameScene: Failed to initialize player renderer");
	}

	// GameLogic state is initialized by MenuScene calling gameLogic->startGame()
	SDL_Log("GameScene: Entered and initialized rendering components");
}

void GameScene::onExit() {
	// Clean up rendering resources when leaving gameplay
	if (objectRenderer) {
		objectRenderer.reset();
	}

	SDL_Log("GameScene: Exited and cleaned up rendering components");
}

void GameScene::handleEvent(SDL_Event& e) {
	// Forward input events to the input handler
	if (inputHandler) {
		inputHandler->update(e);
	}

	// Handle menu escape key
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
		SDL_Log("GameScene: Escape key pressed, returning to menu");
		if (sceneMgr) {
			sceneMgr->change("Menu");
		}
	}
}

void GameScene::update(float dt) {
	// Refresh keyboard state for current frame
	if (inputHandler) {
		inputHandler->updateKeyboard();
	}

	// Update game logic with current input state
	if (gameLogic && inputHandler) {
		gameLogic->update(dt, *inputHandler);
	}
	fuelTimer->update(dt);
	if (fuelTimer->isFinished()) {
		SDL_Log("FuelTimer finished!");
	}
}

void GameScene::render() {
	if (!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameScene: Renderer is null in render");
		return;
	}

	SDL_Renderer* sdlRend = renderer->getSDLRenderer();

	// Clear background with dark color
	renderer->clear(20, 20, 30);

	if (gameLogic) {
		auto gameObjects = gameLogic->getGameObjects();
		for (const auto& obj : gameObjects) {
			if (obj && obj->isActive() && objectRenderer) {
				objectRenderer->render(obj);
			}
		}
	}

	// TODO: Render game HUD (speed, lap time, score, fuel, lives)
	fuelTimer->render(sdlRend);
	renderer->present();
}