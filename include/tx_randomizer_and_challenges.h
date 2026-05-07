#ifndef GUARD_DIFFICULTY_H
#define GUARD_DIFFICULTY_H
//tx_randomizer_and_challenges

// default options set by the dev
#define TX_MODE_MODERN_MOVES            1 // if enabled, overall move pool increased, and updated learnsets used
#define TX_MODE_NEW_SYNCHRONIZE         1 // if enabled, Synchronize ability has Gen8+ version of its overworld effect
#define TX_MODE_STURDY                  1 // if enabled, Sturdy ability works as in Gen5+
#define TX_MODE_NEW_CITRUS              1 // if enabled, Sitrus Berries restore 25% HP as in Gen4+
#define TX_MODE_FAIRY_TYPES             1 // if enabled, relevant species have Gen6+ typings
#define TX_MODE_LEGENDARY_ABILITIES     1 // if enabled, Legendary Pokemon have Pressure ability replaced
#define TX_MODE_INFINITE_TMS            1 // if enabled, TMs not depleted when used
#define TX_MODE_MINTS                   1 // if enabled, Nature Mint shop available after Gym 4
#define TX_MODE_SURVIVE_POISON          1 // if enabled, overworld poison damage stops at 1HP
#define TX_MODE_TYPE_EFFECTIVENESS      1 // if enabled, updated type chart used
#define TX_MODE_ALTERNATE_SPAWNS        0 // ?
#define TX_MODE_MODERN_TYPES            0 // if enabled, some species have custom typings
#define TX_MODE_NEW_STATS               0 // if enabled, some species have custom base stats
#define TX_MODE_NEW_LEGENDARIES         0 // ?

#define TX_FEATURES_RTC_TYPE            0 // 0 Real Time Clock used, 1 fake RTC used (1hr irl = 1 day in-game)
#define TX_FEATURES_SHINY_CHANCE        0 // 0 = 1/8192, 1 = 1/4096, 2 = 1/2048, 3 = 1/1024, 4 = 1/512 (base shiny rate, default 1/8192, is multiplied by 2 to the power of this value)
#define TX_FEATURES_SHINY_COLORS        1 // if enabled, custom palettes are used for shinies if possible
#define TX_FEATURES_ITEM_DROP           0 // if enabled, held items of defeated wild pokemon added to bag
#define TX_FEATURES_FRONTIER_BANS       0 // if enabled, Legendary Pokemon are unbanned in the Battle Frontier
#define TX_FEATURES_EASIER_FEEBAS       0 // ?
#define TX_FEATURES_UNLIMITED_WT        0 // ?

#define TX_RANDOM_STARTER               FALSE   // 0 default starters, 1 randomized starters
#define TX_RANDOM_WILD_POKEMON          FALSE   // 0 normal encounter tables, 1 species in tables replaced by randomized counterpart species
#define TX_RANDOM_TRAINER               FALSE   // 0 normal trainer teams, 1 randomized trainer teams
#define TX_RANDOM_STATIC                FALSE   // 0 static encounters match OW sprite, 1 static encounters randomized
#define TX_RANDOM_SIMILAR               TRUE    // 0 randomized species pull from full pool, 1 randomized species have similar BSTs
#define TX_RANDOM_MAP_BASED             TRUE    // ?
#define TX_RANDOM_INCLUDE_LEGENDARIES   FALSE   // 0 legendaries not included in randomizer pool, 1 legendaries included in pool
#define TX_RANDOM_TYPE                  FALSE   // 0 normal species typings, 1 randomized species typings
#define TX_RANDOM_MOVES                 FALSE   // 0 normal learnsets, 1 moves in learnsets replaced by randomized counterpart moves
#define TX_RANDOM_ABILITIES             FALSE   // 0 normal abilities, 1 species abilites replaced by randomized counterpart abilities
#define TX_RANDOM_EVOLUTION             FALSE   // ?
#define TX_RANDOM_EVOLUTION_METHODS     FALSE   // ?
#define TX_RANDOM_TYPE_EFFECTIVENESS    FALSE   // 0 normal type chart, 1 randomized type chart
#define TX_RANDOM_ITEMS                 FALSE   // 0 normal items, 1 items replaced by randomized counterpart items (?)
#define TX_RANDOM_CHAOS_MODE            FALSE   // 0 no chaos mode, 1 certain randomizer settings become more chaotic (?)

