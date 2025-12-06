#pragma once
#include "../GearShiftLib/IInputState.h"
#include "../GearShiftLib/CommandManager.h"
#include <SDL2/SDL.h>
#include <memory>
#include <unordered_map>

/// \brief Handler pentru input-ul de la utilizator.
///
/// Expune `IInputState` pentru logica de joc și, în plus, mapează
/// taste la comenzi (Command pattern) prin `CommandManager`.
class InputHandler : public IInputState {
private:
    const Uint8* keyState; ///< Starea curentă a tastaturii (SDL).
    int  mouseX;           ///< Coordonata X a mouse-ului.
    int  mouseY;           ///< Coordonata Y a mouse-ului.
    bool mousePressed;     ///< True dacă un buton de mouse este apăsat.
    bool pausePressedLastFrame = false; ///< Flag pentru debounce pe tasta de pauză.

    /// \brief CommandManager global folosit pentru maparea tastelor la comenzi.
    std::shared_ptr<CommandManager> commandManager;

    /// \brief Map între codul de tastă și numele comenzii înregistrate.
    std::unordered_map<SDL_Scancode, std::string> keyBindings;

public:
    /// \brief Creează un InputHandler și inițializează starea tastaturii.
    InputHandler();

    /// \brief Destructor – eliberează referințele la CommandManager.
    ~InputHandler();

    /// \brief Procesează un eveniment SDL pentru mouse (mișcare / click).
    ///
    /// \param e Evenimentul SDL de analizat.
    void update(SDL_Event& e);

    /// \brief Actualizează pointerul către starea tastaturii SDL.
    ///
    /// Trebuie apelată o dată pe frame, înainte de a citi tastele.
    void updateKeyboard();

    // --- Command system integration ---

    /// \brief Setează CommandManager-ul folosit pentru execuția comenzilor.
    /// \param cmdMgr Managerul de comenzi partajat.
    void setCommandManager(std::shared_ptr<CommandManager> cmdMgr) { commandManager = cmdMgr; }

    /// \brief Leagă o tastă de numele unei comenzi.
    ///
    /// \param key Codul de tastă SDL (scancode).
    /// \param commandName Numele comenzii înregistrate în CommandManager.
    void bindKeyToCommand(SDL_Scancode key, const std::string& commandName);

    /// \brief Verifică tastele apăsate și execută comenzile legate.
    ///
    /// Se ocupă și de debounce pentru comanda de pauză (`pause_game`).
    void executeKeyCommands();

    // --- IInputState implementation ---

    bool isUpPressed() const override;
    bool isDownPressed() const override;
    bool isLeftPressed() const override;
    bool isRightPressed() const override;

    bool isAcceleratePressed() const override;
    bool isBrakePressed() const override;

    /// \brief Verifică dacă pauza a fost apăsată „o singură dată”.
    ///
    /// Implementată cu debounce: întoarce true doar când tasta tocmai a fost apăsată.
    bool isPausePressed() override;

    int  getMouseX() const override;
    int  getMouseY() const override;
    bool isMousePressed() const override;

    /// \brief Resetează starea butoanelor de mouse (folosit după click).
    void reset();
};
