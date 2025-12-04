#pragma once

/// \brief Interfață pentru managerul de scor.
///
/// Permite logici diferite de calcul al scorului (strategy) prin implementări
/// alternative care expun aceeași metodă de interogare.
class IScoreManager {
public:
    /// \brief Obține scorul curent.
    /// \return Scorul jucătorului calculat de implementarea concretă.
    virtual int getScore() = 0;

    /// \brief Destructor virtual necesar pentru folosirea prin pointer la interfață.
    virtual ~IScoreManager() = default;
};
