#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class Renderer {
private:
    SDL_Window* win;
    SDL_Renderer* rend;
    int width;
    int height;

public:
    Renderer(int w, int h);
    ~Renderer();

    SDL_Renderer* getSDLRenderer() { return rend; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);
    void present();
};