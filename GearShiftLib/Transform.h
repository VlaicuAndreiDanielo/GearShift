#pragma once
#include "Vec2.h"

/// \brief Reprezintă poziția și rotația unui obiect în spațiul 2D.
///
/// Oferă metode pentru setarea / citirea poziției, rotației și
/// pentru blocarea modificărilor pe axe sau rotație. :contentReference[oaicite:7]{index=7}
class Transform {
public:
    /// \brief Creează un transform cu poziția (0,0) și rotația 0.
    Transform() = default;

    /// \brief Creează un transform cu o poziție inițială dată.
    /// \param startPos Poziția inițială.
    Transform(Vec2 startPos);

    Transform(Transform&&) = default;
    Transform(const Transform&) = default;
    Transform& operator=(Transform&&) = default;
    Transform& operator=(const Transform&) = default;
    virtual ~Transform() = default;

    /// \brief Obține poziția curentă.
    Vec2 getPos() const;

    /// \brief Obține coordonata X curentă.
    float getX() const;

    /// \brief Obține coordonata Y curentă.
    float getY() const;

    /// \brief Setează poziția completă (X, Y).
    ///
    /// Dacă axele sunt blocate (lock X/Y), coordonatele respective nu se schimbă.
    /// \param pos Noua poziție.
    void setPosition(Vec2 pos);

    /// \brief Setează coordonata X.
    ///
    /// Nu are efect dacă axa X este blocată.
    /// \param newX Noua coordonată X.
    void setX(float newX);

    /// \brief Setează coordonata Y.
    ///
    /// Nu are efect dacă axa Y este blocată.
    /// \param newY Noua coordonată Y.
    void setY(float newY);

    /// \brief Setează rotația (în radiani).
    ///
    /// Nu are efect dacă rotația este blocată.
    /// \param radians Unghiul în radiani.
    void setRotation(float radians);

    /// \brief Obține rotația curentă (în radiani).
    float getRotation() const;

    /// \brief Marchează transform-ul ca „fix” (nu este neapărat folosit în toate logicele).
    /// \param fixed True dacă transform-ul este fix.
    void setFixed(bool fixed);

    /// \brief Verifică dacă transform-ul este marcat ca fix.
    bool getFixed() const;

    /// \brief Blochează / deblochează modificarea coordonatei X.
    void setLockX(bool lockX);

    /// \brief Blochează / deblochează modificarea coordonatei Y.
    void setLockY(bool lockY);

    /// \brief Blochează / deblochează modificarea rotației.
    void setLockRotation(bool lockRotation);

    /// \brief Verifică dacă axa X este blocată.
    bool isXLocked() const;

    /// \brief Verifică dacă axa Y este blocată.
    bool isYLocked() const;

    /// \brief Verifică dacă rotația este blocată.
    bool isRotationLocked() const;

private:
    Vec2  position;          ///< Poziția în spațiul 2D.
    float rotation = 0.0f;   ///< Rotația în radiani.

    bool isFixed = false; ///< Flag generic pentru „fix”.
    bool xLocked = false; ///< True dacă modificările pe X sunt blocate.
    bool yLocked = false; ///< True dacă modificările pe Y sunt blocate.
    bool rotationLocked = false; ///< True dacă modificările de rotație sunt blocate.
};
