#pragma once
#include "FuelRenderer.h"
#include "ScoreRenderer.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "ObjectRenderer.h"
#include "IGame.h"
#include "../GearShiftLib/CommandManager.h"
#include <memory>
#include <SDL2/SDL_ttf.h>

/// \brief Scena principală de joc (gameplay).
///
/// Se ocupă de:
///  - randarea obiectelor de joc (mașini, drum, fuel etc.);
///  - randarea HUD-ului (fuel + scor);
///  - gestionarea pauzei (overlay „PAUSED” + PauseGameCommand);
///  - tranziția către GameOverScene la final de rundă.
class GameScene : public IScene {
private:
    Renderer* renderer;        ///< Renderer-ul principal.
    SceneMgr* sceneMgr;        ///< Manager de scene pentru schimbarea în GameOver.
    std::weak_ptr<IGame> game; ///< Logica jocului (IGame).
    InputHandler* inputHandler;///< Handler de input (taste + comenzi).  

    /// \brief CommandManager pentru acțiunile din scena de joc (pauză).
    std::shared_ptr<CommandManager> commandMgr;

    std::unique_ptr<ObjectRenderer> objectRenderer; ///< Renderer pentru obiectele de joc.
    std::unique_ptr<FuelRenderer>   fuelRenderer;   ///< HUD pentru fuel.
    std::unique_ptr<ScoreRenderer>  scoreRenderer;  ///< HUD pentru scor.
    TTF_Font* font;                                 ///< Font pentru textul „PAUSED”.

private:
    /// \brief Helper pentru înregistrarea comenzilor specifice scenei.
    ///
    /// Înregistrează `PauseGameCommand` sub numele „pause_game”.
    void setupCommands();

public:
    /// \brief Creează o scenă de joc.
    ///
    /// \param rend Renderer-ul folosit pentru desen.
    /// \param mgr Managerul de scene.
    /// \param logic Logica jocului (IGame).
    /// \param input Handler-ul de input.
    /// \param globalCommandMgr CommandManager global.
    GameScene(Renderer* rend,
        SceneMgr* mgr,
        std::weak_ptr<IGame> logic,
        InputHandler* input,
        std::shared_ptr<CommandManager> globalCommandMgr);

    /// \brief Destructor default – cleanup-ul principal este în onExit().
    ~GameScene() override = default;

    /// \brief Actualizează logica scenei (input, comenzi, GameLogic).
    void update(float dt) override;

    /// \brief Randează toate obiectele de joc + HUD + overlay de pauză.
    void render() override;

    /// \brief Procesează evenimente SDL (forward către InputHandler).
    void handleEvent(SDL_Event& e) override;

    /// \brief Numele scenei – "Game".
    std::string getName() const override { return "Game"; }

    /// \brief Se apelează când scena devine activă.
    ///
    /// Inițializează rendererele, HUD-ul, fontul și bind-urile de taste pentru pauză.
    void onEnter() override;

    /// \brief Se apelează când scena iese din activ.
    ///
    /// Eliberează resursele de randare și închide runda de joc (endGame()).
    void onExit() override;

private:
    /// \brief Randează overlay-ul semi-transparent „PAUSED”.
    void renderPausedText();
};
