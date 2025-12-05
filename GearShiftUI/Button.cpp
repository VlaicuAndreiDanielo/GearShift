#include "Button.h"
#include "../GearShiftLib/ICommand.h"

//A simple button can be changed TODO:needs look better 

Btn::Btn(SDL_Renderer* rend, TTF_Font* font, const std::string& text,
    int x, int y, int w, int h)
    : txt(text), isHover(false), tex(nullptr), cleanedUp(false) {

    rect = { x, y, w, h };
    norm = { 200, 180, 50, 255 };
    hover = { 255, 220, 80, 255 };

    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Surface* surf = TTF_RenderText_Blended(font, txt.c_str(), white);
    if (surf) {
        tex = SDL_CreateTextureFromSurface(rend, surf);
        SDL_FreeSurface(surf);
    }
}

Btn::~Btn() {
    if (cleanedUp) {
        return; // Already cleaned up
    }
    
    cleanedUp = true;
    SDL_Log("Button: Cleaning up texture");
    
    if (tex) {
        SDL_Log("Button: Setting texture pointer to null (avoiding SDL_DestroyTexture crash)");
        // Don't call SDL_DestroyTexture to avoid access violation
        // SDL will clean up texture resources automatically at program exit
        tex = nullptr;
    }
}

void Btn::update(int mx, int my) {
    isHover = contains(mx, my);
}

void Btn::handleClick(int mx, int my) {
    if (contains(mx, my)) {
        // Prefer command over function callback
        if (command) {
            command->execute();
        } else if (onClick) {
            onClick();
        }
    }
}

void Btn::render(SDL_Renderer* rend) {
    SDL_Color c = isHover ? hover : norm;
    SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(rend, &rect);

    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderDrawRect(rend, &rect);

    if (tex) {
        int tw, th;
        SDL_QueryTexture(tex, nullptr, nullptr, &tw, &th);
        SDL_Rect tr = {
            rect.x + (rect.w - tw) / 2,
            rect.y + (rect.h - th) / 2,
            tw, th
        };
        SDL_RenderCopy(rend, tex, nullptr, &tr);
    }
}

bool Btn::contains(int x, int y) const {
    return x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h;
}