#pragma once
#include <functional>
#include <optional>
#include "CollisionManager.h"
#include "Collision.h"
#include "GameObject.h"

/// \brief Bază abstractă pentru toate tipurile de collider.
///
/// Un Collider este asociat unui GameObject și gestionat de un CollisionManager.
/// Instanțele trebuie create și deținute prin std::shared_ptr.
class CollisionManager::Collider : public std::enable_shared_from_this<Collider> {
public:
    /// \brief Creează un collider gestionat de un CollisionManager.
    ///
    /// \param manager Managerul responsabil de înregistrarea și actualizarea coliziunilor.
    Collider(std::weak_ptr<CollisionManager> manager);

    /// \brief Destructor virtual; dezînregistrează collider-ul din manager.
    virtual ~Collider();

    /// \brief Obține GameObject-ul de care este atașat collider-ul.
    ///
    /// \return Un shared_ptr către GameObject-ul master sau nullptr dacă nu mai există.
    std::shared_ptr<GameObject> getMasterObject() const;

    /// \brief Notifică GameObject-ul master că a avut loc o coliziune.
    ///
    /// Apelează metoda \c onCollision(other) pe GameObject-ul master.
    ///
    /// \param other Collider-ul cu care s-a produs coliziunea.
    void notifyCollision(std::shared_ptr<Collider> other);

    /// \brief Verifică coliziunea cu un alt collider generic.
    ///
    /// Aceasta este partea de bază a mecanismului de double-dispatch.
    ///
    /// \param other Collider-ul de comparat.
    /// \return Un obiect Collision dacă există coliziune, std::nullopt altfel.
    virtual std::optional<Collision> checkCollisionWith(const Collider& other) const = 0;

    /// \brief Verifică coliziunea cu un BoxCollider concret.
    ///
    /// \param other Collider-ul box de comparat.
    /// \return Un obiect Collision dacă există coliziune, std::nullopt altfel.
    virtual std::optional<Collision> checkCollisionWith(const class BoxCollider& other) const = 0;

    /// \brief Setează modul trigger pentru collider.
    ///
    /// Dacă este trigger, coliziile nu vor fi rezolvate fizic, dar notificările
    /// către GameObject vor avea loc în continuare.
    ///
    /// \param trigger True dacă este trigger, false dacă este collider solid.
    void setTrigger(bool trigger);

    /// \brief Verifică dacă acest collider este trigger.
    ///
    /// \return True dacă este trigger, false dacă este collider solid.
    bool isTrigger() const;

protected:
    /// \brief Atașează collider-ul la un GameObject și îl înregistrează în manager.
    ///
    /// Această metodă este apelată de CollisionManager în addCollider().
    ///
    /// \param master GameObject-ul de care se atașează collider-ul.
    void attachToGameObject(std::shared_ptr<GameObject> master);

    friend class CollisionManager;

private:
    std::weak_ptr<CollisionManager> manager;      ///< Managerul de coliziuni proprietar.
    std::weak_ptr<GameObject> masterObject;       ///< GameObject-ul de care este atașat collider-ul.
    bool trigger = false;                         ///< Flag pentru modul trigger (fără rezolvare fizică).
};
