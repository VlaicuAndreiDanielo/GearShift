#pragma once



struct IInputState {
    virtual ~IInputState() = default;

    // movement input
    virtual bool isUpPressed() const = 0;
    virtual bool isDownPressed() const = 0;
    virtual bool isLeftPressed() const = 0;
    virtual bool isRightPressed() const = 0;

    // action input
    virtual bool isAcceleratePressed() const = 0;
    virtual bool isBrakePressed() const = 0;
    virtual bool isPausePressed() const = 0;

    // mouse input (for menu interactions)
    virtual int getMouseX() const = 0;
    virtual int getMouseY() const = 0;
    virtual bool isMousePressed() const = 0;
};