#include "global.h"
#include "main.h"
#include "menu.h"
#include "scanline_effect.h"
#include "palette.h"
#include "sprite.h"
#include "sound.h"
#include "task.h"
#include "malloc.h"
#include "bg.h"
#include "gpu_regs.h"
#include "window.h"
#include "overworld.h"
#include "text.h"
#include "text_window.h"
#include "international_string_util.h"
#include "strings.h"
#include "string_util.h"
#include "gba/m4a_internal.h"
#include "constants/rgb.h"
#include "battle_main.h"
#include "tx_randomizer_and_challenges.h"
#include "pokemon.h"
#include "event_data.h"

enum
{
    MENU_MODE,
    MENU_FEATURES,
    MENU_RANDOMIZER,
    MENU_NUZLOCKE,
    MENU_DIFFICULTY,
    MENU_CHALLENGES,
    MENU_COUNT,
};

// Menu items

enum
{
    MENUITEM_MODE_CLASSIC_MODERN,
    //MENUITEM_MODE_ALTERNATE_SPAWNS,
    MENUITEM_MODE_NEW_EFFECTIVENESS,
    MENUITEM_MODE_MODERN_MOVES,
    MENUITEM_MODE_SYNCHRONIZE,
    MENUITEM_MODE_STURDY,
    MENUITEM_MODE_NEW_CITRUS,
    MENUITEM_MODE_FAIRY_TYPES,
    MENUITEM_MODE_LEGENDARY_ABILITIES,
    MENUITEM_MODE_INFINITE_TMS,
    MENUITEM_MODE_MINTS,
    MENUITEM_MODE_SURVIVE_POISON,
    //Disabled ones below
    MENUITEM_MODE_MODERN_TYPES,
    MENUITEM_MODE_NEW_STATS,
    MENUITEM_MODE_NEW_LEGENDARIES,
    MENUITEM_MODE_NEXT,
    MENUITEM_MODE_COUNT,
};

enum
{
    MENUITEM_FEATURES_RTC_TYPE,
    MENUITEM_FEATURES_SHINY_CHANCE,
    MENUITEM_FEATURES_ITEM_DROP,
    MENUITEM_FEATURES_PKMN_DEATH,
    //Disabled ones below
    MENUITEM_FEATURES_UNLIMITED_WT,
    //MENUITEM_FEATURES_EASY_FEEBAS,
    MENUITEM_FEATURES_FRONTIER_BANS,
    MENUITEM_FEATURES_NEXT,
    MENUITEM_FEATURES_COUNT,
};

enum
{
    MENUITEM_RANDOM_OFF_ON,
    MENUITEM_RANDOM_STARTER,
    MENUITEM_RANDOM_WILD_PKMN,
    MENUITEM_RANDOM_TRAINER,
    MENUITEM_RANDOM_STATIC,
    MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL,
    MENUITEM_RANDOM_INCLUDE_LEGENDARIES,
    MENUITEM_RANDOM_TYPE,
    MENUITEM_RANDOM_MOVES,
    MENUITEM_RANDOM_ABILITIES,
    MENUITEM_RANDOM_EVOLUTIONS,
    MENUITEM_RANDOM_EVOLUTIONS_METHODS,
    MENUITEM_RANDOM_TYPE_EFFEC,
    MENUITEM_RANDOM_ITEMS,
    MENUITEM_RANDOM_CHAOS,
    MENUITEM_RANDOM_NEXT,
    MENUITEM_RANDOM_COUNT,
};

enum
{
    MENUITEM_NUZLOCKE_NUZLOCKE,
    MENUITEM_NUZLOCKE_SPECIES_CLAUSE,
    MENUITEM_NUZLOCKE_SHINY_CLAUSE,
    MENUITEM_NUZLOCKE_NICKNAMING,
    MENUITEM_NUZLOCKE_DELETION,
    MENUITEM_NUZLOCKE_NEXT,
    MENUITEM_NUZLOCKE_COUNT,
};

enum
{
    //MENUITEM_DIFFICULTY_LIMIT_DIFFICULTY,
    MENUITEM_DIFFICULTY_PARTY_LIMIT,
    MENUITEM_DIFFICULTY_LEVEL_CAP,
    MENUITEM_DIFFICULTY_EXP_MULTIPLIER,
    //MENUITEM_DIFFICULTY_HARD_EXP,
    MENUITEM_DIFFICULTY_ITEM_PLAYER,
    MENUITEM_DIFFICULTY_ITEM_TRAINER,
    MENUITEM_DIFFICULTY_MAX_PARTY_IVS,
    MENUITEM_DIFFICULTY_SCALING_IVS,
    MENUITEM_DIFFICULTY_NO_EVS,
    MENUITEM_DIFFICULTY_SCALING_EVS,
    MENUITEM_DIFFICULTY_LESS_ESCAPES,
    MENUITEM_DIFFICULTY_ESCAPE_ROPE_DIG,
    MENUITEM_DIFFICULTY_NEXT,
    MENUITEM_DIFFICULTY_COUNT,
};

enum
{
    MENUITEM_DIFFICULTY_POKECENTER,
    MENUITEM_CHALLENGES_PCHEAL,
    MENUITEM_CHALLENGES_EXPENSIVE,
    MENUITEM_CHALLENGES_EVO_LIMIT,
    MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE,
    MENUITEM_CHALLENGES_BASE_STAT_EQUALIZER,
    MENUITEM_CHALLENGES_MIRROR,
    MENUITEM_CHALLENGES_MIRROR_THIEF,
    MENUITEM_CHALLENGES_SAVE,
    MENUITEM_CHALLENGES_COUNT,
};

// Window Ids
enum
{
    WIN_TOPBAR,
    WIN_OPTIONS,
    WIN_DESCRIPTION
};

static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    {//WIN_TOPBAR
        .bg = 1,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    {//WIN_OPTIONS
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 26,
        .height = 10,
        .paletteNum = 1,
        .baseBlock = 62
    },
    {//WIN_DESCRIPTION
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 1,
        .baseBlock = 500
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
    {
       .bg = 0,
       .charBaseIndex = 1,
       .mapBaseIndex = 30,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
       .baseTile = 0
    },
    {
       .bg = 1,
       .charBaseIndex = 1,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
       .baseTile = 0
    },
};

struct OptionMenu
{
    u16 submenu;
    u8 sel_mode[MENUITEM_MODE_COUNT];
    u8 sel_features[MENUITEM_FEATURES_COUNT];
    u8 sel_randomizer[MENUITEM_RANDOM_COUNT];
    u8 sel_nuzlocke[MENUITEM_NUZLOCKE_COUNT];
    u8 sel_difficulty[MENUITEM_DIFFICULTY_COUNT];
    u8 sel_challenges[MENUITEM_CHALLENGES_COUNT];
    int menuCursor[MENU_COUNT];
    int visibleCursor[MENU_COUNT];
    u8 arrowTaskId;
};

#define Y_DIFF 16 // Difference in pixels between items.
#define OPTIONS_ON_SCREEN 5
#define NUM_OPTIONS_FROM_BORDER 1

// local functions
static void MainCB2(void);
static void VBlankCB(void);
static void DrawTopBarText(void); //top Option text
static void DrawLeftSideOptionText(int selection, int y);
static void DrawRightSideChoiceText(const u8 *str, int x, int y, bool8 choosen, bool8 active);
static void DrawOptionMenuTexts(void); //left side text;
static void DrawChoices(u32 id, int y); //right side draw function
static void HighlightOptionMenuItem(void);
static void Task_OptionMenuFadeIn(u8 taskId);
static void Task_OptionMenuProcessInput(u8 taskId);
static void Task_RandomizerChallengesMenuSave(u8 taskId);
static void Task_RandomizerChallengesMenuFadeOut(u8 taskId);
static void ScrollMenu(int direction);
static void ScrollAll(int direction); // to bottom or top
static int GetMiddleX(const u8 *txt1, const u8 *txt2, const u8 *txt3);
static int XOptions_ProcessInput(int x, int selection);
static int ProcessInput_Options_Two(int selection);
static int ProcessInput_Options_Three(int selection);
static int ProcessInput_Options_Four(int selection);
static int ProcessInput_Options_Five(int selection);
static int ProcessInput_Options_Six(int selection);
static int ProcessInput_Options_Eleven(int selection);
static int ProcessInput_Options_OneTypeChallenge(int selection);
static int ProcessInput_Sound(int selection);
static int ProcessInput_FrameType(int selection);
static const u8 *const OptionTextDescription(void);
static const u8 *const OptionTextRight(u8 menuItem);
static u8 MenuItemCount(void);
static u8 MenuItemCountFromIndex(u8 index);
static u8 MenuItemCancel(void);
static void DrawDescriptionText(void);
static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style, bool8 active);
static void DrawChoices_Options_Three(const u8 *const *const strings, int selection, int y, bool8 active);
static void DrawChoices_Options_Four(const u8 *const *const strings, int selection, int y, bool8 active);
static void DrawChoices_Options_Five(const u8 *const *const strings, int selection, int y, bool8 active);
static void ReDrawAll(void);
static void DrawBgWindowFrames(void);

static void DrawChoices_Random_OffOn(int selection, int y, bool8 active);
static void DrawChoices_Random_OffRandom(int selection, int y, bool8 active);
static void DrawChoices_Random_Toggle(int selection, int y);
static void DrawChoices_Random_Starter(int selection, int y);
static void DrawChoices_Random_WildPkmn(int selection, int y);
static void DrawChoices_Random_Trainer(int selection, int y);
static void DrawChoices_Random_Static(int selection, int y);
static void DrawChoices_Random_EvoStages(int selection, int y);
static void DrawChoices_Random_Legendaries(int selection, int y);
static void DrawChoices_Random_Types(int selection, int y);
static void DrawChoices_Random_Moves(int selection, int y);
static void DrawChoices_Random_Abilities(int selection, int y);
static void DrawChoices_Random_Evolutions(int selection, int y);
static void DrawChoices_Random_EvolutionMethods(int selection, int y);
static void DrawChoices_Random_TypeEffect(int selection, int y);
static void DrawChoices_Random_Items(int selection, int y);
static void DrawChoices_Random_OffChaos(int selection, int y);

static void DrawChoices_Nuzlocke_OnOff(int selection, int y, bool8 active);
static void DrawChoices_Challenges_Nuzlocke(int selection, int y);
static void DrawChoices_Nuzlocke_SpeciesClause(int selection, int y);
static void DrawChoices_Nuzlocke_ShinyClause(int selection, int y);
static void DrawChoices_Nuzlocke_Nicknaming(int selection, int y);
static void DrawChoices_Nuzlocke_Deletion(int selection, int y);

static void DrawChoices_Challenges_PartyLimit(int selection, int y);
static void DrawChoices_Challenges_LevelCap(int selection, int y);
static void DrawChoices_Challenges_ExpMultiplier(int selection, int y);
static void DrawChoices_Challenges_YesNo(int selection, int y, bool8 active);
static void DrawChoices_Challenges_ItemsPlayer(int selection, int y);
static void DrawChoices_Challenges_ItemsTrainer(int selection, int y);
static void DrawChoices_Challenges_NoEVs(int selection, int y);
static void DrawChoices_Challenges_ScalingIVs(int selection, int y);
static void DrawChoices_Challenges_ScalingEVs(int selection, int y);
static void DrawChoices_Challenges_Pokecenters(int selection, int y);

static void DrawChoices_Challenges_EvoLimit(int selection, int y);
static void DrawChoices_Challenges_OneTypeChallenge(int selection, int y);
static void DrawChoices_Challenges_BaseStatEqualizer(int selection, int y);
static void DrawChoices_Challenges_Mirror(int selection, int y);
static void DrawChoices_Challenges_Mirror_Thief(int selection, int y);
//static void DrawChoices_Challenges_LimitDifficulty(int selection, int y);
static void DrawChoices_Challenges_MaxPartyIVs(int selection, int y);
static void DrawChoices_Challenges_PCHeal(int selection, int y);
static void DrawChoices_Challenges_LessEscapes(int selection, int y);
static void DrawChoices_Challenges_Expensive(int selection, int y);

static void DrawChoices_Mode_Classic_Modern_Selector(int selection, int y);
static void DrawChoices_Mode_AlternateSpawns(int selection, int y);
static void DrawChoices_Features_ShinyChance(int selection, int y);
static void DrawChoices_Features_ItemDrop(int selection, int y);
static void DrawChoices_Mode_InfiniteTMs(int selection, int y);
static void DrawChoices_Mode_SurvivePoison(int selection, int y);
static void DrawChoices_Features_EasyFeebas(int selection, int y);
static void DrawChoices_Features_Pkmn_Death(int selection, int y);
static void DrawChoices_Features_Rtc_Type(int selection, int y);
static void DrawChoices_Features_Unlimited_WT(int selection, int y);
static void DrawChoices_Mode_Synchronize(int selection, int y);
static void DrawChoices_Mode_Mints(int selection, int y);
static void DrawChoices_Mode_New_Citrus(int selection, int y);
static void DrawChoices_Mode_Modern_Types(int selection, int y);
static void DrawChoices_Mode_Fairy_Types(int selection, int y);
static void DrawChoices_Mode_New_Stats(int selection, int y);
static void DrawChoices_Mode_Sturdy(int selection, int y);
static void DrawChoices_Mode_Modern_Moves(int selection, int y);
static void DrawChoices_Mode_Legendary_Abilities(int selection, int y);
static void DrawChoices_Mode_New_Legendaries(int selection, int y);
static void DrawChoices_Features_FrontierBans(int selection, int y);
//static void DrawChoices_Difficulty_HardExp(int selection, int y);
static void DrawChoices_Mode_New_Effectiveness(int selection, int y);
static void DrawChoices_Difficulty_Escape_Rope_Dig(int selection, int y);

static void PrintCurrentSelections(void);

// EWRAM vars
EWRAM_DATA static struct OptionMenu *sOptions = NULL;

// const data
static const u8 sEqualSignGfx[] = INCBIN_U8("graphics/interface/option_menu_equals_sign.4bpp"); // note: this is only used in the Japanese release
static const u16 sOptionMenuBg_Pal[] = {RGB(17, 18, 31)};
static const u16 sOptionMenuText_Pal[] = INCBIN_U16("graphics/interface/option_menu_text_custom.gbapal");

#define TEXT_COLOR_OPTIONS_WHITE                1
#define TEXT_COLOR_OPTIONS_GRAY_FG              2
#define TEXT_COLOR_OPTIONS_GRAY_SHADOW          3
#define TEXT_COLOR_OPTIONS_GRAY_LIGHT_FG        4
#define TEXT_COLOR_OPTIONS_ORANGE_FG            5
#define TEXT_COLOR_OPTIONS_ORANGE_SHADOW        6
#define TEXT_COLOR_OPTIONS_RED_FG               7
#define TEXT_COLOR_OPTIONS_RED_SHADOW           8
#define TEXT_COLOR_OPTIONS_GREEN_FG             9
#define TEXT_COLOR_OPTIONS_GREEN_SHADOW         10
#define TEXT_COLOR_OPTIONS_GREEN_DARK_FG        11
#define TEXT_COLOR_OPTIONS_GREEN_DARK_SHADOW    12
#define TEXT_COLOR_OPTIONS_RED_DARK_FG          13
#define TEXT_COLOR_OPTIONS_RED_DARK_SHADOW      14

struct // MENU_MODE
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsMode[MENUITEM_MODE_COUNT] =
{
    [MENUITEM_MODE_CLASSIC_MODERN]        = {DrawChoices_Mode_Classic_Modern_Selector,       ProcessInput_Options_Two}, //ONLY TWO MODES. DRAWING AND BEHAVIOR. LETS FUCKING GO
    //[MENUITEM_MODE_ALTERNATE_SPAWNS]      = {DrawChoices_Mode_AlternateSpawns,      ProcessInput_Options_Hardcoded},
    [MENUITEM_MODE_INFINITE_TMS]          = {DrawChoices_Mode_InfiniteTMs,          ProcessInput_Options_Two},
    [MENUITEM_MODE_SURVIVE_POISON]        = {DrawChoices_Mode_SurvivePoison,        ProcessInput_Options_Two},
    [MENUITEM_MODE_SYNCHRONIZE]           = {DrawChoices_Mode_Synchronize,          ProcessInput_Options_Two},
    [MENUITEM_MODE_STURDY]                = {DrawChoices_Mode_Sturdy,               ProcessInput_Options_Two},
    [MENUITEM_MODE_MINTS]                 = {DrawChoices_Mode_Mints,                ProcessInput_Options_Two},
    [MENUITEM_MODE_MODERN_TYPES]          = {DrawChoices_Mode_Modern_Types,         ProcessInput_Options_Two},
    [MENUITEM_MODE_FAIRY_TYPES]           = {DrawChoices_Mode_Fairy_Types,          ProcessInput_Options_Two},
    [MENUITEM_MODE_NEW_STATS]             = {DrawChoices_Mode_New_Stats,            ProcessInput_Options_Two},
    [MENUITEM_MODE_NEW_CITRUS]            = {DrawChoices_Mode_New_Citrus,           ProcessInput_Options_Two},
    [MENUITEM_MODE_MODERN_MOVES]          = {DrawChoices_Mode_Modern_Moves,         ProcessInput_Options_Two},
    [MENUITEM_MODE_LEGENDARY_ABILITIES]   = {DrawChoices_Mode_Legendary_Abilities,  ProcessInput_Options_Two},
    [MENUITEM_MODE_NEW_LEGENDARIES]       = {DrawChoices_Mode_New_Legendaries,      ProcessInput_Options_Two},
    [MENUITEM_MODE_NEW_EFFECTIVENESS]     = {DrawChoices_Mode_New_Effectiveness,    ProcessInput_Options_Two},
    [MENUITEM_MODE_NEXT]                  = {NULL, NULL},
};

struct // MENU_FEATURES
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsFeatures[MENUITEM_FEATURES_COUNT] =
{
    [MENUITEM_FEATURES_RTC_TYPE]              = {DrawChoices_Features_Rtc_Type,             ProcessInput_Options_Two},
    [MENUITEM_FEATURES_SHINY_CHANCE]          = {DrawChoices_Features_ShinyChance,          ProcessInput_Options_Five},
    [MENUITEM_FEATURES_ITEM_DROP]             = {DrawChoices_Features_ItemDrop,             ProcessInput_Options_Two},
    //[MENUITEM_FEATURES_EASY_FEEBAS]           = {DrawChoices_Features_EasyFeebas,           ProcessInput_Options_Two},
    [MENUITEM_FEATURES_PKMN_DEATH]            = {DrawChoices_Features_Pkmn_Death,           ProcessInput_Options_Two},
    [MENUITEM_FEATURES_UNLIMITED_WT]          = {DrawChoices_Features_Unlimited_WT,         ProcessInput_Options_Two},
    [MENUITEM_FEATURES_FRONTIER_BANS]         = {DrawChoices_Features_FrontierBans,         ProcessInput_Options_Two},
    [MENUITEM_FEATURES_NEXT]                  = {NULL, NULL},
};

// Menu draw and input functions
struct // MENU_RANDOMIZER
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsRandom[MENUITEM_RANDOM_COUNT] =
{
    [MENUITEM_RANDOM_OFF_ON]                    = {DrawChoices_Random_Toggle,           ProcessInput_Options_Two},
    [MENUITEM_RANDOM_STARTER]                   = {DrawChoices_Random_Starter,          ProcessInput_Options_Two},
    [MENUITEM_RANDOM_WILD_PKMN]                 = {DrawChoices_Random_WildPkmn,         ProcessInput_Options_Two},
    [MENUITEM_RANDOM_TRAINER]                   = {DrawChoices_Random_Trainer,          ProcessInput_Options_Two},
    [MENUITEM_RANDOM_STATIC]                    = {DrawChoices_Random_Static,           ProcessInput_Options_Two},
    [MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL]   = {DrawChoices_Random_EvoStages,        ProcessInput_Options_Two},
    [MENUITEM_RANDOM_INCLUDE_LEGENDARIES]       = {DrawChoices_Random_Legendaries,      ProcessInput_Options_Two},
    [MENUITEM_RANDOM_TYPE]                      = {DrawChoices_Random_Types,            ProcessInput_Options_Two},
    [MENUITEM_RANDOM_MOVES]                     = {DrawChoices_Random_Moves,            ProcessInput_Options_Two},
    [MENUITEM_RANDOM_ABILITIES]                 = {DrawChoices_Random_Abilities,        ProcessInput_Options_Two},
    [MENUITEM_RANDOM_EVOLUTIONS]                = {DrawChoices_Random_Evolutions,       ProcessInput_Options_Two},
    [MENUITEM_RANDOM_EVOLUTIONS_METHODS]        = {DrawChoices_Random_EvolutionMethods, ProcessInput_Options_Two},
    [MENUITEM_RANDOM_TYPE_EFFEC]                = {DrawChoices_Random_TypeEffect,       ProcessInput_Options_Two},
    [MENUITEM_RANDOM_ITEMS]                     = {DrawChoices_Random_Items,            ProcessInput_Options_Two},
    [MENUITEM_RANDOM_CHAOS]                     = {DrawChoices_Random_OffChaos,         ProcessInput_Options_Two},
    [MENUITEM_RANDOM_NEXT]                      = {NULL, NULL},
};

