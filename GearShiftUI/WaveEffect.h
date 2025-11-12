#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "../GearShiftLib/FabricPhysics.h"

struct Tile {
    int x, y;
    float z;
    SDL_Color col;
};

class Wave {
private:
    std::vector<Tile> tiles;
    int size;
    float speed;
    float amp;

public:
    Wave(int w, int h, int tileSize);

    void update(float dt, float time);
    void render(SDL_Renderer* rend, const std::vector<Pt>& pts, int fw, int fh);
    void loadImg(const char* path);
};