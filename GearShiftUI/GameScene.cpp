#include "GameScene.h"
#include "GameOverScene.h"
#include "FuelRenderer.h"
#include "IScoreManager.h"
#include "../GearShiftLib/CommandManager.h"
#include "../GearShiftLib/PauseGameCommand.h"

GameScene::GameScene(Renderer* rend, SceneMgr* mgr, std::weak_ptr<IGame> logic, InputHandler* input, std::shared_ptr<CommandManager> globalCommandMgr)
	: renderer(rend), sceneMgr(mgr), game(logic), inputHandler(input), font(nullptr),
	commandMgr(globalCommandMgr) {
}

void GameScene::onEnter() {  
   if (!renderer || game.expired()) {  
       SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameScene: Missing renderer or gameLogic");  
       return;  
   }  

   // Setup command system  
   setupCommands();  

   objectRenderer = std::make_unique<ObjectRenderer>(renderer->getSDLRenderer());  
   fuelRenderer = std::make_unique<FuelRenderer>(850, 20, 300, 20, renderer->getSDLRenderer());  
   scoreRenderer = std::make_unique<ScoreRenderer>(renderer->getSDLRenderer());  

   // Initialize font for paused text  
   if (TTF_WasInit() == 0) {  
       if (TTF_Init() == -1) {  
           SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed: %s", TTF_GetError());  
       }  
   }  
   font = TTF_OpenFont("assets/fonts/VipnagorgiallaBd.otf", 72);  
   if (!font) {  
       SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font for paused text: %s", TTF_GetError());  
   }  

   // Setup input command bindings  
   if (inputHandler && commandMgr) {  
       inputHandler->bindKeyToCommand(SDL_SCANCODE_P, "pause_game");  
       inputHandler->bindKeyToCommand(SDL_SCANCODE_ESCAPE, "pause_game");  
   }  

   SDL_Log("GameScene: Entered and initialized rendering components");  
}

void GameScene::onExit() {
	objectRenderer.reset();

	if (font) {
		SDL_Log("GameScene: Setting font pointer to null (avoiding TTF_CloseFont crash)");
		// Don't call TTF_CloseFont to avoid access violation
		font = nullptr;
	}

	if (auto gameShared = game.lock()) {
		gameShared->endGame();
	}

	SDL_Log("GameScene: Exited and cleaned up rendering components");
}

void GameScene::handleEvent(SDL_Event& e) {
	if (inputHandler) {
		inputHandler->update(e);
	}
}

void GameScene::update(float dt) {
	if (inputHandler) {
		inputHandler->updateKeyboard();
		
		// Execute any input commands (like pause)
		inputHandler->executeKeyCommands();

		if (auto gameShared = game.lock()) {
			gameShared->update(dt, *inputHandler);
		}
	}

	if (auto gameShared = game.lock()) {
		if (gameShared->getState() == GameState::GameOver) {

			int finalScore = gameShared->getScoreManager()->getScore();

			if (auto gameOverScene = sceneMgr->getScene("GameOver")) {
				auto gos = std::dynamic_pointer_cast<GameOverScene>(gameOverScene);
				if (gos) {
					gos->setFinalScore(finalScore);
				}
			}

			SDL_Log("GameScene: Switching to GameOver scene");
			sceneMgr->change("GameOver");
			return;
		}
	}
}

void GameScene::render() {
	if (!renderer) return;

	SDL_Renderer* sdlRend = renderer->getSDLRenderer();

	renderer->clear(0, 0, 0);

	if (auto gameShared = game.lock()) {
		auto objs = gameShared->getGameObjects();
		for (const auto& obj : objs) {
			if (obj && obj->isActive() && objectRenderer) {
				objectRenderer->render(obj);
			}
		}
		if (fuelRenderer) fuelRenderer->render(gameShared->getFuelManager());
		if (scoreRenderer) scoreRenderer->render(gameShared->getScoreManager());
	}


	// Render "Paused" text if game is paused
	if (auto gameShared = game.lock()) {
		if (gameShared->getState() == GameState::Paused) {
			renderPausedText();
		}
	}

	renderer->present();
}


void GameScene::renderPausedText() {
	if (!font || !renderer) return;

	SDL_Renderer* sdlRend = renderer->getSDLRenderer();

	// Create semi-transparent overlay
	SDL_SetRenderDrawBlendMode(sdlRend, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdlRend, 0, 0, 0, 180);
	SDL_Rect fullScreen{ 0, 0, 1920, 1080 };
	SDL_RenderFillRect(sdlRend, &fullScreen);

	// Render "PAUSED" text
	SDL_Color white{ 255, 255, 255, 255 };
	SDL_Surface* surf = TTF_RenderText_Blended(font, "PAUSED", white);
	if (!surf) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render paused text failed: %s", TTF_GetError());
		return;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(sdlRend, surf);
	if (!tex) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "CreateTexture for paused text failed: %s", SDL_GetError());
		SDL_FreeSurface(surf);
		return;
	}

	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);

	// Center the text on screen
	SDL_Rect dst{
		(1920 - w) / 2,
		(1080 - h) / 2,
		w, h
	};

	SDL_RenderCopy(sdlRend, tex, NULL, &dst);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(surf);
}

void GameScene::setupCommands() {
	if (!commandMgr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GameScene: CommandManager not initialized");
		return;
	}

	// Register pause/resume command
	auto pauseCmd = std::make_shared<PauseGameCommand>(game);
	commandMgr->registerCommand("pause_game", pauseCmd);
	
	SDL_Log("GameScene: Commands setup completed");
}

