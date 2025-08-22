#ifndef GUARD_CONSTANTS_VARS_H
#define GUARD_CONSTANTS_VARS_H

#define VARS_START 0x4000

// temporary vars
// The first 0x10 vars are temporary--they are cleared every time a map is loaded.
#define TEMP_VARS_START            0x4000
#define VAR_TEMP_0                 (TEMP_VARS_START + 0x0)
#define VAR_TEMP_1                 (TEMP_VARS_START + 0x1)
#define VAR_TEMP_2                 (TEMP_VARS_START + 0x2)
#define VAR_TEMP_3                 (TEMP_VARS_START + 0x3) // Note: Used when the player checks a TV
#define VAR_TEMP_4                 (TEMP_VARS_START + 0x4)
#define VAR_TEMP_5                 (TEMP_VARS_START + 0x5)
#define VAR_TEMP_6                 (TEMP_VARS_START + 0x6)
#define VAR_TEMP_7                 (TEMP_VARS_START + 0x7)
#define VAR_TEMP_8                 (TEMP_VARS_START + 0x8)
#define VAR_TEMP_9                 (TEMP_VARS_START + 0x9)
#define VAR_TEMP_A                 (TEMP_VARS_START + 0xA)
#define VAR_TEMP_B                 (TEMP_VARS_START + 0xB)
#define VAR_TEMP_C                 (TEMP_VARS_START + 0xC)
#define VAR_TEMP_D                 (TEMP_VARS_START + 0xD)
#define VAR_TEMP_E                 (TEMP_VARS_START + 0xE)
#define VAR_TEMP_F                 (TEMP_VARS_START + 0xF)
#define TEMP_VARS_END              VAR_TEMP_F
#define NUM_TEMP_VARS              (TEMP_VARS_END - TEMP_VARS_START + 1)

// object gfx id vars
// These 0x10 vars are used to dynamically control a map object's sprite.
// For example, the rival's sprite id is dynamically set based on the player's gender.
// See VarGetObjectEventGraphicsId().
#define VAR_OBJ_GFX_ID_0           0x4010
#define VAR_OBJ_GFX_ID_1           0x4011
#define VAR_OBJ_GFX_ID_2           0x4012
#define VAR_OBJ_GFX_ID_3           0x4013
#define VAR_OBJ_GFX_ID_4           0x4014
#define VAR_OBJ_GFX_ID_5           0x4015
#define VAR_OBJ_GFX_ID_6           0x4016
#define VAR_OBJ_GFX_ID_7           0x4017
#define VAR_OBJ_GFX_ID_8           0x4018
#define VAR_OBJ_GFX_ID_9           0x4019
#define VAR_OBJ_GFX_ID_A           0x401A
#define VAR_OBJ_GFX_ID_B           0x401B
#define VAR_OBJ_GFX_ID_C           0x401C
#define VAR_OBJ_GFX_ID_D           0x401D
#define VAR_OBJ_GFX_ID_E           0x401E
#define VAR_OBJ_GFX_ID_F           0x401F

// general purpose vars
#define VAR_RECYCLE_GOODS                                0x4020
#define VAR_REPEL_STEP_COUNT                             0x4021
#define VAR_ICE_STEP_COUNT                               0x4022
#define VAR_STARTER_MON                                  0x4023 // 0=Treecko, 1=Torchic, 2=Mudkip
#define VAR_MIRAGE_RND_H                                 0x4024
#define VAR_MIRAGE_RND_L                                 0x4025
#define VAR_SECRET_BASE_MAP                              0x4026
#define VAR_CYCLING_ROAD_RECORD_COLLISIONS               0x4027
#define VAR_CYCLING_ROAD_RECORD_TIME_L                   0x4028
#define VAR_CYCLING_ROAD_RECORD_TIME_H                   0x4029
#define VAR_FRIENDSHIP_STEP_COUNTER                      0x402A
#define VAR_POISON_STEP_COUNTER                          0x402B
#define VAR_RESET_RTC_ENABLE                             0x402C
#define VAR_ENIGMA_BERRY_AVAILABLE                       0x402D
#define VAR_WONDER_NEWS_STEP_COUNTER                     0x402E

