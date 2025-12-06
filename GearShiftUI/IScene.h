#pragma once
#include <string>
#include <SDL2/SDL.h>

/// \brief Interfață pentru o scenă din joc (meniu, joc, game over etc.).
///
/// Scenele sunt gestionate de `SceneMgr` și reprezintă stări distincte
/// ale aplicației (Main Menu, Game, GameOver...).
class IScene {
public:
    /// \brief Destructor virtual necesar pentru folosirea prin pointer la interfață.
    virtual ~IScene() = default;

    /// \brief Actualizează logica scenei pentru un frame.
    /// \param dt Timpul scurs de la ultimul frame (secunde).
    virtual void update(float dt) = 0;

    /// \brief Randează conținutul scenei pe ecran.
    virtual void render() = 0;

    /// \brief Procesează un eveniment SDL (input).
    /// \param e Evenimentul SDL ce trebuie tratat.
    virtual void handleEvent(SDL_Event& e) = 0;

    /// \brief Numele scenei (folosit de SceneMgr pentru identificare).
    virtual std::string getName() const = 0;

    /// \brief Se apelează când scena devine activă.
    ///
    /// Ideal pentru inițializare / încărcare resurse.
    virtual void onEnter() = 0;

    /// \brief Se apelează când scena devine inactivă.
    ///
    /// Ideal pentru cleanup / salvare stare.
    virtual void onExit() = 0;
};
