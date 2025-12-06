#pragma once
#include "ICommand.h"
#include "IGame.h"
#include <memory>

/// \brief Command pentru pauzarea / reluarea jocului.
///
/// Dacă jocul este în starea \c GameState::Playing, comanda îl pune pe pauză.
/// Dacă este în \c GameState::Paused, comanda reia jocul. În alte stări nu are efect.
class PauseGameCommand : public ICommand {
private:
    /// \brief Referință slabă către instanța de joc.
    std::weak_ptr<IGame> game;

public:
    /// \brief Creează o comandă de pauză pentru un joc dat.
    ///
    /// \param gameLogic Jocul asupra căruia se aplică pauza / resume-ul.
    PauseGameCommand(std::weak_ptr<IGame> gameLogic);

    /// \brief Verifică dacă jocul se află într-o stare în care se poate pauza / relua.
    ///
    /// Comanda este executabilă dacă starea este Playing sau Paused.
    bool canExecute() const override;

    /// \brief Pune jocul pe pauză sau îl reia, în funcție de starea curentă.
    void execute() override;

    /// \brief Descriere textuală a comenzii.
    const char* getDescription() const override;
};
