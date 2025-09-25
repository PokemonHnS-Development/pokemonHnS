#ifndef GUARD_CONSTANTS_FLAGS_H
#define GUARD_CONSTANTS_FLAGS_H

#include "constants/opponents.h"

// Hns Flags: A flag that is within an // HnS Block is used in HnS. A flag with // HnS next to it is also in HnS. Otherwise,
// It is most likely not used for HnS


// Temporary Flags
// These temporary flags are are cleared every time a map is loaded. They are used
// for things like shortening an NPCs introduction text if the player already spoke
// to them once.
#define TEMP_FLAGS_START 0x0
#define FLAG_TEMP_1      (TEMP_FLAGS_START + 0x1)
#define FLAG_TEMP_2      (TEMP_FLAGS_START + 0x2)
#define FLAG_TEMP_3      (TEMP_FLAGS_START + 0x3)
#define FLAG_TEMP_4      (TEMP_FLAGS_START + 0x4)
#define FLAG_TEMP_5      (TEMP_FLAGS_START + 0x5)  // Unused Flag
#define FLAG_TEMP_6      (TEMP_FLAGS_START + 0x6)  // Unused Flag
#define FLAG_TEMP_7      (TEMP_FLAGS_START + 0x7)  // Unused Flag
#define FLAG_TEMP_8      (TEMP_FLAGS_START + 0x8)  // Unused Flag
#define FLAG_TEMP_9      (TEMP_FLAGS_START + 0x9)  // Unused Flag
#define FLAG_TEMP_A      (TEMP_FLAGS_START + 0xA)  // Unused Flag
#define FLAG_TEMP_B      (TEMP_FLAGS_START + 0xB)  // Unused Flag
#define FLAG_TEMP_C      (TEMP_FLAGS_START + 0xC)  // Unused Flag
#define FLAG_TEMP_D      (TEMP_FLAGS_START + 0xD)  // Unused Flag
#define FLAG_TEMP_HIDE_FOLLOWER      (TEMP_FLAGS_START + 0xE)  // When set, follower pokemon won't be spawned
#define FLAG_TEMP_F      (TEMP_FLAGS_START + 0xF)  // Unused Flag
#define FLAG_TEMP_10     (TEMP_FLAGS_START + 0x10) // Unused Flag
#define FLAG_TEMP_11     (TEMP_FLAGS_START + 0x11)
#define FLAG_TEMP_12     (TEMP_FLAGS_START + 0x12)
#define FLAG_TEMP_13     (TEMP_FLAGS_START + 0x13)
#define FLAG_TEMP_14     (TEMP_FLAGS_START + 0x14)
#define FLAG_TEMP_15     (TEMP_FLAGS_START + 0x15)
#define FLAG_TEMP_16     (TEMP_FLAGS_START + 0x16)
#define FLAG_TEMP_17     (TEMP_FLAGS_START + 0x17)
#define FLAG_TEMP_18     (TEMP_FLAGS_START + 0x18)
#define FLAG_TEMP_19     (TEMP_FLAGS_START + 0x19)
#define FLAG_TEMP_1A     (TEMP_FLAGS_START + 0x1A)
#define FLAG_TEMP_1B     (TEMP_FLAGS_START + 0x1B)
#define FLAG_TEMP_1C     (TEMP_FLAGS_START + 0x1C)
#define FLAG_TEMP_1D     (TEMP_FLAGS_START + 0x1D)
#define FLAG_TEMP_1E     (TEMP_FLAGS_START + 0x1E)
#define FLAG_TEMP_1F     (TEMP_FLAGS_START + 0x1F)
#define TEMP_FLAGS_END   FLAG_TEMP_1F
#define NUM_TEMP_FLAGS   (TEMP_FLAGS_END - TEMP_FLAGS_START + 1)     

#define FLAG_SYS_NO_COLLISION                   0x20 // Unused Flag //DEBUG
#define FLAG_SYS_NO_ENCOUNTER                   0x21 // Unused Flag //DEBUG
#define FLAG_SYS_NO_TRAINER_SEE                 0x22 // Unused Flag //DEBUG
#define FLAG_SYS_NO_BAG_USE                     0x23 // Unused Flag //DEBUG
#define FLAG_SYS_NO_CATCHING                    0x24 // Unused Flag //DEBUG
#define FLAG_SYS_PC_FROM_DEBUG_MENU             0x25 // Unused Flag //DEBUG
#define FLAG_ARCEUS_EGG_GIVE                    0x26
#define FLAG_SYS_NO_BATTLE_DMG                  0x27 // Unused Flag //DEBUG
#define FLAG_IV_SETTER                          0x28 
#define FLAG_SIDNEY_REMATCH                     0x29 //Elite Four Rematch 1
#define FLAG_PHOEBE_REMATCH                     0x2A //Elite Four Rematch 2
#define FLAG_SYS_SET_BATTLE_BGM                 0x2B // Changes BGM
#define FLAG_WONDERTRADE_FIRSTIME               0x2C 
#define FLAG_NO_WT_BECAUSE_CHALLENGE            0x2D 
#define FLAG_GLACIA_REMATCH                     0x2E //Elite Four Rematch 3
#define FLAG_DOME_FOSSIL_ALTERING_CAVE          0x2F 
#define FLAG_CAVE_MOONSTONE                     0x30 
#define FLAG_CAVE_SUNSTONE                      0x31 
#define FLAG_EV_MAN_FIRSTIME                    0x32
#define FLAG_MODEST_MINT_LILYCOVE               0x33
#define FLAG_TIMID_MINT_MAUVILLE                0x34 
#define FLAG_HELIX_FOSSIL_ALTERING              0x35 
#define FLAG_CALM_MINT_SANDTOWER                0x36
#define FLAG_DRAKE_REMATCH                      0x37 //Elite Four Rematch 4
#define FLAG_WALLACE_REMATCH                    0x38 //Elite Four Rematch 5, Champion
#define FLAG_STEVEN_REMATCH                     0x39 // Steven Rematch, true champion
#define FLAG_SYS_BRAILLE_REGIELEKI_COMPLETED    0x3A
#define FLAG_DEFEATED_REGIELEKI                 0x3B 
#define FLAG_HIDE_REGIELEKI                     0x3C 
#define FLAG_HIDE_REGIDRAGO                     0x3D
#define FLAG_SAPPHIRE_KECLEON                   0x3E 
#define FLAG_SYS_BRAILLE_REGIDRAGO_COMPLETED    0x3F
#define FLAG_DEFEATED_REGIDRAGO                 0x40 
#define FLAG_DEFEATED_DUSKNOIR                  0x41 
#define FLAG_SYS_BRAILLE_REGIGIGAS_COMPLETED    0x42
#define FLAG_DEFEATED_REGIGIGAS                 0x43
#define FLAG_HIDE_REGIGIGAS                     0x44 
#define FLAG_DEFEATED_ARTICUNO                  0x45 
#define FLAG_DEFEATED_ZAPDOS                    0x46
#define FLAG_DEFEATED_MOLTRES                   0x47 
#define FLAG_HIDE_ARTICUNO                      0x48  //HnS
#define FLAG_HIDE_ZAPDOS                        0x49  //HnS
#define FLAG_HIDE_MOLTRES                       0x4A  //HnS
#define FLAG_DEFEATED_MEWTWO                    0x4B
#define FLAG_HIDE_MEWTWO                        0x4C  //HnS
#define FLAG_UNLOCK_BIRDS                       0x4D
#define FLAG_UNLOCK_MEWTWO                      0x4E
#define FLAG_RASH_MINT_METEOR_FALLS             0x4F

// Scripts
#define FLAG_GARBAGEFLAG_STILL  0x50
#define FLAG_SET_WALL_CLOCK                      0x51
#define FLAG_RESCUED_BIRCH                       0x52
#define FLAG_GARBAGEFLAG           0x53 //used to store calls of removed flags

#define FLAG_LIMIT_TO_50                     0x54
#define FLAG_UNLOCK_DOGS                     0x55

#define FLAG_HIDE_CONTEST_POKE_BALL          0x56  // Always set after new game, object it hides is added directly
#define FLAG_MET_RIVAL_MOM                   0x57
#define FLAG_BIRCH_AIDE_MET                  0x58
#define FLAG_DECLINED_BIKE                   0x59 
#define FLAG_RECEIVED_BIKE                   0x5A //HnS used
#define FLAG_WATTSON_REMATCH_AVAILABLE       0x5B
#define FLAG_COLLECTED_ALL_SILVER_SYMBOLS    0x5C
#define FLAG_GOOD_LUCK_SAFARI_ZONE           0x5D // Set after talking to NPC blocking Safari Zone entrance/exit once.
#define FLAG_GARBAGEFLAG2           0x5E 
#define FLAG_RECEIVED_POKEBLOCK_CASE         0x5F
#define FLAG_RECEIVED_SECRET_POWER           0x60
#define FLAG_MET_TEAM_AQUA_HARBOR            0x61
#define FLAG_TV_EXPLAINED                    0x62
#define FLAG_MAUVILLE_GYM_BARRIERS_STATE     0x63
#define FLAG_MOSSDEEP_GYM_SWITCH_1           0x64 // Leftover from the RS version of Mossdeep Gym, functionally unused
#define FLAG_MOSSDEEP_GYM_SWITCH_2           0x65 //
#define FLAG_MOSSDEEP_GYM_SWITCH_3           0x66 //
#define FLAG_MOSSDEEP_GYM_SWITCH_4           0x67 //

#define FLAG_OLD_AMBER_ALTERING_CAVE         0x68 

#define FLAG_OCEANIC_MUSEUM_MET_REPORTER     0x69
#define FLAG_RECEIVED_HM_STRENGTH            0x6A
#define FLAG_RECEIVED_HM_ROCK_SMASH          0x6B
#define FLAG_WHITEOUT_TO_LAVARIDGE           0x6C // Set after defeating Flannery, so the player cant white out from poison before receiving Go Goggles
#define FLAG_RECEIVED_HM_FLASH               0x6D
#define FLAG_RECEIVED_HM_FLY                 0x6E
#define FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT  0x6F
#define FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE  0x70
#define FLAG_FINITE_TMS                      0x71
#define FLAG_SCOTT_CALL_BATTLE_FRONTIER      0x72 // Used in order to activate a phone call from Scott, inviting the player to the SS Tidal.
#define FLAG_RECEIVED_METEORITE              0x73
#define FLAG_ADVENTURE_STARTED               0x74 // elivered egg to professor ELM
#define FLAG_DEFEATED_MAGMA_SPACE_CENTER     0x75 // Set when Team Magma is defeated at Mossdeep's Space Center.
#define FLAG_MET_HIDDEN_POWER_GIVER          0x76

#define FLAG_CANCEL_BATTLE_ROOM_CHALLENGE    0x77

#define FLAG_LANDMARK_MIRAGE_TOWER           0x78
#define FLAG_RECEIVED_TM_BRICK_BREAK         0x79
#define FLAG_RECEIVED_HM_SURF                0x7A
#define FLAG_RECEIVED_HM_DIVE                0x7B
#define FLAG_REGISTER_RIVAL_POKENAV          0x7C
#define FLAG_DEFEATED_RIVAL_ROUTE_104        0x7D
#define FLAG_DEFEATED_WALLY_VICTORY_ROAD     0x7E
#define FLAG_MET_PRETTY_PETAL_SHOP_OWNER     0x7F
#define FLAG_ENABLE_ROXANNE_FIRST_CALL       0x80 // Set after defeating Brawly. This will activate a call with Roxanne in order to register her.
#define FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN  0x81
#define FLAG_DEFEATED_RIVAL_ROUTE103         0x82
#define FLAG_RECEIVED_DOLL_Bill           0x83
#define FLAG_RECEIVED_POTION_OLDALE          0x84
#define FLAG_RECEIVED_AMULET_COIN            0x85
#define FLAG_PENDING_DAYCARE_EGG             0x86
#define FLAG_THANKED_FOR_PLAYING_WITH_WALLY  0x87
#define FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL 0x88 // Set after defeating Wally outside Mauville Gym. Will activate a call later to register Wally.
#define FLAG_RECEIVED_HM_CUT                 0x89
#define FLAG_SCOTT_CALL_FORTREE_GYM          0x8A // Triggers call from Scott after defeating Winona
#define FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY   0x8B
#define FLAG_RECEIVED_6_SODA_POP             0x8C
#define FLAG_DEFEATED_SEASHORE_HOUSE         0x8D
#define FLAG_DEVON_GOODS_STOLEN              0x8E
#define FLAG_RECOVERED_DEVON_GOODS           0x8F
#define FLAG_RETURNED_DEVON_GOODS            0x90
#define FLAG_CAUGHT_LUGIA                    0x91
#define FLAG_CAUGHT_HO_OH                    0x92
#define FLAG_MR_BRINEY_SAILING_INTRO         0x93
#define FLAG_DOCK_REJECTED_DEVON_GOODS       0x94
#define FLAG_DELIVERED_DEVON_GOODS           0x95
#define FLAG_121_FAIRY_GEM                   0x96
#define FLAG_RECEIVED_CASTFORM               0x97
#define FLAG_RECEIVED_SUPER_ROD              0x98
#define FLAG_RUSTBORO_NPC_TRADE_COMPLETED    0x99
#define FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED  0x9A
#define FLAG_FORTREE_NPC_TRADE_COMPLETED     0x9B
#define FLAG_BATTLE_FRONTIER_TRADE_DONE      0x9C
#define FLAG_FORCE_MIRAGE_TOWER_VISIBLE      0x9D
#define FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE   0x9E
#define FLAG_INTERACTED_WITH_DEVON_EMPLOYEE_GOODS_STOLEN 0x9F
#define FLAG_COOL_PAINTING_MADE              0xA0
#define FLAG_BEAUTY_PAINTING_MADE            0xA1
#define FLAG_CUTE_PAINTING_MADE              0xA2
#define FLAG_SMART_PAINTING_MADE             0xA3
#define FLAG_TOUGH_PAINTING_MADE             0xA4
#define FLAG_RECEIVED_TM_ROCK_TOMB           0xA5
#define FLAG_RECEIVED_TM_BULK_UP             0xA6
#define FLAG_RECEIVED_TM_SHOCK_WAVE          0xA7
#define FLAG_RECEIVED_TM_OVERHEAT            0xA8
#define FLAG_RECEIVED_TM_FACADE              0xA9
#define FLAG_RECEIVED_TM_AERIAL_ACE          0xAA
#define FLAG_RECEIVED_TM_CALM_MIND           0xAB
#define FLAG_RECEIVED_TM_WATER_PULSE         0xAC
#define FLAG_HIDE_SECRET_BASE_TRAINER        0xAD
#define FLAG_DECORATION_1                    0xAE
#define FLAG_DECORATION_2                    0xAF
#define FLAG_DECORATION_3                    0xB0
#define FLAG_DECORATION_4                    0xB1
#define FLAG_DECORATION_5                    0xB2
#define FLAG_DECORATION_6                    0xB3
#define FLAG_DECORATION_7                    0xB4
#define FLAG_DECORATION_8                    0xB5
#define FLAG_DECORATION_9                    0xB6
#define FLAG_DECORATION_10                   0xB7
#define FLAG_DECORATION_11                   0xB8
#define FLAG_DECORATION_12                   0xB9
#define FLAG_DECORATION_13                   0xBA
#define FLAG_DECORATION_14                   0xBB
#define FLAG_RECEIVED_POKENAV                0xBC
#define FLAG_DELIVERED_STEVEN_LETTER         0xBD
#define FLAG_DEFEATED_WALLY_MAUVILLE         0xBE
#define FLAG_DEFEATED_GRUNT_SPACE_CENTER_1F  0xBF
#define FLAG_RECEIVED_SUN_STONE_MOSSDEEP     0xC0
#define FLAG_WALLY_SPEECH                    0xC1
#define FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1   0xC2 // Leftover from the RS version of Puzzle Room 7, functionally unused
#define FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2   0xC3 //
#define FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3   0xC4 //
#define FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4   0xC5 //
#define FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5   0xC6 //
#define FLAG_RUSTURF_TUNNEL_OPENED           0xC7
#define FLAG_RECEIVED_RED_SCARF              0xC8
#define FLAG_RECEIVED_BLUE_SCARF             0xC9
#define FLAG_RECEIVED_PINK_SCARF             0xCA
#define FLAG_RECEIVED_GREEN_SCARF            0xCB
#define FLAG_RECEIVED_YELLOW_SCARF           0xCC
#define FLAG_INTERACTED_WITH_STEVEN_SPACE_CENTER    0xCD
#define FLAG_ENCOUNTERED_LATIAS_OR_LATIOS    0xCE
#define FLAG_MET_ARCHIE_METEOR_FALLS         0xCF
#define FLAG_GOT_BASEMENT_KEY_FROM_WATTSON   0xD0
#define FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON 0xD1
#define FLAG_FAN_CLUB_STRENGTH_SHARED        0xD2 // Set when you rate the strength of another trainer in Lilycove's Trainer Fan Club.
#define FLAG_DEFEATED_RIVAL_RUSTBORO         0xD3
#define FLAG_RECEIVED_RED_OR_BLUE_ORB        0xD4
#define FLAG_RECEIVED_PREMIER_BALL_RUSTBORO  0xD5
#define FLAG_ENABLE_WALLY_MATCH_CALL         0xD6
#define FLAG_ENABLE_SCOTT_MATCH_CALL         0xD7
#define FLAG_ENABLE_MOM_MATCH_CALL           0xD8
#define FLAG_MET_DIVING_TREASURE_HUNTER      0xD9
#define FLAG_MET_WAILMER_TRAINER             0xDA
#define FLAG_EVIL_LEADER_PLEASE_STOP         0xDB

