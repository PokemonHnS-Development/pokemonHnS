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
    MENUITEM_MODE_MODERN_MOVES,
    MENUITEM_MODE_SYNCHRONIZE,
    MENUITEM_MODE_STURDY,
    MENUITEM_MODE_NEW_CITRUS,
    MENUITEM_MODE_FAIRY_TYPES,
    MENUITEM_MODE_LEGENDARY_ABILITIES,
    MENUITEM_MODE_INFINITE_TMS,
    MENUITEM_MODE_MINTS,
    MENUITEM_MODE_SURVIVE_POISON,
    //MENUITEM_MODE_NEW_EFFECTIVENESS,
    //MENUITEM_MODE_MODERN_TYPES,
    //MENUITEM_MODE_NEW_STATS,
    //MENUITEM_MODE_NEW_LEGENDARIES,
    MENUITEM_MODE_NEXT,
    MENUITEM_MODE_COUNT,
};

enum
{
    MENUITEM_FEATURES_RTC_TYPE,
    MENUITEM_FEATURES_SHINY_CHANCE,
    MENUITEM_FEATURES_SHINY_COLOR,
    MENUITEM_FEATURES_ITEM_DROP,
    MENUITEM_FEATURES_FRONTIER_BANS,
    //MENUITEM_FEATURES_UNLIMITED_WT,
    //MENUITEM_FEATURES_EASY_FEEBAS,
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
    MENUITEM_NUZLOCKE_RARE_CANDY,
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
static void DrawChoices_Nuzlocke_RareCandy(int selection, int y);

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
static void DrawChoices_Features_Shiny_Colors(int selection, int y);

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
    //[MENUITEM_MODE_MODERN_TYPES]          = {DrawChoices_Mode_Modern_Types,         ProcessInput_Options_Two},
    [MENUITEM_MODE_FAIRY_TYPES]           = {DrawChoices_Mode_Fairy_Types,          ProcessInput_Options_Two},
    //[MENUITEM_MODE_NEW_STATS]             = {DrawChoices_Mode_New_Stats,            ProcessInput_Options_Two},
    [MENUITEM_MODE_NEW_CITRUS]            = {DrawChoices_Mode_New_Citrus,           ProcessInput_Options_Two},
    [MENUITEM_MODE_MODERN_MOVES]          = {DrawChoices_Mode_Modern_Moves,         ProcessInput_Options_Two},
    [MENUITEM_MODE_LEGENDARY_ABILITIES]   = {DrawChoices_Mode_Legendary_Abilities,  ProcessInput_Options_Two},
    //[MENUITEM_MODE_NEW_LEGENDARIES]       = {DrawChoices_Mode_New_Legendaries,      ProcessInput_Options_Two},
    //[MENUITEM_MODE_NEW_EFFECTIVENESS]     = {DrawChoices_Mode_New_Effectiveness,    ProcessInput_Options_Two},
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
    //[MENUITEM_FEATURES_UNLIMITED_WT]          = {DrawChoices_Features_Unlimited_WT,         ProcessInput_Options_Two},
    [MENUITEM_FEATURES_FRONTIER_BANS]         = {DrawChoices_Features_FrontierBans,         ProcessInput_Options_Two},
    [MENUITEM_FEATURES_SHINY_COLOR]           = {DrawChoices_Features_Shiny_Colors,          ProcessInput_Options_Two},
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
    [MENUITEM_NUZLOCKE_NUZLOCKE]        = {DrawChoices_Challenges_Nuzlocke,     ProcessInput_Options_Four},
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]  = {DrawChoices_Nuzlocke_SpeciesClause,  ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]    = {DrawChoices_Nuzlocke_ShinyClause,    ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_NICKNAMING]      = {DrawChoices_Nuzlocke_Nicknaming,     ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_DELETION]        = {DrawChoices_Nuzlocke_Deletion,       ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_RARE_CANDY]      = {DrawChoices_Nuzlocke_RareCandy,       ProcessInput_Options_Two},
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


static const u8 sText_Gamemode[]            = _("MODO DE JUEGO");
//static const u8 sText_AlternateSpawns[]     = _("ENCUENTROS");
static const u8 sText_InfiniteTMs[]         = _("MT REUTILIZABLES");
static const u8 sText_Poison[]              = _("SOBREVIVIR VENENO");
static const u8 sText_Synchronize[]         = _("SINCRONÍA");
static const u8 sText_Mints[]               = _("MINTAS NATURALEZA");
static const u8 sText_NewCitrus[]           = _("BAYA SITRÓN");
static const u8 sText_ModernTypes[]         = _("{COLOR 3}{SHADOW 3}TIPOS POKéMON");
static const u8 sText_FairyTypes[]          = _("AÑADIR TIPO HADA");
static const u8 sText_NewStats[]            = _("{COLOR 3}{SHADOW 3}ESTADÍS. POKéMON");
static const u8 sText_Sturdy[]              = _("FIRMEZA");
static const u8 sText_Modern_Moves[]        = _("MOVIMIENTOS DE {PKMN}");
static const u8 sText_Legendary_Abilities[] = _("HAB. LEGENDARIAS");
static const u8 sText_New_Legendaries[]     = _("{COLOR 3}{SHADOW 3}EXTRA LEGEND.");
static const u8 sText_New_Effectiveness[]   = _("TABLA DE TIPOS");
static const u8 sText_Next[]                = _("SIGUIENTE");
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
    //[MENUITEM_MODE_MODERN_TYPES]              = sText_ModernTypes,
    [MENUITEM_MODE_FAIRY_TYPES]               = sText_FairyTypes,
    //[MENUITEM_MODE_NEW_STATS]                 = sText_NewStats,
    [MENUITEM_MODE_MODERN_MOVES]              = sText_Modern_Moves,
    [MENUITEM_MODE_LEGENDARY_ABILITIES]       = sText_Legendary_Abilities,
    //[MENUITEM_MODE_NEW_LEGENDARIES]           = sText_New_Legendaries,
    //[MENUITEM_MODE_NEW_EFFECTIVENESS]         = sText_New_Effectiveness,
    [MENUITEM_MODE_NEXT]                      = sText_Next,
};

static const u8 sText_RTC_Type[]            = _("TIPO DE RELOJ");
static const u8 sText_ShinyChance[]         = _("PROB. DE SHINY");
static const u8 sText_ItemDrop[]            = _("OBJETO AL CAER");
static const u8 sText_EasyFeebas[]          = _("{COLOR 3}{SHADOW 3}FEEBAS FÁCIL");
static const u8 sText_Unlimited_WT[]        = _("{COLOR 3}{SHADOW 3}WT ILIMITADO");
static const u8 sText_FrontierBans[]        = _("BANEOS FRONTIER");
static const u8 sText_Shiny_Colors[]        = _("COLORES SHINY");

// Menu left side option names text
static const u8 *const sOptionMenuItemsNamesFeatures[MENUITEM_FEATURES_COUNT] =
{
    [MENUITEM_FEATURES_RTC_TYPE]                  = sText_RTC_Type,
    [MENUITEM_FEATURES_SHINY_CHANCE]              = sText_ShinyChance,
    [MENUITEM_FEATURES_ITEM_DROP]                 = sText_ItemDrop,
    //[MENUITEM_FEATURES_EASY_FEEBAS]               = sText_EasyFeebas,
    //[MENUITEM_FEATURES_UNLIMITED_WT]              = sText_Unlimited_WT,
    [MENUITEM_FEATURES_FRONTIER_BANS]             = sText_FrontierBans,
    [MENUITEM_FEATURES_SHINY_COLOR]               = sText_Shiny_Colors,
    [MENUITEM_FEATURES_NEXT]                      = sText_Next,
};

static const u8 sText_Dummy[] =                     _("DUMMY");
static const u8 sText_Randomizer[] =                _("RANDOMIZER");
static const u8 sText_Starter[] =                   _("POKéMON INICIAL");
static const u8 sText_WildPkmn[] =                  _("POKéMON SALVAJES");
static const u8 sText_Trainer[] =                   _("ENTRENADOR");
static const u8 sText_Static[] =                    _("POKéMON ESTÁTICOS");
static const u8 sText_SimiliarEvolutionLevel[] =    _("EQUILIBRIO");
static const u8 sText_InlcudeLegendaries[]=         _("LEGENDARIOS");
static const u8 sText_Type[] =                      _("TIPO");
static const u8 sText_Moves[] =                     _("MOVIMIENTOS");
static const u8 sText_Abilities[] =                 _("HABILIDADES");
static const u8 sText_Evolutions[] =                _("EVOLUCIONES");
static const u8 sText_EvolutionMethods[] =          _("LÍNEAS EVO");
static const u8 sText_TypeEff[] =                   _("EFECTIVIDAD");
static const u8 sText_Items[] =                     _("OBJETOS");
static const u8 sText_Chaos[] =                     _("MODO CAOS");
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
static const u8 sText_SpeciesClause[]   = _("CLÁUSULA DUPLICADOS");
static const u8 sText_ShinyClause[]     = _("CLÁUSULA SHINY");
static const u8 sText_Nicknaming[]      = _("APODOS");
static const u8 sText_Deletion[]        = _("DESMAYOS");
static const u8 sText_RareCandy[]       = _("CARAMELO RARO INF.");

