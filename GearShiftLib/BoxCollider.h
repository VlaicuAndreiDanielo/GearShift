#pragma once
#include "Collider.h"
#include <array>

/// \brief Colider dreptunghiular (oriented bounding box) pentru un GameObject.
///
/// Reprezintă un paralelogram 2D atașat unui GameObject, folosit pentru
/// detecția coliziunilor cu alți BoxCollider-i prin Separating Axis Theorem.
class BoxCollider : public Collider {
public:
    /// \brief Creează un colider de tip box și îl leagă de un CollisionManager.
    ///
    /// \param manager Managerul de coliziuni care va administra acest collider.
    /// \param width Lățimea box-ului în unitățile lumii.
    /// \param height Înălțimea box-ului în unitățile lumii.
    BoxCollider(std::weak_ptr<CollisionManager> manager, float width, float height);

    /// \brief Verifică coliziunea cu un alt collider generic.
    ///
    /// Folosește double-dispatch: delegă verificarea către metoda
    /// \c other.checkCollisionWith(*this).
    ///
    /// \param other Colliderul cu care se verifică intersecția.
    /// \return Un obiect Collision dacă există coliziune, std::nullopt altfel.
    std::optional<Collision> checkCollisionWith(const Collider& other) const override;

    /// \brief Verifică coliziunea cu un alt BoxCollider.
    ///
    /// Utilizează Separating Axis Theorem pe axe derivate din muchiile celor
    /// două box-uri pentru a determina intersecția și vectorul de corecție.
    ///
    /// \param other Celălalt box collider.
    /// \return Un obiect Collision dacă există coliziune, std::nullopt altfel.
    std::optional<Collision> checkCollisionWith(const BoxCollider& other) const override;

    /// \brief Obține lățimea coliderului.
    float getWidth() const { return width; }

    /// \brief Obține înălțimea coliderului.
    float getHeight() const { return height; }

private:
    /// \brief Calculează colțurile box-ului în coordonate de lume.
    ///
    /// Ține cont de poziția și rotația Transform-ului GameObject-ului master.
    std::array<Vec2, 4> getCorners() const;

    /// \brief Proiectează colțurile pe o axă dată.
    ///
    /// \param corners Colțurile în spațiul lumii.
    /// \param axis Axa normalizată pe care se proiectează.
    /// \return Pereche (min, max) a proiecțiilor scalare.
    static std::pair<float, float> projectOntoAxis(const std::array<Vec2, 4>& corners, const Vec2& axis);

    float width;   ///< Lățimea box-ului în unitățile lumii.
    float height;  ///< Înălțimea box-ului în unitățile lumii.
};
