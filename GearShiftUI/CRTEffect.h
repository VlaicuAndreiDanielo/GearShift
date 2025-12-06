#pragma once
#include <SDL2/SDL.h>

/// \brief Efect vizual tip CRT (scanlines, radial warp, flicker) peste scenă.
///
/// Randează scena într-o textură off-screen și apoi aplică:
///  - deformare tip „pincushion” (warp spre exterior);
///  - scanlines animate;
///  - glow / noise / flicker subtil.
class CRT {
private:
    SDL_Texture* tex; ///< Textura off-screen folosită ca target intermediar.
    int   w, h;       ///< Dimensiunea ecranului (în pixeli).
    float scanInt;    ///< Intensitatea scanlines.
    float curve;      ///< Factorul de curbură pentru distorsiune.
    float time;       ///< Timp acumulat pentru animațiile efectului.

    /// \brief Aplică distorsiunea „pincushion” peste textura curentă.
    ///
    /// Probează texela din tex și o desenează pe un grid sampleStep x sampleStep,
    /// curbat radial în funcție de distanța față de centru.
    void applyPincushionDistortion(SDL_Renderer* rend);

public:
    /// \brief Creează un efect CRT pentru un ecran cu dimensiunile date.
    ///
    /// \param rend Renderer-ul SDL folosit pentru a crea textura off-screen.
    /// \param width Lățimea ecranului.
    /// \param height Înălțimea ecranului.
    CRT(SDL_Renderer* rend, int width, int height);

    /// \brief Destructor – eliberează textura internă.
    ~CRT();

    /// \brief Începe capturarea scenei în textura CRT.
    ///
    /// Setează render target-ul SDL la textura internă.
    void begin(SDL_Renderer* rend);

    /// \brief Aplică efectul CRT și randează rezultatul pe ecran.
    ///
    /// Setează target-ul înapoi la ecran, aplică warp + scanlines +
    /// glow + noise, apoi compune rezultatul final.
    void end(SDL_Renderer* rend);

    /// \brief Actualizează timpul intern al efectului.
    /// \param dt Timpul scurs de la ultimul frame (secunde).
    void update(float dt);

    /// \brief Setează intensitatea scanlines.
    void setScanInt(float i) { scanInt = i; }

    /// \brief Setează factorul de curbură pentru distorsiune.
    void setCurve(float c) { curve = c; }
};