static const u8 *const sOptionMenuItemsNamesNuzlocke[MENUITEM_NUZLOCKE_COUNT] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]        = sText_Nuzlocke,
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]  = sText_SpeciesClause,
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]    = sText_ShinyClause,
    [MENUITEM_NUZLOCKE_NICKNAMING]      = sText_Nicknaming,
    [MENUITEM_NUZLOCKE_DELETION]        = sText_Deletion,
    [MENUITEM_NUZLOCKE_RARE_CANDY]      = sText_RareCandy,
    [MENUITEM_NUZLOCKE_NEXT]            = sText_Next,
};

//MENU_DIFFICULTY
static const u8 sText_PartyLimit[]          = _("LÍMITE DE EQUIPO");
static const u8 sText_LessEscapes[]         = _("MENOS HUIDAS");
static const u8 sText_LevelCap[]            = _("LÍMITE DE NIVEL");
static const u8 sText_ExpMultiplier[]       = _("MULT. DE EXP.");
static const u8 sText_Items_Player[]        = _("OBJ. DEL JUGADOR");
static const u8 sText_Items_Trainer[]       = _("OBJ. DEL ENTRENADOR");
static const u8 sText_NoEVs[]               = _("EVs DEL JUGADOR");
static const u8 sText_ScalingIVs[]          = _("IVs DEL ENTRENADOR");
static const u8 sText_ScalingEVs[]          = _("EVs DEL ENTRENADOR");
//static const u8 sText_LimitDifficulty[]     = _("DIFICULTAD FIJA");
//static const u8 sText_HardExp[]             = _("EXP. MODO DIFÍCIL");
static const u8 sText_MaxPartyIvs[]         = _("IVs del JUGADOR");
static const u8 sText_DigRope[]             = _("C. HUIDA / AGUANTE");
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
static const u8 sText_Pokecenter[]          = _("CENTRO POKéMON");
static const u8 sText_PCHeal[]              = _("PC CURA A {PKMN}");
static const u8 sText_Expensive[]           = _("¡ULTRA CARO!");
static const u8 sText_EvoLimit[]            = _("LÍMITE EVO");
static const u8 sText_OneTypeChallenge[]    = _("SÓLO UN TIPO");
static const u8 sText_BaseStatEqualizer[]   = _("IGUALADOR DE BST");
static const u8 sText_Mirror[]              = _("MODO ESPEJO");
static const u8 sText_MirrorThief[]         = _("LADRÓN ESPEJO");
static const u8 sText_Save[]                = _("GUARDAR");
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
            //case MENUITEM_MODE_MODERN_TYPES:              return FALSE;
            case MENUITEM_MODE_FAIRY_TYPES:               return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            //case MENUITEM_MODE_NEW_STATS:                 return FALSE;
            case MENUITEM_MODE_STURDY:                    return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_MODERN_MOVES:              return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            case MENUITEM_MODE_LEGENDARY_ABILITIES:       return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
            //case MENUITEM_MODE_NEW_LEGENDARIES:           return FALSE;
            //case MENUITEM_MODE_NEW_EFFECTIVENESS:         return sOptions->sel_mode[MENUITEM_MODE_CLASSIC_MODERN] == 1;
        default:       return FALSE;
        }
    case MENU_FEATURES:
        switch(selection)
        {
            //case MENUITEM_FEATURES_UNLIMITED_WT:            return FALSE;
            //case MENUITEM_FEATURES_EASY_FEEBAS:             return FALSE;
            //case MENUITEM_FEATURES_FRONTIER_BANS:           return FALSE;
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
        case MENUITEM_NUZLOCKE_SPECIES_CLAUSE:
            if ((gSaveBlock1Ptr->tx_Nuzlocke_EasyMode) == 0)
                return sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
            else
                return !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
        case MENUITEM_NUZLOCKE_SHINY_CLAUSE:
            if ((gSaveBlock1Ptr->tx_Nuzlocke_EasyMode) == 0)
                return sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
            else
                return !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
        case MENUITEM_NUZLOCKE_NICKNAMING:
            if ((gSaveBlock1Ptr->tx_Nuzlocke_EasyMode) == 0)
                return sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
            else
                return !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
        case MENUITEM_NUZLOCKE_DELETION:
            if ((gSaveBlock1Ptr->tx_Nuzlocke_EasyMode) == 0)
                return sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
            else
                return !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
        case MENUITEM_NUZLOCKE_RARE_CANDY:
            if ((gSaveBlock1Ptr->tx_Nuzlocke_EasyMode) == 0)
                return sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
            else
                return sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
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
static const u8 sText_Description_Save[]    = _("Guardar opciones y continuar...");

static const u8 sText_Description_Mode_Gamemode_Classic[]         = _("Ajustes recomendados.\n{COLOR 7}{COLOR 8}NOTA: Las elecciones son PERMANENTES.");
static const u8 sText_Description_Mode_Gamemode_Modern[]          = _("Elige tus reglas.\n{COLOR 7}{COLOR 8}OJO: Todo queda FIJO.");
static const u8 sText_Description_Mode_Gamemode_Custom[]          = _("Elige tus reglas.\n{COLOR 7}{COLOR 8}OJO: Todo queda FIJO.");
//static const u8 sText_Description_Mode_AlternateSpawns_Vanilla[]        = _("Encuentros salvajes VANILLA.\nIgual que el original.");
//static const u8 sText_Description_Mode_AlternateSpawns_Postgame[]       = _("VANILLA, pero tras ser campeón\nlos 423 {PKMN} disponibles.");
//static const u8 sText_Description_Mode_AlternateSpawns_Modern[]         = _("Encuentros MODERNOS.\nLos 423 {PKMN} estarán.");
static const u8 sText_Description_Mode_InfiniteTMs_On[]           = _("MT reutilizables.\nSe recomienda Esmeralda moderno.");
static const u8 sText_Description_Mode_InfiniteTMs_Off[]          = _("MT no reutilizables.\nComo en el original.");
static const u8 sText_Description_Mode_SurvivePoison_On[]         = _("Tu {PKMN} sobrevivirá al VENENO\ncon 1 PS.");
static const u8 sText_Description_Mode_SurvivePoison_Off[]        = _("Tu {PKMN} se debilitará si está\nENVENENADO.");
static const u8 sText_Description_Mode_Synchronize_Old[]          = _("SINCRONIZAR funciona como GEN III.\n50% de copiar naturaleza.");
static const u8 sText_Description_Mode_Synchronize_New[]          = _("SINCRONIA funciona como en GEN VIII+.\n100% de copiar la naturaleza.");
static const u8 sText_Description_Mode_Mints_Off[]                = _("Las Mints no están disponibles\nhasta terminar el juego.");
static const u8 sText_Description_Mode_Mints_On[]                 = _("Las Mints se compran en la tienda\nPRETTY PETAL tras la 4ª medalla.");
static const u8 sText_Description_Mode_New_Citrus_Off[]           = _("SITRUS BERRY restaura 30PS.\nIgual que en GEN III.");
static const u8 sText_Description_Mode_New_Citrus_On[]            = _("SITRUS BERRY restaura 25% del\nPS total. Igual que GEN IV+.");
static const u8 sText_Description_Mode_Modern_Types_Off[]         = _("Tipos {PKMN} originales. No incluye\nlos {PKMN} que pasaron a HADA en GEN VI.");
static const u8 sText_Description_Mode_Modern_Types_On[]          = _("{PKMN} con tipos modificados\npara hacerlos más viables.");
static const u8 sText_Description_Mode_Fairy_Types_Off[]          = _("El tipo HADA no se agrega a {PKMN} \nque lo obtuvieron en GEN VI.");
static const u8 sText_Description_Mode_Fairy_Types_On[]           = _("El tipo HADA se agrega o cambia\nen ciertos {PKMN}, como en GEN VI.");
static const u8 sText_Description_Mode_New_Stats_Off[]            = _("Stats originales de GEN III de {PKMN}.");
static const u8 sText_Description_Mode_New_Stats_On[]             = _("Estadísticas modificadas para\nhacer más viables a ciertos {PKMN}.");
static const u8 sText_Description_Mode_Sturdy_Off[]               = _("ROBUSTEZ como en GEN III. Solo\nanula OHKO (GUILOTINA, etc.)");
static const u8 sText_Description_Mode_Sturdy_On[]                = _("ROBUSTEZ como en GEN V+.\n {PKMN} sobreviven con 1 PS.");
static const u8 sText_Description_Mode_Modern_Moves_Off[]         = _("Sin MOVIMIENTOS nuevos, POOL\n {PKMN} original + HUEVO/TUTOR");
static const u8 sText_Description_Mode_Modern_Moves_On[]          = _("13 MOVIMIENTOS nuevos y POOL mejorado\npara todos los {PKMN} + MOVIMIENTOS\nde HUEVO y de ENSEÑANZA nuevos.");
static const u8 sText_Description_Mode_Leg_Abilities_Off[]        = _("PRESIÓN sigue como la habilidad\nprincipal de algunos legendarios.");
static const u8 sText_Description_Mode_Leg_Abilities_On[]         = _("Los legendarios tienen PRESIÓN\ncambiada por una mejor hab.");
static const u8 sText_Description_Mode_New_Legendaries_Off[]      = _("No se añaden legendarios extra.");
static const u8 sText_Description_Mode_New_Legendaries_On[]       = _("Los legendarios extra de GEN I\ny II llegan por eventos.");
static const u8 sText_Description_Mode_New_Effectiveness_Original[]  = _("Eficacia de tipos original\npara todos los tipos.");
static const u8 sText_Description_Mode_New_Effectiveness_Modern[]    = _("Eficacia de tipos nueva y\nbalanceada para ciertos tipos.");
static const u8 sText_Description_Mode_Next[]                     = _("Continuar a opciones de funciones.");

static const u8 *const sOptionMenuItemDescriptionsMode[MENUITEM_MODE_COUNT][5] =
{
    [MENUITEM_MODE_CLASSIC_MODERN]        = {sText_Description_Mode_Gamemode_Classic,       sText_Description_Mode_Gamemode_Modern,       sText_Description_Mode_Gamemode_Custom,             sText_Empty,                                        sText_Empty},
    //[MENUITEM_MODE_ALTERNATE_SPAWNS]      = {sText_Description_Mode_AlternateSpawns_Vanilla,    sText_Description_Mode_AlternateSpawns_Modern,      sText_Description_Mode_AlternateSpawns_Postgame,                                         sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_INFINITE_TMS]          = {sText_Description_Mode_InfiniteTMs_Off,        sText_Description_Mode_InfiniteTMs_On,        sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_SURVIVE_POISON]        = {sText_Description_Mode_SurvivePoison_Off,      sText_Description_Mode_SurvivePoison_On,      sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_SYNCHRONIZE]           = {sText_Description_Mode_Synchronize_Old,        sText_Description_Mode_Synchronize_New,       sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_MINTS]                 = {sText_Description_Mode_Mints_Off,              sText_Description_Mode_Mints_On,              sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_NEW_CITRUS]            = {sText_Description_Mode_New_Citrus_Off,         sText_Description_Mode_New_Citrus_On,         sText_Empty,                                        sText_Empty,                                        sText_Empty},
    //[MENUITEM_MODE_MODERN_TYPES]          = {sText_Description_Mode_Modern_Types_Off,       sText_Description_Mode_Modern_Types_On,       sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_FAIRY_TYPES]           = {sText_Description_Mode_Fairy_Types_Off,        sText_Description_Mode_Fairy_Types_On,        sText_Empty,                                        sText_Empty,                                        sText_Empty},
    //[MENUITEM_MODE_NEW_STATS]             = {sText_Description_Mode_New_Stats_Off,          sText_Description_Mode_New_Stats_On,          sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_STURDY]                = {sText_Description_Mode_Sturdy_Off,             sText_Description_Mode_Sturdy_On,             sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_MODERN_MOVES]          = {sText_Description_Mode_Modern_Moves_Off,       sText_Description_Mode_Modern_Moves_On,       sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_LEGENDARY_ABILITIES]   = {sText_Description_Mode_Leg_Abilities_Off,      sText_Description_Mode_Leg_Abilities_On,      sText_Empty,                                        sText_Empty,                                        sText_Empty},
    //[MENUITEM_MODE_NEW_LEGENDARIES]       = {sText_Description_Mode_New_Legendaries_Off,    sText_Description_Mode_New_Legendaries_On,    sText_Empty,                                        sText_Empty,                                        sText_Empty},
    //[MENUITEM_MODE_NEW_EFFECTIVENESS]     = {sText_Description_Mode_New_Effectiveness_Original,    sText_Description_Mode_New_Effectiveness_Modern,    sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_MODE_NEXT]                  = {sText_Description_Mode_Next,                   sText_Empty,                                  sText_Empty,                                        sText_Empty,                                        sText_Empty},
};

static const u8 sText_Description_Features_RTC_Type_RTC[]             = _("Usar Reloj en Tiempo Real original.");
static const u8 sText_Description_Features_RTC_Type_FakeRTC[]         = _("Usa un reloj falso en tiempo\nreal. 1h real = 1 día en juego.");
static const u8 sText_Description_Features_ItemDrop_On[]              = _("{PKMN} soltará su objeto\nal ser derrotado.");
static const u8 sText_Description_Features_ItemDrop_Off[]             = _("Los objetos salvajes de {PKMN} solo\nse obtienen capturando o con LADRÓN.");
static const u8 sText_Description_Features_ShinyChance_8192[]         = _("Muy baja probabilidad de SHINY.\nProbabilidad por defecto de Gen III.");
static const u8 sText_Description_Features_ShinyChance_4096[]         = _("Baja probabilidad de SHINY.\nProbabilidad por defecto de Gen VI+.");
static const u8 sText_Description_Features_ShinyChance_2048[]         = _("Probabilidad decente de SHINY.");
static const u8 sText_Description_Features_ShinyChance_1024[]         = _("Probabilidad alta de SHINY.");
static const u8 sText_Description_Features_ShinyChance_512[]          = _("Probabilidad muy alta de SHINY.");
static const u8 sText_Description_Features_EasyFeebas_On[]            = _("FEEBAS es más fácil de atrapar y\naparece en toda la RUTA 119.");
static const u8 sText_Description_Features_EasyFeebas_Off[]           = _("FEEBAS aparece en puntos\naleatorios de la RUTA 119.");
static const u8 sText_Description_Features_Unlimited_WT_On[]          = _("Activa un límite diario de 3\nIntercambios Maravilla. Recomendado.");
static const u8 sText_Description_Features_Unlimited_WT_Off[]         = _("Intercambios Prodigiosos sin límite.");
static const u8 sText_Description_Features_FrontierBans_Unban[]       = _("Todos los legendarios pueden\nparticipar en el FRENTE DE BATALLA.");
static const u8 sText_Description_Features_FrontierBans_Ban[]         = _("Legendarios {PKMN} poderosos\nprohibidos en el FRENTE DE BATALLA.");
static const u8 sText_Description_Features_Shiny_Colors_Original[]    = _("Paleta shiny original para todos\nlos POKéMON. Predeterminado.");
static const u8 sText_Description_Features_Shiny_Colors_Modern[]      = _("Algunos shiny POKéMON tienen\npaletas de color nuevas.");

static const u8 sText_Description_Features_Next[]                     = _("Ir a opciones de Randomizer.");

static const u8 *const sOptionMenuItemDescriptionsFeatures[MENUITEM_FEATURES_COUNT][5] =
{
    [MENUITEM_FEATURES_RTC_TYPE]              = {sText_Description_Features_RTC_Type_RTC,           sText_Description_Features_RTC_Type_FakeRTC,      sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_FEATURES_SHINY_CHANCE]          = {sText_Description_Features_ShinyChance_8192,       sText_Description_Features_ShinyChance_4096,      sText_Description_Features_ShinyChance_2048,        sText_Description_Features_ShinyChance_1024,        sText_Description_Features_ShinyChance_512},
    [MENUITEM_FEATURES_ITEM_DROP]             = {sText_Description_Features_ItemDrop_Off,           sText_Description_Features_ItemDrop_On,           sText_Empty,                                        sText_Empty,                                        sText_Empty},
    //[MENUITEM_FEATURES_EASY_FEEBAS]           = {sText_Description_Features_EasyFeebas_Off,         sText_Description_Features_EasyFeebas_On,         sText_Empty,                                        sText_Empty,                                        sText_Empty},
    //[MENUITEM_FEATURES_UNLIMITED_WT]          = {sText_Description_Features_Unlimited_WT_On,        sText_Description_Features_Unlimited_WT_Off,      sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_FEATURES_FRONTIER_BANS]         = {sText_Description_Features_FrontierBans_Ban,       sText_Description_Features_FrontierBans_Unban,    sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_FEATURES_SHINY_COLOR]           = {sText_Description_Features_Shiny_Colors_Original,  sText_Description_Features_Shiny_Colors_Modern,    sText_Empty,                                        sText_Empty,                                        sText_Empty},
    [MENUITEM_FEATURES_NEXT]                  = {sText_Description_Features_Next,                   sText_Empty,                                      sText_Empty,                                        sText_Empty,                                        sText_Empty},
};

static const u8 sText_Description_Randomizer_Off[]                  = _("El juego no será aleatorizado.");
static const u8 sText_Description_Randomizer_On[]                   = _("Juega con aleatorización.\n¡Ajustes abajo!");
static const u8 sText_Description_Random_Starter_Off[]              = _("POKéMON iniciales estándar.");
static const u8 sText_Description_Random_Starter_On[]               = _("Aleatorizar POKéMON iniciales.");
static const u8 sText_Description_Random_WildPokemon_Off[]          = _("Encuentros salvajes iguales\nal juego base.");
static const u8 sText_Description_Random_WildPokemon_On[]           = _("Aleatorizar POKéMON silvestres.");
static const u8 sText_Description_Random_Trainer_Off[]              = _("El entrenador tendrá su equipo\nesperado.");
static const u8 sText_Description_Random_Trainer_On[]               = _("Aleatorizar equipos enemigos.");
static const u8 sText_Description_Random_Static_Off[]               = _("Los encuentros fijos serán iguales\nal juego base.");
static const u8 sText_Description_Random_Static_On[]                = _("Named {PKMN}, casino {PKMN}, roamers, and\nsome other special {PKMN} won't change.");
static const u8 sText_Description_Random_BalanceTiers_Off[]         = _("POKéMON {COLOR 7}{COLOR 8}no balanceados{COLOR 1}{COLOR 2}\nsegún su fuerza!");
static const u8 sText_Description_Random_BalanceTiers_On[]          = _("Se cambian {PKMN} por otros de\nnivel similar según evolución.");
static const u8 sText_Description_Random_IncludeLegendaries_Off[]   = _("Los POKéMON legendarios no se\nincluyen ni se aleatorizan.");
static const u8 sText_Description_Random_IncludeLegendaries_On[]    = _("¡Incluye POKéMON legendarios\nen la aleatorización!");
static const u8 sText_Description_Random_Types_Off[]                = _("Los tipos de POKéMON son los\nmismos que en el juego base.");
static const u8 sText_Description_Random_Types_On[]                 = _("Aleatoriza todos los tipos POKéMON.");
static const u8 sText_Description_Random_Moves_Off[]                = _("Los movimientos de POKéMON son\nlos mismos que en el juego base.");
static const u8 sText_Description_Random_Moves_On[]                 = _("Aleatorizar todos los movimientos.");
static const u8 sText_Description_Random_Abilities_Off[]            = _("Las habilidades de los POKéMON son\nlas mismas que en el juego base.");
static const u8 sText_Description_Random_Abilities_On[]             = _("Aleatorizar todas las habilidades.");
static const u8 sText_Description_Random_Evos_Off[]                 = _("Las evoluciones de los POKéMON son\nlas mismas que en el juego base.");
static const u8 sText_Description_Random_Evos_On[]                  = _("Aleatorizar todas las evoluciones.");
static const u8 sText_Description_Random_Evo_Methods_Off[]          = _("Los POKéMON que pueden evolucionar\nno cambian.");
static const u8 sText_Description_Random_Evo_Methods_On[]           = _("Aleatoriza líneas evolutivas.\n¡Permite nuevas evoluciones!");
static const u8 sText_Description_Random_Effectiveness_Off[]        = _("La tabla de tipos será igual que\nla del juego base.");
static const u8 sText_Description_Random_Effectiveness_On[]         = _("Aleatorizar efectividad de tipos.\n{COLOR 7}{COLOR 8}¡ADVERTENCIA: PUEDE FALLAR!");
static const u8 sText_Description_Random_Items_Off[]                = _("Todos los objetos hallados o recibidos\nson iguales que en el juego base.");
static const u8 sText_Description_Random_Items_On[]                 = _("Aleatoriza objetos encontrados,\nocultos\ny recibidos. ¡Los OBJETOS CLAVE no!");
static const u8 sText_Description_Random_ChaosMode_Off[]            = _("Modo Caos desactivado.");
static const u8 sText_Description_Random_ChaosMode_On[]             = _("Cada opción elegida arriba será\nmuy caótica. {COLOR 7}{COLOR 8}¡NO recomendado!");
static const u8 sText_Description_Random_Next[]                     = _("Ir a opciones de Nuzlocke.");
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

static const u8 sText_Description_Nuzlocke_Base[]               = _("Modo Nuzlocke desactivado.");
static const u8 sText_Description_Nuzlocke_Easy[]               = _("¡Un {PKMN} debilitado no se puede\nusar más! No se aplican más reglas.");
static const u8 sText_Description_Nuzlocke_Normal[]             = _("¡Un Pokémon por ruta! Los Pokémon\nderrotados ya no se pueden usar.");
static const u8 sText_Description_Nuzlocke_Hard[]               = _("Igual que NORMAL, pero además\n{COLOR 7}{COLOR 8}borra la PARTIDA al perder!");
static const u8 sText_Description_Nuzlocke_SpeciesClause_Off[]  = _("El jugador siempre debe atrapar\nel primer Pokémon de cada ruta.");
static const u8 sText_Description_Nuzlocke_SpeciesClause_On[]   = _("Solo cuentan Pokémon no atrapados\nantes. {COLOR 7}{COLOR 8}¡RECOMENDADO!");
static const u8 sText_Description_Nuzlocke_ShinyClause_Off[]    = _("Solo se puede capturar un POKéMON\nvariocolor en el primer encuentro.");
static const u8 sText_Description_Nuzlocke_ShinyClause_On[]     = _("El jugador siempre puede capturar\nPOKéMON variocolor. {COLOR 7}{COLOR 8}¡RECOMENDADO!");
static const u8 sText_Description_Nuzlocke_Nicknaming_Off[]     = _("Los apodos son opcionales.");
static const u8 sText_Description_Nuzlocke_Nicknaming_On[]      = _("Obliga a poner apodo a cada\nPOKéMON. {COLOR 7}{COLOR 8}¡RECOMENDADO!");
static const u8 sText_Description_Nuzlocke_Deletion_Cemetery[]  = _("Los POKéMON debilitados van a la\nPC tras el combate y no vuelven.");
static const u8 sText_Description_Nuzlocke_Deletion_Deletion[]  = _("Los POKéMON debilitados son\n{COLOR 7}{COLOR 8}liberados{COLOR 1}{COLOR 2} tras la batalla!");
static const u8 sText_Description_Nuzlocke_RareCandy_On[]       = _("Caramelos raros infinitos en la\nPC del jugador al iniciar.");
static const u8 sText_Description_Nuzlocke_RareCandy_Off[]       = _("El jugador no tendrá acceso a\n Caramelo Raro Infinito.");
static const u8 sText_Description_Nuzlocke_Next[]               = _("Continuar a opciones de dificultad.");
static const u8 *const sOptionMenuItemDescriptionsNuzlocke[MENUITEM_NUZLOCKE_COUNT][4] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]            = {sText_Description_Nuzlocke_Base,                 sText_Description_Nuzlocke_Easy,                    sText_Description_Nuzlocke_Normal,  sText_Description_Nuzlocke_Hard},
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]      = {sText_Description_Nuzlocke_SpeciesClause_On,     sText_Description_Nuzlocke_SpeciesClause_Off,       sText_Empty,                        sText_Empty},
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]        = {sText_Description_Nuzlocke_ShinyClause_On,       sText_Description_Nuzlocke_ShinyClause_Off,         sText_Empty,                        sText_Empty},
    [MENUITEM_NUZLOCKE_NICKNAMING]          = {sText_Description_Nuzlocke_Nicknaming_On,        sText_Description_Nuzlocke_Nicknaming_Off,          sText_Empty,                        sText_Empty},
    [MENUITEM_NUZLOCKE_DELETION]            = {sText_Description_Nuzlocke_Deletion_Cemetery,    sText_Description_Nuzlocke_Deletion_Deletion,       sText_Empty,                        sText_Empty},
    [MENUITEM_NUZLOCKE_RARE_CANDY]          = {sText_Description_Nuzlocke_RareCandy_On,            sText_Description_Nuzlocke_RareCandy_Off,               sText_Empty,                        sText_Empty},
    [MENUITEM_NUZLOCKE_NEXT]                = {sText_Description_Nuzlocke_Next,                 sText_Empty,                                        sText_Empty,                        sText_Empty},
};

