#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/// \brief Renderer HUD pentru afișarea scorului jucătorului.
///
/// Folosește SDL_ttf pentru a randa text de forma "Score: <valoare>"
/// în colțul din dreapta sus al ecranului.
class ScoreRenderer {
public:
    /// \brief Creează un ScoreRenderer asociat cu un SDL_Renderer.
    ///
    /// Încarcă fontul și pregătește textura internă pentru scorul 0.
    ///
    /// \param renderer Renderer-ul SDL folosit la desenarea textului.
    ScoreRenderer(SDL_Renderer* renderer);

    /// \brief Destructor – eliberează textura și invalidază pointerul la font.
    ~ScoreRenderer();

    /// \brief Randează scorul curent pe ecran.
    ///
    /// Intern, actualizează textura dacă scorul s-a schimbat.
    ///
    /// \param scoreManager Managerul care furnizează scorul curent.
    void render(std::shared_ptr<class IScoreManager> scoreManager);
private:
    SDL_Renderer* renderer; ///< Renderer-ul folosit la desen.
    TTF_Font* font;     ///< Fontul folosit pentru text.

    SDL_Color   color;      ///< Culoarea textului.
    SDL_Texture* texture;   ///< Textura textului curent.
    SDL_Rect     rect;      ///< Zona în care se randează scorul.

    /// \brief Flag pentru a preveni double-cleanup în destructor.
    bool cleanedUp;

    /// \brief Recreează textura pentru noul scor.
    ///
    /// \param score Scorul care trebuie afișat.
    void updateTexture(int score);
};
