#ifndef GUARD_MEGA_EVOLUTION_H
#define GUARD_MEGA_EVOLUTION_H

#include "global.h"
#include "pokemon.h"

/*
 * mega_evolution.h
 * Declares all functions for Mega Evolution and Z-Move systems.
 */

// ============================================================
// Mega Evolution Functions
// ============================================================

// Returns the Evolution entry if the battler can currently mega evolve, NULL otherwise.
const struct Evolution *CanMegaEvolve(u8 battlerId);

// Returns the mega form species for a given species + held item combo (SPECIES_NONE if none).
u16 GetMegaSpecies(u16 species, u16 heldItem);

// Returns the primal form species for a given species + held item (SPECIES_NONE if none).
u16 GetPrimalSpecies(u16 species, u16 heldItem);

// Performs the in-battle mega evolution for the given battler.
// Updates gBattleMons stats/ability. Returns TRUE if evolution occurred.
bool8 DoMegaEvolution(u8 battlerId);

// Revert all mega forms in a party back to their base forms (called at battle end).
void RevertAllMegaForms(struct Pokemon *party, u8 partyCount);

// Returns TRUE if the battler's side has a keystone (player has Mega Ring, trainer has items).
bool8 MegaEvolutionEnabled(u8 battlerId);

// Returns TRUE if the side has already mega evolved once this battle.
bool8 HasMegaEvolvedThisBattle(u8 battlerId);

// Returns TRUE if the species is a mega form (has a reversion EVO_MEGA entry with param=0).
bool8 IsMegaSpecies(u16 species);

// Returns TRUE if the species is a primal form.
bool8 IsPrimalSpecies(u16 species);

// Checks all battlers for pending primal reversion on switch-in (for Red/Blue Orbs).
bool8 TryDoPrimalReversion(u8 battlerId);

// AI helper: returns TRUE if the opponent battler should choose to mega evolve this turn.
bool8 AI_ShouldMegaEvolve(u8 battlerId);

// ============================================================
// Z-Move Functions
// ============================================================

// Returns TRUE if the given item is a Z-Crystal.
bool8 IsZCrystal(u16 item);

// Returns the Z-Crystal that matches a given type (TYPE_* constant). ITEM_NONE if no match.
u16 GetTypeZCrystal(u8 type);

// Returns the boosted Z-Move power for a damaging move.
// Uses the standard formula: power <= 55 -> 100, <= 65 -> 120, etc.
u16 GetZMovePower(u16 move);

// Returns TRUE if the battler can use a Z-Move with their current move and held item.
bool8 CanUseZMove(u8 battlerId, u8 moveIndex);

// Applies Z-Move boost to the current move being used (power/effect override).
// Call this just before damage calculation. Returns TRUE if Z-Move was triggered.
bool8 TryApplyZMoveBoost(u8 battlerId);

// AI helper: returns TRUE if the opponent should use a Z-Move on this attack.
bool8 AI_ShouldUseZMove(u8 battlerId);

#endif // GUARD_MEGA_EVOLUTION_H
