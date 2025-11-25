#include "InputHandler.h"

InputHandler::InputHandler()
    : mouseX(0), mouseY(0), mousePressed(false) {
    keyState = SDL_GetKeyboardState(nullptr);
}

void InputHandler::update(SDL_Event& e) {
    if (e.type == SDL_MOUSEMOTION) {
        mouseX = e.motion.x;
        mouseY = e.motion.y;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN) {
        mousePressed = true;
    }
    else if (e.type == SDL_MOUSEBUTTONUP) {
        mousePressed = false;
    }
}

void InputHandler::updateKeyboard() {
    // called each frame to refresh keyboard 
    keyState = SDL_GetKeyboardState(nullptr);
}

bool InputHandler::isUpPressed() const {
    return keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP];
}

bool InputHandler::isDownPressed() const {
    return keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN];
}

bool InputHandler::isLeftPressed() const {
    return keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT];
}

bool InputHandler::isRightPressed() const {
    return keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT];
}

bool InputHandler::isAcceleratePressed() const {
    return keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP] ||
        keyState[SDL_SCANCODE_SPACE];
}

bool InputHandler::isBrakePressed() const {
    return keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN];
}

bool InputHandler::isPausePressed() {
    if (keyState[SDL_SCANCODE_ESCAPE] || keyState[SDL_SCANCODE_P]) {
        if (pausePressedLastFrame) return false;
        else {
            pausePressedLastFrame = true;
            return true;
        }
    }
    pausePressedLastFrame = false;
    return false;
}

int InputHandler::getMouseX() const {
    return mouseX;
}

int InputHandler::getMouseY() const {
    return mouseY;
}

bool InputHandler::isMousePressed() const {
    return mousePressed;
}

void InputHandler::reset() {
    mousePressed = false;
}