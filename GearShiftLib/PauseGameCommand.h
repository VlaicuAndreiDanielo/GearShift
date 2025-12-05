#pragma once
#include "ICommand.h"
#include "IGame.h"
#include <memory>

/**
 * Command to pause/resume the game
 * Toggles between Playing and Paused states
 */
class PauseGameCommand : public ICommand {
private:
    std::weak_ptr<IGame> game;
    
public:
    PauseGameCommand(std::weak_ptr<IGame> gameLogic);
    
    bool canExecute() const override;
    void execute() override;
    
    const char* getDescription() const override;
};