#define FLAG_NEVER_SET_0x0DC                 0xDC // This flag is read, but never written to

#define FLAG_RECEIVED_GO_GOGGLES             0xDD
#define FLAG_WINGULL_SENT_ON_ERRAND          0xDE
#define FLAG_RECEIVED_MENTAL_HERB            0xDF
#define FLAG_WINGULL_DELIVERED_MAIL          0xE0
#define FLAG_RECEIVED_20_COINS               0xE1
#define FLAG_RECEIVED_STARTER_DOLL           0xE2
#define FLAG_RECEIVED_GOOD_ROD               0xE3
#define FLAG_REGI_DOORS_OPENED               0xE4
#define FLAG_RECEIVED_TM_RETURN              0xE5
#define FLAG_RECEIVED_TM_SLUDGE_BOMB         0xE6
#define FLAG_RECEIVED_TM_ROAR                0xE7
#define FLAG_RECEIVED_TM_GIGA_DRAIN          0xE8

#define FLAG_FINITE_TMS_CLERK                0xE9

#define FLAG_RECEIVED_TM_REST                0xEA
#define FLAG_RECEIVED_TM_ATTRACT             0xEB
#define FLAG_RECEIVED_GLASS_ORNAMENT         0xEC
#define FLAG_RECEIVED_SILVER_SHIELD          0xED
#define FLAG_RECEIVED_GOLD_SHIELD            0xEE
#define FLAG_USED_STORAGE_KEY                0xEF
#define FLAG_USED_ROOM_1_KEY                 0xF0
#define FLAG_USED_ROOM_2_KEY                 0xF1
#define FLAG_USED_ROOM_4_KEY                 0xF2
#define FLAG_USED_ROOM_6_KEY                 0xF3
#define FLAG_MET_PROF_COZMO                  0xF4
#define FLAG_RECEIVED_WAILMER_DOLL           0xF5
#define FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104 0xF6
#define FLAG_DEFEATED_SS_TIDAL_TRAINERS      0xF7
#define FLAG_RECEIVED_SPELON_BERRY           0xF8
#define FLAG_RECEIVED_PAMTRE_BERRY           0xF9
#define FLAG_RECEIVED_WATMEL_BERRY           0xFA
#define FLAG_RECEIVED_DURIN_BERRY            0xFB
#define FLAG_RECEIVED_BELUE_BERRY            0xFC
#define FLAG_ENABLE_RIVAL_MATCH_CALL         0xFD
#define FLAG_GARBAGEFLAG4               0xFE
#define FLAG_LATIOS_OR_LATIAS_ROAMING        0xFF
#define FLAG_RECEIVED_REPEAT_BALL            0x100
#define FLAG_RECEIVED_OLD_ROD                0x101
#define FLAG_RECEIVED_COIN_CASE              0x102
#define FLAG_RETURNED_RED_OR_BLUE_ORB        0x103
#define FLAG_RECEIVED_TM_SNATCH              0x104
#define FLAG_RECEIVED_TM_DIG                 0x105
#define FLAG_RECEIVED_TM_BULLET_SEED         0x106
#define FLAG_ENTERED_ELITE_FOUR              0x107
#define FLAG_RECEIVED_TM_HIDDEN_POWER        0x108
#define FLAG_RECEIVED_TM_TORMENT             0x109
#define FLAG_RECEIVED_LAVARIDGE_EGG          0x10A
#define FLAG_RECEIVED_REVIVED_FOSSIL_MON     0x10B
#define FLAG_SECRET_BASE_REGISTRY_ENABLED    0x10C
#define FLAG_RECEIVED_TM_THIEF               0x10D
#define FLAG_CONTEST_SKETCH_CREATED          0x10E  // Set but never read
#define FLAG_EVIL_TEAM_ESCAPED_STERN_SPOKE   0x10F
#define FLAG_RECEIVED_EXP_SHARE              0x110
#define FLAG_POKERUS_EXPLAINED               0x111
#define FLAG_RECEIVED_RUNNING_SHOES          0x112
#define FLAG_RECEIVED_QUICK_CLAW             0x113
#define FLAG_RECEIVED_KINGS_ROCK             0x114
#define FLAG_RECEIVED_MACHO_BRACE            0x115
#define FLAG_RECEIVED_SOOTHE_BELL            0x116
#define FLAG_RECEIVED_WHITE_HERB             0x117
#define FLAG_RECEIVED_SOFT_SAND              0x118
#define FLAG_ENABLE_PROF_BIRCH_MATCH_CALL    0x119
#define FLAG_RECEIVED_CLEANSE_TAG            0x11A
#define FLAG_RECEIVED_FOCUS_BAND             0x11B
#define FLAG_DECLINED_WALLY_BATTLE_MAUVILLE  0x11C
#define FLAG_RECEIVED_DEVON_SCOPE            0x11D
#define FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE  0x11E
#define FLAG_MET_DEVON_EMPLOYEE              0x11F
#define FLAG_MET_RIVAL_RUSTBORO              0x120
#define FLAG_RECEIVED_SILK_SCARF             0x121
#define FLAG_NOT_READY_FOR_BATTLE_ROUTE_120  0x122
#define FLAG_RECEIVED_SS_TICKET              0x123
#define FLAG_MET_RIVAL_LILYCOVE              0x124
#define FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE 0x125
#define FLAG_EXCHANGED_SCANNER               0x126
#define FLAG_KECLEON_FLED_FORTREE            0x127
#define FLAG_PETALBURG_MART_EXPANDED_ITEMS   0x128
#define FLAG_RECEIVED_MIRACLE_SEED           0x129
#define FLAG_RECEIVED_BELDUM                 0x12A
#define FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK   0x12B
#define FLAG_MET_FANCLUB_YOUNGER_BROTHER     0x12C
#define FLAG_RIVAL_LEFT_FOR_ROUTE103         0x12D
#define FLAG_OMIT_DIVE_FROM_STEVEN_LETTER    0x12E
#define FLAG_HAS_MATCH_CALL                  0x12F
#define FLAG_ADDED_MATCH_CALL_TO_POKENAV     0x130
#define FLAG_REGISTERED_STEVEN_POKENAV       0x131
#define FLAG_ENABLE_NORMAN_MATCH_CALL        0x132
#define FLAG_STEVEN_GUIDES_TO_CAVE_OF_ORIGIN 0x133 // Set after you follow Steven to the entrance of the Cave of Origin.
#define FLAG_MET_ARCHIE_SOOTOPOLIS           0x134
#define FLAG_MET_MAXIE_SOOTOPOLIS            0x135
#define FLAG_MET_SCOTT_RUSTBORO              0x136
#define FLAG_WALLACE_GOES_TO_SKY_PILLAR      0x137 // Set after speaking to Wallace within the Cave of Origin.
#define FLAG_RECEIVED_HM_WATERFALL           0x138
#define FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS    0x139
#define FLAG_RECEIVED_AURORA_TICKET          0x13A
#define FLAG_RECEIVED_MYSTIC_TICKET          0x13B
#define FLAG_RECEIVED_OLD_SEA_MAP            0x13C
#define FLAG_WONDER_CARD_UNUSED_1            0x13D // These Wonder Card flags are referenced but never set
#define FLAG_WONDER_CARD_UNUSED_2            0x13E
#define FLAG_WONDER_CARD_UNUSED_3            0x13F
#define FLAG_WONDER_CARD_UNUSED_4            0x140
#define FLAG_WONDER_CARD_UNUSED_5            0x141
#define FLAG_WONDER_CARD_UNUSED_6            0x142
#define FLAG_WONDER_CARD_UNUSED_7            0x143
#define FLAG_WONDER_CARD_UNUSED_8            0x144
#define FLAG_WONDER_CARD_UNUSED_9            0x145
#define FLAG_WONDER_CARD_UNUSED_10           0x146
#define FLAG_WONDER_CARD_UNUSED_11           0x147
#define FLAG_WONDER_CARD_UNUSED_12           0x148
#define FLAG_WONDER_CARD_UNUSED_13           0x149
#define FLAG_WONDER_CARD_UNUSED_14           0x14A
#define FLAG_WONDER_CARD_UNUSED_15           0x14B
#define FLAG_WONDER_CARD_UNUSED_16           0x14C
#define FLAG_WONDER_CARD_UNUSED_17           0x14D
#define NUM_WONDER_CARD_FLAGS                (1 + FLAG_WONDER_CARD_UNUSED_17 - FLAG_RECEIVED_AURORA_TICKET)

#define FLAG_MIRAGE_TOWER_VISIBLE            0x14E
#define FLAG_CHOSE_ROOT_FOSSIL               0x14F
#define FLAG_CHOSE_CLAW_FOSSIL               0x150
#define FLAG_RECEIVED_POWDER_JAR             0x151

#define FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER 0x152

#define FLAG_MET_BATTLE_FRONTIER_BREEDER     0x153
#define FLAG_MET_BATTLE_FRONTIER_MANIAC      0x154
#define FLAG_ENTERED_CONTEST                 0x155
#define FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN  0x156
#define FLAG_MET_BATTLE_FRONTIER_GAMBLER     0x157
#define FLAG_ENABLE_MR_STONE_POKENAV         0x158
#define FLAG_NURSE_MENTIONS_GOLD_CARD        0x159
#define FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR  0x15A
#define FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR 0x15B

// Trainer Rematch Flags
#define FLAG_MATCH_CALL_REGISTERED           0x15C
#define FLAG_REMATCH_ROSE                    0x15D
#define FLAG_REMATCH_ANDRES                  0x15E
#define FLAG_REMATCH_DUSTY                   0x15F
#define FLAG_REMATCH_LOLA                    0x160
#define FLAG_REMATCH_RICKY                   0x161
#define FLAG_REMATCH_LILA_AND_ROY            0x162
#define FLAG_REMATCH_CRISTIN                 0x163
#define FLAG_REMATCH_BROOKE                  0x164
#define FLAG_REMATCH_WILTON                  0x165
#define FLAG_REMATCH_VALERIE                 0x166
#define FLAG_REMATCH_CINDY                   0x167
#define FLAG_REMATCH_THALIA                  0x168
#define FLAG_REMATCH_JESSICA                 0x169
#define FLAG_REMATCH_WINSTON                 0x16A
#define FLAG_REMATCH_STEVE                   0x16B
#define FLAG_REMATCH_TONY                    0x16C
#define FLAG_REMATCH_NOB                     0x16D
#define FLAG_REMATCH_KOJI                    0x16E
#define FLAG_REMATCH_FERNANDO                0x16F
#define FLAG_REMATCH_DALTON                  0x170
#define FLAG_REMATCH_BERNIE                  0x171
#define FLAG_REMATCH_ETHAN                   0x172
#define FLAG_REMATCH_JOHN_AND_JAY            0x173
#define FLAG_REMATCH_JEFFREY                 0x174
#define FLAG_REMATCH_CAMERON                 0x175
#define FLAG_REMATCH_JACKI                   0x176
#define FLAG_REMATCH_WALTER                  0x177
#define FLAG_REMATCH_KAREN                   0x178
#define FLAG_REMATCH_JERRY                   0x179
#define FLAG_REMATCH_ANNA_AND_MEG            0x17A
#define FLAG_REMATCH_ISABEL                  0x17B
#define FLAG_REMATCH_MIGUEL                  0x17C
#define FLAG_REMATCH_TIMOTHY                 0x17D
#define FLAG_REMATCH_SHELBY                  0x17E
#define FLAG_REMATCH_CALVIN                  0x17F
#define FLAG_REMATCH_ELLIOT                  0x180
#define FLAG_REMATCH_ISAIAH                  0x181
#define FLAG_REMATCH_MARIA                   0x182
#define FLAG_REMATCH_ABIGAIL                 0x183
#define FLAG_REMATCH_DYLAN                   0x184
#define FLAG_REMATCH_KATELYN                 0x185
#define FLAG_REMATCH_BENJAMIN                0x186
#define FLAG_REMATCH_PABLO                   0x187
#define FLAG_REMATCH_NICOLAS                 0x188
#define FLAG_REMATCH_ROBERT                  0x189
#define FLAG_REMATCH_LAO                     0x18A
#define FLAG_REMATCH_CYNDY                   0x18B
#define FLAG_REMATCH_MADELINE                0x18C
#define FLAG_REMATCH_JENNY                   0x18D
#define FLAG_REMATCH_DIANA                   0x18E
#define FLAG_REMATCH_AMY_AND_LIV             0x18F
#define FLAG_REMATCH_ERNEST                  0x190
#define FLAG_REMATCH_CORY                    0x191
#define FLAG_REMATCH_EDWIN                   0x192
#define FLAG_REMATCH_LYDIA                   0x193
#define FLAG_REMATCH_ISAAC                   0x194
#define FLAG_REMATCH_GABRIELLE               0x195
#define FLAG_REMATCH_CATHERINE               0x196
#define FLAG_REMATCH_JACKSON                 0x197
#define FLAG_REMATCH_HALEY                   0x198
#define FLAG_REMATCH_JAMES                   0x199
#define FLAG_REMATCH_TRENT                   0x19A
#define FLAG_REMATCH_SAWYER                  0x19B
#define FLAG_REMATCH_KIRA_AND_DAN            0x19C
#define FLAG_REMATCH_WALLY                   0x19D
#define FLAG_REMATCH_ROXANNE                 0x19E
#define FLAG_REMATCH_BRAWLY                  0x19F
#define FLAG_REMATCH_WATTSON                 0x1A0
#define FLAG_REMATCH_FLANNERY                0x1A1
#define FLAG_REMATCH_NORMAN                  0x1A2
#define FLAG_REMATCH_WINONA                  0x1A3
#define FLAG_REMATCH_TATE_AND_LIZA           0x1A4
// Note: FLAG_REMATCH_JUAN is handled by FLAG_ENABLE_JUAN_MATCH_CALL instead.
#define FLAG_REMATCH_SIDNEY                  0x1A5
#define FLAG_REMATCH_PHOEBE                  0x1A6
#define FLAG_REMATCH_GLACIA                  0x1A7
#define FLAG_REMATCH_DRAKE                   0x1A8
#define FLAG_REMATCH_WALLACE                 0x1A9

#define FLAG_DIFFICULTY_HARD                 0x1AA
#define FLAG_NO_SHINY                        0x1AB

#define FLAG_DEFEATED_DEOXYS                 0x1AC //HnS
#define FLAG_BATTLED_DEOXYS                  0x1AD //HnS
#define FLAG_SHOWN_EON_TICKET                0x1AE
#define FLAG_SHOWN_AURORA_TICKET             0x1AF
#define FLAG_SHOWN_OLD_SEA_MAP               0x1B0
#define FLAG_MOVE_TUTOR_TAUGHT_SWAGGER       0x1B1
#define FLAG_MOVE_TUTOR_TAUGHT_ROLLOUT       0x1B2
#define FLAG_MOVE_TUTOR_TAUGHT_FURY_CUTTER   0x1B3
#define FLAG_MOVE_TUTOR_TAUGHT_MIMIC         0x1B4
#define FLAG_MOVE_TUTOR_TAUGHT_METRONOME     0x1B5
#define FLAG_MOVE_TUTOR_TAUGHT_SLEEP_TALK    0x1B6
#define FLAG_MOVE_TUTOR_TAUGHT_SUBSTITUTE    0x1B7
#define FLAG_MOVE_TUTOR_TAUGHT_DYNAMICPUNCH  0x1B8
#define FLAG_MOVE_TUTOR_TAUGHT_DOUBLE_EDGE   0x1B9
#define FLAG_MOVE_TUTOR_TAUGHT_EXPLOSION     0x1BA
#define FLAG_DEFEATED_REGIROCK               0x1BB
#define FLAG_DEFEATED_REGICE                 0x1BC
#define FLAG_DEFEATED_REGISTEEL              0x1BD
#define FLAG_DEFEATED_KYOGRE                 0x1BE
#define FLAG_DEFEATED_GROUDON                0x1BF
#define FLAG_DEFEATED_RAYQUAZA               0x1C0
#define FLAG_DEFEATED_VOLTORB_1_NEW_MAUVILLE 0x1C1
#define FLAG_DEFEATED_VOLTORB_2_NEW_MAUVILLE 0x1C2
#define FLAG_DEFEATED_VOLTORB_3_NEW_MAUVILLE 0x1C3
#define FLAG_DEFEATED_ELECTRODE_1_AQUA_HIDEOUT 0x1C4
#define FLAG_DEFEATED_ELECTRODE_2_AQUA_HIDEOUT 0x1C5
#define FLAG_DEFEATED_SUDOWOODO              0x1C6
#define FLAG_DEFEATED_MEW                    0x1C7 //HnS
#define FLAG_DEFEATED_LATIAS_OR_LATIOS       0x1C8
#define FLAG_CAUGHT_LATIAS_OR_LATIOS         0x1C9
#define FLAG_CAUGHT_MEW                      0x1CA
#define FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE 0x1CB
#define FLAG_MET_SCOTT_IN_VERDANTURF         0x1CC
#define FLAG_MET_SCOTT_IN_FALLARBOR          0x1CD
#define FLAG_MET_SCOTT_IN_LILYCOVE           0x1CE
#define FLAG_MET_SCOTT_IN_EVERGRANDE         0x1CF
#define FLAG_MET_SCOTT_ON_SS_TIDAL           0x1D0
#define FLAG_SCOTT_GIVES_BATTLE_POINTS       0x1D1
#define FLAG_COLLECTED_ALL_GOLD_SYMBOLS      0x1D2
#define FLAG_ENABLE_ROXANNE_MATCH_CALL       0x1D3
#define FLAG_ENABLE_BRAWLY_MATCH_CALL        0x1D4
#define FLAG_ENABLE_WATTSON_MATCH_CALL       0x1D5
#define FLAG_ENABLE_FLANNERY_MATCH_CALL      0x1D6
#define FLAG_ENABLE_WINONA_MATCH_CALL        0x1D7
#define FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL 0x1D8
#define FLAG_ENABLE_JUAN_MATCH_CALL          0x1D9

