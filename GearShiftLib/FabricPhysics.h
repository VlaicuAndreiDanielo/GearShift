#pragma once
#include "IFabric.h"
#include <memory>

/// \brief Implementare de pânză (cloth) 2D bazată pe masă–arc.
///
/// Reprezintă o rețea de puncte conectate care se comportă ca un material
/// flexibil. Poate fi actualizată în timp, perturbată cu forțe locale și resetată.
class Fabric : public IFabric {
public:
    /// \brief Creează o instanță de Fabric cu o grilă de dimensiune dată.
    ///
    /// \param width Numărul de puncte pe axa X.
    /// \param height Numărul de puncte pe axa Y.
    /// \param spacing Distanța inițială între puncte.
    /// \return Un shared_ptr către IFabric implementat de Fabric.
    static std::shared_ptr<IFabric> create(int width, int height, float spacing);

    /// \brief Actualizează simularea pânzei pentru un frame.
    ///
    /// Aplică integrarea pozițiilor pentru punctele ne-pinned și relaxează
    /// constrângerile dintre puncte pentru a menține rigiditatea.
    ///
    /// \param dt Timpul scurs de la ultimul frame.
    void update(float dt) override;

    /// \brief Aplică o forță locală asupra pânzei.
    ///
    /// Toate punctele aflate într-un cerc de rază \p radius în jurul (mx, my)
    /// vor primi o forță proporțională cu distanța până la centru.
    ///
    /// \param mx Coordonata X a centrului (de ex. mouse).
    /// \param my Coordonata Y a centrului.
    /// \param radius Raza zonei de influență.
    /// \param strength Intensitatea forței aplicate.
    void applyForce(float mx, float my, float radius, float strength) override;

    /// \brief Resetează pânza la poziția inițială.
    void reset() override;

    /// \brief Obține vectorul cu toate punctele pânzei.
    const std::vector<Pt>& getPts() const override { return pts; }

    /// \brief Obține numărul de puncte pe axa X.
    int getW() const override { return w; }

    /// \brief Obține numărul de puncte pe axa Y.
    int getH() const override { return h; }

    /// \brief Obține referința la un punct din grilă.
    ///
    /// \param x Indexul pe axa X (0 .. w-1).
    /// \param y Indexul pe axa Y (0 .. h-1).
    /// \return Referință la punctul cerut.
    Pt& getPt(int x, int y) override;

private:
    /// \brief Constructor privat, folosit de metoda factory create().
    Fabric(int width, int height, float spacing);

    std::vector<Pt> pts;  ///< Punctele care compun pânza.
    int   w;              ///< Numărul de puncte pe axa X.
    int   h;              ///< Numărul de puncte pe axa Y.
    float space;          ///< Spațierea inițială între puncte.
    float damp;           ///< Factor de amortizare a vitezei.
    float stiff;          ///< Factor de rigiditate a constrângerilor.
};