static const u8 sText_Description_Difficulty_Party_Limit[]              = _("Limita la cantidad de {PKMN} en el equipo.\n{COLOR 7}{COLOR 8}“1” falla en DOBLE BATALLA.");
static const u8 sText_Description_Difficulty_LevelCap_Base[]            = _("Sin límite de nivel. Puedes subirlo.\n");
static const u8 sText_Description_Difficulty_LevelCap_Normal[]          = _("El nivel máximo depende del\nmayor POKéMON del próximo gimnasio.");
static const u8 sText_Description_Difficulty_LevelCap_Hard[]            = _("El nivel máximo se basa en el\nnivel {COLOR 7}{COLOR 8}más bajo del próximo gimnasio.");
static const u8 sText_Description_Difficulty_ExpMultiplier_1_0[]        = _("POKéMON gana EXP. normal.\nSe acumula con EXP. de MODO DIFÍCIL.");
static const u8 sText_Description_Difficulty_ExpMultiplier_1_5[]        = _("Los POKéMON ganan 50% más puntos de\nEXP. ¡Se acumula con EXP MODO DIFÍCIL!");
static const u8 sText_Description_Difficulty_ExpMultiplier_2_0[]        = _("POKéMON ganan doble EXP. Puntos!\nSe acumula con EXP MODO DIFÍCIL.");
static const u8 sText_Description_Difficulty_ExpMultiplier_0_0[]        = _("POKéMON ganan {COLOR 7}{COLOR 8}CERO EXP. Puntos!!!\nAplica también a EXP MODO DIFÍCIL.");
static const u8 sText_Description_Difficulty_Items_Player_Yes[]         = _("El jugador puede usar objetos.");
static const u8 sText_Description_Difficulty_Items_Player_No[]          = _("El jugador {COLOR 7}{COLOR 8}NO puede usar\nobjetos de combate. ¡Sí objetos equip!");
static const u8 sText_Description_Difficulty_Items_Trainer_Yes[]        = _("Los rivales pueden usar objetos.");
static const u8 sText_Description_Difficulty_Items_Trainer_No[]         = _("Los rivales {COLOR 7}{COLOR 8}NO usan\nobjetos de combate.");
static const u8 sText_Description_Difficulty_NoEVs_Off[]                = _("Tus POKéMON ganan EVs\ncomo es habitual.");
static const u8 sText_Description_Difficulty_NoEVs_On[]                 = _("Tus POKéMON {COLOR 7}{COLOR 8}NO{COLOR 1}{COLOR 2}\nganan ningún EV!");
static const u8 sText_Description_Difficulty_ScalingIVs_Off[]           = _("Los POKéMON del rival tienen\nlos IVs esperados.");
static const u8 sText_Description_Difficulty_ScalingIVs_Scaling[]       = _("Los IVs de los POKéMON de\nEntrenadores suben con medallas!");
static const u8 sText_Description_Difficulty_ScalingIVs_Hard[]          = _("Todos los POKéMON de Entrenador\ntienen IVs perfectos!");
static const u8 sText_Description_Difficulty_ScalingEVs_Off[]           = _("Los POKéMON del rival\nno tienen EVs.");
static const u8 sText_Description_Difficulty_ScalingEVs_Scaling[]       = _("Los EVs de los POKéMON de\nEntrenadores suben con medallas!");
static const u8 sText_Description_Difficulty_ScalingEVs_Hard[]          = _("¡Los POKéMON rivales tienen EVs altos!");
static const u8 sText_Description_Difficulty_ScalingEVs_Extreme[]       = _("Todos los POKéMON rivales tienen\n{COLOR 7}{COLOR 8}252 EVs! ¡Muy difícil!");
static const u8 sText_Description_Difficulty_Next[]                     = _("Continúa a las opciones de desafío.");
static const u8 sText_Description_Challenges_LimitDifficulty_Off[]      = _("Cambia la dificultad cuando y\ndonde quieras.");
static const u8 sText_Description_Challenges_LimitDifficulty_On[]       = _("No se puede cambiar la dificultad.\nMODO DIFICIL fija ESTILO en FIJO.");
static const u8 sText_Description_Difficulty_MaxPartyIvs_Off[]          = _("Tus POKéMON tienen los IVs\nesperados (entre 0 y 31).");
static const u8 sText_Description_Difficulty_MaxPartyIvs_On[]           = _("Los IVs de tus POKéMON\nsiempre son el maximo (31).");
static const u8 sText_Description_Difficulty_MaxPartyIvs_On_HP[]        = _("Los IVs se fijan entre 30 y 31\npara variar Poder Oculto.");
static const u8 sText_Description_Difficulty_LessEscapes_Off[]          = _("El jugador puede huir de los\ncombates facilmente, como siempre.");
static const u8 sText_Description_Difficulty_LessEscapes_On[]           = _("El jugador no puede huir\nfácilmente. ¡Usa repelentes!");
static const u8 sText_Description_Difficulty_EscapeRopeDig_Off[]        = _("CUERDA HUIDA y EXCAVAR no\nsirven para salir de mazmorras.");
static const u8 sText_Description_Difficulty_EscapeRopeDig_On[]         = _("CUERDA HUIDA y EXCAVAR\nsirven para salir de mazmorras.");
//static const u8 sText_Description_Difficulty_HardExp_Enabled[]          = _("{PKMN} ganan 60% del EXP total en\nDIFÍCIL. {COLOR 7}{COLOR 8}RECOMENDADO, buen desafío.");
//static const u8 sText_Description_Difficulty_HardExp_Disabled[]         = _("{PKMN} ganan EXP normal en DIFÍCIL.\n{COLOR 7}{COLOR 8}NO RECOMENDADO, lo hace fácil.");
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

