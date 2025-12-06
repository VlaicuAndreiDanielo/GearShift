#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <functional>
#include <memory>

// Forward declaration
class ICommand;

/// \brief Buton UI simplu folosit în meniuri.
///
/// Desenează un dreptunghi colorat cu text centrat, detectează hover-ul
/// și click-ul și, la click, execută fie o ICommand, fie un callback funcțional.
class Btn {
private:
    SDL_Rect rect;        ///< Zona butonului pe ecran.
    std::string txt;      ///< Textul afișat pe buton.
    SDL_Texture* tex;     ///< Textura generată din font + text.
    SDL_Color norm;       ///< Culoare normală (ne-hover).
    SDL_Color hover;      ///< Culoare când mouse-ul e deasupra.
    bool isHover;         ///< True dacă mouse-ul este peste buton.

    /// \brief Command asociată butonului (interfața nouă).
    std::shared_ptr<ICommand> command;

    /// \brief Callback funcțional legacy (backward compatibility).
    std::function<void()> onClick;

    /// \brief Flag pentru a preveni double-cleanup la destructor.
    bool cleanedUp;

public:
    /// \brief Creează un buton cu text, poziție și dimensiune date.
    ///
    /// \param rend Renderer-ul SDL folosit pentru a crea textura textului.
    /// \param font Fontul folosit pentru text.
    /// \param text Textul de afișat.
    /// \param x Poziția X a butonului.
    /// \param y Poziția Y a butonului.
    /// \param w Lățimea butonului.
    /// \param h Înălțimea butonului.
    Btn(SDL_Renderer* rend, TTF_Font* font, const std::string& text,
        int x, int y, int w, int h);

    /// \brief Destructor – marchează textura pentru cleanup sigur.
    ~Btn();

    /// \brief Actualizează starea de hover în funcție de poziția mouse-ului.
    /// \param mx Coordonata X a mouse-ului.
    /// \param my Coordonata Y a mouse-ului.
    void update(int mx, int my);

    /// \brief Gestionează un click de mouse la coordonatele date.
    ///
    /// Dacă click-ul este în interiorul butonului, preferă să execute
    /// ICommand (dacă există), altfel callback-ul funcțional.
    ///
    /// \param mx Coordonata X a click-ului.
    /// \param my Coordonata Y a click-ului.
    void handleClick(int mx, int my);

    /// \brief Randează butonul (rect + text) folosind renderer-ul dat.
    /// \param rend Renderer-ul SDL folosit la desenare.
    void render(SDL_Renderer* rend);

    /// \brief Setează comanda care va fi executată la click.
    void setCommand(std::shared_ptr<ICommand> cmd) { command = cmd; }

    /// \brief Setează un callback funcțional pentru click (interfață legacy).
    void setClick(std::function<void()> cb) { onClick = cb; }

    /// \brief Verifică dacă un punct (x,y) se află în interiorul butonului.
    bool contains(int x, int y) const;
};