struct // MENU_NUZLOCKE
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsNuzlocke[MENUITEM_NUZLOCKE_COUNT] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]        = {DrawChoices_Challenges_Nuzlocke,     ProcessInput_Options_Three},
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]  = {DrawChoices_Nuzlocke_SpeciesClause,  ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]    = {DrawChoices_Nuzlocke_ShinyClause,    ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_NICKNAMING]      = {DrawChoices_Nuzlocke_Nicknaming,     ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_DELETION]        = {DrawChoices_Nuzlocke_Deletion,       ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_NEXT]            = {NULL, NULL},
};

struct // MENU_DIFFICULTY
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsDifficulty[MENUITEM_DIFFICULTY_COUNT] =
{
    [MENUITEM_DIFFICULTY_PARTY_LIMIT]           = {DrawChoices_Challenges_PartyLimit,       ProcessInput_Options_Six},
    [MENUITEM_DIFFICULTY_LEVEL_CAP]             = {DrawChoices_Challenges_LevelCap,         ProcessInput_Options_Three},
    [MENUITEM_DIFFICULTY_EXP_MULTIPLIER]        = {DrawChoices_Challenges_ExpMultiplier,    ProcessInput_Options_Four},
    [MENUITEM_DIFFICULTY_ITEM_PLAYER]           = {DrawChoices_Challenges_ItemsPlayer,      ProcessInput_Options_Two},
    [MENUITEM_DIFFICULTY_ITEM_TRAINER]          = {DrawChoices_Challenges_ItemsTrainer,     ProcessInput_Options_Two},
    [MENUITEM_DIFFICULTY_NO_EVS]                = {DrawChoices_Challenges_NoEVs,            ProcessInput_Options_Two},
    [MENUITEM_DIFFICULTY_SCALING_IVS]           = {DrawChoices_Challenges_ScalingIVs,       ProcessInput_Options_Three},
    [MENUITEM_DIFFICULTY_SCALING_EVS]           = {DrawChoices_Challenges_ScalingEVs,       ProcessInput_Options_Four},
    //[MENUITEM_DIFFICULTY_LIMIT_DIFFICULTY]      = {DrawChoices_Challenges_LimitDifficulty,  ProcessInput_Options_Two},
    [MENUITEM_DIFFICULTY_MAX_PARTY_IVS]         = {DrawChoices_Challenges_MaxPartyIVs,      ProcessInput_Options_Three},
    [MENUITEM_DIFFICULTY_LESS_ESCAPES]          = {DrawChoices_Challenges_LessEscapes,      ProcessInput_Options_Two},
    [MENUITEM_DIFFICULTY_ESCAPE_ROPE_DIG]       = {DrawChoices_Difficulty_Escape_Rope_Dig,  ProcessInput_Options_Two},
    //[MENUITEM_DIFFICULTY_HARD_EXP]              = {DrawChoices_Difficulty_HardExp,          ProcessInput_Options_Two},
    [MENUITEM_DIFFICULTY_NEXT] = {NULL, NULL},
};

struct // MENU_CHALLENGES
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsChallenges[MENUITEM_CHALLENGES_COUNT] =
{
    [MENUITEM_DIFFICULTY_POKECENTER]            = {DrawChoices_Challenges_Pokecenters,          ProcessInput_Options_Two},
    [MENUITEM_CHALLENGES_PCHEAL]                = {DrawChoices_Challenges_PCHeal,               ProcessInput_Options_Two},
    [MENUITEM_CHALLENGES_EXPENSIVE]             = {DrawChoices_Challenges_Expensive,            ProcessInput_Options_Four},
    [MENUITEM_CHALLENGES_EVO_LIMIT]             = {DrawChoices_Challenges_EvoLimit,             ProcessInput_Options_Three},
    [MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE]    = {DrawChoices_Challenges_OneTypeChallenge,     ProcessInput_Options_OneTypeChallenge},
    [MENUITEM_CHALLENGES_BASE_STAT_EQUALIZER]   = {DrawChoices_Challenges_BaseStatEqualizer,    ProcessInput_Options_Four},
    [MENUITEM_CHALLENGES_MIRROR]                = {DrawChoices_Challenges_Mirror,               ProcessInput_Options_Two},
    [MENUITEM_CHALLENGES_MIRROR_THIEF]          = {DrawChoices_Challenges_Mirror_Thief,         ProcessInput_Options_Two},
    [MENUITEM_CHALLENGES_SAVE] = {NULL, NULL},
};


static const u8 sText_Gamemode[]            = _("GAMEMODE");
//static const u8 sText_AlternateSpawns[]     = _("ENCOUNTERS");
static const u8 sText_InfiniteTMs[]         = _("REUSABLE TMS");
static const u8 sText_Poison[]              = _("SURVIVE POISON");
static const u8 sText_Synchronize[]         = _("SYNCHRONIZE");
static const u8 sText_Mints[]               = _("NATURE MINTS");
static const u8 sText_NewCitrus[]           = _("SITRUS BERRY");
static const u8 sText_ModernTypes[]         = _("{COLOR 3}{SHADOW 3}POKéMON TYPES");
static const u8 sText_FairyTypes[]          = _("ADD FAIRY TYPE");
static const u8 sText_NewStats[]            = _("{COLOR 3}{SHADOW 3}POKéMON STATS");
static const u8 sText_Sturdy[]              = _("STURDY");
static const u8 sText_Modern_Moves[]        = _("{PKMN} MOVEPOOL");
static const u8 sText_Legendary_Abilities[] = _("LEGEN. ABILITIES");
static const u8 sText_New_Legendaries[]     = _("{COLOR 3}{SHADOW 3}EXTRA LEGEND.");
static const u8 sText_New_Effectiveness[]   = _("TYPE CHART");
static const u8 sText_Next[]                = _("NEXT");
// Menu left side option names text
static const u8 *const sOptionMenuItemsNamesMode[MENUITEM_MODE_COUNT] =
{
    [MENUITEM_MODE_CLASSIC_MODERN]            = sText_Gamemode,
    //[MENUITEM_MODE_ALTERNATE_SPAWNS]          = sText_AlternateSpawns,
    [MENUITEM_MODE_INFINITE_TMS]              = sText_InfiniteTMs,
    [MENUITEM_MODE_SURVIVE_POISON]            = sText_Poison,
    [MENUITEM_MODE_SYNCHRONIZE]               = sText_Synchronize,
    [MENUITEM_MODE_STURDY]                    = sText_Sturdy,
    [MENUITEM_MODE_MINTS]                     = sText_Mints,
    [MENUITEM_MODE_NEW_CITRUS]                = sText_NewCitrus,
    [MENUITEM_MODE_MODERN_TYPES]              = sText_ModernTypes,
    [MENUITEM_MODE_FAIRY_TYPES]               = sText_FairyTypes,
    [MENUITEM_MODE_NEW_STATS]                 = sText_NewStats,
    [MENUITEM_MODE_MODERN_MOVES]              = sText_Modern_Moves,
    [MENUITEM_MODE_LEGENDARY_ABILITIES]       = sText_Legendary_Abilities,
    [MENUITEM_MODE_NEW_LEGENDARIES]           = sText_New_Legendaries,
    [MENUITEM_MODE_NEW_EFFECTIVENESS]         = sText_New_Effectiveness,
    [MENUITEM_MODE_NEXT]                      = sText_Next,
};

static const u8 sText_RTC_Type[]            = _("CLOCK TYPE");
static const u8 sText_ShinyChance[]         = _("SHINY CHANCE");
static const u8 sText_ItemDrop[]            = _("ITEM DROP");
static const u8 sText_EasyFeebas[]          = _("{COLOR 3}{SHADOW 3}EASIER FEEBAS");
static const u8 sText_Pkmn_Death[]          = _("{COLOR 7}{COLOR 8}POKéMON FAINT"); //Original Color is {COLOR 7}{COLOR 8}
static const u8 sText_Unlimited_WT[]        = _("{COLOR 3}{SHADOW 3}UNLIMITED WT");
static const u8 sText_FrontierBans[]        = _("{COLOR 3}{SHADOW 3}FRONTIER BANS");

// Menu left side option names text
static const u8 *const sOptionMenuItemsNamesFeatures[MENUITEM_FEATURES_COUNT] =
{
    [MENUITEM_FEATURES_RTC_TYPE]                  = sText_RTC_Type,
    [MENUITEM_FEATURES_SHINY_CHANCE]              = sText_ShinyChance,
    [MENUITEM_FEATURES_ITEM_DROP]                 = sText_ItemDrop,
    //[MENUITEM_FEATURES_EASY_FEEBAS]               = sText_EasyFeebas,
    [MENUITEM_FEATURES_PKMN_DEATH]                = sText_Pkmn_Death,
    [MENUITEM_FEATURES_UNLIMITED_WT]              = sText_Unlimited_WT,
    [MENUITEM_FEATURES_FRONTIER_BANS]             = sText_FrontierBans,
    [MENUITEM_FEATURES_NEXT]                      = sText_Next,
};

static const u8 sText_Dummy[] =                     _("DUMMY");
static const u8 sText_Randomizer[] =                _("RANDOMIZER");
static const u8 sText_Starter[] =                   _("STARTER POKéMON");
static const u8 sText_WildPkmn[] =                  _("WILD POKéMON");
static const u8 sText_Trainer[] =                   _("TRAINER");
static const u8 sText_Static[] =                    _("STATIC POKéMON");
static const u8 sText_SimiliarEvolutionLevel[] =    _("BALANCE ON TIERS");
static const u8 sText_InlcudeLegendaries[]=         _("LEGENDARIES");
static const u8 sText_Type[] =                      _("TYPE");
static const u8 sText_Moves[] =                     _("MOVES");
static const u8 sText_Abilities[] =                 _("ABILTIES");
static const u8 sText_Evolutions[] =                _("EVOLUTIONS");
static const u8 sText_EvolutionMethods[] =          _("EVO LINES");
static const u8 sText_TypeEff[] =                   _("EFFECTIVENESS");
static const u8 sText_Items[] =                     _("ITEMS");
static const u8 sText_Chaos[] =                     _("CHAOS MODE");
static const u8 *const sOptionMenuItemsNamesRandom[MENUITEM_RANDOM_COUNT] =
{
    [MENUITEM_RANDOM_OFF_ON]                    = sText_Randomizer,
    [MENUITEM_RANDOM_STARTER]                   = sText_Starter,
    [MENUITEM_RANDOM_WILD_PKMN]                 = sText_WildPkmn,
    [MENUITEM_RANDOM_TRAINER]                   = sText_Trainer,
    [MENUITEM_RANDOM_STATIC]                    = sText_Static,
    [MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL]   = sText_SimiliarEvolutionLevel,
    [MENUITEM_RANDOM_INCLUDE_LEGENDARIES]       = sText_InlcudeLegendaries,
    [MENUITEM_RANDOM_TYPE]                      = sText_Type,
    [MENUITEM_RANDOM_MOVES]                     = sText_Moves,
    [MENUITEM_RANDOM_ABILITIES]                 = sText_Abilities,
    [MENUITEM_RANDOM_EVOLUTIONS]                = sText_Evolutions,
    [MENUITEM_RANDOM_EVOLUTIONS_METHODS]        = sText_EvolutionMethods,
    [MENUITEM_RANDOM_TYPE_EFFEC]                = sText_TypeEff,
    [MENUITEM_RANDOM_ITEMS]                     = sText_Items,
    [MENUITEM_RANDOM_CHAOS]                     = sText_Chaos,
    [MENUITEM_RANDOM_NEXT]                      = sText_Next,
};

// MENU_NUZLOCKE
static const u8 sText_Nuzlocke[]        = _("NUZLOCKE");
static const u8 sText_SpeciesClause[]   = _("DUPES CLAUSE");
static const u8 sText_ShinyClause[]     = _("SHINY CLAUSE");
static const u8 sText_Nicknaming[]      = _("NICKNAMES");
static const u8 sText_Deletion[]        = _("FAINTING");
static const u8 *const sOptionMenuItemsNamesNuzlocke[MENUITEM_NUZLOCKE_COUNT] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]        = sText_Nuzlocke,
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]  = sText_SpeciesClause,
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]    = sText_ShinyClause,
    [MENUITEM_NUZLOCKE_NICKNAMING]      = sText_Nicknaming,
    [MENUITEM_NUZLOCKE_DELETION]        = sText_Deletion,
    [MENUITEM_NUZLOCKE_NEXT]            = sText_Next,
};

//MENU_DIFFICULTY
static const u8 sText_PartyLimit[]          = _("PARTY LIMIT");
static const u8 sText_LessEscapes[]         = _("LESS ESCAPES");
static const u8 sText_LevelCap[]            = _("LEVEL CAP");
static const u8 sText_ExpMultiplier[]       = _("EXP. MULTIPLIER");
static const u8 sText_Items_Player[]        = _("PLAYER ITEMS");
static const u8 sText_Items_Trainer[]       = _("TRAINER ITEMS");
static const u8 sText_NoEVs[]               = _("PLAYER EVs");
static const u8 sText_ScalingIVs[]          = _("TRAINER IVs");
static const u8 sText_ScalingEVs[]          = _("TRAINER EVs");
//static const u8 sText_LimitDifficulty[]     = _("LOCK DIFFICULTY");
//static const u8 sText_HardExp[]             = _("HARD MODE EXP.");
static const u8 sText_MaxPartyIvs[]         = _("PLAYER IVs");
static const u8 sText_DigRope[]             = _("ESC. ROPE / DIG");
static const u8 *const sOptionMenuItemsNamesDifficulty[MENUITEM_DIFFICULTY_COUNT] =
{
    [MENUITEM_DIFFICULTY_PARTY_LIMIT]           = sText_PartyLimit,
    [MENUITEM_DIFFICULTY_LEVEL_CAP]             = sText_LevelCap,
    [MENUITEM_DIFFICULTY_EXP_MULTIPLIER]        = sText_ExpMultiplier,
    [MENUITEM_DIFFICULTY_ITEM_PLAYER]           = sText_Items_Player,
    [MENUITEM_DIFFICULTY_ITEM_TRAINER]          = sText_Items_Trainer,
    [MENUITEM_DIFFICULTY_NO_EVS]                = sText_NoEVs,
    [MENUITEM_DIFFICULTY_SCALING_IVS]           = sText_ScalingIVs,
    [MENUITEM_DIFFICULTY_SCALING_EVS]           = sText_ScalingEVs,
    //[MENUITEM_DIFFICULTY_LIMIT_DIFFICULTY]      = sText_LimitDifficulty,
    //[MENUITEM_DIFFICULTY_HARD_EXP]              = sText_HardExp,
    [MENUITEM_DIFFICULTY_MAX_PARTY_IVS]         = sText_MaxPartyIvs,
    [MENUITEM_DIFFICULTY_LESS_ESCAPES]          = sText_LessEscapes,
    [MENUITEM_DIFFICULTY_ESCAPE_ROPE_DIG]       = sText_DigRope,
    [MENUITEM_DIFFICULTY_NEXT]                  = sText_Next,
};

// MENU_CHALLENGES
static const u8 sText_Pokecenter[]          = _("POKéCENTER");
static const u8 sText_PCHeal[]              = _("PC HEALS {PKMN}");
static const u8 sText_Expensive[]           = _("ULTRA EXPENSIVE!");
static const u8 sText_EvoLimit[]            = _("EVO LIMIT");
static const u8 sText_OneTypeChallenge[]    = _("ONE TYPE ONLY");
static const u8 sText_BaseStatEqualizer[]   = _("STAT EQUALIZER");
static const u8 sText_Mirror[]              = _("MIRROR MODE");
static const u8 sText_MirrorThief[]         = _("MIRROR THIEF");
static const u8 sText_Save[]                = _("SAVE");
static const u8 *const sOptionMenuItemsNamesChallenges[MENUITEM_CHALLENGES_COUNT] =
{
    [MENUITEM_DIFFICULTY_POKECENTER]            = sText_Pokecenter,
    [MENUITEM_CHALLENGES_PCHEAL]                = sText_PCHeal,
    [MENUITEM_CHALLENGES_EXPENSIVE]             = sText_Expensive,
    [MENUITEM_CHALLENGES_EVO_LIMIT]             = sText_EvoLimit,
    [MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE]    = sText_OneTypeChallenge,
    [MENUITEM_CHALLENGES_BASE_STAT_EQUALIZER]   = sText_BaseStatEqualizer,
    [MENUITEM_CHALLENGES_MIRROR]                = sText_Mirror,
    [MENUITEM_CHALLENGES_MIRROR_THIEF]          = sText_MirrorThief,
    [MENUITEM_CHALLENGES_SAVE]                  = sText_Save,
};

static const u8 *const OptionTextRight(u8 menuItem)
{
    switch (sOptions->submenu)
    {
    case MENU_MODE:             return sOptionMenuItemsNamesMode[menuItem];
    case MENU_FEATURES:         return sOptionMenuItemsNamesFeatures[menuItem];
    case MENU_RANDOMIZER:       return sOptionMenuItemsNamesRandom[menuItem];
    case MENU_NUZLOCKE:         return sOptionMenuItemsNamesNuzlocke[menuItem];
    case MENU_DIFFICULTY:       return sOptionMenuItemsNamesDifficulty[menuItem];
    case MENU_CHALLENGES:       return sOptionMenuItemsNamesChallenges[menuItem];
    }
}

// Menu left side text conditions
static bool8 CheckConditions(int selection)
{
    switch (sOptions->submenu)
    {
    case MENU_MODE:
        switch(selection)
        {
            case MENUITEM_MODE_CLASSIC_MODERN:            return TRUE;
            case MENUITEM_MODE_NEXT:                      return TRUE;
            //case MENUITEM_MODE_ALTERNATE_SPAWNS:          return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_MINTS:                     return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_SYNCHRONIZE:               return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1; //changed to 1 so it only locks the options for the first mode (classic, gonna be recommended)
            case MENUITEM_MODE_INFINITE_TMS:              return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_NEW_CITRUS:                return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_SURVIVE_POISON:            return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_MODERN_TYPES:              return FALSE;
            case MENUITEM_MODE_FAIRY_TYPES:               return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_NEW_STATS:                 return FALSE;
            case MENUITEM_MODE_STURDY:                    return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_MODERN_MOVES:              return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_LEGENDARY_ABILITIES:       return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_NEW_LEGENDARIES:           return FALSE;
            case MENUITEM_MODE_NEW_EFFECTIVENESS:         return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
        default:       return FALSE;
        }
    case MENU_FEATURES:
        switch(selection)
        {
            case MENUITEM_FEATURES_PKMN_DEATH:              return !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
            case MENUITEM_FEATURES_UNLIMITED_WT:            return FALSE;
            //case MENUITEM_FEATURES_EASY_FEEBAS:             return FALSE;
            case MENUITEM_FEATURES_FRONTIER_BANS:           return FALSE;
            default:       return TRUE;
        }
    case MENU_RANDOMIZER:
        switch(selection)
        {
            case MENUITEM_RANDOM_STARTER:                   return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_WILD_PKMN:                 return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_TRAINER:                   return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_STATIC:                    return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL:   return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON] 
                                                                && (sOptions->sel_randomizer[MENUITEM_RANDOM_WILD_PKMN] 
                                                                    || sOptions->sel_randomizer[MENUITEM_RANDOM_STARTER]
                                                                    || sOptions->sel_randomizer[MENUITEM_RANDOM_TRAINER] 
                                                                    || sOptions->sel_randomizer[MENUITEM_RANDOM_STATIC])
                                                                && !sOptions->sel_randomizer[MENUITEM_RANDOM_CHAOS];
            case MENUITEM_RANDOM_INCLUDE_LEGENDARIES:       return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON] 
                                                                && (sOptions->sel_randomizer[MENUITEM_RANDOM_WILD_PKMN] 
                                                                    || sOptions->sel_randomizer[MENUITEM_RANDOM_STARTER]
                                                                    || sOptions->sel_randomizer[MENUITEM_RANDOM_TRAINER]
                                                                    || sOptions->sel_randomizer[MENUITEM_RANDOM_STATIC]);
            case MENUITEM_RANDOM_TYPE:                      return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_MOVES:                     return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_ABILITIES:                 return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_EVOLUTIONS:                return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_EVOLUTIONS_METHODS:        return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_TYPE_EFFEC:                return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_ITEMS:                     return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON];
            case MENUITEM_RANDOM_CHAOS:                     return sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON] && (sOptions->sel_randomizer[MENUITEM_RANDOM_WILD_PKMN]
                                                                || sOptions->sel_randomizer[MENUITEM_RANDOM_STARTER]
                                                                || sOptions->sel_randomizer[MENUITEM_RANDOM_TRAINER]
                                                                || sOptions->sel_randomizer[MENUITEM_RANDOM_STATIC]
                                                                || sOptions->sel_randomizer[MENUITEM_RANDOM_TYPE]
                                                                || sOptions->sel_randomizer[MENUITEM_RANDOM_MOVES]
                                                                || sOptions->sel_randomizer[MENUITEM_RANDOM_ABILITIES]
                                                                || sOptions->sel_randomizer[MENUITEM_RANDOM_EVOLUTIONS]
                                                                || sOptions->sel_randomizer[MENUITEM_RANDOM_EVOLUTIONS_METHODS]
                                                                || sOptions->sel_randomizer[MENUITEM_RANDOM_TYPE_EFFEC]);
            default:                                        return TRUE;
        }
    case MENU_NUZLOCKE:
        switch(selection)
        {
        case MENUITEM_NUZLOCKE_SPECIES_CLAUSE:  return sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
        case MENUITEM_NUZLOCKE_SHINY_CLAUSE:    return sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
        case MENUITEM_NUZLOCKE_NICKNAMING:      return sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
        case MENUITEM_NUZLOCKE_DELETION:        return sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
        default:                                return TRUE;
        }
    case MENU_DIFFICULTY:
        switch(selection)
        {
        default:       return TRUE;
        }
    case MENU_CHALLENGES:
        switch(selection)
        {
        case MENUITEM_CHALLENGES_PCHEAL:        return !sOptions->sel_challenges[MENUITEM_DIFFICULTY_POKECENTER];
        case MENUITEM_CHALLENGES_MIRROR_THIEF:  return sOptions->sel_challenges[MENUITEM_CHALLENGES_MIRROR];
        default:                                return TRUE;
        }
    }
}