#define FLAG_WT_ENABLED                      0x1DA

#define FLAG_SHOWN_MYSTIC_TICKET             0x1DB
#define FLAG_DEFEATED_HO_OH                  0x1DC
#define FLAG_DEFEATED_LUGIA                  0x1DD

#define FLAG_INFINITE_STUFF                  0x1DE
#define FLAG_INFINITE_STUFF_GIRL             0x1DF
#define FLAG_WT_ENABLED_RANDOMIZER           0x1E0
#define FLAG_FERTILIZER_ROUTE_102            0x1E1
#define FLAG_UNLIMITIED_WONDERTRADE          0x1E2
#define FLAG_MINTS_ENABLED                   0x1E3

// Mystery Gift Flags (Unknown)
#define FLAG_MYSTERY_GIFT_DONE               0x1E4
#define FLAG_MYSTERY_GIFT_1                  0x1E5
#define FLAG_MYSTERY_GIFT_2                  0x1E6
#define FLAG_MYSTERY_GIFT_3                  0x1E7
#define FLAG_MYSTERY_GIFT_4                  0x1E8
#define FLAG_MYSTERY_GIFT_5                  0x1E9
#define FLAG_MYSTERY_GIFT_6                  0x1EA
#define FLAG_MYSTERY_GIFT_7                  0x1EB
#define FLAG_MYSTERY_GIFT_8                  0x1EC
#define FLAG_MYSTERY_GIFT_9                  0x1ED
#define FLAG_MYSTERY_GIFT_10                 0x1EE
#define FLAG_MYSTERY_GIFT_11                 0x1EF
#define FLAG_MYSTERY_GIFT_12                 0x1F0
#define FLAG_MYSTERY_GIFT_13                 0x1F1
#define FLAG_MYSTERY_GIFT_14                 0x1F2
#define FLAG_MYSTERY_GIFT_15                 0x1F3

// Emerald Hidden Items
#define FLAG_HIDDEN_ITEMS_START                                                         0x1F4
#define FLAG_HIDDEN_ITEM_LAVARIDGE_TOWN_ICE_HEAL             (FLAG_HIDDEN_ITEMS_START + 0x00)
#define FLAG_HIDDEN_ITEM_TRICK_HOUSE_NUGGET                  (FLAG_HIDDEN_ITEMS_START + 0x01)
#define FLAG_HIDDEN_ITEM_ROUTE_111_STARDUST                  (FLAG_HIDDEN_ITEMS_START + 0x02)
#define FLAG_HIDDEN_ITEM_ROUTE_113_ETHER                     (FLAG_HIDDEN_ITEMS_START + 0x03)
#define FLAG_HIDDEN_ITEM_ROUTE_114_CARBOS                    (FLAG_HIDDEN_ITEMS_START + 0x04)
#define FLAG_HIDDEN_ITEM_ROUTE_119_CALCIUM                   (FLAG_HIDDEN_ITEMS_START + 0x05)
#define FLAG_HIDDEN_ITEM_ROUTE_119_ULTRA_BALL                (FLAG_HIDDEN_ITEMS_START + 0x06)
#define FLAG_HIDDEN_ITEM_ROUTE_123_SUPER_REPEL               (FLAG_HIDDEN_ITEMS_START + 0x07)
#define FLAG_HIDDEN_ITEM_UNDERWATER_124_CARBOS               (FLAG_HIDDEN_ITEMS_START + 0x08)
#define FLAG_HIDDEN_ITEM_UNDERWATER_124_GREEN_SHARD          (FLAG_HIDDEN_ITEMS_START + 0x09)
#define FLAG_HIDDEN_ITEM_UNDERWATER_124_PEARL                (FLAG_HIDDEN_ITEMS_START + 0x0A)
#define FLAG_HIDDEN_ITEM_UNDERWATER_124_BIG_PEARL            (FLAG_HIDDEN_ITEMS_START + 0x0B)
#define FLAG_HIDDEN_ITEM_UNDERWATER_126_BLUE_SHARD           (FLAG_HIDDEN_ITEMS_START + 0x0C)
#define FLAG_HIDDEN_ITEM_UNDERWATER_124_HEART_SCALE_1        (FLAG_HIDDEN_ITEMS_START + 0x0D)
#define FLAG_HIDDEN_ITEM_UNDERWATER_126_HEART_SCALE          (FLAG_HIDDEN_ITEMS_START + 0x0E)
#define FLAG_HIDDEN_ITEM_UNDERWATER_126_ULTRA_BALL           (FLAG_HIDDEN_ITEMS_START + 0x0F)
#define FLAG_HIDDEN_ITEM_UNDERWATER_126_STARDUST             (FLAG_HIDDEN_ITEMS_START + 0x10)
#define FLAG_HIDDEN_ITEM_UNDERWATER_126_PEARL                (FLAG_HIDDEN_ITEMS_START + 0x11)
#define FLAG_HIDDEN_ITEM_UNDERWATER_126_YELLOW_SHARD         (FLAG_HIDDEN_ITEMS_START + 0x12)
#define FLAG_HIDDEN_ITEM_UNDERWATER_126_IRON                 (FLAG_HIDDEN_ITEMS_START + 0x13)
#define FLAG_HIDDEN_ITEM_UNDERWATER_126_BIG_PEARL            (FLAG_HIDDEN_ITEMS_START + 0x14)
#define FLAG_HIDDEN_ITEM_UNDERWATER_127_STAR_PIECE           (FLAG_HIDDEN_ITEMS_START + 0x15)
#define FLAG_HIDDEN_ITEM_UNDERWATER_127_HP_UP                (FLAG_HIDDEN_ITEMS_START + 0x16)
#define FLAG_HIDDEN_ITEM_UNDERWATER_127_HEART_SCALE          (FLAG_HIDDEN_ITEMS_START + 0x17)
#define FLAG_HIDDEN_ITEM_UNDERWATER_127_RED_SHARD            (FLAG_HIDDEN_ITEMS_START + 0x18)
#define FLAG_HIDDEN_ITEM_UNDERWATER_128_PROTEIN              (FLAG_HIDDEN_ITEMS_START + 0x19)
#define FLAG_HIDDEN_ITEM_UNDERWATER_128_PEARL                (FLAG_HIDDEN_ITEMS_START + 0x1A)
#define FLAG_HIDDEN_ITEM_LILYCOVE_CITY_HEART_SCALE           (FLAG_HIDDEN_ITEMS_START + 0x1B)
#define FLAG_HIDDEN_ITEM_FALLARBOR_TOWN_NUGGET               (FLAG_HIDDEN_ITEMS_START + 0x1C)
#define FLAG_HIDDEN_ITEM_MT_PYRE_EXTERIOR_ULTRA_BALL         (FLAG_HIDDEN_ITEMS_START + 0x1D)
#define FLAG_HIDDEN_ITEM_ROUTE_113_TM_DOUBLE_TEAM            (FLAG_HIDDEN_ITEMS_START + 0x1E)
#define FLAG_HIDDEN_ITEM_ABANDONED_SHIP_RM_1_KEY             (FLAG_HIDDEN_ITEMS_START + 0x1F)
#define FLAG_HIDDEN_ITEM_ABANDONED_SHIP_RM_2_KEY             (FLAG_HIDDEN_ITEMS_START + 0x20)
#define FLAG_HIDDEN_ITEM_ABANDONED_SHIP_RM_4_KEY             (FLAG_HIDDEN_ITEMS_START + 0x21)
#define FLAG_HIDDEN_ITEM_ABANDONED_SHIP_RM_6_KEY             (FLAG_HIDDEN_ITEMS_START + 0x22)
#define FLAG_HIDDEN_ITEM_SS_TIDAL_LOWER_DECK_LEFTOVERS       (FLAG_HIDDEN_ITEMS_START + 0x23)
#define FLAG_HIDDEN_ITEM_UNDERWATER_124_CALCIUM              (FLAG_HIDDEN_ITEMS_START + 0x24)
#define FLAG_HIDDEN_ITEM_ROUTE_104_POTION                    (FLAG_HIDDEN_ITEMS_START + 0x25)
#define FLAG_HIDDEN_ITEM_UNDERWATER_124_HEART_SCALE_2        (FLAG_HIDDEN_ITEMS_START + 0x26)
#define FLAG_HIDDEN_ITEM_ROUTE_121_HP_UP                     (FLAG_HIDDEN_ITEMS_START + 0x27)
#define FLAG_HIDDEN_ITEM_ROUTE_121_NUGGET                    (FLAG_HIDDEN_ITEMS_START + 0x28)
#define FLAG_HIDDEN_ITEM_ROUTE_123_REVIVE                    (FLAG_HIDDEN_ITEMS_START + 0x29)
#define FLAG_HIDDEN_ITEM_ROUTE_113_REVIVE                    (FLAG_HIDDEN_ITEMS_START + 0x2A)
#define FLAG_HIDDEN_ITEM_LILYCOVE_CITY_PP_UP                 (FLAG_HIDDEN_ITEMS_START + 0x2B)
#define FLAG_HIDDEN_ITEM_ROUTE_104_SUPER_POTION              (FLAG_HIDDEN_ITEMS_START + 0x2C)
#define FLAG_HIDDEN_ITEM_ROUTE_116_SUPER_POTION              (FLAG_HIDDEN_ITEMS_START + 0x2D)
#define FLAG_HIDDEN_ITEM_ROUTE_106_STARDUST                  (FLAG_HIDDEN_ITEMS_START + 0x2E)
#define FLAG_HIDDEN_ITEM_ROUTE_106_HEART_SCALE               (FLAG_HIDDEN_ITEMS_START + 0x2F)
#define FLAG_HIDDEN_ITEM_GRANITE_CAVE_B2F_EVERSTONE_1        (FLAG_HIDDEN_ITEMS_START + 0x30)
#define FLAG_HIDDEN_ITEM_GRANITE_CAVE_B2F_EVERSTONE_2        (FLAG_HIDDEN_ITEMS_START + 0x31)
#define FLAG_HIDDEN_ITEM_ROUTE_109_REVIVE                    (FLAG_HIDDEN_ITEMS_START + 0x32)
#define FLAG_HIDDEN_ITEM_ROUTE_109_GREAT_BALL                (FLAG_HIDDEN_ITEMS_START + 0x33)
#define FLAG_HIDDEN_ITEM_ROUTE_109_HEART_SCALE_1             (FLAG_HIDDEN_ITEMS_START + 0x34)
#define FLAG_HIDDEN_ITEM_ROUTE_110_GREAT_BALL                (FLAG_HIDDEN_ITEMS_START + 0x35)
#define FLAG_HIDDEN_ITEM_ROUTE_110_REVIVE                    (FLAG_HIDDEN_ITEMS_START + 0x36)
#define FLAG_HIDDEN_ITEM_ROUTE_110_FULL_HEAL                 (FLAG_HIDDEN_ITEMS_START + 0x37)
#define FLAG_HIDDEN_ITEM_ROUTE_111_PROTEIN                   (FLAG_HIDDEN_ITEMS_START + 0x38)
#define FLAG_HIDDEN_ITEM_ROUTE_111_RARE_CANDY                (FLAG_HIDDEN_ITEMS_START + 0x39)
#define FLAG_HIDDEN_ITEM_PETALBURG_WOODS_POTION              (FLAG_HIDDEN_ITEMS_START + 0x3A)
#define FLAG_HIDDEN_ITEM_PETALBURG_WOODS_TINY_MUSHROOM_1     (FLAG_HIDDEN_ITEMS_START + 0x3B)
#define FLAG_HIDDEN_ITEM_PETALBURG_WOODS_TINY_MUSHROOM_2     (FLAG_HIDDEN_ITEMS_START + 0x3C)
#define FLAG_HIDDEN_ITEM_PETALBURG_WOODS_POKE_BALL           (FLAG_HIDDEN_ITEMS_START + 0x3D)
#define FLAG_HIDDEN_ITEM_ROUTE_104_POKE_BALL                 (FLAG_HIDDEN_ITEMS_START + 0x3E)
#define FLAG_HIDDEN_ITEM_ROUTE_106_POKE_BALL                 (FLAG_HIDDEN_ITEMS_START + 0x3F)
#define FLAG_HIDDEN_ITEM_ROUTE_109_ETHER                     (FLAG_HIDDEN_ITEMS_START + 0x40)
#define FLAG_HIDDEN_ITEM_ROUTE_110_POKE_BALL                 (FLAG_HIDDEN_ITEMS_START + 0x41)
#define FLAG_HIDDEN_ITEM_ROUTE_118_HEART_SCALE               (FLAG_HIDDEN_ITEMS_START + 0x42)
#define FLAG_HIDDEN_ITEM_ROUTE_118_IRON                      (FLAG_HIDDEN_ITEMS_START + 0x43)
#define FLAG_HIDDEN_ITEM_ROUTE_119_FULL_HEAL                 (FLAG_HIDDEN_ITEMS_START + 0x44)
#define FLAG_HIDDEN_ITEM_ROUTE_120_RARE_CANDY_2              (FLAG_HIDDEN_ITEMS_START + 0x45)
#define FLAG_HIDDEN_ITEM_ROUTE_120_ZINC                      (FLAG_HIDDEN_ITEMS_START + 0x46)
#define FLAG_HIDDEN_ITEM_ROUTE_120_RARE_CANDY_1              (FLAG_HIDDEN_ITEMS_START + 0x47)
#define FLAG_HIDDEN_ITEM_ROUTE_117_REPEL                     (FLAG_HIDDEN_ITEMS_START + 0x48)
#define FLAG_HIDDEN_ITEM_ROUTE_121_FULL_HEAL                 (FLAG_HIDDEN_ITEMS_START + 0x49)
#define FLAG_HIDDEN_ITEM_ROUTE_123_HYPER_POTION              (FLAG_HIDDEN_ITEMS_START + 0x4A)
#define FLAG_HIDDEN_ITEM_LILYCOVE_CITY_POKE_BALL             (FLAG_HIDDEN_ITEMS_START + 0x4B)
#define FLAG_HIDDEN_ITEM_JAGGED_PASS_GREAT_BALL              (FLAG_HIDDEN_ITEMS_START + 0x4C)
#define FLAG_HIDDEN_ITEM_JAGGED_PASS_FULL_HEAL               (FLAG_HIDDEN_ITEMS_START + 0x4D)
#define FLAG_HIDDEN_ITEM_MT_PYRE_EXTERIOR_MAX_ETHER          (FLAG_HIDDEN_ITEMS_START + 0x4E)
#define FLAG_HIDDEN_ITEM_MT_PYRE_SUMMIT_ZINC                 (FLAG_HIDDEN_ITEMS_START + 0x4F)
#define FLAG_HIDDEN_ITEM_MT_PYRE_SUMMIT_RARE_CANDY           (FLAG_HIDDEN_ITEMS_START + 0x50)
#define FLAG_HIDDEN_ITEM_VICTORY_ROAD_1F_ULTRA_BALL          (FLAG_HIDDEN_ITEMS_START + 0x51)
#define FLAG_HIDDEN_ITEM_VICTORY_ROAD_B2F_ELIXIR             (FLAG_HIDDEN_ITEMS_START + 0x52)
#define FLAG_HIDDEN_ITEM_VICTORY_ROAD_B2F_MAX_REPEL          (FLAG_HIDDEN_ITEMS_START + 0x53)
#define FLAG_HIDDEN_ITEM_ROUTE_120_REVIVE                    (FLAG_HIDDEN_ITEMS_START + 0x54)
#define FLAG_HIDDEN_ITEM_ROUTE_104_ANTIDOTE                  (FLAG_HIDDEN_ITEMS_START + 0x55)
#define FLAG_HIDDEN_ITEM_ROUTE_108_RARE_CANDY                (FLAG_HIDDEN_ITEMS_START + 0x56)
#define FLAG_HIDDEN_ITEM_ROUTE_119_MAX_ETHER                 (FLAG_HIDDEN_ITEMS_START + 0x57)
#define FLAG_HIDDEN_ITEM_ROUTE_104_HEART_SCALE               (FLAG_HIDDEN_ITEMS_START + 0x58)
#define FLAG_HIDDEN_ITEM_ROUTE_105_HEART_SCALE               (FLAG_HIDDEN_ITEMS_START + 0x59)
#define FLAG_HIDDEN_ITEM_ROUTE_109_HEART_SCALE_2             (FLAG_HIDDEN_ITEMS_START + 0x5A)
#define FLAG_HIDDEN_ITEM_ROUTE_109_HEART_SCALE_3             (FLAG_HIDDEN_ITEMS_START + 0x5B)
#define FLAG_HIDDEN_ITEM_ROUTE_128_HEART_SCALE_1             (FLAG_HIDDEN_ITEMS_START + 0x5C)
#define FLAG_HIDDEN_ITEM_ROUTE_128_HEART_SCALE_2             (FLAG_HIDDEN_ITEMS_START + 0x5D)
#define FLAG_HIDDEN_ITEM_ROUTE_128_HEART_SCALE_3             (FLAG_HIDDEN_ITEMS_START + 0x5E)
#define FLAG_HIDDEN_ITEM_PETALBURG_CITY_RARE_CANDY           (FLAG_HIDDEN_ITEMS_START + 0x5F)
#define FLAG_HIDDEN_ITEM_ROUTE_116_BLACK_GLASSES             (FLAG_HIDDEN_ITEMS_START + 0x60)
#define FLAG_HIDDEN_ITEM_ROUTE_115_HEART_SCALE               (FLAG_HIDDEN_ITEMS_START + 0x61)
#define FLAG_HIDDEN_ITEM_ROUTE_113_NUGGET                    (FLAG_HIDDEN_ITEMS_START + 0x62)
#define FLAG_HIDDEN_ITEM_ROUTE_123_PP_UP                     (FLAG_HIDDEN_ITEMS_START + 0x63)
#define FLAG_HIDDEN_ITEM_ROUTE_121_MAX_REVIVE                (FLAG_HIDDEN_ITEMS_START + 0x64)
#define FLAG_HIDDEN_ITEM_ARTISAN_CAVE_B1F_CALCIUM            (FLAG_HIDDEN_ITEMS_START + 0x65)
#define FLAG_HIDDEN_ITEM_ARTISAN_CAVE_B1F_ZINC               (FLAG_HIDDEN_ITEMS_START + 0x66)
#define FLAG_HIDDEN_ITEM_ARTISAN_CAVE_B1F_PROTEIN            (FLAG_HIDDEN_ITEMS_START + 0x67)
#define FLAG_HIDDEN_ITEM_ARTISAN_CAVE_B1F_IRON               (FLAG_HIDDEN_ITEMS_START + 0x68)
#define FLAG_HIDDEN_ITEM_SAFARI_ZONE_SOUTH_EAST_FULL_RESTORE (FLAG_HIDDEN_ITEMS_START + 0x69)
#define FLAG_HIDDEN_ITEM_SAFARI_ZONE_NORTH_EAST_RARE_CANDY   (FLAG_HIDDEN_ITEMS_START + 0x6A)
#define FLAG_HIDDEN_ITEM_SAFARI_ZONE_NORTH_EAST_ZINC         (FLAG_HIDDEN_ITEMS_START + 0x6B)
#define FLAG_HIDDEN_ITEM_SAFARI_ZONE_SOUTH_EAST_PP_UP        (FLAG_HIDDEN_ITEMS_START + 0x6C)
#define FLAG_HIDDEN_ITEM_NAVEL_ROCK_TOP_SACRED_ASH           (FLAG_HIDDEN_ITEMS_START + 0x6D)
#define FLAG_HIDDEN_ITEM_ROUTE_123_RARE_CANDY                (FLAG_HIDDEN_ITEMS_START + 0x6E)
#define FLAG_HIDDEN_ITEM_ROUTE_105_BIG_PEARL                 (FLAG_HIDDEN_ITEMS_START + 0x6F)

