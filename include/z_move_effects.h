#ifndef GUARD_Z_MOVE_EFFECTS_H
#define GUARD_Z_MOVE_EFFECTS_H

/*
 * z_move_effects.h
 * Constants for the side effects that Z-Status moves grant to the user.
 * These are stored in BattleMove.zMoveEffect for status moves.
 * Damaging moves use BattleMove.zMovePower instead and zMoveEffect = Z_EFFECT_NONE.
 */

#define Z_EFFECT_NONE                0
#define Z_EFFECT_RESET_STATS         1  // Reset all stat drops to 0 (Breakneck Blitz etc.)
#define Z_EFFECT_ALL_STATS_UP_1      2  // +1 to all stats
#define Z_EFFECT_BOOST_CRITS         3  // Raise critical hit ratio by 2 stages
#define Z_EFFECT_FOLLOW_ME           4  // Use Follow Me effect
#define Z_EFFECT_CURSE               5  // Curse effect (Ghost: halve HP; else: +Atk +Def -Spe)
#define Z_EFFECT_RECOVER_HP          6  // Restore 100% HP
#define Z_EFFECT_RESTORE_REPLACEMENT_HP 7 // Heal 100% HP of a replacement Pokemon

// +1 stat boosts
#define Z_EFFECT_ATK_UP_1            8
#define Z_EFFECT_DEF_UP_1            9
#define Z_EFFECT_SPD_UP_1            10
#define Z_EFFECT_SPATK_UP_1          11
#define Z_EFFECT_SPDEF_UP_1          12
#define Z_EFFECT_ACC_UP_1            13
#define Z_EFFECT_EVSN_UP_1           14

// +2 stat boosts
#define Z_EFFECT_ATK_UP_2            15
#define Z_EFFECT_DEF_UP_2            16
#define Z_EFFECT_SPD_UP_2            17
#define Z_EFFECT_SPATK_UP_2          18
#define Z_EFFECT_SPDEF_UP_2          19
#define Z_EFFECT_ACC_UP_2            20
#define Z_EFFECT_EVSN_UP_2           21

// +3 stat boosts
#define Z_EFFECT_ATK_UP_3            22
#define Z_EFFECT_DEF_UP_3            23
#define Z_EFFECT_SPD_UP_3            24
#define Z_EFFECT_SPATK_UP_3          25
#define Z_EFFECT_SPDEF_UP_3          26
#define Z_EFFECT_ACC_UP_3            27
#define Z_EFFECT_EVSN_UP_3           28

#define Z_EFFECT_COUNT               29

#endif // GUARD_Z_MOVE_EFFECTS_H