#define VAR_FRONTIER_MANIAC_FACILITY                     0x402F
#define VAR_FRONTIER_GAMBLER_CHALLENGE                   0x4030
#define VAR_FRONTIER_GAMBLER_SET_CHALLENGE               0x4031
#define VAR_FRONTIER_GAMBLER_AMOUNT_BET                  0x4032
#define VAR_FRONTIER_GAMBLER_STATE                       0x4033

#define VAR_DEOXYS_ROCK_STEP_COUNT                       0x4034
#define VAR_DEOXYS_ROCK_LEVEL                            0x4035
#define VAR_PC_BOX_TO_SEND_MON                           0x4036
#define VAR_ABNORMAL_WEATHER_LOCATION                    0x4037
#define VAR_ABNORMAL_WEATHER_STEP_COUNTER                0x4038
#define VAR_SHOULD_END_ABNORMAL_WEATHER                  0x4039
#define VAR_FARAWAY_ISLAND_STEP_COUNTER                  0x403A
#define VAR_REGICE_STEPS_1                               0x403B
#define VAR_REGICE_STEPS_2                               0x403C
#define VAR_REGICE_STEPS_3                               0x403D
#define VAR_ALTERING_CAVE_WILD_SET                       0x403E
#define VAR_DISTRIBUTE_EON_TICKET                        0x403F // This var is read and written, but is always zero. The only way to obtain the Eon Ticket in Emerald is via Record Mixing
#define VAR_DAYS                                         0x4040
#define VAR_FANCLUB_FAN_COUNTER                          0x4041
#define VAR_FANCLUB_LOSE_FAN_TIMER                       0x4042
#define VAR_DEPT_STORE_FLOOR                             0x4043
#define VAR_TRICK_HOUSE_LEVEL                            0x4044
#define VAR_POKELOT_PRIZE_ITEM                           0x4045
#define VAR_NATIONAL_DEX                                 0x4046
#define VAR_SEEDOT_SIZE_RECORD                           0x4047
#define VAR_ASH_GATHER_COUNT                             0x4048
#define VAR_BIRCH_STATE                                  0x4049
#define VAR_CRUISE_STEP_COUNT                            0x404A
#define VAR_POKELOT_RND1                                 0x404B
#define VAR_POKELOT_RND2                                 0x404C
#define VAR_POKELOT_PRIZE_PLACE                          0x404D
#define VAR_REPEL_LAST_USED                              0x404E
#define VAR_LOTAD_SIZE_RECORD                            0x404F
#define VAR_NEWBARK_TOWN_STATE                           0x4050 //START VARS FOR CRYSTAL HERE. 0 = havent set clock, 1 = convo with mom, 2 = talk to elm, 3 = go to mr pokemon, 4 = go to mom again, 5 = done. 6 = First time beating league, 7 = done.
#define VAR_STARTER_SPECIES                              0x4051 //152 = CHIKO, 155 = CYNDA, 158 = TOTOD
#define VAR_NEWBARKTOWN_LABSTATE                         0x4052 // 0 = talk to elm first time, 1 = choose starter, 2 = chosen starter, 3=received potion 4 = police! 5 = receive balls, 6 = get masterball, 7 = gotokimono, 8 = goto league, 9 = get SS ticket, 10 = done
#define VAR_CHERRYGROVE_CITY_STATE                       0x4053 //0 = guidegent, 1= goto mrpokemon, 2= phonecall, 3=silver, 4=done
#define VAR_PALLETTOWN_LABSTATE                          0x4054 // 0 = goto lab, 1 = been to lab
#define VAR_COMPLETED_LUGIA                              0x4055 // 0, 1 = Not Primed.  2 = fight lugia, 3 = done. 4 = non-story lugia encounter active.
#define VAR_COMPLETED_HO_OH                              0x4056 // 0, 1 = Not Primed. 2 = fight hooh, 3 = done. 4 = non-story hooh encounter active.
#define VAR_VIOLET_CITY_STATE                            0x4057 //0 on trigger, 1 when done
#define VAR_AZALEA_TOWN_STATE                            0x4058 //0 on trigger, 1 = talk to kurt, 2 = goto well, 3 = goto kurt well, 4 = goto gym, 5 = fight silver, 6 = find farfetchd, 7 = bringGSBall, 8 = GoOutside, 9 = Celebi, 10 = done
#define VAR_GOLDENROD_CITY_STATE                         0x4059 //0 on trigger, 1 = get radio, 2 = fight whitney, 3 = whitney crying, 4 = whitney give badge, 5 = complete before rocket. 6 = fight petrel, 7 = meet kimono, 8 = silver, 9 = director-archer, 10 = return NPCS, 11 = done
#define VAR_ECRUTEAK_CITY_STATE                          0x405A //1 = goto burnedtower, 2 = goto silver, 3 = release the beasts, 4 = beat Morty, 5 = done. 10 goto sage office, 11 goto ho-oh, 12 ho-oh done.
#define VAR_MAHOGANY_TOWN_STATE                          0x405B //1 = fight gyarados, 2 = talk to lance, 3 = agree with lance, 4 = goto shop, 5 = goto B2F hideout,  6 = goto B3F, 7 = silver at the door, 8 = petrel, 9 = murkrow1, 10 = murkrow2, 11 = murkrow3, 12 = fight ariana, 13 = do electrodes, 14 = beat pryce, 15 = get call, 16 = solve goldenrod, 17 = done.
#define VAR_OLIVINE_CITY_STATE                           0x405C //1 = trigger silver, 2 = climb lighthouse, 3 = get potion, 4 = deliver potion, 5 = goto gym row1, 6 = gymrow2, 7 = jasmine, 8 = done
#define VAR_CIANWOOD_CITY_STATE                          0x405D 
#define VAR_SAFARI_ZONE_GATE_STATE                       0x405E
#define VAR_BLACKTHORN_CITY_STATE                        0x405F //1 = fight clair, 2 =goto elder, 3 = talk to clair again, 4 = get phonecall, 5 = done
#define VAR_PALLET_TOWN_STATE                            0x4060
#define VAR_VIRIDIAN_CITY_STATE                          0x4061 
#define VAR_PEWTER_CITY_STATE                            0x4062 
#define VAR_CERULEAN_CITY_STATE                          0x4063 //0 = enter town, 1 = fix power, 2 = find misty, 3 = battle misty, 4 = done
#define VAR_VERMILION_CITY_STATE                         0x4064 
#define VAR_LAVENDER_TOWN_STATE                          0x4065 
#define VAR_CELADON_CITY_STATE                           0x4066 
#define VAR_SAFFRON_CITY_STATE                           0x4067 
#define VAR_FUCHSIA_CITY_STATE                           0x4068 
#define VAR_SPROUT_TOWER                                 0x4069
#define VAR_VIOLET_CITY_KIMONO_GIRL                      0x406A 
#define VAR_SLOWPOKE_TAIL                                0x406B 
#define VAR_ILEX_FOREST_FARFETCHD                        0x406C //0 = CHASING, 1// start going right way, 2 = done
#define VAR_ELEVATOR                                     0x406D 
#define VAR_TRAIN                                        0x406E 
#define VAR_LUGIA_OR_HOOH                                0x406F // 0 = unset, 1 = lugia, 2 = ho-oh
#define VAR_KENYA                                        0x4070 // 0 = take, 1 = deliver, 2 = delivered, 3 = informed of delivery
#define VAR_BUG_CONTEST_STATE                            0x4071
#define VAR_ECRUTEAK_THEATER                             0x4072 //0 = goto theater, 1 = talk to rocket, 2 = get surf, 3 = wait until 8th badge elm visit. 4 = talktosilver, 5 = fightkimono, 6 = goto legendary, 7 = done legendary.
#define VAR_ROUTE39_BARN                                 0x4073 // 0 = give 5 berries. 1 = give 4 berries. 2 = give 3 berries, 3 = give 2 berries, 4 = give 1 berry, 5 = healed, can buy milk.
#define VAR_RUINSOFALPH_STATE                            0x4074
#define VAR_SHUCKIE                                      0x4075 // 0 = unset, 1 = given, 2 = returnable, 3 = returned
#define VAR_GETFLY                                       0x4076 
#define VAR_ROCKET_HIDEOUT_STATUE_1                      0x4077 
#define VAR_ROCKET_HIDEOUT_STATUE_2                      0x4078 
#define VAR_ROCKET_HIDEOUT_STATUE_3                      0x4079 
#define VAR_ROCKET_HIDEOUT_STATUE_4                      0x407A 
#define VAR_ROCKET_HIDEOUT_STATUE_5                      0x407B
#define VAR_ROCKET_PASSWORD                              0x407C // 0-2
#define VAR_ELECTRODES_FAINTED                           0x407D 
#define VAR_LAKE_OF_RAGE_FISHERMAN                       0x407E // 0 = unmet, 1 = met, 2 = received a magikarp, 3 = received a satisfactory magikarp
#define VAR_BLACKTHORN_GYM_STATE                         0x407F // Unused Var
#define VAR_DRAGONS_DEN_QUIZ                             0x4080 // Unused Var
#define VAR_ROUTE27_STATE                                0x4081 // 0 = enter route 27 via surf, 1 = goto junction, 2 = fight silver, 3 = done
#define VAR_LEAGUE_STATE                                 0x4082
#define VAR_TIME_BASED_ENCOUNTER                         0x4083 // Different encounter tables
#define VAR_ICE_PATH_STATE                               0x4084 //0 = meet kimono, 1 = done
#define VAR_SSAQUA_STATE                                 0x4085 // 0 = ride to kanto on SS AQUA, 1 = encounter grandfather, 2 = find sleeping sailor, 3 = find girl, 4 = receive arrival message, 5 = done
#define VAR_CLEFAIRY_DOLL_STATE                          0x4086
#define VAR_CABLE_CLUB_STATE                             0x4087
#define VAR_CONTEST_TYPE                                 0x4088
#define VAR_SECRET_BASE_INITIALIZED                      0x4089
#define VAR_CONTEST_PRIZE_PICKUP                         0x408A
#define VAR_FAN_CLUB_GUY                                 0x408B // Unused Var
#define VAR_FAN_CLUB_CLEFAIRY                            0x408C //0 = goto copycat, 1 = goto fanclub, 2 = goto copycat, 3 = done
#define VAR_KANTO_ROCKET_STORY_STATE                     0x408D //0 = goto powerplant, 1 = powerplant cop, 2 = goto cerulean gym, 3 = goto bridge, 4 = battle rocket, 5 = retrieve part, 6 = return part, 7 = done.
#define VAR_SUICUNE_ENCOUNTERS                           0x408E //0 = goto cianwood, 1 = encounter suicune cianwood, 2 = find suicune on route 42, 3 = goto vermilion, 4 = goto route 14, 5 = beat cerulean gym, 6 = goto route 25, 7 = talk to suicune, 8 = done
#define VAR_BILLS_GRANDPA                                0x408F //0 = meet gramps
#define VAR_NUM_BADGES                                   0x4090
#define VAR_KANTO_SAFARI_ZONE_PROGRESS                   0x4091 // 0 = meet steven, 1 = unlock brush, 2 = unlock mountain, 3 = unlock cave, 4  = don
#define VAR_BAOBA_QUEST_STATE                            0x4092 //0 = goto FUCHSIA, 1 = give BELDUM to baoba for 200k, 2 = give CASTFORM to baoba for 300k, 3 = give MEDICHAM to baoba for 400k, 4 = give BAGON to baboa for 500k, 5 = done
#define VAR_CINNABAR_ISLAND_STATE                        0x4093
#define VAR_MT_SILVER_STATE                              0x4094
#define VAR_LILYCOVE_FAN_CLUB_STATE                      0x4095
#define VAR_EMBEDDED_TOWER                               0x4096 // 2 = fight rayquaza
#define VAR_INIT_SECRET_BASE                             0x4097
#define VAR_PETALBURG_WOODS_STATE                        0x4098
#define VAR_LILYCOVE_CONTEST_LOBBY_STATE                 0x4099
#define VAR_RUSTURF_TUNNEL_STATE                         0x409A
#define VAR_UNUSED_0x409B                                0x409B // Unused Var
#define VAR_ELITE_4_STATE                                0x409C
#define VAR_UNUSED_0x409D                                0x409D // Unused Var
#define VAR_MOSSDEEP_SPACE_CENTER_STAIR_GUARD_STATE      0x409E
#define VAR_MOSSDEEP_SPACE_CENTER_STATE                  0x409F
#define VAR_SLATEPORT_HARBOR_STATE                       0x40A0
#define VAR_UNUSED_0x40A1                                0x40A1 // Unused var
#define VAR_SEAFLOOR_CAVERN_STATE                        0x40A2
#define VAR_CABLE_CAR_STATION_STATE                      0x40A3
#define VAR_SAFARI_ZONE_STATE                            0x40A4  // 0: In or out of SZ, 1: Player exiting SZ, 2: Player entering SZ
#define VAR_TRICK_HOUSE_BEING_WATCHED_STATE              0x40A5
#define VAR_TRICK_HOUSE_FOUND_TRICK_MASTER               0x40A6
#define VAR_TRICK_HOUSE_ENTRANCE_STATE                   0x40A7
#define VAR_UNUSED_0x40A8                                0x40A8 // Unused Var
#define VAR_CYCLING_CHALLENGE_STATE                      0x40A9
#define VAR_SLATEPORT_MUSEUM_1F_STATE                    0x40AA
#define VAR_TRICK_HOUSE_PUZZLE_1_STATE                   0x40AB
#define VAR_TRICK_HOUSE_PUZZLE_2_STATE                   0x40AC
#define VAR_TRICK_HOUSE_PUZZLE_3_STATE                   0x40AD
#define VAR_TRICK_HOUSE_PUZZLE_4_STATE                   0x40AE
#define VAR_TRICK_HOUSE_PUZZLE_5_STATE                   0x40AF
#define VAR_TRICK_HOUSE_PUZZLE_6_STATE                   0x40B0
#define VAR_TRICK_HOUSE_PUZZLE_7_STATE                   0x40B1
#define VAR_TRICK_HOUSE_PUZZLE_8_STATE                   0x40B2
#define VAR_WEATHER_INSTITUTE_STATE                      0x40B3
#define VAR_SS_TIDAL_STATE                               0x40B4
#define VAR_TRICK_HOUSE_ENTER_FROM_CORRIDOR              0x40B5
#define VAR_TRICK_HOUSE_PUZZLE_7_STATE_2                 0x40B6 // Leftover from RS, never set
#define VAR_SLATEPORT_FAN_CLUB_STATE                     0x40B7
#define VAR_UNUSED_0x40B8                                0x40B8 // Unused Var
#define VAR_MT_PYRE_STATE                                0x40B9
#define VAR_NEW_MAUVILLE_STATE                           0x40BA
#define VAR_UNUSED_0x40BB                                0x40BB // Unused Var
#define VAR_BRAVO_TRAINER_BATTLE_TOWER_ON                0x40BC
#define VAR_JAGGED_PASS_ASH_WEATHER                      0x40BD
#define VAR_GLASS_WORKSHOP_STATE                         0x40BE
#define VAR_METEOR_FALLS_STATE                           0x40BF
#define VAR_SOOTOPOLIS_MYSTERY_EVENTS_STATE              0x40C0
#define VAR_TRICK_HOUSE_PRIZE_PICKUP                     0x40C1
#define VAR_PACIFIDLOG_TM_RECEIVED_DAY                   0x40C2
#define VAR_VICTORY_ROAD_1F_STATE                        0x40C3
#define VAR_FOSSIL_RESURRECTION_STATE                    0x40C4
#define VAR_WHICH_FOSSIL_REVIVED                         0x40C5
#define VAR_STEVENS_HOUSE_STATE                          0x40C6
#define VAR_OLDALE_RIVAL_STATE                           0x40C7
#define VAR_JAGGED_PASS_STATE                            0x40C8
#define VAR_SCOTT_PETALBURG_ENCOUNTER                    0x40C9
#define VAR_SKY_PILLAR_STATE                             0x40CA
#define VAR_MIRAGE_TOWER_STATE                           0x40CB
#define VAR_FOSSIL_MANIAC_STATE                          0x40CC
#define VAR_CABLE_CLUB_TUTORIAL_STATE                    0x40CD
#define VAR_FRONTIER_BATTLE_MODE                         0x40CE
#define VAR_FRONTIER_FACILITY                            0x40CF
#define VAR_HAS_ENTERED_BATTLE_FRONTIER                  0x40D0 // Var is used like a flag.
#define VAR_SCOTT_STATE                                  0x40D1
#define VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE               0x40D2
#define VAR_DEX_UPGRADE_JOHTO_STARTER_STATE              0x40D3
#define VAR_SS_TIDAL_SCOTT_STATE                         0x40D4 // Always equal to FLAG_MET_SCOTT_ON_SS_TIDAL
#define VAR_ROAMER_POKEMON                               0x40D5 // 0 = Latias, 1 = Latios
#define VAR_TRAINER_HILL_IS_ACTIVE                       0x40D6
#define VAR_SKY_PILLAR_RAYQUAZA_CRY_DONE                 0x40D7
#define VAR_SOOTOPOLIS_WALLACE_STATE                     0x40D8
#define VAR_HAS_TALKED_TO_SEAFLOOR_CAVERN_ENTRANCE_GRUNT 0x40D9
#define VAR_REGISTER_BIRCH_STATE                         0x40DA
#define VAR_UNUSED_0x40DB                                0x40DB // Unused Var
#define VAR_UNUSED_0x40DC                                0x40DC // Unused Var
#define VAR_GIFT_PICHU_SLOT                              0x40DD
#define VAR_GIFT_UNUSED_1                                0x40DE // Var is written to, but never read
#define VAR_GIFT_UNUSED_2                                0x40DF // Var is written to, but never read
#define VAR_GIFT_UNUSED_3                                0x40E0 // Var is written to, but never read
#define VAR_GIFT_UNUSED_4                                0x40E1 // Var is written to, but never read
#define VAR_GIFT_UNUSED_5                                0x40E2 // Var is written to, but never read
#define VAR_GIFT_UNUSED_6                                0x40E3 // Var is written to, but never read
#define VAR_GIFT_UNUSED_7                                0x40E4 // var is written to, but never read
#define VAR_DEBUG_OPTIONS                                0x40E5
#define VAR_DAILY_SLOTS                                  0x40E6
#define VAR_DAILY_WILDS                                  0x40E7
#define VAR_DAILY_BLENDER                                0x40E8
#define VAR_DAILY_PLANTED_BERRIES                        0x40E9
#define VAR_DAILY_PICKED_BERRIES                         0x40EA
#define VAR_DAILY_ROULETTE                               0x40EB
#define VAR_SECRET_BASE_STEP_COUNTER                     0x40EC // Used by Secret Base TV programs
#define VAR_SECRET_BASE_LAST_ITEM_USED                   0x40ED // Used by Secret Base TV programs
#define VAR_SECRET_BASE_LOW_TV_FLAGS                     0x40EE // Used by Secret Base TV programs
#define VAR_SECRET_BASE_HIGH_TV_FLAGS                    0x40EF // Used by Secret Base TV programs
#define VAR_SECRET_BASE_IS_NOT_LOCAL                     0x40F0 // Set to TRUE while in another player's secret base.
#define VAR_DAILY_BP                                     0x40F1
#define VAR_WALLY_CALL_STEP_COUNTER                      0x40F2
#define VAR_SCOTT_FORTREE_CALL_STEP_COUNTER              0x40F3
#define VAR_ROXANNE_CALL_STEP_COUNTER                    0x40F4
#define VAR_SCOTT_BF_CALL_STEP_COUNTER                   0x40F5
#define VAR_RIVAL_RAYQUAZA_CALL_STEP_COUNTER             0x40F6
#define VAR_SUICUNE_EVENT                                0x40F7
#define VAR_ENTEI_EVENT                                  0x40F8
#define VAR_RAIKOU_EVENT                                 0x40F9
#define VAR_UNUSED_0x40FA                                0x40FA // Unused Var
#define VAR_UNUSED_0x40FB                                0x40FB // Unused Var
#define VAR_UNUSED_0x40FC                                0x40FC // Unused Var
#define VAR_UNUSED_0x40FD                                0x40FD // Unused Var
#define VAR_UNUSED_0x40FE                                0x40FE // Unused Var
#define VAR_GARBAGEVAR                                   0x40FF // Used to replace little root state

