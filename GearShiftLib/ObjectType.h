#pragma once

/// \brief Tipuri logice de obiecte din joc.
///
/// Sunt folosite pentru a identifica rolul unui GameObject (jucător, drum,
/// NPC, obstacle, fuel etc.) în logica de joc și la coliziuni.
enum class ObjectType {
    NONE,       ///< Tip necunoscut / implicit.
    TRIGGER,    ///< Obiect folosit doar ca trigger (fără coliziune fizică).
    PLAYER,     ///< Mașina controlată de jucător.
    CAMERA,     ///< Obiect de tip cameră.
    ROAD,       ///< Segment de drum.
    ROAD_GUARD, ///< Gard margine de drum / barieră.
    NPC,        ///< Trafic (mașini controlate de AI).
    OBSTACLE,   ///< Obstacol din decor.
    FUEL        ///< Bidon / obiect de fuel colectabil.
};
