#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "battle_transition.h"
#include "main.h"
#include "task.h"
#include "safari_zone.h"
#include "script.h"
#include "event_data.h"
#include "metatile_behavior.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "random.h"
#include "starter_choose.h"
#include "script_pokemon_util.h"
#include "palette.h"
#include "window.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "tv.h"
#include "trainer_see.h"
#include "field_message_box.h"
#include "sound.h"
#include "strings.h"
#include "trainer_hill.h"
#include "secret_base.h"
#include "string_util.h"
#include "overworld.h"
#include "field_weather.h"
#include "battle_tower.h"
#include "gym_leader_rematch.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "fldeff.h"
#include "fldeff_misc.h"
#include "field_control_avatar.h"
#include "mirage_tower.h"
#include "field_screen_effect.h"
#include "data.h"
#include "constants/battle_frontier.h"
#include "constants/battle_setup.h"
#include "constants/game_stat.h"
#include "constants/items.h"
#include "constants/songs.h"
#include "constants/map_types.h"
#include "constants/trainers.h"
#include "constants/trainer_hill.h"
#include "constants/weather.h"
#include "tx_randomizer_and_challenges.h"
#include "pokedex.h" //tx_randomizer_and_challenges
#include "constants/region_map_sections.h" //tx_randomizer_and_challenges
#include "debug.h"
#include "bug_contest.h"
#include "roamer.h"


enum {
    TRANSITION_TYPE_NORMAL,
    TRANSITION_TYPE_CAVE,
    TRANSITION_TYPE_FLASH,
    TRANSITION_TYPE_WATER,
};

enum {
    TRAINER_PARAM_LOAD_VAL_8BIT,
    TRAINER_PARAM_LOAD_VAL_16BIT,
    TRAINER_PARAM_LOAD_VAL_32BIT,
    TRAINER_PARAM_CLEAR_VAL_8BIT,
    TRAINER_PARAM_CLEAR_VAL_16BIT,
    TRAINER_PARAM_CLEAR_VAL_32BIT,
    TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR,
};

struct TrainerBattleParameter
{
    void *varPtr;
    u8 ptrType;
};

// this file's functions
static void DoBattlePikeWildBattle(void);
static void DoSafariBattle(void);
static void DoBugContestBattle(void);
static void DoStandardWildBattle(void);
static void CB2_EndWildBattle(void);
static void CB2_EndScriptedWildBattle(void);
static u8 GetWildBattleTransition(void);
static u8 GetTrainerBattleTransition(void);
static void TryUpdateGymLeaderRematchFromWild(void);
static void TryUpdateGymLeaderRematchFromTrainer(void);
static void CB2_GiveStarter(void);
static void CB2_StartFirstBattle(void);
static void CB2_EndFirstBattle(void);
static void CB2_EndTrainerBattle(void);
static bool32 IsPlayerDefeated(u32 battleOutcome);
static u16 GetRematchTrainerId(u16 trainerId);
static void RegisterTrainerInMatchCall(void);
static void HandleRematchVarsOnBattleEnd(void);
static const u8 *GetIntroSpeechOfApproachingTrainer(void);
static const u8 *GetTrainerCantBattleSpeech(void);

EWRAM_DATA static u16 sTrainerBattleMode = 0;
EWRAM_DATA u16 gTrainerBattleOpponent_A = 0;
EWRAM_DATA u16 gTrainerBattleOpponent_B = 0;
EWRAM_DATA u16 gPartnerTrainerId = 0;
EWRAM_DATA static u16 sTrainerObjectEventLocalId = 0;
EWRAM_DATA static u8 *sTrainerAIntroSpeech = NULL;
EWRAM_DATA static u8 *sTrainerBIntroSpeech = NULL;
EWRAM_DATA static u8 *sTrainerADefeatSpeech = NULL;
EWRAM_DATA static u8 *sTrainerBDefeatSpeech = NULL;
EWRAM_DATA static u8 *sTrainerVictorySpeech = NULL;
EWRAM_DATA static u8 *sTrainerCannotBattleSpeech = NULL;
EWRAM_DATA static u8 *sTrainerBattleEndScript = NULL;
EWRAM_DATA static u8 *sTrainerABattleScriptRetAddr = NULL;
EWRAM_DATA static u8 *sTrainerBBattleScriptRetAddr = NULL;
EWRAM_DATA static bool8 sShouldCheckTrainerBScript = FALSE;
EWRAM_DATA static u8 sNoOfPossibleTrainerRetScripts = 0;
//tx_difficulty_options
EWRAM_DATA u8 NuzlockeIsCaptureBlocked = FALSE;
EWRAM_DATA u8 NuzlockeIsSpeciesClauseActive = FALSE;
EWRAM_DATA u8 OneTypeChallengeCaptureBlocked = FALSE;

// The first transition is used if the enemy Pokémon are lower level than our Pokémon.
// Otherwise, the second transition is used.
static const u8 sBattleTransitionTable_Wild[][2] =
{
    [TRANSITION_TYPE_NORMAL] = {B_TRANSITION_SLICE,          B_TRANSITION_WHITE_BARS_FADE},
    [TRANSITION_TYPE_CAVE]   = {B_TRANSITION_CLOCKWISE_WIPE, B_TRANSITION_GRID_SQUARES},
    [TRANSITION_TYPE_FLASH]  = {B_TRANSITION_BLUR,           B_TRANSITION_GRID_SQUARES},
    [TRANSITION_TYPE_WATER]  = {B_TRANSITION_WAVE,           B_TRANSITION_RIPPLE},
};

static const u8 sBattleTransitionTable_Trainer[][2] =
{
    [TRANSITION_TYPE_NORMAL] = {B_TRANSITION_POKEBALLS_TRAIL, B_TRANSITION_ANGLED_WIPES},
    [TRANSITION_TYPE_CAVE]   = {B_TRANSITION_SHUFFLE,         B_TRANSITION_BIG_POKEBALL},
    [TRANSITION_TYPE_FLASH]  = {B_TRANSITION_BLUR,            B_TRANSITION_GRID_SQUARES},
    [TRANSITION_TYPE_WATER]  = {B_TRANSITION_SWIRL,           B_TRANSITION_RIPPLE},
};

// Battle Frontier (excluding Pyramid and Dome, which have their own tables below)
static const u8 sBattleTransitionTable_BattleFrontier[] =
{
    B_TRANSITION_FRONTIER_LOGO_WIGGLE,
    B_TRANSITION_FRONTIER_LOGO_WAVE,
    B_TRANSITION_FRONTIER_SQUARES,
    B_TRANSITION_FRONTIER_SQUARES_SCROLL,
    B_TRANSITION_FRONTIER_CIRCLES_MEET,
    B_TRANSITION_FRONTIER_CIRCLES_CROSS,
    B_TRANSITION_FRONTIER_CIRCLES_ASYMMETRIC_SPIRAL,
    B_TRANSITION_FRONTIER_CIRCLES_SYMMETRIC_SPIRAL,
    B_TRANSITION_FRONTIER_CIRCLES_MEET_IN_SEQ,
    B_TRANSITION_FRONTIER_CIRCLES_CROSS_IN_SEQ,
    B_TRANSITION_FRONTIER_CIRCLES_ASYMMETRIC_SPIRAL_IN_SEQ,
    B_TRANSITION_FRONTIER_CIRCLES_SYMMETRIC_SPIRAL_IN_SEQ
};

static const u8 sBattleTransitionTable_BattlePyramid[] =
{
    B_TRANSITION_FRONTIER_SQUARES,
    B_TRANSITION_FRONTIER_SQUARES_SCROLL,
    B_TRANSITION_FRONTIER_SQUARES_SPIRAL
};

static const u8 sBattleTransitionTable_BattleDome[] =
{
    B_TRANSITION_FRONTIER_LOGO_WIGGLE,
    B_TRANSITION_FRONTIER_SQUARES,
    B_TRANSITION_FRONTIER_SQUARES_SCROLL,
    B_TRANSITION_FRONTIER_SQUARES_SPIRAL
};

static const struct TrainerBattleParameter sOrdinaryBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sContinueScriptBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sDoubleBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sOrdinaryNoIntroBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sContinueScriptDoubleBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_A,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerAIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerADefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerABattleScriptRetAddr, TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sTrainerBOrdinaryBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_B,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerBIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBDefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBBattleScriptRetAddr, TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

static const struct TrainerBattleParameter sTrainerBContinueScriptBattleParams[] =
{
    {&sTrainerBattleMode,           TRAINER_PARAM_LOAD_VAL_8BIT},
    {&gTrainerBattleOpponent_B,     TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerObjectEventLocalId,   TRAINER_PARAM_LOAD_VAL_16BIT},
    {&sTrainerBIntroSpeech,         TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBDefeatSpeech,        TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerVictorySpeech,        TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerCannotBattleSpeech,   TRAINER_PARAM_CLEAR_VAL_32BIT},
    {&sTrainerBBattleScriptRetAddr, TRAINER_PARAM_LOAD_VAL_32BIT},
    {&sTrainerBattleEndScript,      TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR},
};

#define REMATCH(trainer1, trainer2, trainer3, trainer4, trainer5, map)  \
{                                                                       \
    .trainerIds = {trainer1, trainer2, trainer3, trainer4, trainer5},   \
    .mapGroup = MAP_GROUP(map),                                         \
    .mapNum = MAP_NUM(map),                                             \
}

