#pragma once
#include <random>
#include "GameObject.h"
#include "PlayerTrigger.h"

/// \brief Mașină NPC de bază din trafic.
///
/// Se deplasează pe drum cu o viteză aleatoare în intervalul [minSpeed, maxSpeed],
/// se repoziționează (respawn) în fața camerei când este depășită de jucător și
/// folosește trigger-e suplimentare pentru a încetini în funcție de trafic. :contentReference[oaicite:1]{index=1}
class TrafficBaseNPC : public GameObject {
public:
    /// \brief Creează un NPC de trafic și obiectele asociate (trigger-e).
    ///
    /// Creează:
    ///  - NPC-ul propriu-zis;
    ///  - un PlayerTrigger pentru respawn;
    ///  - un SlowDownTrigger pentru încetinire în funcție de trafic;
    ///  - atașează un BoxCollider NPC-ului.
    ///
    /// \param collisionManager Managerul de coliziuni.
    /// \param gameRng Generatorul de numere aleatoare al jocului (partajat).
    /// \param startX Poziția inițială X.
    /// \param startY Poziția inițială Y.
    /// \param width Lățimea mașinii NPC.
    /// \param height Înălțimea mașinii NPC.
    /// \param roadWidth Lățimea drumului.
    /// \param roadHeight Înălțimea unui segment de drum.
    /// \param minSpeed Viteza minimă generată pentru NPC.
    /// \param maxSpeed Viteza maximă generată pentru NPC.
    /// \return Un vector cu GameObject-urile create (NPC + trigger-e).
    static std::vector<std::shared_ptr<GameObject>> create(
        std::weak_ptr<CollisionManager> collisionManager,
        std::mt19937& gameRng,
        float startX, float startY,
        float width, float height,
        float roadWidth, float roadHeight,
        float minSpeed, float maxSpeed
    );

    /// \brief Obține trigger-ul folosit pentru respawn-ul NPC-ului.
    std::shared_ptr<PlayerTrigger> getRespawnTrigger() const;

    /// \brief Trigger intern folosit pentru încetinirea NPC-ului.
    ///
    /// Detectează prezența altor mașini (PLAYER sau NPC) în față și,
    /// la coliziune, apelează TrafficBaseNPC::stop() pe NPC-ul părinte. :contentReference[oaicite:2]{index=2}
    class SlowDownTrigger : public GameObject {
    public:
        /// \brief Creează un SlowDownTrigger și îi atașează un BoxCollider trigger.
        ///
        /// \param collisionManager Managerul de coliziuni.
        /// \param startX Poziția inițială X.
        /// \param startY Poziția inițială Y.
        /// \param width Lățimea trigger-ului.
        /// \param height Înălțimea trigger-ului.
        /// \return Un shared_ptr către trigger.
        static std::shared_ptr<SlowDownTrigger> create(
            std::weak_ptr<CollisionManager> collisionManager,
            float startX, float startY,
            float width, float height
        );

    protected:
        /// \brief Constructor protejat, folosit de metoda factory create().
        SlowDownTrigger(float startX, float startY, float width, float height);

        /// \brief Callback la coliziune cu alt collider.
        ///
        /// Dacă obiectul cu care se ciocnește este PLAYER sau NPC și
        /// aparține altui GameObject decât cel părinte, notifică NPC-ul
        /// părinte să încetinească (TrafficBaseNPC::stop()). :contentReference[oaicite:3]{index=3}
        ///
        /// \param other Collider-ul celuilalt obiect.
        void onCollision(std::shared_ptr<CollisionManager::Collider> other) override;
    };

    /// \brief Obține trigger-ul de încetinire asociat acestui NPC.
    std::shared_ptr<TrafficBaseNPC::SlowDownTrigger> getSlowDownTrigger() const;

protected:
    friend class PlayerTrigger;
    friend class SlowDownTrigger;

    /// \brief Marchează NPC-ul ca „în proces de oprire”.
    ///
    /// La următorul update viteza este redusă gradual până aproape de 0. :contentReference[oaicite:4]{index=4}
    void stop();

    /// \brief Metodă apelată de PlayerTrigger când jucătorul depășește NPC-ul.
    ///
    /// Repoziționează NPC-ul în fața camerei prin respawn().
    void playerTriggered();

    /// \brief Actualizează deplasarea NPC-ului pe verticală și viteza în timp.
    ///
    /// \param dt Timpul scurs de la ultimul frame.
    /// \param input Input-ul curent (nefolosit în implementarea actuală).
    void update(float dt, const IInputState& input) override;

private:
    /// \brief Constructor privat, folosit de metoda factory create().
    TrafficBaseNPC(std::mt19937& gameRng,
        float startX, float startY,
        float width, float height,
        float roadWidth, float roadHeight,
        float minSpeed, float maxSpeed);

    /// \brief Creează și atașează trigger-ul de respawn.
    void createRespawnTrigger(std::weak_ptr<CollisionManager> collisionManager);

    /// \brief Creează și atașează trigger-ul de încetinire.
    void createSlowDownTrigger(std::weak_ptr<CollisionManager> collisionManager);

    /// \brief Repoziționează NPC-ul în față cu o poziție și viteză noi.
    ///
    /// Alege aleator sprite-ul, viteza, poziția X și distanța Y de respawn. :contentReference[oaicite:5]{index=5}
    void respawn();

    std::shared_ptr<PlayerTrigger> respawnTrigger;                      ///< Trigger pentru respawn.
    std::shared_ptr<TrafficBaseNPC::SlowDownTrigger> slowDownTrigger;  ///< Trigger pentru încetinire.

    float roadWidth = 100.0f;  ///< Lățimea drumului.
    float roadHeight = 100.0f;  ///< Înălțimea unui segment de drum.
    float roadCenterX = 50.0f;   ///< Centrul pe axa X al drumului.

    float speed = 5.0f;   ///< Viteza curentă.
    float desiredSpeed = 5.0f;   ///< Viteza „țintă” a NPC-ului.
    float minSpeed = 0.0f;   ///< Viteza minimă generată.
    float maxSpeed = 50.0f;  ///< Viteza maximă generată.

    bool isStopping = false;     ///< True dacă NPC-ul trebuie să încetinească.

    std::mt19937& rng;                           ///< Generatorul global de numere aleatoare.
    std::uniform_real_distribution<float> speedDist;  ///< Distribuție pentru viteza NPC-ului.
    std::uniform_real_distribution<float> xPosDist;   ///< Distribuție pentru poziția X la respawn.
    std::uniform_real_distribution<float> yPosDist;   ///< Distribuție pentru distanța Y la respawn.
    std::uniform_int_distribution<int>   spriteDist;  ///< Distribuție pentru alegerea sprite-ului.
};