static const u8 sText_Description_Difficulty_Pokecenter_Yes[]           = _("El jugador puede visitar los\nCentros Poké para curar a su equipo.");
static const u8 sText_Description_Difficulty_Pokecenter_No[]            = _("El jugador {COLOR 7}{COLOR 8}NO PUEDE visitar\nPokécenters ni otros lugares\npara curar a su equipo.");
static const u8 sText_Description_Challenges_PCHeal_Yes[]               = _("Los POKéMON depositados en la PC\nse curarán como de costumbre.");
static const u8 sText_Description_Challenges_PCHeal_No[]                = _("Los POKéMON en la PC\nno serán curados.");
static const u8 sText_Description_Challenges_EvoLimit_Base[]            = _("Los POKéMON evolucionan normal.");
static const u8 sText_Description_Challenges_EvoLimit_First[]           = _("Los POKéMON solo pueden evolucionar\na su primera evolución.");
static const u8 sText_Description_Challenges_EvoLimit_All[]             = _("¡Los POKéMON {COLOR 7}{COLOR 8}NO pueden evolucionar!");
static const u8 sText_Description_Challenges_OneTypeChallenge[]         = _("Solo se permite un tipo de POKéMON\nque el jugador pueda capturar y usar.");
static const u8 sText_Description_Challenges_BaseStatEqualizer_Base[]   = _("Todos los POKéMON tienen sus\nestadísticas base originales.");
static const u8 sText_Description_Challenges_BaseStatEqualizer_100[]    = _("Estadísticas calculadas con\n100 en cada estadística base.");
static const u8 sText_Description_Challenges_BaseStatEqualizer_255[]    = _("Estadísticas calculadas con\n255 en cada estadística base.");
static const u8 sText_Description_Challenges_BaseStatEqualizer_500[]    = _("Estadísticas calculadas con\n500 en cada estadística base.");
static const u8 sText_Description_Challenges_Mirror_Off[]               = _("El jugador usa su propio equipo.");
static const u8 sText_Description_Challenges_Mirror_Trainer[]           = _("¡En batallas contra Entrenadores\nobtienes el equipo del rival!");
static const u8 sText_Description_Challenges_Mirror_All[]               = _("¡El jugador obtiene una copia\ndel equipo enemigo en {COLOR 7}{COLOR 8}TODAS\nlas batallas!");
static const u8 sText_Description_Challenges_MirrorThief_Off[]          = _("Recuperas tu equipo tras\nlas batallas.");
static const u8 sText_Description_Challenges_MirrorThief_On[]           = _("¡El jugador conserva el equipo\nenemigo tras la batalla!");
static const u8 sText_Description_Challenges_Expensive_0ff[]            = _("Todo tiene el costo habitual.");
static const u8 sText_Description_Challenges_Expensive_5[]              = _("¡Todo es 5 veces más\ncaro!");
static const u8 sText_Description_Challenges_Expensive_10[]             = _("¡Todo cuesta 10 veces más!\nEl capitalismo de siempre.");
static const u8 sText_Description_Challenges_Expensive_50[]             = _("¡Todo cuesta 50 veces más!\n¡Capitalismo ultra!");
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
static const u8 sText_Description_Disabled_Feature[]  = _("{COLOR 7}{COLOR 8}Esta función no está\ndisponible para este juego.");
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
    //[MENUITEM_MODE_MODERN_TYPES]          = sText_Description_Disabled_Feature,
    [MENUITEM_MODE_FAIRY_TYPES]           = sText_Empty,
    //[MENUITEM_MODE_NEW_STATS]             = sText_Description_Disabled_Feature,
    [MENUITEM_MODE_MODERN_MOVES]          = sText_Empty,
    [MENUITEM_MODE_NEXT]                  = sText_Empty,
    [MENUITEM_MODE_LEGENDARY_ABILITIES]   = sText_Empty,
    //[MENUITEM_MODE_NEW_LEGENDARIES]       = sText_Description_Disabled_Feature,
    //[MENUITEM_MODE_NEW_EFFECTIVENESS]     = sText_Empty,
};