const struct RematchTrainer gRematchTable[REMATCH_TABLE_ENTRIES] =
{
    [REMATCH_ROSE] = REMATCH(TRAINER_GRUNT_33, TRAINER_ROSE_2, TRAINER_ROSE_3, TRAINER_ROSE_4, TRAINER_ROSE_5, ROUTE118),
    [REMATCH_ANDRES] = REMATCH(TRAINER_BRIANA, TRAINER_BROOKE, TRAINER_BURT, TRAINER_CALVIN, TRAINER_CAMERON, ROUTE105),
    [REMATCH_DUSTY] = REMATCH(TRAINER_KRISE, TRAINER_KUNI, TRAINER_KYLE, TRAINER_LAO, TRAINER_LEA_AND_PIA, ROUTE111),
    [REMATCH_LOLA] = REMATCH(TRAINER_LOLA_1, TRAINER_LOLA_2, TRAINER_LOLA_3, TRAINER_LOLA_4, TRAINER_LOLA_5, ROUTE109),
    [REMATCH_RICKY] = REMATCH(TRAINER_RICKY_1, TRAINER_RICKY_2, TRAINER_RICKY_3, TRAINER_RICKY_4, TRAINER_RICKY_5, ROUTE109),
    [REMATCH_LILA_AND_ROY] = REMATCH(TRAINER_LILA_AND_ROY_1, TRAINER_LILA_AND_ROY_2, TRAINER_LILA_AND_ROY_3, TRAINER_LILA_AND_ROY_4, TRAINER_LILA_AND_ROY_5, ROUTE124),
    [REMATCH_CRISTIN] = REMATCH(TRAINER_HILLARY, TRAINER_HORTON, TRAINER_IAN, TRAINER_IRWIN, TRAINER_ISSAC, ROUTE121),
    [REMATCH_BROOKE] = REMATCH(TRAINER_EMMA, TRAINER_ERICK, TRAINER_ERIK, TRAINER_ERIN, TRAINER_ERNEST, ROUTE111),
    [REMATCH_WILTON] = REMATCH(TRAINER_WILTON_1, TRAINER_WILTON_2, TRAINER_WILTON_3, TRAINER_WILTON_4, TRAINER_WILTON_5, ROUTE111),
    [REMATCH_VALERIE] = REMATCH(TRAINER_VALERIE_1, TRAINER_VALERIE_2, TRAINER_VALERIE_3, TRAINER_VALERIE_4, TRAINER_VALERIE_5, MT_PYRE_6F),
    [REMATCH_CINDY] = REMATCH(TRAINER_GRUNT_18, TRAINER_GRUNT_20, TRAINER_GRUNT_21, TRAINER_GRUNT_22, TRAINER_GRUNT_23, ROUTE104),
    [REMATCH_THALIA] = REMATCH(TRAINER_THALIA_1, TRAINER_THALIA_2, TRAINER_THALIA_3, TRAINER_THALIA_4, TRAINER_THALIA_5, ABANDONED_SHIP_ROOMS_1F),
    [REMATCH_JESSICA] = REMATCH(TRAINER_ARIANA_1, TRAINER_ARIANA_2, TRAINER_JESSICA_3, TRAINER_JESSICA_4, TRAINER_JESSICA_5, ROUTE121),
    [REMATCH_WINSTON] = REMATCH(TRAINER_WINSTON_1, TRAINER_WINSTON_2, TRAINER_WINSTON_3, TRAINER_WINSTON_4, TRAINER_WINSTON_5, ROUTE104),
    [REMATCH_STEVE] = REMATCH(TRAINER_STEVE_1, TRAINER_STEVE_2, TRAINER_STEVE_3, TRAINER_STEVE_4, TRAINER_STEVE_5, ROUTE114),
    [REMATCH_TONY] = REMATCH(TRAINER_TONY_1, TRAINER_TONY_2, TRAINER_TONY_3, TRAINER_TONY_4, TRAINER_TONY_5, ROUTE107),
    [REMATCH_NOB] = REMATCH(TRAINER_NOB_1, TRAINER_NOB_2, TRAINER_NOB_3, TRAINER_NOB_4, TRAINER_NOB_5, ROUTE115),
    [REMATCH_KOJI] = REMATCH(TRAINER_KOJI_1, TRAINER_KOJI_2, TRAINER_KOJI_3, TRAINER_KOJI_4, TRAINER_KOJI_5, ROUTE127),
    [REMATCH_FERNANDO] = REMATCH(TRAINER_NORTON, TRAINER_OTIS, TRAINER_PARRY, TRAINER_PATON, TRAINER_PETER, ROUTE123),
    [REMATCH_DALTON] = REMATCH(TRAINER_JENN, TRAINER_JEREMY, TRAINER_JERRY, TRAINER_JESSICA, TRAINER_JILL, ROUTE118),
    [REMATCH_BERNIE] = REMATCH(TRAINER_DARYL, TRAINER_DAVE, TRAINER_DAWN, TRAINER_DENIS, TRAINER_DIANA, ROUTE114),
    [REMATCH_ETHAN] = REMATCH(TRAINER_NAOKO, TRAINER_NATHAN, TRAINER_NEAL, TRAINER_NICK, TRAINER_NICO, JAGGED_PASS),
    [REMATCH_JOHN_AND_JAY] = REMATCH(TRAINER_JOHN_AND_JAY_1, TRAINER_JOHN_AND_JAY_2, TRAINER_JOHN_AND_JAY_3, TRAINER_JOHN_AND_JAY_4, TRAINER_JOHN_AND_JAY_5, METEOR_FALLS_1F_2R),
    [REMATCH_JEFFREY] = REMATCH(TRAINER_RIVAL_TOTODILE_5, TRAINER_RIVAL_TOTODILE_6, TRAINER_RIVAL_TOTODILE_7, TRAINER_RED_1, TRAINER_RED_2, ROUTE120),
    [REMATCH_CAMERON] = REMATCH(TRAINER_GAVEN, TRAINER_GINA, TRAINER_GLENN, TRAINER_GORDON, TRAINER_GREGG, ROUTE123),
    [REMATCH_JACKI] = REMATCH(TRAINER_LANCE_1, TRAINER_LANCE_2, TRAINER_RIVAL_CHIKORITA_1, TRAINER_RIVAL_CHIKORITA_2, TRAINER_RIVAL_CHIKORITA_3, ROUTE123),
    [REMATCH_WALTER] = REMATCH(TRAINER_WALTER_1, TRAINER_WALTER_2, TRAINER_WALTER_3, TRAINER_WALTER_4, TRAINER_WALTER_5, ROUTE121),
    [REMATCH_KAREN] = REMATCH(TRAINER_KAREN_1, TRAINER_KAREN_2, TRAINER_KAREN_3, TRAINER_KAREN_4, TRAINER_KAREN_5, ROUTE116),
    [REMATCH_JERRY] = REMATCH(TRAINER_ARCHER_1, TRAINER_ARCHER_4, TRAINER_ARCHER_5, TRAINER_ARCHER_5, TRAINER_ARCHER_5, ROUTE116),
    [REMATCH_ANNA_AND_MEG] = REMATCH(TRAINER_ANNA_AND_MEG_1, TRAINER_ANNA_AND_MEG_2, TRAINER_ANNA_AND_MEG_3, TRAINER_ANNA_AND_MEG_4, TRAINER_ANNA_AND_MEG_5, ROUTE117),
    [REMATCH_ISABEL] = REMATCH(TRAINER_LTSURGE, TRAINER_ERIKA, TRAINER_SABRINA, TRAINER_JANINE, TRAINER_BLAINE, ROUTE110),
    [REMATCH_MIGUEL] = REMATCH(TRAINER_MIGUEL_1, TRAINER_MIGUEL_2, TRAINER_MIGUEL_3, TRAINER_MIGUEL_4, TRAINER_MIGUEL_5, ROUTE103),
    [REMATCH_TIMOTHY] = REMATCH(TRAINER_TIMOTHY_1, TRAINER_TIMOTHY_2, TRAINER_TIMOTHY_3, TRAINER_TIMOTHY_4, TRAINER_TIMOTHY_5, ROUTE115),
    [REMATCH_SHELBY] = REMATCH(TRAINER_SHELBY_1, TRAINER_SHELBY_2, TRAINER_SHELBY_3, TRAINER_SHELBY_4, TRAINER_SHELBY_5, MT_CHIMNEY),
    [REMATCH_CALVIN] = REMATCH(TRAINER_EUGENE, TRAINER_FIDEL, TRAINER_FRAN, TRAINER_FRITZ, TRAINER_GAKU, ROUTE102),
    [REMATCH_ELLIOT] = REMATCH(TRAINER_MASA, TRAINER_MATHEW, TRAINER_MEG_AND_PEG, TRAINER_MEGAN, TRAINER_MICHAEL, ROUTE106),
    [REMATCH_ISAIAH] = REMATCH(TRAINER_WILL_2, TRAINER_BRUNO_1, TRAINER_BRUNO_2, TRAINER_KAREN_1, TRAINER_KAREN_2, ROUTE128),
    [REMATCH_MARIA] = REMATCH(TRAINER_MARIA_1, TRAINER_MARIA_2, TRAINER_MARIA_3, TRAINER_MARIA_4, TRAINER_MARIA_5, ROUTE117),
    [REMATCH_ABIGAIL] = REMATCH(TRAINER_ABE, TRAINER_AL, TRAINER_ALFRED, TRAINER_ALLAN, TRAINER_ANDRE, ROUTE110),
    [REMATCH_DYLAN] = REMATCH(TRAINER_LEWIS, TRAINER_LI, TRAINER_LISA, TRAINER_LIZ, TRAINER_LLOYD, ROUTE117),
    [REMATCH_KATELYN] = REMATCH(TRAINER_KATELYN_1, TRAINER_KATELYN_2, TRAINER_KATELYN_3, TRAINER_KATELYN_4, TRAINER_KATELYN_5, ROUTE128),
    [REMATCH_BENJAMIN] = REMATCH(TRAINER_BENJAMIN_1, TRAINER_BENJAMIN_2, TRAINER_BENJAMIN_3, TRAINER_BENJAMIN_4, TRAINER_BENJAMIN_5, ROUTE110),
    [REMATCH_PABLO] = REMATCH(TRAINER_PABLO_1, TRAINER_PABLO_2, TRAINER_PABLO_3, TRAINER_PABLO_4, TRAINER_PABLO_5, ROUTE126),
    [REMATCH_NICOLAS] = REMATCH(TRAINER_NICOLAS_1, TRAINER_NICOLAS_2, TRAINER_NICOLAS_3, TRAINER_NICOLAS_4, TRAINER_NICOLAS_5, METEOR_FALLS_1F_2R),
    [REMATCH_ROBERT] = REMATCH(TRAINER_ROBERT_1, TRAINER_ROBERT_2, TRAINER_ROBERT_3, TRAINER_ROBERT_4, TRAINER_ROBERT_5, ROUTE120),
    [REMATCH_LAO] = REMATCH(TRAINER_LAO_1, TRAINER_LAO_2, TRAINER_LAO_3, TRAINER_LAO_4, TRAINER_LAO_5, ROUTE113),
    [REMATCH_CYNDY] = REMATCH(TRAINER_JAMIE, TRAINER_JAKE, TRAINER_JAMES, TRAINER_JASON, TRAINER_JAY, ROUTE115),
    [REMATCH_MADELINE] = REMATCH(TRAINER_MADELINE_1, TRAINER_MADELINE_2, TRAINER_MADELINE_3, TRAINER_MADELINE_4, TRAINER_MADELINE_5, ROUTE113),
    [REMATCH_JENNY] = REMATCH(TRAINER_PROTON_1, TRAINER_PROTON_2, TRAINER_ARCHER_5, TRAINER_PETREL_1, TRAINER_ARCHER, ROUTE124),
    [REMATCH_DIANA] = REMATCH(TRAINER_KAZU, TRAINER_KEITH, TRAINER_KELLY, TRAINER_KEN, TRAINER_KEANDRA, JAGGED_PASS),
    [REMATCH_AMY_AND_LIV] = REMATCH(TRAINER_AMY_AND_MAY, TRAINER_ANN_AND_ANNE, TRAINER_AMY_AND_LIV_4, TRAINER_AMY_AND_LIV_5, TRAINER_AMY_AND_LIV_6, ROUTE103),
    [REMATCH_ERNEST] = REMATCH(TRAINER_MIKE, TRAINER_MIKEY, TRAINER_MIKI, TRAINER_MILLER, TRAINER_MITCH, ROUTE125),
    [REMATCH_CORY] = REMATCH(TRAINER_GRUNT_29, TRAINER_HAL, TRAINER_HANK, TRAINER_HAROLD, TRAINER_HARRIS, ROUTE108),
    [REMATCH_EDWIN] = REMATCH(TRAINER_LOLA, TRAINER_LORI, TRAINER_MARGRET, TRAINER_MARKUS, TRAINER_MARTIN, ROUTE110),
    [REMATCH_LYDIA] = REMATCH(TRAINER_LYDIA_1, TRAINER_LYDIA_2, TRAINER_LYDIA_3, TRAINER_LYDIA_4, TRAINER_LYDIA_5, ROUTE117),
    [REMATCH_ISAAC] = REMATCH(TRAINER_CHUCK_1_3, TRAINER_CLAIR_1, TRAINER_CLAIR_2, TRAINER_BROCK, TRAINER_MISTY, ROUTE117),
    [REMATCH_GABRIELLE] = REMATCH(TRAINER_ROD, TRAINER_RON, TRAINER_ROSS, TRAINER_ROXANNE, TRAINER_ROY, MT_PYRE_3F),
    [REMATCH_CATHERINE] = REMATCH(TRAINER_GRUNT_3, TRAINER_GRUNT_4, TRAINER_GRUNT_5, TRAINER_GRUNT_6, TRAINER_GRUNT_7, ROUTE119),
    [REMATCH_JACKSON] = REMATCH(TRAINER_RIVAL_CHIKORITA_4, TRAINER_RIVAL_CHIKORITA_5, TRAINER_RIVAL_CHIKORITA_6, TRAINER_RIVAL_CHIKORITA_7, TRAINER_RIVAL_CYNDAQUIL_1, ROUTE119),
    [REMATCH_HALEY] = REMATCH(TRAINER_WHITNEY_1, TRAINER_WHITNEY_2, TRAINER_MORTY_1, TRAINER_MORTY_2, TRAINER_PRYCE_1, ROUTE104),
    [REMATCH_JAMES] = REMATCH(TRAINER_RIVAL_CYNDAQUIL_4, TRAINER_RIVAL_CYNDAQUIL_5, TRAINER_RIVAL_CYNDAQUIL_6, TRAINER_RIVAL_CYNDAQUIL_7, TRAINER_RIVAL_TOTODILE_1, PETALBURG_WOODS),
    [REMATCH_TRENT] = REMATCH(TRAINER_TRENT_1, TRAINER_TRENT_2, TRAINER_TRENT_3, TRAINER_TRENT_4, TRAINER_TRENT_5, ROUTE112),
    [REMATCH_SAWYER] = REMATCH(TRAINER_SAWYER_1, TRAINER_SAWYER_2, TRAINER_SAWYER_3, TRAINER_SAWYER_4, TRAINER_SAWYER_5, MT_CHIMNEY),
    [REMATCH_KIRA_AND_DAN] = REMATCH(TRAINER_KIRA_AND_DAN_1, TRAINER_KIRA_AND_DAN_2, TRAINER_KIRA_AND_DAN_3, TRAINER_KIRA_AND_DAN_4, TRAINER_KIRA_AND_DAN_5, ABANDONED_SHIP_ROOMS2_1F),
    [REMATCH_WALLY_VR] = REMATCH(TRAINER_WALLY_VR_2, TRAINER_WALLY_VR_3, TRAINER_WALLY_VR_4, TRAINER_WALLY_VR_5, TRAINER_WALLY_VR_5, VICTORY_ROAD_1F),
    [REMATCH_ROXANNE] = REMATCH(TRAINER_ROXANNE_1, TRAINER_ROXANNE_2, TRAINER_ROXANNE_3, TRAINER_ROXANNE_4, TRAINER_ROXANNE_5, RUSTBORO_CITY),
    [REMATCH_BRAWLY] = REMATCH(TRAINER_DICK, TRAINER_DIRK, TRAINER_DON, TRAINER_DORIS, TRAINER_EDNA, DEWFORD_TOWN),
    [REMATCH_WATTSON] = REMATCH(TRAINER_WATTSON_1, TRAINER_WATTSON_4, TRAINER_WATTSON_4, TRAINER_WATTSON_4, TRAINER_WATTSON_5, MAUVILLE_CITY),
    [REMATCH_FLANNERY] = REMATCH(TRAINER_PING, TRAINER_QUENTIN, TRAINER_QUINN, TRAINER_RACHAEL, TRAINER_RALPH, LAVARIDGE_TOWN),
    [REMATCH_NORMAN] = REMATCH(TRAINER_NORMAN_1, TRAINER_NORMAN_2, TRAINER_NORMAN_3, TRAINER_NORMAN_4, TRAINER_NORMAN_5, PETALBURG_CITY),
    [REMATCH_WINONA] = REMATCH(TRAINER_WINONA_1, TRAINER_WINONA_2, TRAINER_WINONA_3, TRAINER_WINONA_4, TRAINER_WINONA_5, FORTREE_CITY),
    [REMATCH_TATE_AND_LIZA] = REMATCH(TRAINER_TATE_AND_LIZA_1, TRAINER_TATE_AND_LIZA_2, TRAINER_TATE_AND_LIZA_3, TRAINER_TATE_AND_LIZA_4, TRAINER_TATE_AND_LIZA_5, MOSSDEEP_CITY),
    [REMATCH_JUAN] = REMATCH(TRAINER_JUAN_1, TRAINER_JUAN_2, TRAINER_JUAN_3, TRAINER_JUAN_4, TRAINER_JUAN_5, SOOTOPOLIS_CITY),
    [REMATCH_SIDNEY] = REMATCH(TRAINER_SIDNEY, TRAINER_SIDNEY, TRAINER_SIDNEY, TRAINER_SIDNEY, TRAINER_SIDNEY, EVER_GRANDE_CITY),
    [REMATCH_PHOEBE] = REMATCH(TRAINER_PHOEBE, TRAINER_PHOEBE, TRAINER_PHOEBE, TRAINER_PHOEBE, TRAINER_PHOEBE, EVER_GRANDE_CITY),
    [REMATCH_GLACIA] = REMATCH(TRAINER_GLACIA, TRAINER_GLACIA, TRAINER_GLACIA, TRAINER_GLACIA, TRAINER_GLACIA, EVER_GRANDE_CITY),
    [REMATCH_DRAKE] = REMATCH(TRAINER_KIP, TRAINER_KIP, TRAINER_KIP, TRAINER_KIP, TRAINER_KIP, EVER_GRANDE_CITY),
    [REMATCH_WALLACE] = REMATCH(TRAINER_WALLACE, TRAINER_WALLACE, TRAINER_WALLACE, TRAINER_WALLACE, TRAINER_WALLACE, EVER_GRANDE_CITY),
};

