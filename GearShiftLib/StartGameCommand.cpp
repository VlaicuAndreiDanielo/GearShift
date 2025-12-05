#include "StartGameCommand.h"
#include <SDL2/SDL.h>

StartGameCommand::StartGameCommand(std::weak_ptr<IGame> gameLogic) 
    : game(gameLogic) {}

bool StartGameCommand::canExecute() const {
    if (auto gameShared = game.lock()) {
        // Can only start game if we're in Menu state
        return gameShared->getState() == GameState::Menu;
    }
    return false;
}

void StartGameCommand::execute() {
    if (auto gameShared = game.lock()) {
        gameShared->startGame();
        SDL_Log("StartGameCommand: Game started successfully");
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "StartGameCommand: Game instance is expired");
    }
}

const char* StartGameCommand::getDescription() const {
    return "Start new game";
}