// Disabled descriptions
static const u8 *const sOptionMenuItemDescriptionsDisabledFeatures[MENUITEM_FEATURES_COUNT] =
{
    [MENUITEM_FEATURES_RTC_TYPE]              = sText_Empty,
    [MENUITEM_FEATURES_SHINY_CHANCE]          = sText_Empty,
    [MENUITEM_FEATURES_ITEM_DROP]             = sText_Empty,
    //[MENUITEM_FEATURES_EASY_FEEBAS]           = sText_Description_Disabled_Feature,
    //[MENUITEM_FEATURES_UNLIMITED_WT]          = sText_Description_Disabled_Feature,
    [MENUITEM_FEATURES_FRONTIER_BANS]         = sText_Empty,
    [MENUITEM_FEATURES_SHINY_COLOR]           = sText_Empty,
    [MENUITEM_FEATURES_NEXT]                  = sText_Empty,
};

static const u8 sText_Description_Disabled_Random_SimiliarEvolutionLevel[]  = _("Solo usable con inicial aleatorio,\nPOKéMON de Entrenador, salvaje o fijo.");
static const u8 sText_Description_Disabled_Random_IncludeLegendaries[]      = _("Solo usable con inicial aleatorio,\nPOKéMON de Entrenador, salvaje o fijo.");
static const u8 sText_Description_Disabled_Random_Chaos_Mode[]              = _("Solo usable si otras opciones\nal azar están activadas.");
static const u8 sText_Description_Disabled_Random_Type_Effectiveness[]      = _("No disponible actualmente.");
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