static const u16 sBadgeFlags[NUM_BADGES] =
{
    FLAG_BADGE01_GET, FLAG_BADGE02_GET, FLAG_BADGE03_GET, FLAG_BADGE04_GET,
    FLAG_BADGE05_GET, FLAG_BADGE06_GET, FLAG_BADGE07_GET, FLAG_BADGE08_GET,
};

#define tState data[0]
#define tTransition data[1]

static void Task_BattleStart(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        if (!FldEffPoison_IsActive()) // is poison not active?
        {
            BattleTransition_StartOnField(tTransition);
            ClearMirageTowerPulseBlendEffect();
            tState++; // go to case 1.
        }
        break;
    case 1:
        if (IsBattleTransitionDone() == TRUE)
        {
            CleanupOverworldWindowsAndTilemaps();
            SetMainCallback2(CB2_InitBattle);
            RestartWildEncounterImmunitySteps();
            ClearPoisonStepCounter();
            DestroyTask(taskId);
        }
        break;
    }
}

static void CreateBattleStartTask(u8 transition, u16 song)
{
    u8 taskId = CreateTask(Task_BattleStart, 1);

    gTasks[taskId].tTransition = transition;
    PlayMapChosenOrBattleBGM(song);
}

static void Task_BattleStart_Debug(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    switch (tState)
    {
    case 0:
        if (!FldEffPoison_IsActive()) // is poison not active?
        {
            BattleTransition_StartOnField(tTransition);
            ClearMirageTowerPulseBlendEffect();
            tState++; // go to case 1.
        }
        break;
    case 1:
        if (IsBattleTransitionDone() == TRUE)
        {
            CleanupOverworldWindowsAndTilemaps();
            SetMainCallback2(CB2_InitBattle);
            RestartWildEncounterImmunitySteps();
            ClearPoisonStepCounter();
            DestroyTask(taskId);
        }
        break;
    }
}

static void CreateBattleStartTask_Debug(u8 transition, u16 song)
{
    u8 taskId = CreateTask(Task_BattleStart_Debug, 1);

    gTasks[taskId].tTransition = transition;
    PlayMapChosenOrBattleBGM(song);
}

#undef tState
#undef tTransition

void BattleSetup_StartWildBattle(void)
{
    SetNuzlockeChecks(); //tx_randomizer_and_challenges
    if (GetSafariZoneFlag())
        DoSafariBattle();
    else if (GetBugContestFlag())
        DoBugContestBattle();
    else
        DoStandardWildBattle();
}

void BattleSetup_StartBattlePikeWildBattle(void)
{
    DoBattlePikeWildBattle();
}

static void DoStandardWildBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = 0;
    if (InBattlePyramid())
    {
        VarSet(VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0);
        gBattleTypeFlags |= BATTLE_TYPE_PYRAMID;
    }
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void DoStandardWildBattle_Debug(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = 0;
    if (InBattlePyramid())
    {
        VarSet(VAR_TEMP_E, 0);
        gBattleTypeFlags |= BATTLE_TYPE_PYRAMID;
    }
    CreateBattleStartTask_Debug(GetWildBattleTransition(), 0);
    //IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    //IncrementGameStat(GAME_STAT_WILD_BATTLES);
    //IncrementDailyWildBattles();
    //TryUpdateGymLeaderRematchFromWild();
}

void BattleSetup_StartRoamerBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_ROAMER;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

static void DoSafariBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndSafariBattle;
    gBattleTypeFlags = BATTLE_TYPE_SAFARI;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
}

static void DoBugContestBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndBugContestBattle;
    gBattleTypeFlags = 0;
    if (InBattlePyramid())
    {
        VarSet(VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0);
        gBattleTypeFlags |= BATTLE_TYPE_PYRAMID;
    }
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

static void DoBattlePikeWildBattle(void)
{
    LockPlayerFieldControls();
    FreezeObjectEvents();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_PIKE;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

static void DoTrainerBattle(void)
{
    CreateBattleStartTask(GetTrainerBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_TRAINER_BATTLES);
    TryUpdateGymLeaderRematchFromTrainer();
}

static void DoBattlePyramidTrainerHillBattle(void)
{
    if (InBattlePyramid())
        CreateBattleStartTask(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PYRAMID), 0);
    else
        CreateBattleStartTask(GetSpecialBattleTransition(B_TRANSITION_GROUP_TRAINER_HILL), 0);

    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_TRAINER_BATTLES);
    TryUpdateGymLeaderRematchFromTrainer();
}

// Initiates battle where Wally catches Ralts
void StartWallyTutorialBattle(void)
{
    CreateMaleMon(&gEnemyParty[0], SPECIES_SENTRET, 5);
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_ReturnToFieldContinueScriptPlayMapMusic;
    gBattleTypeFlags = BATTLE_TYPE_WALLY_TUTORIAL;
    CreateBattleStartTask(B_TRANSITION_SLICE, 0);
}

void BattleSetup_StartScriptedWildBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = 0;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void BattleSetup_StartLatiBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY;
    CreateBattleStartTask(GetWildBattleTransition(), 0);
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void BattleSetup_StartLegendaryBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY;

    switch (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL))
    {
    default:
    case SPECIES_GROUDON:
        gBattleTypeFlags |= BATTLE_TYPE_GROUDON;
        CreateBattleStartTask(B_TRANSITION_GROUDON, MUS_VS_KYOGRE_GROUDON);
        break;
    case SPECIES_KYOGRE:
        gBattleTypeFlags |= BATTLE_TYPE_KYOGRE;
        CreateBattleStartTask(B_TRANSITION_KYOGRE, MUS_VS_KYOGRE_GROUDON);
        break;
    case SPECIES_RAYQUAZA:
        gBattleTypeFlags |= BATTLE_TYPE_RAYQUAZA;
        CreateBattleStartTask(B_TRANSITION_RAYQUAZA, MUS_HG_VS_KYOGRE_GROUDON);
        break;
    case SPECIES_DEOXYS:
        CreateBattleStartTask(B_TRANSITION_BLUR, MUS_RG_VS_DEOXYS);
        break;
    case SPECIES_RAIKOU:
        CreateBattleStartTask(B_TRANSITION_BLACKHOLE, MUS_HG_VS_RAIKOU);
        break;
    case SPECIES_ENTEI:
        CreateBattleStartTask(B_TRANSITION_BLACKHOLE, MUS_HG_VS_ENTEI);
        break;
    case SPECIES_SUICUNE:
        CreateBattleStartTask(B_TRANSITION_BLACKHOLE, MUS_HG_VS_SUICUNE);
        break;
    case SPECIES_LUGIA:
        gBattleTypeFlags |= BATTLE_TYPE_KYOGRE;
        CreateBattleStartTask(B_TRANSITION_RECTANGULAR_SPIRAL, MUS_HG_VS_LUGIA);
        break;
    case SPECIES_HO_OH:
        gBattleTypeFlags |= BATTLE_TYPE_RAYQUAZA;
        CreateBattleStartTask(B_TRANSITION_RECTANGULAR_SPIRAL, MUS_HG_VS_HO_OH);
        break;
    case SPECIES_ARTICUNO:
    case SPECIES_ZAPDOS:
    case SPECIES_MOLTRES:
        CreateBattleStartTask(B_TRANSITION_BLUR, MUS_RG_VS_LEGEND);
        break;
    case SPECIES_REGIGIGAS:
        CreateBattleStartTask(B_TRANSITION_BLUR, MUS_DP_VS_LEGEND);
        break;
    case SPECIES_MEW:
        CreateBattleStartTask(B_TRANSITION_GRID_SQUARES, MUS_VS_MEW);
        break;
    case SPECIES_MEWTWO:
        CreateBattleStartTask(B_TRANSITION_GRID_SQUARES, MUS_RG_VS_MEWTWO);
        break;
    case SPECIES_CELEBI:
    case SPECIES_JIRACHI:
        CreateBattleStartTask(B_TRANSITION_GRID_SQUARES, MUS_DP_VS_UXIE_MESPRIT_AZELF);
        break;
    case SPECIES_LATIOS:
    case SPECIES_LATIAS:
        CreateBattleStartTask(B_TRANSITION_GRID_SQUARES, MUS_RG_VS_LEGEND);
        break;
    }

    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void StartGroudonKyogreBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY | BATTLE_TYPE_KYOGRE_GROUDON;

    if (gGameVersion == VERSION_RUBY)
        CreateBattleStartTask(B_TRANSITION_ANGLED_WIPES, MUS_VS_KYOGRE_GROUDON); // GROUDON
    else
        CreateBattleStartTask(B_TRANSITION_RIPPLE, MUS_VS_KYOGRE_GROUDON); // KYOGRE

    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

void StartRegiBattle(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY | BATTLE_TYPE_REGI;

    switch (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL))
    {
    case SPECIES_REGIROCK:
        CreateBattleStartTask(B_TRANSITION_REGIROCK, MUS_VS_REGI);
        break;
    case SPECIES_REGICE:
        CreateBattleStartTask(B_TRANSITION_REGICE, MUS_VS_REGI);
        break;
    case SPECIES_REGISTEEL:
        CreateBattleStartTask(B_TRANSITION_REGISTEEL, MUS_VS_REGI);
        break;
    case SPECIES_REGIELEKI:
        CreateBattleStartTask(B_TRANSITION_SHRED_SPLIT, MUS_PL_VS_REGI);
        break;
    case SPECIES_REGIDRAGO:
        CreateBattleStartTask(B_TRANSITION_SHRED_SPLIT, MUS_PL_VS_REGI);
        break;
    }

    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
    IncrementDailyWildBattles();
    TryUpdateGymLeaderRematchFromWild();
}

static void CB2_EndWildBattle(void)
{
    CpuFill16(0, (void *)(BG_PLTT), BG_PLTT_SIZE);
    ResetOamRange(0, 128);

    if (IsPlayerDefeated(gBattleOutcome) == TRUE && !InBattlePyramid() && !InBattlePike())
    {
        SetMainCallback2(CB2_WhiteOut);
    }
    else
    {      //if caught roamer, setflag caught
        if (gBattleOutcome == B_OUTCOME_CAUGHT){
            switch (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL))
            {
            case SPECIES_ENTEI:
                FlagSet(FLAG_CAUGHT_ENTEI);
                break;
            case SPECIES_RAIKOU:
                FlagSet(FLAG_CAUGHT_RAIKOU);
                break;
            }
        }

        //if won or beat roamer, if not already caught other roamer, create them
        if (gBattleOutcome == B_OUTCOME_CAUGHT || gBattleOutcome == B_OUTCOME_WON){
            switch (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL))
            {
            case SPECIES_ENTEI:
                if(!(FlagGet(FLAG_CAUGHT_RAIKOU)))
                {
                    gSpecialVar_0x8004 = 0;
                    InitRoamer();
                    break;
                }
            case SPECIES_RAIKOU:
                if(!(FlagGet(FLAG_CAUGHT_ENTEI)))
                {
                    gSpecialVar_0x8004 = 1;
                    InitRoamer();
                    break;
                }
            }
        }
        SetMainCallback2(CB2_ReturnToField);
        gFieldCallback = FieldCB_ReturnToFieldNoScriptCheckMusic;
    }
}

static void CB2_EndScriptedWildBattle(void)
{
    CpuFill16(0, (void *)(BG_PLTT), BG_PLTT_SIZE);
    ResetOamRange(0, 128);

    if (IsPlayerDefeated(gBattleOutcome) == TRUE)
    {
        if (InBattlePyramid())
            SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        else
            SetMainCallback2(CB2_WhiteOut);
    }
    else
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
}

