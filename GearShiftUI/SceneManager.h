#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include "IScene.h"

/// \brief Manager pentru scenele jocului (Menu, Game, GameOver etc.).
///
/// Deține un map de scene, știe scena curentă și gestionează tranzițiile
/// într-un mod sigur (tranziția se face la începutul lui update()).
class SceneMgr {
private:
    /// \brief Toate scenele înregistrate, indexate după nume.
    std::unordered_map<std::string, std::shared_ptr<IScene>> scenes;
    /// \brief Scena curent activă.
    std::shared_ptr<IScene> current;
    /// \brief Numele scenei spre care vrem să comutăm.
    std::string nextName;
    /// \brief Flag intern care indică dacă există o tranziție pending.
    bool shouldChange;

    /// \brief Metodă helper pentru a executa tranziția dintre scene.
    ///
    /// Apelează onExit() pe scena curentă și onEnter() pe noua scenă.
    void performSceneTransition();

public:
    /// \brief Construiește un SceneMgr gol (fără scene).
    SceneMgr();

    /// \brief Adaugă (sau înlocuiește) o scenă sub numele dat.
    ///
    /// Dacă este prima scenă adăugată, devine scena curentă și i se apelează onEnter().
    ///
    /// \param name Numele logic al scenei.
    /// \param scene Instanța scenei.
    void add(const std::string& name, std::shared_ptr<IScene> scene);

    /// \brief Cere schimbarea scenei curente cu o alta, după nume.
    ///
    /// Tranziția se va executa la începutul următorului update().
    ///
    /// \param name Numele scenei spre care se va trece.
    void change(const std::string& name);

    /// \brief Obține o scenă după nume, sau nullptr dacă nu există.
    std::shared_ptr<IScene> getScene(const std::string& name) const;

    /// \brief Actualizează scena curentă.
    ///
    /// Tratează mai întâi orice tranziție pending, apoi apelează update() pe scenă.
    ///
    /// \param dt Delta time (secunde).
    void update(float dt);

    /// \brief Randează scena curentă.
    void render();

    /// \brief Trimite un eveniment SDL scenei curente.
    /// \param e Evenimentul de procesat.
    void handleEvent(SDL_Event& e);

    /// \brief Obține scena curentă (poate fi nullptr).
    std::shared_ptr<IScene> getCurrent() const { return current; }

    /// \brief Verifică dacă există o scenă cu numele dat.
    bool has(const std::string& name) const;
};