// Descriptions
static const u8 sText_Empty[]               = _("");
static const u8 sText_Description_Save[]    = _("Save choices and continue...");

static const u8 sText_Description_Mode_Gamemode_Classic[]         = _("Recommended settings.\n{COLOR 7}{COLOR 8}NOTE: All selections are PERMANENT.");
static const u8 sText_Description_Mode_Gamemode_Modern[]          = _("Choose your own rules.\n{COLOR 7}{COLOR 8}NOTE: All selections are PERMANENT.");
static const u8 sText_Description_Mode_Gamemode_Custom[]          = _("Choose your own rules.\n{COLOR 7}{COLOR 8}NOTE: All selections are PERMANENT.");
//static const u8 sText_Description_Mode_AlternateSpawns_Vanilla[]        = _("Use VANILLA wild encounters.\nUnchanged from the original.");
//static const u8 sText_Description_Mode_AlternateSpawns_Postgame[]       = _("VANILLA, but after becoming champion,\nall 423 {PKMN} will be available.");
//static const u8 sText_Description_Mode_AlternateSpawns_Modern[]         = _("Use MODERN wild encounters.\nAll 423 {PKMN} will be available.");
static const u8 sText_Description_Mode_InfiniteTMs_On[]           = _("TMs are reusable.\nModern Emerald recommended.");
static const u8 sText_Description_Mode_InfiniteTMs_Off[]          = _("TMs are not reusable.\nLike in the original.");
static const u8 sText_Description_Mode_SurvivePoison_On[]         = _("Your {PKMN} will survive the POISON\nstatus with 1HP.");
static const u8 sText_Description_Mode_SurvivePoison_Off[]        = _("Your {PKMN} will faint if they are\nPOISONED.");
static const u8 sText_Description_Mode_Synchronize_Old[]          = _("SYNCHRONIZE works as in GEN III.\n50% chance to copy nature.");
static const u8 sText_Description_Mode_Synchronize_New[]          = _("SYNCHRONIZE works as in GEN VIII+.\n100% chance to copy nature.");
static const u8 sText_Description_Mode_Mints_Off[]                = _("Mints are not availabe ingame until\nfinishing the game.");
static const u8 sText_Description_Mode_Mints_On[]                 = _("Mints can be bought at PRETTY PETAL\nFLOWER SHOP after the 4th medal.");
static const u8 sText_Description_Mode_New_Citrus_Off[]           = _("SITRUS BERRY restores 30HP.\nSame as GEN III.");
static const u8 sText_Description_Mode_New_Citrus_On[]            = _("SITRUS BERRY restores 25% of\ntotal HP. Same as GEN IV and up.");
static const u8 sText_Description_Mode_Modern_Types_Off[]         = _("Original {PKMN} typings. Doesn't include\n{PKMN} that got added to FAIRY in GEN VI.");
static const u8 sText_Description_Mode_Modern_Types_On[]          = _("{PKMN} have modified typings\nto make them more viable.");
static const u8 sText_Description_Mode_Fairy_Types_Off[]          = _("FAIRY TYPE isn't added to {PKMN} \nthat got it in GEN VI.");
static const u8 sText_Description_Mode_Fairy_Types_On[]           = _("FAIRY TYPE is added / changed to\ncertain {PKMN}, as in GEN VI.");
static const u8 sText_Description_Mode_New_Stats_Off[]            = _("Original GEN III {PKMN} stats.");
static const u8 sText_Description_Mode_New_Stats_On[]             = _("Modified stats to make certain\n{PKMN} more viable.");
static const u8 sText_Description_Mode_Sturdy_Off[]               = _("STURDY works as in GEN III. Only\nnegates OHKO moves (GUILLOTINE, etc.)");
static const u8 sText_Description_Mode_Sturdy_On[]                = _("STURDY works as in GEN V+.\n{PKMN} survive lethal hits with 1HP.");
static const u8 sText_Description_Mode_Modern_Moves_Off[]         = _("No new MOVES, and original MOVEPOOL\nfor all {PKMN} + new EGG and TUTOR MOVES.");
static const u8 sText_Description_Mode_Modern_Moves_On[]          = _("13 new MOVES, and improved MOVEPOOL\nfor all {PKMN} + new EGG and TUTOR MOVES.");
static const u8 sText_Description_Mode_Leg_Abilities_Off[]        = _("PRESSURE stays as the main\nability of some legendaries.");
static const u8 sText_Description_Mode_Leg_Abilities_On[]         = _("Legendaries have PRESSURE changed\nfor a better ability.");
static const u8 sText_Description_Mode_New_Legendaries_Off[]      = _("No extra legendaries are added.");
static const u8 sText_Description_Mode_New_Legendaries_On[]       = _("Extra legendaries from GEN I and II\nare added via ingame events.");
static const u8 sText_Description_Mode_New_Effectiveness_Original[]  = _("Original type effectiveness\nfor all types.");
static const u8 sText_Description_Mode_New_Effectiveness_Modern[]    = _("New and balanced type effectiveness\nfor certain types.");
static const u8 sText_Description_Mode_Next[]                     = _("Continue to Features options.");

static const u8 *const sOptionMenuItemDescriptionsMode[MENUITEM_MODE_COUNT][5] =
{
    [MENUITEM_MODE_CLASSIC_MODERN]        = {sText_Description_Mode_Gamemode_Classic,       sText_Description_Mode_Gamemode_Modern,       sText_Description_Mode_Gamemode_Custom,             sText_Empty,                                        sText_Empty},
    //[MENUITEM_MODE_ALTERNATE_SPAWNS]      = {sText_Description_Mode_AlternateSpawns_Vanilla,    sText_Description_Mode_AlternateSpawns_Modern,      sText_Description_Mode_AlternateSpawns_Postgame,                                         sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_INFINITE_TMS]          = {sText_Description_Mode_InfiniteTMs_Off,        sText_Description_Mode_InfiniteTMs_On,        sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_SURVIVE_POISON]        = {sText_Description_Mode_SurvivePoison_Off,      sText_Description_Mode_SurvivePoison_On,      sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_SYNCHRONIZE]           = {sText_Description_Mode_Synchronize_Old,        sText_Description_Mode_Synchronize_New,       sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_MINTS]                 = {sText_Description_Mode_Mints_Off,              sText_Description_Mode_Mints_On,              sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_NEW_CITRUS]            = {sText_Description_Mode_New_Citrus_Off,         sText_Description_Mode_New_Citrus_On,         sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_MODERN_TYPES]          = {sText_Description_Mode_Modern_Types_Off,       sText_Description_Mode_Modern_Types_On,       sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_FAIRY_TYPES]           = {sText_Description_Mode_Fairy_Types_Off,        sText_Description_Mode_Fairy_Types_On,        sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_NEW_STATS]             = {sText_Description_Mode_New_Stats_Off,          sText_Description_Mode_New_Stats_On,          sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_STURDY]                = {sText_Description_Mode_Sturdy_Off,             sText_Description_Mode_Sturdy_On,             sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_MODERN_MOVES]          = {sText_Description_Mode_Modern_Moves_Off,       sText_Description_Mode_Modern_Moves_On,       sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_LEGENDARY_ABILITIES]   = {sText_Description_Mode_Leg_Abilities_Off,      sText_Description_Mode_Leg_Abilities_On,      sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_NEW_LEGENDARIES]       = {sText_Description_Mode_New_Legendaries_Off,    sText_Description_Mode_New_Legendaries_On,    sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_NEW_EFFECTIVENESS]     = {sText_Description_Mode_New_Effectiveness_Original,    sText_Description_Mode_New_Effectiveness_Modern,    sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_NEXT]                  = {sText_Description_Mode_Next,                   sText_Empty,                                  sText_Empty,                                        sText_Empty,                                        sText_Empty},
};

static const u8 sText_Description_Features_RTC_Type_RTC[]             = _("Use vanilla Real Time Clock.");
static const u8 sText_Description_Features_RTC_Type_FakeRTC[]         = _("Use a fake Real Time Clock.\n1h in real life = 1 day in-game.");
static const u8 sText_Description_Features_ItemDrop_On[]              = _("Wild {PKMN} will drop their hold item\nafter defeating them.");
static const u8 sText_Description_Features_ItemDrop_Off[]             = _("Wild {PKMN} items will be only obtainable\nvia capture or THIEF.");
static const u8 sText_Description_Features_ShinyChance_8192[]         = _("Very low chance of SHINY encounter.\nDefault chance from Generation III.");
static const u8 sText_Description_Features_ShinyChance_4096[]         = _("Low chance of SHINY encounter.\nDefault chance from Generation VI+.");
static const u8 sText_Description_Features_ShinyChance_2048[]         = _("Decent chance of SHINY encounter.");
static const u8 sText_Description_Features_ShinyChance_1024[]         = _("High chance of SHINY encounter.");
static const u8 sText_Description_Features_ShinyChance_512[]          = _("Very high chance of SHINY encounter.");
static const u8 sText_Description_Features_EasyFeebas_On[]            = _("FEEBAS is easier to catch and spawns\neverywhere in ROUTE 119.");
static const u8 sText_Description_Features_EasyFeebas_Off[]           = _("FEEBAS is encountered in random\nspots in ROUTE 119.");
static const u8 sText_Description_Features_Pkmn_Death_On[]            = _("{COLOR 7}{COLOR 8}YOUR {PKMN} WILL DIE!! Getting to zero\n{PKMN} could be the end of your save."); //{COLOR 1}{COLOR 2} 
static const u8 sText_Description_Features_Pkmn_Death_Off[]           = _("{PKMN} will not die from fainting.\nRecommended.");
static const u8 sText_Description_Features_Unlimited_WT_On[]          = _("Enables a daily limit of 3\nWonderTrades. Recommended.");
static const u8 sText_Description_Features_Unlimited_WT_Off[]         = _("WonderTrades have no daily limit.");
static const u8 sText_Description_Features_FrontierBans_Unban[]       = _("All legendaries are allowed to\nparticipate in the BATTLE FRONTIER.");
static const u8 sText_Description_Features_FrontierBans_Ban[]         = _("According to the chosen difficulty,\nsome lengendaries are banned in BF.");

static const u8 sText_Description_Features_Next[]                     = _("Continue to Randomizer options.");

static const u8 *const sOptionMenuItemDescriptionsFeatures[MENUITEM_FEATURES_COUNT][5] =
{
    [MENUITEM_FEATURES_RTC_TYPE]              = {sText_Description_Features_RTC_Type_RTC,           sText_Description_Features_RTC_Type_FakeRTC,      sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_FEATURES_SHINY_CHANCE]          = {sText_Description_Features_ShinyChance_8192,       sText_Description_Features_ShinyChance_4096,      sText_Description_Features_ShinyChance_2048,        sText_Description_Features_ShinyChance_1024,        sText_Description_Features_ShinyChance_512},
    [MENUITEM_FEATURES_ITEM_DROP]             = {sText_Description_Features_ItemDrop_Off,           sText_Description_Features_ItemDrop_On,           sText_Empty,                                        sText_Empty,                                        sText_Empty},
    //[MENUITEM_FEATURES_EASY_FEEBAS]           = {sText_Description_Features_EasyFeebas_Off,         sText_Description_Features_EasyFeebas_On,         sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_FEATURES_PKMN_DEATH]            = {sText_Description_Features_Pkmn_Death_Off,         sText_Description_Features_Pkmn_Death_On,         sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_FEATURES_UNLIMITED_WT]          = {sText_Description_Features_Unlimited_WT_On,        sText_Description_Features_Unlimited_WT_Off,      sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_FEATURES_FRONTIER_BANS]         = {sText_Description_Features_FrontierBans_Ban,       sText_Description_Features_FrontierBans_Unban,    sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_FEATURES_NEXT]                  = {sText_Description_Features_Next,                   sText_Empty,                                      sText_Empty,                                        sText_Empty,                                        sText_Empty},
};

static const u8 sText_Description_Randomizer_Off[]                  = _("Game will not be randomized.");
static const u8 sText_Description_Randomizer_On[]                   = _("Play the game randomized.\nSettings below!");
static const u8 sText_Description_Random_Starter_Off[]              = _("Standard starter POKéMON.");
static const u8 sText_Description_Random_Starter_On[]               = _("Randomize starter POKéMON.");
static const u8 sText_Description_Random_WildPokemon_Off[]          = _("Same wild encounter as in the\nbase game.");
static const u8 sText_Description_Random_WildPokemon_On[]           = _("Randomize wild POKéMON.");
static const u8 sText_Description_Random_Trainer_Off[]              = _("Trainer will have their expected\nparty.");
static const u8 sText_Description_Random_Trainer_On[]               = _("Randomize enemy trainer parties.");
static const u8 sText_Description_Random_Static_Off[]               = _("Static encounter will be the same\nas in the base game.");
static const u8 sText_Description_Random_Static_On[]                = _("Randomize static encounter POKéMON.");
static const u8 sText_Description_Random_BalanceTiers_Off[]         = _("Distribution of POKéMON {COLOR 7}{COLOR 8}not balanced{COLOR 1}{COLOR 2}\naround their strength!");
static const u8 sText_Description_Random_BalanceTiers_On[]          = _("{PKMN} replaced with similar tiered ones.\nCurrently based on evo stages.");
static const u8 sText_Description_Random_IncludeLegendaries_Off[]   = _("Legendary POKéMON will not be\nincluded and randomized.");
static const u8 sText_Description_Random_IncludeLegendaries_On[]    = _("Include legendary POKéMON in\nrandomization!");
static const u8 sText_Description_Random_Types_Off[]                = _("POKéMON types stay the same as in\nthe base game.");
static const u8 sText_Description_Random_Types_On[]                 = _("Randomize all POKéMON types.");
static const u8 sText_Description_Random_Moves_Off[]                = _("POKéMON moves stay the same as in\nthe base game.");
static const u8 sText_Description_Random_Moves_On[]                 = _("Randomize all POKéMON moves.");
static const u8 sText_Description_Random_Abilities_Off[]            = _("POKéMON abilities stay the same as in\nthe base game.");
static const u8 sText_Description_Random_Abilities_On[]             = _("Randomize all POKéMON abilities.");
static const u8 sText_Description_Random_Evos_Off[]                 = _("POKéMON evolutions stay the same as\nin the base game.");
static const u8 sText_Description_Random_Evos_On[]                  = _("Randomize all POKéMON evolutions.");
static const u8 sText_Description_Random_Evo_Methods_Off[]          = _("The POKéMON that can potentially\nevolve are unchanged.");
static const u8 sText_Description_Random_Evo_Methods_On[]           = _("Randomize evolution lines. Allows\nnew evolution lines to occure!");
static const u8 sText_Description_Random_Effectiveness_Off[]        = _("Type effectiveness chart will remain\nthe same as in the base game.");
static const u8 sText_Description_Random_Effectiveness_On[]         = _("Randomize type effectiveness.\n{COLOR 7}{COLOR 8}WARNING: CAN BE BUGGY!");
static const u8 sText_Description_Random_Items_Off[]                = _("All found or recieved items are the\nsame as in the base game.");
static const u8 sText_Description_Random_Items_On[]                 = _("Randomize found, hidden and revieved\nitems. KEY items are excluded!");
static const u8 sText_Description_Random_ChaosMode_Off[]            = _("Chaos mode disabled.");
static const u8 sText_Description_Random_ChaosMode_On[]             = _("Every above choosen option will be\nvery chaotic. {COLOR 7}{COLOR 8}NOT recommended!");
static const u8 sText_Description_Random_Next[]                     = _("Continue to Nuzlocke options.");
static const u8 *const sOptionMenuItemDescriptionsRandomizer[MENUITEM_RANDOM_COUNT][2] =
{
    [MENUITEM_RANDOM_OFF_ON]                    = {sText_Description_Randomizer_Off,               sText_Description_Randomizer_On},
    [MENUITEM_RANDOM_STARTER]                   = {sText_Description_Random_Starter_Off,                  sText_Description_Random_Starter_On},
    [MENUITEM_RANDOM_WILD_PKMN]                 = {sText_Description_Random_WildPokemon_Off,              sText_Description_Random_WildPokemon_On},
    [MENUITEM_RANDOM_TRAINER]                   = {sText_Description_Random_Trainer_Off,           sText_Description_Random_Trainer_On},
    [MENUITEM_RANDOM_STATIC]                    = {sText_Description_Random_Static_Off,            sText_Description_Random_Static_On},
    [MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL]   = {sText_Description_Random_BalanceTiers_On,    sText_Description_Random_BalanceTiers_Off},
    [MENUITEM_RANDOM_INCLUDE_LEGENDARIES]       = {sText_Description_Random_IncludeLegendaries_Off,       sText_Description_Random_IncludeLegendaries_On},
    [MENUITEM_RANDOM_TYPE]                      = {sText_Description_Random_Types_Off,             sText_Description_Random_Types_On},
    [MENUITEM_RANDOM_MOVES]                     = {sText_Description_Random_Moves_Off,             sText_Description_Random_Moves_On},
    [MENUITEM_RANDOM_ABILITIES]                 = {sText_Description_Random_Abilities_Off,         sText_Description_Random_Abilities_On},
    [MENUITEM_RANDOM_EVOLUTIONS]                = {sText_Description_Random_Evos_Off,              sText_Description_Random_Evos_On},
    [MENUITEM_RANDOM_EVOLUTIONS_METHODS]        = {sText_Description_Random_Evo_Methods_Off,       sText_Description_Random_Evo_Methods_On},
    [MENUITEM_RANDOM_TYPE_EFFEC]                = {sText_Description_Random_Effectiveness_Off,     sText_Description_Random_Effectiveness_On},
    [MENUITEM_RANDOM_ITEMS]                     = {sText_Description_Random_Items_Off,             sText_Description_Random_Items_On},
    [MENUITEM_RANDOM_CHAOS]                     = {sText_Description_Random_ChaosMode_Off,               sText_Description_Random_ChaosMode_On},
    [MENUITEM_RANDOM_NEXT]                      = {sText_Description_Random_Next,                  sText_Empty},
};

static const u8 sText_Description_Nuzlocke_Base[]               = _("Nuzlocke mode is disabled.");
static const u8 sText_Description_Nuzlocke_Normal[]             = _("One catch per route! Fainted POKéMON\ncan't be used anymore.");
static const u8 sText_Description_Nuzlocke_Hard[]               = _("Same rules as NORMAL but also\n{COLOR 7}{COLOR 8}deletes SAVE on battle loss!");
static const u8 sText_Description_Nuzlocke_SpeciesClause_Off[]  = _("The player always has to catch the\nfirst POKéMON per route.");
static const u8 sText_Description_Nuzlocke_SpeciesClause_On[]   = _("Only not prior caught POKéMON count\nas first encounter. {COLOR 7}{COLOR 8}RECOMMENDED!");
static const u8 sText_Description_Nuzlocke_ShinyClause_Off[]    = _("The player can only catch a shiny\nPOKéMON if it's the first encounter.");
static const u8 sText_Description_Nuzlocke_ShinyClause_On[]     = _("The player can always catch shiny\nPOKéMON. {COLOR 7}{COLOR 8}RECOMMENDED!");
static const u8 sText_Description_Nuzlocke_Nicknaming_Off[]     = _("Nicknames are optional.");
static const u8 sText_Description_Nuzlocke_Nicknaming_On[]      = _("Forces the player to nickname every\nPOKéMON. {COLOR 7}{COLOR 8}RECOMMENDED!");
static const u8 sText_Description_Nuzlocke_Deletion_Cemetery[]  = _("Fainted POKéMON are sent to the PC\nafter battle and can't be retrieved.");
static const u8 sText_Description_Nuzlocke_Deletion_Deletion[]  = _("Fainted POKéMON are {COLOR 7}{COLOR 8}released{COLOR 1}{COLOR 2} after\nbattle!");
static const u8 sText_Description_Nuzlocke_Next[]                   = _("Continue to difficulty options.");
static const u8 *const sOptionMenuItemDescriptionsNuzlocke[MENUITEM_NUZLOCKE_COUNT][4] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]            = {sText_Description_Nuzlocke_Base,                 sText_Description_Nuzlocke_Normal,                  sText_Description_Nuzlocke_Hard,    sText_Empty},
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]      = {sText_Description_Nuzlocke_SpeciesClause_On,     sText_Description_Nuzlocke_SpeciesClause_Off,       sText_Empty,                        sText_Empty},
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]        = {sText_Description_Nuzlocke_ShinyClause_On,       sText_Description_Nuzlocke_ShinyClause_Off,         sText_Empty,                        sText_Empty},
    [MENUITEM_NUZLOCKE_NICKNAMING]          = {sText_Description_Nuzlocke_Nicknaming_On,        sText_Description_Nuzlocke_Nicknaming_Off,          sText_Empty,                        sText_Empty},
    [MENUITEM_NUZLOCKE_DELETION]            = {sText_Description_Nuzlocke_Deletion_Cemetery,    sText_Description_Nuzlocke_Deletion_Deletion,       sText_Empty,                        sText_Empty},
    [MENUITEM_NUZLOCKE_NEXT]                = {sText_Description_Nuzlocke_Next,                 sText_Empty,                                        sText_Empty,                        sText_Empty},
};