u8 BattleSetup_GetTerrainId(void)
{
    #define IS_MAP(mapGroupId, mapNumId) \
    (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(mapGroupId) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(mapNumId))
    u16 tileBehavior;
    s16 x, y;

    PlayerGetDestCoords(&x, &y);
    tileBehavior = MapGridGetMetatileBehaviorAt(x, y);

    if (MetatileBehavior_IsTallGrass(tileBehavior))
    {
        if (
            IS_MAP(BLACKTHORN_CITY, BLACKTHORN_CITY) ||
            IS_MAP(CIANWOOD_CITY, CIANWOOD_CITY) ||
            IS_MAP(DRAGONS_DEN_CAVERN, DRAGONS_DEN_CAVERN) ||
            IS_MAP(LAKE_OF_RAGE, LAKE_OF_RAGE) ||
            IS_MAP(LAKE_OF_RAGE_LOW_TIDE, LAKE_OF_RAGE_LOW_TIDE) ||
            IS_MAP(MAHOGANYTOWN, MAHOGANYTOWN) ||
            IS_MAP(MT_MORTAR_2F, MT_MORTAR_2F) ||
            IS_MAP(MT_MORTAR_B1F, MT_MORTAR_B1F) ||
            IS_MAP(MT_SILVER_OUTSIDE, MT_SILVER_OUTSIDE) ||
            IS_MAP(MT_SILVER_MOUNTAIN_SIDE, MT_SILVER_MOUNTAIN_SIDE) ||
            IS_MAP(MT_SILVER_2F, MT_SILVER_2F) ||
            IS_MAP(MT_SILVER_SNOW, MT_SILVER_SNOW) ||
            IS_MAP(MT_SILVER_3F, MT_SILVER_3F) ||
            IS_MAP(ROUTE28, ROUTE28) ||
            IS_MAP(ROUTE41, ROUTE41) ||
            IS_MAP(ROUTE42, ROUTE42) ||
            IS_MAP(ROUTE43, ROUTE43) ||
            IS_MAP(ROUTE44, ROUTE44) ||
            IS_MAP(ROUTE45, ROUTE45) ||
            IS_MAP(ROUTE46, ROUTE46) ||
            IS_MAP(ROUTE47, ROUTE47) ||
            IS_MAP(ROUTE48, ROUTE48) ||
            IS_MAP(RUINS_OF_ALPH_OUTSIDE, RUINS_OF_ALPH_OUTSIDE) ||
            IS_MAP(SAFARI_ZONE1, SAFARI_ZONE1) ||
            IS_MAP(SAFARI_ZONE2, SAFARI_ZONE2) ||
            IS_MAP(SAFARI_ZONE3, SAFARI_ZONE3) ||
            IS_MAP(SAFARI_ZONE_ENTERANCE, SAFARI_ZONE_ENTERANCE) ||
            IS_MAP(SAFARI_ZONE_GATE, SAFARI_ZONE_GATE) ||
            IS_MAP(SAFARI_ZONE_LOW_LEFT, SAFARI_ZONE_LOW_LEFT) ||
            IS_MAP(SAFARI_ZONE_LOW_MID, SAFARI_ZONE_LOW_MID) ||
            IS_MAP(SAFARI_ZONE_LOW_RIGHT, SAFARI_ZONE_LOW_RIGHT) ||
            IS_MAP(SAFARI_ZONE_TOP_LEFT, SAFARI_ZONE_TOP_LEFT) ||
            IS_MAP(SAFARI_ZONE_TOP_MID, SAFARI_ZONE_TOP_MID) ||
            IS_MAP(SAFARI_ZONE_TOP_RIGHT, SAFARI_ZONE_TOP_RIGHT) ||
            IS_MAP(WHIRL_ISLANDS_1F, WHIRL_ISLANDS_1F) ||
            IS_MAP(MT_SILVER_SNOW, MT_SILVER_SNOW) ||
            IS_MAP(ROUTE3, ROUTE3) ||
            IS_MAP(ROUTE4, ROUTE4) ||
            IS_MAP(ROUTE9, ROUTE9) ||
            IS_MAP(ROUTE10, ROUTE10))
        {
            return BATTLE_TERRAIN_MOUNTAIN;
        }
        if (IS_MAP(FUCHSIA_CITY_SAFARI_ZONE_BEACH, FUCHSIA_CITY_SAFARI_ZONE_BEACH) || IS_MAP(CINNABAR_ISLAND, CINNABAR_ISLAND))
            return BATTLE_TERRAIN_SAND;
    return BATTLE_TERRAIN_GRASS;
    }
    if (MetatileBehavior_IsLongGrass(tileBehavior)) {
        if(IS_MAP(FUCHSIA_CITY_SAFARI_ZONE_MOUNTAIN, FUCHSIA_CITY_SAFARI_ZONE_MOUNTAIN)) {
            return BATTLE_TERRAIN_MOUNTAIN;
        }
        return BATTLE_TERRAIN_LONG_GRASS;
    }
    if(MetatileBehavior_IsDeepSand(tileBehavior))
        return BATTLE_TERRAIN_MOUNTAIN;
    if (MetatileBehavior_IsSand(tileBehavior))
        return BATTLE_TERRAIN_SAND;

    switch (gMapHeader.mapType)
    {
    case MAP_TYPE_TOWN:
    case MAP_TYPE_CITY:
    case MAP_TYPE_ROUTE:
        break;
    case MAP_TYPE_UNDERGROUND:
        if (MetatileBehavior_IsIndoorEncounter(tileBehavior))
            return BATTLE_TERRAIN_BUILDING;
       /* if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
            return BATTLE_TERRAIN_WATER;
        {*/
        if (
            IS_MAP(CERULEAN_CAVE1, CERULEAN_CAVE1) ||
            IS_MAP(CERULEAN_CAVE2, CERULEAN_CAVE2) ||
            IS_MAP(CERULEAN_CAVE3, CERULEAN_CAVE3) ||
            IS_MAP(WHIRL_ISLANDS_1F, WHIRL_ISLANDS_1F) ||
            IS_MAP(WHIRL_ISLANDS_B1F, WHIRL_ISLANDS_B1F) ||
            IS_MAP(WHIRL_ISLANDS_B2F, WHIRL_ISLANDS_B2F) ||
            IS_MAP(SEAFOAM_ISLANDS_1F, SEAFOAM_ISLANDS_1F) ||
            IS_MAP(SEAFOAM_ISLANDS_GYM, SEAFOAM_ISLANDS_GYM) ||
            IS_MAP(SEAFOAM_ISLANDS_B1F, SEAFOAM_ISLANDS_B1F) ||
            IS_MAP(MT_SILVER_1F_ITEM_ROOM, MT_SILVER_1F_ITEM_ROOM) ||
            IS_MAP(MT_SILVER_1F_WATERFALL_ROOM, MT_SILVER_1F_WATERFALL_ROOM) ||
            IS_MAP(MT_SILVER_1F_MOLTRES_ROOM, MT_SILVER_1F_MOLTRES_ROOM) ||
            IS_MAP(MT_SILVER_2F, MT_SILVER_2F) ||
            IS_MAP(MT_SILVER_3F, MT_SILVER_3F) ||
            IS_MAP(ICE_PATH_1F, ICE_PATH_1F) ||
            IS_MAP(ICE_PATH_B1F, ICE_PATH_B1F) ||
            IS_MAP(ICE_PATH_B2F, ICE_PATH_B2F) ||
            IS_MAP(ICE_PATH_B3F, ICE_PATH_B3F) ||
            IS_MAP(ICE_PATH_B4F, ICE_PATH_B4F) ||
            IS_MAP(MT_MORTAR_1F_SOUTH, MT_MORTAR_1F_SOUTH) ||
            IS_MAP(MT_MORTAR_1F_NORTH, MT_MORTAR_1F_NORTH) ||
            IS_MAP(MT_MORTAR_2F, MT_MORTAR_2F) ||
            IS_MAP(MT_MORTAR_B1F, MT_MORTAR_B1F) ||
            IS_MAP(DRAGONS_DEN_ENTRANCE, DRAGONS_DEN_ENTRANCE) ||
            IS_MAP(DRAGONS_DEN_CAVERN, DRAGONS_DEN_CAVERN) ||
            IS_MAP(ROCK_TUNNEL_B1F, ROCK_TUNNEL_B1F) ||
            IS_MAP(ROCK_TUNNEL_1F, ROCK_TUNNEL_1F) ||
            IS_MAP(SLOWPOKE_WELL_B1F, SLOWPOKE_WELL_B1F) ||
            IS_MAP(SLOWPOKE_WELL_B2F, SLOWPOKE_WELL_B2F) ||
            IS_MAP(SAFARI_ZONE_LOW_RIGHT, SAFARI_ZONE_LOW_RIGHT) ||
            IS_MAP(FUCHSIA_CITY_SAFARI_ZONE_CAVE, FUCHSIA_CITY_SAFARI_ZONE_CAVE) ||
            IS_MAP(RUINS_OF_ALPH_B1F, RUINS_OF_ALPH_B1F))
        {
            return BATTLE_TERRAIN_GRAY_CAVE;
        }
    return BATTLE_TERRAIN_CAVE;
    
    case MAP_TYPE_INDOOR:
            if (
            IS_MAP(ROCKET_HIDEOUT_B1F, ROCKET_HIDEOUT_B1F) ||
            IS_MAP(ROCKET_HIDEOUT_B2F, ROCKET_HIDEOUT_B2F) ||
            IS_MAP(ROCKET_HIDEOUT_B3F, ROCKET_HIDEOUT_B3F) ||
            IS_MAP(GOLDENROD_CITY_UNDERGROUND_ENTRANCE, GOLDENROD_CITY_UNDERGROUND_ENTRANCE) ||
            IS_MAP(GOLDENROD_CITY_UNDERGROUND_SWITCHES, GOLDENROD_CITY_UNDERGROUND_SWITCHES) ||
            IS_MAP(GOLDENROD_CITY_UNDERGROUND_TUNNEL, GOLDENROD_CITY_UNDERGROUND_TUNNEL) ||
            IS_MAP(GOLDENROD_CITY_UNDERGROUND_STORAGE, GOLDENROD_CITY_UNDERGROUND_STORAGE) ||
            IS_MAP(GOLDENROD_CITY_RADIO_TOWER_1F, GOLDENROD_CITY_RADIO_TOWER_1F) ||
            IS_MAP(GOLDENROD_CITY_RADIO_TOWER_2F, GOLDENROD_CITY_RADIO_TOWER_2F) ||
            IS_MAP(GOLDENROD_CITY_RADIO_TOWER_3F, GOLDENROD_CITY_RADIO_TOWER_3F) ||
            IS_MAP(GOLDENROD_CITY_RADIO_TOWER_4F, GOLDENROD_CITY_RADIO_TOWER_4F) ||
            IS_MAP(GOLDENROD_CITY_RADIO_TOWER_5F, GOLDENROD_CITY_RADIO_TOWER_5F) ||
            IS_MAP(VIOLET_CITY_GYM, VIOLET_CITY_GYM) ||
            IS_MAP(ECRUTEAK_CITY_GYM, ECRUTEAK_CITY_GYM) ||
            IS_MAP(CIANWOOD_GYM, CIANWOOD_GYM) ||
            IS_MAP(OLIVINE_CITY_LIGHTHOUSE, OLIVINE_CITY_LIGHTHOUSE) ||
            IS_MAP(OLIVINE_CITY_GYM, OLIVINE_CITY_GYM) ||
            IS_MAP(MAHOGANY_TOWN_GYM, MAHOGANY_TOWN_GYM) ||
            IS_MAP(BLACKTHORN_CITY_GYM, BLACKTHORN_CITY_GYM) ||
            IS_MAP(VIRIDIAN_CITY_GYM, VIRIDIAN_CITY_GYM) ||
            IS_MAP(CERULEAN_CITY_GYM, CERULEAN_CITY_GYM) ||
            IS_MAP(SAFFRON_CITY_GYM, SAFFRON_CITY_GYM))
        {
            return BATTLE_TERRAIN_BLUE_BUILDING;
        }
    case MAP_TYPE_SECRET_BASE:
        return BATTLE_TERRAIN_BUILDING;
        if (
                IS_MAP(BLACKTHORN_CITY_GYM, BLACKTHORN_CITY_GYM))
            {
                return BATTLE_TERRAIN_CAVE;
            }
    case MAP_TYPE_UNDERWATER:
        return BATTLE_TERRAIN_GRAY_CAVE;
    case MAP_TYPE_OCEAN_ROUTE:
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
            return BATTLE_TERRAIN_WATER;
        return BATTLE_TERRAIN_PLAIN;
    }
    if (MetatileBehavior_IsDeepOrOceanWater(tileBehavior))
        return BATTLE_TERRAIN_WATER;
    if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
        return BATTLE_TERRAIN_POND;
    if (MetatileBehavior_IsMountain(tileBehavior))
        return BATTLE_TERRAIN_MOUNTAIN;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
    {
        // Is BRIDGE_TYPE_POND_*?
        if (MetatileBehavior_GetBridgeType(tileBehavior) != BRIDGE_TYPE_OCEAN)
            return BATTLE_TERRAIN_POND;

        if (MetatileBehavior_IsBridgeOverWater(tileBehavior) == TRUE)
            return BATTLE_TERRAIN_WATER;
    }
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(ROUTE113) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE113))
        return BATTLE_TERRAIN_SAND;
    if (GetSavedWeather() == WEATHER_SANDSTORM)
        return BATTLE_TERRAIN_SAND;


    if (
        IS_MAP(BLACKTHORN_CITY, BLACKTHORN_CITY) ||
        IS_MAP(CIANWOOD_CITY, CIANWOOD_CITY) ||
        IS_MAP(DRAGONS_DEN_CAVERN, DRAGONS_DEN_CAVERN) ||
        IS_MAP(LAKE_OF_RAGE, LAKE_OF_RAGE) ||
        IS_MAP(LAKE_OF_RAGE_LOW_TIDE, LAKE_OF_RAGE_LOW_TIDE) ||
        IS_MAP(MAHOGANYTOWN, MAHOGANYTOWN) ||
        IS_MAP(MT_MORTAR_2F, MT_MORTAR_2F) ||
        IS_MAP(MT_MORTAR_B1F, MT_MORTAR_B1F) ||
        IS_MAP(MT_SILVER_OUTSIDE, MT_SILVER_OUTSIDE) ||
        IS_MAP(MT_SILVER_MOUNTAIN_SIDE, MT_SILVER_MOUNTAIN_SIDE) ||
        IS_MAP(MT_SILVER_2F, MT_SILVER_2F) ||
        IS_MAP(MT_SILVER_3F, MT_SILVER_3F) ||
        IS_MAP(ROUTE28, ROUTE28) ||
        IS_MAP(ROUTE41, ROUTE41) ||
        IS_MAP(ROUTE42, ROUTE42) ||
        IS_MAP(ROUTE43, ROUTE43) ||
        IS_MAP(ROUTE44, ROUTE44) ||
        IS_MAP(ROUTE45, ROUTE45) ||
        IS_MAP(ROUTE46, ROUTE46) ||
        IS_MAP(ROUTE47, ROUTE47) ||
        IS_MAP(ROUTE48, ROUTE48) ||
        IS_MAP(RUINS_OF_ALPH_OUTSIDE, RUINS_OF_ALPH_OUTSIDE) ||
        IS_MAP(SAFARI_ZONE1, SAFARI_ZONE1) ||
        IS_MAP(SAFARI_ZONE2, SAFARI_ZONE2) ||
        IS_MAP(SAFARI_ZONE3, SAFARI_ZONE3) ||
        IS_MAP(SAFARI_ZONE_ENTERANCE, SAFARI_ZONE_ENTERANCE) ||
        IS_MAP(SAFARI_ZONE_GATE, SAFARI_ZONE_GATE) ||
        IS_MAP(SAFARI_ZONE_LOW_LEFT, SAFARI_ZONE_LOW_LEFT) ||
        IS_MAP(SAFARI_ZONE_LOW_MID, SAFARI_ZONE_LOW_MID) ||
        IS_MAP(SAFARI_ZONE_LOW_RIGHT, SAFARI_ZONE_LOW_RIGHT) ||
        IS_MAP(SAFARI_ZONE_TOP_LEFT, SAFARI_ZONE_TOP_LEFT) ||
        IS_MAP(SAFARI_ZONE_TOP_MID, SAFARI_ZONE_TOP_MID) ||
        IS_MAP(SAFARI_ZONE_TOP_RIGHT, SAFARI_ZONE_TOP_RIGHT) ||
        IS_MAP(WHIRL_ISLANDS_1F, WHIRL_ISLANDS_1F) ||
        IS_MAP(ROUTE3, ROUTE3) ||
        IS_MAP(ROUTE4, ROUTE4) ||
        IS_MAP(ROUTE9, ROUTE9) ||
        IS_MAP(ROUTE10, ROUTE10))
    {
        return BATTLE_TERRAIN_MOUNTAIN;
    }
    if (
            IS_MAP(CERULEAN_CAVE1, CERULEAN_CAVE1) ||
            IS_MAP(CERULEAN_CAVE2, CERULEAN_CAVE2) ||
            IS_MAP(CERULEAN_CAVE3, CERULEAN_CAVE3) ||
            IS_MAP(WHIRL_ISLANDS_1F, WHIRL_ISLANDS_1F) ||
            IS_MAP(WHIRL_ISLANDS_B1F, WHIRL_ISLANDS_B1F) ||
            IS_MAP(WHIRL_ISLANDS_B2F, WHIRL_ISLANDS_B2F) ||
            IS_MAP(SEAFOAM_ISLANDS_1F, SEAFOAM_ISLANDS_1F) ||
            IS_MAP(SEAFOAM_ISLANDS_GYM, SEAFOAM_ISLANDS_GYM) ||
            IS_MAP(SEAFOAM_ISLANDS_B1F, SEAFOAM_ISLANDS_B1F) ||
            IS_MAP(MT_SILVER_1F_ITEM_ROOM, MT_SILVER_1F_ITEM_ROOM) ||
            IS_MAP(MT_SILVER_1F_WATERFALL_ROOM, MT_SILVER_1F_WATERFALL_ROOM) ||
            IS_MAP(MT_SILVER_1F_MOLTRES_ROOM, MT_SILVER_1F_MOLTRES_ROOM) ||
            IS_MAP(MT_SILVER_2F, MT_SILVER_2F) ||
            IS_MAP(MT_SILVER_3F, MT_SILVER_3F) ||
            IS_MAP(ICE_PATH_1F, ICE_PATH_1F) ||
            IS_MAP(ICE_PATH_B1F, ICE_PATH_B1F) ||
            IS_MAP(ICE_PATH_B2F, ICE_PATH_B2F) ||
            IS_MAP(ICE_PATH_B3F, ICE_PATH_B3F) ||
            IS_MAP(ICE_PATH_B4F, ICE_PATH_B4F) ||
            IS_MAP(MT_MORTAR_1F_SOUTH, MT_MORTAR_1F_SOUTH) ||
            IS_MAP(MT_MORTAR_1F_NORTH, MT_MORTAR_1F_NORTH) ||
            IS_MAP(MT_MORTAR_2F, MT_MORTAR_2F) ||
            IS_MAP(MT_MORTAR_B1F, MT_MORTAR_B1F) ||
            IS_MAP(DRAGONS_DEN_ENTRANCE, DRAGONS_DEN_ENTRANCE) ||
            IS_MAP(DRAGONS_DEN_CAVERN, DRAGONS_DEN_CAVERN) ||
            IS_MAP(ROCK_TUNNEL_B1F, ROCK_TUNNEL_B1F) ||
            IS_MAP(ROCK_TUNNEL_1F, ROCK_TUNNEL_1F) ||
            IS_MAP(SLOWPOKE_WELL_B1F, SLOWPOKE_WELL_B1F) ||
            IS_MAP(SLOWPOKE_WELL_B2F, SLOWPOKE_WELL_B2F) ||
            IS_MAP(SAFARI_ZONE_LOW_RIGHT, SAFARI_ZONE_LOW_RIGHT) ||
            IS_MAP(FUCHSIA_CITY_SAFARI_ZONE_CAVE, FUCHSIA_CITY_SAFARI_ZONE_CAVE))
        {
            return BATTLE_TERRAIN_GRAY_CAVE;
        }

    return BATTLE_TERRAIN_GRASS;
}

