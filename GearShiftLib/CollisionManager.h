#pragma once
#include <memory>
#include <vector>

/// \brief Manager global pentru coliziuni.
///
/// Deține referințe slabe către toate collider-ele înregistrate în scenă.
/// La fiecare apel de update(), curăță collider-ele expirate, verifică
/// coliziunile pereche și apelează rezolvarea + notificarea GameObject-urilor.
class CollisionManager : public std::enable_shared_from_this<CollisionManager> {
public:
    /// \brief Tip intern care reprezintă un collider atașat unui GameObject.
    class Collider;

    /// \brief Tip intern care reprezintă o coliziune între două collider-e.
    class Collision;

    /// \brief Actualizează sistemul de coliziuni.
    ///
    /// Curăță referințele slabe expirate și verifică toate perechile de
    /// collider-e active. Pentru coliziunile detectate, creează un obiect
    /// Collision, îl rezolvă și notifică GameObject-urile implicate.
    void update();

    /// \brief Înregistrează un collider în manager.
    ///
    /// Managerul păstrează doar o referință slabă (nu deține viața obiectului).
    ///
    /// \param collider Collider-ul de înregistrat.
    void registerCollider(std::weak_ptr<Collider> collider);

    /// \brief Dezînregistrează un collider din manager.
    ///
    /// \param collider Pointer brut către collider-ul care trebuie scos.
    void unregisterCollider(Collider* collider);

    ~CollisionManager() = default;

    /// \brief Creează și atașează un collider de tip T la un GameObject.
    ///
    /// Funcție helper care construiește un collider \c T, îi pasează acest
    /// CollisionManager ca manager și îl atașează la GameObject-ul primit.
    ///
    /// \tparam T Tipul specific de collider (trebuie să derive din Collider).
    /// \tparam Args Tipurile parametrilor de construcție.
    /// \param obj GameObject-ul la care se atașează collider-ul.
    /// \param args Parametrii suplimentari transmiși constructorului lui T.
    /// \return Un shared_ptr către collider-ul creat.
    template<typename T, typename... Args>
    std::shared_ptr<T> addCollider(std::shared_ptr<class GameObject> obj, Args&&... args) {
        static_assert(std::is_base_of_v<Collider, T>);
        std::shared_ptr<T> collider =
            std::make_shared<T>(shared_from_this(), std::forward<Args>(args)...);
        collider->attachToGameObject(obj);
        return collider;
    }

private:
    /// \brief Lista de collider-e gestionate, stocate ca weak_ptr.
    std::vector<std::weak_ptr<Collider>> colliderList;
};

/// \brief Alias global pentru a face folosirea Collider mai comodă.
using Collider = CollisionManager::Collider;

/// \brief Alias global pentru tipul de coliziune gestionat de CollisionManager.
using Collision = CollisionManager::Collision;