static const u8 sText_Description_Difficulty_Party_Limit[]              = _("Limit the amount of POKéMON in the\nplayers party.");
static const u8 sText_Description_Difficulty_LevelCap_Base[]            = _("No level cap. Overleveling possible.\n");
static const u8 sText_Description_Difficulty_LevelCap_Normal[]          = _("Maximum level is based on the\nnext gym's highest POKéMON level.");
static const u8 sText_Description_Difficulty_LevelCap_Hard[]            = _("Maximum level is based on the\nnext gym's {COLOR 7}{COLOR 8}lowest POKéMON level.");
static const u8 sText_Description_Difficulty_ExpMultiplier_1_0[]        = _("POKéMON gain normal EXP. Points.\nStacks with HARD MODE EXP.");
static const u8 sText_Description_Difficulty_ExpMultiplier_1_5[]        = _("POKéMON gain 50 percent more EXP.\nPoints! Stacks with HARD MODE EXP.");
static const u8 sText_Description_Difficulty_ExpMultiplier_2_0[]        = _("POKéMON gain double EXP. Points!\nStacks with HARD MODE EXP.");
static const u8 sText_Description_Difficulty_ExpMultiplier_0_0[]        = _("POKéMON gain {COLOR 7}{COLOR 8}ZERO EXP. Points!!!\nApplies to HARD MODE EXP. as well.");
static const u8 sText_Description_Difficulty_Items_Player_Yes[]         = _("The player can use battle items.");
static const u8 sText_Description_Difficulty_Items_Player_No[]          = _("The player can {COLOR 7}{COLOR 8}NOT use battle items.\nHold items are allowed!");
static const u8 sText_Description_Difficulty_Items_Trainer_Yes[]        = _("Enemy trainers can use battle items.");
static const u8 sText_Description_Difficulty_Items_Trainer_No[]         = _("Enemy trainers can {COLOR 7}{COLOR 8}NOT use battle\nitems.");
static const u8 sText_Description_Difficulty_NoEVs_Off[]                = _("The player's POKéMON gain effort\nvalues as expected.");
static const u8 sText_Description_Difficulty_NoEVs_On[]                 = _("The player's POKéMON do {COLOR 7}{COLOR 8}NOT{COLOR 1}{COLOR 2} gain\nany effort values!");
static const u8 sText_Description_Difficulty_ScalingIVs_Off[]           = _("The POKéMON of enemy Trainer have\nthe expected IVs.");
static const u8 sText_Description_Difficulty_ScalingIVs_Scaling[]       = _("The IVs of Trainer POKéMON increase\nwith gym badges!");
static const u8 sText_Description_Difficulty_ScalingIVs_Hard[]          = _("All Trainer POKéMON have perfect\nIVs!");
static const u8 sText_Description_Difficulty_ScalingEVs_Off[]           = _("The POKéMON of enemy Trainer have\nno EVs.");
static const u8 sText_Description_Difficulty_ScalingEVs_Scaling[]       = _("The EVs of Trainer POKéMON increase\nwith gym badges!");
static const u8 sText_Description_Difficulty_ScalingEVs_Hard[]          = _("All Trainer POKéMON have high EVs!");
static const u8 sText_Description_Difficulty_ScalingEVs_Extreme[]       = _("All Trainer POKéMON have {COLOR 7}{COLOR 8}252 EVs!\nVery Hard!");
static const u8 sText_Description_Difficulty_Next[]                     = _("Continue to challenge options.");
static const u8 sText_Description_Challenges_LimitDifficulty_Off[]      = _("Change the difficulty whenever and\nwherever you want.");
static const u8 sText_Description_Challenges_LimitDifficulty_On[]       = _("Difficulty cannot be changed.\nHARD MODE locks BATTLE STYLE to SET.");
static const u8 sText_Description_Difficulty_MaxPartyIvs_Off[]          = _("Your POKéMON have the expected IVs\n(between 0 and 31).");
static const u8 sText_Description_Difficulty_MaxPartyIvs_On[]           = _("The IVs of your POKéMON are set\nalways to the maximum (31).");
static const u8 sText_Description_Difficulty_MaxPartyIvs_On_HP[]        = _("IVs are set between 30 and 31\nto allow different Hidden Powers.");
static const u8 sText_Description_Difficulty_LessEscapes_Off[]          = _("The player can easily run\naway from battles, as usual.");
static const u8 sText_Description_Difficulty_LessEscapes_On[]           = _("The player can't easily run\naway from battles. Use repels!");
static const u8 sText_Description_Difficulty_EscapeRopeDig_Off[]        = _("ESCAPE ROPE and DIG can't\nbe used to exit dungeons.");
static const u8 sText_Description_Difficulty_EscapeRopeDig_On[]         = _("ESCAPE ROPE and DIG can\nbe used to exit dungeons.");
//static const u8 sText_Description_Difficulty_HardExp_Enabled[]          = _("{PKMN} gain 60% of total EXP in HARD.\n{COLOR 7}{COLOR 8}RECOMMENDED, provides good challenge.");
//static const u8 sText_Description_Difficulty_HardExp_Disabled[]         = _("{PKMN} gain the default EXP in HARD. {COLOR 7}{COLOR 8}NOT\nRECOMMENDED, makes HARD MODE easy.");
static const u8 *const sOptionMenuItemDescriptionsDifficulty[MENUITEM_DIFFICULTY_COUNT][4] =
{
    [MENUITEM_DIFFICULTY_PARTY_LIMIT]           = {sText_Description_Difficulty_Party_Limit,        sText_Empty,                                        sText_Empty,                                    sText_Empty},
    [MENUITEM_DIFFICULTY_LEVEL_CAP]             = {sText_Description_Difficulty_LevelCap_Base,      sText_Description_Difficulty_LevelCap_Normal,       sText_Description_Difficulty_LevelCap_Hard,     sText_Empty},
    [MENUITEM_DIFFICULTY_EXP_MULTIPLIER]        = {sText_Description_Difficulty_ExpMultiplier_1_0,  sText_Description_Difficulty_ExpMultiplier_1_5,     sText_Description_Difficulty_ExpMultiplier_2_0, sText_Description_Difficulty_ExpMultiplier_0_0},
    [MENUITEM_DIFFICULTY_LESS_ESCAPES]          = {sText_Description_Difficulty_LessEscapes_Off,    sText_Description_Difficulty_LessEscapes_On,        sText_Empty,                                        sText_Empty},
    [MENUITEM_DIFFICULTY_ITEM_PLAYER]           = {sText_Description_Difficulty_Items_Player_Yes,   sText_Description_Difficulty_Items_Player_No,       sText_Empty,                                    sText_Empty},
    [MENUITEM_DIFFICULTY_ITEM_TRAINER]          = {sText_Description_Difficulty_Items_Trainer_Yes,  sText_Description_Difficulty_Items_Trainer_No,      sText_Empty,                                    sText_Empty},
    [MENUITEM_DIFFICULTY_NO_EVS]                = {sText_Description_Difficulty_NoEVs_Off,          sText_Description_Difficulty_NoEVs_On,              sText_Empty,                                    sText_Empty},
    [MENUITEM_DIFFICULTY_SCALING_IVS]           = {sText_Description_Difficulty_ScalingIVs_Off,     sText_Description_Difficulty_ScalingIVs_Scaling,    sText_Description_Difficulty_ScalingIVs_Hard,   sText_Empty},
    [MENUITEM_DIFFICULTY_SCALING_EVS]           = {sText_Description_Difficulty_ScalingEVs_Off,     sText_Description_Difficulty_ScalingEVs_Scaling,    sText_Description_Difficulty_ScalingEVs_Hard,   sText_Description_Difficulty_ScalingEVs_Extreme},
    [MENUITEM_DIFFICULTY_NEXT]                  = {sText_Description_Difficulty_Next,               sText_Empty,                                        sText_Empty,                                    sText_Empty},
    //[MENUITEM_DIFFICULTY_LIMIT_DIFFICULTY]      = {sText_Description_Challenges_LimitDifficulty_Off,    sText_Description_Challenges_LimitDifficulty_On,    sText_Empty,                                        sText_Empty},
    [MENUITEM_DIFFICULTY_ESCAPE_ROPE_DIG]       = {sText_Description_Difficulty_EscapeRopeDig_On,  sText_Description_Difficulty_EscapeRopeDig_Off,  sText_Empty,                                        sText_Empty},
    [MENUITEM_DIFFICULTY_MAX_PARTY_IVS]         = {sText_Description_Difficulty_MaxPartyIvs_Off,    sText_Description_Difficulty_MaxPartyIvs_On,    sText_Description_Difficulty_MaxPartyIvs_On_HP,                                        sText_Empty},
    //[MENUITEM_DIFFICULTY_HARD_EXP]              = {sText_Description_Difficulty_HardExp_Enabled,    sText_Description_Difficulty_HardExp_Disabled,    sText_Empty,                                        sText_Empty},
};  

static const u8 sText_Description_Difficulty_Pokecenter_Yes[]           = _("The player can visit Pokécenters and\nother locations to heal their party.");
static const u8 sText_Description_Difficulty_Pokecenter_No[]            = _("The player {COLOR 7}{COLOR 8}CAN'T visit Pokécenters or\nother locations to heal their party.");
static const u8 sText_Description_Challenges_PCHeal_Yes[]               = _("POKéMON deposited to the PC\nwill be healed as usual.");
static const u8 sText_Description_Challenges_PCHeal_No[]                = _("POKéMON deposited to the PC\nwill not be healed.");
static const u8 sText_Description_Challenges_EvoLimit_Base[]            = _("POKéMON evolve as expected.");
static const u8 sText_Description_Challenges_EvoLimit_First[]           = _("POKéMON can only evolve into\ntheir first evolution.");
static const u8 sText_Description_Challenges_EvoLimit_All[]             = _("POKéMON can {COLOR 7}{COLOR 8}NOT evolve at all!");
static const u8 sText_Description_Challenges_OneTypeChallenge[]         = _("Allow only one POKéMON type the\nplayer can capture and use.");
static const u8 sText_Description_Challenges_BaseStatEqualizer_Base[]   = _("All POKéMON have their original base\nstats.");
static const u8 sText_Description_Challenges_BaseStatEqualizer_100[]    = _("POKéMON stats are calculated with\n100 of each base stat.");
static const u8 sText_Description_Challenges_BaseStatEqualizer_255[]    = _("POKéMON stats are calculated with\n255 of each base stat.");
static const u8 sText_Description_Challenges_BaseStatEqualizer_500[]    = _("POKéMON stats are calculated with\n500 of each base stat.");
static const u8 sText_Description_Challenges_Mirror_Off[]               = _("The player uses their own party.");
static const u8 sText_Description_Challenges_Mirror_Trainer[]           = _("In Trainer battles, the player gets\na copy of the enemy's party!");
static const u8 sText_Description_Challenges_Mirror_All[]               = _("The player gets a copy of the\nenemy's party in {COLOR 7}{COLOR 8}ALL battles!");
static const u8 sText_Description_Challenges_MirrorThief_Off[]          = _("The player gets their own party back\nafter battles.");
static const u8 sText_Description_Challenges_MirrorThief_On[]           = _("The player keeps the enemies party\nafter battle!");
static const u8 sText_Description_Challenges_Expensive_0ff[]            = _("Everything has the usual cost.");
static const u8 sText_Description_Challenges_Expensive_5[]              = _("Everything is 5 times more\nexpensive!");
static const u8 sText_Description_Challenges_Expensive_10[]             = _("Everything is 10 times more\nexpensive! Good ol' capitalism.");
static const u8 sText_Description_Challenges_Expensive_50[]             = _("Everything is 50 times more\nexpensive! Ultra capitalism!");
static const u8 *const sOptionMenuItemDescriptionsChallenges[MENUITEM_CHALLENGES_COUNT][5] =
{
    [MENUITEM_DIFFICULTY_POKECENTER]            = {sText_Description_Difficulty_Pokecenter_Yes,         sText_Description_Difficulty_Pokecenter_No,         sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_CHALLENGES_PCHEAL]                = {sText_Description_Challenges_PCHeal_Yes,             sText_Description_Challenges_PCHeal_No,             sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_CHALLENGES_EXPENSIVE]             = {sText_Description_Challenges_Expensive_0ff,          sText_Description_Challenges_Expensive_5,           sText_Description_Challenges_Expensive_10,          sText_Description_Challenges_Expensive_50,          sText_Empty},
    [MENUITEM_CHALLENGES_EVO_LIMIT]             = {sText_Description_Challenges_EvoLimit_Base,          sText_Description_Challenges_EvoLimit_First,        sText_Description_Challenges_EvoLimit_All,          sText_Empty,                                        sText_Empty},
    [MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE]    = {sText_Description_Challenges_OneTypeChallenge,       sText_Empty,                                        sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_CHALLENGES_BASE_STAT_EQUALIZER]   = {sText_Description_Challenges_BaseStatEqualizer_Base, sText_Description_Challenges_BaseStatEqualizer_100, sText_Description_Challenges_BaseStatEqualizer_255, sText_Description_Challenges_BaseStatEqualizer_500, sText_Empty},
    [MENUITEM_CHALLENGES_MIRROR]                = {sText_Description_Challenges_Mirror_Off,             sText_Description_Challenges_Mirror_Trainer,        sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_CHALLENGES_MIRROR_THIEF]          = {sText_Description_Challenges_MirrorThief_Off,        sText_Description_Challenges_MirrorThief_On,        sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_CHALLENGES_SAVE]                  = {sText_Description_Save,                              sText_Empty,                                        sText_Empty,                                        sText_Empty,                                        sText_Empty},
};

// Disabled descriptions
static const u8 sText_Description_Disabled_Feature[]  = _("{COLOR 7}{COLOR 8}This feature is not currently\nsupported for this game.");
static const u8 *const sOptionMenuItemDescriptionsDisabledMode[MENUITEM_MODE_COUNT] =
{
    [MENUITEM_MODE_CLASSIC_MODERN]        = sText_Empty,
    //[MENUITEM_MODE_ALTERNATE_SPAWNS]      = sText_Empty,
    [MENUITEM_MODE_INFINITE_TMS]          = sText_Empty,
    [MENUITEM_MODE_SURVIVE_POISON]        = sText_Empty,
    [MENUITEM_MODE_SYNCHRONIZE]           = sText_Empty,
    [MENUITEM_MODE_STURDY]                = sText_Empty,
    [MENUITEM_MODE_MINTS]                 = sText_Empty,
    [MENUITEM_MODE_NEW_CITRUS]            = sText_Empty,
    [MENUITEM_MODE_MODERN_TYPES]          = sText_Description_Disabled_Feature,
    [MENUITEM_MODE_FAIRY_TYPES]           = sText_Empty,
    [MENUITEM_MODE_NEW_STATS]             = sText_Description_Disabled_Feature,
    [MENUITEM_MODE_MODERN_MOVES]          = sText_Empty,
    [MENUITEM_MODE_NEXT]                  = sText_Empty,
    [MENUITEM_MODE_LEGENDARY_ABILITIES]   = sText_Empty,
    [MENUITEM_MODE_NEW_LEGENDARIES]       = sText_Description_Disabled_Feature,
    [MENUITEM_MODE_NEW_EFFECTIVENESS]     = sText_Empty,
};

// Disabled descriptions
static const u8 sText_Description_Disabled_Features_PkmnDeath[]  = _("Already enabled via\nthe Nuzlocke Challenge.");
static const u8 *const sOptionMenuItemDescriptionsDisabledFeatures[MENUITEM_FEATURES_COUNT] =
{
    [MENUITEM_FEATURES_RTC_TYPE]              = sText_Empty,
    [MENUITEM_FEATURES_SHINY_CHANCE]          = sText_Empty,
    [MENUITEM_FEATURES_ITEM_DROP]             = sText_Empty,
    //[MENUITEM_FEATURES_EASY_FEEBAS]           = sText_Description_Disabled_Feature,
    [MENUITEM_FEATURES_PKMN_DEATH]            = sText_Description_Disabled_Features_PkmnDeath,
    [MENUITEM_FEATURES_UNLIMITED_WT]          = sText_Description_Disabled_Feature,
    [MENUITEM_FEATURES_FRONTIER_BANS]         = sText_Description_Disabled_Feature,
    [MENUITEM_FEATURES_NEXT]                  = sText_Empty,
};

static const u8 sText_Description_Disabled_Random_SimiliarEvolutionLevel[]  = _("Only usable with random starter,\nTrainer, wild or static POKéMON.");
static const u8 sText_Description_Disabled_Random_IncludeLegendaries[]      = _("Only usable with random starter,\nTrainer, wild or static POKéMON.");
static const u8 sText_Description_Disabled_Random_Chaos_Mode[]              = _("Only usable if other random options\nare activated.");
static const u8 sText_Description_Disabled_Random_Type_Effectiveness[]      = _("Currently not available.");
static const u8 *const sOptionMenuItemDescriptionsDisabledRandomizer[MENUITEM_RANDOM_COUNT] =
{
    [MENUITEM_RANDOM_OFF_ON]                    = sText_Empty,
    [MENUITEM_RANDOM_STARTER]                   = sText_Empty,
    [MENUITEM_RANDOM_WILD_PKMN]                 = sText_Empty,
    [MENUITEM_RANDOM_TRAINER]                   = sText_Empty,
    [MENUITEM_RANDOM_STATIC]                    = sText_Empty,
    [MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL]   = sText_Description_Disabled_Random_SimiliarEvolutionLevel,
    [MENUITEM_RANDOM_INCLUDE_LEGENDARIES]       = sText_Description_Disabled_Random_IncludeLegendaries,
    [MENUITEM_RANDOM_TYPE]                      = sText_Empty,
    [MENUITEM_RANDOM_MOVES]                     = sText_Empty,
    [MENUITEM_RANDOM_ABILITIES]                 = sText_Empty,
    [MENUITEM_RANDOM_EVOLUTIONS]                = sText_Empty,
    [MENUITEM_RANDOM_EVOLUTIONS_METHODS]        = sText_Empty,
    [MENUITEM_RANDOM_TYPE_EFFEC]                = sText_Description_Disabled_Random_Type_Effectiveness,
    [MENUITEM_RANDOM_ITEMS]                     = sText_Empty,
    [MENUITEM_RANDOM_CHAOS]                     = sText_Description_Disabled_Random_Chaos_Mode,
    [MENUITEM_RANDOM_NEXT]                      = sText_Empty,
};

static const u8 sText_Description_Disabled_Nuzlocke_Nuzlocke[]   = _("Only usable with Nuzlocke!");
static const u8 *const sOptionMenuItemDescriptionsDisabledNuzlocke[MENUITEM_NUZLOCKE_COUNT] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]            = sText_Empty,
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]      = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]        = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_NICKNAMING]          = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_DELETION]            = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_NEXT]                = sText_Empty,
};

static const u8 *const sOptionMenuItemDescriptionsDisabledDifficulty[MENUITEM_DIFFICULTY_COUNT] =
{
    [MENUITEM_DIFFICULTY_PARTY_LIMIT]           = sText_Empty,
    [MENUITEM_DIFFICULTY_LESS_ESCAPES]          = sText_Empty,
    [MENUITEM_DIFFICULTY_LEVEL_CAP]             = sText_Empty,
    [MENUITEM_DIFFICULTY_EXP_MULTIPLIER]        = sText_Empty,
    [MENUITEM_DIFFICULTY_ITEM_PLAYER]           = sText_Empty,
    [MENUITEM_DIFFICULTY_ITEM_TRAINER]          = sText_Empty,
    [MENUITEM_DIFFICULTY_NO_EVS]                = sText_Empty,
    [MENUITEM_DIFFICULTY_SCALING_IVS]           = sText_Empty,
    [MENUITEM_DIFFICULTY_SCALING_EVS]           = sText_Empty,
    [MENUITEM_DIFFICULTY_NEXT]                  = sText_Empty,
};  

static const u8 sText_Description_Disabled_Challenges_MirrorThief[]    = _("Only usable with Mirror Mode!");
static const u8 sText_Description_Disabled_Features_PCHeal[]  = _("Always disabled with POKéCENTER\nChallenge.");
static const u8 *const sOptionMenuItemDescriptionsDisabledChallenges[MENUITEM_CHALLENGES_COUNT] =
{
    [MENUITEM_DIFFICULTY_POKECENTER]            = sText_Empty,
    [MENUITEM_CHALLENGES_PCHEAL]                = sText_Description_Disabled_Features_PCHeal,
    [MENUITEM_CHALLENGES_EVO_LIMIT]             = sText_Empty,
    [MENUITEM_CHALLENGES_EXPENSIVE]             = sText_Empty,
    [MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE]    = sText_Empty,
    [MENUITEM_CHALLENGES_BASE_STAT_EQUALIZER]   = sText_Empty,
    [MENUITEM_CHALLENGES_MIRROR]                = sText_Empty,
    [MENUITEM_CHALLENGES_MIRROR_THIEF]          = sText_Description_Disabled_Challenges_MirrorThief,
    [MENUITEM_CHALLENGES_SAVE]                  = sText_Empty,
};