static u8 GetBattleTransitionTypeByMap(void)
{
    u16 tileBehavior;
    s16 x, y;

    PlayerGetDestCoords(&x, &y);
    tileBehavior = MapGridGetMetatileBehaviorAt(x, y);

    if (GetFlashLevel())
        return TRANSITION_TYPE_FLASH;

    if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior))
        return TRANSITION_TYPE_WATER;

    switch (gMapHeader.mapType)
    {
    case MAP_TYPE_UNDERGROUND:
        return TRANSITION_TYPE_CAVE;
    case MAP_TYPE_UNDERWATER:
        return TRANSITION_TYPE_WATER;
    default:
        return TRANSITION_TYPE_NORMAL;
    }
}

static u16 GetSumOfPlayerPartyLevel(u8 numMons)
{
    u8 sum = 0;
    int i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        u32 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);

        if (species != SPECIES_EGG && species != SPECIES_NONE && GetMonData(&gPlayerParty[i], MON_DATA_HP) != 0)
        {
            sum += GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
            if (--numMons == 0)
                break;
        }
    }
    return sum;
}

static u8 GetSumOfEnemyPartyLevel(u16 opponentId, u8 numMons)
{
    u8 i;
    u8 sum;
    u32 count = numMons;

    if (gTrainers[opponentId].partySize < count)
        count = gTrainers[opponentId].partySize;

    sum = 0;

    switch (gTrainers[opponentId].partyFlags)
    {
    case 0:
        {
            const struct TrainerMonNoItemDefaultMoves *party;
            party = gTrainers[opponentId].party.NoItemDefaultMoves;
            for (i = 0; i < count; i++)
                //sum += party[i].lvl;
                sum += GetScaledLevel(party[i].lvl); //difficulty
        }
        break;
    case F_TRAINER_PARTY_CUSTOM_MOVESET:
        {
            const struct TrainerMonNoItemCustomMoves *party;
            party = gTrainers[opponentId].party.NoItemCustomMoves;
            for (i = 0; i < count; i++)
                //sum += party[i].lvl;
                sum += GetScaledLevel(party[i].lvl); //difficulty
        }
        break;
    case F_TRAINER_PARTY_HELD_ITEM:
        {
            const struct TrainerMonItemDefaultMoves *party;
            party = gTrainers[opponentId].party.ItemDefaultMoves;
            for (i = 0; i < count; i++)
                //sum += party[i].lvl;
                sum += GetScaledLevel(party[i].lvl); //difficulty
        }
        break;
    case F_TRAINER_PARTY_CUSTOM_MOVESET | F_TRAINER_PARTY_HELD_ITEM:
        {
            const struct TrainerMonItemCustomMoves *party;
            party = gTrainers[opponentId].party.ItemCustomMoves;
            for (i = 0; i < count; i++)
                //sum += party[i].lvl;
                sum += GetScaledLevel(party[i].lvl); //difficulty
        }
        break;
    }

    return sum;
}

u8 GetScaledLevel(u8 lvl)
{
    u8 badgeCount = 0;
    u8 levelScaling = 0;
    u32 i;
    for (i = FLAG_BADGE01_GET; i < FLAG_BADGE01_GET + NUM_BADGES; i++)
    {
        if (FlagGet(i))
            badgeCount++;
    }

    if (FlagGet(FLAG_IS_CHAMPION))
        levelScaling = 10;
    else if (badgeCount >= 6)
        levelScaling = 6;
    else if (badgeCount >= 3)
        levelScaling = 3;
    else if (badgeCount >= 1)
        levelScaling = 2;
    else
        levelScaling = 1;

    if (gSaveBlock2Ptr->optionsDifficulty == 2)
        lvl += levelScaling;
    else if (gSaveBlock2Ptr->optionsDifficulty == 0)
        lvl -= levelScaling;

    if (lvl > 100)
        lvl = 100;
    if (lvl < 1)
        lvl = 1;

    if (!FlagGet(FLAG_IS_CHAMPION))
    {
        if ((IsTrainerReadyForRematch() == TRUE) || (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_INTERVIEWER) && (gSaveBlock2Ptr->optionsDifficulty == 2)) 
        //hardmode rematches level cap
        {
            if ((lvl >= 36) && (badgeCount == 5))
                lvl = 33;
            else if ((lvl >= 48) && (badgeCount == 6))
                lvl = 43;
            else if ((lvl >= 52) && (badgeCount == 7))
                lvl = 47;
            else if ((lvl >= 64) && (badgeCount == 8))
                lvl = 57;
        }
        else if ((IsTrainerReadyForRematch() == TRUE) || (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_INTERVIEWER) && (gSaveBlock2Ptr->optionsDifficulty == 1)) 
        //normal mode rematch level cap
        {
            if ((lvl >= 33) && (badgeCount == 5))
                lvl = 30;
            else if ((lvl >= 42) && (badgeCount == 6))
                lvl = 37;
            else if ((lvl >= 46) && (badgeCount == 7))
                lvl = 41;
            else if ((lvl >= 58) && (badgeCount == 8))
                lvl = 53;
        }
        else if ((IsTrainerReadyForRematch() == TRUE) || (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_INTERVIEWER) && (gSaveBlock2Ptr->optionsDifficulty == 0)) 
        //easy mode rematch level cap
        {
            if ((lvl >= 30) && (badgeCount == 5))
                lvl = 30;
            else if ((lvl >= 36) && (badgeCount == 6))
                lvl = 36;
            else if ((lvl >= 40) && (badgeCount == 7))
                lvl = 40;
            else if ((lvl >= 52) && (badgeCount == 8))
                lvl = 52;
        }
    }
    return lvl;
}

static u8 GetWildBattleTransition(void)
{
    u8 transitionType = GetBattleTransitionTypeByMap();
    u8 enemyLevel = GetMonData(&gEnemyParty[0], MON_DATA_LEVEL);
    u8 playerLevel = GetSumOfPlayerPartyLevel(1);

    if (enemyLevel < playerLevel)
    {
        if (InBattlePyramid())
            return B_TRANSITION_BLUR;
        else
            return sBattleTransitionTable_Wild[transitionType][0];
    }
    else
    {
        if (InBattlePyramid())
            return B_TRANSITION_GRID_SQUARES;
        else
            return sBattleTransitionTable_Wild[transitionType][1];
    }
}

static u8 GetTrainerBattleTransition(void)
{
    u8 minPartyCount;
    u8 transitionType;
    u8 enemyLevel;
    u8 playerLevel;

    if (gTrainerBattleOpponent_A == TRAINER_SECRET_BASE)
        return B_TRANSITION_CHAMPION;

    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_ELITE_FOUR)
    {
        if (gTrainerBattleOpponent_A == TRAINER_WILL_1)
            return B_TRANSITION_SIDNEY;
        if (gTrainerBattleOpponent_A == TRAINER_KOGA_1)
            return B_TRANSITION_PHOEBE;
        if (gTrainerBattleOpponent_A == TRAINER_BRUNO_1)
            return B_TRANSITION_GLACIA;
        if (gTrainerBattleOpponent_A == TRAINER_KAREN_1)
            return B_TRANSITION_DRAKE;
        if (gTrainerBattleOpponent_A == TRAINER_WILL_2)
            return B_TRANSITION_SIDNEY;
        if (gTrainerBattleOpponent_A == TRAINER_KOGA_2)
            return B_TRANSITION_PHOEBE;
        if (gTrainerBattleOpponent_A == TRAINER_BRUNO_2)
            return B_TRANSITION_GLACIA;
        if (gTrainerBattleOpponent_A == TRAINER_KAREN_2)
            return B_TRANSITION_DRAKE;
        return B_TRANSITION_CHAMPION;
    }

    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_LEADER)
    {
        if(gTrainerBattleOpponent_A == TRAINER_FALKNER_1)
            return B_TRANSITION_FALKNER;
        if(gTrainerBattleOpponent_A == TRAINER_BUGSY_1)
            return B_TRANSITION_BUGSY;
        if(gTrainerBattleOpponent_A == TRAINER_WHITNEY_1)
            return B_TRANSITION_WHITNEY;
        if(gTrainerBattleOpponent_A == TRAINER_MORTY_1)
            return B_TRANSITION_MORTY;
        if(gTrainerBattleOpponent_A == TRAINER_CHUCK_1)
            return B_TRANSITION_CHUCK;
        if(gTrainerBattleOpponent_A == TRAINER_CHUCK_1_2)
            return B_TRANSITION_CHUCK;
        if(gTrainerBattleOpponent_A == TRAINER_CHUCK_1_3)
            return B_TRANSITION_CHUCK;
        if(gTrainerBattleOpponent_A == TRAINER_JASMINE_1)
            return B_TRANSITION_JASMINE;
        if(gTrainerBattleOpponent_A == TRAINER_JASMINE_1_2)
            return B_TRANSITION_JASMINE;
        if(gTrainerBattleOpponent_A == TRAINER_JASMINE_1_3)
            return B_TRANSITION_JASMINE;
        if(gTrainerBattleOpponent_A == TRAINER_PRYCE_1)
            return B_TRANSITION_PRYCE;
        if(gTrainerBattleOpponent_A == TRAINER_PRYCE_1_2)
            return B_TRANSITION_PRYCE;
        if(gTrainerBattleOpponent_A == TRAINER_PRYCE_1_3)
            return B_TRANSITION_PRYCE;
        if(gTrainerBattleOpponent_A == TRAINER_CLAIR_1)
            return B_TRANSITION_CLAIR;
        if(gTrainerBattleOpponent_A == TRAINER_FALKNER_2)
            return B_TRANSITION_FALKNER;
        if(gTrainerBattleOpponent_A == TRAINER_BUGSY_2)
            return B_TRANSITION_BUGSY;
        if(gTrainerBattleOpponent_A == TRAINER_WHITNEY_2)
            return B_TRANSITION_WHITNEY;
        if(gTrainerBattleOpponent_A == TRAINER_MORTY_2)
            return B_TRANSITION_MORTY;
        if(gTrainerBattleOpponent_A == TRAINER_CHUCK_2)
            return B_TRANSITION_CHUCK;
        if(gTrainerBattleOpponent_A == TRAINER_JASMINE_2)
            return B_TRANSITION_JASMINE;
        if(gTrainerBattleOpponent_A == TRAINER_PRYCE_2)
            return B_TRANSITION_PRYCE;
        if(gTrainerBattleOpponent_A == TRAINER_CLAIR_2)
            return B_TRANSITION_CLAIR;
        if(gTrainerBattleOpponent_A == TRAINER_BROCK)
            return B_TRANSITION_BROCK;
        if(gTrainerBattleOpponent_A == TRAINER_MISTY)
            return B_TRANSITION_MISTY;
        if(gTrainerBattleOpponent_A == TRAINER_LTSURGE)
            return B_TRANSITION_SURGE;
        if(gTrainerBattleOpponent_A == TRAINER_ERIKA)
            return B_TRANSITION_ERIKA;
        if(gTrainerBattleOpponent_A == TRAINER_SABRINA)
            return B_TRANSITION_SABRINA;
        if(gTrainerBattleOpponent_A == TRAINER_JANINE)
            return B_TRANSITION_JANINE;
        if(gTrainerBattleOpponent_A == TRAINER_BLAINE)
            return B_TRANSITION_BLAINE;
        if(gTrainerBattleOpponent_A == TRAINER_BLUE)
            return B_TRANSITION_BLUE;
        }

    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_PKMN_TRAINER_1){
        return B_TRANSITION_BIG_POKEBALL;
    }


    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_RIVAL){
        return B_TRANSITION_SILVER;
    }

    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_KIMONO_GIRL)
    {
        if(gTrainerBattleOpponent_A == TRAINER_NAOKO)
            return B_TRANSITION_NAOKO;
        if(gTrainerBattleOpponent_A == TRAINER_SAYO)
            return B_TRANSITION_SAYO;
        if(gTrainerBattleOpponent_A == TRAINER_ZUKI)
            return B_TRANSITION_ZUKI;
        if(gTrainerBattleOpponent_A == TRAINER_KUNI)
            return B_TRANSITION_KUNI;
        if(gTrainerBattleOpponent_A == TRAINER_MIKI){
            return B_TRANSITION_MIKI;
        }
    }
        

    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_MYSTERY_MAN){
        return B_TRANSITION_EUSINE;
    }

    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_ROCKET_ADMIN)
    {
        if (gTrainerBattleOpponent_A == TRAINER_PROTON_1)
            return B_TRANSITION_PROTON;
        if (gTrainerBattleOpponent_A == TRAINER_PETREL_1)
            return B_TRANSITION_PETREL;
        if (gTrainerBattleOpponent_A == TRAINER_ARIANA_1)
            return B_TRANSITION_ARIANA;
        if (gTrainerBattleOpponent_A == TRAINER_PETREL_2)
            return B_TRANSITION_PETREL;
        if (gTrainerBattleOpponent_A == TRAINER_PROTON_2)
            return B_TRANSITION_PROTON;
        if (gTrainerBattleOpponent_A == TRAINER_ARIANA_2)
            return B_TRANSITION_ARIANA;
        if (gTrainerBattleOpponent_A == TRAINER_ARCHER)
            return B_TRANSITION_ARCHER;
        if (gTrainerBattleOpponent_A == TRAINER_GIOVANNI)
            return B_TRANSITION_GIOVANNI;
        return B_TRANSITION_ROCKET;
    }

    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_CHAMPION)
        return B_TRANSITION_CHAMPION;

    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_TEAM_MAGMA
        || gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_MAGMA_LEADER
        || gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_MAGMA_ADMIN)
        return B_TRANSITION_MAGMA;

    if (gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_TEAM_AQUA
        || gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_AQUA_LEADER
        || gTrainers[gTrainerBattleOpponent_A].trainerClass == TRAINER_CLASS_AQUA_ADMIN)
        return B_TRANSITION_AQUA;

    if (gTrainers[gTrainerBattleOpponent_A].doubleBattle == TRUE)
        minPartyCount = 2; // double battles always at least have 2 Pokémon.
    else
        minPartyCount = 1;

    transitionType = GetBattleTransitionTypeByMap();
    enemyLevel = GetSumOfEnemyPartyLevel(gTrainerBattleOpponent_A, minPartyCount);
    playerLevel = GetSumOfPlayerPartyLevel(minPartyCount);

    if (enemyLevel < playerLevel)
        return sBattleTransitionTable_Trainer[transitionType][0];
    else
        return sBattleTransitionTable_Trainer[transitionType][1];
}

