#pragma once
#include "SpriteManager.h"
#include "IFuelManager.h"

/// \brief Manager simplu pentru „combustibilul” rundei.
///
/// Ține evidența timpului de joc rămas (fuel), scade în timp și permite
/// verificarea când „rezervorul” este gol și jocul trebuie încheiat.
class FuelManager : public IFuelManager {
public:
    /// \brief Creează un manager de fuel cu o durată maximă dată.
    /// \param duration Durata maximă (în secunde) până când fuel-ul se epuizează.
    FuelManager(float duration);

    /// \brief Destructor virtual default.
    virtual ~FuelManager() = default;

    /// \brief Actualizează timpul de fuel rămas.
    ///
    /// Scade \p dt din timpul curent dacă încă mai este fuel.
    /// Nu permite scăderea sub 0.
    ///
    /// \param dt Timpul scurs de la ultimul frame (în secunde).
    void update(float dt);

    /// \brief Resetează fuel-ul la valoarea maximă.
    void reset();

    /// \brief Verifică dacă fuel-ul a fost epuizat.
    /// \return true dacă timpul a ajuns la 0 sau sub 0, false altfel.
    bool isFinished() const override;

    /// \brief Obține timpul curent de fuel rămas.
    /// \return Timpul rămas până la epuizarea fuel-ului.
    float getCurrentTime() const override;

    /// \brief Obține durata maximă de fuel.
    /// \return Timpul maxim (durata completă a rundei) configurat la început.
    float getMaxTime() const override;

private:
    float maxTime;      ///< Durata maximă de fuel (în secunde).
    float currentTime;  ///< Timpul curent rămas (în secunde).
};