// Functions to dynamically retrieve data
static const u8 *const OptionTextDescription(void)
{
    u8 menuItem = sOptions->menuCursor[sOptions->submenu];
    u8 selection;

    switch (sOptions->submenu)
    {
    case MENU_MODE:
        if (!CheckConditions(menuItem) && sOptionMenuItemDescriptionsDisabledMode[menuItem] != sText_Empty)
            return sOptionMenuItemDescriptionsDisabledMode[menuItem];
        selection = sOptions->sel_mode[menuItem];  
        return sOptionMenuItemDescriptionsMode[menuItem][selection];
    case MENU_FEATURES:
        if (!CheckConditions(menuItem) && sOptionMenuItemDescriptionsDisabledFeatures[menuItem] != sText_Empty)
            return sOptionMenuItemDescriptionsDisabledFeatures[menuItem];
        selection = sOptions->sel_features[menuItem];  
        return sOptionMenuItemDescriptionsFeatures[menuItem][selection];
    case MENU_RANDOMIZER:
        if (!CheckConditions(menuItem) && sOptionMenuItemDescriptionsDisabledRandomizer[menuItem] != sText_Empty)
            return sOptionMenuItemDescriptionsDisabledRandomizer[menuItem];
        selection = sOptions->sel_randomizer[menuItem];  
        return sOptionMenuItemDescriptionsRandomizer[menuItem][selection];
    case MENU_NUZLOCKE:
        if (!CheckConditions(menuItem) && sOptionMenuItemDescriptionsDisabledNuzlocke[menuItem] != sText_Empty)
            return sOptionMenuItemDescriptionsDisabledNuzlocke[menuItem];
        selection = sOptions->sel_nuzlocke[menuItem];
        return sOptionMenuItemDescriptionsNuzlocke[menuItem][selection];
    case MENU_DIFFICULTY:
        if (!CheckConditions(menuItem) && sOptionMenuItemDescriptionsDisabledDifficulty[menuItem] != sText_Empty)
            return sOptionMenuItemDescriptionsDisabledDifficulty[menuItem];
        selection = sOptions->sel_difficulty[menuItem];
        if (sOptions->menuCursor[MENU_DIFFICULTY] == MENUITEM_DIFFICULTY_PARTY_LIMIT)
            return sOptionMenuItemDescriptionsDifficulty[menuItem][0];
        else
            return sOptionMenuItemDescriptionsDifficulty[menuItem][selection];
    case MENU_CHALLENGES:
        if (!CheckConditions(menuItem) && sOptionMenuItemDescriptionsDisabledChallenges[menuItem] != sText_Empty)
            return sOptionMenuItemDescriptionsDisabledChallenges[menuItem];
        selection = sOptions->sel_challenges[menuItem];
        if (sOptions->menuCursor[MENU_CHALLENGES] == MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE)
            return sOptionMenuItemDescriptionsChallenges[menuItem][0];
        else
            return sOptionMenuItemDescriptionsChallenges[menuItem][selection];
    }
}

static u8 MenuItemCount(void)
{
    switch (sOptions->submenu)
    {
    case MENU_MODE:         return MENUITEM_MODE_COUNT;
    case MENU_FEATURES:     return MENUITEM_FEATURES_COUNT;
    case MENU_RANDOMIZER:   return MENUITEM_RANDOM_COUNT;
    case MENU_NUZLOCKE:     return MENUITEM_NUZLOCKE_COUNT;
    case MENU_DIFFICULTY:   return MENUITEM_DIFFICULTY_COUNT;
    case MENU_CHALLENGES:   return MENUITEM_CHALLENGES_COUNT;
    }
}

static u8 MenuItemCountFromIndex(u8 index)
{
    switch (index)
    {
    case MENU_MODE:         return MENUITEM_MODE_COUNT; 
    case MENU_FEATURES:     return MENUITEM_FEATURES_COUNT; 
    case MENU_RANDOMIZER:   return MENUITEM_RANDOM_COUNT;
    case MENU_NUZLOCKE:     return MENUITEM_NUZLOCKE_COUNT;
    case MENU_DIFFICULTY:   return MENUITEM_DIFFICULTY_COUNT;
    case MENU_CHALLENGES:   return MENUITEM_CHALLENGES_COUNT;
    }
}

static u8 MenuItemCancel(void)
{
    switch (sOptions->submenu)
    {
    case MENU_MODE:         return MENUITEM_MODE_NEXT;
    case MENU_FEATURES:     return MENUITEM_FEATURES_NEXT;
    case MENU_RANDOMIZER:   return MENUITEM_RANDOM_NEXT;
    case MENU_NUZLOCKE:     return MENUITEM_NUZLOCKE_NEXT;
    case MENU_DIFFICULTY:   return MENUITEM_DIFFICULTY_NEXT;
    case MENU_CHALLENGES:   return MENUITEM_CHALLENGES_SAVE;
    }
}

// Main code
static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static const u8 sText_TopBar_Left[]             = _("{L_BUTTON}PREVIOUS");
static const u8 sText_TopBar_Right[]            = _("{R_BUTTON}NEXT");
static const u8 sText_TopBar_Mode[]             = _("GAMEMODE");
static const u8 sText_TopBar_Features[]         = _("FEATURES");
static const u8 sText_TopBar_Randomizer[]       = _("RANDOMIZER");
static const u8 sText_TopBar_Nuzlocke[]         = _("NUZLOCKE");
static const u8 sText_TopBar_Difficulty[]       = _("DIFFICULTY");
static const u8 sText_TopBar_Challenges[]       = _("CHALLENGES");
static void DrawTopBarText(void)
{
    const u8 color[3] = { TEXT_DYNAMIC_COLOR_6, TEXT_COLOR_WHITE, TEXT_COLOR_OPTIONS_GRAY_FG };
    int width = 0;
    int right = 240 - GetStringWidth(FONT_SMALL, sText_TopBar_Right, 0) - 5;

    FillWindowPixelBuffer(WIN_TOPBAR, PIXEL_FILL(15));
    switch (sOptions->submenu)
    {
        case MENU_MODE:
            width = GetStringWidth(FONT_SMALL, sText_TopBar_Mode, 0) / 2;
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 120-width, 1, color, 0, sText_TopBar_Mode);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, right, 1, color, 0, sText_TopBar_Right);
            break;
        case MENU_FEATURES:
            width = GetStringWidth(FONT_SMALL, sText_TopBar_Features, 0) / 2;
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 5, 1, color, 0, sText_TopBar_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 120-width, 1, color, 0, sText_TopBar_Features);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, right, 1, color, 0, sText_TopBar_Right);
            break;
        case MENU_RANDOMIZER:
            width = GetStringWidth(FONT_SMALL, sText_TopBar_Randomizer, 0) / 2;
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 5, 1, color, 0, sText_TopBar_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 120-width, 1, color, 0, sText_TopBar_Randomizer);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, right, 1, color, 0, sText_TopBar_Right);
            break;
        case MENU_NUZLOCKE:
            width = GetStringWidth(FONT_SMALL, sText_TopBar_Nuzlocke, 0) / 2;
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 5, 1, color, 0, sText_TopBar_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 120-width, 1, color, 0, sText_TopBar_Nuzlocke);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, right, 1, color, 0, sText_TopBar_Right);
            break;
        case MENU_DIFFICULTY:
            width = GetStringWidth(FONT_SMALL, sText_TopBar_Difficulty, 0) / 2;
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 5, 1, color, 0, sText_TopBar_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 120-width, 1, color, 0, sText_TopBar_Difficulty);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, right, 1, color, 0, sText_TopBar_Right);
            break;
        case MENU_CHALLENGES:
            width = GetStringWidth(FONT_SMALL, sText_TopBar_Challenges, 0) / 2;
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 5, 1, color, 0, sText_TopBar_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 120-width, 1, color, 0, sText_TopBar_Challenges);
            break;
    }
    PutWindowTilemap(WIN_TOPBAR);
    CopyWindowToVram(WIN_TOPBAR, COPYWIN_FULL);
}

static void DrawOptionMenuTexts(void) //left side text
{
    u8 i;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < MenuItemCount(); i++)
        DrawLeftSideOptionText(i, (i * Y_DIFF) + 1);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static void DrawDescriptionText(void)
{
    u8 color_gray[3];
    color_gray[0] = TEXT_COLOR_TRANSPARENT;
    color_gray[1] = TEXT_COLOR_OPTIONS_GRAY_FG;
    color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;
        
    FillWindowPixelBuffer(WIN_DESCRIPTION, PIXEL_FILL(1));
    AddTextPrinterParameterized4(WIN_DESCRIPTION, FONT_NORMAL, 8, 1, 0, 0, color_gray, TEXT_SKIP_DRAW, OptionTextDescription());
    CopyWindowToVram(WIN_DESCRIPTION, COPYWIN_FULL);
}

static void DrawLeftSideOptionText(int selection, int y)
{
    u8 color_yellow[3];
    u8 color_gray[3];

    color_yellow[0] = TEXT_COLOR_TRANSPARENT;
    color_yellow[1] = TEXT_COLOR_OPTIONS_ORANGE_FG;
    color_yellow[2] = TEXT_COLOR_OPTIONS_ORANGE_SHADOW;
    color_gray[0] = TEXT_COLOR_TRANSPARENT;
    color_gray[1] = TEXT_COLOR_OPTIONS_GRAY_LIGHT_FG;
    color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;

    if (CheckConditions(selection))
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y, 0, 0, color_yellow, TEXT_SKIP_DRAW, OptionTextRight(selection));
    else
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y, 0, 0, color_gray, TEXT_SKIP_DRAW, OptionTextRight(selection));
}

static void DrawRightSideChoiceText(const u8 *text, int x, int y, bool8 choosen, bool8 active)
{
    u8 color_red[3];
    u8 color_gray[3];

    if (active)
    {
        color_red[0] = TEXT_COLOR_TRANSPARENT;
        color_red[1] = TEXT_COLOR_OPTIONS_RED_FG;
        color_red[2] = TEXT_COLOR_OPTIONS_RED_SHADOW;
        color_gray[0] = TEXT_COLOR_TRANSPARENT;
        color_gray[1] = TEXT_COLOR_OPTIONS_GRAY_FG;
        color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;
    }
    else
    {
        color_red[0] = TEXT_COLOR_TRANSPARENT;
        color_red[1] = TEXT_COLOR_OPTIONS_RED_DARK_FG;
        color_red[2] = TEXT_COLOR_OPTIONS_RED_DARK_SHADOW;
        color_gray[0] = TEXT_COLOR_TRANSPARENT;
        color_gray[1] = TEXT_COLOR_OPTIONS_GRAY_LIGHT_FG;
        color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;
    }


    if (choosen)
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, x, y, 0, 0, color_red, TEXT_SKIP_DRAW, text);
    else
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, x, y, 0, 0, color_gray, TEXT_SKIP_DRAW, text);
}

static void DrawChoices(u32 id, int y) //right side draw function
{
    switch (sOptions->submenu)
    {
        case MENU_MODE:
            if (sItemFunctionsMode[id].drawChoices != NULL)
                sItemFunctionsMode[id].drawChoices(sOptions->sel_mode[id], y);
            break;
        case MENU_FEATURES:
            if (sItemFunctionsFeatures[id].drawChoices != NULL)
                sItemFunctionsFeatures[id].drawChoices(sOptions->sel_features[id], y);
            break;
        case MENU_RANDOMIZER:
            if (sItemFunctionsRandom[id].drawChoices != NULL)
                sItemFunctionsRandom[id].drawChoices(sOptions->sel_randomizer[id], y);
            break;
        case MENU_NUZLOCKE:
            if (sItemFunctionsNuzlocke[id].drawChoices != NULL)
                sItemFunctionsNuzlocke[id].drawChoices(sOptions->sel_nuzlocke[id], y);
            break;
        case MENU_DIFFICULTY:
            if (sItemFunctionsDifficulty[id].drawChoices != NULL)
                sItemFunctionsDifficulty[id].drawChoices(sOptions->sel_difficulty[id], y);
            break;
        case MENU_CHALLENGES:
            if (sItemFunctionsChallenges[id].drawChoices != NULL)
                sItemFunctionsChallenges[id].drawChoices(sOptions->sel_challenges[id], y);
            break;
    }
}

static void HighlightOptionMenuItem(void)
{
    int cursor = sOptions->visibleCursor[sOptions->submenu];

    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(Y_DIFF, 224));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(cursor * Y_DIFF + 24, cursor * Y_DIFF + 40));
}

