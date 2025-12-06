#pragma once
#include <string>
#include <unordered_map>
#include "SpriteType.h"

/// \brief Map static între SpriteType și path-ul fișierului imagine.
///
/// Folosit de layer-ul de randare pentru a obține rapid calea către textura
/// corectă în funcție de tipul de sprite (PLAYER, ROAD, NPC etc.).
class SpriteMapper {
public:
    /// \brief Obține path-ul texturii asociate unui tip de sprite.
    ///
    /// Dacă sprite-ul nu există în map, poate întoarce un path gol sau unul
    /// default, în funcție de implementare.
    ///
    /// \param sprite Tipul de sprite pentru care se caută path-ul.
    /// \return Calea către fișierul imagine din assets.
    static const std::string getSpritePath(SpriteType sprite);

private:
    /// \brief Constructor privat – clasa este doar un holder static.
    SpriteMapper();

    /// \brief Map static între SpriteType și path-urile imaginilor.
    static const std::unordered_map<SpriteType, std::string> spritePathMap;
};
