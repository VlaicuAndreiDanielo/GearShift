#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "../GearShiftLib/FabricPhysics.h"

/// \brief Un „tile” din fundalul animat tip valuri.
///
/// Fiecare tile are o poziție 2D de bază (x, y), un offset vertical z
/// calculat din funcții sinus/cosinus și o culoare de bază. :contentReference[oaicite:2]{index=2}
struct Tile {
    int x, y;      ///< Poziția de bază a tile-ului.
    float z;       ///< Offset vertical animat (efect de val).
    SDL_Color col; ///< Culoarea de bază a tile-ului.
};

/// \brief Efect de fundal tip „valuri” care folosesc pânza (Fabric) ca deformare.
///
/// Construiește o grilă de tile-uri colorate, le animă cu funcții trigonometrice
/// în timp și le „agață” de punctele pânzei (IFabric) pentru a le deforma
/// în funcție de mișcarea cloth-ului. :contentReference[oaicite:3]{index=3}
class Wave {
private:
    std::vector<Tile> tiles; ///< Toate tile-urile fundalului.
    int   size;              ///< Dimensiunea (latura) unui tile, în pixeli.
    float speed;             ///< Viteza de propagare a valurilor.
    float amp;               ///< Amplitudinea maximă a valurilor.

public:
    /// \brief Creează un efect de wave pentru o zonă de ecran dată.
    ///
    /// Construcția generează o grilă de tile-uri ușor mai mare decât ecranul,
    /// pentru a permite mișcarea și deformarea fără să se vadă marginile. :contentReference[oaicite:4]{index=4}
    ///
    /// \param w Lățimea ecranului (pixeli).
    /// \param h Înălțimea ecranului (pixeli).
    /// \param tileSize Dimensiunea unui tile (pixeli).
    Wave(int w, int h, int tileSize);

    /// \brief Actualizează offset-ul vertical al fiecărui tile.
    ///
    /// Folosește combinații de \c sin și \c cos în funcție de timp și de
    /// poziția tile-ului pentru a crea un efect de valuri. :contentReference[oaicite:5]{index=5}
    ///
    /// \param dt Timpul scurs de la ultimul frame (secunde).
    /// \param time Timpul global acumulat (pentru animație continuă).
    void update(float dt, float time);

    /// \brief Randează fundalul în funcție de pozițiile pânzei (Fabric).
    ///
    /// Ia pentru fiecare tile cel mai apropiat \c Pt din pânză, calculează
    /// un offset (ox, oy) și aplică z + offset pentru a obține un efect
    /// de deformare sincron cu mișcarea cloth-ului. :contentReference[oaicite:6]{index=6}
    ///
    /// \param rend Renderer-ul SDL pentru desen.
    /// \param pts Vectorul de puncte din pânză.
    /// \param fw Numărul de puncte pe axa X (fabric width).
    /// \param fh Numărul de puncte pe axa Y (fabric height).
    void render(SDL_Renderer* rend, const std::vector<Pt>& pts, int fw, int fh);

    /// \brief Placeholder pentru încărcarea unei imagini de fundal.
    ///
    /// În implementarea curentă nu face nimic, dar poate fi extinsă
    /// pentru a folosi o textură în loc de simple dreptunghiuri colorate.
    ///
    /// \param path Calea către fișierul imagine.
    void loadImg(const char* path);
};
