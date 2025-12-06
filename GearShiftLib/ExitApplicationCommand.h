#pragma once
#include "ICommand.h"

/// \brief Command pentru ieșirea din aplicație.
///
/// Trimite un eveniment \c SDL_QUIT în coada de evenimente SDL, lăsând
/// bucla principală a aplicației să facă shut-down-ul controlat.
class ExitApplicationCommand : public ICommand {
public:
    /// \brief Execută comanda de ieșire din aplicație.
    ///
    /// Creează și împinge un eveniment SDL_QUIT în event queue.
    void execute() override;

    /// \brief Descriere textuală a comenzii.
    const char* getDescription() const override;
};
