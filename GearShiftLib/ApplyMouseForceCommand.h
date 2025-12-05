#pragma once
#include "ICommand.h"
#include "IGame.h"
#include <memory>

/**
 * Command to handle mouse force application
 * Used for fabric physics interaction
 */
class ApplyMouseForceCommand : public ICommand {
private:
    std::weak_ptr<IGame> game;
    int mouseX, mouseY;
    bool pressed;
    
public:
    ApplyMouseForceCommand(std::weak_ptr<IGame> gameLogic, int x, int y, bool isPressed);
    
    bool canExecute() const override;
    void execute() override;
    
    const char* getDescription() const override;
};