static const u8 sText_Description_Disabled_Nuzlocke_Nuzlocke[]   = _("¡Solo para Nuzlocke!");
static const u8 *const sOptionMenuItemDescriptionsDisabledNuzlocke[MENUITEM_NUZLOCKE_COUNT] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]            = sText_Empty,
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]      = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]        = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_NICKNAMING]          = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_DELETION]            = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_RARE_CANDY]          = sText_Description_Disabled_Nuzlocke_Nuzlocke,
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

static const u8 sText_Description_Disabled_Challenges_MirrorThief[]    = _("¡Solo para Mirror Mode!");
static const u8 sText_Description_Disabled_Features_PCHeal[]  = _("Desactivado en el\nReto POKéCENTER.");
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

static const u8 sText_TopBar_Left[]             = _("{L_BUTTON}ANTERIOR");
static const u8 sText_TopBar_Right[]            = _("{R_BUTTON}SIGUIENTE");
static const u8 sText_TopBar_Mode[]             = _("MODO DE JUEGO");
static const u8 sText_TopBar_Features[]         = _("FUNCIONES");
static const u8 sText_TopBar_Randomizer[]       = _("RANDOMIZER");
static const u8 sText_TopBar_Nuzlocke[]         = _("NUZLOCKE");
static const u8 sText_TopBar_Difficulty[]       = _("DIFICULTAD");
static const u8 sText_TopBar_Challenges[]       = _("DESAFÍOS");
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
        //gSaveBlock1Ptr->tx_Mode_TypeEffectiveness           = TX_MODE_TYPE_EFFECTIVENESS;

        gSaveBlock1Ptr->tx_Features_RTCType                 = TX_FEATURES_RTC_TYPE;
        gSaveBlock1Ptr->tx_Features_ShinyChance             = TX_FEATURES_SHINY_CHANCE;
        gSaveBlock1Ptr->tx_Features_WildMonDropItems        = TX_FEATURES_ITEM_DROP;
        //gSaveBlock1Ptr->tx_Features_EasierFeebas            = TX_FEATURES_EASIER_FEEBAS;
        gSaveBlock1Ptr->tx_Features_Unlimited_WT            = TX_FEATURES_UNLIMITED_WT;
        gSaveBlock1Ptr->tx_Features_FrontierBans            = TX_FEATURES_FRONTIER_BANS;
        gSaveBlock1Ptr->tx_Features_ShinyColors             = TX_FEATURES_SHINY_COLORS;

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
        gSaveBlock1Ptr->tx_Nuzlocke_RareCandy               = TX_NUZLOCKE_RARE_CANDY;
    
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
        //sOptions->sel_mode[MENUITEM_MODE_MODERN_TYPES]           = gSaveBlock1Ptr->tx_Mode_Modern_Types;
        sOptions->sel_mode[MENUITEM_MODE_FAIRY_TYPES]            = gSaveBlock1Ptr->tx_Mode_Fairy_Types;
        //sOptions->sel_mode[MENUITEM_MODE_NEW_STATS]              = gSaveBlock1Ptr->tx_Mode_New_Stats;
        sOptions->sel_mode[MENUITEM_MODE_STURDY]                 = gSaveBlock1Ptr->tx_Mode_Sturdy;
        sOptions->sel_mode[MENUITEM_MODE_MODERN_MOVES]           = gSaveBlock1Ptr->tx_Mode_Modern_Moves;
        sOptions->sel_mode[MENUITEM_MODE_LEGENDARY_ABILITIES]    = gSaveBlock1Ptr->tx_Mode_Legendary_Abilities;
        //sOptions->sel_mode[MENUITEM_MODE_NEW_LEGENDARIES]        = gSaveBlock1Ptr->tx_Mode_New_Legendaries;
        //sOptions->sel_mode[MENUITEM_MODE_NEW_EFFECTIVENESS]      = gSaveBlock1Ptr->tx_Mode_TypeEffectiveness;
        //MENU FEATURES
        sOptions->sel_features[MENUITEM_FEATURES_RTC_TYPE]               = gSaveBlock1Ptr->tx_Features_RTCType;
        sOptions->sel_features[MENUITEM_FEATURES_SHINY_CHANCE]           = gSaveBlock1Ptr->tx_Features_ShinyChance;
        sOptions->sel_features[MENUITEM_FEATURES_ITEM_DROP]              = gSaveBlock1Ptr->tx_Features_WildMonDropItems;
        //sOptions->sel_features[MENUITEM_FEATURES_EASY_FEEBAS]            = gSaveBlock1Ptr->tx_Features_EasierFeebas;
        //sOptions->sel_features[MENUITEM_FEATURES_UNLIMITED_WT]           = gSaveBlock1Ptr->tx_Features_Unlimited_WT;
        sOptions->sel_features[MENUITEM_FEATURES_FRONTIER_BANS]          = gSaveBlock1Ptr->tx_Features_FrontierBans;
        sOptions->sel_features[MENUITEM_FEATURES_SHINY_COLOR]            = gSaveBlock1Ptr->tx_Features_ShinyColors;
        
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
            sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE] = 3;
        else if (gSaveBlock1Ptr->tx_Challenges_Nuzlocke)
            sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE] = 2;
        else if (gSaveBlock1Ptr->tx_Nuzlocke_EasyMode)
            sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE] = 1;
        else
            sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE] = 0;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SPECIES_CLAUSE]    = !gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SHINY_CLAUSE]      = !gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NICKNAMING]        = !gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_DELETION]          = gSaveBlock1Ptr->tx_Nuzlocke_Deletion;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_RARE_CANDY]        = gSaveBlock1Ptr->tx_Nuzlocke_RareCandy;
        
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
    //gSaveBlock1Ptr->tx_Mode_Modern_Types                = sOptions->sel_mode[MENUITEM_MODE_MODERN_TYPES]; 
    gSaveBlock1Ptr->tx_Mode_Fairy_Types                 = sOptions->sel_mode[MENUITEM_MODE_FAIRY_TYPES]; 
    //gSaveBlock1Ptr->tx_Mode_New_Stats                   = sOptions->sel_mode[MENUITEM_MODE_NEW_STATS]; 
    gSaveBlock1Ptr->tx_Mode_Sturdy                      = sOptions->sel_mode[MENUITEM_MODE_STURDY]; 
    gSaveBlock1Ptr->tx_Mode_Modern_Moves                = sOptions->sel_mode[MENUITEM_MODE_MODERN_MOVES]; 
    gSaveBlock1Ptr->tx_Mode_Legendary_Abilities         = sOptions->sel_mode[MENUITEM_MODE_LEGENDARY_ABILITIES]; 
    //gSaveBlock1Ptr->tx_Mode_New_Legendaries             = sOptions->sel_mode[MENUITEM_MODE_NEW_LEGENDARIES]; 
    //gSaveBlock1Ptr->tx_Mode_TypeEffectiveness           = sOptions->sel_mode[MENUITEM_MODE_NEW_EFFECTIVENESS];
    //MENU FEAUTRES
    gSaveBlock1Ptr->tx_Features_RTCType                     = sOptions->sel_features[MENUITEM_FEATURES_RTC_TYPE]; 
    gSaveBlock1Ptr->tx_Features_ShinyChance                 = sOptions->sel_features[MENUITEM_FEATURES_SHINY_CHANCE]; 
    gSaveBlock1Ptr->tx_Features_WildMonDropItems            = sOptions->sel_features[MENUITEM_FEATURES_ITEM_DROP]; 
    //gSaveBlock1Ptr->tx_Features_EasierFeebas                = sOptions->sel_features[MENUITEM_FEATURES_EASY_FEEBAS]; 
    //gSaveBlock1Ptr->tx_Features_Unlimited_WT                = sOptions->sel_features[MENUITEM_FEATURES_UNLIMITED_WT]; 
    gSaveBlock1Ptr->tx_Features_FrontierBans                = sOptions->sel_features[MENUITEM_FEATURES_FRONTIER_BANS]; 
    gSaveBlock1Ptr->tx_Features_ShinyColors                 = sOptions->sel_features[MENUITEM_FEATURES_SHINY_COLOR];
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
        gSaveBlock1Ptr->tx_Nuzlocke_EasyMode           = FALSE;
        gSaveBlock1Ptr->tx_Challenges_Nuzlocke          = FALSE;
        gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore  = FALSE;
        break;
    case 1:
        gSaveBlock1Ptr->tx_Nuzlocke_EasyMode           = TRUE;
        gSaveBlock1Ptr->tx_Challenges_Nuzlocke          = FALSE;
        gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore  = FALSE;
        break;
    case 2:
        gSaveBlock1Ptr->tx_Nuzlocke_EasyMode           = FALSE;
        gSaveBlock1Ptr->tx_Challenges_Nuzlocke          = TRUE;
        gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore  = FALSE;
        break;
    case 3:
        gSaveBlock1Ptr->tx_Nuzlocke_EasyMode           = FALSE;
        gSaveBlock1Ptr->tx_Challenges_Nuzlocke          = TRUE;
        gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore  = TRUE;
        break;
    }
    if (gSaveBlock1Ptr->tx_Nuzlocke_EasyMode)
    {
        gSaveBlock1Ptr->tx_Nuzlocke_RareCandy        = !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_RARE_CANDY];
    }
    if (gSaveBlock1Ptr->tx_Challenges_Nuzlocke)
    {
        gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause   = !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SPECIES_CLAUSE];
        gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause     = !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SHINY_CLAUSE];
        gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming      = !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NICKNAMING];
        gSaveBlock1Ptr->tx_Nuzlocke_Deletion        = sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_DELETION];
        gSaveBlock1Ptr->tx_Nuzlocke_RareCandy        = !sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_RARE_CANDY];
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

