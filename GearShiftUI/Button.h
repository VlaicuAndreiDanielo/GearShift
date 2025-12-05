#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <functional>
#include <memory>

// Forward declaration
class ICommand;

class Btn {
private:
    SDL_Rect rect;
    std::string txt;
    SDL_Texture* tex;
    SDL_Color norm;
    SDL_Color hover;
    bool isHover;
    std::shared_ptr<ICommand> command;
    std::function<void()> onClick; // Keep for backward compatibility
    
    // Cleanup flag to prevent double-cleanup
    bool cleanedUp;

public:
    Btn(SDL_Renderer* rend, TTF_Font* font, const std::string& text,
        int x, int y, int w, int h);
    ~Btn();

    void update(int mx, int my);
    void handleClick(int mx, int my);
    void render(SDL_Renderer* rend);
    
    // New command-based interface
    void setCommand(std::shared_ptr<ICommand> cmd) { command = cmd; }
    
    // Legacy interface for backward compatibility
    void setClick(std::function<void()> cb) { onClick = cb; }
    
    bool contains(int x, int y) const;
};