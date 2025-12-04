#pragma once
#include "CollisionManager.h"
#include "Vec2.h"

/// \brief Reprezintă o coliziune între două collider-e.
///
/// Conține collider-ele implicate, normală de coliziune și adâncimea de
/// penetrare, precum și logica simplă de rezolvare a coliziunii.
class CollisionManager::Collision {
public:
    /// \brief Creează o coliziune între două collider-e.
    ///
    /// \param a Primul collider implicat (de obicei „A” în calcul).
    /// \param b Al doilea collider implicat (de obicei „B”).
    Collision(std::shared_ptr<const Collider> a, std::shared_ptr<const Collider> b);

    ~Collision() = default;

    /// \brief Obține primul collider implicat.
    std::shared_ptr<const Collider> getColliderA() const;

    /// \brief Obține al doilea collider implicat.
    std::shared_ptr<const Collider> getColliderB() const;

    /// \brief Setează normala coliziunii.
    ///
    /// Normala ar trebui să indice direcția în care „B” este împins față de „A”.
    ///
    /// \param normal Vector normalizat al coliziunii.
    void setCollisionNormal(const Vec2& normal);

    /// \brief Obține normala coliziunii.
    Vec2 getCollisionNormal() const;

    /// \brief Setează adâncimea de penetrare.
    ///
    /// \param depth Cantitatea de intersecție de-a lungul normalei.
    void setPenetrationDepth(float depth);

    /// \brief Obține adâncimea de penetrare.
    float getPenetrationDepth() const;

    /// \brief Rezolvă coliziunea mutând GameObject-urile implicate.
    ///
    /// - Dacă oricare collider este trigger, nu se aplică rezolvare fizică.
    /// - Dacă ambele obiecte sunt fixe, nu se mișcă niciunul.
    /// - Dacă doar unul este fix, se mișcă celălalt complet.
    /// - Dacă ambele sunt mobile, se împart corecțiile pe jumătate.
    void resolve() const;

private:
    std::shared_ptr<const Collider> colliderA;  ///< Primul collider implicat.
    std::shared_ptr<const Collider> colliderB;  ///< Al doilea collider implicat.
    Vec2  collisionNormal = Vec2{};            ///< Normala coliziunii în spațiul lumii.
    float penetrationDepth = 0.0f;             ///< Adâncimea de penetrare de-a lungul normalei.
};
