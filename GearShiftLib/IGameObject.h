#pragma once
#include "SpriteType.h"

/// \brief Interfață pentru un obiect de joc utilizat la randare.
///
/// Este un „view simplificat” peste GameObject, folosit de layer-ul de UI
/// pentru a desena obiectele fără să depindă de logica lor internă.
class IGameObject
{
public:
    /// \brief Obține coordonata X în lume.
    virtual float getX() const = 0;

    /// \brief Obține coordonata Y în lume.
    virtual float getY() const = 0;

    /// \brief Obține lățimea obiectului.
    virtual float getWidth() const = 0;

    /// \brief Obține înălțimea obiectului.
    virtual float getHeight() const = 0;

    /// \brief Obține sprite-ul asociat obiectului.
    virtual SpriteType getSprite() const = 0;

    /// \brief Obține rotația obiectului (de obicei în grade).
    virtual float getRotation() const = 0;

    /// \brief Verifică dacă obiectul este activ și trebuie randat.
    virtual bool isActive() const = 0;

    /// \brief Destructor virtual necesar pentru folosirea prin pointer la interfață.
    virtual ~IGameObject() = default;
};