#define TX_NUZLOCKE_NUZLOCKE_EASY       0 // if enabled, enforces permadeath but no other nuzlocke rules
#define TX_NUZLOCKE_NUZLOCKE            0 // if enabled, enforces all chosen nuzlocke rules
#define TX_NUZLOCKE_NUZLOCKE_HARDCORE   0 // CAREFULL!!!!! if enabled, enforces all chosen nuzlocke rules and deletes save file on TPK
#define TX_NUZLOCKE_SPECIES_CLAUSE      1 // if enabled, prevents previously caught species from being forced as your encounter for a location
#define TX_NUZLOCKE_SHINY_CLAUSE        1 // if enabled, removes any catch restrictions for shiny pokemon
#define TX_NUZLOCKE_NICKNAMING          1 // if enabled, forces player to nickname all pokemon
#define TX_NUZLOCKE_DELETION            0 // if enabled, pokemon that faint are instantly released rather than sent to the cemetery
#define TX_NUZLOCKE_RARE_CANDY          1 // if enabled at start of new game, Rare Candy Box can be found in player PC
#define TX_NUZLOCKE_MINI_MODE           0 // ?

#define TX_DIFFICULTY_PARTY_LIMIT       0 // default party limit of 6 reduced by set value
#define TX_DIFFICULTY_LEVEL_CAP         0 // 0 no level cap, 1 level cap based on next boss' highest level, 2 level cap based on next boss' lowest level
#define TX_DIFFICULTY_EXP_MULTIPLIER    0 // 0 x1.0, 1 x1.5, 2 x2.0, 3 x0.0
#define TX_DIFFICULTY_NO_ITEM_PLAYER    0 // if enabled, player cannot use items mid-battle (held items are not included)
#define TX_DIFFICULTY_NO_ITEM_TRAINER   0 // if enabled, enemy trainers cannot use items mid-battle (held items are not included)
#define TX_DIFFICULTY_MAX_PARTY_IVS     0 // 0 default IV behavior, 1 all IVs set to 31, 2 all IVs randomly set to 30 or 31 to allow variety of Hidden Power types
#define TX_DIFFICULTY_SCALING_IVS       0 // 0 default trainer IVs, 1 trainer IVs scaled by badge count, 2 all trainer IVs set to 31
#define TX_DIFFICULTY_NO_EVS            0 // if enabled, player's pokemon cannot gain EVs
#define TX_DIFFICULTY_SCALING_EVS       0 // 0 default trainers have no EVs, 1 trainer EVs scaled by badge count, 2 trainer EVs maxed
#define TX_DIFFICULTY_LESS_ESCAPES      0 // if enabled, running from battles becomes (harder? less likely? requires item?)
#define TX_DIFFICULTY_ESCAPE_ROPE_DIG   0 // if enabled, Dig and Escape Ropes cannot be used to escape dungeons
#define TX_DIFFICULTY_LIMIT_DIFFICULTY  0 // ?
#define TX_DIFFICULTY_HARD_EXP 0

#define TX_CHALLENGE_PKMN_CENTER            0 // if enabled, pokecenters will not provide healing services, and PCHEAL will be treated as enabled (?)
#define TX_CHALLENGE_PCHEAL                 0 // if enabled, depositing a pokemon in the PC will not heal it
#define TX_CHALLENGES_EXPENSIVE             0 // 0 default prices, 1 prices x5, 2 prices x10, 3 prices x50
#define TX_CHALLENGE_EVO_LIMIT              0 // 0 no evolution limits, 1 pokemon can only evolve into their second stage (or can only evolve once after being caught?), 2 pokemon cannot evolve
#define TX_CHALLENGE_TYPE_OFF               31 // default value of TX_CHALLENGE_TYPE which disables One Type challenge
#define TX_CHALLENGE_TYPE                   TX_CHALLENGE_TYPE_OFF // 31 = disabled, 0-8 and 10-18 represent valid types as per include/constants/pokemon.h
#define TX_CHALLENGE_BASE_STAT_EQUALIZER    0 // 0 default Base Stats, 1 Every Base Stat set to 100 for all species, 2 = 255, 3 = 500
#define TX_CHALLENGE_MIRROR                 0 // if enabled, player will have same party as enemy trainer in trainer battles 
#define TX_CHALLENGE_MIRROR_THIEF           0 // 0 player builds and keeps own party (for wild battles and such), 1 player keeps enemy party after trainer battles

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