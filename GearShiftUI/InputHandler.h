#pragma once
#include "../GearShiftLib/IInputState.h"
#include <SDL2/SDL.h>



class InputHandler : public IInputState {
private:
    const Uint8* keyState;
    int mouseX, mouseY;
    bool mousePressed;
	bool pausePressedLastFrame = false;

public:
    InputHandler();


    void update(SDL_Event& e);
    void updateKeyboard();

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