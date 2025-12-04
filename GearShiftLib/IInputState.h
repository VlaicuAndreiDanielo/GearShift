#pragma once

/// \brief Interfață care descrie starea curentă a input-ului de la utilizator.
///
/// Implementările concrete (de ex. din SDL) furnizează informații despre
/// tastele apăsate și despre mouse, astfel încât logica de joc să fie
/// independentă de framework-ul de input.
struct IInputState {
    virtual ~IInputState() = default;

    // --- movement input ---

    /// \brief Verifică dacă input-ul „sus” este apăsat.
    virtual bool isUpPressed() const = 0;

    /// \brief Verifică dacă input-ul „jos” este apăsat.
    virtual bool isDownPressed() const = 0;

    /// \brief Verifică dacă input-ul „stânga” este apăsat.
    virtual bool isLeftPressed() const = 0;

    /// \brief Verifică dacă input-ul „dreapta” este apăsat.
    virtual bool isRightPressed() const = 0;

    // --- action input ---

    /// \brief Verifică dacă accelerația este apăsată.
    virtual bool isAcceleratePressed() const = 0;

    /// \brief Verifică dacă frâna este apăsată.
    virtual bool isBrakePressed() const = 0;

    /// \brief Verifică dacă tasta de pauză este apăsată.
    virtual bool isPausePressed() = 0;

    // --- mouse input (pentru interacțiuni de meniu / pânză) ---

    /// \brief Obține coordonata X a mouse-ului în fereastră.
    virtual int getMouseX() const = 0;

    /// \brief Obține coordonata Y a mouse-ului în fereastră.
    virtual int getMouseY() const = 0;

    /// \brief Verifică dacă un buton de mouse este apăsat.
    virtual bool isMousePressed() const = 0;
};
