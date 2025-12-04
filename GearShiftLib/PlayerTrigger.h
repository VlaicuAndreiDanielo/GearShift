#pragma once
#include "GameObject.h"

/// \brief GameObject invizibil folosit ca trigger pentru Player.
///
/// Este atașat de obicei la un RoadSegment sau la un NPC și detectează
/// momentul în care Player-ul îl depășește / îl atinge, notificând obiectul părinte.
class PlayerTrigger : public GameObject {
public:
    /// \brief Creează un PlayerTrigger și îi atașează un BoxCollider în modul trigger.
    ///
    /// \param collisionManager Managerul de coliziuni folosit pentru collider.
    /// \param startX Poziția inițială X în lume.
    /// \param startY Poziția inițială Y în lume.
    /// \param width Lățimea trigger-ului.
    /// \param height Înălțimea trigger-ului.
    /// \return Un shared_ptr către trigger-ul creat.
    static std::shared_ptr<PlayerTrigger> create(std::weak_ptr<CollisionManager> collisionManager,
        float startX, float startY,
        float width, float height);
protected:
    /// \brief Constructor protejat, folosit de metoda factory create().
    PlayerTrigger(float startX, float startY, float width, float height);

    /// \brief Callback la coliziune cu un alt collider.
    ///
    /// Dacă obiectul cu care se ciocnește este Player-ul, notifică obiectul
    /// părinte (RoadSegment sau TrafficBaseNPC) prin metoda playerTriggered().
    ///
    /// \param other Collider-ul celuilalt obiect.
    void onCollision(std::shared_ptr<CollisionManager::Collider> other) override;
};
