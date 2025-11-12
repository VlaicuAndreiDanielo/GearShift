#include "CRTEffect.h"
#include <cmath>

CRT::CRT(SDL_Renderer* rend, int width, int height)
    : w(width), h(height), scanInt(0.45f), curve(0.25f), time(0) {

    tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, w, h);
}

CRT::~CRT() {
    if (tex) SDL_DestroyTexture(tex);
}

void CRT::begin(SDL_Renderer* rend) {
    SDL_SetRenderTarget(rend, tex);
}

void CRT::end(SDL_Renderer* rend) {
    SDL_SetRenderTarget(rend, nullptr);

    applyPincushionDistortion(rend);

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

    // scanlines with slow scrolling ->  the effect that you see in the menu if someone reads the code  
    int scanlineOffset = static_cast<int>(time * 30.0f) % h;

    for (int y = 0; y < h; y += 3) {
        int actualY = (y + scanlineOffset) % h;

        float brightness = std::sin(time * 5.0f + y * 0.1f) * 0.15f + 0.85f;
        Uint8 a = static_cast<Uint8>(scanInt * 255 * brightness);

        SDL_SetRenderDrawColor(rend, 0, 0, 0, a);
        SDL_RenderDrawLine(rend, 0, actualY, w, actualY);
        SDL_RenderDrawLine(rend, 0, actualY + 1, w, actualY + 1);
    }

    //i dont remeber what it was used for but let it its for the crt effects
    float glowOffset = std::sin(time * 2.0f) * 2.0f;
    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_ADD);

    SDL_SetRenderDrawColor(rend, 20, 0, 0, 30);
    for (int i = 0; i < 3; i++) {
        SDL_Rect glowRect = { (int)glowOffset + i, 0, w, h };
        SDL_RenderDrawRect(rend, &glowRect);
    }

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

    // screen flickers -> can be deleted but its a minimal effect sometimes you see it sometimes you dont
    float flicker = std::sin(time * 120.0f) * 0.02f + 0.98f;
    if (flicker < 0.97f) {
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 10);
        SDL_Rect fullScreen = { 0, 0, w, h };
        SDL_RenderFillRect(rend, &fullScreen);
    }

    // horizontal noise lines -> the true crt 
    if (static_cast<int>(time * 100.0f) % 200 < 5) {
        int noiseY = static_cast<int>(time * 500.0f) % h;
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 40);
        for (int i = 0; i < 3; i++) {
            SDL_RenderDrawLine(rend, 0, noiseY + i, w, noiseY + i);
        }
    }
}

void CRT::applyPincushionDistortion(SDL_Renderer* rend) {
    // OUTWARD warp !!!
 

    const int sampleStep = 4;

    for (int y = 0; y < h; y += sampleStep) {
        for (int x = 0; x < w; x += sampleStep) {
            
            float nx = (x / (float)w) * 2.0f - 1.0f;
            float ny = (y / (float)h) * 2.0f - 1.0f;

            //  distance from center
            float dist = std::sqrt(nx * nx + ny * ny);

    
            // this pushes edges OUTWARD!~ dont mess with it it breaks the game 
            float distortion = 1.0f + curve * dist * dist;

            float warpedX = nx * distortion;  // MULTIPLY = outward !
            float warpedY = ny * distortion;

            // convert back to screen coordinates
            int srcX = (int)((warpedX + 1.0f) * 0.5f * w);
            int srcY = (int)((warpedY + 1.0f) * 0.5f * h);

            // only render if within bounds the fabric it has some outbounds these is for the black things on the edges if you need to mess with it 
            if (srcX >= 0 && srcX < w && srcY >= 0 && srcY < h) {
                SDL_Rect src = { srcX, srcY, sampleStep, sampleStep };
                SDL_Rect dst = { x, y, sampleStep, sampleStep };
                SDL_RenderCopy(rend, tex, &src, &dst);
            }
            else {
                // outside bounds = black 
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                SDL_Rect dst = { x, y, sampleStep, sampleStep };
                SDL_RenderFillRect(rend, &dst);
            }
        }
    }
}

void CRT::update(float dt) {
    time += dt;
}