void CB2_InitTxRandomizerChallengesMenu(void)
{
    u32 i, taskId;
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void*)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sOptionMenuBgTemplates, ARRAY_COUNT(sOptionMenuBgTemplates));
        ResetBgPositions();
        InitWindows(sOptionMenuWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0 | WININ_WIN1_BG0 | WININ_WIN0_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sOptionMenuBg_Pal, 0, sizeof(sOptionMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, 0x70, 0x20);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sOptionMenuText_Pal, 16, sizeof(sOptionMenuText_Pal));
        gMain.state++;
        break;
    case 6:
        //tx_randomizer_and_challenges
        //gSaveBlock1Ptr->tx_Mode_AlternateSpawns                  = tx_Mode_AlternateSpawns;
        gSaveBlock1Ptr->tx_Mode_InfiniteTMs                 = TX_MODE_INFINITE_TMS;
        gSaveBlock1Ptr->tx_Mode_PoisonSurvive               = TX_MODE_SURVIVE_POISON;
        gSaveBlock1Ptr->tx_Mode_Synchronize                 = TX_MODE_NEW_SYNCHRONIZE;
        gSaveBlock1Ptr->tx_Mode_Mints                       = TX_MODE_MINTS;
        gSaveBlock1Ptr->tx_Mode_New_Citrus                  = TX_MODE_NEW_CITRUS;
        gSaveBlock1Ptr->tx_Mode_Modern_Types                = TX_MODE_MODERN_TYPES;
        gSaveBlock1Ptr->tx_Mode_Fairy_Types                 = TX_MODE_FAIRY_TYPES;
        gSaveBlock1Ptr->tx_Mode_New_Stats                   = TX_MODE_NEW_STATS;
        gSaveBlock1Ptr->tx_Mode_Sturdy                      = TX_MODE_STURDY;
        gSaveBlock1Ptr->tx_Mode_Modern_Moves                = TX_MODE_MODERN_MOVES;
        gSaveBlock1Ptr->tx_Mode_Legendary_Abilities         = TX_MODE_LEGENDARY_ABILITIES;
        gSaveBlock1Ptr->tx_Mode_New_Legendaries             = TX_MODE_NEW_LEGENDARIES;
        gSaveBlock1Ptr->tx_Mode_TypeEffectiveness           = TX_MODE_TYPE_EFFECTIVENESS;

        gSaveBlock1Ptr->tx_Features_RTCType                 = TX_FEATURES_RTC_TYPE;
        gSaveBlock1Ptr->tx_Features_ShinyChance             = TX_FEATURES_SHINY_CHANCE;
        gSaveBlock1Ptr->tx_Features_WildMonDropItems        = TX_FEATURES_ITEM_DROP;
        //gSaveBlock1Ptr->tx_Features_EasierFeebas            = TX_FEATURES_EASIER_FEEBAS;
        gSaveBlock1Ptr->tx_Features_PkmnDeath               = TX_FEATURES_PKMN_DEATH;
        gSaveBlock1Ptr->tx_Features_Unlimited_WT            = TX_FEATURES_UNLIMITED_WT;
        gSaveBlock1Ptr->tx_Features_FrontierBans            = TX_FEATURES_FRONTIER_BANS;

        gSaveBlock1Ptr->tx_Random_Starter                   = TX_RANDOM_STARTER;
        gSaveBlock1Ptr->tx_Random_WildPokemon               = TX_RANDOM_WILD_POKEMON;
        gSaveBlock1Ptr->tx_Random_Trainer                   = TX_RANDOM_TRAINER;
        gSaveBlock1Ptr->tx_Random_Static                    = TX_RANDOM_STATIC;
        gSaveBlock1Ptr->tx_Random_Similar                   = TX_RANDOM_SIMILAR;
        gSaveBlock1Ptr->tx_Random_MapBased                  = TX_RANDOM_MAP_BASED;
        gSaveBlock1Ptr->tx_Random_IncludeLegendaries        = TX_RANDOM_INCLUDE_LEGENDARIES;
        gSaveBlock1Ptr->tx_Random_Type                      = TX_RANDOM_TYPE;
        gSaveBlock1Ptr->tx_Random_Moves                     = TX_RANDOM_MOVES;
        gSaveBlock1Ptr->tx_Random_Abilities                 = TX_RANDOM_ABILITIES;
        gSaveBlock1Ptr->tx_Random_Evolutions                = TX_RANDOM_EVOLUTION;
        gSaveBlock1Ptr->tx_Random_EvolutionMethods          = TX_RANDOM_EVOLUTION_METHODE;
        gSaveBlock1Ptr->tx_Random_TypeEffectiveness         = TX_RANDOM_TYPE_EFFECTIVENESS;
        gSaveBlock1Ptr->tx_Random_Items                     = TX_RANDOM_ITEMS;
        gSaveBlock1Ptr->tx_Random_Chaos                     = TX_RANDOM_CHAOS_MODE;
        gSaveBlock1Ptr->tx_Challenges_LessEscapes           = TX_CHALLENGES_LESS_ESCAPES;

        gSaveBlock1Ptr->tx_Challenges_Nuzlocke              = TX_NUZLOCKE_NUZLOCKE;
        gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore      = TX_NUZLOCKE_NUZLOCKE_HARDCORE;
        gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause           = TX_NUZLOCKE_SPECIES_CLAUSE;
        gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause             = TX_NUZLOCKE_SHINY_CLAUSE;
        gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming              = TX_NUZLOCKE_NICKNAMING;
        gSaveBlock1Ptr->tx_Nuzlocke_Deletion                = TX_NUZLOCKE_DELETION;
    
        gSaveBlock1Ptr->tx_Challenges_PartyLimit            = TX_DIFFICULTY_PARTY_LIMIT;
        gSaveBlock1Ptr->tx_Challenges_LevelCap              = TX_DIFFICULTY_LEVEL_CAP;
        gSaveBlock1Ptr->tx_Challenges_ExpMultiplier         = TX_DIFFICULTY_EXP_MULTIPLIER;
        gSaveBlock1Ptr->tx_Challenges_NoItemPlayer          = TX_DIFFICULTY_NO_ITEM_PLAYER;
        gSaveBlock1Ptr->tx_Challenges_NoItemTrainer         = TX_DIFFICULTY_NO_ITEM_TRAINER;
        gSaveBlock1Ptr->tx_Challenges_NoEVs                 = TX_DIFFICULTY_NO_EVS;
        gSaveBlock1Ptr->tx_Challenges_TrainerScalingIVs     = TX_DIFFICULTY_SCALING_IVS;
        gSaveBlock1Ptr->tx_Challenges_TrainerScalingEVs     = TX_DIFFICULTY_SCALING_EVS;
        gSaveBlock1Ptr->tx_Challenges_PkmnCenter            = TX_DIFFICULTY_PKMN_CENTER;
        //gSaveBlock1Ptr->tx_Features_LimitDifficulty         = TX_DIFFICULTY_LIMIT_DIFFICULTY;
        gSaveBlock1Ptr->tx_Challenges_MaxPartyIVs           = TX_DIFFICULTY_MAX_PARTY_IVS;
        gSaveBlock1Ptr->tx_Difficulty_EscapeRopeDig         = TX_DIFFICULTY_ESCAPE_ROPE_DIG;
        //gSaveBlock1Ptr->tx_Difficulty_HardExp               = TX_DIFFICULTY_HARD_EXP;

        gSaveBlock1Ptr->tx_Challenges_PCHeal                = TX_CHALLENGE_PCHEAL;
        gSaveBlock1Ptr->tx_Challenges_Expensive             = TX_CHALLENGES_EXPENSIVE;
        gSaveBlock1Ptr->tx_Challenges_EvoLimit              = TX_CHALLENGE_EVO_LIMIT;
        gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge      = TX_CHALLENGE_TYPE;
        gSaveBlock1Ptr->tx_Challenges_BaseStatEqualizer     = TX_CHALLENGE_BASE_STAT_EQUALIZER;
        gSaveBlock1Ptr->tx_Challenges_Mirror                = TX_CHALLENGE_MIRROR;
        gSaveBlock1Ptr->tx_Challenges_Mirror_Thief          = TX_CHALLENGE_MIRROR_THIEF;
               

        sOptions = AllocZeroed(sizeof(*sOptions));
        //MENU MODE
        sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN]         = FALSE;
        //sOptions->sel_mode[MENUITEM_MODE_ALTERNATE_SPAWNS]       = gSaveBlock1Ptr->tx_Mode_AlternateSpawns;
        sOptions->sel_mode[MENUITEM_MODE_INFINITE_TMS]           = gSaveBlock1Ptr->tx_Mode_InfiniteTMs;
        sOptions->sel_mode[MENUITEM_MODE_SURVIVE_POISON]         = gSaveBlock1Ptr->tx_Mode_PoisonSurvive;  
        sOptions->sel_mode[MENUITEM_MODE_SYNCHRONIZE]            = gSaveBlock1Ptr->tx_Mode_Synchronize;
        sOptions->sel_mode[MENUITEM_MODE_MINTS]                  = gSaveBlock1Ptr->tx_Mode_Mints;
        sOptions->sel_mode[MENUITEM_MODE_NEW_CITRUS]             = gSaveBlock1Ptr->tx_Mode_New_Citrus;
        sOptions->sel_mode[MENUITEM_MODE_MODERN_TYPES]           = gSaveBlock1Ptr->tx_Mode_Modern_Types;
        sOptions->sel_mode[MENUITEM_MODE_FAIRY_TYPES]            = gSaveBlock1Ptr->tx_Mode_Fairy_Types;
        sOptions->sel_mode[MENUITEM_MODE_NEW_STATS]              = gSaveBlock1Ptr->tx_Mode_New_Stats;
        sOptions->sel_mode[MENUITEM_MODE_STURDY]                 = gSaveBlock1Ptr->tx_Mode_Sturdy;
        sOptions->sel_mode[MENUITEM_MODE_MODERN_MOVES]           = gSaveBlock1Ptr->tx_Mode_Modern_Moves;
        sOptions->sel_mode[MENUITEM_MODE_LEGENDARY_ABILITIES]    = gSaveBlock1Ptr->tx_Mode_Legendary_Abilities;
        sOptions->sel_mode[MENUITEM_MODE_NEW_LEGENDARIES]        = gSaveBlock1Ptr->tx_Mode_New_Legendaries;
        sOptions->sel_mode[MENUITEM_MODE_NEW_EFFECTIVENESS]      = gSaveBlock1Ptr->tx_Mode_TypeEffectiveness;
        //MENU FEATURES
        sOptions->sel_features[MENUITEM_FEATURES_RTC_TYPE]               = gSaveBlock1Ptr->tx_Features_RTCType;
        sOptions->sel_features[MENUITEM_FEATURES_SHINY_CHANCE]           = gSaveBlock1Ptr->tx_Features_ShinyChance;
        sOptions->sel_features[MENUITEM_FEATURES_ITEM_DROP]              = gSaveBlock1Ptr->tx_Features_WildMonDropItems;
        //sOptions->sel_features[MENUITEM_FEATURES_EASY_FEEBAS]            = gSaveBlock1Ptr->tx_Features_EasierFeebas;
        sOptions->sel_features[MENUITEM_FEATURES_PKMN_DEATH]             = gSaveBlock1Ptr->tx_Features_PkmnDeath;
        sOptions->sel_features[MENUITEM_FEATURES_UNLIMITED_WT]           = gSaveBlock1Ptr->tx_Features_Unlimited_WT;
        sOptions->sel_features[MENUITEM_FEATURES_FRONTIER_BANS]          = gSaveBlock1Ptr->tx_Features_FrontierBans;
        
        //MENU RANDOMIZER
        sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON]                     = FALSE;
        sOptions->sel_randomizer[MENUITEM_RANDOM_STARTER]                    = gSaveBlock1Ptr->tx_Random_Starter;
        sOptions->sel_randomizer[MENUITEM_RANDOM_WILD_PKMN]                  = gSaveBlock1Ptr->tx_Random_WildPokemon;
        sOptions->sel_randomizer[MENUITEM_RANDOM_TRAINER]                    = gSaveBlock1Ptr->tx_Random_Trainer;
        sOptions->sel_randomizer[MENUITEM_RANDOM_STATIC]                     = gSaveBlock1Ptr->tx_Random_Static;
        sOptions->sel_randomizer[MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL]    = !gSaveBlock1Ptr->tx_Random_Similar;
        sOptions->sel_randomizer[MENUITEM_RANDOM_INCLUDE_LEGENDARIES]        = gSaveBlock1Ptr->tx_Random_IncludeLegendaries;
        sOptions->sel_randomizer[MENUITEM_RANDOM_TYPE]                       = gSaveBlock1Ptr->tx_Random_Type;
        sOptions->sel_randomizer[MENUITEM_RANDOM_MOVES]                      = gSaveBlock1Ptr->tx_Random_Moves;
        sOptions->sel_randomizer[MENUITEM_RANDOM_ABILITIES]                  = gSaveBlock1Ptr->tx_Random_Abilities;
        sOptions->sel_randomizer[MENUITEM_RANDOM_EVOLUTIONS]                 = gSaveBlock1Ptr->tx_Random_Evolutions;
        sOptions->sel_randomizer[MENUITEM_RANDOM_EVOLUTIONS_METHODS]         = gSaveBlock1Ptr->tx_Random_EvolutionMethods;
        sOptions->sel_randomizer[MENUITEM_RANDOM_TYPE_EFFEC]                 = gSaveBlock1Ptr->tx_Random_TypeEffectiveness;
        sOptions->sel_randomizer[MENUITEM_RANDOM_ITEMS]                      = gSaveBlock1Ptr->tx_Random_Items;
        sOptions->sel_randomizer[MENUITEM_RANDOM_CHAOS]                      = gSaveBlock1Ptr->tx_Random_Chaos;

        // MENU_NUZLOCKE
        if (gSaveBlock1Ptr->tx_Challenges_Nuzlocke && gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore)
            sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE] = 2;
        else if (gSaveBlock1Ptr->tx_Challenges_Nuzlocke)
            sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE] = 1;
        else
            sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE] = 0;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SPECIES_CLAUSE]    = !gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SHINY_CLAUSE]      = !gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NICKNAMING]        = !gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_DELETION]          = gSaveBlock1Ptr->tx_Nuzlocke_Deletion;
        
        // MENU_DIFFICULTY
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_PARTY_LIMIT]    = gSaveBlock1Ptr->tx_Challenges_PartyLimit;
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_LEVEL_CAP]      = gSaveBlock1Ptr->tx_Challenges_LevelCap;
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_EXP_MULTIPLIER] = gSaveBlock1Ptr->tx_Challenges_ExpMultiplier;
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_LESS_ESCAPES]   = gSaveBlock1Ptr->tx_Challenges_LessEscapes;
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_ITEM_PLAYER]    = gSaveBlock1Ptr->tx_Challenges_NoItemPlayer;
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_ITEM_TRAINER]   = gSaveBlock1Ptr->tx_Challenges_NoItemTrainer;
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_NO_EVS]         = gSaveBlock1Ptr->tx_Challenges_NoEVs;
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_SCALING_IVS]    = gSaveBlock1Ptr->tx_Challenges_TrainerScalingIVs;
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_SCALING_EVS]    = gSaveBlock1Ptr->tx_Challenges_TrainerScalingEVs; 
        //sOptions->sel_difficulty[MENUITEM_DIFFICULTY_LIMIT_DIFFICULTY]      = gSaveBlock1Ptr->tx_Features_LimitDifficulty;
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_MAX_PARTY_IVS]         = gSaveBlock1Ptr->tx_Challenges_MaxPartyIVs;
        sOptions->sel_difficulty[MENUITEM_DIFFICULTY_ESCAPE_ROPE_DIG]       = gSaveBlock1Ptr->tx_Difficulty_EscapeRopeDig;
        //sOptions->sel_difficulty[MENUITEM_DIFFICULTY_HARD_EXP]              = gSaveBlock1Ptr->tx_Difficulty_HardExp;
        // MENU_CHALLENGES
        sOptions->sel_challenges[MENUITEM_DIFFICULTY_POKECENTER]             = gSaveBlock1Ptr->tx_Challenges_PkmnCenter;
        sOptions->sel_challenges[MENUITEM_CHALLENGES_PCHEAL]                 = gSaveBlock1Ptr->tx_Challenges_PCHeal;
        sOptions->sel_challenges[MENUITEM_CHALLENGES_EXPENSIVE]              = gSaveBlock1Ptr->tx_Challenges_Expensive;
        sOptions->sel_challenges[MENUITEM_CHALLENGES_EVO_LIMIT]              = gSaveBlock1Ptr->tx_Challenges_EvoLimit;
        sOptions->sel_challenges[MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE]     = gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge;
        sOptions->sel_challenges[MENUITEM_CHALLENGES_BASE_STAT_EQUALIZER]    = gSaveBlock1Ptr->tx_Challenges_BaseStatEqualizer;
        sOptions->sel_challenges[MENUITEM_CHALLENGES_MIRROR]                 = gSaveBlock1Ptr->tx_Challenges_Mirror;
        sOptions->sel_challenges[MENUITEM_CHALLENGES_MIRROR_THIEF]           = gSaveBlock1Ptr->tx_Challenges_Mirror_Thief;

        sOptions->submenu = MENU_MODE;

        gMain.state++;
        break;
    case 7:
        PutWindowTilemap(WIN_TOPBAR);
        DrawTopBarText();
        gMain.state++;
        break;
    case 8:
        PutWindowTilemap(WIN_DESCRIPTION);
        DrawDescriptionText();
        gMain.state++;
        break;
    case 9:
        PutWindowTilemap(WIN_OPTIONS);
        DrawOptionMenuTexts();
        gMain.state++;
        break;
    case 10:
        taskId = CreateTask(Task_OptionMenuFadeIn, 0);
        
        sOptions->arrowTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 240 / 2, 20, 110, MENUITEM_MODE_COUNT - 1, 110, 110, 0);

        for (i = 0; i < OPTIONS_ON_SCREEN; i++)
            DrawChoices(i, i * Y_DIFF);

        HighlightOptionMenuItem();

        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        gMain.state++;
        break;
    case 11:
        DrawBgWindowFrames();
        gMain.state++;
        break;
    case 12:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

void Task_ChooseChallenge_NoNewGame(u8 taskId)
{
    gMain.savedCallback = CB2_ReturnToField_SaveChallengesData;
    SetMainCallback2(CB2_InitTxRandomizerChallengesMenu);
    DestroyTask(taskId);
}

static void Task_OptionMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_OptionMenuProcessInput;
}

static void Task_OptionMenuProcessInput(u8 taskId)
{
    int i, scrollCount = 0, itemsToRedraw;
    // Treat the L BUTTON as an L BUTTON even if the user has L=A set.
    if (JOY_NEW(A_BUTTON) && !(JOY_NEW(L_BUTTON)))
    {
        if (sOptions->menuCursor[sOptions->submenu] == MenuItemCancel())
        {
            if (sOptions->submenu == MENU_COUNT-1)
                gTasks[taskId].func = Task_RandomizerChallengesMenuSave;
            else
            {
                sOptions->submenu++;
                DrawTopBarText();
                ReDrawAll();
                HighlightOptionMenuItem();
                DrawDescriptionText();
            }
        }
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (sOptions->visibleCursor[sOptions->submenu] == NUM_OPTIONS_FROM_BORDER) // don't advance visible cursor until scrolled to the bottom
        {
            if (--sOptions->menuCursor[sOptions->submenu] == 0)
                sOptions->visibleCursor[sOptions->submenu]--;
            else
                ScrollMenu(1);
        }
        else
        {
            if (--sOptions->menuCursor[sOptions->submenu] < 0) // Scroll all the way to the bottom.
            {
                sOptions->visibleCursor[sOptions->submenu] = sOptions->menuCursor[sOptions->submenu] = 3;
                ScrollAll(0);
                sOptions->visibleCursor[sOptions->submenu] = 4;
                sOptions->menuCursor[sOptions->submenu] = MenuItemCount() - 1;
            }
            else
            {
                sOptions->visibleCursor[sOptions->submenu]--;
            }
        }
        HighlightOptionMenuItem();
        DrawDescriptionText();
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (sOptions->visibleCursor[sOptions->submenu] == 3) // don't advance visible cursor until scrolled to the bottom
        {
            if (++sOptions->menuCursor[sOptions->submenu] == MenuItemCount() - 1)
                sOptions->visibleCursor[sOptions->submenu]++;
            else
                ScrollMenu(0);
        }
        else
        {
            if (++sOptions->menuCursor[sOptions->submenu] >= MenuItemCount()-1) // Scroll all the way to the top.
            {
                sOptions->visibleCursor[sOptions->submenu] = 3;
                sOptions->menuCursor[sOptions->submenu] = MenuItemCount() - 4;
                ScrollAll(1);
                sOptions->visibleCursor[sOptions->submenu] = sOptions->menuCursor[sOptions->submenu] = 0;
            }
            else
            {
                sOptions->visibleCursor[sOptions->submenu]++;
            }
        }
        HighlightOptionMenuItem();
        DrawDescriptionText();
    }
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        if (sOptions->submenu == MENU_MODE)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_mode[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsMode[cursor].processInput != NULL)
                {
                    sOptions->sel_mode[cursor] = sItemFunctionsMode[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_mode[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
        else if (sOptions->submenu == MENU_FEATURES)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_features[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsFeatures[cursor].processInput != NULL)
                {
                    sOptions->sel_features[cursor] = sItemFunctionsFeatures[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_features[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
        else if (sOptions->submenu == MENU_RANDOMIZER)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_randomizer[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsRandom[cursor].processInput != NULL)
                {
                    sOptions->sel_randomizer[cursor] = sItemFunctionsRandom[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_randomizer[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
        else if (sOptions->submenu == MENU_NUZLOCKE)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_nuzlocke[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsNuzlocke[cursor].processInput != NULL)
                {
                    sOptions->sel_nuzlocke[cursor] = sItemFunctionsNuzlocke[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_nuzlocke[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
        else if (sOptions->submenu == MENU_DIFFICULTY)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_difficulty[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsDifficulty[cursor].processInput != NULL)
                {
                    sOptions->sel_difficulty[cursor] = sItemFunctionsDifficulty[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_difficulty[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
        else if (sOptions->submenu == MENU_CHALLENGES)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_challenges[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsChallenges[cursor].processInput != NULL)
                {
                    sOptions->sel_challenges[cursor] = sItemFunctionsChallenges[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_challenges[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
    }
    else if (JOY_NEW(R_BUTTON))
    {
        if (sOptions->submenu != MENU_COUNT-1)
            sOptions->submenu++;

        DrawTopBarText();
        ReDrawAll();
        HighlightOptionMenuItem();
        DrawDescriptionText();
    }
    else if (JOY_NEW(L_BUTTON))
    {
        if (sOptions->submenu != 0)
            sOptions->submenu--;
        
        DrawTopBarText();
        ReDrawAll();
        HighlightOptionMenuItem();
        DrawDescriptionText();
    }
}

static void Task_RandomizerChallengesMenuSave(u8 taskId)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gTasks[taskId].func = Task_RandomizerChallengesMenuFadeOut;
}

static void Task_RandomizerChallengesMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}

void SaveData_TxRandomizerAndChallenges(void)
{
    PrintCurrentSelections();
    //MENU MODE
    //gSaveBlock1Ptr->tx_Mode_AlternateSpawns                  = sOptions->sel_mode[MENUITEM_MODE_ALTERNATE_SPAWNS]; 
    gSaveBlock1Ptr->tx_Mode_InfiniteTMs                 = sOptions->sel_mode[MENUITEM_MODE_INFINITE_TMS]; 
    gSaveBlock1Ptr->tx_Mode_PoisonSurvive               = sOptions->sel_mode[MENUITEM_MODE_SURVIVE_POISON]; 
    gSaveBlock1Ptr->tx_Mode_Synchronize                 = sOptions->sel_mode[MENUITEM_MODE_SYNCHRONIZE]; 
    gSaveBlock1Ptr->tx_Mode_Mints                       = sOptions->sel_mode[MENUITEM_MODE_MINTS]; 
    gSaveBlock1Ptr->tx_Mode_New_Citrus                  = sOptions->sel_mode[MENUITEM_MODE_NEW_CITRUS]; 
    gSaveBlock1Ptr->tx_Mode_Modern_Types                = sOptions->sel_mode[MENUITEM_MODE_MODERN_TYPES]; 
    gSaveBlock1Ptr->tx_Mode_Fairy_Types                 = sOptions->sel_mode[MENUITEM_MODE_FAIRY_TYPES]; 
    gSaveBlock1Ptr->tx_Mode_New_Stats                   = sOptions->sel_mode[MENUITEM_MODE_NEW_STATS]; 
    gSaveBlock1Ptr->tx_Mode_Sturdy                      = sOptions->sel_mode[MENUITEM_MODE_STURDY]; 
    gSaveBlock1Ptr->tx_Mode_Modern_Moves                = sOptions->sel_mode[MENUITEM_MODE_MODERN_MOVES]; 
    gSaveBlock1Ptr->tx_Mode_Legendary_Abilities         = sOptions->sel_mode[MENUITEM_MODE_LEGENDARY_ABILITIES]; 
    gSaveBlock1Ptr->tx_Mode_New_Legendaries             = sOptions->sel_mode[MENUITEM_MODE_NEW_LEGENDARIES]; 
    gSaveBlock1Ptr->tx_Mode_TypeEffectiveness           = sOptions->sel_mode[MENUITEM_MODE_NEW_EFFECTIVENESS];
    //MENU FEAUTRES
    gSaveBlock1Ptr->tx_Features_RTCType                     = sOptions->sel_features[MENUITEM_FEATURES_RTC_TYPE]; 
    gSaveBlock1Ptr->tx_Features_ShinyChance                 = sOptions->sel_features[MENUITEM_FEATURES_SHINY_CHANCE]; 
    gSaveBlock1Ptr->tx_Features_WildMonDropItems            = sOptions->sel_features[MENUITEM_FEATURES_ITEM_DROP]; 
    //gSaveBlock1Ptr->tx_Features_EasierFeebas                = sOptions->sel_features[MENUITEM_FEATURES_EASY_FEEBAS]; 
    gSaveBlock1Ptr->tx_Features_PkmnDeath                   = sOptions->sel_features[MENUITEM_FEATURES_PKMN_DEATH]; 
    gSaveBlock1Ptr->tx_Features_Unlimited_WT                = sOptions->sel_features[MENUITEM_FEATURES_UNLIMITED_WT]; 
    gSaveBlock1Ptr->tx_Features_FrontierBans                = sOptions->sel_features[MENUITEM_FEATURES_FRONTIER_BANS]; 
    // MENU_RANDOMIZER
    if (sOptions->sel_randomizer[MENUITEM_RANDOM_OFF_ON] == TRUE)
    {
        gSaveBlock1Ptr->tx_Random_Starter            = sOptions->sel_randomizer[MENUITEM_RANDOM_STARTER];
        gSaveBlock1Ptr->tx_Random_WildPokemon        = sOptions->sel_randomizer[MENUITEM_RANDOM_WILD_PKMN];
        gSaveBlock1Ptr->tx_Random_Trainer            = sOptions->sel_randomizer[MENUITEM_RANDOM_TRAINER];
        gSaveBlock1Ptr->tx_Random_Static             = sOptions->sel_randomizer[MENUITEM_RANDOM_STATIC];
        gSaveBlock1Ptr->tx_Random_Similar            = !sOptions->sel_randomizer[MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL];
        gSaveBlock1Ptr->tx_Random_MapBased           = TX_RANDOM_MAP_BASED;
        gSaveBlock1Ptr->tx_Random_IncludeLegendaries = sOptions->sel_randomizer[MENUITEM_RANDOM_INCLUDE_LEGENDARIES];
        gSaveBlock1Ptr->tx_Random_Type               = sOptions->sel_randomizer[MENUITEM_RANDOM_TYPE];
        gSaveBlock1Ptr->tx_Random_Moves              = sOptions->sel_randomizer[MENUITEM_RANDOM_MOVES];
        gSaveBlock1Ptr->tx_Random_Abilities          = sOptions->sel_randomizer[MENUITEM_RANDOM_ABILITIES];
        gSaveBlock1Ptr->tx_Random_Evolutions         = sOptions->sel_randomizer[MENUITEM_RANDOM_EVOLUTIONS];
        gSaveBlock1Ptr->tx_Random_EvolutionMethods   = sOptions->sel_randomizer[MENUITEM_RANDOM_EVOLUTIONS_METHODS];
        gSaveBlock1Ptr->tx_Random_TypeEffectiveness  = sOptions->sel_randomizer[MENUITEM_RANDOM_TYPE_EFFEC];
        gSaveBlock1Ptr->tx_Random_Items              = sOptions->sel_randomizer[MENUITEM_RANDOM_ITEMS];
        gSaveBlock1Ptr->tx_Random_Chaos              = sOptions->sel_randomizer[MENUITEM_RANDOM_CHAOS];
    }
    else
    {
        gSaveBlock1Ptr->tx_Random_Starter            = FALSE;
        gSaveBlock1Ptr->tx_Random_WildPokemon        = FALSE;
        gSaveBlock1Ptr->tx_Random_Trainer            = FALSE;
        gSaveBlock1Ptr->tx_Random_Static             = FALSE;
        gSaveBlock1Ptr->tx_Random_Similar            = FALSE;
        gSaveBlock1Ptr->tx_Random_MapBased           = FALSE;
        gSaveBlock1Ptr->tx_Random_IncludeLegendaries = FALSE;
        gSaveBlock1Ptr->tx_Random_Type               = FALSE;
        gSaveBlock1Ptr->tx_Random_Moves              = FALSE;
        gSaveBlock1Ptr->tx_Random_Abilities          = FALSE;
        gSaveBlock1Ptr->tx_Random_Evolutions         = FALSE;
        gSaveBlock1Ptr->tx_Random_EvolutionMethods   = FALSE;
        gSaveBlock1Ptr->tx_Random_TypeEffectiveness  = FALSE;
        gSaveBlock1Ptr->tx_Random_Chaos              = FALSE;
    } 
    //MENU_NUZLOCKE
    switch (sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE])
    {
    case 0:
        gSaveBlock1Ptr->tx_Challenges_Nuzlocke          = FALSE;
        gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore  = FALSE;
        break;
    case 1:
        gSaveBlock1Ptr->tx_Challenges_Nuzlocke          = TRUE;
        gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore  = FALSE;
        break;
    case 2:
        gSaveBlock1Ptr->tx_Challenges_Nuzlocke          = TRUE;
        gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore  = TRUE;
        break;
    }
    if (gSaveBlock1Ptr->tx_Challenges_Nuzlocke)
    {
        gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause   = !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SPECIES_CLAUSE];
        gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause     = !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SHINY_CLAUSE];
        gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming      = !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NICKNAMING];
        gSaveBlock1Ptr->tx_Nuzlocke_Deletion        = sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_DELETION];
    }
    else
    {
        gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause   = FALSE;
        gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause     = FALSE;
        gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming      = FALSE;
    }
    // MENU_DIFFICULTY
    gSaveBlock1Ptr->tx_Challenges_PartyLimit    = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_PARTY_LIMIT];
    gSaveBlock1Ptr->tx_Challenges_LevelCap      = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_LEVEL_CAP];
    gSaveBlock1Ptr->tx_Challenges_ExpMultiplier = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_EXP_MULTIPLIER];
    gSaveBlock1Ptr->tx_Challenges_LessEscapes   = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_LESS_ESCAPES];
    gSaveBlock1Ptr->tx_Challenges_NoItemPlayer  = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_ITEM_PLAYER];
    gSaveBlock1Ptr->tx_Challenges_NoItemTrainer = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_ITEM_TRAINER];
    gSaveBlock1Ptr->tx_Challenges_NoEVs                 = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_NO_EVS];
    gSaveBlock1Ptr->tx_Challenges_TrainerScalingIVs     = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_SCALING_IVS];
    gSaveBlock1Ptr->tx_Challenges_TrainerScalingEVs     = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_SCALING_EVS];
    //gSaveBlock1Ptr->tx_Features_LimitDifficulty              = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_LIMIT_DIFFICULTY];
    gSaveBlock1Ptr->tx_Challenges_MaxPartyIVs                         = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_MAX_PARTY_IVS];
    // MENU_CHALLENGES
    gSaveBlock1Ptr->tx_Challenges_EvoLimit             = sOptions->sel_challenges[MENUITEM_CHALLENGES_EVO_LIMIT];
    if (sOptions->sel_challenges[MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE] > NUMBER_OF_MON_TYPES-1)
        gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge = TX_CHALLENGE_TYPE_OFF;
    else if (sOptions->sel_challenges[MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE] == NUMBER_OF_MON_TYPES-1)
        gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge = GetRandomType();
    else if (sOptions->sel_challenges[MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE] >= TYPE_MYSTERY)
        gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge = sOptions->sel_challenges[MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE] + 1;
    else
        gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge = sOptions->sel_challenges[MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE];
    gSaveBlock1Ptr->tx_Challenges_BaseStatEqualizer    = sOptions->sel_challenges[MENUITEM_CHALLENGES_BASE_STAT_EQUALIZER];
    gSaveBlock1Ptr->tx_Challenges_Mirror               = sOptions->sel_challenges[MENUITEM_CHALLENGES_MIRROR]; 
    gSaveBlock1Ptr->tx_Challenges_Mirror_Thief         = sOptions->sel_challenges[MENUITEM_CHALLENGES_MIRROR_THIEF]; 
    gSaveBlock1Ptr->tx_Challenges_PCHeal               = sOptions->sel_challenges[MENUITEM_CHALLENGES_PCHEAL]; 
    gSaveBlock1Ptr->tx_Challenges_PkmnCenter           = sOptions->sel_challenges[MENUITEM_DIFFICULTY_POKECENTER];
    gSaveBlock1Ptr->tx_Challenges_Expensive            = sOptions->sel_challenges[MENUITEM_CHALLENGES_EXPENSIVE];
    gSaveBlock1Ptr->tx_Difficulty_EscapeRopeDig        = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_ESCAPE_ROPE_DIG];
    //gSaveBlock1Ptr->tx_Difficulty_HardExp              = sOptions->sel_difficulty[MENUITEM_DIFFICULTY_HARD_EXP];

    PrintTXSaveData();

    FREE_AND_SET_NULL(sOptions);
}