#define FLAG_MINTS_CLERK   0x264
#define FLAG_EXTRA_LEGENDARIES  0x265
#define FLAG_OLD_MAN_AND_DUSCLOPS  0x266
#define FLAG_CERULEAN_CAVE_LUCKY_EGG  0x267
#define FLAG_MET_FRONTIER_ELEMENTAL_MOVE_TUTOR  0x268 //HnSFLAGS SPILLOVER
#define FLAG_HIDE_WHIRL_ISLANDS_KIMONO_GIRLS  0x269 // Set after compelted legendary event
#define FLAG_HIDE_TIN_TOWER_KIMONO_GIRLS  0x26A // Set after completing legendary event
#define FLAG_NIGHT_POKEMON  0x26B // Set at day to hide nighttime overworld pokemon
#define FLAG_DAY_POKEMON  0x26C // Set at night to hide daytime overworld pokemon
#define FLAG_DEFEATED_PEWTER_GYM  0x26D // KANTO GYM LEADER FLAGS
#define FLAG_DEFEATED_CERULEAN_GYM  0x26E 
#define FLAG_DEFEATED_VERMILION_GYM  0x26F 
#define FLAG_DEFEATED_CELADON_GYM  0x270 
#define FLAG_DEFEATED_SAFFRON_GYM  0x271 
#define FLAG_DEFEATED_FUCHSIA_GYM  0x272 
#define FLAG_DEFEATED_CINNABAR_ISLAND_GYM  0x273 
#define FLAG_DEFEATED_VIRIDIAN_GYM  0x274 
#define FLAG_HIDE_CELADON_FALKNER  0x275  //gym leader rematches
#define FLAG_HIDE_DOJO_FALKNER  0x276 
#define FLAG_HIDE_VIRIDIAN_BUGSY  0x277 
#define FLAG_HIDE_DOJO_BUGSY  0x278 
#define FLAG_HIDE_DEPTSTORE_WHITNEY  0x279 
#define FLAG_HIDE_DOJO_WHITNEY  0x27A 
#define FLAG_HIDE_BELLCHIME_MORTY  0x27B 
#define FLAG_HIDE_DOJO_MORTY  0x27C 
#define FLAG_HIDE_DOJO_CHUCK  0x27D 
#define FLAG_HIDE_CAFE_JASMINE  0x27E 
#define FLAG_HIDE_DOJO_JASMINE  0x27F 
#define FLAG_HIDE_LAKE_PRYCE  0x280 
#define FLAG_HIDE_DOJO_PRYCE  0x281 
#define FLAG_HIDE_DEN_CLAIR  0x282 
#define FLAG_HIDE_DOJO_CLAIR  0x283 
#define FLAG_HIDE_DIGLETT_BROCK  0x284 
#define FLAG_HIDE_DOJO_BROCK  0x285 
#define FLAG_HIDE_CAPE_MISTY  0x286 
#define FLAG_HIDE_DOJO_MISTY  0x287 
#define FLAG_HIDE_PLANT_SURGE  0x288 
#define FLAG_HIDE_DOJO_SURGE  0x289 
#define FLAG_HIDE_FOUNTAIN_ERIKA  0x28A 
#define FLAG_HIDE_DOJO_ERIKA  0x292 
#define FLAG_HIDE_ROUTE22_JANINE  0x28B 
#define FLAG_HIDE_DOJO_JANINE  0x28C 
#define FLAG_HIDE_OLIVINE_SABRINA  0x28D 
#define FLAG_HIDE_DOJO_SABRINA  0x28E 
#define FLAG_HIDE_CINNABAR_BLAINE  0x28F 
#define FLAG_HIDE_DOJO_BLAINE  0x290 
#define FLAG_HIDE_DOJO_BLUE  0x291 
#define FLAG_UNUSED_0x293  0x293 // Unused Flag
#define FLAG_UNUSED_0x294  0x294 // Unused Flag
#define FLAG_UNUSED_0x295  0x295 // Unused Flag
#define FLAG_UNUSED_0x296  0x296 // Unused Flag
#define FLAG_UNUSED_0x297  0x297 // Unused Flag
#define FLAG_UNUSED_0x298  0x298 // Unused Flag
#define FLAG_UNUSED_0x299  0x299 // Unused Flag
#define FLAG_UNUSED_0x29A  0x29A // Unused Flag
#define FLAG_UNUSED_0x29B  0x29B // Unused Flag
#define FLAG_UNUSED_0x29C  0x29C // Unused Flag
#define FLAG_UNUSED_0x29D  0x29D // Unused Flag
#define FLAG_UNUSED_0x29E  0x29E // Unused Flag
#define FLAG_UNUSED_0x29F  0x29F // Unused Flag
#define FLAG_UNUSED_0x2A0  0x2A0 // Unused Flag
#define FLAG_UNUSED_0x2A1  0x2A1 // Unused Flag
#define FLAG_UNUSED_0x2A2  0x2A2 // Unused Flag
#define FLAG_UNUSED_0x2A3  0x2A3 // Unused Flag
#define FLAG_UNUSED_0x2A4  0x2A4 // Unused Flag
#define FLAG_UNUSED_0x2A5  0x2A5 // Unused Flag
#define FLAG_UNUSED_0x2A6  0x2A6 // Unused Flag
#define FLAG_UNUSED_0x2A7  0x2A7 // Unused Flag
#define FLAG_UNUSED_0x2A8  0x2A8 // Unused Flag
#define FLAG_UNUSED_0x2A9  0x2A9 // Unused Flag
#define FLAG_UNUSED_0x2AA  0x2AA // Unused Flag
#define FLAG_UNUSED_0x2AB  0x2AB // Unused Flag
#define FLAG_UNUSED_0x2AC  0x2AC // Unused Flag
#define FLAG_UNUSED_0x2AD  0x2AD // Unused Flag
#define FLAG_UNUSED_0x2AE  0x2AE // Unused Flag
#define FLAG_UNUSED_0x2AF  0x2AF // Unused Flag
#define FLAG_UNUSED_0x2B0  0x2B0 // Unused Flag
#define FLAG_UNUSED_0x2B1  0x2B1 // Unused Flag
#define FLAG_UNUSED_0x2B2  0x2B2 // Unused Flag
#define FLAG_UNUSED_0x2B3  0x2B3 // Unused Flag
#define FLAG_UNUSED_0x2B4  0x2B4 // Unused Flag
#define FLAG_UNUSED_0x2B5  0x2B5 // Unused Flag
#define FLAG_UNUSED_0x2B6  0x2B6 // Unused Flag
#define FLAG_UNUSED_0x2B7  0x2B7 // Unused Flag
#define FLAG_UNUSED_0x2B8  0x2B8 // Unused Flag
#define FLAG_UNUSED_0x2B9  0x2B9 // Unused Flag
#define FLAG_UNUSED_0x2BA  0x2BA // Unused Flag
#define FLAG_UNUSED_0x2BB  0x2BB // Unused Flag

// Emerald Event Flags
#define FLAG_GARBAGEFLAG6                      0x2BC
#define FLAG_HIDE_APPRENTICE                                        0x2BD
#define FLAG_HIDE_POKEMON_CENTER_2F_MYSTERY_GIFT_MAN                0x2BE
#define FLAG_HIDE_UNION_ROOM_PLAYER_1                               0x2BF
#define FLAG_HIDE_UNION_ROOM_PLAYER_2                               0x2C0
#define FLAG_HIDE_UNION_ROOM_PLAYER_3                               0x2C1
#define FLAG_HIDE_UNION_ROOM_PLAYER_4                               0x2C2
#define FLAG_HIDE_UNION_ROOM_PLAYER_5                               0x2C3
#define FLAG_HIDE_UNION_ROOM_PLAYER_6                               0x2C4
#define FLAG_HIDE_UNION_ROOM_PLAYER_7                               0x2C5
#define FLAG_HIDE_UNION_ROOM_PLAYER_8                               0x2C6
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1               0x2C7
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2               0x2C8
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3               0x2C9
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4               0x2CA
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5               0x2CB
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6               0x2CC
#define FLAG_HIDE_SAFARI_ZONE_SOUTH_CONSTRUCTION_WORKERS            0x2CD
#define FLAG_HIDE_MEW                                               0x2CE //HnS
#define FLAG_HIDE_ROUTE_104_RIVAL                                   0x2CF
#define FLAG_GARBAGEFLAG5                                           0x2D0
#define FLAG_GARBAGEFLAGS_LAB_BIRCH                                 0x2D1
#define FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM          0x2D2
#define FLAG_HIDE_ROUTE_103_RIVAL                                   0x2D3
#define FLAG_HIDE_PETALBURG_WOODS_DEVON_EMPLOYEE                    0x2D4
#define FLAG_HIDE_PETALBURG_WOODS_AQUA_GRUNT                        0x2D5
#define FLAG_HIDE_PETALBURG_CITY_WALLY                              0x2D6
#define FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_INVISIBLE_NINJA_BOY   0x2D7
#define FLAG_HIDE_PETALBURG_CITY_WALLYS_MOM                         0x2D8

#define FLAG_UNUSED_0x2D9                                           0x2D9 // Unused Flag

