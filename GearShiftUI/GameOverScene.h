#pragma once
#include "IScene.h"
#include "Renderer.h"
#include "SceneManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

/// \brief Scena afișată la sfârșitul jocului (Game Over).
///
/// Desenează un ecran roșu cu un panou „GAME OVER” + scorul final.
/// După câteva secunde revine automat în meniul principal sau
/// poate fi schimbată scena la apăsarea Enter / Escape.
class GameOverScene : public IScene {
private:
    Renderer* renderer; ///< Renderer-ul folosit pentru desenarea scenei.
    SceneMgr* sceneMgr; ///< Managerul de scene pentru schimbarea în „Menu”.

    float timeAlive;      ///< Timpul scurs de când scena a fost intrată.
    float autoReturnTime; ///< Timpul după care se revine automat la „Menu”.
    int   finalScore;     ///< Scorul final afișat pe ecran.

    TTF_Font* font = nullptr; ///< Fontul folosit pentru textul „GAME OVER” + scor.

public:
    /// \brief Creează o scenă GameOver legată de renderer și scene manager.
    ///
    /// \param rend Renderer-ul folosit pentru desen.
    /// \param mgr Managerul de scene pentru navigare.
    GameOverScene(Renderer* rend, SceneMgr* mgr);

    /// \brief Destructor – eliberează resursele fontului (gestionat safe in cpp).
    ~GameOverScene();

    /// \brief Actualizează timer-ul intern și revine în Menu la nevoie.
    /// \param dt Timpul scurs de la ultimul frame (secunde).
    void update(float dt) override;

    /// \brief Randează ecranul de Game Over și scorul final.
    void render() override;

    /// \brief Gestionează input-ul de la utilizator.
    ///
    /// Enter / Escape duc imediat înapoi la „Menu”.
    /// \param e Evenimentul SDL de procesat.
    void handleEvent(SDL_Event& e) override;

    /// \brief Numele scenei (folosit de SceneMgr).
    std::string getName() const override { return "GameOver"; }

    /// \brief Setează scorul final ce va fi rulat pe ecran.
    void setFinalScore(int score) { finalScore = score; }

    /// \brief Se apelează când scena devine activă.
    ///
    /// Resetează timer-ul și loghează intrarea în scenă.
    void onEnter() override;

    /// \brief Se apelează când scena iese din activ.
    void onExit() override;
};