// Dibuja los valores de una opcion midiendo cada texto antes de colocarlo.
// Si no caben todos, muestra solo los que entran: nunca se solapan.
#define CHOICE_X_START 104
#define CHOICE_X_END   198
#define CHOICE_GAP     6
#define CHOICE_MAX     6

static void DrawChoiceRowFrom(const u8 *const *strings, int count, int selection, int y, bool8 active, int showCount)
{
    u32 widths[CHOICE_MAX];
    int idx[CHOICE_MAX];
    int n = 0;
    int i, x, total;

    if (count > CHOICE_MAX)
        count = CHOICE_MAX;

    for (i = 0; i < count && n < showCount; i++)
        idx[n++] = (selection + i) % count;

    for (i = 0; i < n; i++)
        widths[i] = GetStringWidth(FONT_NORMAL, strings[idx[i]], 0);

    while (n > 1)
    {
        total = 0;
        for (i = 0; i < n; i++)
            total += (int)widths[i] + CHOICE_GAP;
        if (total - CHOICE_GAP <= CHOICE_X_END - CHOICE_X_START)
            break;
        n--;
    }

    for (i = 0, x = CHOICE_X_START; i < n; i++)
    {
        DrawOptionMenuChoice(strings[idx[i]], x, y, (idx[i] == selection), active);
        x += (int)widths[i] + CHOICE_GAP;
    }
}

static void DrawChoices_Options_Four(const u8 *const *const strings, int selection, int y, bool8 active)
{
    DrawChoiceRowFrom(strings, 4, selection, y, active, 3);
}


static void DrawChoices_Options_Three(const u8 *const *const strings, int selection, int y, bool8 active)
{
    DrawChoiceRowFrom(strings, 3, selection, y, active, 2);
}



static void DrawChoices_Options_Five(const u8 *const *const strings, int selection, int y, bool8 active)
{
    DrawChoiceRowFrom(strings, 5, selection, y, active, 3);
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
static const u8 sText_Off[]  = _("DESACT.");
static const u8 sText_On[]   = _("ACT.");
static const u8 sText_None[] = _("NINGUNO");
static void DrawChoices_Random_OffOn(int selection, int y, bool8 active)
{
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}


static const u8 sClassic[]  = _("RECOMENDADO");
static const u8 sModern[]   = _("MODERNO");
static const u8 sCustom[]   = _("PERSONALIZADO");
static const u8 *const sText_Mode_Strings[] = {sClassic,  sCustom};

static void DrawChoices_Mode_Classic_Modern_Selector(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MODE_CLASSIC_MODERN);

    static const u8 *const rowStrings[] = {sClassic, sCustom};
    DrawChoiceRowFrom(rowStrings, 2, selection, y, active, 2);
    
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
        FlagSet (FLAG_MINTS_ENABLED);
        sOptions->sel_mode[MENUITEM_MODE_NEW_CITRUS]                = !TX_MODE_NEW_CITRUS;
        gSaveBlock1Ptr->tx_Mode_New_Citrus = 1;
        //sOptions->sel_mode[MENUITEM_MODE_MODERN_TYPES]              = TX_MODE_MODERN_TYPES;
        //gSaveBlock1Ptr->tx_Mode_Modern_Types = 0;
        sOptions->sel_mode[MENUITEM_MODE_FAIRY_TYPES]               = !TX_MODE_FAIRY_TYPES;
        gSaveBlock1Ptr->tx_Mode_Fairy_Types = 1;
        //sOptions->sel_mode[MENUITEM_MODE_NEW_STATS]                 = TX_MODE_NEW_STATS;
        //gSaveBlock1Ptr->tx_Mode_New_Stats = 0;
        sOptions->sel_mode[MENUITEM_MODE_STURDY]                    = !TX_MODE_STURDY;
        gSaveBlock1Ptr->tx_Mode_Sturdy = 1;
        sOptions->sel_mode[MENUITEM_MODE_MODERN_MOVES]              = !TX_MODE_MODERN_MOVES;
        gSaveBlock1Ptr->tx_Mode_Modern_Moves = 1;
        sOptions->sel_mode[MENUITEM_MODE_LEGENDARY_ABILITIES]       = !TX_MODE_LEGENDARY_ABILITIES;
        gSaveBlock1Ptr->tx_Mode_Legendary_Abilities = 1;
        //sOptions->sel_mode[MENUITEM_MODE_NEW_LEGENDARIES]           = TX_MODE_NEW_LEGENDARIES;
        //gSaveBlock1Ptr->tx_Mode_New_Legendaries = 0;
        //sOptions->sel_mode[MENUITEM_MODE_NEW_EFFECTIVENESS]         = TX_MODE_TYPE_EFFECTIVENESS;
        gSaveBlock1Ptr->tx_Mode_TypeEffectiveness = 1;
    }
}

