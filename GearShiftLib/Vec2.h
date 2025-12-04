#pragma once
#include <cmath>

/// \brief Vector 2D simplu cu operații de bază.
///
/// Folosit pentru poziții, direcții și calcule de coliziune.
struct Vec2 {
    float x = 0.0f; ///< Coordonata X.
    float y = 0.0f; ///< Coordonata Y.

    /// \brief Adunare vectorială.
    Vec2 operator+(const Vec2& other) const {
        return Vec2{ x + other.x, y + other.y };
    }

    /// \brief Scădere vectorială.
    Vec2 operator-(const Vec2& other) const {
        return Vec2{ x - other.x, y - other.y };
    }

    /// \brief Înmulțire cu un scalar.
    /// \param scalar Factorul de scalare.
    Vec2 operator*(float scalar) const {
        return Vec2{ x * scalar, y * scalar };
    }
};

/// \brief Produsul scalar (dot product) a doi vectori.
///
/// \param a Primul vector.
/// \param b Al doilea vector.
/// \return Valoarea scalară a produsului a·b.
inline float dot(const Vec2& a, const Vec2& b) {
    return a.x * b.x + a.y * b.y;
}

/// \brief Normalizează un vector (îl aduce la lungime 1).
///
/// Dacă vectorul are lungimea 0, întoarce (0,0).
///
/// \param v Vectorul de normalizat.
/// \return Vectorul normalizat.
inline Vec2 normalize(const Vec2& v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length == 0.0f) return { 0,0 };
    return Vec2{ v.x / length, v.y / length };
}
