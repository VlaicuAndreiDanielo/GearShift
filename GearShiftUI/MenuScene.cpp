#include "MenuScene.h"


MenuScene::MenuScene(Renderer* rend, SceneMgr* mgr, std::weak_ptr<IGame> logic, InputHandler* input)
	: renderer(rend), sceneMgr(mgr), game(logic), inputHandler(input),
	font(nullptr), carTexture(nullptr) {
}

MenuScene::~MenuScene() {
	onExit();  // Ensure cleanup happens
}

void MenuScene::onEnter() {
	// Validate required components
	if (!renderer || game.expired() || !inputHandler) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "MenuScene: Missing required component (renderer, gameLogic, or inputHandler)");
		return;
	}

	SDL_Renderer* sdlRend = renderer->getSDLRenderer();
	int w = renderer->getWidth();
	int h = renderer->getHeight();

	// Create visual effects
	crt = std::make_unique<CRT>(sdlRend, w, h);
	wave = std::make_unique<Wave>(w, h, 32);

	// Load font with fallback paths
	font = TTF_OpenFont("arial.ttf", 32);
	if (!font) {
		font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 32);
	}
	if (!font) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "MenuScene: Failed to load font - button text will not render");
	}

	// Create play button (can work without font, will render with fallback color)
	playBtn = std::make_unique<Btn>(sdlRend, font, "PLAY",
		w / 2 - 120, h / 2 + 200, 240, 70);

	if (!playBtn) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "MenuScene: Failed to create play button");
		return;
	}

	// Set button callback to transition to game
	playBtn->setClick([this]() {
		if (auto gameShared = game.lock()) {
			gameShared->startGame();
		}
		if (sceneMgr) {
			sceneMgr->change("Game");
		}
		});

	// Create exit button below the play button
	exitBtn = std::make_unique<Btn>(sdlRend, font, "EXIT",
		w / 2 - 120, h / 2 + 290, 240, 70);

	if (!exitBtn) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "MenuScene: Failed to create exit button");
		return;
	}

	// Set button callback to exit the application
	exitBtn->setClick([this]() {
		SDL_Event quitEvent;
		quitEvent.type = SDL_QUIT;
		SDL_PushEvent(&quitEvent);
		});


	// Load car menu sprite
	SDL_Surface* carSurf = nullptr;
	const char* paths[] = {
		   "assets/images/car_menu.png",
		   "../assets/images/car_menu.png",
		"../../assets/images/car_menu.png"
	};

	for (const char* path : paths) {
		carSurf = IMG_Load(path);
		if (carSurf) {
			SDL_Log("MenuScene: Car texture loaded from '%s'", path);
			break;
		}
	}

	if (carSurf) {
		carTexture = SDL_CreateTextureFromSurface(sdlRend, carSurf);
		SDL_FreeSurface(carSurf);
		if (!carTexture) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "MenuScene: Failed to create car texture");
		}
	}
	else {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "MenuScene: Car texture file not found - placeholder will be drawn");
	}

	// Position car sprite
	carRect = { w / 2 - 200, h / 2 - 100, 400, 180 };

	SDL_Log("MenuScene: Entered and initialized");
}

void MenuScene::onExit() {
	// Clean up resources in reverse order of creation
	exitBtn.reset();
	playBtn.reset();
	wave.reset();
	crt.reset();

	if (carTexture) {
		SDL_DestroyTexture(carTexture);
		carTexture = nullptr;
	}

	if (font) {
		TTF_CloseFont(font);
		font = nullptr;
	}

	SDL_Log("MenuScene: Exited and cleaned up");
}

void MenuScene::handleEvent(SDL_Event& e) {
	// Forward input event to handler
	if (inputHandler) {
		inputHandler->update(e);
	}

	// Handle button events
	if (playBtn) {
		if (e.type == SDL_MOUSEMOTION) {
			playBtn->update(e.motion.x, e.motion.y);
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			playBtn->handleClick(e.motion.x, e.motion.y);
		}
	}

	if (exitBtn) {
		if (e.type == SDL_MOUSEMOTION) {
			exitBtn->update(e.motion.x, e.motion.y);
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			exitBtn->handleClick(e.motion.x, e.motion.y);
		}
	}
}

void MenuScene::update(float dt) {
	// Refresh keyboard state
	if (inputHandler) {
		inputHandler->updateKeyboard();
	}

	// Update game logic fabric physics
	if (auto gameShared = game.lock()) {
		gameShared->update(dt, *inputHandler);

		// Apply mouse force for visual effect
		if (inputHandler && inputHandler->isMousePressed()) {
			gameShared->applyMouseForce(
				inputHandler->getMouseX(),
				inputHandler->getMouseY(),
				true
			);
		}
	}



	// Update CRT effect
	if (crt) {
		crt->update(dt);
	}
}

void MenuScene::render() {
	if (!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "MenuScene: Renderer is null in render");
		return;
	}

	SDL_Renderer* sdlRend = renderer->getSDLRenderer();

	// Begin CRT rendering
	if (crt) {
		crt->begin(sdlRend);
	}

	// Clear background with dark color
	SDL_SetRenderDrawColor(sdlRend, 15, 8, 8, 255);
	SDL_RenderClear(sdlRend);

	// Render wave background
	if (auto gameShared = game.lock()) {
		if (wave && gameShared->getFabric()) {
			wave->update(0.016f, gameShared->getTime());
			wave->render(sdlRend, gameShared->getFabric()->getPts(),
				gameShared->getFabric()->getW(), gameShared->getFabric()->getH());
		}
	}

	// Render car
	if (carTexture) {
		SDL_RenderCopy(sdlRend, carTexture, nullptr, &carRect);
	}
	else {
		// Draw placeholder rectangle if texture failed to load
		SDL_SetRenderDrawColor(sdlRend, 255, 0, 0, 255);
		SDL_RenderFillRect(sdlRend, &carRect);
	}

	// Render button
	if (playBtn) {
		playBtn->render(sdlRend);
	}

	if (exitBtn) {
		exitBtn->render(sdlRend);
	}

	// End CRT rendering
	if (crt) {
		crt->end(sdlRend);
	}

	if (renderer) {
		renderer->present();
	}
}