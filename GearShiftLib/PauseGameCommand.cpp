#include "PauseGameCommand.h"
#include <SDL2/SDL.h>

PauseGameCommand::PauseGameCommand(std::weak_ptr<IGame> gameLogic) : game(gameLogic) {}

bool PauseGameCommand::canExecute() const {
    if (auto gameShared = game.lock()) {
        auto state = gameShared->getState();
        // Can pause/resume if we're Playing or Paused
        return state == GameState::Playing || state == GameState::Paused;
    }
    return false;
}

void PauseGameCommand::execute() {
    if (auto gameShared = game.lock()) {
        auto currentState = gameShared->getState();
        
        if (currentState == GameState::Playing) {
            gameShared->pauseGame();
            SDL_Log("PauseGameCommand: Game paused");
        } else if (currentState == GameState::Paused) {
            gameShared->resumeGame();
            SDL_Log("PauseGameCommand: Game resumed");
        } else {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "PauseGameCommand: Cannot pause/resume in current state");
        }
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "PauseGameCommand: Game instance is expired");
    }
}

const char* PauseGameCommand::getDescription() const {
    return "Pause or resume the game";
}
