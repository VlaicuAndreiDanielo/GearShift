#pragma once

/// \brief Tipuri de sprite-uri utilizate în atlasul grafic al jocului.
///
/// Sunt folosite de layer-ul de randare pentru a selecta textura corespunzătoare
/// fiecărui GameObject.
enum class SpriteType {
    NONE,           ///< Fără sprite (invizibil sau neinițializat).
    PLAYER,         ///< Mașina jucătorului.
    ROAD,           ///< Textura de drum.
    ROAD_GUARD,     ///< Gărduleț / barieră de margine.
    BASE_NPC_1,     ///< Primul tip de mașină NPC.
    BASE_NPC_2,     ///< Al doilea tip de mașină NPC.
    BASE_NPC_3,     ///< Al treilea tip de mașină NPC.
    BASE_NPC_4,     ///< Al patrulea tip de mașină NPC.
    FUEL_CANISTER,  ///< Bidon de combustibil colectabil.
};
