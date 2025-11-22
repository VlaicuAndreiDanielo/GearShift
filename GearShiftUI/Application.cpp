#include "Application.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameLogic.h"
#include "GameOverScene.h"

Application::Application()
	: running(false), lastTime(0) {
	initializeComponents();
	initializeScenes();
}

Application::~Application() {
	// Resources are automatically cleaned up via smart pointers
}

void Application::initializeComponents() {
	// Create renderer
	renderer = std::make_unique<Renderer>(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create game logic
	gameLogic = GameLogic::create(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create input handler
	inputHandler = std::make_unique<InputHandler>();

	SDL_Log("Application: Core components initialized");
}

void Application::initializeScenes() {
	// Create menu scene with shared resources
	auto menuScene = std::make_shared<MenuScene>(
		renderer.get(), &sceneMgr, gameLogic, inputHandler.get()
	);
	if (!menuScene) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Application: Failed to create menu scene");
		return;
	}

	// Create game scene with shared resources
	auto gameScene = std::make_shared<GameScene>(
		renderer.get(), &sceneMgr, gameLogic, inputHandler.get()
	);
	if (!gameScene) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Application: Failed to create game scene");
		return;
	}

	auto gameOverScene = std::make_shared<GameOverScene>(
		renderer.get(), &sceneMgr
	);

	// Register scenes with manager (first scene will auto-initialize via onEnter)
	sceneMgr.add("Menu", menuScene);
	sceneMgr.add("Game", gameScene);
	sceneMgr.add("GameOver", gameOverScene);

	SDL_Log("Application: All scenes registered");
}

void Application::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
			SDL_Log("Application: Quit requested");
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F11) {
			// TODO: Toggle fullscreen to see the logs
		}

		// Forward all events to current scene for handling
		sceneMgr.handleEvent(event);
	}
}

void Application::update(float dt) {
	// Limit delta time to prevent huge jumps (good practice when something goes wrong)
	if (dt > MAX_DELTA_TIME) {
		dt = MAX_DELTA_TIME;
	}

	// Update current scene
	sceneMgr.update(dt);
}

void Application::render() {
	// Render current scene
	sceneMgr.render();
}

void Application::run() {
	running = true;
	lastTime = SDL_GetTicks();

	while (running) {
		// Handle events
		handleEvents();

		// Calculate delta time
		Uint32 currentTime = SDL_GetTicks();
		float dt = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		// Update and render
		update(dt);
		render();
	}

	SDL_Log("Application: Shutting down");
}