static void ScrollMenu(int direction)
{
    int menuItem, pos;

    if (direction == 0) // scroll down
        menuItem = sOptions->menuCursor[sOptions->submenu] + NUM_OPTIONS_FROM_BORDER, pos = OPTIONS_ON_SCREEN - 1;
    else
        menuItem = sOptions->menuCursor[sOptions->submenu] - NUM_OPTIONS_FROM_BORDER, pos = 0;

    // Hide one
    ScrollWindow(WIN_OPTIONS, direction, Y_DIFF, PIXEL_FILL(0));
    // Show one
    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(1), 0, Y_DIFF * pos, 26 * 8, Y_DIFF);
    // Print
    DrawChoices(menuItem, pos * Y_DIFF);
    DrawLeftSideOptionText(menuItem, (pos * Y_DIFF) + 1);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}
static void ScrollAll(int direction) // to bottom or top
{
    int i, y, menuItem, pos;
    int scrollCount;

    scrollCount = MenuItemCount() - OPTIONS_ON_SCREEN;

    // Move items up/down
    ScrollWindow(WIN_OPTIONS, direction, Y_DIFF * scrollCount, PIXEL_FILL(1));

    // Clear moved items
    if (direction == 0)
    {
        y = OPTIONS_ON_SCREEN - scrollCount;
        if (y < 0)
            y = OPTIONS_ON_SCREEN;
        y *= Y_DIFF;
    }
    else
    {
        y = 0;
    }

    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(1), 0, y, 26 * 8, Y_DIFF * scrollCount);
    // Print new texts
    for (i = 0; i < scrollCount; i++)
    {
        if (direction == 0) // From top to bottom
            menuItem = MenuItemCount() - 1 - i, pos = OPTIONS_ON_SCREEN - 1 - i;
        else // From bottom to top
            menuItem = i, pos = i;
        DrawChoices(menuItem, pos * Y_DIFF);
        DrawLeftSideOptionText(menuItem, (pos * Y_DIFF) + 1);
    }
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}

// Process Input functions ****GENERIC****
static int GetMiddleX(const u8 *txt1, const u8 *txt2, const u8 *txt3)
{
    int xMid;
    int widthLeft = GetStringWidth(1, txt1, 0);
    int widthMid = GetStringWidth(1, txt2, 0);
    int widthRight = GetStringWidth(1, txt3, 0);

    widthMid -= (198 - 104);
    xMid = (widthLeft - widthMid - widthRight) / 2 + 104;
    return xMid;
}

static int XOptions_ProcessInput(int x, int selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (++selection > (x - 1))
            selection = 0;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (--selection < 0)
            selection = (x - 1);
    }
    return selection;
}

static int ProcessInput_Options_Two(int selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
        selection ^= 1;

    return selection;
}

static int ProcessInput_Options_Three(int selection)
{
    return XOptions_ProcessInput(3, selection);
}

static int ProcessInput_Options_Four(int selection)
{
    return XOptions_ProcessInput(4, selection);
}

static int ProcessInput_Options_Five(int selection)
{
    return XOptions_ProcessInput(5, selection);
}

static int ProcessInput_Options_Six(int selection)
{
    return XOptions_ProcessInput(6, selection);
}

static int ProcessInput_Options_Eleven(int selection)
{
    return XOptions_ProcessInput(11, selection);
}

static int ProcessInput_Options_OneTypeChallenge(int selection)
{
    return XOptions_ProcessInput(NUMBER_OF_MON_TYPES+1, selection);
}

// Process Input functions ****SPECIFIC****
static int ProcessInput_Sound(int selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        SetPokemonCryStereo(selection);
    }

    return selection;
}

static int ProcessInput_FrameType(int selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < WINDOW_FRAMES_COUNT - 1)
            selection++;
        else
            selection = 0;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, 0x70, 0x20);
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = WINDOW_FRAMES_COUNT - 1;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, 0x70, 0x20);
    }
    return selection;
}

// Draw Choices functions ****GENERIC****
static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style, bool8 active)
{
    bool8 choosen = FALSE;
    if (style != 0)
        choosen = TRUE;

    DrawRightSideChoiceText(text, x, y+1, choosen, active);
}

static void DrawChoices_Options_Four(const u8 *const *const strings, int selection, int y, bool8 active)
{
    static const u8 choiceOrders[][3] =
    {
        {0, 1, 2},
        {0, 1, 2},
        {1, 2, 3},
        {1, 2, 3},
    };
    u8 styles[4] = {0};
    int xMid;
    const u8 *order = choiceOrders[selection];
    styles[selection] = 1;
    xMid = GetMiddleX(strings[order[0]], strings[order[1]], strings[order[2]]);

    DrawOptionMenuChoice(strings[order[0]], 104, y, styles[order[0]], active);
    DrawOptionMenuChoice(strings[order[1]], xMid, y, styles[order[1]], active);
    DrawOptionMenuChoice(strings[order[2]], GetStringRightAlignXOffset(1, strings[order[2]], 198), y, styles[order[2]], active);
}


static void DrawChoices_Options_Three(const u8 *const *const strings, int selection, int y, bool8 active)
{
    static const u8 choiceOrders[][2] =
    {
        {0, 1},
        {1, 2},
        {1, 2},
    };
    u8 styles[3] = {0};
    const u8 *order = choiceOrders[selection];
    styles[selection] = 1;

    DrawOptionMenuChoice(strings[order[0]], 104, y, styles[order[0]], active);
    DrawOptionMenuChoice(strings[order[1]], GetStringRightAlignXOffset(1, strings[order[1]], 198), y, styles[order[1]], active);
}


static void DrawChoices_Options_Five(const u8 *const *const strings, int selection, int y, bool8 active)
{
    static const u8 choiceOrders[][3] =
    {
        {0, 1, 2},
        {0, 1, 2},
        {1, 2, 3},
        {2, 3, 4},
        {2, 3, 4},
    };
    u8 styles[5] = {0};
    int xMid;
    const u8 *order = choiceOrders[selection];
    styles[selection] = 1;
    xMid = GetMiddleX(strings[order[0]], strings[order[1]], strings[order[2]]);

    DrawOptionMenuChoice(strings[order[0]], 104, y, styles[order[0]], active);
    DrawOptionMenuChoice(strings[order[1]], xMid, y, styles[order[1]], active);
    DrawOptionMenuChoice(strings[order[2]], GetStringRightAlignXOffset(1, strings[order[2]], 198), y, styles[order[2]], active);
}

static void ReDrawAll(void)
{
    u8 menuItem = sOptions->menuCursor[sOptions->submenu] - sOptions->visibleCursor[sOptions->submenu];
    u8 i;

    if (MenuItemCount() <= 5) // Draw or delete the scrolling arrows based on options in the menu
    {
        if (sOptions->arrowTaskId != TASK_NONE)
        {
            RemoveScrollIndicatorArrowPair(sOptions->arrowTaskId);
            sOptions->arrowTaskId = TASK_NONE;
        }
    }
    else
    {
        if (sOptions->arrowTaskId == TASK_NONE)
            sOptions->arrowTaskId = sOptions->arrowTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 240 / 2, 20, 110, MenuItemCount() - 1, 110, 110, 0);

    }

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < OPTIONS_ON_SCREEN; i++)
    {
        DrawChoices(menuItem+i, i * Y_DIFF);
        DrawLeftSideOptionText(menuItem+i, (i * Y_DIFF) + 1);
    }
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}

// Draw Choices functions ****SPECIFIC****
// MENU_RANDOMIZER
static const u8 sText_Off[]  = _("OFF");
static const u8 sText_On[]   = _("ON");
static const u8 sText_None[] = _("NONE");
static void DrawChoices_Random_OffOn(int selection, int y, bool8 active)
{
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}


static const u8 sClassic[]  = _("RECOMMENDED");
static const u8 sModern[]   = _("MODERN");
static const u8 sCustom[]   = _("CUSTOM");
static const u8 *const sText_Mode_Strings[] = {sClassic,  sCustom};

static void DrawChoices_Mode_Classic_Modern_Selector(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_CLASSIC_MODERN);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sClassic, 74, y, styles[0], active);
    DrawOptionMenuChoice(sCustom, GetStringRightAlignXOffset(1, sCustom, 198), y, styles[1], active);
    
    if (selection == 0)
    {
        //sOptions->sel_mode[MENUITEM_MODE_ALTERNATE_SPAWNS]          = tx_Mode_AlternateSpawns;
        //gSaveBlock1Ptr->tx_Mode_AlternateSpawns = 0;
        sOptions->sel_mode[MENUITEM_MODE_INFINITE_TMS]              = !TX_MODE_INFINITE_TMS;
        gSaveBlock1Ptr->tx_Mode_InfiniteTMs = 1;
        FlagClear (FLAG_FINITE_TMS);
        sOptions->sel_mode[MENUITEM_MODE_SURVIVE_POISON]            = !TX_MODE_SURVIVE_POISON;
        gSaveBlock1Ptr->tx_Mode_PoisonSurvive = 1;
        sOptions->sel_mode[MENUITEM_MODE_SYNCHRONIZE]               = !TX_MODE_NEW_SYNCHRONIZE;
        gSaveBlock1Ptr->tx_Mode_Synchronize = 1;
        sOptions->sel_mode[MENUITEM_MODE_MINTS]                     = !TX_MODE_MINTS;
        gSaveBlock1Ptr->tx_Mode_Mints = 1;
        FlagClear (FLAG_MINTS_ENABLED);
        sOptions->sel_mode[MENUITEM_MODE_NEW_CITRUS]                = !TX_MODE_NEW_CITRUS;
        gSaveBlock1Ptr->tx_Mode_New_Citrus = 1;
        sOptions->sel_mode[MENUITEM_MODE_MODERN_TYPES]              = TX_MODE_MODERN_TYPES;
        gSaveBlock1Ptr->tx_Mode_Modern_Types = 0;
        sOptions->sel_mode[MENUITEM_MODE_FAIRY_TYPES]               = !TX_MODE_FAIRY_TYPES;
        gSaveBlock1Ptr->tx_Mode_Fairy_Types = 1;
        sOptions->sel_mode[MENUITEM_MODE_NEW_STATS]                 = TX_MODE_NEW_STATS;
        gSaveBlock1Ptr->tx_Mode_New_Stats = 0;
        sOptions->sel_mode[MENUITEM_MODE_STURDY]                    = !TX_MODE_STURDY;
        gSaveBlock1Ptr->tx_Mode_Sturdy = 1;
        sOptions->sel_mode[MENUITEM_MODE_MODERN_MOVES]              = !TX_MODE_MODERN_MOVES;
        gSaveBlock1Ptr->tx_Mode_Modern_Moves = 1;
        sOptions->sel_mode[MENUITEM_MODE_LEGENDARY_ABILITIES]       = !TX_MODE_LEGENDARY_ABILITIES;
        gSaveBlock1Ptr->tx_Mode_Legendary_Abilities = 1;
        sOptions->sel_mode[MENUITEM_MODE_NEW_LEGENDARIES]           = TX_MODE_NEW_LEGENDARIES;
        gSaveBlock1Ptr->tx_Mode_New_Legendaries = 0;
        sOptions->sel_mode[MENUITEM_MODE_NEW_EFFECTIVENESS]         = TX_MODE_TYPE_EFFECTIVENESS;
        gSaveBlock1Ptr->tx_Mode_TypeEffectiveness = 1;
    }
}

static const u8 sText_Random[]  = _("RANDOM");
static void DrawChoices_Random_OffRandom(int selection, int y, bool8 active)
{
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);   
    DrawOptionMenuChoice(sText_Random, GetStringRightAlignXOffset(1, sText_Random, 198), y, styles[1], active);
}

static void DrawChoices_Random_Toggle(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_OFF_ON);
    DrawChoices_Random_OffOn(selection, y, active);
}
static void DrawChoices_Random_Starter(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_STARTER);
    DrawChoices_Random_OffRandom(selection, y, active);
}
static void DrawChoices_Random_WildPkmn(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_WILD_PKMN);
    DrawChoices_Random_OffRandom(selection, y, active);
}
static void DrawChoices_Random_Trainer(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_TRAINER);
    DrawChoices_Random_OffRandom(selection, y, active);
}
static void DrawChoices_Random_Static(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_STATIC);
    DrawChoices_Random_OffRandom(selection, y, active);
}
static void DrawChoices_Random_EvoStages(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}
static void DrawChoices_Random_Legendaries(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_INCLUDE_LEGENDARIES);
    DrawChoices_Random_OffOn(selection, y, active);
}
static void DrawChoices_Random_Types(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_TYPE);
    DrawChoices_Random_OffRandom(selection, y, active);
}
static void DrawChoices_Random_Moves(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_MOVES);
    DrawChoices_Random_OffRandom(selection, y, active);
}
static void DrawChoices_Random_Abilities(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_ABILITIES);
    DrawChoices_Random_OffRandom(selection, y, active);
}
static void DrawChoices_Random_Evolutions(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_EVOLUTIONS);
    DrawChoices_Random_OffRandom(selection, y, active);
}
static void DrawChoices_Random_EvolutionMethods(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_EVOLUTIONS_METHODS);
    DrawChoices_Random_OffRandom(selection, y, active);
}
static void DrawChoices_Random_TypeEffect(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_TYPE_EFFEC);
    DrawChoices_Random_OffRandom(selection, y, active);
}
static void DrawChoices_Random_Items(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_ITEMS);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static const u8 sText_Random_Chaos[] = _("CHAOS");
static void DrawChoices_Random_OffChaos(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_CHAOS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Random_Chaos, GetStringRightAlignXOffset(1, sText_Random_Chaos, 198), y, styles[1], active);

    if (selection == 1)
        sOptions->sel_randomizer[MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL] = 1;
}

// MENU_NUZLOCKE
static void DrawChoices_Nuzlocke_OnOff(int selection, int y, bool8 active)
{
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}
static const u8 sText_Challenges_Nuzlocke_Normal[]      = _("NORMAL");
static const u8 sText_Challenges_Nuzlocke_Hardcore[]    = _("HARD");
static void DrawChoices_Challenges_Nuzlocke(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_NUZLOCKE);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Off, sText_Challenges_Nuzlocke_Normal, sText_Challenges_Nuzlocke_Hardcore);
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Challenges_Nuzlocke_Normal, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_Challenges_Nuzlocke_Hardcore, GetStringRightAlignXOffset(1, sText_Challenges_Nuzlocke_Hardcore, 198), y, styles[2], active);

    if (selection == 0)
    {
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SPECIES_CLAUSE]    = !TX_NUZLOCKE_SPECIES_CLAUSE;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SHINY_CLAUSE]      = !TX_NUZLOCKE_SHINY_CLAUSE; 
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NICKNAMING]        = !TX_NUZLOCKE_NICKNAMING;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_DELETION]          = TX_NUZLOCKE_DELETION;
    }
}

static void DrawChoices_Nuzlocke_SpeciesClause(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_SPECIES_CLAUSE);
    DrawChoices_Nuzlocke_OnOff(selection, y, active);
}
static void DrawChoices_Nuzlocke_ShinyClause(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_SHINY_CLAUSE);
    DrawChoices_Nuzlocke_OnOff(selection, y, active);
}
static void DrawChoices_Nuzlocke_Nicknaming(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_NICKNAMING);
    DrawChoices_Nuzlocke_OnOff(selection, y, active);
}
static const u8 sText_Nuzlocke_Cemetery[]  = _("CEMETERY");
static const u8 sText_Nuzlocke_Deletion[]  = _("RELEASE");
static void DrawChoices_Nuzlocke_Deletion(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_DELETION);
    u8 styles[2] = {0};
    styles[selection] = 1;
    DrawOptionMenuChoice(sText_Nuzlocke_Cemetery, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Nuzlocke_Deletion, GetStringRightAlignXOffset(1, sText_Nuzlocke_Deletion, 198), y, styles[1], active);
}

