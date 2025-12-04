#pragma once
#include <vector>

/// \brief Reprezintă un punct din pânza (cloth) simulată.
///
/// Fiecare punct reține poziția curentă, poziția anterioară (pentru integrare
/// de tip Verlet), forța acumulată și un flag dacă este sau nu „pin-uit”.
struct Pt {
    float x, y;   ///< Poziția curentă a punctului.
    float ox, oy; ///< Poziția anterioară (pentru calculul vitezei implicite).
    float fx, fy; ///< Forța acumulată ce urmează a fi aplicată.
    bool pinned;  ///< True dacă punctul este fixat (nu se mișcă).

    /// \brief Creează un punct la poziția dată, fără forță inițială.
    /// \param _x Coordonata X inițială.
    /// \param _y Coordonata Y inițială.
    Pt(float _x, float _y) : x(_x), y(_y), ox(_x), oy(_y),
        fx(0), fy(0), pinned(false) {
    }
};

/// \brief Interfață pentru o pânză (cloth) 2D.
///
/// Expune operații pentru actualizare, aplicare de forțe locale și acces
/// la punctele care compun structura.
class IFabric {
public:
    /// \brief Actualizează simularea pânzei pentru un frame.
    /// \param dt Timpul scurs de la ultimul frame (în secunde).
    virtual void update(float dt) = 0;

    /// \brief Aplică o forță locală asupra pânzei.
    ///
    /// \param mx Coordonata X a centrului (de exemplu poziția mouse-ului).
    /// \param my Coordonata Y a centrului.
    /// \param radius Raza zonei de influență.
    /// \param strength Intensitatea forței aplicate.
    virtual void applyForce(float mx, float my, float radius, float strength) = 0;

    /// \brief Resetează pânza la starea inițială.
    virtual void reset() = 0;

    /// \brief Obține toate punctele pânzei.
    /// \return Un vector constant cu punctele pânzei.
    virtual const std::vector<Pt>& getPts() const = 0;

    /// \brief Obține numărul de puncte pe axa X.
    virtual int getW() const = 0;

    /// \brief Obține numărul de puncte pe axa Y.
    virtual int getH() const = 0;

    /// \brief Obține o referință la un punct din grilă.
    ///
    /// \param x Indexul pe axa X.
    /// \param y Indexul pe axa Y.
    /// \return Referință la punctul cerut.
    virtual Pt& getPt(int x, int y) = 0;
};