static const u8 sText_Random[]  = _("ALEATORIO");
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

static const u8 sText_Random_Chaos[] = _("CAOS");
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

static const u8 sText_Challenges_Nuzlocke_Easy[]        = _("FÁCIL");
static const u8 sText_Challenges_Nuzlocke_Normal[]      = _("NORMAL");
static const u8 sText_Challenges_Nuzlocke_Hardcore[]    = _("DIFÍCIL");
static const u8 *const sText_Nuzlocke_Strings[] = {sText_Off, sText_Challenges_Nuzlocke_Easy, sText_Challenges_Nuzlocke_Normal, sText_Challenges_Nuzlocke_Hardcore};

static void DrawChoices_Challenges_Nuzlocke(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_NUZLOCKE);
    DrawChoices_Options_Four(sText_Nuzlocke_Strings, selection, y, active);

    if (selection == 0)
    {
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SPECIES_CLAUSE]    = !TX_NUZLOCKE_SPECIES_CLAUSE;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SHINY_CLAUSE]      = !TX_NUZLOCKE_SHINY_CLAUSE; 
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NICKNAMING]        = !TX_NUZLOCKE_NICKNAMING;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_DELETION]          = TX_NUZLOCKE_DELETION;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_RARE_CANDY]          = !TX_NUZLOCKE_RARE_CANDY;
        gSaveBlock1Ptr->tx_Nuzlocke_EasyMode = 0; //off
    }
    else if (selection == 1)
    {
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SPECIES_CLAUSE]    = !TX_NUZLOCKE_SPECIES_CLAUSE;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_SHINY_CLAUSE]      = !TX_NUZLOCKE_SHINY_CLAUSE; 
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_NICKNAMING]        = !TX_NUZLOCKE_NICKNAMING;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_DELETION]          = TX_NUZLOCKE_DELETION;
        sOptions->sel_nuzlocke[MENUITEM_NUZLOCKE_RARE_CANDY]          = !TX_NUZLOCKE_RARE_CANDY;
        gSaveBlock1Ptr->tx_Nuzlocke_EasyMode = 1; //on
    }
    else
        gSaveBlock1Ptr->tx_Nuzlocke_EasyMode = 0; //off
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
static const u8 sText_Nuzlocke_Cemetery[]  = _("CEMENTERIO");
static const u8 sText_Nuzlocke_Deletion[]  = _("LIBERAR");
static void DrawChoices_Nuzlocke_Deletion(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_DELETION);
    static const u8 *const rowStrings[] = {sText_Nuzlocke_Cemetery, sText_Nuzlocke_Deletion};
    DrawChoiceRowFrom(rowStrings, 2, selection, y, active, 2);
}
static void DrawChoices_Nuzlocke_RareCandy(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_RARE_CANDY);
    DrawChoices_Nuzlocke_OnOff(selection, y, active);
}

// MENU_DIFFICULTY
static const u8 sText_Yes[] = _("SÍ");
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
static const u8 sText_ScalingIVsEVs_Scaling[]   = _("ESCALADO");
static const u8 sText_ScalingIVsEVs_Hard[]      = _("DIFÍCIL");
static void DrawChoices_Challenges_ScalingIVs(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_SCALING_IVS);

    static const u8 *const rowStrings[] = {sText_Off, sText_ScalingIVsEVs_Scaling, sText_ScalingIVsEVs_Hard};
    DrawChoiceRowFrom(rowStrings, 3, selection, y, active, 3);
}
static const u8 sText_ScalingIVsEVs_Extrem[]    = _("EXTREMO");
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

    static const u8 *const rowStrings[] = {sText_Off, sText_Challenges_PartyLimit_5, sText_Challenges_PartyLimit_4, sText_Challenges_PartyLimit_3, sText_Challenges_PartyLimit_2, sText_Challenges_PartyLimit_1};
    DrawChoiceRowFrom(rowStrings, 6, selection, y, active, 6);
}

static const u8 sText_Challenges_LevelCap_Normal[]  = _("NORMAL");
static const u8 sText_Challenges_LevelCap_Hard[]    = _("DIFÍCIL");
static void DrawChoices_Challenges_LevelCap(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_LEVEL_CAP);

    static const u8 *const rowStrings[] = {sText_Off, sText_Challenges_LevelCap_Normal, sText_Challenges_LevelCap_Hard};
    DrawChoiceRowFrom(rowStrings, 3, selection, y, active, 3);
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
static const u8 sText_Challenges_EvoLimit_First[]   = _("PRIMERO");
static const u8 sText_Challenges_EvoLimit_All[]     = _("TODO");
static void DrawChoices_Challenges_EvoLimit(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_CHALLENGES_EVO_LIMIT);

    static const u8 *const rowStrings[] = {sText_Off, sText_Challenges_EvoLimit_First, sText_Challenges_EvoLimit_All};
    DrawChoiceRowFrom(rowStrings, 3, selection, y, active, 3);
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

static const u8 sText_Challenges_Mirror_All[]   = _("TODO");
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
static const u8 sText_Features_RTC_Fake_RTC[]   = _("RTC FALSO");
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
static const u8 sText_Encounters_Modern_Long[]    = _("MODERNO");

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


    static const u8 *const rowStrings[] = {sText_Yes, sText_No, sText_Max_Party_IVs_30_31};
    DrawChoiceRowFrom(rowStrings, 3, selection, y, active, 3);
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

/*static void DrawChoices_Features_Unlimited_WT(int selection, int y)
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
}*/

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

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_New_Citrus = 0; //No new citrus, old citrus
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_New_Citrus = 1; //Yes new citrus
    }

    static const u8 *const rowStrings[] = {sText_Encounters_Vanilla_Long, sText_Encounters_Modern_Long};
    DrawChoiceRowFrom(rowStrings, 2, selection, y, active, 2);
}

/*static void DrawChoices_Mode_Modern_Types(int selection, int y)
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
}*/

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

/*static void DrawChoices_Mode_New_Stats(int selection, int y)
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
}*/

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

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Mode_Modern_Moves = 0; //Old movepool, and moves
    }
    else
    {
        gSaveBlock1Ptr->tx_Mode_Modern_Moves = 1; //New movepool, and moves
    }

    static const u8 *const rowStrings[] = {sText_Encounters_Vanilla_Long, sText_Encounters_Modern_Long};
    DrawChoiceRowFrom(rowStrings, 2, selection, y, active, 2);
}

/*static void DrawChoices_Mode_New_Effectiveness(int selection, int y)
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
}*/

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

/*static void DrawChoices_Mode_New_Legendaries(int selection, int y)
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
}*/

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

static const u8 sText_Features_Frontier_Ban[]   = _("BANEO");
static const u8 sText_Features_Frontier_UnBan[]     = _("DESBANEO");
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

    DrawOptionMenuChoice(sText_Features_Frontier_Ban, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Features_Frontier_UnBan, GetStringRightAlignXOffset(1, sText_Features_Frontier_UnBan, 198), y, styles[1], active);
}

/*static const u8 sText_Difficulty_HardExp_Enabled[]   = _("PREDETERM.");
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

static void DrawChoices_Features_Shiny_Colors(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_FEATURES_SHINY_COLOR);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock1Ptr->tx_Features_ShinyColors = 0; //Old shinies
    }
    else
    {
        gSaveBlock1Ptr->tx_Features_ShinyColors = 1; //New shinies
    }

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}


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