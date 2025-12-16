#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include "Renderer.h"
#include "SceneManager.h"
#include "InputHandler.h"
#include "../GearShiftLib/CommandManager.h"

/// \brief Punctul central al aplicației GearShift.
///
/// Creează renderer-ul, logica de joc, managerul de scene, input handler-ul
/// și CommandManager-ul global. Ține bucla principală (events → update → render).
class Application {
private:
    /// \brief Lățimea ferestrei principale.
    static constexpr int WINDOW_WIDTH = 1920;
    /// \brief Înălțimea ferestrei principale.
    static constexpr int WINDOW_HEIGHT = 880;
    /// \brief Delta time maxim permis, pentru a evita „sărituri” uriașe.
    static constexpr float MAX_DELTA_TIME = 0.1f;

    // Core components
    std::unique_ptr<Renderer> renderer;          ///< Wrapper pentru SDL_Renderer + utilitare.
    std::shared_ptr<class IGame> gameLogic;      ///< Logica principală a jocului.
    std::unique_ptr<InputHandler> inputHandler;  ///< Handler pentru input + mapping pe comenzi.
    SceneMgr sceneMgr;                           ///< Manager de scene (Menu, Game, GameOver).

    /// \brief CommandManager global folosit din UI (butoane, input).
    std::shared_ptr<CommandManager> globalCommandMgr;

    // Main loop state
    bool   running;   ///< True cât timp aplicația rulează.
    Uint32 lastTime;  ///< Timestamp-ul ultimei iteratii (ms).

    // Initialization methods

    /// \brief Creează componentele principale (renderer, gameLogic, input, commands).
    void initializeComponents();

    /// \brief Creează și înregistrează toate scenele (Menu, Game, GameOver).
    void initializeScenes();

    // Main loop methods

    /// \brief Procesează evenimentele SDL și le pasează scenei curente.
    void handleEvents();

    /// \brief Actualizează scena curentă cu delta time-ul dat.
    /// \param dt Timpul scurs de la ultimul frame (secunde).
    void update(float dt);

    /// \brief Randează scena curentă.
    void render();

public:
    /// \brief Construiește aplicația și inițializează toate componentele.
    Application();

    /// \brief Destructor – curăță resursele principale.
    ~Application();

    // Delete copy semantics
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    /// \brief Punctul de intrare în bucla principală a jocului.
    ///
    /// Rulează până când este primit un eveniment SDL_QUIT sau running devine false.
    void run();
};