#define FLAG_GOT_SILK_SCARF                                         0x2DA //HnS NormalFlags Block 2
#define FLAG_GOT_MYSTICWATER                                        0x2DB
#define FLAG_GOT_BERRY_ROUTE_30_HOUSE                               0x2DC
#define FLAG_HIDE_VIOLET_CITY_EARL                                  0x2DD
#define FLAG_HIDE_TRAINER_SCHOOL_EARL                               0x2DE
#define FLAG_VIOLET_NPC_TRADE_COMPLETED                             0x2DF
#define FLAG_HOOH_BROUGHT                                           0x2E0
#define FLAG_AERODACTYL_BROUGHT                                     0x2E1
#define FLAG_KABUTO_BROUGHT                                         0x2E2
#define FLAG_OMANYTE_BROUGHT                                        0x2E3
#define FLAG_GOT_HARD_STONE                                         0x2E4
#define FLAG_GOT_POISON_BARB                                        0x2E5
#define FLAG_HIDE_SUDOWOODO                                         0x2E6
#define FLAG_HIDE_UNION_CAVE_LAPRAS                                 0x2E7
#define FLAG_GOT_CHARCOAL                                           0x2E8
#define FLAG_HIDE_CELEBI                                            0x2E9
#define FLAG_HIDE_ILEX_FOREST_KURT                                  0x2EA
#define FLAG_MOVE_TUTOR_TAUGHT_HEADBUTT                             0x2EB
#define FLAG_GOLDENROD_CITY_AIDE_VISITED                            0x2EC
#define FLAG_SHOWN_ELM_TOGEPI                                       0x2ED
#define FLAG_HIDE_AZALEA_ARIADOS_LEFT                               0x2EE
#define FLAG_HIDE_AZALEA_ARIADOS_MID                                0x2EF
#define FLAG_HIDE_AZALEA_ARIADOS_RIGHT                              0x2F0
#define FLAG_GOT_RETURN                                             0x2F1
#define FLAG_GOT_FRUSTRATION                                        0x2F2
#define FLAG_HIDE_GOLDENROD_BILL                                    0x2F3
#define FLAG_GOT_EEVEE                                              0x2F4
#define FLAG_FIXED_TRAIN                                            0x2F5//unused
#define FLAG_GOLDENROD_MACHOKE_1                                    0x2F6
#define FLAG_GOLDENROD_MACHOKE_2                                    0x2F7
#define FLAG_GOLDENROD_MACHOKE_3                                    0x2F8
#define FLAG_GOLDENROD_NPC_TRADE_COMPLETED                          0x2F9
#define FLAG_GOT_SKILL_SWAP                                         0x2FA
#define FLAG_HIDE_DEOXYS                                            0x2FB 
#define FLAG_HIDE_BIRTH_ISLAND_DEOXYS_TRIANGLE                      0x2FC
#define FLAG_GOT_MARY_BRIGHT_POWDER                                 0x2FD
#define FLAG_HIDE_BUG_CONTEST_BUGS                                  0x2FE
#define FLAG_HIDE_BUG_CONTEST_ATTENDANT_SIDE                        0x2FF
#define FLAG_GOT_QUICK_CLAW                                         0x300
#define FLAG_GOT_MAGNET                                             0x301
#define FLAG_GOT_TM_SNATCH                                          0x302
#define FLAG_HIDE_BATTLEFRONTIER_ENGINEER                           0x303
#define FLAG_GOT_SHARP_BEAK                                         0x304
#define FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL                          0x305
#define FLAG_ENABLE_BAOBA_MATCH_CALL                                0x306
#define FLAG_SAFARI_ZONE_WEST_EXPANSION                             0x307
#define FLAG_SAFARI_ZONE_EAST_EXPANSION                             0x308
#define FLAG_HIDE_LAKE_OF_RAGE_GYARADOS                             0x309
#define FLAG_HIDE_LAKE_OF_RAGE_LANCE                                0x30A
#define FLAG_HIDE_MAHOGANY_TOWN_FATMAN                              0x30B
#define FLAG_HIDE_MAHOGANY_TOWN_SHOP_NPCS                           0x30C
#define FLAG_HIDE_MAHOGANY_COP                                      0x30D
#define FLAG_HIDE_MAHOGANY_ROCKETS                                  0x30E
#define FLAG_GOT_TM_FROM_MAHOGANY_COP                               0x30F
#define FLAG_GOT_BLACK_BELT                                         0x310
#define FLAG_GOT_HIDDEN_POWER                                       0x311
#define FLAG_GOT_SPELL_TAG                                          0x312 
#define FLAG_HIDE_DRAGONS_DEN_CAVERN_SILVER                         0x313
#define FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR                          0x314//unused
#define FLAG_HIDE_DRAGONS_DEN_CAVERN_LANCE                          0x315
#define FLAG_HIDE_DRAGONS_DEN_SHRINE_CLAIR                          0x316
#define FLAG_GOT_DRATINI                                            0x317
#define FLAG_GOT_BLACK_GLASSES                                      0x318
#define FLAG_GOT_TM_SANDSTORM                                       0x319
#define FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD                        0x31A
#define FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD                       0x31B
#define FLAG_HIDE_VERMILION_EUSINE_SUICUNE                          0x31C //HnS NormalFlags Block 3
#define FLAG_GOT_VERMILION_HP_UP                                    0x31D
#define FLAG_UNUSED_FLAG_999                                        0x31E
#define FLAG_HIDE_VERMILION_SNORLAX                                 0x31F
#define FLAG_HIDE_LUGIA                                             0x320
#define FLAG_HIDE_HO_OH                                             0x321
#define FLAG_HIDE_FAN_CLUB_CLEFAIRY_DOLL                            0x322
#define FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES                      0x323
#define FLAG_RETURNED_MACHINE_PART                                  0x324
#define FLAG_HIDE_COPYCAT_CLEFAIRY_DOLL                             0x325
#define FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY                0x326
#define FLAG_GOT_TM_PSYCHIC                                         0x327
#define FLAG_GOT_HOENN_STARTER                                      0x328
#define FLAG_GOT_UP_GRADE                                           0x329
#define FLAG_GOT_CLEANSE_TAG                                        0x32A
#define FLAG_HIDE_CERULEAN_GYM_TRAINERS                             0x32B
#define FLAG_HIDE_CERULEAN_GYM_ROCKET                               0x32C
#define FLAG_HIDE_CERULEAN_CAPE_ROCKET                              0x32D
#define FLAG_HIDDEN_ITEM_MACHINE_PART                               0x32E
#define FLAG_ROUTE25_GOT_NUGGET                                     0x32F
#define FLAG_HIDE_ROUTE25_MISTY                                     0x330
#define FLAG_HIDE_ROUTE25_SUICUNE                                   0x331
#define FLAG_HIDE_ROUTE25_EUSINE                                    0x332
#define FLAG_HIDE_POWER_PLANT_ENGINEER                              0x333
#define FLAG_HIDE_CELADON_EUSINE                                    0x334
#define FLAG_GOT_TM_REST                                            0x335
#define FLAG_GOT_SUPER_ROD                                          0x336
#define FLAG_HIDE_SEAFOAM_GYMGUY                                    0x337
#define FLAG_HIDE_CINNABAR_BLUE                                     0x338
#define FLAG_HIDE_VIRIDIAN_BLUE                                     0x339 
#define FLAG_HIDE_ROUTE14_EUSINE                                    0x33A
#define FLAG_HIDE_ROUTE14_SUICUNE                                   0x33B
#define FLAG_IN_KANTO_SAFARI_ZONE                                   0x33C
#define FLAG_IS_KANTO_CHAMPION                                      0x33D
#define FLAG_HIDE_LEAGUE_BLACKBELT                                  0x33E
#define FLAG_GOT_ROUTE2_NUGGET                                      0x33F
#define FLAG_GOT_VIRIDIAN_TM_SLUDGE_BOMB                            0x340
#define FLAG_GOT_ROUTE_14_AERIAL_ACE                                0x341
#define FLAG_HIDE_PEWTER_ROOT_FOSSIL                                0x342
#define FLAG_HIDE_PEWTER_CLAW_FOSSIL                                0x343
#define FLAG_HIDE_MTMOON_SILVER                                     0x344
#define FLAG_HIDE_CERULEANCAVE_GUARD                                0x345
#define FLAG_GOT_TM_STEEL_WING                                      0x346
#define FLAG_HIDE_LATIOS                                            0x347
#define FLAG_HIDE_MTSILVER_RED                                      0x348
#define FLAG_HIDE_LATIAS                                            0x349
#define FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO                         0x34A
#define FLAG_HIDE_GROUDON                                           0x34B
#define FLAG_HIDE_KYOGRE                                            0x34C
#define FLAG_HIDE_RAYQUAZA                                          0x34D
#define FLAG_HIDE_SEAFOAM_BLAINE                                    0x34E
#define FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI                         0x34F
#define FLAG_HIDE_OLIVINE_PORT_OAK                                            0x350
#define FLAG_HIDE_ROUTE22_GIOVANNI_SILVER                                            0x351
#define FLAG_UNUSED_SET3                                            0x352
#define FLAG_UNUSED_SET4                                            0x353
#define FLAG_UNUSED_SET5                                            0x354
#define FLAG_UNUSED_SET6                                            0x355
#define FLAG_UNUSED_SET7                                            0x356
#define FLAG_UNUSED_SET8                                            0x357
#define FLAG_UNUSED_SET9                                            0x358
#define FLAG_VISITED_KANTO                                          0x359
#define FLAG_RECEIVED_ODD_EGG                                       0x35A
#define FLAG_HIDE_CERULEAN_GYM_POKEMON                                          0x35B
#define FLAG_HIDE_NEWBARKTOWN_LAB_AIDE                                          0x35C
#define FLAG_HIDE_AZALEA_TOWN_CUT_MASTER                                          0x35D
#define FLAG_UNUSED_UNSET6                                          0x35E
#define FLAG_UNUSED_UNSET7                                          0x35F
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1           0x360
#define FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2           0x361
#define FLAG_UNUSED_UNSET8                                          0x362
#define FLAG_UNUSED_UNSET9                                          0x363 
#define FLAG_HIDE_MOMS_FRIEND                                       0x364 //HnS NormalFlags Block 1
#define FLAG_MOM_VISITED                                            0x365 //mom gives good luck speech
#define FLAG_HIDE_SILVER_NEWBARKTOWN                                0x366 //for beginning
#define FLAG_HIDE_CHIKORITABALL                                     0x367 
#define FLAG_HIDE_CYNDAQUILBALL                                     0x368
#define FLAG_HIDE_TOTODILEBALL                                      0x369
#define FLAG_RECEIVED_FIRST_POTION                                  0x36A
#define FLAG_RECEIVED_FIRST_BALLS                                   0x36B
#define FLAG_HIDE_LAB_POLICEMAN                                     0x36C
#define FLAG_HIDE_MOMS_FRIEND2                                      0x36D
#define FLAG_COMPLETED_KABUTO_PUZZLE                                0x36E
#define FLAG_COMPLETED_HOOH_PUZZLE                                  0x36F
#define FLAG_COMPLETED_OMANYTE_PUZZLE                               0x370
#define FLAG_COMPLETED_AERODACTYL_PUZZLE                            0x371 
#define FLAG_GET_HEADBUTT                                           0x372
#define FLAG_HIDE_SILVER_CHERRYGROVE                                0x373
#define FLAG_HIDE_GUIDE_GENT_CHERRYGROVE                            0x374
#define FLAG_HIDE_ROUTE_30_NPCS                                     0x375
#define FLAG_DELIVERED_EGG                                          0x376
#define FLAG_HIDE_MRPOKEMON                                         0x377
#define FLAG_HIDE_BATTLE_TOWER_OPPONENT                             0x378
#define FLAG_RECEIVED_TOGEPI_EGG                                    0x379
#define FLAG_HIDE_VIOLET_CITY_AIDE                                  0x37A
#define FLAG_HIDE_SPROUT_TOWER_SILVER                               0x37B
#define FLAG_HIDE_JOHTO_GYM_LEADERS                                 0x37C
#define FLAG_HIDE_AZALEA_TOWN_ROCKETS                               0x37D
#define FLAG_HIDE_AZALEA_TOWN_SLOWPOKE                              0x37E
#define FLAG_HIDE_AZALEA_TOWN_SILVER                                0x37F
#define FLAG_HIDE_AZALEA_TOWN_FARFETCHD                             0x380
#define FLAG_HIDE_ILEX_FOREST_FARFETCHD                             0x381
#define FLAG_HIDE_KURT_1                                            0x382
#define FLAG_HIDE_KURT_2                                            0x383
#define FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET                           0x384
#define FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL                           0x385
#define FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE                      0x386
#define FLAG_UNLOCKED_KURT_BALLS                                    0x387
#define FLAG_HIDE_AZALEA_TOWN_KURT                                  0x388
#define FLAG_HIDE_SLOWPOKE_WELL_KURT                                0x389
#define FLAG_HIDE_ILEX_FOREST_FARFETCHD_1                           0x38A
#define FLAG_HIDE_ILEX_FOREST_FARFETCHD_2                           0x38B
#define FLAG_HIDE_ILEX_FOREST_FARFETCHD_3                           0x38C
#define FLAG_HIDE_ILEX_FOREST_FARFETCHD_4                           0x38D
#define FLAG_HIDE_ILEX_FOREST_APPRENTICE                            0x38E
#define FLAG_HIDE_ILEX_FOREST_MASTER                                0x38F
#define FLAG_HIDE_ILEX_FOREST_KIMONO                                0x390
#define FLAG_HIDE_GOLDENROD_ROCKET_SCOUT                            0x391
#define FLAG_HIDE_GOLDENROD_ROCKETS                                 0x392
#define FLAG_HIDE_GOLDENROD_NPCS                                    0x393 // Set, however has no purpose.
#define FLAG_RECEIVED_SQUIRTBOTTLE                                  0x394
#define FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR                    0x395
#define FLAG_HIDE_BATTLE_TOWER_REPORTER                             0x396
#define FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO                      0x397
#define FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER                      0x398
#define FLAG_GOLDENROD_SWITCH_1                                     0x399
#define FLAG_GOLDENROD_SWITCH_2                                     0x39A
#define FLAG_GOLDENROD_SWITCH_3                                     0x39B
#define FLAG_GOLDENROD_SWITCH_ORDER                                 0x39C
#define FLAG_COMPLETED_SWITCHES                                     0x39D
#define FLAG_HIDE_GOLDENROD_BEAUTY                                  0x39E
#define FLAG_ENABLE_RADIO                                           0x39F
#define FLAG_KANTO_RADIO_GOT                                        0x3A0
#define FLAG_HIDE_RADIOTOWER_GATE                                   0x3A1
#define FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1                     0x3A2
#define FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR                     0x3A3
#define FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL                       0x3A4
#define FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2                   0x3A5
#define FLAG_RELEASED_BEASTS                                        0x3A6
#define FLAG_HIDE_REGIROCK                                          0x3A7
#define FLAG_HIDE_REGICE                                            0x3A8
#define FLAG_HIDE_REGISTEEL                                         0x3A9
#define FLAG_AMPHAROS_HEALED                                        0x3AA
#define FLAG_HIDE_ECRUTEAK_BILL                                     0x3AB
#define FLAG_HIDE_ECRUTEAK_ROCKET                                   0x3AC
#define FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS                     0x3AD
#define FLAG_HIDE_BURNED_TOWER_NPCS                                 0x3AE
#define FLAG_HIDE_BURNED_TOWER_BEASTS                               0x3AF
#define FLAG_HIDE_BURNED_TOWER_B1F_EUSINE                           0x3B0
#define FLAG_HIDE_ECRUTEAK_CITY_SAGE                                0x3B1
#define FLAG_CAUGHT_ENTEI                                           0x3B2
#define FLAG_CAUGHT_RAIKOU                                          0x3B3
#define FLAG_HIDE_ROUTE39_SHADOW                                    0x3B4
#define FLAG_HIDE_OLIVINE_SILVER                                    0x3B5
#define FLAG_HIDE_OLIVINE_CITY_GYM_JASMINE                          0x3B6
#define FLAG_HIDE_LIGHTHOUSE_JASMINE                                0x3B7
#define FLAG_HIDE_ROUTE42_EUSINE                                    0x3B8
#define FLAG_HIDE_ROUTE42_SUICUNE                                   0x3B9
#define FLAG_GOT_TYROGUE                                            0x3BA
#define FLAG_BEAT_KIYO                                              0x3BB
#define FLAG_OLIVINE_NPC_TRADE_COMPLETED                            0x3BC
#define FLAG_HIDE_CIANWOOD_EUSINE                                   0x3BD
#define FLAG_HIDE_CIANWOOD_SUICUNE                                  0x3BE
#define FLAG_HIDE_ROCKETHIDEOUT_ROCKETS                             0x3BF
#define FLAG_ROCKETHIDEOUT_SWITCH                                   0x3C0 
#define FLAG_HIDE_ROCKETHIDEOUT2_LANCE_DRAGONITE                    0x3C1 
#define FLAG_HIDE_ROCKETHIDEOUT2_GATE                               0x3C2  
#define FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE1                          0x3C3 
#define FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE2                          0x3C4
#define FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE3                          0x3C5
#define FLAG_HIDE_ROCKETHIDEOUT3_LANCE_DRAGONITE                    0x3C6
#define FLAG_HIDE_ROCKETHIDEOUT3_SILVER                             0x3C7
#define FLAG_HIDE_ROCKETHIDEOUT3_GATE                               0x3C8
#define FLAG_GOT_PASSWORD_FROM_ETO                                  0x3C9
#define FLAG_GOT_PASSWORD_FROM_GRUNTF                               0x3CA
#define FLAG_HIDE_ROCKETHIDEOUT3_PETREL                             0x3CB
#define FLAG_HIDE_ROCKETHIDEOUT3_GIOVANNI                           0x3CC
#define FLAG_HIDE_ROCKETHIDEOUT3_MURKROW                            0x3CD
#define FLAG_HIDE_ROCKETHIDEOUT2_MURKROWSTAIRS                      0x3CE
#define FLAG_HIDE_ROCKETHIDEOUT2_MURKROWGATE                        0x3CF
#define FLAG_HIDE_ROCKETHIDEOUT3_MURKROWSTAIRS                      0x3D0
#define FLAG_HIDE_ROCKETHIDEOUT2_ARIANA_AND_GRUNT                   0x3D1
#define FLAG_HIDE_ROCKETHIDEOUT2_ELECTRODE_1                        0x3D2 
#define FLAG_HIDE_ROCKETHIDEOUT2_ELECTRODE_2                        0x3D3 
#define FLAG_HIDE_ROCKETHIDEOUT2_ELECTRODE_3                        0x3D4
#define FLAG_HIDE_ICE_PATH_KIMONO                                   0x3D5
#define FLAG_BLACKTHORN_NPC_TRADE_COMPLETED                         0x3D6
#define FLAG_HIDE_TOHJO_GIOVANNI                                    0x3D7
#define FLAG_HIDE_ECRUTEAK_SILVER                                   0x3D8
#define FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS                        0x3D9
#define FLAG_HIDE_ECRUTEAK_CITY_THEATER_ZUKI                        0x3DA
#define FLAG_HIDE_TINTOWER_GUARD                                    0x3DB
#define FLAG_HIDE_WHIRLISLANDS_GUARD                                0x3DC
#define FLAG_HIDE_VICTORY_ROAD_SILVER                               0x3DD
#define FLAG_HIDE_INDIGO_PLATEAU_SILVER                             0x3DE
#define FLAG_HIDE_INDIGO_PLATEAU_MARY_OAK                           0x3DF
#define FLAG_HIDE_SSAQUA_1F_GRANDPA                                 0x3E0
#define FLAG_HIDE_SSAQUA_ROOM_SSE_GRANDDAUGHTER                     0x3E1
#define FLAG_HIDE_SSAQUA_SAILOR                                     0x3E2
#define FLAG_HIDE_SSAQUA_CAPTAINS_ROOM_GRANDDAUGHTER                0x3E3
#define FLAG_HIDE_SOOTOPOLIS_CITY_RAYQUAZA                          0x3E4//unused
#define FLAG_HIDE_SOOTOPOLIS_CITY_KYOGRE                            0x3E5//unused
#define FLAG_HIDE_SOOTOPOLIS_CITY_GROUDON                           0x3E6//unused
#define FLAG_HIDE_RUSTBORO_CITY_POKEMON_SCHOOL_SCOTT                0x3E7//unused

// Item Ball Flags 
#define FLAG_ITEM_GARBAGEFLAG                                       0x3E8    //HnS ItemFlags Block 2
#define FLAG_ITEM_ROUTE39_NUGGET                                    0x3E9
#define FLAG_ITEM_ROUTE42_ULTRA_BALL                                0x3EA
#define FLAG_ITEM_ROUTE42_SUPER_POTION                              0x3EB
#define FLAG_ITEM_ROUTE42_MODEST_MINT                               0x3EC
#define FLAG_ITEM_MTMORTAR1_REVIVE                                  0x3ED
#define FLAG_ITEM_MTMORTAR1_ELIXIR                                  0x3EE
#define FLAG_ITEM_MTMORTAR2_MAX_REPEL                               0x3EF
#define FLAG_ITEM_MTMORTAR2_ESCAPE_ROPE                             0x3F0
#define FLAG_ITEM_MTMORTAR2_MAX_POTION                              0x3F1
#define FLAG_ITEM_MTMORTAR2_NUGGET                                  0x3F2
#define FLAG_ITEM_MTMORTAR2_ULTRA_BALL                              0x3F3
#define FLAG_ITEM_MTMORTAR2_REVIVE                                  0x3F4
#define FLAG_ITEM_MTMORTAR2_KINGS_ROCK                              0x3F5
#define FLAG_ITEM_MTMORTAR3_IRON                                    0x3F6
#define FLAG_ITEM_MTMORTAR3_MAX_REVIVE                              0x3F7
#define FLAG_ITEM_MTMORTAR3_ETHER                                   0x3F8
#define FLAG_ITEM_MTMORTAR3_RARE_CANDY                              0x3F9
#define FLAG_ITEM_MTMORTAR3_DRAGON_SCALE                            0x3FA
#define FLAG_ITEM_MTMORTAR3_ELIXIR                                  0x3FB
#define FLAG_ITEM_MTMORTAR4_HYPER_POTION                            0x3FC
#define FLAG_ITEM_MTMORTAR4_CARBOS                                  0x3FD
#define FLAG_ITEM_MTMORTAR4_PP_UP                                   0x3FE
#define FLAG_ITEM_MTMORTAR4_MAX_ETHER                               0x3FF
#define FLAG_ITEM_MTMORTAR4_MAX_REVIVE                              0x400
#define FLAG_ITEM_LIGHTHOUSE_ETHER                                  0x401
#define FLAG_ITEM_LIGHTHOUSE_RARE_CANDY                             0x402
#define FLAG_ITEM_LUCKY_PUNCH                                0x403
#define FLAG_ITEM_LIGHTHOUSE_HYPER_POTION                           0x404
#define FLAG_ITEM_LIGHTHOUSE_PROTEIN                                0x405

