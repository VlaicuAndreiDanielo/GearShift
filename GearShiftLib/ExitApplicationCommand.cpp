#include "ExitApplicationCommand.h"
#include <SDL2/SDL.h>

void ExitApplicationCommand::execute() {
    SDL_Log("ExitApplicationCommand: Initiating application exit");
    
    SDL_Event quitEvent;
    quitEvent.type = SDL_QUIT;
    
    if (SDL_PushEvent(&quitEvent) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ExitApplicationCommand: Failed to push quit event: %s", SDL_GetError());
    } else {
        SDL_Log("ExitApplicationCommand: Quit event pushed successfully");
    }
}

const char* ExitApplicationCommand::getDescription() const {
    return "Exit the application safely";
}
