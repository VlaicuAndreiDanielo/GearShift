#pragma once
#include <SDL2/SDL.h>

class CRT {
private:
    SDL_Texture* tex;
    int w, h;
    float scanInt;
    float curve;
    float time;

    void applyPincushionDistortion(SDL_Renderer* rend);

public:
    CRT(SDL_Renderer* rend, int width, int height);
    ~CRT();

    void begin(SDL_Renderer* rend);
    void end(SDL_Renderer* rend);
    void update(float dt);

    void setScanInt(float i) { scanInt = i; }
    void setCurve(float c) { curve = c; }
};