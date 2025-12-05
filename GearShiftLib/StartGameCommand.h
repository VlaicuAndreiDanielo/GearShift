#pragma once
#include "ICommand.h"
#include "IGame.h"
#include <memory>

/**
 * Command to start a new game
 * Only handles game logic startup - scene transitions handled separately
 */
class StartGameCommand : public ICommand {
private:
    std::weak_ptr<IGame> game;
    
public:
    StartGameCommand(std::weak_ptr<IGame> gameLogic);
    
    bool canExecute() const override;
    void execute() override;
    
    const char* getDescription() const override;
};