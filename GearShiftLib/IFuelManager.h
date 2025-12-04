#pragma once

/// \brief Interfață pentru managerul de „fuel” (timp de joc / energie).
///
/// Este folosită de logica de joc pentru a verifica dacă runda se termină
/// din cauza epuizării timpului / combustibilului.
class IFuelManager
{
public:
    /// \brief Verifică dacă fuel-ul a fost epuizat.
    /// \return true dacă nu mai este fuel disponibil, false altfel.
    virtual bool isFinished() const = 0;

    /// \brief Obține timpul curent de fuel rămas.
    /// \return Timpul rămas (în secunde).
    virtual float getCurrentTime() const = 0;

    /// \brief Obține durata maximă de fuel.
    /// \return Timpul maxim (în secunde) configurat pentru rundă.
    virtual float getMaxTime() const = 0;

    /// \brief Destructor virtual necesar pentru folosirea prin pointer la interfață.
    virtual ~IFuelManager() = default;
};