#define FLAG_ITEM_RUINSOFALPH_LUM_BERRY_1                           0x406
#define FLAG_ITEM_RUINSOFALPH_CHARCOAL                              0x407
#define FLAG_ITEM_RUINSOFALPH_MAX_REVIVE_1                          0x408
#define FLAG_ITEM_RUINSOFALPH_SACRED_ASH                            0x409
#define FLAG_ITEM_RUINSOFALPH_HEAL_POWDER_1                         0x40A
#define FLAG_ITEM_RUINSOFALPH_ENERGY_ROOT                           0x40B
#define FLAG_ITEM_RUINSOFALPH_SITRUS_BERRY_2                        0x40C
#define FLAG_ITEM_RUINSOFALPH_MOON_STONE                            0x40D
#define FLAG_ITEM_RUINSOFALPH_HEAL_POWDER_2                         0x40E
#define FLAG_ITEM_RUINSOFALPH_ENERGY_POWDER                         0x40F
#define FLAG_ITEM_RUINSOFALPH_ORAN_BERRY                            0x410
#define FLAG_ITEM_RUINSOFALPH_PECHA_BERRY                           0x411
#define FLAG_ITEM_RUINSOFALPH_STARDUST                              0x412
#define FLAG_ITEM_RUINSOFALPH_STAR_PIECE                            0x413
#define FLAG_ITEM_RUINSOFALPH_LUM_BERRY_2                           0x414
#define FLAG_ITEM_RUINSOFALPH_WATER_STONE                           0x415
#define FLAG_ITEM_WHIRL_ISLANDS_1F_ULTRA_BALL                       0x416
#define FLAG_ITEM_WHIRL_ISLANDS_1F_RARE_CANDY                       0x417
#define FLAG_ITEM_WHIRL_ISLANDS_1F_FULL_RESTORE                     0x418
#define FLAG_ITEM_WHIRL_ISLANDS_1F_GUARD_SPEC                       0x419
#define FLAG_ITEM_WHIRL_ISLANDS_B1F_MAX_REVIVE                      0x41A
#define FLAG_ITEM_WHIRL_ISLANDS_B1F_FULL_RESTORE                    0x41B
#define FLAG_ITEM_WHIRL_ISLANDS_B1F_PP_MAX                          0x41C
#define FLAG_ITEM_WHIRL_ISLANDS_B2F_BIG_NUGGET                      0x41D
#define FLAG_ITEM_WHIRL_ISLANDS_B2F_FULL_RESTORE                    0x41E
#define FLAG_ITEM_WHIRL_ISLANDS_B2F_CARBOS                          0x41F
#define FLAG_ITEM_WHIRL_ISLANDS_B2F_CALCIUM                         0x420
#define FLAG_ITEM_WHIRL_ISLANDS_B2F_ESCAPE_ROPE                     0x421
#define FLAG_ITEM_ROUTE47_PEARL                                     0x422
#define FLAG_ITEM_ROUTE47_REVIVE                                    0x423
#define FLAG_ITEM_ROUTE47_WHITE_FLUTE                               0x424
#define FLAG_ITEM_ROUTE47_STARDUST                                  0x425
#define FLAG_ITEM_ROUTE43_MAX_ETHER                                 0x426
#define FLAG_ITEM_LAKEOFRAGE_FULL_RESTORE                           0x427
#define FLAG_ITEM_LAKEOFRAGE_MAX_REVIVE                             0x428
#define FLAG_ITEM_LAKEOFRAGE_RED_FLUTE                              0x429
#define FLAG_ITEM_ROUTE44_MAX_REPEL                                 0x42A
#define FLAG_ITEM_ROUTE44_ULTRA_BALL                                0x42B
#define FLAG_ITEM_ROUTE44_ELIXIR                                    0x42C
#define FLAG_ITEM_ROCKETHIDEOUT1_BIG_NUGGET                         0x42D
#define FLAG_ITEM_ROCKETHIDEOUT1_REVIVE                             0x42E
#define FLAG_ITEM_ROCKETHIDEOUT1_HYPER_POTION                       0x42F
#define FLAG_ITEM_ROCKETHIDEOUT2_TM_THIEF                           0x430
#define FLAG_ITEM_ROCKETHIDEOUT3_ICE_HEAL                           0x431
#define FLAG_ITEM_ROCKETHIDEOUT3_PROTEIN                            0x432
#define FLAG_ITEM_ROCKETHIDEOUT3_FULL_HEAL                          0x433
#define FLAG_ITEM_ROCKETHIDEOUT3_GUARD_SPEC                         0x434
#define FLAG_ITEM_ROCKETHIDEOUT3_HYPER_POTION                       0x435

#define FLAG_ITEM_ICEPATH1_HM_WATERFALL                             0x436
#define FLAG_ITEM_ICEPATH1_PP_UP                                    0x437
#define FLAG_ITEM_ICEPATH1_PROTEIN                                  0x438
#define FLAG_ITEM_ICEPATH2_IRON                                     0x439
#define FLAG_ITEM_ICEPATH2_REVIVE                                   0x43A
#define FLAG_ITEM_ICEPATH3_MAX_POTION                               0x43B
#define FLAG_ITEM_ICEPATH3_FULL_HEAL                                0x43C
#define FLAG_ITEM_ICEPATH3_CARBOS                                   0x43D
#define FLAG_ITEM_ICEPATH3_NEVER_MELT_ICE                           0x43E
#define FLAG_ITEM_DRAGONSDEN2_DRAGON_FANG                           0x43F
#define FLAG_ITEM_DRAGONSDEN2_MAX_POTION                            0x440
#define FLAG_ITEM_DRAGONSDEN2_PP_MAX                                0x441
#define FLAG_ITEM_ROUTE45_ELIXIR                                    0x442
#define FLAG_ITEM_ROUTE45_MAX_POTION                                0x443
#define FLAG_ITEM_ROUTE45_FULL_HEAL                                 0x444
#define FLAG_ITEM_ROUTE45_NUGGET                                    0x445
#define FLAG_ITEM_ROUTE46_REVIVE                                    0x446
#define FLAG_ITEM_DARKCAVE1_REVIVE                                  0x447
#define FLAG_ITEM_DARKCAVE1_POTION                                  0x448
#define FLAG_ITEM_DARKCAVE1_ELIXIR                                  0x449
#define FLAG_ITEM_DARKCAVE1_MAX_REVIVE                              0x44A
#define FLAG_ITEM_DARKCAVE2_BLACK_FLUTE                             0x44B
#define FLAG_ITEM_DARKCAVE2_STAR_PIECE                              0x44C
#define FLAG_ITEM_OLIVINE_TM_SHOCKWAVE                              0x44D
#define FLAG_ITEM_ROUTE27_MOONSTONE                                 0x44E
#define FLAG_ITEM_ROUTE27_SOLARBEAM                                 0x44F
#define FLAG_ITEM_ROUTE27_RARECANDY                                 0x450
#define FLAG_ITEM_ROUTE27_REVIVE                                    0x451
#define FLAG_ITEM_TOHJOFALLS_HEART_SCALE                            0x452
#define FLAG_ITEM_VICTORYROAD1_MAX_REVIVE                           0x453
#define FLAG_ITEM_VICTORYROAD1_FULL_HEAL                            0x454
#define FLAG_ITEM_VICTORYROAD1_POTION                               0x455
#define FLAG_ITEM_VICTORYROAD2_FULL_RESTORE                         0x456
#define FLAG_ITEM_VICTORYROAD2_HP_UP                                0x457
#define FLAG_ITEM_VICTORYROAD2_MAX_REVIVE                           0x458
#define FLAG_ITEM_VICTORYROAD3_RARE_CANDY                           0x459
#define FLAG_ITEM_VICTORYROAD3_MAX_ETHER                            0x45A
#define FLAG_ITEM_VICTORYROAD3_ULTRA_BALL                           0x45B
#define FLAG_ITEM_ICEPATH4_TM_BLIZZARD                              0x45C
#define FLAG_ITEM_ROCKTUNNEL1_TM_FACADE                             0x45D
#define FLAG_ITEM_ROCKTUNNEL1_ELIXIR                                0x45E
#define FLAG_ITEM_ROCKTUNNEL2_IRON                                  0x45F
#define FLAG_ITEM_ROCKTUNNEL2_PP_UP                                 0x460
#define FLAG_ITEM_ROUTE10_ULTRABALL                                 0x461
#define FLAG_ITEM_VERMILION_OLD_SEA_MAP                             0x462
#define FLAG_ITEM_CELADON_LEFTOVERS                                 0x463
#define FLAG_ITEM_ROUTE12_ELIXIR                                    0x464
#define FLAG_DEFEATED_ENTEI                                         0x465
#define FLAG_DEFEATED_RAIKOU                                        0x466
#define FLAG_DEFEATED_SUICUNE                                       0x467
#define FLAG_DEFEATEDCELEBI                                         0x468
#define FLAG_ITEM_ROUTE12_CALCIUM                                   0x469
#define FLAG_ITEM_ROUTE13_CALCIUM                                   0x46A
#define FLAG_ITEM_ROUTE15_PP_UP                                     0x46B
#define FLAG_ITEM_ROUTE2_CARBOS                                     0x46C
#define FLAG_ITEM_ROUTE2_NUGGET                                     0x46D // Unused Flag, leftover from R/S. HM08 is given to the player directly in Emerald
#define FLAG_ITEM_VIRIDIANFOREST_MAX_POTION                         0x46E
#define FLAG_ITEM_VIRIDIANFOREST_DIRE_HIT                           0x46F
#define FLAG_CAUGHT_CELEBI                                          0x470
#define FLAG_ITEM_VIRIDIANFOREST_ELIXIR                             0x471
#define FLAG_ITEM_VIRIDIANFOREST_REVIVE                             0x472 
#define FLAG_ITEM_VIRIDIANFOREST_FULL_RESTORE                       0x473
#define FLAG_ITEM_VIRIDIANFOREST_MAX_ETHER                          0x474
#define FLAG_ITEM_VIRIDIANFOREST_FULL_HEAL                          0x475 //pewter
#define FLAG_ITEM_ROUTE4_ULTRABALL                                  0x476
#define FLAG_ITEM_ROUTE4_HPUP                                       0x477
#define FLAG_ITEM_MTMOON_MOONSTONE                                  0x478
#define FLAG_EVEN_FASTER_JOY                                        0x479
#define FLAG_ITEM_MTSILVER_FULLRESTORE                              0x47A
#define FLAG_ITEM_MTSILVER_DIREHIT                                  0x47B
#define FLAG_ITEM_MTSILVER_ULTRABALL                                0x47C
#define FLAG_ITEM_MTSILVER_MAXPOTION                                0x47D
#define FLAG_ITEM_MTSILVER_SPELL_TAG                                0x47E
#define FLAG_ITEM_MTSILVER_NERVERMELTICE                            0x47F
#define FLAG_ITEM_MTSILVER_RARECANDY                                0x480
#define FLAG_ITEM_CERULEANCAVE1_MAX_ELIXIR                          0x481
#define FLAG_ITEM_CERULEANCAVE1_RARE_CANDY                          0x482
#define FLAG_ITEM_CERULEANCAVE1_PP_UP                               0x483
#define FLAG_ITEM_CERULEANCAVE2_ZINC                                0x484
#define FLAG_ITEM_CERULEANCAVE2_PROTEIN                             0x485
#define FLAG_ITEM_CERULEANCAVE2_BIG_PEARL                           0x486
#define FLAG_ITEM_CERULEANCAVE3_MAX_REVIVE                          0x487
#define FLAG_ITEM_CERULEANCAVE3_ULTRA_BALL                          0x488
#define FLAG_ITEM_ROUTE20_SHELL_BELL                                   0x489
#define FLAG_ITEM_ARTISAN_CAVE_B1F_HP_UP                            0x48A
#define FLAG_ITEM_ARTISAN_CAVE_1F_CARBOS                            0x48B
#define FLAG_ITEM_MAGMA_HIDEOUT_2F_2R_MAX_ELIXIR                    0x48C
#define FLAG_ITEM_MAGMA_HIDEOUT_2F_2R_FULL_RESTORE                  0x48D
#define FLAG_ITEM_MAGMA_HIDEOUT_3F_1R_NUGGET                        0x48E
#define FLAG_ITEM_MAGMA_HIDEOUT_3F_2R_PP_MAX                        0x48F
#define FLAG_ITEM_MAGMA_HIDEOUT_4F_MAX_REVIVE                       0x490
#define FLAG_ITEM_SAFARI_ZONE_NORTH_EAST_NUGGET                     0x491
#define FLAG_ITEM_SAFARI_ZONE_SOUTH_EAST_BIG_PEARL                  0x492

#define FLAG_JIRACHI                                                0x493
#define FLAG_ROBERTO1                                               0x494
#define FLAG_ENTEI_BATTLE_1                                         0x495
#define FLAG_ENTEI_BATTLE_2                                         0x496
#define FLAG_ENTEI_BATTLE_3                                         0x497
#define FLAG_INCREASE_DIFFICULTY                                    0x498
#define FLAG_ROCKETHIDEOUT2_BATTLE                                  0x499
#define FLAG_RAIKOU_BATTLE_1                                        0x49A
#define FLAG_LANDMARK_DRACO_CHAMBER                                 0x49B
#define FLAG_RAIKOU_BATTLE_2                                        0x49C
#define FLAG_SUICUNE_BATTLE_1                                       0x49D
#define FLAG_SUICUNE_BATTLE_2                                       0x49E
#define FLAG_NO_SLOW_STAIR_MOVEMENT                                 0x49F // Used to temporaly remove slow stair movement, as it glitches things 
                                                                          // like Steven in Sootopolis leading to Origin Cave.
#define FLAG_ITEM_ROUTE_29_POTION                                   0x4A0 //HnS ItemFlags Block 1
#define FLAG_ITEM_ROUTE_31_ANTIDOE                                  0x4A1 
#define FLAG_ITEM_ROUTE_31_POKEBALL                                 0x4A2 
#define FLAG_ITEM_VIOLET_CITY_PECHA_BERRY                           0x4A3 
#define FLAG_ITEM_VIOLET_CITY_RARE_CANDY                            0x4A4 
#define FLAG_ITEM_VIOLET_CITY_HYPER_POTION                          0x4A5 
#define FLAG_EXP_SHARE                                              0x4A6 //EXP SHARE
#define FLAG_ITEM_SPROUT_TOWER_PARALYZE_HEAL                        0x4A7 
#define FLAG_ITEM_SPROUT_TOWER_X_DEFEND                             0x4A8 
#define FLAG_ITEM_SPROUT_TOWER_POTION                               0x4A9 
#define FLAG_ITEM_SPROUT_TOWER_ESCAPE_ROPE                          0x4AA 
#define FLAG_ITEM_HELIX_FOSSIL                                      0x4AB 
#define FLAG_ITEM_DOME_FOSSIL                                       0x4AC 
#define FLAG_ITEM_OLD_AMBER                                         0x4AD 
#define FLAG_ITEM_GS_BALL                                           0x4AE 
#define FLAG_GARBAGEFLAG3                                           0x4AF 
#define FLAG_ITEM_ROUTE_32_GREATBALL                                0x4B0 
#define FLAG_ITEM_ROUTE_32_GREATBALL2                               0x4B1 
#define FLAG_ITEM_ROUTE_32_POTION                                   0x4B2 
#define FLAG_ITEM_ROUTE_32_SUPERPOTION                              0x4B3 
#define FLAG_ITEM_UNION_CAVE_POTION                                 0x4B4 
#define FLAG_ITEM_UNION_CAVE_GREAT_BALL                             0x4B5 
#define FLAG_ITEM_UNION_CAVE_X_ATTACK                               0x4B6 
#define FLAG_ITEM_UNION_CAVE_AWAKENING                              0x4B7 
#define FLAG_ITEM_UNION_CAVE_SECRET_POWER                           0x4B8 
#define FLAG_ITEM_UNION_CAVE_X_DEFEND                               0x4B9 
#define FLAG_ITEM_UNION_CAVE_ETHER                                  0x4BA 
#define FLAG_ITEM_UNION_CAVE_HYPERPOTION                            0x4BB 
#define FLAG_ITEM_UNION_CAVE_MAXREVIVE                              0x4BC 
#define FLAG_ITEM_SLOWPOKE_WELL_SUPER_POTION                        0x4BD 
#define FLAG_ITEM_SLOWPOKE_WELL_SUPER_POTION2                       0x4BE 
#define FLAG_ITEM_SLOWPOKE_WELL_GREAT_BALL                          0x4BF 
#define FLAG_ITEM_SLOWPOKE_WELL_FULL_HEAL                           0x4C0 
#define FLAG_ITEM_SLOWPOKE_WELL_KINGS_ROCK                          0x4C1 
#define FLAG_ITEM_SLOWPOKE_WELL_RAIN_DANCE                          0x4C2 
#define FLAG_ITEM_ILEX_FOREST_ETHER                                 0x4C3 
#define FLAG_ITEM_ILEX_FOREST_SUPER_POTION                          0x4C4 
#define FLAG_ITEM_ILEX_FOREST_FULL_HEAL                             0x4C5 
#define FLAG_ITEM_ILEX_FOREST_TM_SUNNY_DAY                          0x4C6 
#define FLAG_ITEM_ROUTE34_SUPERPOTION                               0x4C7 
#define FLAG_ITEM_ROUTE34_RARECANDY                                 0x4C8 
#define FLAG_ITEM_ROUTE34_SOFTSAND                                  0x4C9 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_COIN_CASE                   0x4CA 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_SUPER_POTION                0x4CB 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_PARALYZE_HEAL               0x4CC 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_ANTIDOTE                    0x4CD 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_AMULET_COIN                 0x4CE 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_EXP_SHARE                   0x4CF 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_ULTRA_BALL                  0x4D0 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_ETHER                       0x4D1 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_ULTRA_BALL2                 0x4D2 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_TM_CALM_MIND                0x4D3 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_MAX_ETHER                   0x4D4 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_MAX_POTION                  0x4D5 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_REVIVE                      0x4D6 
#define FLAG_ITEM_GOLDENROD_UNDERGROUND_SMOKE_BALL                  0x4D7 
#define FLAG_ITEM_ROUTE35_ROCK_TOMB                                 0x4D8 
#define FLAG_ITEM_ROUTE35_PARALYZE_HEAL                             0x4D9 
#define FLAG_ITEM_ROUTE35_BIG_NUGGET                                0x4DA 
#define FLAG_ITEM_NATIONAL_PARK_SOOTHE_BELL                         0x4DB 
#define FLAG_ITEM_NATIONAL_PARK_TM_DIG                              0x4DC 
#define FLAG_ITEM_ECRUTEAK_RARE_CANDY                               0x4DD 
#define FLAG_ITEM_BELLCHIME_BIG_MUSHROOM                            0x4DE 
#define FLAG_ITEM_TIN_TOWER_3F_FULL_HEAL                            0x4DF 
#define FLAG_ITEM_TIN_TOWER_4F_ULTRA_BALL                           0x4E0 
#define FLAG_ITEM_TIN_TOWER_4F_ESCAPE_ROPE                          0x4E1 
#define FLAG_ITEM_TIN_TOWER_4F_MAX_POTION                           0x4E2 
#define FLAG_ITEM_TIN_TOWER_5F_RARE_CANDY                           0x4E3 
#define FLAG_ITEM_TIN_TOWER_5F_MAX_POTION                           0x4E4 
#define FLAG_ITEM_TIN_TOWER_5F_CARBOS                               0x4E5 
#define FLAG_ITEM_TIN_TOWER_7F_MAX_REVIVE                           0x4E6 
#define FLAG_ITEM_TIN_TOWER_8F_FULL_RESTORE                         0x4E7 
#define FLAG_ITEM_TIN_TOWER_8F_MAX_ELIXIR                           0x4E8 
#define FLAG_ITEM_TIN_TOWER_8F_BIG_NUGGET                           0x4E9 
#define FLAG_ITEM_BURNED_TOWER_1F_HP_UP                             0x4EA 
#define FLAG_ITEM_BURNED_TOWER_1F_ETHER                             0x4EB 
#define FLAG_ITEM_BURNED_TOWER_B1F_TM_TAUNT                         0x4EC 
#define FLAG_ITEM_BURNED_TOWER_B1F_ULTRA_BALL                       0x4ED 
#define FLAG_ITEM_ROUTE38_LAX_INCENSE                               0x4EE 
#define FLAG_ITEM_ROUTE39_TM_BRICK_BREAK                            0x4EF 

