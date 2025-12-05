#pragma once
#include "ICommand.h"

/**
 * Command to exit the application
 * Sends SDL_QUIT event to terminate the program
 */
class ExitApplicationCommand : public ICommand {
public:
    void execute() override;
    
    const char* getDescription() const override;
};