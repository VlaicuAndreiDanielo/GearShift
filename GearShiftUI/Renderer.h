#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/// \brief Thin wrapper peste fereastra și renderer-ul SDL.
///
/// Se ocupă de inițializarea SDL (video, TTF, PNG), crearea ferestrei și a
/// renderer-ului hardware-accelerat, plus operațiile de clear/present.
class Renderer {
private:
    SDL_Window* win;   ///< Fereastra SDL.
    SDL_Renderer* rend;  ///< Renderer-ul SDL.
    int width;           ///< Lățimea ferestrei în pixeli.
    int height;          ///< Înălțimea ferestrei în pixeli.

public:
    /// \brief Creează fereastra și renderer-ul pentru dimensiunile date.
    ///
    /// \param w Lățimea ferestrei.
    /// \param h Înălțimea ferestrei.
    Renderer(int w, int h);

    /// \brief Destructor – distruge renderer-ul, fereastra și închide SDL.
    ~Renderer();

    /// \brief Obține pointerul brut la SDL_Renderer.
    SDL_Renderer* getSDLRenderer() { return rend; }

    /// \brief Obține lățimea ferestrei.
    int getWidth() const { return width; }

    /// \brief Obține înălțimea ferestrei.
    int getHeight() const { return height; }

    /// \brief Șterge backbuffer-ul cu culoarea dată.
    ///
    /// \param r Componenta roșu (0–255).
    /// \param g Componenta verde (0–255).
    /// \param b Componenta albastru (0–255).
    void clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);

    /// \brief Face swap la buffere și afișează conținutul pe ecran.
    void present();
};