#define VARS_END                                         0x40FF
#define VARS_COUNT                                       (VARS_END - VARS_START + 1)

#define SPECIAL_VARS_START            0x8000
// special vars
// They are commonly used as parameters to commands, or return values from commands.
#define VAR_0x8000                    0x8000
#define VAR_0x8001                    0x8001
#define VAR_0x8002                    0x8002
#define VAR_0x8003                    0x8003
#define VAR_0x8004                    0x8004
#define VAR_0x8005                    0x8005
#define VAR_0x8006                    0x8006
#define VAR_0x8007                    0x8007
#define VAR_0x8008                    0x8008
#define VAR_0x8009                    0x8009
#define VAR_0x800A                    0x800A
#define VAR_0x800B                    0x800B
#define VAR_FACING                    0x800C
#define VAR_RESULT                    0x800D
#define VAR_ITEM_ID                   0x800E
#define VAR_LAST_TALKED               0x800F
#define VAR_CONTEST_RANK              0x8010
#define VAR_CONTEST_CATEGORY          0x8011
#define VAR_MON_BOX_ID                0x8012
#define VAR_MON_BOX_POS               0x8013
#define VAR_UNUSED_0x8014             0x8014
#define VAR_TRAINER_BATTLE_OPPONENT_A 0x8015 // Alias of gTrainerBattleOpponent_A and TRAINER_BATTLE_PARAM.opponentA

