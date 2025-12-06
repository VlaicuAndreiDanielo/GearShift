/**
 * \file Source.cpp
 * \brief Punctul de intrare pentru aplicația GearShift.
 *
 * Setează SDL_MAIN_HANDLED, expune hint-uri pentru folosirea plăcii video
 * dedicate și pornește bucla principală prin clasa Application.
 */

#define SDL_MAIN_HANDLED
#include "Application.h"
#include <SDL2/SDL.h>

extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main(int argc, char* argv[]) {
    Application app;
    app.run();
    return 0;
}
