#pragma once
#include <memory>
#include <random>
#include "IGame.h"
#include "Player.h"
#include "IInputState.h"
#include "IGameObject.h"
#include "CollisionManager.h"

/// \brief Coordonează logica principală a jocului GearShift.
///
/// Gestionează starea jocului (meniu, playing, pauză, game over),
/// lista de GameObject-uri, coliziunile, camera, scorul, fuel-ul și
/// contextul global al unei runde.
class GameLogic : public IGame,
    public IPlayerListener,
    public std::enable_shared_from_this<GameLogic> {
public:
    /// \brief Creează o instanță de GameLogic pentru un ecran dat.
    ///
    /// \param screenW Lățimea ferestrei în pixeli.
    /// \param screenH Înălțimea ferestrei în pixeli.
    /// \return Un shared_ptr către IGame implementat de GameLogic.
    static std::shared_ptr<IGame> create(int screenW, int screenH);

    /// \brief Actualizează logica jocului pentru un frame.
    ///
    /// În funcție de GameState:
    ///  - actualizează GameObject-urile, coliziunile, scorul și fuel-ul;
    ///  - gestionează pauza și tranziția spre GameOver.
    ///
    /// \param dt Timpul scurs de la ultimul frame (în secunde).
    /// \param input Starea curentă a input-ului (tastatură, mouse etc.).
    void update(float dt, IInputState& input) override;

    // --- management stare joc ---

    /// \brief Pornește o rundă nouă de joc.
    ///
    /// Resetează scorul, timpul, creează player-ul, camera, drumul, NPC-urile
    /// și inițializează managerii de scor și fuel.
    void startGame() override;

    /// \brief Pune jocul în pauză (dacă se afla în Playing).
    void pauseGame() override;

    /// \brief Reia jocul din pauză (dacă se afla în Paused).
    void resumeGame() override;

    /// \brief Încheie jocul și golește lista de obiecte active.
    void endGame() override;

    /// \brief Obține obiectele de joc într-o formă adaptată pentru UI.
    ///
    /// \return Vector de IGameObject folosit la randare în GearShiftUI.
    const std::vector<std::shared_ptr<IGameObject>>& getGameObjects() const override;

    // --- acces la „pânza” de fundal (fabric) ---

    /// \brief Obține pânza (efectul vizual de fundal) pentru modificare.
    std::shared_ptr<class IFabric> getFabric() override;

    /// \brief Obține pânza în variantă constantă.
    const std::shared_ptr<class IFabric> getFabric() const override;

    /// \brief Obține starea curentă a jocului.
    GameState getState() const override { return currentState; }

    /// \brief Obține timpul total scurs în runda curentă.
    float getTime() const override { return gameTime; }

    /// \brief Obține managerul de scor folosit în runda curentă.
    std::shared_ptr<class IScoreManager> getScoreManager() const;

    /// \brief Verifică dacă jocul este în starea GameOver.
    bool isGameOver() const { return currentState == GameState::GameOver; }

    /// \brief Generează și adaugă în scenă un nou FuelCanister.
    void spawnFuelCanister();

    // --- logică de joc suplimentară ---

    /// \brief Aplică o forță asupra pânzei în urma input-ului de mouse.
    ///
    /// \param x Coordonata X a mouse-ului în pixeli.
    /// \param y Coordonata Y a mouse-ului în pixeli.
    /// \param pressed True dacă butonul este apăsat.
    void applyMouseForce(int x, int y, bool pressed) override;

    /// \brief Obține managerul de fuel folosit în runda curentă.
    std::shared_ptr<class IFuelManager> getFuelManager() const override;

    /// \brief Marchează faptul că fuel-ul a fost reîncărcat.
    ///
    /// Apelează reset() pe FuelManager.
    void setFuelRecharged();

    /// \brief Callback din partea Player-ului când este eliminat.
    ///
    /// Implică trecerea în starea GameOver.
    void onPlayerEliminated() override;

private:
    /// \brief Constructor privat, folosit de metoda factory create().
    GameLogic(int screenW, int screenH);

    /// \brief Ajustează pozițiile obiectelor în funcție de camera principală.
    void scaleToCamera();

    /// \brief Creează segmentele de drum și le adaugă în scenă.
    void createRoadSegments();

    /// \brief Creează NPC-urile (trafic) și le adaugă în scenă.
    void createNPCs();

    /// \brief Apel intern atunci când fuel-ul se termină.
    void onFuelEmpty();

    // --- resurse joc ---
    std::shared_ptr<class IFabric>       fabric;
    std::shared_ptr<class FuelManager>   fuelManager;
    std::shared_ptr<class ScoreManager>  scoreManager;
    std::shared_ptr<class Camera>        mainCamera;

    /// \brief Lista completă de GameObject-uri din scenă.
    std::vector<std::shared_ptr<GameObject>> gameObjects;

    /// \brief Adaptori pentru GameObject-uri folosiți în UI/randare.
    std::vector<std::shared_ptr<IGameObject>> objectAdapters;

    std::shared_ptr<CollisionManager> collisionManager; ///< Manager global de coliziuni.

    // --- stare joc ---
    GameState currentState;  ///< Starea curentă (Menu, Playing, Paused, GameOver).
    float     gameTime;      ///< Timpul scurs în runda curentă.
    int       screenWidth;   ///< Lățimea ferestrei.
    int       screenHeight;  ///< Înălțimea ferestrei.

    // --- statistici joc ---
    int score;               ///< Scorul curent (referință pentru UI / scoring).

    std::mt19937 rng;        ///< Generator de numere aleatoare pentru spawn-uri etc.
};
