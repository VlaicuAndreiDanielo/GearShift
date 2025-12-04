#pragma once
#include "GameObject.h"

/// \brief Reprezintă camera 2D prin care este vizualizată scena.
///
/// Camera este un GameObject special, folosit pentru a determina ce parte
/// din lume este randată pe ecran.
class Camera : public GameObject {
public:
    /// \brief Creează o instanță de cameră.
    ///
    /// \param startX Poziția inițială X în lume.
    /// \param startY Poziția inițială Y în lume.
    /// \param width Lățimea viewport-ului camerei.
    /// \param height Înălțimea viewport-ului camerei.
    /// \return Un shared_ptr către noua cameră.
    static std::shared_ptr<Camera> create(
        float startX = 0,
        float startY = 0,
        float width = 1920,
        float height = 1080
    );

private:
    /// \brief Constructor privat, folosit de metoda factory create().
    Camera(
        float startX = 0,
        float startY = 0,
        float width = 1920,
        float height = 1080
    );
};
