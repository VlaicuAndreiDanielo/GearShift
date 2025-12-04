#pragma once
#include "IScoreManager.h"

/// \brief Manager simplu pentru scorul jucătorului.
///
/// Acumulează puncte în timp (de exemplu 10 puncte / secundă) și oferă
/// metode pentru resetarea și interogarea scorului curent.
class ScoreManager : public IScoreManager {
public:
    /// \brief Creează un ScoreManager cu scor inițial 0.
    ScoreManager();

    /// \brief Destructor virtual default.
    ~ScoreManager() = default;

    /// \brief Actualizează scorul în funcție de timpul scurs.
    ///
    /// \param dt Timpul scurs de la ultimul frame (în secunde).
    void update(float dt);

    /// \brief Resetează scorul la 0 și golește accumulator-ul intern.
    void reset();

    /// \brief Obține scorul curent.
    /// \return Scorul curent al jucătorului.
    int getScore() override;

private:
    int   score;        ///< Scorul curent.
    float accumulator;  ///< Acumulator de timp pentru incrementarea scorului.
};