#define RANDOM_TRANSITION(table)(table[Random() % ARRAY_COUNT(table)])
u8 GetSpecialBattleTransition(s32 id)
{
    u16 var;
    u8 enemyLevel = GetMonData(&gEnemyParty[0], MON_DATA_LEVEL);
    u8 playerLevel = GetSumOfPlayerPartyLevel(1);

    if (enemyLevel < playerLevel)
    {
        switch (id)
        {
        case B_TRANSITION_GROUP_TRAINER_HILL:
        case B_TRANSITION_GROUP_SECRET_BASE:
        case B_TRANSITION_GROUP_E_READER:
            return B_TRANSITION_POKEBALLS_TRAIL;
        case B_TRANSITION_GROUP_B_PYRAMID:
            return RANDOM_TRANSITION(sBattleTransitionTable_BattlePyramid);
        case B_TRANSITION_GROUP_B_DOME:
            return RANDOM_TRANSITION(sBattleTransitionTable_BattleDome);
        }

        if (VarGet(VAR_FRONTIER_BATTLE_MODE) != FRONTIER_MODE_LINK_MULTIS)
            return RANDOM_TRANSITION(sBattleTransitionTable_BattleFrontier);
    }
    else
    {
        switch (id)
        {
        case B_TRANSITION_GROUP_TRAINER_HILL:
        case B_TRANSITION_GROUP_SECRET_BASE:
        case B_TRANSITION_GROUP_E_READER:
            return B_TRANSITION_BIG_POKEBALL;
        case B_TRANSITION_GROUP_B_PYRAMID:
            return RANDOM_TRANSITION(sBattleTransitionTable_BattlePyramid);
        case B_TRANSITION_GROUP_B_DOME:
            return RANDOM_TRANSITION(sBattleTransitionTable_BattleDome);
        }

        if (VarGet(VAR_FRONTIER_BATTLE_MODE) != FRONTIER_MODE_LINK_MULTIS)
            return RANDOM_TRANSITION(sBattleTransitionTable_BattleFrontier);
    }

    var = gSaveBlock2Ptr->frontier.trainerIds[gSaveBlock2Ptr->frontier.curChallengeBattleNum * 2 + 0]
        + gSaveBlock2Ptr->frontier.trainerIds[gSaveBlock2Ptr->frontier.curChallengeBattleNum * 2 + 1];

    return sBattleTransitionTable_BattleFrontier[var % ARRAY_COUNT(sBattleTransitionTable_BattleFrontier)];
}

void ChooseStarter(void)
{
    SetMainCallback2(CB2_ChooseStarter);
    gMain.savedCallback = CB2_GiveStarter;
}

static void CB2_GiveStarter(void)
{
    u16 starterMon;

    *GetVarPointer(VAR_STARTER_MON) = gSpecialVar_Result;
    starterMon = GetStarterPokemon(gSpecialVar_Result);
    ScriptGiveMon(starterMon, 5, ITEM_NONE, 0, 0, 0);
    ResetTasks();
    PlayBattleBGM();
    SetMainCallback2(CB2_StartFirstBattle);
    BattleTransition_Start(B_TRANSITION_BLUR);
}

static void CB2_StartFirstBattle(void)
{
    UpdatePaletteFade();
    RunTasks();

    if (IsBattleTransitionDone() == TRUE)
    {
        gBattleTypeFlags = BATTLE_TYPE_FIRST_BATTLE;
        gMain.savedCallback = CB2_EndFirstBattle;
        FreeAllWindowBuffers();
        SetMainCallback2(CB2_InitBattle);
        RestartWildEncounterImmunitySteps();
        ClearPoisonStepCounter();
        IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
        IncrementGameStat(GAME_STAT_WILD_BATTLES);
        IncrementDailyWildBattles();
        TryUpdateGymLeaderRematchFromWild();
    }
}

