#include "WaveEffect.h"
#include <cmath>
//just dont ask about the wave effect  and how it works
Wave::Wave(int w, int h, int tileSize)
    : size(tileSize), speed(1.5f), amp(40.0f) {

    for (int y = -tileSize * 2; y < h + tileSize * 2; y += size) {
        for (int x = -tileSize * 2; x < w + tileSize * 2; x += size) {
            Tile t;
            t.x = x;
            t.y = y;
            t.z = 0;

            bool dark = ((x / size) + (y / size)) % 2 == 0;
            t.col = dark ? SDL_Color{ 100, 50, 50, 255 } : SDL_Color{ 200, 180, 100, 255 };
            tiles.push_back(t);
        }
    }
}

void Wave::update(float dt, float time) {
    for (auto& t : tiles) {
        float dist = (t.x + t.y) * 0.008f;
        float wave1 = std::sin(time * speed + dist) * amp;
        float wave2 = std::cos(time * speed * 0.7f + dist * 1.3f) * amp * 0.5f;
        t.z = wave1 + wave2;
    }
}

void Wave::render(SDL_Renderer* rend, const std::vector<Pt>& pts, int fw, int fh) {
    for (const auto& t : tiles) {
        int fx = (t.x + 32) / 16;
        int fy = (t.y + 32) / 16;

        if (fx >= 0 && fx < fw && fy >= 0 && fy < fh) {
            const Pt& p = pts[fy * fw + fx];

            float ox = p.x - (fx * 16);
            float oy = p.y - (fy * 16);

            SDL_Rect r = {
                t.x + (int)ox,
                t.y + (int)oy + (int)t.z,
                size, size
            };

            float bright = 1.0f + (t.z / amp) * 0.5f;
            bright = std::max(0.3f, std::min(1.5f, bright));

            SDL_SetRenderDrawColor(rend,
                (Uint8)(t.col.r * bright),
                (Uint8)(t.col.g * bright),
                (Uint8)(t.col.b * bright),
                t.col.a);

            SDL_RenderFillRect(rend, &r);
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 100);
            SDL_RenderDrawRect(rend, &r);
        }
    }
}

void Wave::loadImg(const char* path) {
}