#define FLAG_DEFEATED_VIOLET_GYM                                    0x4F0
#define FLAG_DEFEATED_AZALEA_TOWN_GYM                               0x4F1
#define FLAG_DEFEATED_GOLDENROD_CITY_GYM                            0x4F2
#define FLAG_DEFEATED_ECRUTEAK_CITY_GYM                             0x4F3
#define FLAG_DEFEATED_CIANWOOD_GYM                                  0x4F4
#define FLAG_DEFEATED_OLIVINE_CITY_GYM                              0x4F5
#define FLAG_DEFEATED_MAHOGANY_TOWN_GYM                             0x4F6
#define FLAG_DEFEATED_BLACKTHORN_GYM                                0x4F7
#define FLAG_DEFEATED_RED                                           0x4F8

#define FLAG_UNUSED_0x4F9                                           0x4F9 // Unused Flag
#define FLAG_UNUSED_0x4FA                                           0x4FA // Unused Flag

#define FLAG_DEFEATED_ELITE_4_WILL                                  0x4FB
#define FLAG_DEFEATED_ELITE_4_KOGA                                  0x4FC
#define FLAG_DEFEATED_ELITE_4_BRUNO                                 0x4FD
#define FLAG_DEFEATED_ELITE_4_KAREN                                 0x4FE

#define FLAG_UNUSED_0x4FF                                           0x4FF // Unused Flag

// Trainer Flags
// Trainer flags occupy 0x500 - 0x85F, the last 9 of which are unused
// See constants/opponents.h. The values there + FLAG_TRAINER_FLAG_START are the flag IDs

#define TRAINER_FLAGS_START                                         0x500
#define TRAINER_FLAGS_END                                           (TRAINER_FLAGS_START + MAX_TRAINERS_COUNT - 1) // 0x85F

// System Flags

#define SYSTEM_FLAGS                                   (TRAINER_FLAGS_END + 1) // 0x860

#define FLAG_SYS_POKEMON_GET                         (SYSTEM_FLAGS + 0x0) // FLAG_0x860
#define FLAG_SYS_POKEDEX_GET                         (SYSTEM_FLAGS + 0x1)
#define FLAG_SYS_POKENAV_GET                         (SYSTEM_FLAGS + 0x2)
#define FLAG_UNUSED_0x863                            (SYSTEM_FLAGS + 0x3) // Unused Flag
#define FLAG_SYS_GAME_CLEAR                          (SYSTEM_FLAGS + 0x4)
#define FLAG_SYS_CHAT_USED                           (SYSTEM_FLAGS + 0x5)
#define FLAG_UNLOCKED_TRENDY_SAYINGS                 (SYSTEM_FLAGS + 0x6)

// Badges
#define FLAG_BADGE01_GET                             (SYSTEM_FLAGS + 0x7)
#define FLAG_BADGE02_GET                             (SYSTEM_FLAGS + 0x8)
#define FLAG_BADGE03_GET                             (SYSTEM_FLAGS + 0x9)
#define FLAG_BADGE04_GET                             (SYSTEM_FLAGS + 0xA)
#define FLAG_BADGE05_GET                             (SYSTEM_FLAGS + 0xB)
#define FLAG_BADGE06_GET                             (SYSTEM_FLAGS + 0xC)
#define FLAG_BADGE07_GET                             (SYSTEM_FLAGS + 0xD)
#define FLAG_BADGE08_GET                             (SYSTEM_FLAGS + 0xE)
#define NUM_BADGES                                   (1 + FLAG_BADGE08_GET - FLAG_BADGE01_GET)

// Towns and Cities
#define FLAG_VISITED_NEWBARK_TOWN                (SYSTEM_FLAGS + 0xF)
#define FLAG_VISITED_CHERRYGROVE_CITY                  (SYSTEM_FLAGS + 0x10)
#define FLAG_VISITED_VIOLET_CITY                    (SYSTEM_FLAGS + 0x11)
#define FLAG_VISITED_AZALEA_TOWN                   (SYSTEM_FLAGS + 0x12)
#define FLAG_VISITED_GOLDENROD_CITY                 (SYSTEM_FLAGS + 0x13)
#define FLAG_VISITED_ECRUTEAK_CITY                 (SYSTEM_FLAGS + 0x14)
#define FLAG_VISITED_OLIVINE_CITY                (SYSTEM_FLAGS + 0x15)
#define FLAG_VISITED_CIANWOOD_CITY                (SYSTEM_FLAGS + 0x16)
#define FLAG_VISITED_SAFARI_ZONE_GATE                 (SYSTEM_FLAGS + 0x17)
#define FLAG_VISITED_MAHOGANY_TOWN                 (SYSTEM_FLAGS + 0x18)
#define FLAG_VISITED_LAKE_OF_RAGE                           (SYSTEM_FLAGS + 0x19) //25
#define FLAG_VISITED_BLACKTHORN_CITY                  (SYSTEM_FLAGS + 0x1A)
#define FLAG_VISITED_INDIGO_PLATEAU               (SYSTEM_FLAGS + 0x1B)
#define FLAG_VISITED_PALLET_TOWN                           (SYSTEM_FLAGS + 0x1C) 
#define FLAG_VISITED_VIRIDIAN_CITY                   (SYSTEM_FLAGS + 0x1D)
#define FLAG_VISITED_PEWTER_CITY                         (SYSTEM_FLAGS + 0x1E) 
#define FLAG_VISITED_CERULEAN_CITY               (SYSTEM_FLAGS + 0x1F) //49
#define FLAG_VISITED_VERMILION_CITY                          (SYSTEM_FLAGS + 0x20) 
#define FLAG_VISITED_LAVENDER_TOWN                (SYSTEM_FLAGS + 0x21)
#define FLAG_VISITED_CELADON_CITY                  (SYSTEM_FLAGS + 0x22)
#define FLAG_VISITED_SAFFRON_CITY                  (SYSTEM_FLAGS + 0x23)
#define FLAG_VISITED_FUCHSIA_CITY               (SYSTEM_FLAGS + 0x24) //48
#define FLAG_VISITED_CINNABAR_ISLAND                          (SYSTEM_FLAGS + 0x25) 
#define FLAG_VISITED_MT_SILVER                           (SYSTEM_FLAGS + 0x26) //26
#define FLAG_VISITED_RECEPTION_GATE                           (SYSTEM_FLAGS + 0x27) // 27

#define FLAG_SYS_USE_FLASH                          (SYSTEM_FLAGS + 0x28)
#define FLAG_SYS_USE_STRENGTH                       (SYSTEM_FLAGS + 0x29)
#define FLAG_SYS_WEATHER_CTRL                       (SYSTEM_FLAGS + 0x2A)
#define FLAG_SYS_CYCLING_ROAD                       (SYSTEM_FLAGS + 0x2B)
#define FLAG_SYS_SAFARI_MODE                        (SYSTEM_FLAGS + 0x2C)
#define FLAG_SYS_CRUISE_MODE                        (SYSTEM_FLAGS + 0x2D)

#define FLAG_SYS_BUG_CONTEST_MODE                           (SYSTEM_FLAGS + 0x2E) // Unused Flag
#define FLAG_UNUSED_0x88F                           (SYSTEM_FLAGS + 0x2F) // Unused Flag

#define FLAG_SYS_TV_HOME                            (SYSTEM_FLAGS + 0x30)
#define FLAG_SYS_TV_WATCH                           (SYSTEM_FLAGS + 0x31)
#define FLAG_SYS_TV_START                           (SYSTEM_FLAGS + 0x32)
#define FLAG_SYS_CHANGED_DEWFORD_TREND              (SYSTEM_FLAGS + 0x33)
#define FLAG_SYS_MIX_RECORD                         (SYSTEM_FLAGS + 0x34)
#define FLAG_SYS_CLOCK_SET                          (SYSTEM_FLAGS + 0x35)
#define FLAG_SYS_NATIONAL_DEX                       (SYSTEM_FLAGS + 0x36)
#define FLAG_SYS_CAVE_SHIP                          (SYSTEM_FLAGS + 0x37) // Unused Flag, leftover from R/S debug, presumably used by Emerald's debug too
#define FLAG_LANDMARK_CAVE_OF_SHOCK                 (SYSTEM_FLAGS + 0x38) 
#define UNUSED_SYSTEM_FLAG_0x39                     (SYSTEM_FLAGS + 0x39) // Unused Flag
#define FLAG_SYS_LAKE_OF_RAGE_TIDE                         (SYSTEM_FLAGS + 0x3A)
#define FLAG_SYS_RIBBON_GET                         (SYSTEM_FLAGS + 0x3B)

#define FLAG_LANDMARK_FLOWER_SHOP                   (SYSTEM_FLAGS + 0x3C)
#define FLAG_LANDMARK_MR_BRINEY_HOUSE               (SYSTEM_FLAGS + 0x3D)
#define FLAG_LANDMARK_ABANDONED_SHIP                (SYSTEM_FLAGS + 0x3E)
#define FLAG_LANDMARK_SEASHORE_HOUSE                (SYSTEM_FLAGS + 0x3F)
#define FLAG_LANDMARK_NEW_MAUVILLE                  (SYSTEM_FLAGS + 0x40)
#define FLAG_LANDMARK_OLD_LADY_REST_SHOP            (SYSTEM_FLAGS + 0x41)
#define FLAG_LANDMARK_TRICK_HOUSE                   (SYSTEM_FLAGS + 0x42)
#define FLAG_LANDMARK_WINSTRATE_FAMILY              (SYSTEM_FLAGS + 0x43)
#define FLAG_LANDMARK_GLASS_WORKSHOP                (SYSTEM_FLAGS + 0x44)
#define FLAG_LANDMARK_BillS_HOUSE                (SYSTEM_FLAGS + 0x45)
#define FLAG_LANDMARK_POKEMON_DAYCARE               (SYSTEM_FLAGS + 0x46)
#define FLAG_LANDMARK_SEAFLOOR_CAVERN               (SYSTEM_FLAGS + 0x47)
#define FLAG_IS_CHAMPION                            (SYSTEM_FLAGS + 0x48) // 1f Seems to be related to linking.
#define FLAG_NURSE_UNION_ROOM_REMINDER              (SYSTEM_FLAGS + 0x49) // 20
#define FLAG_LANDMARK_FIERY_PATH                    (SYSTEM_FLAGS + 0x4A)

#define FLAG_SYS_PC_BILL                         (SYSTEM_FLAGS + 0x4B)
#define FLAG_SYS_MYSTERY_EVENT_ENABLE               (SYSTEM_FLAGS + 0x4C)
#define FLAG_SYS_ENC_UP_ITEM                        (SYSTEM_FLAGS + 0x4D)
#define FLAG_SYS_ENC_DOWN_ITEM                      (SYSTEM_FLAGS + 0x4E)
#define FLAG_SYS_BRAILLE_DIG                        (SYSTEM_FLAGS + 0x4F)
#define FLAG_SYS_REGIROCK_PUZZLE_COMPLETED          (SYSTEM_FLAGS + 0x50)
#define FLAG_SYS_BRAILLE_REGICE_COMPLETED           (SYSTEM_FLAGS + 0x51)
#define FLAG_SYS_REGISTEEL_PUZZLE_COMPLETED         (SYSTEM_FLAGS + 0x52)
#define FLAG_ENABLE_SHIP_SOUTHERN_ISLAND            (SYSTEM_FLAGS + 0x53)

#define FLAG_LANDMARK_POKEMON_LEAGUE                (SYSTEM_FLAGS + 0x54)
#define FLAG_LANDMARK_ISLAND_CAVE                   (SYSTEM_FLAGS + 0x55)
#define FLAG_LANDMARK_DESERT_RUINS                  (SYSTEM_FLAGS + 0x56)
#define FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE          (SYSTEM_FLAGS + 0x57)
#define FLAG_LANDMARK_SCORCHED_SLAB                 (SYSTEM_FLAGS + 0x58)
#define FLAG_LANDMARK_ANCIENT_TOMB                  (SYSTEM_FLAGS + 0x59)
#define FLAG_LANDMARK_TUNNELERS_REST_HOUSE          (SYSTEM_FLAGS + 0x5A)
#define FLAG_LANDMARK_HUNTERS_HOUSE                 (SYSTEM_FLAGS + 0x5B)
#define FLAG_LANDMARK_SEALED_CHAMBER                (SYSTEM_FLAGS + 0x5C)

#define FLAG_SYS_TV_LATIAS_LATIOS                   (SYSTEM_FLAGS + 0x5D)

#define FLAG_LANDMARK_SKY_PILLAR                    (SYSTEM_FLAGS + 0x5E)

#define FLAG_SYS_SHOAL_ITEM                         (SYSTEM_FLAGS + 0x5F)
#define FLAG_SYS_B_DASH                             (SYSTEM_FLAGS + 0x60) // RECEIVED Running Shoes
#define FLAG_SYS_CTRL_OBJ_DELETE                    (SYSTEM_FLAGS + 0x61)
#define FLAG_SYS_RESET_RTC_ENABLE                   (SYSTEM_FLAGS + 0x62)

#define FLAG_LANDMARK_BERRY_MASTERS_HOUSE           (SYSTEM_FLAGS + 0x63)

#define FLAG_SYS_TOWER_SILVER                       (SYSTEM_FLAGS + 0x64)
#define FLAG_SYS_TOWER_GOLD                         (SYSTEM_FLAGS + 0x65)
#define FLAG_SYS_DOME_SILVER                        (SYSTEM_FLAGS + 0x66)
#define FLAG_SYS_DOME_GOLD                          (SYSTEM_FLAGS + 0x67)
#define FLAG_SYS_PALACE_SILVER                      (SYSTEM_FLAGS + 0x68)
#define FLAG_SYS_PALACE_GOLD                        (SYSTEM_FLAGS + 0x69)
#define FLAG_SYS_ARENA_SILVER                       (SYSTEM_FLAGS + 0x6A)
#define FLAG_SYS_ARENA_GOLD                         (SYSTEM_FLAGS + 0x6B)
#define FLAG_SYS_FACTORY_SILVER                     (SYSTEM_FLAGS + 0x6C)
#define FLAG_SYS_FACTORY_GOLD                       (SYSTEM_FLAGS + 0x6D)
#define FLAG_SYS_PIKE_SILVER                        (SYSTEM_FLAGS + 0x6E)
#define FLAG_SYS_PIKE_GOLD                          (SYSTEM_FLAGS + 0x6F)
#define FLAG_SYS_PYRAMID_SILVER                     (SYSTEM_FLAGS + 0x70)
#define FLAG_SYS_PYRAMID_GOLD                       (SYSTEM_FLAGS + 0x71)
#define FLAG_SYS_FRONTIER_PASS                      (SYSTEM_FLAGS + 0x72)

#define FLAG_MAP_SCRIPT_CHECKED_DEOXYS              (SYSTEM_FLAGS + 0x73)
#define FLAG_DEOXYS_ROCK_COMPLETE                   (SYSTEM_FLAGS + 0x74)
#define FLAG_ENABLE_SHIP_BIRTH_ISLAND               (SYSTEM_FLAGS + 0x75)
#define FLAG_ENABLE_SHIP_FARAWAY_ISLAND             (SYSTEM_FLAGS + 0x76)

#define FLAG_SHOWN_BOX_WAS_FULL_MESSAGE             (SYSTEM_FLAGS + 0x77)

