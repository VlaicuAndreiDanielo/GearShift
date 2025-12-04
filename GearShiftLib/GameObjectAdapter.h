#pragma once
#include "IGameObject.h"
#include <memory>

/// \brief Adapter între GameObject și interfața IGameObject.
///
/// Permite folosirea GameObject-urilor din logica de joc în layer-ul de UI
/// (randare) fără ca acesta să depindă de implementarea concretă a GameObject.
class GameObjectAdapter : public IGameObject {
public:
    /// \brief Creează un adapter pentru un GameObject dat.
    /// \param obj Obiectul de joc pe care îl adaptează.
    GameObjectAdapter(std::shared_ptr<class GameObject> obj);

    /// \brief Obține coordonata X în lume (preluată din Transform-ul obiectului).
    float getX() const override;

    /// \brief Obține coordonata Y în lume.
    float getY() const override;

    /// \brief Obține lățimea GameObject-ului adaptat.
    float getWidth() const override;

    /// \brief Obține înălțimea GameObject-ului adaptat.
    float getHeight() const override;

    /// \brief Obține rotația GameObject-ului adaptat.
    float getRotation() const override;

    /// \brief Obține sprite-ul asociat GameObject-ului adaptat.
    SpriteType getSprite() const override;

    /// \brief Verifică dacă GameObject-ul adaptat este activ.
    bool isActive() const override;

private:
    /// \brief Obiectul de joc adaptat pentru interfața IGameObject.
    std::shared_ptr<class GameObject> object;
};
