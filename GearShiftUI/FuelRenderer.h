#pragma once
#include "SpriteManager.h"
#include "IFuelManager.h"

/// \brief HUD pentru afișarea fuel-ului (timp de joc) + iconiță de canistră.
///
/// Desenează o bară de fundal, o zonă umplută proporțional cu
/// currentTime / maxTime și un sprite cu canistra de fuel lângă bară.
class FuelRenderer : public SpriteManager
{
public:
    /// \brief Creează un FuelRenderer cu poziție și dimensiune date.
    ///
    /// \param x Poziția X a colțului stânga-sus al barei.
    /// \param y Poziția Y a colțului stânga-sus al barei.
    /// \param w Lățimea barei.
    /// \param h Înălțimea barei.
    /// \param renderer Renderer-ul SDL folosit pentru desen și încărcat textură.
    FuelRenderer(int x, int y, int w, int h, SDL_Renderer* renderer);

    /// \brief Randează bara de fuel în funcție de starea managerului.
    ///
    /// \param manager Managerul de fuel (timp rămas / timp maxim).
    void render(std::shared_ptr<IFuelManager> manager);

    /// \brief Destructor – eliberează textura canistrei, dacă e încărcată.
    ~FuelRenderer();

private:
    SDL_Renderer* renderer; ///< Renderer-ul SDL folosit pentru desen.
    SDL_Rect      barRect;  ///< Rect pentru bara de fuel.

    SDL_Color bgColor;      ///< Culoarea de fundal a barei.
    SDL_Color fillColor;    ///< Culoarea porțiunii umplute.

    int       squareSize;   ///< Dimensiunea pătratului pentru iconiță.
    int       spacing;      ///< Spațierea dintre bară și iconiță.
    SDL_Rect  spriteSquare; ///< Rect pentru desenarea sprite-ului.

    const char* fuelSpritePath = "assets/images/FuelCanister.png"; ///< Calea spre sprite-ul de fuel.
    SDL_Texture* fuelTexture = nullptr;                             ///< Textura sprite-ului de fuel.
};
