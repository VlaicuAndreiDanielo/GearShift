#pragma once
#include "../GearShiftLib/IInputState.h"
#include "../GearShiftLib/CommandManager.h"
#include <SDL2/SDL.h>
#include <memory>
#include <unordered_map>



class InputHandler : public IInputState {
private:
    const Uint8* keyState;
    int mouseX, mouseY;
    bool mousePressed;
	bool pausePressedLastFrame = false;
	
    // Command system integration
    std::shared_ptr<CommandManager> commandManager;
    std::unordered_map<SDL_Scancode, std::string> keyBindings;

public:
    InputHandler();
    ~InputHandler();

    void update(SDL_Event& e);
    void updateKeyboard();
    
    // Command system methods
    void setCommandManager(std::shared_ptr<CommandManager> cmdMgr) { commandManager = cmdMgr; }
    void bindKeyToCommand(SDL_Scancode key, const std::string& commandName);
    void executeKeyCommands(); // Check for key presses and execute bound commands

    // IInputState implementation -> i dont remember why it was needed or good but here it is 
    bool isUpPressed() const override;
    bool isDownPressed() const override;
    bool isLeftPressed() const override;
    bool isRightPressed() const override;

    bool isAcceleratePressed() const override;
    bool isBrakePressed() const override;
    bool isPausePressed() override;

    int getMouseX() const override;
    int getMouseY() const override;
    bool isMousePressed() const override;

    void reset();
};