#define SPECIAL_VARS_END              0x8015

// If an overworld trigger uses this pseudo-variable as the trigger check,
// then the script will be run using RunScriptImmediately instead of in the
// global script context. This means it will run faster, but cannot do any
// cutscenes nor call a wait command. Used for weather effects in vanilla.
#define TRIGGER_RUN_IMMEDIATELY   0

// Temp var aliases
#define VAR_TEMP_CHALLENGE_STATUS  VAR_TEMP_0

#define VAR_TEMP_MIXED_RECORDS         VAR_TEMP_0
#define VAR_TEMP_RECORD_MIX_GIFT_ITEM  VAR_TEMP_1

#define VAR_TEMP_PLAYING_PYRAMID_MUSIC  VAR_TEMP_E

#define VAR_TEMP_FRONTIER_TUTOR_SELECTION  VAR_TEMP_D
#define VAR_TEMP_FRONTIER_TUTOR_ID         VAR_TEMP_E

#define VAR_TEMP_TRANSFERRED_SPECIES  VAR_TEMP_1

#if TESTING
#define TESTING_VARS_START                  0x9000
#define TESTING_VAR_DIFFICULTY              (TESTING_VARS_START + 0x0)
#define TESTING_VAR_STARTING_STATUS         (TESTING_VARS_START + 0x1)
#define TESTING_VAR_STARTING_STATUS_TIMER   (TESTING_VARS_START + 0x2)
#define TESTING_VAR_UNUSED_3                (TESTING_VARS_START + 0x3)
#define TESTING_VAR_UNUSED_4                (TESTING_VARS_START + 0x4)
#define TESTING_VAR_UNUSED_5                (TESTING_VARS_START + 0x5)
#define TESTING_VAR_UNUSED_6                (TESTING_VARS_START + 0x6)
#define TESTING_VAR_UNUSED_7                (TESTING_VARS_START + 0x7)
#endif // TESTING

#endif // GUARD_CONSTANTS_VARS_H
