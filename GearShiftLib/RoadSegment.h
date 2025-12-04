#pragma once
#include "GameObject.h"
#include "PlayerTrigger.h"

/// \brief Segment de drum pe care rulează mașina.
///
/// Conține un trigger pentru detectarea trecerii Player-ului și poate avea
/// atașate gărdulețe de margine ca GameObject-uri copil. Se repoziționează
/// pentru a simula un drum infinit.
class RoadSegment : public GameObject {
public:
    /// \brief Creează un segment de drum, trigger-ul aferent și gărdulețele.
    ///
    /// \param collisionManager Managerul de coliziuni pentru collider-e.
    /// \param startX Poziția inițială X a segmentului.
    /// \param startY Poziția inițială Y a segmentului.
    /// \param width Lățimea segmentului (în lume).
    /// \param height Înălțimea segmentului (în lume).
    /// \param totalRoadCount Numărul total de segmente folosite în scenă.
    /// \return Un vector cu GameObject-urile create (segment, trigger, gărdulețe).
    static std::vector<std::shared_ptr<GameObject>> create(std::weak_ptr<CollisionManager> collisionManager,
        float startX, float startY,
        float width, float height,
        int totalRoadCount);

    /// \brief Contor global al numărului de segmente de drum trecute de Player.
    static int segmentPassCounter;

    /// \brief Obține trigger-ul asociat acestui segment.
    std::shared_ptr<PlayerTrigger> getTrigger() const { return trigger; }

protected:
    friend class PlayerTrigger;

    /// \brief Metodă apelată când PlayerTrigger-ul asociat este activat.
    ///
    /// Repoziționează segmentul (și copiii săi) mai sus, pentru a simula
    /// un drum care se „repetă” și incrementează segmentPassCounter.
    void playerTriggered();

private:
    /// \brief Constructor privat, folosit de metoda factory create().
    RoadSegment(float startX, float startY, float width, float height, int totalRoadCount);

    /// \brief Creează și atașează trigger-ul pentru segment.
    /// \param collisionManager Managerul de coliziuni folosit pentru collider.
    void createTrigger(std::weak_ptr<CollisionManager> collisionManager);

    std::shared_ptr<PlayerTrigger> trigger; ///< Trigger-ul asociat acestui segment.
    int roadCount;                          ///< Numărul total de segmente din scenă.
};
