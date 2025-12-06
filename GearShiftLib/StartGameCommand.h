#pragma once
#include "ICommand.h"
#include "IGame.h"
#include <memory>

/// \brief Command pentru pornirea unei runde noi de joc.
///
/// Verifică dacă jocul se află în starea \c GameState::Menu în \c canExecute()
/// și, la \c execute(), apelează \c IGame::startGame(). Scene transitions
/// și logica UI sunt tratate separat.
class StartGameCommand : public ICommand {
private:
    /// \brief Referință slabă către instanța de joc asupra căreia operează.
    std::weak_ptr<IGame> game;

public:
    /// \brief Creează o comandă de start game pentru un joc dat.
    ///
    /// \param gameLogic Jocul asupra căruia se va executa comanda.
    StartGameCommand(std::weak_ptr<IGame> gameLogic);

    /// \brief Verifică dacă jocul poate fi pornit.
    ///
    /// Comanda este executabilă doar dacă jocul există și se află în starea Menu.
    bool canExecute() const override;

    /// \brief Pornește jocul dacă este într-o stare validă.
    ///
    /// Apelează \c IGame::startGame() și loghează rezultatul în SDL log.
    void execute() override;

    /// \brief Descriere textuală a comenzii (pentru logging / debugging).
    const char* getDescription() const override;
};