// MENU_DIFFICULTY
static const u8 sText_Yes[] = _("YES");
static const u8 sText_No[]  = _("NO");
static void DrawChoices_Challenges_YesNo(int selection, int y, bool8 active)
{
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Yes, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_No, GetStringRightAlignXOffset(1, sText_No, 198), y, styles[1], active);
}
static void DrawChoices_Challenges_ItemsPlayer(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_ITEM_PLAYER);
    DrawChoices_Challenges_YesNo(selection, y, active);
}
static void DrawChoices_Challenges_ItemsTrainer(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_ITEM_TRAINER);
    DrawChoices_Challenges_YesNo(selection, y, active);
}
static void DrawChoices_Challenges_NoEVs(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_NO_EVS);
    DrawChoices_Challenges_YesNo(selection, y, active);
}
static const u8 sText_ScalingIVsEVs_Scaling[]   = _("SCALE");
static const u8 sText_ScalingIVsEVs_Hard[]      = _("HARD");
static void DrawChoices_Challenges_ScalingIVs(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_SCALING_IVS);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Off, sText_ScalingIVsEVs_Scaling, sText_ScalingIVsEVs_Hard);
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_ScalingIVsEVs_Scaling, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_ScalingIVsEVs_Hard, GetStringRightAlignXOffset(1, sText_ScalingIVsEVs_Hard, 198), y, styles[2], active);
}
static const u8 sText_ScalingIVsEVs_Extrem[]    = _("EXTREM");
static const u8 *const sText_ScalingEVs_Strings[] = {sText_Off, sText_ScalingIVsEVs_Scaling, sText_ScalingIVsEVs_Hard, sText_ScalingIVsEVs_Extrem};
static void DrawChoices_Challenges_ScalingEVs(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_SCALING_EVS);
    DrawChoices_Options_Four(sText_ScalingEVs_Strings, selection, y, active);
}

static const u8 sText_Challenges_PartyLimit_1[]  = _("1");
static const u8 sText_Challenges_PartyLimit_2[]  = _("2");
static const u8 sText_Challenges_PartyLimit_3[]  = _("3");
static const u8 sText_Challenges_PartyLimit_4[]  = _("4");
static const u8 sText_Challenges_PartyLimit_5[]  = _("5");
static void DrawChoices_Challenges_PartyLimit(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_PARTY_LIMIT);
    u8 styles[6] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Challenges_PartyLimit_5, 130, y, styles[1], active);
    DrawOptionMenuChoice(sText_Challenges_PartyLimit_4, 146, y, styles[2], active);
    DrawOptionMenuChoice(sText_Challenges_PartyLimit_3, 161, y, styles[3], active);
    DrawOptionMenuChoice(sText_Challenges_PartyLimit_2, 176, y, styles[4], active);
    DrawOptionMenuChoice(sText_Challenges_PartyLimit_1, 192, y, styles[5], active);
}

static const u8 sText_Challenges_LevelCap_Normal[]  = _("NORMAL");
static const u8 sText_Challenges_LevelCap_Hard[]    = _("HARD");
static void DrawChoices_Challenges_LevelCap(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_LEVEL_CAP);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Off, sText_Challenges_LevelCap_Normal, sText_Challenges_LevelCap_Hard);
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Challenges_LevelCap_Normal, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_Challenges_LevelCap_Hard, GetStringRightAlignXOffset(1, sText_Challenges_LevelCap_Hard, 198), y, styles[2], active);
}

static const u8 sText_Challenges_ExpMultiplier_1_0[]   = _("x1.0");
static const u8 sText_Challenges_ExpMultiplier_1_5[]   = _("x1.5");
static const u8 sText_Challenges_ExpMultiplier_2_0[]   = _("x2.0");
static const u8 sText_Challenges_ExpMultiplier_0_0[]   = _("x0.0");
static const u8 *const sText_Challenges_ExpMultiplier_Strings[] = {sText_Challenges_ExpMultiplier_1_0, sText_Challenges_ExpMultiplier_1_5, sText_Challenges_ExpMultiplier_2_0, sText_Challenges_ExpMultiplier_0_0};
static void DrawChoices_Challenges_ExpMultiplier(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_EXP_MULTIPLIER);
    DrawChoices_Options_Four(sText_Challenges_ExpMultiplier_Strings, selection, y, active);
}

static void DrawChoices_Challenges_Pokecenters(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_POKECENTER);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Yes, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_No, GetStringRightAlignXOffset(1, sText_No, 198), y, styles[1], active);
}


// MENU_CHALLENGES
static const u8 sText_Challenges_EvoLimit_First[]   = _("FIRST");
static const u8 sText_Challenges_EvoLimit_All[]     = _("ALL");
static void DrawChoices_Challenges_EvoLimit(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_CHALLENGES_EVO_LIMIT);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Off, sText_Challenges_EvoLimit_First, sText_None);
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Challenges_EvoLimit_First, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_Challenges_EvoLimit_All, GetStringRightAlignXOffset(1, sText_Challenges_EvoLimit_All, 198), y, styles[2], active);
}

static void DrawChoices_Challenges_OneTypeChallenge(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_CHALLENGES_ONE_TYPE_CHALLENGE);
    u8 n = selection;

    if (n > NUMBER_OF_MON_TYPES-1)
        StringCopyPadded(gStringVar1, sText_Off, 0, 15);
    else if (n == NUMBER_OF_MON_TYPES-1)
        StringCopyPadded(gStringVar1, sText_Random, 0, 15);
    else if (n >= TYPE_MYSTERY)
        StringCopyPadded(gStringVar1, gTypeNames[n+1], 0, 10);
    else
        StringCopyPadded(gStringVar1, gTypeNames[n], 0, 10);

    DrawOptionMenuChoice(gStringVar1, 104, y, 1, active);
}

static const u8 sText_Challenges_BaseStatEqualizer_100[]   = _("100");
static const u8 sText_Challenges_BaseStatEqualizer_255[]   = _("255");
static const u8 sText_Challenges_BaseStatEqualizer_500[]   = _("500");
static const u8 *const sText_Challenges_BaseStatEqualizer_Strings[] = {sText_Off, sText_Challenges_BaseStatEqualizer_100, sText_Challenges_BaseStatEqualizer_255, sText_Challenges_BaseStatEqualizer_500};
static void DrawChoices_Challenges_BaseStatEqualizer(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_CHALLENGES_BASE_STAT_EQUALIZER);
    DrawChoices_Options_Four(sText_Challenges_BaseStatEqualizer_Strings, selection, y, active);
}

static const u8 sText_Challenges_Mirror_All[]   = _("ALL");
static void DrawChoices_Challenges_Mirror(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_CHALLENGES_MIRROR);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);

    if (selection == 0)
        sOptions->sel_challenges[MENUITEM_CHALLENGES_MIRROR_THIEF] = 0;
}
static void DrawChoices_Challenges_Mirror_Thief(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_CHALLENGES_MIRROR_THIEF);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static const u8 sText_Features_RTC_RTC[]   = _("RTC");
static const u8 sText_Features_RTC_Fake_RTC[]   = _("FAKE RTC");
static void DrawChoices_Features_Rtc_Type(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_FEATURES_RTC_TYPE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Features_RTCType = 0; //Off, RTC
    }
    else
    {
        gSaveBlock1Ptr->tx_Features_RTCType = 1; //On, Fake RTC
    }

    DrawOptionMenuChoice(sText_Features_RTC_RTC, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Features_RTC_Fake_RTC, GetStringRightAlignXOffset(1, sText_Features_RTC_Fake_RTC, 198), y, styles[1], active);
}

static const u8 sText_Encounters_Vanilla_Long[]   = _("ORIGINAL");
static const u8 sText_Encounters_Modern_Long[]    = _("MODERN");

/*static void DrawChoices_Mode_AlternateSpawns(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_ALTERNATE_SPAWNS);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Encounters_Vanilla, sText_Encounters_Modern, sText_Encounters_Postgame);
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_AlternateSpawns = 0; //Vanilla, unmodified encounters
    }
    else if (selection == 1)
    {
        gSaveBlock1Ptr->tx_Mode_AlternateSpawns = 1; //Full modern encounters
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_AlternateSpawns = 2; //Vanilla encounters, with post-game pokémon
    }

    DrawOptionMenuChoice(sText_Encounters_Vanilla, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Encounters_Modern, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_Encounters_Postgame, GetStringRightAlignXOffset(1, sText_Encounters_Postgame, 198), y, styles[2], active);
}*/

/*static void DrawChoices_Challenges_LimitDifficulty(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_LIMIT_DIFFICULTY);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Features_LimitDifficulty = 0; //Don't limit difficulty
    }
    else
    {
        gSaveBlock1Ptr->tx_Features_LimitDifficulty = 1; //limit difficulty
    }

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}*/

static const u8 sText_Max_Party_IVs_30_31[]   = _("NO (HP)");
static void DrawChoices_Challenges_MaxPartyIVs(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_MAX_PARTY_IVS);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Yes, sText_No, sText_Max_Party_IVs_30_31);
    styles[selection] = 1;



    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Challenges_MaxPartyIVs = 0; //Ivs set to normal
    }
    else if (selection == 1)
    {
        gSaveBlock1Ptr->tx_Challenges_MaxPartyIVs = 1; //Ivs are always 31
    }
    else
    {
        gSaveBlock1Ptr->tx_Challenges_MaxPartyIVs = 2; //Ivs are set between 30 and 31
    }


    DrawOptionMenuChoice(sText_Yes, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_No, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_Max_Party_IVs_30_31, GetStringRightAlignXOffset(1, sText_Max_Party_IVs_30_31, 198), y, styles[2], active);
}

static void DrawChoices_Features_ItemDrop(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_FEATURES_ITEM_DROP);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Features_WildMonDropItems = 0; //items don't drop
    }
    else
    {
        gSaveBlock1Ptr->tx_Features_WildMonDropItems = 1; //items do drop
    }

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static void DrawChoices_Mode_InfiniteTMs(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_INFINITE_TMS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_InfiniteTMs = 0; //TMs are finite
        FlagSet (FLAG_FINITE_TMS);
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_InfiniteTMs = 1; //TMs are infinite
        FlagClear (FLAG_FINITE_TMS);
    }

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static void DrawChoices_Mode_SurvivePoison(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_SURVIVE_POISON);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_PoisonSurvive = 0; //Poison will kill
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_PoisonSurvive = 1; //1hp survive poison
    }

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

/*static void DrawChoices_Features_EasyFeebas(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_FEATURES_EASY_FEEBAS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Features_EasierFeebas = 0; //off
    }
    else
    {
        gSaveBlock1Ptr->tx_Features_EasierFeebas = 1; //on
    }

    //DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    //DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}*/

static void DrawChoices_Features_Pkmn_Death(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_FEATURES_PKMN_DEATH);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Features_PkmnDeath = 0; //off
    }
    else
    {
        gSaveBlock1Ptr->tx_Features_PkmnDeath = 1; //on
    }

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static void DrawChoices_Challenges_PCHeal(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_CHALLENGES_PCHEAL);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Challenges_PCHeal = 0; //PC heal enabled
    }
    else
    {
        gSaveBlock1Ptr->tx_Challenges_PCHeal = 1; //PC heal disabled
    }

    DrawOptionMenuChoice(sText_Yes, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_No, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static const u8 sText_Challenges_ShinyChance_8192[]   = _("8192");
static const u8 sText_Challenges_ShinyChance_4096[]   = _("4096");
static const u8 sText_Challenges_ShinyChance_2048[]   = _("2048");
static const u8 sText_Challenges_ShinyChance_1024[]   = _("1024");
static const u8 sText_Challenges_ShinyChance_512[]    = _("512");
static const u8 *const sText_Challenges_ShinyChance_Strings[] = {sText_Challenges_ShinyChance_8192,  sText_Challenges_ShinyChance_4096,  sText_Challenges_ShinyChance_2048,  sText_Challenges_ShinyChance_1024,  sText_Challenges_ShinyChance_512};
static void DrawChoices_Features_ShinyChance(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_FEATURES_SHINY_CHANCE);
    DrawChoices_Options_Five(sText_Challenges_ShinyChance_Strings, selection, y, active);
    
    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Features_ShinyChance = 0; // 1/8192
    }
    else if (selection == 1)
    {
        gSaveBlock1Ptr->tx_Features_ShinyChance = 1; // 1/4096 -> Gen VI
    }
    else if (selection == 2)
    {
        gSaveBlock1Ptr->tx_Features_ShinyChance = 2; // 1/2048
    }
    else if (selection == 3)
    {
        gSaveBlock1Ptr->tx_Features_ShinyChance = 3; // 1/1024
    }
    else //(selection == 4)
    {
        gSaveBlock1Ptr->tx_Features_ShinyChance = 4; // 1/512
    }
}

static void DrawChoices_Features_Unlimited_WT(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_FEATURES_UNLIMITED_WT);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Features_Unlimited_WT = 0; //WTs are capped to 3 daily
        FlagClear (FLAG_UNLIMITIED_WONDERTRADE);
    }
    else
    {
        gSaveBlock1Ptr->tx_Features_Unlimited_WT = 1; //WTs are uncapped
        FlagSet (FLAG_UNLIMITIED_WONDERTRADE);
    }

    //DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    //DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static void DrawChoices_Mode_Synchronize(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_SYNCHRONIZE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_Synchronize = 0; //Old synchronize
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_Synchronize = 1; //New synchronize
    }

    DrawOptionMenuChoice(sText_Encounters_Vanilla_Long, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Encounters_Modern_Long, GetStringRightAlignXOffset(1, sText_Encounters_Modern_Long, 198), y, styles[1], active);
}

static void DrawChoices_Mode_Mints(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_MINTS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_Mints = 0; //No mints
        FlagClear (FLAG_MINTS_ENABLED);
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_Mints = 1; //Yes mints
        FlagSet (FLAG_MINTS_ENABLED);
    }

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static void DrawChoices_Mode_New_Citrus(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_NEW_CITRUS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_New_Citrus = 0; //No new citrus, old citrus
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_New_Citrus = 1; //Yes new citrus
    }

    DrawOptionMenuChoice(sText_Encounters_Vanilla_Long, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Encounters_Modern_Long, GetStringRightAlignXOffset(1, sText_Encounters_Modern_Long, 198), y, styles[1], active);
}

static void DrawChoices_Mode_Modern_Types(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_MODERN_TYPES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_Modern_Types = 0; //No type changes, except fairy
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_Modern_Types = 1; //New typings
    }

    //DrawOptionMenuChoice(sText_Encounters_Vanilla_Long, 104, y, styles[0], active);
    //DrawOptionMenuChoice(sText_Encounters_Modern_Long, GetStringRightAlignXOffset(1, sText_Encounters_Modern_Long, 198), y, styles[1], active);
}

static void DrawChoices_Mode_Fairy_Types(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_FAIRY_TYPES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_Fairy_Types = 0; //Pkmn who have fairy since GEN VI don't have it
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_Fairy_Types = 1; //They do now
    }

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static void DrawChoices_Mode_New_Stats(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_NEW_STATS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_New_Stats = 0; //Old stats
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_New_Stats = 1; //New stats
    }

    //DrawOptionMenuChoice(sText_Encounters_Vanilla_Long, 104, y, styles[0], active);
    //DrawOptionMenuChoice(sText_Encounters_Modern_Long, GetStringRightAlignXOffset(1, sText_Encounters_Modern_Long, 198), y, styles[1], active);
}

static void DrawChoices_Mode_Sturdy(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_STURDY);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_Sturdy = 0; //Old sturdy
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_Sturdy = 1; //New sturdy
    }

    DrawOptionMenuChoice(sText_Encounters_Vanilla_Long, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Encounters_Modern_Long, GetStringRightAlignXOffset(1, sText_Encounters_Modern_Long, 198), y, styles[1], active);
}

static void DrawChoices_Mode_Modern_Moves(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_MODERN_MOVES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_Modern_Moves = 0; //Old movepool, and moves
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_Modern_Moves = 1; //New movepool, and moves
    }

    DrawOptionMenuChoice(sText_Encounters_Vanilla_Long, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Encounters_Modern_Long, GetStringRightAlignXOffset(1, sText_Encounters_Modern_Long, 198), y, styles[1], active);
}

static void DrawChoices_Mode_New_Effectiveness(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_NEW_EFFECTIVENESS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_TypeEffectiveness = 0; //Old type chart
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_TypeEffectiveness = 1; //New type chart
    }

    DrawOptionMenuChoice(sText_Encounters_Vanilla_Long, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Encounters_Modern_Long, GetStringRightAlignXOffset(1, sText_Encounters_Modern_Long, 198), y, styles[1], active);
}

static void DrawChoices_Mode_Legendary_Abilities(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_LEGENDARY_ABILITIES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_Legendary_Abilities = 0; //Pressure as main ability
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_Legendary_Abilities = 1; //New abilities
    }

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static void DrawChoices_Mode_New_Legendaries(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_NEW_LEGENDARIES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_New_Legendaries = 0; //No extra legendaries
        FlagClear (FLAG_EXTRA_LEGENDARIES);
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_New_Legendaries = 1; //7 extra legendaries
        FlagSet (FLAG_EXTRA_LEGENDARIES);
    }

    //DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    //DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static void DrawChoices_Challenges_LessEscapes(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_LESS_ESCAPES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Challenges_LessEscapes = 0; //Run away as usual
    }
    else
    {
        gSaveBlock1Ptr->tx_Challenges_LessEscapes = 1; //Less running away
    }

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static const u8 sText_Challenges_Expensive_Off[]   = _("OFF");
static const u8 sText_Challenges_Expensive_5[]     = _("x5");
static const u8 sText_Challenges_Expensive_10[]    = _("x10");
static const u8 sText_Challenges_Expensive_50[]    = _("x50!");
static const u8 *const sText_Challenges_Expensive_Strings[] = {sText_Challenges_Expensive_Off, sText_Challenges_Expensive_5, sText_Challenges_Expensive_10, sText_Challenges_Expensive_50};
static void DrawChoices_Challenges_Expensive(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_CHALLENGES_EXPENSIVE);
    DrawChoices_Options_Four(sText_Challenges_Expensive_Strings, selection, y, active);
}

static void DrawChoices_Difficulty_Escape_Rope_Dig(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_ESCAPE_ROPE_DIG);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Difficulty_EscapeRopeDig = 0; //YES, Escape rope and dig are allowed. DEFAULT.
    }
    else
    {
        gSaveBlock1Ptr->tx_Difficulty_EscapeRopeDig = 1; //NO, Escape rope and dig are disallowed
    }

    DrawOptionMenuChoice(sText_Yes, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_No, GetStringRightAlignXOffset(1, sText_No, 198), y, styles[1], active);
}

static const u8 sText_Features_Frontier_Ban[]   = _("BAN");
static const u8 sText_Features_Frontier_UnBan[]     = _("UNBAN");
static void DrawChoices_Features_FrontierBans(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_FEATURES_FRONTIER_BANS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Features_FrontierBans = 0; //Ban
    }
    else
    {
        gSaveBlock1Ptr->tx_Features_FrontierBans = 1; //Unban
    }

    //DrawOptionMenuChoice(sText_Features_Frontier_Ban, 104, y, styles[0], active);
    //DrawOptionMenuChoice(sText_Features_Frontier_UnBan, GetStringRightAlignXOffset(1, sText_Features_Frontier_UnBan, 198), y, styles[1], active);
}

/*static const u8 sText_Difficulty_HardExp_Enabled[]   = _("DEFAULT");
static const u8 sText_Difficulty_HardExp_Disabled[]  = _("NORMAL");
static void DrawChoices_Difficulty_HardExp(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_HARD_EXP);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Difficulty_HardExp = 0; //50% EXP gain in HARD
    }
    else
    {
        gSaveBlock1Ptr->tx_Difficulty_HardExp = 1; //100% (usual) EXP gain in HARD
    }

    DrawOptionMenuChoice(sText_Difficulty_HardExp_Enabled, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Difficulty_HardExp_Disabled, GetStringRightAlignXOffset(1, sText_Difficulty_HardExp_Disabled, 198), y, styles[1], active);
}*/


// Background tilemap
#define TILE_TOP_CORNER_L 0x1A2 // 418
#define TILE_TOP_EDGE     0x1A3 // 419
#define TILE_TOP_CORNER_R 0x1A4 // 420
#define TILE_LEFT_EDGE    0x1A5 // 421
#define TILE_RIGHT_EDGE   0x1A7 // 423
#define TILE_BOT_CORNER_L 0x1A8 // 424
#define TILE_BOT_EDGE     0x1A9 // 425
#define TILE_BOT_CORNER_R 0x1AA // 426

static void DrawBgWindowFrames(void)
{
    //                     bg, tile,              x, y, width, height, palNum
    // Option Texts window
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  2,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  2, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  2,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  3,  1, 16,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  3,  1, 16,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 13,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 13, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 13,  1,  1,  7);

    // Description window
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1, 14,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2, 14, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28, 14,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1, 15,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28, 15,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 19,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 19, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 19,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}


// Debug
static void PrintCurrentSelections(void)
{
    u8 i, j;
    #ifndef NDEBUG
    for (i = 0; i < MENU_COUNT; i++)
    {
        MgbaPrintf(MGBA_LOG_DEBUG, "Menu = %d", i);
        for (j = 0; j < MenuItemCountFromIndex(i); j++)
        {
            switch (i)
            {
            case MENU_RANDOMIZER:   MgbaPrintf(MGBA_LOG_DEBUG, "MENU_RANDOMIZER %d",   sOptions->sel_randomizer[j]); break;
            case MENU_NUZLOCKE:     MgbaPrintf(MGBA_LOG_DEBUG, "MENU_NUZLOCKE %d",     sOptions->sel_nuzlocke[j]); break;
            case MENU_DIFFICULTY:   MgbaPrintf(MGBA_LOG_DEBUG, "MENU_DIFFICULTY %d",   sOptions->sel_difficulty[j]); break;
            case MENU_CHALLENGES:   MgbaPrintf(MGBA_LOG_DEBUG, "MENU_CHALLENGES %d",   sOptions->sel_challenges[j]); break;
            }
        }
           
    }
    #endif
}