static void CB2_EndFirstBattle(void)
{
    Overworld_ClearSavedMusic();
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void TryUpdateGymLeaderRematchFromWild(void)
{
    if (GetGameStat(GAME_STAT_WILD_BATTLES) % 10 == 0)
        UpdateGymLeaderRematch();
}

static void TryUpdateGymLeaderRematchFromTrainer(void)
{
    if (GetGameStat(GAME_STAT_TRAINER_BATTLES) % 5 == 0)
        UpdateGymLeaderRematch();
}

// why not just use the macros? maybe its because they didnt want to uncast const every time?
static u32 TrainerBattleLoadArg32(const u8 *ptr)
{
    return T1_READ_32(ptr);
}

static u16 TrainerBattleLoadArg16(const u8 *ptr)
{
    return T1_READ_16(ptr);
}

static u8 TrainerBattleLoadArg8(const u8 *ptr)
{
    return T1_READ_8(ptr);
}

static u16 GetTrainerAFlag(void)
{
    return TRAINER_FLAGS_START + gTrainerBattleOpponent_A;
}

static u16 GetTrainerBFlag(void)
{
    return TRAINER_FLAGS_START + gTrainerBattleOpponent_B;
}

static bool32 IsPlayerDefeated(u32 battleOutcome)
{
    switch (battleOutcome)
    {
    case B_OUTCOME_LOST:
    case B_OUTCOME_DREW:
        return TRUE;
    case B_OUTCOME_WON:
    case B_OUTCOME_RAN:
    case B_OUTCOME_PLAYER_TELEPORTED:
    case B_OUTCOME_MON_FLED:
    case B_OUTCOME_CAUGHT:
        return FALSE;
    default:
        return FALSE;
    }
}

void ResetTrainerOpponentIds(void)
{
    gTrainerBattleOpponent_A = 0;
    gTrainerBattleOpponent_B = 0;
}

static void InitTrainerBattleVariables(void)
{
    sTrainerBattleMode = 0;
    if (gApproachingTrainerId == 0)
    {
        sTrainerAIntroSpeech = NULL;
        sTrainerADefeatSpeech = NULL;
        sTrainerABattleScriptRetAddr = NULL;
    }
    else
    {
        sTrainerBIntroSpeech = NULL;
        sTrainerBDefeatSpeech = NULL;
        sTrainerBBattleScriptRetAddr = NULL;
    }
    sTrainerObjectEventLocalId = 0;
    sTrainerVictorySpeech = NULL;
    sTrainerCannotBattleSpeech = NULL;
    sTrainerBattleEndScript = NULL;
}

static inline void SetU8(void *ptr, u8 value)
{
    *(u8 *)(ptr) = value;
}

static inline void SetU16(void *ptr, u16 value)
{
    *(u16 *)(ptr) = value;
}

static inline void SetU32(void *ptr, u32 value)
{
    *(u32 *)(ptr) = value;
}

static inline void SetPtr(const void *ptr, const void *value)
{
    *(const void **)(ptr) = value;
}

static void TrainerBattleLoadArgs(const struct TrainerBattleParameter *specs, const u8 *data)
{
    while (1)
    {
        switch (specs->ptrType)
        {
        case TRAINER_PARAM_LOAD_VAL_8BIT:
            SetU8(specs->varPtr, TrainerBattleLoadArg8(data));
            data += 1;
            break;
        case TRAINER_PARAM_LOAD_VAL_16BIT:
            SetU16(specs->varPtr, TrainerBattleLoadArg16(data));
            data += 2;
            break;
        case TRAINER_PARAM_LOAD_VAL_32BIT:
            SetU32(specs->varPtr, TrainerBattleLoadArg32(data));
            data += 4;
            break;
        case TRAINER_PARAM_CLEAR_VAL_8BIT:
            SetU8(specs->varPtr, 0);
            break;
        case TRAINER_PARAM_CLEAR_VAL_16BIT:
            SetU16(specs->varPtr, 0);
            break;
        case TRAINER_PARAM_CLEAR_VAL_32BIT:
            SetU32(specs->varPtr, 0);
            break;
        case TRAINER_PARAM_LOAD_SCRIPT_RET_ADDR:
            SetPtr(specs->varPtr, data);
            return;
        }
        specs++;
    }
}

void SetMapVarsToTrainer(void)
{
    if (sTrainerObjectEventLocalId != 0)
    {
        gSpecialVar_LastTalked = sTrainerObjectEventLocalId;
        gSelectedObjectEvent = GetObjectEventIdByLocalIdAndMap(sTrainerObjectEventLocalId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
    }
}

const u8 *BattleSetup_ConfigureTrainerBattle(const u8 *data)
{
    InitTrainerBattleVariables();
    sTrainerBattleMode = TrainerBattleLoadArg8(data);

    switch (sTrainerBattleMode)
    {
    case TRAINER_BATTLE_SINGLE_NO_INTRO_TEXT:
        TrainerBattleLoadArgs(sOrdinaryNoIntroBattleParams, data);
        return EventScript_DoNoIntroTrainerBattle;
    case TRAINER_BATTLE_DOUBLE:
        TrainerBattleLoadArgs(sDoubleBattleParams, data);
        SetMapVarsToTrainer();
        return EventScript_TryDoDoubleTrainerBattle;
    case TRAINER_BATTLE_CONTINUE_SCRIPT:
        if (gApproachingTrainerId == 0)
        {
            TrainerBattleLoadArgs(sContinueScriptBattleParams, data);
            SetMapVarsToTrainer();
        }
        else
        {
            TrainerBattleLoadArgs(sTrainerBContinueScriptBattleParams, data);
        }
        return EventScript_TryDoNormalTrainerBattle;
    case TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC:
        TrainerBattleLoadArgs(sContinueScriptBattleParams, data);
        SetMapVarsToTrainer();
        return EventScript_TryDoNormalTrainerBattle;
    case TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE:
    case TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC:
        TrainerBattleLoadArgs(sContinueScriptDoubleBattleParams, data);
        SetMapVarsToTrainer();
        return EventScript_TryDoDoubleTrainerBattle;
    case TRAINER_BATTLE_REMATCH_DOUBLE:
        TrainerBattleLoadArgs(sDoubleBattleParams, data);
        SetMapVarsToTrainer();
        gTrainerBattleOpponent_A = GetRematchTrainerId(gTrainerBattleOpponent_A);
        return EventScript_TryDoDoubleRematchBattle;
    case TRAINER_BATTLE_REMATCH:
        TrainerBattleLoadArgs(sOrdinaryBattleParams, data);
        SetMapVarsToTrainer();
        gTrainerBattleOpponent_A = GetRematchTrainerId(gTrainerBattleOpponent_A);
        return EventScript_TryDoRematchBattle;
    case TRAINER_BATTLE_PYRAMID:
        if (gApproachingTrainerId == 0)
        {
            TrainerBattleLoadArgs(sOrdinaryBattleParams, data);
            SetMapVarsToTrainer();
            gTrainerBattleOpponent_A = LocalIdToPyramidTrainerId(gSpecialVar_LastTalked);
        }
        else
        {
            TrainerBattleLoadArgs(sTrainerBOrdinaryBattleParams, data);
            gTrainerBattleOpponent_B = LocalIdToPyramidTrainerId(gSpecialVar_LastTalked);
        }
        return EventScript_TryDoNormalTrainerBattle;
    case TRAINER_BATTLE_SET_TRAINER_A:
        TrainerBattleLoadArgs(sOrdinaryBattleParams, data);
        return NULL;
    case TRAINER_BATTLE_SET_TRAINER_B:
        TrainerBattleLoadArgs(sTrainerBOrdinaryBattleParams, data);
        return NULL;
    case TRAINER_BATTLE_HILL:
        if (gApproachingTrainerId == 0)
        {
            TrainerBattleLoadArgs(sOrdinaryBattleParams, data);
            SetMapVarsToTrainer();
            gTrainerBattleOpponent_A = LocalIdToHillTrainerId(gSpecialVar_LastTalked);
        }
        else
        {
            TrainerBattleLoadArgs(sTrainerBOrdinaryBattleParams, data);
            gTrainerBattleOpponent_B = LocalIdToHillTrainerId(gSpecialVar_LastTalked);
        }
        return EventScript_TryDoNormalTrainerBattle;
    default:
        if (gApproachingTrainerId == 0)
        {
            TrainerBattleLoadArgs(sOrdinaryBattleParams, data);
            SetMapVarsToTrainer();
        }
        else
        {
            TrainerBattleLoadArgs(sTrainerBOrdinaryBattleParams, data);
        }
        return EventScript_TryDoNormalTrainerBattle;
    }
}

void ConfigureAndSetUpOneTrainerBattle(u8 trainerObjEventId, const u8 *trainerScript)
{
    gSelectedObjectEvent = trainerObjEventId;
    gSpecialVar_LastTalked = gObjectEvents[trainerObjEventId].localId;
    BattleSetup_ConfigureTrainerBattle(trainerScript + 1);
    ScriptContext_SetupScript(EventScript_StartTrainerApproach);
    LockPlayerFieldControls();
}

void ConfigureTwoTrainersBattle(u8 trainerObjEventId, const u8 *trainerScript)
{
    gSelectedObjectEvent = trainerObjEventId;
    gSpecialVar_LastTalked = gObjectEvents[trainerObjEventId].localId;
    BattleSetup_ConfigureTrainerBattle(trainerScript + 1);
}

void SetUpTwoTrainersBattle(void)
{
    ScriptContext_SetupScript(EventScript_StartTrainerApproach);
    LockPlayerFieldControls();
}

bool32 GetTrainerFlagFromScriptPointer(const u8 *data)
{
    u32 flag = TrainerBattleLoadArg16(data + 2);
    return FlagGet(TRAINER_FLAGS_START + flag);
}

// Set trainer's movement type so they stop and remain facing that direction
// Note: Only for trainers who are spoken to directly
//       For trainers who spot the player this is handled by PlayerFaceApproachingTrainer
void SetTrainerFacingDirection(void)
{
    struct ObjectEvent *objectEvent = &gObjectEvents[gSelectedObjectEvent];
    SetTrainerMovementType(objectEvent, GetTrainerFacingDirectionMovementType(objectEvent->facingDirection));
}

u8 GetTrainerBattleMode(void)
{
    return sTrainerBattleMode;
}

bool8 GetTrainerFlag(void)
{
    if (InBattlePyramid())
        return GetBattlePyramidTrainerFlag(gSelectedObjectEvent);
    else if (InTrainerHill())
        return GetHillTrainerFlag(gSelectedObjectEvent);
    else
        return FlagGet(GetTrainerAFlag());
}

static void SetBattledTrainersFlags(void)
{
    if (gTrainerBattleOpponent_B != 0)
        FlagSet(GetTrainerBFlag());
    FlagSet(GetTrainerAFlag());
}

static void UNUSED SetBattledTrainerFlag(void)
{
    FlagSet(GetTrainerAFlag());
}

bool8 HasTrainerBeenFought(u16 trainerId)
{
    return FlagGet(TRAINER_FLAGS_START + trainerId);
}

void SetTrainerFlag(u16 trainerId)
{
    FlagSet(TRAINER_FLAGS_START + trainerId);
}

void ClearTrainerFlag(u16 trainerId)
{
    FlagClear(TRAINER_FLAGS_START + trainerId);
}

void BattleSetup_StartTrainerBattle(void)
{
    if (gNoOfApproachingTrainers == 2)
        gBattleTypeFlags = (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_TRAINER);
    else
        gBattleTypeFlags = (BATTLE_TYPE_TRAINER);

    if (InBattlePyramid())
    {
        VarSet(VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0);
        gBattleTypeFlags |= BATTLE_TYPE_PYRAMID;

        if (gNoOfApproachingTrainers == 2)
        {
            FillFrontierTrainersParties(1);
            ZeroMonData(&gEnemyParty[1]);
            ZeroMonData(&gEnemyParty[2]);
            ZeroMonData(&gEnemyParty[4]);
            ZeroMonData(&gEnemyParty[5]);
        }
        else
        {
            FillFrontierTrainerParty(1);
            ZeroMonData(&gEnemyParty[1]);
            ZeroMonData(&gEnemyParty[2]);
        }

        MarkApproachingPyramidTrainersAsBattled();
    }
    else if (InTrainerHillChallenge())
    {
        gBattleTypeFlags |= BATTLE_TYPE_TRAINER_HILL;

        if (gNoOfApproachingTrainers == 2)
            FillHillTrainersParties();
        else
            FillHillTrainerParty();

        SetHillTrainerFlag();
    }

    sNoOfPossibleTrainerRetScripts = gNoOfApproachingTrainers;
    gNoOfApproachingTrainers = 0;
    sShouldCheckTrainerBScript = FALSE;
    gWhichTrainerToFaceAfterBattle = 0;
    gMain.savedCallback = CB2_EndTrainerBattle;

    if (InBattlePyramid() || InTrainerHillChallenge())
        DoBattlePyramidTrainerHillBattle();
    else
        DoTrainerBattle();

    ScriptContext_Stop();
}

void BattleSetup_StartTrainerBattle_Debug(void)
{
    sNoOfPossibleTrainerRetScripts = gNoOfApproachingTrainers;
    gNoOfApproachingTrainers = 0;
    sShouldCheckTrainerBScript = FALSE;
    gWhichTrainerToFaceAfterBattle = 0;
    gMain.savedCallback = CB2_EndTrainerBattle;

    CreateBattleStartTask_Debug(GetWildBattleTransition(), 0);

    ScriptContext_Stop();
}

static void CB2_EndTrainerBattle(void)
{
    #if TX_DEBUG_SYSTEM_ENABLE == TRUE
        gIsDebugBattle = FALSE;
    #endif
    if (gTrainerBattleOpponent_A == TRAINER_SECRET_BASE)
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
    else if (IsPlayerDefeated(gBattleOutcome) == TRUE)
    {
        if (InBattlePyramid() || InTrainerHillChallenge())
            SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        else
            SetMainCallback2(CB2_WhiteOut);
    }
    else
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        if (!InBattlePyramid() && !InTrainerHillChallenge())
        {
            RegisterTrainerInMatchCall();
            SetBattledTrainersFlags();
        }
    }
}

static void CB2_EndRematchBattle(void)
{
    if (gTrainerBattleOpponent_A == TRAINER_SECRET_BASE)
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
    }
    else if (IsPlayerDefeated(gBattleOutcome) == TRUE)
    {
        SetMainCallback2(CB2_WhiteOut);
    }
    else
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        RegisterTrainerInMatchCall();
        SetBattledTrainersFlags();
        HandleRematchVarsOnBattleEnd();
    }
}

void BattleSetup_StartRematchBattle(void)
{
    gBattleTypeFlags = BATTLE_TYPE_TRAINER;
    gMain.savedCallback = CB2_EndRematchBattle;
    DoTrainerBattle();
    ScriptContext_Stop();
}

void ShowTrainerIntroSpeech(void)
{
    if (InBattlePyramid())
    {
        if (gNoOfApproachingTrainers == 0 || gNoOfApproachingTrainers == 1)
            CopyPyramidTrainerSpeechBefore(LocalIdToPyramidTrainerId(gSpecialVar_LastTalked));
        else
            CopyPyramidTrainerSpeechBefore(LocalIdToPyramidTrainerId(gObjectEvents[gApproachingTrainers[gApproachingTrainerId].objectEventId].localId));

        ShowFieldMessageFromBuffer();
    }
    else if (InTrainerHillChallenge())
    {
        if (gNoOfApproachingTrainers == 0 || gNoOfApproachingTrainers == 1)
            CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_INTRO, LocalIdToHillTrainerId(gSpecialVar_LastTalked));
        else
            CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_INTRO, LocalIdToHillTrainerId(gObjectEvents[gApproachingTrainers[gApproachingTrainerId].objectEventId].localId));

        ShowFieldMessageFromBuffer();
    }
    else
    {
        ShowFieldMessage(GetIntroSpeechOfApproachingTrainer());
    }
}

const u8 *BattleSetup_GetScriptAddrAfterBattle(void)
{
    if (sTrainerBattleEndScript != NULL)
        return sTrainerBattleEndScript;
    else
        return EventScript_TestSignpostMsg;
}

const u8 *BattleSetup_GetTrainerPostBattleScript(void)
{
    if (sShouldCheckTrainerBScript)
    {
        sShouldCheckTrainerBScript = FALSE;
        if (sTrainerBBattleScriptRetAddr != NULL)
        {
            gWhichTrainerToFaceAfterBattle = 1;
            return sTrainerBBattleScriptRetAddr;
        }
    }
    else
    {
        if (sTrainerABattleScriptRetAddr != NULL)
        {
            gWhichTrainerToFaceAfterBattle = 0;
            return sTrainerABattleScriptRetAddr;
        }
    }

    return EventScript_TryGetTrainerScript;
}

void ShowTrainerCantBattleSpeech(void)
{
    ShowFieldMessage(GetTrainerCantBattleSpeech());
}

void PlayTrainerEncounterMusic(void)
{
    u16 trainerId;
    u16 music;

    if (gApproachingTrainerId == 0)
        trainerId = gTrainerBattleOpponent_A;
    else
        trainerId = gTrainerBattleOpponent_B;

    if (sTrainerBattleMode != TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC
        && sTrainerBattleMode != TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC)
    {
        switch (GetTrainerEncounterMusicId(trainerId))
        {
        case TRAINER_ENCOUNTER_MUSIC_MALE:
            music = MUS_ENCOUNTER_MALE;
            break;
        case TRAINER_ENCOUNTER_MUSIC_FEMALE:
            music = MUS_ENCOUNTER_FEMALE;
            break;
        case TRAINER_ENCOUNTER_MUSIC_GIRL:
            music = MUS_ENCOUNTER_GIRL;
            break;
        case TRAINER_ENCOUNTER_MUSIC_INTENSE:
            music = MUS_ENCOUNTER_INTENSE;
            break;
        case TRAINER_ENCOUNTER_MUSIC_COOL:
            music = MUS_ENCOUNTER_COOL;
            break;
        case TRAINER_ENCOUNTER_MUSIC_ROCKET:
            music = MUS_HG_ENCOUNTER_ROCKET;
            break;
        case TRAINER_ENCOUNTER_MUSIC_MAGMA:
            music = MUS_ENCOUNTER_MAGMA;
            break;
        case TRAINER_ENCOUNTER_MUSIC_SWIMMER:
            music = MUS_ENCOUNTER_SWIMMER;
            break;
        case TRAINER_ENCOUNTER_MUSIC_TWINS:
            music = MUS_ENCOUNTER_TWINS;
            break;
        case TRAINER_ENCOUNTER_MUSIC_ELITE_FOUR:
            music = MUS_ENCOUNTER_ELITE_FOUR;
            break;
        case TRAINER_ENCOUNTER_MUSIC_HIKER:
            music = MUS_ENCOUNTER_HIKER;
            break;
        case TRAINER_ENCOUNTER_MUSIC_SILVER:
            music = MUS_HG_ENCOUNTER_RIVAL;
            break;
        case TRAINER_ENCOUNTER_MUSIC_RICH:
            music = MUS_ENCOUNTER_RICH;
            break;
        case TRAINER_ENCOUNTER_MUSIC_HG_CHAMPION:
            music = MUS_HG_VS_CHAMPION;
            break;
        case  TRAINER_ENCOUNTER_MUSIC_HG_BOY_1:
            music = MUS_HG_ENCOUNTER_BOY_1;
            break;
        case  TRAINER_ENCOUNTER_MUSIC_HG_BOY_2:
            music = MUS_HG_ENCOUNTER_BOY_2;
            break;
        case  TRAINER_ENCOUNTER_MUSIC_HG_GIRL_1:
            music = MUS_HG_ENCOUNTER_GIRL_1;
            break;
        case  TRAINER_ENCOUNTER_MUSIC_HG_GIRL_2:
            music = MUS_HG_ENCOUNTER_GIRL_2;
            break;
        case  TRAINER_ENCOUNTER_MUSIC_HG_SUSPICIOUS_1:
            music = MUS_HG_ENCOUNTER_SUSPICIOUS_1;
            break;
        case  TRAINER_ENCOUNTER_MUSIC_HG_SUSPICIOUS_2:
            music = MUS_HG_ENCOUNTER_SUSPICIOUS_2;
            break;
        case  TRAINER_ENCOUNTER_MUSIC_HG_SAGE:
            music = MUS_HG_ENCOUNTER_SAGE;
            break;
        default:
            music = MUS_ENCOUNTER_SUSPICIOUS;
        }
        PlayNewMapMusic(music);
    }
}

static const u8 *ReturnEmptyStringIfNull(const u8 *string)
{
    if (string == NULL)
        return gText_EmptyString2;
    else
        return string;
}

static const u8 *GetIntroSpeechOfApproachingTrainer(void)
{
    if (gApproachingTrainerId == 0)
        return ReturnEmptyStringIfNull(sTrainerAIntroSpeech);
    else
        return ReturnEmptyStringIfNull(sTrainerBIntroSpeech);
}