#define FLAG_ARRIVED_ON_FARAWAY_ISLAND              (SYSTEM_FLAGS + 0x78)
#define FLAG_ARRIVED_AT_MARINE_CAVE_EMERGE_SPOT     (SYSTEM_FLAGS + 0x79)
#define FLAG_ARRIVED_AT_TERRA_CAVE_ENTRANCE         (SYSTEM_FLAGS + 0x7A)

#define FLAG_SYS_MYSTERY_GIFT_ENABLE                (SYSTEM_FLAGS + 0x7B)

#define FLAG_ENTERED_MIRAGE_TOWER                   (SYSTEM_FLAGS + 0x7C)
#define FLAG_LANDMARK_ALTERING_CAVE                 (SYSTEM_FLAGS + 0x7D)
#define FLAG_LANDMARK_DESERT_UNDERPASS              (SYSTEM_FLAGS + 0x7E)
#define FLAG_LANDMARK_ARTISAN_CAVE                  (SYSTEM_FLAGS + 0x7F)
#define FLAG_ENABLE_SHIP_NAVEL_ROCK                 (SYSTEM_FLAGS + 0x80)
#define FLAG_ARRIVED_AT_NAVEL_ROCK                  (SYSTEM_FLAGS + 0x81)
#define FLAG_LANDMARK_TRAINER_HILL                  (SYSTEM_FLAGS + 0x82)

#define FLAG_UNUSED_0x8E3                           (SYSTEM_FLAGS + 0x83) // Unused Flag

#define FLAG_RECEIVED_POKEDEX_FROM_BIRCH            (SYSTEM_FLAGS + 0x84)

#define FLAG_BADGE09_GET                           (SYSTEM_FLAGS + 0x85) 
#define FLAG_BADGE10_GET                           (SYSTEM_FLAGS + 0x86)  
#define FLAG_BADGE11_GET                           (SYSTEM_FLAGS + 0x87)  
#define FLAG_BADGE12_GET                           (SYSTEM_FLAGS + 0x88)  
#define FLAG_BADGE13_GET                           (SYSTEM_FLAGS + 0x89)  
#define FLAG_BADGE14_GET                           (SYSTEM_FLAGS + 0x8A)  
#define FLAG_BADGE15_GET                           (SYSTEM_FLAGS + 0x8B)  
#define FLAG_BADGE16_GET                           (SYSTEM_FLAGS + 0x8C)  
#define FLAG_UNUSED_0x8ED                           (SYSTEM_FLAGS + 0x8D) // Unused Flag
#define FLAG_UNUSED_0x8EE                           (SYSTEM_FLAGS + 0x8E) // Unused Flag
#define FLAG_UNUSED_0x8EF                           (SYSTEM_FLAGS + 0x8F) // Unused Flag
#define FLAG_UNUSED_0x8F0                           (SYSTEM_FLAGS + 0x90) // Unused Flag
#define FLAG_UNUSED_0x8F1                           (SYSTEM_FLAGS + 0x91) // Unused Flag
#define FLAG_UNUSED_0x8F2                           (SYSTEM_FLAGS + 0x92) // Unused Flag
#define FLAG_UNUSED_0x8F3                           (SYSTEM_FLAGS + 0x93) // Unused Flag
#define FLAG_UNUSED_0x8F4                           (SYSTEM_FLAGS + 0x94) // Unused Flag
#define FLAG_UNUSED_0x8F5                           (SYSTEM_FLAGS + 0x95) // Unused Flag
#define FLAG_UNUSED_0x8F6                           (SYSTEM_FLAGS + 0x96) // Unused Flag
#define FLAG_UNUSED_0x8F7                           (SYSTEM_FLAGS + 0x97) // Unused Flag
#define FLAG_UNUSED_0x8F8                           (SYSTEM_FLAGS + 0x98) // Unused Flag
#define FLAG_UNUSED_0x8F9                           (SYSTEM_FLAGS + 0x99) // Unused Flag
#define FLAG_UNUSED_0x8FA                           (SYSTEM_FLAGS + 0x9A) // Unused Flag
#define FLAG_UNUSED_0x8FB                           (SYSTEM_FLAGS + 0x9B) // Unused Flag
#define FLAG_UNUSED_0x8FC                           (SYSTEM_FLAGS + 0x9C) // Unused Flag
#define FLAG_UNUSED_0x8FD                           (SYSTEM_FLAGS + 0x9D) // Unused Flag
#define FLAG_UNUSED_0x8FE                           (SYSTEM_FLAGS + 0x9E) // Unused Flag
#define FLAG_UNUSED_0x8FF                           (SYSTEM_FLAGS + 0x9F) // Unused Flag
#define FLAG_UNUSED_0x900                           (SYSTEM_FLAGS + 0xA0) // Unused Flag
#define FLAG_UNUSED_0x901                           (SYSTEM_FLAGS + 0xA1) // Unused Flag
#define FLAG_UNUSED_0x902                           (SYSTEM_FLAGS + 0xA2) // Unused Flag
#define FLAG_UNUSED_0x903                           (SYSTEM_FLAGS + 0xA3) // Unused Flag
#define FLAG_UNUSED_0x904                           (SYSTEM_FLAGS + 0xA4) // Unused Flag
#define FLAG_UNUSED_0x905                           (SYSTEM_FLAGS + 0xA5) // Unused Flag
#define FLAG_UNUSED_0x906                           (SYSTEM_FLAGS + 0xA6) // Unused Flag
#define FLAG_UNUSED_0x907                           (SYSTEM_FLAGS + 0xA7) // Unused Flag
#define FLAG_UNUSED_0x908                           (SYSTEM_FLAGS + 0xA8) // Unused Flag
#define FLAG_UNUSED_0x909                           (SYSTEM_FLAGS + 0xA9) // Unused Flag
#define FLAG_UNUSED_0x90A                           (SYSTEM_FLAGS + 0xAA) // Unused Flag
#define FLAG_UNUSED_0x90B                           (SYSTEM_FLAGS + 0xAB) // Unused Flag
#define FLAG_UNUSED_0x90C                           (SYSTEM_FLAGS + 0xAC) // Unused Flag
#define FLAG_UNUSED_0x90D                           (SYSTEM_FLAGS + 0xAD) // Unused Flag
#define FLAG_UNUSED_0x90E                           (SYSTEM_FLAGS + 0xAE) // Unused Flag
#define FLAG_UNUSED_0x90F                           (SYSTEM_FLAGS + 0xAF) // Unused Flag
#define FLAG_UNUSED_0x910                           (SYSTEM_FLAGS + 0xB0) // Unused Flag
#define FLAG_UNUSED_0x911                           (SYSTEM_FLAGS + 0xB1) // Unused Flag
#define FLAG_UNUSED_0x912                           (SYSTEM_FLAGS + 0xB2) // Unused Flag
#define FLAG_UNUSED_0x913                           (SYSTEM_FLAGS + 0xB3) // Unused Flag
#define FLAG_UNUSED_0x914                           (SYSTEM_FLAGS + 0xB4) // Unused Flag
#define FLAG_UNUSED_0x915                           (SYSTEM_FLAGS + 0xB5) // Unused Flag
#define FLAG_UNUSED_0x916                           (SYSTEM_FLAGS + 0xB6) // Unused Flag
#define FLAG_UNUSED_0x917                           (SYSTEM_FLAGS + 0xB7) // Unused Flag
#define FLAG_UNUSED_0x918                           (SYSTEM_FLAGS + 0xB8) // Unused Flag
#define FLAG_UNUSED_0x919                           (SYSTEM_FLAGS + 0xB9) // Unused Flag
#define FLAG_UNUSED_0x91A                           (SYSTEM_FLAGS + 0xBA) // Unused Flag
#define FLAG_UNUSED_0x91B                           (SYSTEM_FLAGS + 0xBB) // Unused Flag
#define FLAG_UNUSED_0x91C                           (SYSTEM_FLAGS + 0xBC) // Unused Flag
#define FLAG_UNUSED_0x91D                           (SYSTEM_FLAGS + 0xBD) // Unused Flag
#define FLAG_UNUSED_0x91E                           (SYSTEM_FLAGS + 0xBE) // Unused Flag
#define FLAG_UNUSED_0x91F                           (SYSTEM_FLAGS + 0xBF) // Unused Flag

// Daily Flags
// These flags are cleared once per day
// The start and end are byte-aligned because the flags are cleared in byte increments
#define DAILY_FLAGS_START                           (FLAG_UNUSED_0x91F + (8 - FLAG_UNUSED_0x91F % 8))
#define FLAG_DAILY_BEAT_SILVER                           (DAILY_FLAGS_START + 0x0)  // Unused Flag
#define FLAG_DAILY_CONTEST_LOBBY_RECEIVED_BERRY     (DAILY_FLAGS_START + 0x1)
#define FLAG_DAILY_SECRET_BASE                      (DAILY_FLAGS_START + 0x2)
#define FLAG_DAILY_HAIRCUT1_RECEIVED                           (DAILY_FLAGS_START + 0x3)  // Sudo2
#define FLAG_DAILY_HAIRCUT2_RECEIVED                           (DAILY_FLAGS_START + 0x4)  // Sudo3
#define FLAG_DAILY_BUG_CONTEST_COMPLETED                           (DAILY_FLAGS_START + 0x5)  // Unused Flag
#define FLAG_WONDERTRADE1                           (DAILY_FLAGS_START + 0x6)  // WondertradeFlag (1)
#define FLAG_WONDERTRADE2                           (DAILY_FLAGS_START + 0x7)  // WondertradeFlag (2)
#define FLAG_WONDERTRADE3                           (DAILY_FLAGS_START + 0x8)  // WondertradeFlag (3)
#define FLAG_UNUSED_0x929                           (DAILY_FLAGS_START + 0x9)  // Unused Flag
#define FLAG_DAILY_PICKED_LOTO_TICKET               (DAILY_FLAGS_START + 0xA)
#define FLAG_DAILY_ROUTE_114_RECEIVED_BERRY         (DAILY_FLAGS_START + 0xB)
#define FLAG_DAILY_ROUTE_111_RECEIVED_BERRY         (DAILY_FLAGS_START + 0xC)
#define FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY      (DAILY_FLAGS_START + 0xD)
#define FLAG_DAILY_ROUTE_120_RECEIVED_BERRY         (DAILY_FLAGS_START + 0xE)
#define FLAG_DAILY_LILYCOVE_RECEIVED_BERRY          (DAILY_FLAGS_START + 0xF)
#define FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY       (DAILY_FLAGS_START + 0x10)
#define FLAG_DAILY_BERRY_MASTERS_WIFE               (DAILY_FLAGS_START + 0x11)
#define FLAG_DAILY_SOOTOPOLIS_RECEIVED_BERRY        (DAILY_FLAGS_START + 0x12)
#define FLAG_DAILY_DAISY_GROOMED                           (DAILY_FLAGS_START + 0x13) // Unused Flag
#define FLAG_DAILY_APPRENTICE_LEAVES                (DAILY_FLAGS_START + 0x14)

#define FLAG_UNUSED_0x935                           (DAILY_FLAGS_START + 0x15) // Unused Flag
#define FLAG_UNUSED_0x936                           (DAILY_FLAGS_START + 0x16) // Unused Flag
#define FLAG_UNUSED_0x937                           (DAILY_FLAGS_START + 0x17) // Unused Flag
#define FLAG_UNUSED_0x938                           (DAILY_FLAGS_START + 0x18) // Unused Flag
#define FLAG_UNUSED_0x939                           (DAILY_FLAGS_START + 0x19) // Unused Flag
#define FLAG_UNUSED_0x93A                           (DAILY_FLAGS_START + 0x1A) // Unused Flag
#define FLAG_UNUSED_0x93B                           (DAILY_FLAGS_START + 0x1B) // Unused Flag
#define FLAG_UNUSED_0x93C                           (DAILY_FLAGS_START + 0x1C) // Unused Flag
#define FLAG_UNUSED_0x93D                           (DAILY_FLAGS_START + 0x1D) // Unused Flag
#define FLAG_UNUSED_0x93E                           (DAILY_FLAGS_START + 0x1E) // Unused Flag
#define FLAG_UNUSED_0x93F                           (DAILY_FLAGS_START + 0x1F) // Unused Flag
#define FLAG_UNUSED_0x940                           (DAILY_FLAGS_START + 0x20) // Unused Flag
#define FLAG_UNUSED_0x941                           (DAILY_FLAGS_START + 0x21) // Unused Flag
#define FLAG_UNUSED_0x942                           (DAILY_FLAGS_START + 0x22) // Unused Flag
#define FLAG_UNUSED_0x943                           (DAILY_FLAGS_START + 0x23) // Unused Flag
#define FLAG_UNUSED_0x944                           (DAILY_FLAGS_START + 0x24) // Unused Flag
#define FLAG_UNUSED_0x945                           (DAILY_FLAGS_START + 0x25) // Unused Flag
#define FLAG_UNUSED_0x946                           (DAILY_FLAGS_START + 0x26) // Unused Flag
#define FLAG_UNUSED_0x947                           (DAILY_FLAGS_START + 0x27) // Unused Flag
#define FLAG_UNUSED_0x948                           (DAILY_FLAGS_START + 0x28) // Unused Flag
#define FLAG_UNUSED_0x949                           (DAILY_FLAGS_START + 0x29) // Unused Flag
#define FLAG_UNUSED_0x94A                           (DAILY_FLAGS_START + 0x2A) // Unused Flag
#define FLAG_UNUSED_0x94B                           (DAILY_FLAGS_START + 0x2B) // Unused Flag
#define FLAG_UNUSED_0x94C                           (DAILY_FLAGS_START + 0x2C) // Unused Flag
#define FLAG_UNUSED_0x94D                           (DAILY_FLAGS_START + 0x2D) // Unused Flag
#define FLAG_UNUSED_0x94E                           (DAILY_FLAGS_START + 0x2E) // Unused Flag
#define FLAG_UNUSED_0x94F                           (DAILY_FLAGS_START + 0x2F) // Unused Flag
#define FLAG_UNUSED_0x950                           (DAILY_FLAGS_START + 0x30) // Unused Flag
#define FLAG_UNUSED_0x951                           (DAILY_FLAGS_START + 0x31) // Unused Flag
#define FLAG_UNUSED_0x952                           (DAILY_FLAGS_START + 0x32) // Unused Flag
#define FLAG_UNUSED_0x953                           (DAILY_FLAGS_START + 0x33) // Unused Flag
#define FLAG_UNUSED_0x954                           (DAILY_FLAGS_START + 0x34) // Unused Flag
#define FLAG_UNUSED_0x955                           (DAILY_FLAGS_START + 0x35) // Unused Flag
#define FLAG_UNUSED_0x956                           (DAILY_FLAGS_START + 0x36) // Unused Flag
#define FLAG_UNUSED_0x957                           (DAILY_FLAGS_START + 0x37) // Unused Flag
#define FLAG_UNUSED_0x958                           (DAILY_FLAGS_START + 0x38) // Unused Flag
#define FLAG_UNUSED_0x959                           (DAILY_FLAGS_START + 0x39) // Unused Flag
#define FLAG_UNUSED_0x95A                           (DAILY_FLAGS_START + 0x3A) // Unused Flag
#define FLAG_UNUSED_0x95B                           (DAILY_FLAGS_START + 0x3B) // Unused Flag
#define FLAG_UNUSED_0x95C                           (DAILY_FLAGS_START + 0x3C) // Unused Flag
#define FLAG_UNUSED_0x95D                           (DAILY_FLAGS_START + 0x3D) // Unused Flag
#define FLAG_UNUSED_0x95E                           (DAILY_FLAGS_START + 0x3E) // Unused Flag
#define FLAG_UNUSED_0x95F                           (DAILY_FLAGS_START + 0x3F) // Unused Flag
#define DAILY_FLAGS_END                             (FLAG_UNUSED_0x95F + (7 - FLAG_UNUSED_0x95F % 8))
#define NUM_DAILY_FLAGS                             (DAILY_FLAGS_END - DAILY_FLAGS_START + 1)

#define FLAGS_COUNT (DAILY_FLAGS_END + 1)

// Special Flags (Stored in EWRAM (sSpecialFlags), not in the SaveBlock)
#define SPECIAL_FLAGS_START                     0x4000
#define FLAG_HIDE_MAP_NAME_POPUP                (SPECIAL_FLAGS_START + 0x0)
#define FLAG_DONT_TRANSITION_MUSIC              (SPECIAL_FLAGS_START + 0x1)
#define FLAG_ENABLE_MULTI_CORRIDOR_DOOR         (SPECIAL_FLAGS_START + 0x2)
#define FLAG_SPECIAL_FLAG_UNUSED_0x4003         (SPECIAL_FLAGS_START + 0x3) // Unused Flag
#define FLAG_STORING_ITEMS_IN_PYRAMID_BAG       (SPECIAL_FLAGS_START + 0x4)
#define FLAG_SAFE_FOLLOWER_MOVEMENT             (SPECIAL_FLAGS_START + 0x5) // When set, applymovement does not put the follower inside a pokeball
// FLAG_SPECIAL_FLAG_0x4005 - 0x407F also exist and are unused
#define SPECIAL_FLAGS_END                       (SPECIAL_FLAGS_START + 0x7F)
#define NUM_SPECIAL_FLAGS                       (SPECIAL_FLAGS_END - SPECIAL_FLAGS_START + 1)

// Temp flag aliases
#define FLAG_TEMP_SKIP_GABBY_INTERVIEW          FLAG_TEMP_1
#define FLAG_TEMP_REGICE_PUZZLE_STARTED         FLAG_TEMP_2
#define FLAG_TEMP_REGICE_PUZZLE_FAILED          FLAG_TEMP_3
#define FLAG_TEMP_HIDE_MIRAGE_ISLAND_BERRY_TREE FLAG_TEMP_11

#endif // GUARD_CONSTANTS_FLAGS_H
