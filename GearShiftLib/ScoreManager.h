#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class ScoreManager {
public:
    ScoreManager(SDL_Renderer* renderer);
    ~ScoreManager();

    void update(float dt);
    void render();
    void reset();
	int getScore() { return score; }

private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    int score;
    float accumulator;

    SDL_Color color;
    SDL_Texture* texture;
    SDL_Rect rect;

    void updateTexture();
};