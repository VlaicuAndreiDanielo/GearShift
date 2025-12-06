#pragma once
#include "ICommand.h"
#include "IGame.h"
#include <memory>

/// \brief Command pentru aplicarea unei forțe de mouse asupra pânzei (fabric).
///
/// Este folosită pentru interacțiunea cu \c IFabric (efectul de cloth) din joc,
/// în funcție de poziția mouse-ului și dacă butonul este apăsat.
class ApplyMouseForceCommand : public ICommand {
private:
    std::weak_ptr<IGame> game; ///< Jocul asupra căruia se aplică forța.
    int  mouseX;               ///< Coordonata X a mouse-ului în fereastră.
    int  mouseY;               ///< Coordonata Y a mouse-ului în fereastră.
    bool pressed;              ///< True dacă butonul de mouse este apăsat.

public:
    /// \brief Creează o comandă de aplicare a forței de mouse.
    ///
    /// \param gameLogic Jocul asupra căruia se va aplica forța.
    /// \param x Coordonata X a mouse-ului.
    /// \param y Coordonata Y a mouse-ului.
    /// \param isPressed True dacă butonul de mouse este apăsat.
    ApplyMouseForceCommand(std::weak_ptr<IGame> gameLogic, int x, int y, bool isPressed);

    /// \brief Verifică dacă comanda poate fi executată.
    ///
    /// Comanda este executabilă dacă jocul există și coordonatele mouse-ului
    /// sunt valide (non-negative).
    bool canExecute() const override;

    /// \brief Aplică forța de mouse asupra pânzei jocului.
    ///
    /// Apelează \c IGame::applyMouseForce() și loghează în SDL log.
    void execute() override;

    /// \brief Descriere textuală a comenzii (pentru logging / debugging).
    const char* getDescription() const override;
};
