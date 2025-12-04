#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "CollisionManager.h"
#include "Transform.h"
#include "ObjectType.h"
#include "SpriteType.h"
#include "IInputState.h"

/// \brief Bază abstractă pentru toate obiectele din lume.
///
/// Reprezintă un obiect 2D cu poziție, rotație, dimensiune, sprite și tip.
/// Instanțele trebuie gestionate prin std::shared_ptr.
class GameObject : public std::enable_shared_from_this<GameObject> {
public:
    /// \brief Constructor implicit.
    GameObject() = default;

    /// \brief Creează un GameObject cu poziție și dimensiune specificate.
    ///
    /// \param startX Poziția inițială X în lume.
    /// \param startY Poziția inițială Y în lume.
    /// \param width Lățimea obiectului.
    /// \param height Înălțimea obiectului.
    /// \param active True dacă obiectul este activ la început.
    GameObject(float startX, float startY, float width, float height, bool active);

    virtual ~GameObject() = default;

    /// \brief Wrapper pentru update care menține corect ierarhia părinte–copil.
    ///
    /// Apelează metoda virtuală update(), apoi propagă modificările către copii
    /// pe baza diferențelor de transform (local/world).
    ///
    /// \param dt Timpul scurs de la ultimul frame.
    /// \param input Starea curentă a input-ului.
    void handleUpdate(float dt, const IInputState& input);

    /// \brief Setează GameObject-ul părinte pentru acest obiect.
    ///
    /// Actualizează transform-ul local și înregistrează acest obiect ca și copil.
    ///
    /// \param parentObj Obiectul părinte.
    void setParent(std::shared_ptr<GameObject> parentObj);

    /// \brief Obține transform-ul în spațiul lumii.
    /// \return Referință la Transform-ul world al obiectului.
    Transform& getWorldTransform();

    /// \brief Setează transform-ul în spațiul lumii.
    ///
    /// Dacă obiectul nu are părinte valid, actualizează și transform-ul local.
    ///
    /// \param pos Poziția în lume.
    /// \param rotation Rotația în lume (grade).
    void setWorldTransform(Vec2 pos, float rotation);

    /// \brief Obține tipul logic al obiectului (Road, Player, Fuel etc.).
    ObjectType getType() const;

    /// \brief Obține tipul de sprite asociat obiectului.
    SpriteType getSprite() const;

    /// \brief Setează sprite-ul asociat obiectului.
    /// \param sprite Tipul de sprite din atlas.
    void setSprite(SpriteType sprite);

    /// \brief Activează sau dezactivează obiectul.
    void setActive(bool isActive);

    /// \brief Verifică dacă obiectul este activ.
    bool isActive() const;

    /// \brief Obține lățimea obiectului.
    float getWidth() const;

    /// \brief Obține înălțimea obiectului.
    float getHeight() const;

    /// \brief Setează dimensiunea obiectului.
    /// \param w Noua lățime.
    /// \param h Noua înălțime.
    void setSize(float w, float h);

protected:
    /// \brief Actualizare specifică pentru tipul concret de GameObject.
    ///
    /// Implementările derivatelor ar trebui să suprascrie această metodă pentru
    /// a implementa comportamentul de frame.
    ///
    /// \param dt Timpul scurs de la ultimul frame.
    /// \param input Starea curentă a input-ului.
    virtual void update(float dt, const IInputState& input);

    friend class CollisionManager::Collider;

    Transform worldTransform;                 ///< Transform-ul în spațiul lumii.
    Transform localTransform;                 ///< Transform-ul relativ la părinte.
    std::shared_ptr<Collider> collider;      ///< Collider-ul atașat (dacă există).
    bool active = true;                      ///< Flag de activare.
    float width = 0.0f;                     ///< Lățimea obiectului.
    float height = 0.0f;                     ///< Înălțimea obiectului.
    SpriteType sprite = SpriteType::NONE;    ///< Sprite-ul asociat.
    ObjectType type = ObjectType::NONE;    ///< Tipul logic al obiectului.

    /// \brief Callback la coliziune cu un alt collider.
    ///
    /// Implementările derivate pot suprascrie pentru a reacționa la coliziuni.
    ///
    /// \param other Collider-ul cu care a avut loc coliziunea.
    virtual void onCollision(std::shared_ptr<Collider> other);

    /// \brief Propagă modificările de poziție și rotație către copii.
    ///
    /// \param deltaPos Diferența de poziție locală.
    /// \param deltaRotation Diferența de rotație locală.
    void parentUpdate(Vec2 deltaPos, float deltaRotation);

    /// \brief Părinte opțional al acestui GameObject (pentru ierarhii).
    std::optional<std::weak_ptr<GameObject>> parent = std::nullopt;

private:
    /// \brief Lista de copii ai acestui GameObject.
    std::vector<std::weak_ptr<GameObject>> children;
};
