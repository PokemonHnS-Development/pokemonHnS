#ifndef GUARD_DIFFICULTY_H
#define GUARD_DIFFICULTY_H
//tx_randomizer_and_challenges

// default options set by the dev
#define TX_RANDOM_STARTER               FALSE
#define TX_RANDOM_WILD_POKEMON          FALSE
#define TX_RANDOM_TRAINER               FALSE
#define TX_RANDOM_STATIC                FALSE
#define TX_RANDOM_SIMILAR               TRUE
#define TX_RANDOM_MAP_BASED             TRUE
#define TX_RANDOM_INCLUDE_LEGENDARIES   FALSE
#define TX_RANDOM_TYPE                  FALSE
#define TX_RANDOM_MOVES                 FALSE
#define TX_RANDOM_ABILITIES             FALSE
#define TX_RANDOM_EVOLUTION             FALSE
#define TX_RANDOM_EVOLUTION_METHODE     FALSE
#define TX_RANDOM_TYPE_EFFECTIVENESS    FALSE
#define TX_RANDOM_ITEMS                 FALSE
#define TX_RANDOM_CHAOS_MODE            FALSE

#define TX_NUZLOCKE_NUZLOCKE 0
#define TX_NUZLOCKE_NUZLOCKE_HARDCORE 0 //CAREFULL!!!!!
#define TX_NUZLOCKE_SPECIES_CLAUSE 1
#define TX_NUZLOCKE_SHINY_CLAUSE 1
#define TX_NUZLOCKE_NICKNAMING 1
#define TX_NUZLOCKE_DELETION 0

#define TX_DIFFICULTY_PARTY_LIMIT 0
#define TX_DIFFICULTY_LEVEL_CAP 0
#define TX_DIFFICULTY_EXP_MULTIPLIER 0
#define TX_DIFFICULTY_NO_ITEM_PLAYER 0
#define TX_DIFFICULTY_NO_ITEM_TRAINER 0
#define TX_DIFFICULTY_NO_EVS 0
#define TX_DIFFICULTY_SCALING_IVS 0
#define TX_DIFFICULTY_SCALING_EVS 0
#define TX_DIFFICULTY_PKMN_CENTER 0 //0 no limit, 1 none
#define TX_DIFFICULTY_LIMIT_DIFFICULTY 0
#define TX_DIFFICULTY_MAX_PARTY_IVS 0

#define TX_CHALLENGE_EVO_LIMIT 0 //0 off, 1 first, 2 none
#define TX_CHALLENGE_BASE_STAT_EQUALIZER 0 //0=off, 1=100, 2=255, 3=500
#define TX_CHALLENGE_TYPE_OFF 31
#define TX_CHALLENGE_TYPE TX_CHALLENGE_TYPE_OFF //TX_CHALLENGE_TYPE_OFF for off
#define TX_CHALLENGE_MIRROR 0
#define TX_CHALLENGE_PCHEAL 0
#define TX_CHALLENGE_MIRROR_THIEF 0
#define TX_CHALLENGES_LESS_ESCAPES 0
#define TX_MODE_ALTERNATE_SPAWNS 0 
#define TX_FEATURES_SHINY_CHANCE 0
#define TX_FEATURES_ITEM_DROP 0
#define TX_MODE_INFINITE_TMS 0
#define TX_MODE_SURVIVE_POISON 0
#define TX_FEATURES_EASIER_FEEBAS 0
#define TX_FEATURES_PKMN_DEATH 0
#define TX_FEATURES_RTC_TYPE 0
#define TX_FEATURES_UNLIMITED_WT 0
#define TX_MODE_NEW_SYNCHRONIZE 0
#define TX_MODE_MINTS 0
#define TX_MODE_NEW_CITRUS 0
#define TX_MODE_MODERN_TYPES 0
#define TX_MODE_FAIRY_TYPES 0
#define TX_MODE_NEW_STATS 0
#define TX_MODE_STURDY 0
#define TX_MODE_MODERN_MOVES 0
#define TX_MODE_LEGENDARY_ABILITIES 0
#define TX_MODE_NEW_LEGENDARIES 0
#define TX_CHALLENGES_EXPENSIVE 0
#define TX_DIFFICULTY_ESCAPE_ROPE_DIG 0
#define TX_DIFFICULTY_HARD_EXP 0
#define TX_FEATURES_FRONTIER_BANS 0
#define TX_MODE_TYPE_EFFECTIVENESS 0

// randomization types
#define TX_RANDOM_T_WILD_POKEMON    0
#define TX_RANDOM_T_TRAINER         1
#define TX_RANDOM_T_MOVES           2
#define TX_RANDOM_T_ABILITY         3
#define TX_RANDOM_T_EVO             4
#define TX_RANDOM_T_EVO_METH        5
#define TX_RANDOM_T_STATIC          6

void CB2_InitTxRandomizerChallengesMenu(void);
void Task_ChooseChallenge_NoNewGame(u8 taskId);
void SaveData_TxRandomizerAndChallenges(void);

bool8 IsRandomizerActivated(void);
bool8 IsOneTypeChallengeActive(void);
bool8 AreAnyChallengesActive(void);
bool8 AreFeaturesActivated(void);
bool8 IsNuzlockeActive(void);
bool8 IsNuzlockeNicknamingActive(void);
bool8 IsPokecenterChallengeActivated(void);
bool8 IsRandomItemsActivated(void);
bool8 HMsOverwriteOptionActive(void);

u8 NuzlockeFlagGet(u16 mapsec);
u8 NuzlockeFlagSet(u16 mapsec);
u8 NuzlockeFlagClear(u16 mapsec);
void NuzlockeDeletePartyMon(u8 position);
void NuzlockeDeletePartyMonOption(u8 position);
void NuzlockeDeleteFaintedPartyPokemon(void);
u8 GetMaxPartySize(void);
u8 GetCurrentPartyLevelCap(void);
u8 GetCurrentTrainerIVs(void);
u8 GetCurrentTrainerEVs(void);

void PrintTXSaveData(void);
void TestRandomizerValues(u8 type);

// constants
#define TX_MENU_ITEMS_PER_PAGE 6

extern struct tx_randomizer_OptionsMenu *sRandomizerOptions;
extern struct tx_challenges_OptionsMenu *sChallengesOptions;

#define TX_EXP_MULTIPLER_ONLY_ON_NUZLOCKE_AND_RANDOMIZER FALSE

#define TX_NUZLOCKE_CEMETERY_ICON_GRAY TRUE

#endif // GUARD_DIFFICULTY_H