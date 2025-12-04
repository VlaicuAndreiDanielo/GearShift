#pragma once
#include "GameObject.h"
#include "GameLogic.h"
#include "CollisionManager.h"
#include <memory>
#include <vector>

/// \brief Obiect de tip „bidon de combustibil” colectabil.
///
/// Când intră în coliziune cu Player-ul, dezactivează propriul GameObject
/// și notifică GameLogic pentru a reîncărca fuel-ul.
class FuelCanister : public GameObject {
public:
    /// \brief Creează un FuelCanister cu poziție și dimensiune date.
    ///
    /// \param startX Poziția inițială X în lume.
    /// \param startY Poziția inițială Y în lume.
    /// \param width Lățimea canistrei.
    /// \param height Înălțimea canistrei.
    /// \param gameLogic Pointer către GameLogic pentru notificări.
    FuelCanister(float startX, float startY, float width, float height, GameLogic* gameLogic);

    /// \brief Actualizare pe frame pentru FuelCanister.
    ///
    /// În implementarea curentă comportamentul e minim; logica principală
    /// este în onCollision().
    void update(float dt, const IInputState& input) override;

    /// \brief Callback la coliziune cu alt collider.
    ///
    /// Dacă obiectul cu care intră în coliziune este de tip PLAYER,
    /// dezactivează canistra și apelează GameLogic::setFuelRecharged().
    ///
    /// \param other Collider-ul celuilalt obiect.
    void onCollision(std::shared_ptr<CollisionManager::Collider> other) override;

    /// \brief Pointer brut către GameLogic pentru notificarea reîncărcării fuel-ului.
    GameLogic* gameLogic = nullptr;

    /// \brief Creează un FuelCanister și îi atașează collider de tip BoxCollider.
    ///
    /// \param collisionManager Managerul de coliziuni folosit pentru creare.
    /// \param startX Poziția inițială X.
    /// \param startY Poziția inițială Y.
    /// \param gameLogic Pointer către GameLogic.
    /// \return Un vector cu GameObject-urile create (în prezent un singur element).
    static std::vector<std::shared_ptr<GameObject>> create(
        std::weak_ptr<CollisionManager> collisionManager,
        float startX, float startY, GameLogic* gameLogic
    );

private:
    // momentan nu ai câmpuri private, dar poți adăuga aici în viitor
};
