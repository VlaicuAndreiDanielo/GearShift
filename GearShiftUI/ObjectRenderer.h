#pragma once
#include <SDL2/SDL.h>
#include "IGameObject.h"
#include "SpriteManager.h"
#include <memory>

/// \brief Renderer pentru un singur obiect de joc.
///
/// Desenează mai întâi un dreptunghi colorat (hitbox / fundal) și apoi
/// sprite-ul asociat, obținut prin `SpriteManager` și `SpriteMapper`.
class ObjectRenderer {
public:
    /// \brief Creează un ObjectRenderer legat de un SDL_Renderer.
    /// \param renderer Renderer-ul SDL folosit pentru desen.
    ObjectRenderer(SDL_Renderer* renderer);

    /// \brief Destructor.
    ~ObjectRenderer();

    /// \brief Randează un obiect de joc.
    ///
    /// 1. Desenează un dreptunghi de culoare configurată;
    /// 2. Desenează sprite-ul mapat la `object->getSprite()` peste acel rect.
    ///
    /// \param object Obiectul de randat (IGameObject adaptor).
    void render(const std::shared_ptr<IGameObject> object);

    /// \brief Setează culoarea dreptunghiului de fundal.
    ///
    /// \param r Componenta roșu (0–255).
    /// \param g Componenta verde (0–255).
    /// \param b Componenta albastru (0–255).
    void setColor(Uint8 r, Uint8 g, Uint8 b);

private:
    SDL_Color     color;         ///< Culoarea dreptunghiului de fundal.
    SpriteManager spriteManager; ///< Manager de texturi pentru sprite-uri.
    SDL_Renderer* renderer;      ///< Renderer-ul SDL folosit pentru desen.
};
