#pragma once
#include "SceneManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "CRTEffect.h"
#include "WaveEffect.h"
#include "Button.h"
#include "IGame.h"
#include "../GearShiftLib/CommandManager.h"
#include <SDL2/SDL_ttf.h>
#include <memory>

/// \brief Scena de meniu principal al jocului.
///
/// Afișează fundalul animat (wave + fabric), efectul CRT, mașina din meniu
/// și butoanele PLAY / EXIT. Folosește Command pattern pentru:
///  - start de joc (`StartGameCommand`);
///  - ieșire din aplicație (`ExitApplicationCommand`).
class MenuScene : public IScene {
private:
    Renderer* renderer;     ///< Renderer-ul folosit pentru desen.
    SceneMgr* sceneMgr;     ///< Managerul de scene (pentru schimbare în Game).
    std::weak_ptr<IGame> game; ///< Logica de joc (pentru start și fabric).
    InputHandler* inputHandler; ///< Handler pentru input-ul utilizatorului.  

    /// \brief CommandManager global pentru acțiunile de meniu.
    std::shared_ptr<CommandManager> commandMgr;

    std::unique_ptr<CRT>  crt;       ///< Efect CRT aplicat peste scenă.
    std::unique_ptr<Wave> wave;      ///< Efect de valuri pentru fundal.
    std::unique_ptr<Btn>  playBtn;   ///< Butonul PLAY.
    std::unique_ptr<Btn>  exitBtn;   ///< Butonul EXIT.

    TTF_Font* font;        ///< Font folosit pentru textul butoanelor.
    SDL_Texture* carTexture; ///< Textură pentru mașina din meniul principal.
    SDL_Rect    carRect;     ///< Poziția și dimensiunea mașinii.

    /// \brief Flag pentru a preveni dublul cleanup în destructor.
    bool cleanedUp;

private:
    /// \brief Helper pentru setup-ul comenzilor specifice meniului.
    ///
    /// Înregistrează în CommandManager comenzile „start_game”, „exit_app”.
    void setupCommands();

public:
    /// \brief Creează scena de meniu.
    ///
    /// \param rend Renderer-ul folosit pentru desen.
    /// \param mgr Managerul de scene.
    /// \param logic Logica jocului (IGame).
    /// \param input Handler-ul de input.
    /// \param globalCommandMgr CommandManager global.
    MenuScene(Renderer* rend,
        SceneMgr* mgr,
        std::weak_ptr<IGame> logic,
        InputHandler* input,
        std::shared_ptr<CommandManager> globalCommandMgr);

    /// \brief Destructor – se ocupă de cleanup sigur prin `onExit()`.
    ~MenuScene() override;

    /// \brief Actualizează logica meniului (fabric, efecte, comenzi).
    void update(float dt) override;

    /// \brief Randează meniul (fundal, mașină, butoane).
    void render() override;

    /// \brief Gestionează evenimentele SDL (mouse, tastatură).
    ///
    /// Se forward-ează și la `InputHandler`, și la butoane.
    void handleEvent(SDL_Event& e) override;

    /// \brief Numele scenei – "Menu".
    std::string getName() const override { return "Menu"; }

    /// \brief Se apelează când scena devine activă.
    ///
    /// Încarcă fontul, texturile, creează efectele și butoanele.
    void onEnter() override;

    /// \brief Se apelează când scena iese din activ.
    ///
    /// Eliberează resursele vizuale și UI.
    void onExit() override;
};