const u8 *GetTrainerALoseText(void)
{
    const u8 *string;

    if (gTrainerBattleOpponent_A == TRAINER_SECRET_BASE)
        string = GetSecretBaseTrainerLoseText();
    else
        string = sTrainerADefeatSpeech;

    StringExpandPlaceholders(gStringVar4, ReturnEmptyStringIfNull(string));
    return gStringVar4;
}

const u8 *GetTrainerBLoseText(void)
{
    StringExpandPlaceholders(gStringVar4, ReturnEmptyStringIfNull(sTrainerBDefeatSpeech));
    return gStringVar4;
}

const u8 *GetTrainerWonSpeech(void)
{
    return ReturnEmptyStringIfNull(sTrainerVictorySpeech);
}

static const u8 *GetTrainerCantBattleSpeech(void)
{
    return ReturnEmptyStringIfNull(sTrainerCannotBattleSpeech);
}

static s32 FirstBattleTrainerIdToRematchTableId(const struct RematchTrainer *table, u16 trainerId)
{
    s32 i;

    for (i = 0; i < REMATCH_TABLE_ENTRIES; i++)
    {
        if (table[i].trainerIds[0] == trainerId)
            return i;
    }

    return -1;
}

static s32 TrainerIdToRematchTableId(const struct RematchTrainer *table, u16 trainerId)
{
    s32 i, j;

    for (i = 0; i < REMATCH_TABLE_ENTRIES; i++)
    {
        for (j = 0; j < REMATCHES_COUNT; j++)
        {
            if (table[i].trainerIds[j] == 0) break; // one line required to match -g
            if (table[i].trainerIds[j] == trainerId)
                return i;
        }
    }

    return -1;
}

// Returns TRUE if the given trainer (by their entry in the rematch table) is not allowed to have rematches.
// This applies to the Elite Four and Victory Road Wally (if he's not been defeated yet)
static bool32 IsRematchForbidden(s32 rematchTableId)
{
    if (rematchTableId >= REMATCH_ELITE_FOUR_ENTRIES)
        return TRUE;
    else if (rematchTableId == REMATCH_WALLY_VR)
        return !FlagGet(FLAG_DEFEATED_WALLY_VICTORY_ROAD);
    else
        return FALSE;
}

static void SetRematchIdForTrainer(const struct RematchTrainer *table, u32 tableId)
{
    s32 i;

    for (i = 1; i < REMATCHES_COUNT; i++)
    {
        u16 trainerId = table[tableId].trainerIds[i];

        if (trainerId == 0)
            break;
        if (!HasTrainerBeenFought(trainerId))
            break;
    }

    gSaveBlock1Ptr->trainerRematches[tableId] = i;
}

static bool32 UpdateRandomTrainerRematches(const struct RematchTrainer *table, u16 mapGroup, u16 mapNum)
{
    s32 i;
    bool32 ret = FALSE;

    for (i = 0; i <= REMATCH_SPECIAL_TRAINER_START; i++)
    {
        if (table[i].mapGroup == mapGroup && table[i].mapNum == mapNum && !IsRematchForbidden(i))
        {
            if (gSaveBlock1Ptr->trainerRematches[i] != 0)
            {
                // Trainer already wants a rematch. Don't bother updating it.
                ret = TRUE;
            }
            else if (FlagGet(FLAG_MATCH_CALL_REGISTERED + i)
             && (Random() % 100) <= 50)  // 51% chance of getting a rematch.
            {
                SetRematchIdForTrainer(table, i);
                ret = TRUE;
            }
        }
    }

    return ret;
}

void UpdateRematchIfDefeated(s32 rematchTableId)
{
    if (HasTrainerBeenFought(gRematchTable[rematchTableId].trainerIds[0]) == TRUE)
        SetRematchIdForTrainer(gRematchTable, rematchTableId);
}

static bool32 DoesSomeoneWantRematchIn_(const struct RematchTrainer *table, u16 mapGroup, u16 mapNum)
{
    s32 i;

    for (i = 0; i < REMATCH_TABLE_ENTRIES; i++)
    {
        if (table[i].mapGroup == mapGroup && table[i].mapNum == mapNum && gSaveBlock1Ptr->trainerRematches[i] != 0)
            return TRUE;
    }

    return FALSE;
}

static bool32 IsRematchTrainerIn_(const struct RematchTrainer *table, u16 mapGroup, u16 mapNum)
{
    s32 i;

    for (i = 0; i < REMATCH_TABLE_ENTRIES; i++)
    {
        if (table[i].mapGroup == mapGroup && table[i].mapNum == mapNum)
            return TRUE;
    }

    return FALSE;
}

static bool8 IsFirstTrainerIdReadyForRematch(const struct RematchTrainer *table, u16 firstBattleTrainerId)
{
    s32 tableId = FirstBattleTrainerIdToRematchTableId(table, firstBattleTrainerId);

    if (tableId == -1)
        return FALSE;
    if (tableId >= MAX_REMATCH_ENTRIES)
        return FALSE;
    if (gSaveBlock1Ptr->trainerRematches[tableId] == 0)
        return FALSE;

    return TRUE;
}

static bool8 IsTrainerReadyForRematch_(const struct RematchTrainer *table, u16 trainerId)
{
    s32 tableId = TrainerIdToRematchTableId(table, trainerId);

    if (tableId == -1)
        return FALSE;
    if (tableId >= MAX_REMATCH_ENTRIES)
        return FALSE;
    if (gSaveBlock1Ptr->trainerRematches[tableId] == 0)
        return FALSE;

    return TRUE;
}

static u16 GetRematchTrainerIdFromTable(const struct RematchTrainer *table, u16 firstBattleTrainerId)
{
    const struct RematchTrainer *trainerEntry;
    s32 i;
    s32 tableId = FirstBattleTrainerIdToRematchTableId(table, firstBattleTrainerId);

    if (tableId == -1)
        return FALSE;

    trainerEntry = &table[tableId];
    for (i = 1; i < REMATCHES_COUNT; i++)
    {
        if (trainerEntry->trainerIds[i] == 0) // previous entry was this trainer's last one
            return trainerEntry->trainerIds[i - 1];
        if (!HasTrainerBeenFought(trainerEntry->trainerIds[i]))
            return trainerEntry->trainerIds[i];
    }

    return trainerEntry->trainerIds[REMATCHES_COUNT - 1]; // already beaten at max stage
}

static u16 GetLastBeatenRematchTrainerIdFromTable(const struct RematchTrainer *table, u16 firstBattleTrainerId)
{
    const struct RematchTrainer *trainerEntry;
    s32 i;
    s32 tableId = FirstBattleTrainerIdToRematchTableId(table, firstBattleTrainerId);

    if (tableId == -1)
        return FALSE;

    trainerEntry = &table[tableId];
    for (i = 1; i < REMATCHES_COUNT; i++)
    {
        if (trainerEntry->trainerIds[i] == 0) // previous entry was this trainer's last one
            return trainerEntry->trainerIds[i - 1];
        if (!HasTrainerBeenFought(trainerEntry->trainerIds[i]))
            return trainerEntry->trainerIds[i - 1];
    }

    return trainerEntry->trainerIds[REMATCHES_COUNT - 1]; // already beaten at max stage
}

static void ClearTrainerWantRematchState(const struct RematchTrainer *table, u16 firstBattleTrainerId)
{
    s32 tableId = TrainerIdToRematchTableId(table, firstBattleTrainerId);

    if (tableId != -1)
        gSaveBlock1Ptr->trainerRematches[tableId] = 0;
}

static u32 GetTrainerMatchCallFlag(u32 trainerId)
{
    s32 i;

    for (i = 0; i < REMATCH_TABLE_ENTRIES; i++)
    {
        if (gRematchTable[i].trainerIds[0] == trainerId)
            return FLAG_MATCH_CALL_REGISTERED + i;
    }

    return 0xFFFF;
}

static void RegisterTrainerInMatchCall(void)
{
    if (FlagGet(FLAG_HAS_MATCH_CALL))
    {
        u32 matchCallFlagId = GetTrainerMatchCallFlag(gTrainerBattleOpponent_A);
        if (matchCallFlagId != 0xFFFF)
            FlagSet(matchCallFlagId);
    }
}

static bool8 WasSecondRematchWon(const struct RematchTrainer *table, u16 firstBattleTrainerId)
{
    s32 tableId = FirstBattleTrainerIdToRematchTableId(table, firstBattleTrainerId);

    if (tableId == -1)
        return FALSE;
    if (!HasTrainerBeenFought(table[tableId].trainerIds[1]))
        return FALSE;

    return TRUE;
}

static bool32 HasAtLeastFiveBadges(void)
{
    s32 i, count;

    for (count = 0, i = 0; i < ARRAY_COUNT(sBadgeFlags); i++)
    {
        if (FlagGet(sBadgeFlags[i]) == TRUE)
        {
            if (++count >= 5)
                return TRUE;
        }
    }

    return FALSE;
}

#define STEP_COUNTER_MAX 255

void IncrementRematchStepCounter(void)
{
    if (HasAtLeastFiveBadges())
    {
        if (gSaveBlock1Ptr->trainerRematchStepCounter >= STEP_COUNTER_MAX)
            gSaveBlock1Ptr->trainerRematchStepCounter = STEP_COUNTER_MAX;
        else
            gSaveBlock1Ptr->trainerRematchStepCounter++;
    }
}

static bool32 IsRematchStepCounterMaxed(void)
{
    if (HasAtLeastFiveBadges() && gSaveBlock1Ptr->trainerRematchStepCounter >= STEP_COUNTER_MAX)
        return TRUE;
    else
        return FALSE;
}

void TryUpdateRandomTrainerRematches(u16 mapGroup, u16 mapNum)
{
    if (IsRematchStepCounterMaxed() && UpdateRandomTrainerRematches(gRematchTable, mapGroup, mapNum) == TRUE)
        gSaveBlock1Ptr->trainerRematchStepCounter = 0;
}

bool32 DoesSomeoneWantRematchIn(u16 mapGroup, u16 mapNum)
{
    return DoesSomeoneWantRematchIn_(gRematchTable, mapGroup, mapNum);
}

bool32 IsRematchTrainerIn(u16 mapGroup, u16 mapNum)
{
    return IsRematchTrainerIn_(gRematchTable, mapGroup, mapNum);
}

static u16 GetRematchTrainerId(u16 trainerId)
{
    return GetRematchTrainerIdFromTable(gRematchTable, trainerId);
}

u16 GetLastBeatenRematchTrainerId(u16 trainerId)
{
    return GetLastBeatenRematchTrainerIdFromTable(gRematchTable, trainerId);
}

bool8 ShouldTryRematchBattle(void)
{
    if (IsFirstTrainerIdReadyForRematch(gRematchTable, gTrainerBattleOpponent_A))
        return TRUE;

    return WasSecondRematchWon(gRematchTable, gTrainerBattleOpponent_A);
}

bool8 IsTrainerReadyForRematch(void)
{
    return IsTrainerReadyForRematch_(gRematchTable, gTrainerBattleOpponent_A);
}

static void HandleRematchVarsOnBattleEnd(void)
{
    ClearTrainerWantRematchState(gRematchTable, gTrainerBattleOpponent_A);
    SetBattledTrainersFlags();
}

void ShouldTryGetTrainerScript(void)
{
    if (sNoOfPossibleTrainerRetScripts > 1)
    {
        sNoOfPossibleTrainerRetScripts = 0;
        sShouldCheckTrainerBScript = TRUE;
        gSpecialVar_Result = TRUE;
    }
    else
    {
        sShouldCheckTrainerBScript = FALSE;
        gSpecialVar_Result = FALSE;
    }
}

u16 CountBattledRematchTeams(u16 trainerId)
{
    s32 i;

    if (HasTrainerBeenFought(gRematchTable[trainerId].trainerIds[0]) != TRUE)
        return 0;

    for (i = 1; i < REMATCHES_COUNT; i++)
    {
        if (gRematchTable[trainerId].trainerIds[i] == 0)
            break;
        if (!HasTrainerBeenFought(gRematchTable[trainerId].trainerIds[i]))
            break;
    }

    return i;
}

//tx_randomizer_and_challenges
u8 NuzlockeIsCaptureBlockedBySpeciesClause(u16 species) // @Kurausukun
{
    u8 i;
    if (!gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause)
        return FALSE;

    //disable double catch
    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT))
        return 2; //player already has this exact pokemon

    for (i = 0; i < EVOS_PER_LINE; i++)
    {
        if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(gEvolutionLines[species][i]), FLAG_GET_CAUGHT))
            return TRUE;
    }
    return FALSE;
}

void SetNuzlockeChecks(void)
{
    if (IsOneTypeChallengeActive())
    {
        u8 typeChallenge = gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge;
        OneTypeChallengeCaptureBlocked = (GetTypeBySpecies(GetMonData(&gEnemyParty[0], MON_DATA_SPECIES), 1) != typeChallenge && 
            GetTypeBySpecies(GetMonData(&gEnemyParty[0], MON_DATA_SPECIES), 2) != typeChallenge);
    }

    if (IsNuzlockeActive())
    {
        NuzlockeIsSpeciesClauseActive = NuzlockeIsCaptureBlockedBySpeciesClause(GetMonData(&gEnemyParty[0], MON_DATA_SPECIES));

        NuzlockeIsCaptureBlocked = NuzlockeFlagGet(NuzlockeGetCurrentRegionMapSectionId());

        if (IsMonShiny(&gEnemyParty[0]) && gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause)
        {
            NuzlockeIsCaptureBlocked = FALSE;
            NuzlockeIsSpeciesClauseActive = FALSE;
        }

        #ifndef NDEBUG
        MgbaPrintf(MGBA_LOG_DEBUG, "NuzlockeIsCaptureBlocked=%d", NuzlockeIsCaptureBlocked);
        MgbaPrintf(MGBA_LOG_DEBUG, "NuzlockeIsSpeciesClauseActive=%d", NuzlockeIsSpeciesClauseActive);
        MgbaPrintf(MGBA_LOG_DEBUG, "OneTypeChallengeCaptureBlocked=%d", OneTypeChallengeCaptureBlocked);
        #endif
    }
    else
    {
        NuzlockeIsCaptureBlocked = FALSE;
        NuzlockeIsSpeciesClauseActive = FALSE;
    }
}
