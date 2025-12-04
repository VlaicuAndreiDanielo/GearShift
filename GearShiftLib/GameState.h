#pragma once

/// \brief Stările principale ale jocului.
///
/// Sunt folosite de GameLogic pentru a decide ce se întâmplă la fiecare update
/// (meniu, joc activ, pauză, ecran de Game Over).
enum class GameState {
    Menu,      ///< Jocul se află în meniul principal.
    Playing,   ///< Jocul este în desfășurare (rundă activă).
    Paused,    ///< Jocul este pus pe pauză.
    GameOver   ///< Runda s-a încheiat (de ex. fuel 0 sau coliziune fatală).
};
