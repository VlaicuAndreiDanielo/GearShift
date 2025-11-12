#include "Renderer.h"

Renderer::Renderer(int w, int h) : win(nullptr), rend(nullptr), width(w), height(h) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    win = SDL_CreateWindow("GearShift",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_SHOWN);

    rend = SDL_CreateRenderer(win, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer() {
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void Renderer::clear(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(rend, r, g, b, 255);
    SDL_RenderClear(rend);
}

void Renderer::present() {
    SDL_RenderPresent(rend);
}