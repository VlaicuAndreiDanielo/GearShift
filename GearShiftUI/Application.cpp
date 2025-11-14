#include "Application.h"
#include "MenuScene.h"
#include "GameScene.h"

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
	gameLogic = std::make_unique<GameLogic>(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create input handler
	inputHandler = std::make_unique<InputHandler>();

	SDL_Log("Application: Core components initialized");
}

void Application::initializeScenes() {
	// Create scenes and pass shared resources
	auto menuScene = std::make_shared<MenuScene>(
		renderer.get(), &sceneMgr, gameLogic.get(), inputHandler.get()
	);
	auto gameScene = std::make_shared<GameScene>(
		renderer.get(), &sceneMgr, gameLogic.get(), inputHandler.get()
	);

	// Add scenes to manager
	sceneMgr.add("Menu", menuScene);
	sceneMgr.add("Game", gameScene);

	// Start with menu scene
	sceneMgr.change("Menu");

	SDL_Log("Application: Scenes initialized");
}

void Application::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F11) {
			// TODO: Toggle fullscreen to see the logs
		}

		// Forward events to current scene
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
