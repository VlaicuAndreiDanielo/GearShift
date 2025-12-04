#pragma once
#include "GameObject.h"
#include "IPlayerListener.h"

/// \brief Mașina controlată de jucător.
///
/// Gestionează input-ul de la utilizator (mișcare, accelerație/frânare),
/// limitele de deplasare pe ecran și notifică listener-ii atunci când
/// jucătorul este eliminat.
class Player : public GameObject {
public:
    /// \brief Creează un Player și îi atașează un BoxCollider.
    ///
    /// \param collisionManager Managerul de coliziuni folosit pentru collider.
    /// \param startX Poziția inițială X în lume.
    /// \param startY Poziția inițială Y în lume.
    /// \return Un shared_ptr către Player-ul creat.
    static std::shared_ptr<Player> create(std::weak_ptr<CollisionManager> collisionManager,
        float startX, float startY);

    /// \brief Actualizează poziția și viteza player-ului pe baza input-ului.
    ///
    /// \param dt Timpul scurs de la ultimul frame (în secunde).
    /// \param input Starea curentă a input-ului (taste).
    void update(float dt, const IInputState& input) override;

    // --- game logic / query state ---

    /// \brief Setează direct poziția player-ului în lume.
    ///
    /// \param newX Noua coordonată X.
    /// \param newY Noua coordonată Y.
    void setPosition(float newX, float newY);

    /// \brief Setează limitele maxime de deplasare pe ecran.
    ///
    /// Player-ul va fi „clamp-uit” în interiorul [0, maxX - width] × [0, maxY - height].
    ///
    /// \param maxX Lățimea maximă (în pixeli).
    /// \param maxY Înălțimea maximă (în pixeli).
    void setBounds(int maxX, int maxY);

    /// \brief Adaugă un listener interesat de evenimentele Player-ului.
    ///
    /// \param listener Listener implementând IPlayerListener.
    void addListener(PlayerListenerPtr listener);

    /// \brief Elimină un listener (dacă mai este valid).
    ///
    /// \param listener Listener-ul care trebuie scos.
    void removeListener(PlayerListenerPtr listener);

protected:
    /// \brief Callback la coliziune cu un alt collider.
    ///
    /// Dacă intră în coliziune cu un NPC, notifică listener-ii că
    /// player-ul a fost eliminat.
    ///
    /// \param other Collider-ul celuilalt obiect.
    void onCollision(std::shared_ptr<Collider> other) override;

private:
    /// \brief Constructor privat, folosit de metoda factory create().
    Player(float startX, float startY);

    /// \brief Notifică toți listener-ii că Player-ul a fost eliminat.
    void notifyPlayerEliminated();

    /// \brief Curăță din listă listener-ii care au expirat.
    void cleanupExpiredListeners();

    /// \brief Listener-ii interesați de evenimentele Player-ului.
    std::vector<PlayerListenerWeakPtr> m_listeners;

    float vx, vy;          ///< Vitezele pe axele X și Y.

    float currentSpeed;    ///< Viteza curentă înainte/înapoi.
    float maxSpeed;        ///< Viteza maximă.
    float acceleration;    ///< Rata de accelerare.
    float deceleration;    ///< Rata de decelerare.
    float baseSpeed;       ///< Viteza laterală (stânga/dreapta).

    // boundaries
    int boundMaxX;         ///< Lățimea maximă a zonei de joc.
    int boundMaxY;         ///< Înălțimea maximă a zonei de joc.

    /// \brief Procesează input-ul și actualizează vitezele interne.
    /// \param input Starea curentă a input-ului.
    void handleInput(const IInputState& input);
};
