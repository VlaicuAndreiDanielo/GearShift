#pragma once
#include <memory>

/// \brief Interfață pentru obiectele interesate de evenimente legate de Player.
///
/// De exemplu, GameLogic implementează acest listener pentru a fi notificat
/// când Player-ul este eliminat.
class IPlayerListener {
public:
    /// \brief Destructor virtual necesar pentru folosirea prin pointer la interfață.
    virtual ~IPlayerListener() = default;

    /// \brief Notificare că Player-ul a fost eliminat.
    virtual void onPlayerEliminated() = 0;
};

/// \brief Alias practic pentru un pointer smart la IPlayerListener.
using PlayerListenerPtr = std::shared_ptr<IPlayerListener>;

/// \brief Alias practic pentru un weak_ptr la IPlayerListener.
using PlayerListenerWeakPtr = std::weak_ptr<IPlayerListener>;
