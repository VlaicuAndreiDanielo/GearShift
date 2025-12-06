#include "ApplyMouseForceCommand.h"
#include <SDL2/SDL.h>

ApplyMouseForceCommand::ApplyMouseForceCommand(std::weak_ptr<IGame> gameLogic, int x, int y, bool isPressed)
    : game(gameLogic), mouseX(x), mouseY(y), pressed(isPressed) {}

bool ApplyMouseForceCommand::canExecute() const {

    if (auto gameShared = game.lock()) {
        return mouseX >= 0 && mouseY >= 0;
    }
    return false;
}

void ApplyMouseForceCommand::execute() {
    if (auto gameShared = game.lock()) {
        gameShared->applyMouseForce(mouseX, mouseY, pressed);
        SDL_Log("ApplyMouseForceCommand: Applied mouse force at (%d, %d), pressed: %s", 
                mouseX, mouseY, pressed ? "true" : "false");
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ApplyMouseForceCommand: Game instance is expired");
    }
}

const char* ApplyMouseForceCommand::getDescription() const {
    return "Apply mouse force to fabric physics";
}
