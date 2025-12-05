#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class ScoreRenderer {
public:
	ScoreRenderer(SDL_Renderer* renderer);
	~ScoreRenderer();
	void render(std::shared_ptr<class IScoreManager> scoreManager);
private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    SDL_Color color;
    SDL_Texture* texture;
    SDL_Rect rect;
    
    // Cleanup flag to prevent double-cleanup
    bool cleanedUp;

    void updateTexture(int score);
};

