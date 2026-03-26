// tx_rac_viewer.c
#include "global.h"
#include "main.h"
#include "bg.h"
#include "gpu_regs.h"
#include "window.h"
#include "menu.h"
#include "scanline_effect.h"
#include "palette.h"
#include "sprite.h"
#include "sound.h"
#include "task.h"
#include "malloc.h"
#include "overworld.h"
#include "text.h"
#include "text_window.h"
#include "string_util.h"
#include "international_string_util.h" // for GetStringRightAlignXOffset
#include "strings.h"
#include "gba/m4a_internal.h"
#include "constants/rgb.h"
#include "event_data.h"
#include "tx_randomizer_and_challenges.h"

// ---- Paging ----
enum
{
    VIEWER_PAGE_MODE = 0,   // page 1
    VIEWER_PAGE_2,          // page 2
    VIEWER_PAGE_3,          // page 3
    VIEWER_PAGE_4,          // page 4
    VIEWER_PAGE_5,          // page 5
    VIEWER_PAGE_6,          // page 6  <-- add this
    VIEWER_PAGE_COUNT
};


static u8 sPage;    // current page index


// ---- Layout matches tx_rac_menu ------------------------------------------------

// Windows: top bar, options list area, description area.
enum
{
    WIN_TOPBAR,
    WIN_OPTIONS,
    WIN_DESCRIPTION,
};

static const struct BgTemplate sViewerBgTemplates[] =
{
    { // bg0 (options text)
        .bg = 0, .charBaseIndex = 1, .mapBaseIndex = 30, .screenSize = 0,
        .paletteMode = 0, .priority = 1, .baseTile = 0
    },
    { // bg1 (frame tiles and top/desc windows)
        .bg = 1, .charBaseIndex = 1, .mapBaseIndex = 31, .screenSize = 0,
        .paletteMode = 0, .priority = 0, .baseTile = 0
    },
};

static const struct WindowTemplate sViewerWinTemplates[] =
{
    { // WIN_TOPBAR
        .bg = 1, .tilemapLeft = 0, .tilemapTop = 0, .width = 30, .height = 2,
        .paletteNum = 1, .baseBlock = 2
    },
    { // WIN_OPTIONS (content list area) — move to BG1 so it shows
        .bg = 1, .tilemapLeft = 2, .tilemapTop = 3,
        .width = 26, .height = 10,
        .paletteNum = 1, .baseBlock = 62
    },
    { // WIN_DESCRIPTION
        .bg = 1, .tilemapLeft = 2, .tilemapTop = 15, .width = 26, .height = 4,
        .paletteNum = 1, .baseBlock = 500
    },
    DUMMY_WIN_TEMPLATE
};

// The menu loads the window frame tiles into BG1 at base tile 0x1A2
// and uses those tile ids to draw the big rectangles. Reuse that here.
#define TILE_TOP_CORNER_L 0x1A2
#define TILE_TOP_EDGE     0x1A3
#define TILE_TOP_CORNER_R 0x1A4
#define TILE_LEFT_EDGE    0x1A5
#define TILE_RIGHT_EDGE   0x1A7
#define TILE_BOT_CORNER_L 0x1A8
#define TILE_BOT_EDGE     0x1A9
#define TILE_BOT_CORNER_R 0x1AA
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

// ---- Scrolling state ----
#define VIEWER_VISIBLE_ROWS 5
static u8 sTopIndex;

// ---- Cursor state (read-only highlight) ----
static u16 sCurIndex;   // absolute row index on current page


// --- Viewer-only text/colors (keep local; do not export) ---
//page 1 Mode
static const u8 sText_InfiniteTMs_Label[]   = _("REUSABLE TMS");
static const u8 sText_SurvivePoison_Label[] = _("SURVIVE POISON");
static const u8 sText_Synchronize_Label[]   = _("SYNCHRONIZE");
static const u8 sText_Mints_Label[]         = _("NATURE MINTS");
static const u8 sText_NewCitrus_Label[]     = _("SITRUS BERRY");
static const u8 sText_FairyTypes_Label[]    = _("ADD FAIRY TYPE");
static const u8 sText_Sturdy_Label[]        = _("STURDY");
static const u8 sText_ModernMoves_Label[]   = _("{PKMN} MOVEPOOL");
static const u8 sText_LegendaryAbils_Label[]= _("LEGEN. ABILITIES");

//page 2 Features
static const u8 sText_RTCType_Label[]      = _("CLOCK TYPE");
static const u8 sText_ShinyChance_Label[]  = _("SHINY CHANCE");
static const u8 sText_ItemDrops_Label[]    = _("ITEM DROP");
static const u8 sText_FrontierBans_Label[] = _("FRONTIER BANS");
static const u8 sText_ShinyColors_Label[]  = _("SHINY COLORS");

// page 3 (Randomizer)
static const u8 sText_Randomizer[]            = _("RANDOMIZER");
static const u8 sText_Rand_Starter[]          = _("STARTER POKéMON");
static const u8 sText_Rand_Wild[]             = _("WILD POKéMON");
static const u8 sText_Rand_Trainer[]          = _("TRAINER");
static const u8 sText_Rand_Static[]           = _("RANDOM STATIC");
static const u8 sText_Rand_SimilarEvoLvl[]    = _("BALANCING");
static const u8 sText_Rand_IncludeLegends[]   = _("LEGENDARIES");
static const u8 sText_Rand_Type[]             = _("TYPE");
static const u8 sText_Rand_Moves[]            = _("MOVES");
static const u8 sText_Rand_Abilities[]        = _("ABILITIES");
static const u8 sText_Rand_Evolutions[]       = _("EVOLUTIONS");
static const u8 sText_Rand_EvoMethods[]       = _("EVO LINES");
static const u8 sText_Rand_TypeEffect[]       = _("EFFECTIVENESS");
static const u8 sText_Rand_Items[]            = _("ITEMS");
static const u8 sText_Rand_Chaos[]            = _("CHAOS");


// page 4 (Nuzlocke)
static const u8 sText_Nuz_Nuzlocke[]         = _("NUZLOCKE");
static const u8 sText_Nuz_Hardcore[]         = _("NUZLOCKE HARDCORE");
static const u8 sText_Nuz_Mode[]             = _("NUZLOCKE MODE");
static const u8 sText_Nuz_SpeciesClause[]    = _("DUPES CLAUSE");
static const u8 sText_Nuz_ShinyClause[]      = _("SHINY CLAUSE");
static const u8 sText_Nuz_Nicknaming[]       = _("NICKNAMES");
static const u8 sText_Nuz_Fainting[]         = _("FAINTING");
static const u8 sText_Nuz_RareCandy[]        = _("INF. RARE CANDY");

// page 5 (Difficulty) — labels
static const u8 sText_Diff_PartyLimit[]      = _("PARTY LIMIT");
static const u8 sText_Diff_LevelCap[]        = _("LEVEL CAP");
static const u8 sText_Diff_ExpMult[]         = _("EXP. MULTIPLIER");
static const u8 sText_Diff_NoItemPlayer[]    = _("PLAYER ITEMS");
static const u8 sText_Diff_NoItemTrainer[]   = _("TRAINER ITEMS");
static const u8 sText_Diff_PartyIVs[]        = _("PLAYER IVs");
static const u8 sText_Diff_TrainerIVs[]      = _("TRAINER IVs");
static const u8 sText_Diff_PlayerEVs[]       = _("PLAYER EVs");
static const u8 sText_Diff_TrainerEVs[]      = _("TRAINER EVs");
static const u8 sText_Diff_LessEscapes[]     = _("LESS ESCAPES");
static const u8 sText_Diff_EscapeRopeDig[]   = _("ESC. ROPE / DIG");

// page 6 (Other Challenges) — labels
static const u8 sText_Chk_PkmnCenter[]        = _("POKéCENTER");
static const u8 sText_Chk_PCHeal[]            = _("PC HEAL {PKMN}");
static const u8 sText_Chk_Expensive[]         = _("ULTRA EXPENSIVE!");
static const u8 sText_Chk_EvoLimit[]          = _("EVO LIMIT");
static const u8 sText_Chk_OneType[]           = _("ONE TYPE ONLY");
static const u8 sText_Chk_BaseStatEq[]        = _("BST EQUALIZER");
static const u8 sText_Chk_Mirror[]            = _("MIRROR MODE");
static const u8 sText_Chk_MirrorThief[]       = _("MIRROR THIEF");

//Options
static const u8 sText_On[]  = _("ON");
static const u8 sText_Off[] = _("OFF");
static const u8 sText_Yes[]   = _("YES");
static const u8 sText_No[]    = _("NO");
static const u8 sText_Original[]  = _("ORIGINAL");
static const u8 sText_Modern[]    = _("MODERN");
static const u8 sText_RTC[]     = _("RTC");
static const u8 sText_FakeRTC[] = _("FAKE RTC");
static const u8 sText_Frontier_Ban[]     = _("BAN");
static const u8 sText_Frontier_Unban[]   = _("UNBAN");
static const u8 sText_Nuz_Mode_Off[]        = _("OFF");
static const u8 sText_Nuz_Mode_Easy[]       = _("EASY");
static const u8 sText_Nuz_Mode_Standard[]   = _("NORMAL");
static const u8 sText_Nuz_Mode_Hardcore[]   = _("HARD");
static const u8 sText_Nuz_Fainting_Cemetery[]   = _("CEMETERY");
static const u8 sText_Nuz_Fainting_Release[]    = _("RELEASE");

// Party Limit: OFF,5,4,3,2,1
static const u8 sPL_Off[] = _("OFF");
static const u8 sPL_5[]   = _("5");
static const u8 sPL_4[]   = _("4");
static const u8 sPL_3[]   = _("3");
static const u8 sPL_2[]   = _("2");
static const u8 sPL_1[]   = _("1");
static const u8 *const sText_Diff_PartyLimit_Strings[] = {
    sPL_Off, sPL_5, sPL_4, sPL_3, sPL_2, sPL_1
};
static const u8 sLC_Off[]  = _("OFF");
static const u8 sLC_Easy[] = _("EASY");
static const u8 sLC_Hard[] = _("HARD");
static const u8 *const sText_Diff_LevelCap_Strings[] = {
    sLC_Off, sLC_Easy, sLC_Hard
};
static const u8 sEM_1x[]   = _("1x");
static const u8 sEM_15x[]  = _("1.5x");
static const u8 sEM_2x[]   = _("2x");
static const u8 sEM_0x[]   = _("0x");
static const u8 *const sText_Diff_ExpMult_Strings[] = {
    sEM_1x, sEM_15x, sEM_2x, sEM_0x
};
static const u8 sIVs_Yes[]   = _("YES");
static const u8 sIVs_No[]    = _("NO");
static const u8 sIVs_NoHP[]  = _("NO (HP)");
static const u8 *const sText_Diff_PlayerIVs_Strings[] = {
    sIVs_Yes, sIVs_No, sIVs_NoHP
};
static const u8 sTrainerEVs_Off[]   = _("OFF");
static const u8 sTrainerEVs_Scale[] = _("SCALE");
static const u8 sTrainerEVs_Hard[]  = _("HARD");
static const u8 sTrainerEVs_Extreme[]  = _("EXTREME");
static const u8 *const sText_TrainerEV_Strings[] = {
    sTrainerEVs_Off, sTrainerEVs_Scale, sTrainerEVs_Hard, sTrainerEVs_Extreme
};
static const u8 sEX_Off[]  = _("OFF");
static const u8 sEX_5x[]   = _("x5");
static const u8 sEX_10x[]  = _("x10");
static const u8 sEX_50x[]  = _("x50!");
static const u8 *const sText_Chk_Expensive_Strings[] = { sEX_Off, sEX_5x, sEX_10x, sEX_50x };
static const u8 sEL_Off[]   = _("OFF");
static const u8 sEL_First[] = _("FIRST");
static const u8 sEL_All[]   = _("ALL");
static const u8 *const sText_Chk_EvoLimit_Strings[] = { sEL_Off, sEL_First, sEL_All };
static const u8 sBE_Off[]  = _("OFF");
static const u8 sBE_100[]  = _("100");
static const u8 sBE_255[]  = _("255");
static const u8 sBE_500[]  = _("500");
static const u8 *const sText_Chk_BaseStatEq_Strings[] = { sBE_Off, sBE_100, sBE_255, sBE_500 };
// --- One Type Challenge display strings (index == type constant) ---
static const u8 sTypeName_Normal[]   = _("NORMAL");
static const u8 sTypeName_Fighting[] = _("FIGHTING");
static const u8 sTypeName_Flying[]   = _("FLYING");
static const u8 sTypeName_Poison[]   = _("POISON");
static const u8 sTypeName_Ground[]   = _("GROUND");
static const u8 sTypeName_Rock[]     = _("ROCK");
static const u8 sTypeName_Bug[]      = _("BUG");
static const u8 sTypeName_Ghost[]    = _("GHOST");
static const u8 sTypeName_Steel[]    = _("STEEL");
static const u8 sTypeName_Mystery[]  = _("MYSTERY");
static const u8 sTypeName_Fire[]     = _("FIRE");
static const u8 sTypeName_Water[]    = _("WATER");
static const u8 sTypeName_Grass[]    = _("GRASS");
static const u8 sTypeName_Electric[] = _("ELECTRIC");
static const u8 sTypeName_Psychic[]  = _("PSYCHIC");
static const u8 sTypeName_Ice[]      = _("ICE");
static const u8 sTypeName_Dragon[]   = _("DRAGON");
static const u8 sTypeName_Dark[]     = _("DARK");
static const u8 sTypeName_Fairy[]    = _("FAIRY");

// Display "OFF" when value is out of range
static const u8 sText_TypeOff[] = _("OFF");

// Index order matches your TYPE_* defines (0..18)
static const u8 *const sTypeNames[19] = {
    sTypeName_Normal,   // 0
    sTypeName_Fighting, // 1
    sTypeName_Flying,   // 2
    sTypeName_Poison,   // 3
    sTypeName_Ground,   // 4
    sTypeName_Rock,     // 5
    sTypeName_Bug,      // 6
    sTypeName_Ghost,    // 7
    sTypeName_Steel,    // 8
    sTypeName_Mystery,  // 9
    sTypeName_Fire,     // 10
    sTypeName_Water,    // 11
    sTypeName_Grass,    // 12
    sTypeName_Electric, // 13
    sTypeName_Psychic,  // 14
    sTypeName_Ice,      // 15
    sTypeName_Dragon,   // 16
    sTypeName_Dark,     // 17
    sTypeName_Fairy     // 18
};

// Color triplets: {bg, fg, shadow} — keep choices close to menu look
static const u8 sTextWhite[3] = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE,     TEXT_COLOR_DARK_GRAY };
static const u8 sTextGray[3]  = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY };
static const u8 sTextSel[3]   = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_GREEN,     TEXT_COLOR_DARK_GRAY };

static const u16 sOptionMenuText_Pal[] = INCBIN_U16("graphics/interface/option_menu_text_custom.gbapal");


// Colors to match tx_rac_menu (bg, fg, shadow)
static const u8 sColorLeftActive[3]  = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_ORANGE_FG,    TEXT_COLOR_OPTIONS_ORANGE_SHADOW };
static const u8 sColorLeftGray[3]    = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_GRAY_LIGHT_FG, TEXT_COLOR_OPTIONS_GRAY_SHADOW };
static const u8 sColorRightRed[3]    = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_RED_FG,       TEXT_COLOR_OPTIONS_RED_SHADOW };
static const u8 sColorRightRedDark[3]= { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_RED_DARK_FG,  TEXT_COLOR_OPTIONS_RED_DARK_SHADOW };
static const u8 sColorRightGray[3]   = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_GRAY_FG,      TEXT_COLOR_OPTIONS_GRAY_SHADOW };

// Top bar / desc strings
static const u8 sViewerTopLeft[] = _("CHALLENGE VIEWER");
static const u8 sViewerDesc[] = _("{DPAD_UP}/{DPAD_DOWN} : Scroll     {L_BUTTON}/{R_BUTTON} : Change Page\n{A_BUTTON}/{B_BUTTON} : Exit       {START_BUTTON} : Edit");

// Match tx_rac_menu background (light blue)
static const u16 sOptionMenuBg_Pal[] = { RGB(17, 18, 31) };


// fwd decls
static void CB2_InitChallengeViewer(void);
static void Viewer_MainCB2(void);
static void Viewer_VBlankCB(void);
static void Task_ViewerFadeIn(u8 taskId);
static void Task_ViewerInput(u8 taskId);
static void Task_ViewerFadeOutBegin(u8 taskId);
static void Task_ViewerFadeOut(u8 taskId);

static void DrawBgWindowFrames(void);
static void DrawTopBar(void);
static void DrawDescription(void);
static void Viewer_DrawMode_InfiniteTMs(void);

// ----- Generic row plumbing (bool rows first) -----
typedef u8 (*ViewerGetterFn)(void); // returns selected index

struct ViewerBoolRow {
    const u8 *label;       // left-side text
    ViewerGetterFn getSel; // returns 0/1
};

// Reuse the existing color triplets & ON/OFF strings.
extern const u8 sText_On[];
extern const u8 sText_Off[];

static const u8 sText_Challenges_ShinyChance_8192[]   = _("8192");
static const u8 sText_Challenges_ShinyChance_4096[]   = _("4096");
static const u8 sText_Challenges_ShinyChance_2048[]   = _("2048");
static const u8 sText_Challenges_ShinyChance_1024[]   = _("1024");
static const u8 sText_Challenges_ShinyChance_512[]    = _("512");
static const u8 *const sText_Challenges_ShinyChance_Strings[] = {sText_Challenges_ShinyChance_8192,  sText_Challenges_ShinyChance_4096,  sText_Challenges_ShinyChance_2048,  sText_Challenges_ShinyChance_1024,  sText_Challenges_ShinyChance_512};

static inline void Viewer_ClearRow(u8 visRow, bool8 selected)
{
    const int y = visRow * 16;
    // Normal row uses PIXEL_FILL(1); highlighted row uses PIXEL_FILL(15)
    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(selected ? 3 : 1), 0, y, 26 * 8, 16);
}

static void Viewer_DrawBoolRow(u8 rowIndex, const u8 *label, u8 sel, bool8 selected)
{
    const int y = rowIndex * 16;

    // Clear background for this row (normal or highlighted)
    Viewer_ClearRow(rowIndex, selected);

    // Left label (orange like the menu)
    AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                 sColorLeftActive, TEXT_SKIP_DRAW, label);

    // Right choices: selected one in red, the other in gray (menu style)
    const u8 *offStyle = (sel == 0) ? sColorRightRed  : sColorRightGray;
    const u8 *onStyle  = (sel == 1) ? sColorRightRed  : sColorRightGray;

    AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                 offStyle, TEXT_SKIP_DRAW, sText_Off);
    AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL,
                                 GetStringRightAlignXOffset(1, sText_On, 198), y, 0, 0,
                                 onStyle, TEXT_SKIP_DRAW, sText_On);
}


// Draw a row with a single right-aligned value (for multi-state settings)
static void Viewer_DrawSingleValueRow(u8 rowIndex, const u8 *label, const u8 *valueText, bool8 selected)
{
    const int y = rowIndex * 16;

    // Clear background for this row (normal or highlighted)
    Viewer_ClearRow(rowIndex, selected);

    // Left label (orange like the menu)
    AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                 sColorLeftActive, TEXT_SKIP_DRAW, label);

    // Single value on the right (red/highlighted)
    int xRight = GetStringRightAlignXOffset(1, valueText, 198);
    AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xRight, y, 0, 0,
                                 sColorRightRed, TEXT_SKIP_DRAW, valueText);
}



//Page 1
static u8 GetSel_InfiniteTMs(void)        { return gSaveBlock1Ptr->tx_Mode_InfiniteTMs       ? 1 : 0; }
static u8 GetSel_SurvivePoison(void)      { return gSaveBlock1Ptr->tx_Mode_PoisonSurvive     ? 1 : 0; }
static u8 GetSel_Synchronize(void)        { return gSaveBlock1Ptr->tx_Mode_Synchronize       ? 1 : 0; }
static u8 GetSel_Mints(void)              { return gSaveBlock1Ptr->tx_Mode_Mints             ? 1 : 0; }
static u8 GetSel_NewCitrus(void)          { return gSaveBlock1Ptr->tx_Mode_New_Citrus        ? 1 : 0; }
static u8 GetSel_FairyTypes(void)         { return gSaveBlock1Ptr->tx_Mode_Fairy_Types       ? 1 : 0; }
static u8 GetSel_Sturdy(void)             { return gSaveBlock1Ptr->tx_Mode_Sturdy            ? 1 : 0; }
static u8 GetSel_ModernMoves(void)        { return gSaveBlock1Ptr->tx_Mode_Modern_Moves      ? 1 : 0; }
static u8 GetSel_LegendaryAbilities(void) { return gSaveBlock1Ptr->tx_Mode_Legendary_Abilities ? 1 : 0; }

//Page 2
static u8 GetSel_Feature_RTCType(void)      { return gSaveBlock1Ptr->tx_Features_RTCType          ? 1 : 0; }
static u8 GetSel_Feature_ShinyChance(void)  { return gSaveBlock1Ptr->tx_Features_ShinyChance      ? 1 : 0; }
static u8 GetSel_Feature_ItemDrops(void)    { return gSaveBlock1Ptr->tx_Features_WildMonDropItems ? 1 : 0; }
static u8 GetSel_Feature_FrontierBans(void) { return (gSaveBlock1Ptr->tx_Features_FrontierBans==0)     ? 1 : 0; } //reversed from the rest
static u8 GetSel_Feature_ShinyColors(void)  { return gSaveBlock1Ptr->tx_Features_ShinyColors      ? 1 : 0; }

// Page 3 (Randomizer) getters
static u8 GetSel_Randomizer(void)
{
    if (IsRandomizerActivated())
        return 1;
    else
        return 0;
}
static u8 GetSel_Rand_Starter(void)        { return gSaveBlock1Ptr->tx_Random_Starter            ? 1 : 0; }
static u8 GetSel_Rand_Wild(void)           { return gSaveBlock1Ptr->tx_Random_WildPokemon        ? 1 : 0; }
static u8 GetSel_Rand_Trainer(void)        { return gSaveBlock1Ptr->tx_Random_Trainer            ? 1 : 0; }
static u8 GetSel_Rand_Static(void)         { return gSaveBlock1Ptr->tx_Random_Static             ? 1 : 0; }
static u8 GetSel_Rand_SimilarEvoLvl(void)  { return gSaveBlock1Ptr->tx_Random_Similar            ? 1 : 0; }
static u8 GetSel_Rand_IncludeLegends(void) { return gSaveBlock1Ptr->tx_Random_IncludeLegendaries ? 1 : 0; }
static u8 GetSel_Rand_Type(void)           { return gSaveBlock1Ptr->tx_Random_Type               ? 1 : 0; }
static u8 GetSel_Rand_Moves(void)          { return gSaveBlock1Ptr->tx_Random_Moves              ? 1 : 0; }
static u8 GetSel_Rand_Abilities(void)      { return gSaveBlock1Ptr->tx_Random_Abilities          ? 1 : 0; }
static u8 GetSel_Rand_Evolutions(void)     { return gSaveBlock1Ptr->tx_Random_Evolutions         ? 1 : 0; }
static u8 GetSel_Rand_EvoMethods(void)     { return gSaveBlock1Ptr->tx_Random_EvolutionMethods   ? 1 : 0; }
static u8 GetSel_Rand_TypeEffect(void)     { return gSaveBlock1Ptr->tx_Random_TypeEffectiveness  ? 1 : 0; }
static u8 GetSel_Rand_Items(void)          { return gSaveBlock1Ptr->tx_Random_Items              ? 1 : 0; }
static u8 GetSel_Rand_Chaos(void)          { return gSaveBlock1Ptr->tx_Random_Chaos              ? 1 : 0; }

// Page 4 (Nuzlocke) getters
// Returns 0=OFF, 1=EASY, 2=STANDARD, 3=HARDCORE based on how the menu writes the flags
static u8 GetNuzlockeModeIndex(void)
{
    if (gSaveBlock1Ptr->tx_Nuzlocke_EasyMode)                      // case 1 in the menu switch
        return 1;
    if (!gSaveBlock1Ptr->tx_Challenges_Nuzlocke)                   // case 0 in the menu switch
        return 0;
    if (gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore)            // case 3 in the menu switch
        return 3;
    return 2;                                                      // case 2: standard Nuzlocke
}
static u8 GetSel_Nuz_Nuzlocke(void)        { return gSaveBlock1Ptr->tx_Challenges_Nuzlocke         ? 1 : 0; }
static u8 GetSel_Nuz_Hardcore(void)        { return gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore ? 1 : 0; }
static u8 GetSel_Nuz_SpeciesClause(void)   { return gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause      ? 1 : 0; }
static u8 GetSel_Nuz_ShinyClause(void)     { return gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause        ? 1 : 0; }
static u8 GetSel_Nuz_Nicknaming(void)      { return gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming         ? 1 : 0; }
static u8 GetSel_Nuz_Deletion(void)        { return gSaveBlock1Ptr->tx_Nuzlocke_Deletion           ? 1 : 0; } 
static u8 GetSel_Nuz_RareCandy(void)       { return gSaveBlock1Ptr->tx_Nuzlocke_RareCandy          ? 1 : 0; }

// ---- Page 5 getters ----
// Multi-choice rows
static u8 GetSel_Diff_PartyLimit(void)      { return gSaveBlock1Ptr->tx_Challenges_PartyLimit; }      // 0..5 (OFF,5,4,3,2,1)
static u8 GetSel_Diff_LevelCap(void)        { return gSaveBlock1Ptr->tx_Challenges_LevelCap; }        // 0..2 (Off, Easy, Hard)
static u8 GetSel_Diff_ExpMult(void)         { return gSaveBlock1Ptr->tx_Challenges_ExpMultiplier; }   // 0..3 (1x,1.5x,2x,0x)
static u8 GetSel_Diff_PlayerIVs(void)       { return gSaveBlock1Ptr->tx_Challenges_MaxPartyIVs; }     //0..2 (Yes, No, No(HP))
static u8 GetSel_Diff_TrainerIVs(void)      { return gSaveBlock1Ptr->tx_Challenges_TrainerScalingIVs; } // 0..2 (Off, Scale, Hard)
static u8 GetSel_Diff_TrainerEVs(void)      { return gSaveBlock1Ptr->tx_Challenges_TrainerScalingEVs; } // 0..3 (Off, Scale, Hard, Extreme)

// Plain bool rows (normalize to 0/1 for the shared bool renderer)
static u8 GetSel_Diff_NoItemPlayer(void)    { return gSaveBlock1Ptr->tx_Challenges_NoItemPlayer ? 1 : 0; } //Yes/No
static u8 GetSel_Diff_NoItemTrainer(void)   { return gSaveBlock1Ptr->tx_Challenges_NoItemTrainer ? 1 : 0; } //Yes/No
static u8 GetSel_Diff_PlayerEVs(void)       { return gSaveBlock1Ptr->tx_Challenges_NoEVs ? 1 : 0; } //Yes/No
static u8 GetSel_Diff_EscapeRopeDig(void)   { return (gSaveBlock1Ptr->tx_Difficulty_EscapeRopeDig==0) ? 1 : 0; }//Inverted
static u8 GetSel_Diff_LessEscapes(void)     { return gSaveBlock1Ptr->tx_Challenges_LessEscapes ? 1 : 0; } //Yes/No

// ---- Page 6 getters ----
// Multi-choice rows return raw index; bool rows return 0/1
static u8 GetSel_Chk_PkmnCenter(void)      { return gSaveBlock1Ptr->tx_Challenges_PkmnCenter ? 1 : 0; }
static u8 GetSel_Chk_PCHeal(void)          { return gSaveBlock1Ptr->tx_Challenges_PCHeal ? 1 : 0; }

// Expensive (0..3) => OFF, 5X, 10X, 50X
static u8 GetSel_Chk_Expensive(void)
{
    u8 v = gSaveBlock1Ptr->tx_Challenges_Expensive;
    if (v > 3) v = 0;
    return v;
}

// Evo Limit (0..2) => OFF, FIRST, ALL
static u8 GetSel_Chk_EvoLimit(void)
{
    u8 v = gSaveBlock1Ptr->tx_Challenges_EvoLimit;
    if (v > 2) v = 0;
    return v;
}

static u8 GetSel_Chk_OneType(void)         { return (gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge==0) ? 1 : 0; }

// Base Stat Equalizer (0..3) => OFF, 100, 255, 500
static u8 GetSel_Chk_BaseStatEq(void)
{
    u8 v = gSaveBlock1Ptr->tx_Challenges_BaseStatEqualizer;
    if (v > 3) v = 0;
    return v;
}

static u8 GetSel_Chk_Mirror(void)          { return gSaveBlock1Ptr->tx_Challenges_Mirror ? 1 : 0; }
static u8 GetSel_Chk_MirrorThief(void)     { return gSaveBlock1Ptr->tx_Challenges_Mirror_Thief ? 1 : 0; }



static const struct ViewerBoolRow sBoolRows[] = {
    { sText_ModernMoves_Label,   GetSel_ModernMoves        },
    { sText_Synchronize_Label,   GetSel_Synchronize        },
    { sText_Sturdy_Label,        GetSel_Sturdy             },
    { sText_NewCitrus_Label,     GetSel_NewCitrus          },
    { sText_FairyTypes_Label,    GetSel_FairyTypes         },
    { sText_LegendaryAbils_Label,GetSel_LegendaryAbilities },
    { sText_InfiniteTMs_Label,   GetSel_InfiniteTMs        },
    { sText_Mints_Label,         GetSel_Mints              },
    { sText_SurvivePoison_Label, GetSel_SurvivePoison      },
};

static const struct ViewerBoolRow sBoolRows_Page2[] = {
    { sText_RTCType_Label,      GetSel_Feature_RTCType      },
    { sText_ShinyChance_Label,  GetSel_Feature_ShinyChance  },
    { sText_ShinyColors_Label,  GetSel_Feature_ShinyColors  },
    { sText_ItemDrops_Label,    GetSel_Feature_ItemDrops    },
    { sText_FrontierBans_Label, GetSel_Feature_FrontierBans },
};

// Page 3 (Randomizer)
static const struct ViewerBoolRow sBoolRows_Page3[] = {
    { sText_Randomizer,          GetSel_Randomizer          },
    { sText_Rand_Starter,        GetSel_Rand_Starter        },
    { sText_Rand_Wild,           GetSel_Rand_Wild           },
    { sText_Rand_Trainer,        GetSel_Rand_Trainer        },
    { sText_Rand_Static,         GetSel_Rand_Static         },
    { sText_Rand_SimilarEvoLvl,  GetSel_Rand_SimilarEvoLvl  },
    { sText_Rand_IncludeLegends, GetSel_Rand_IncludeLegends },
    { sText_Rand_Type,           GetSel_Rand_Type           },
    { sText_Rand_Moves,          GetSel_Rand_Moves          },
    { sText_Rand_Abilities,      GetSel_Rand_Abilities      },
    { sText_Rand_Evolutions,     GetSel_Rand_Evolutions     },
    { sText_Rand_EvoMethods,     GetSel_Rand_EvoMethods     },
    { sText_Rand_TypeEffect,     GetSel_Rand_TypeEffect     },
    { sText_Rand_Items,          GetSel_Rand_Items          },
    { sText_Rand_Chaos,          GetSel_Rand_Chaos          },
};

// Page 4 (Nuzlocke)
// For Page 4 we keep the bool row table for the subordinate options only;
// row 0 is drawn specially (single value) and not part of this array.
static const struct ViewerBoolRow sBoolRows_Page4[] = {
    { sText_Nuz_SpeciesClause, GetSel_Nuz_SpeciesClause },
    { sText_Nuz_ShinyClause,   GetSel_Nuz_ShinyClause   },
    { sText_Nuz_Nicknaming,    GetSel_Nuz_Nicknaming    },
    { sText_Nuz_Fainting,      GetSel_Nuz_Deletion      },
    { sText_Nuz_RareCandy,     GetSel_Nuz_RareCandy     },
};

// Page 5 (Difficulty) — for the bool-style rows we reuse the generic bool renderer.
// The multi-choice rows will be handled in the page draw switch.
static const struct ViewerBoolRow sBoolRows_Page5[] = {
    { sText_Diff_PartyLimit,    NULL }, // idx 0 — single-value
    { sText_Diff_LevelCap,      NULL }, // idx 1 — single-value
    { sText_Diff_ExpMult,       NULL }, // idx 2 — single-value
    { sText_Diff_NoItemPlayer,  GetSel_Diff_NoItemPlayer  }, // idx 3
    { sText_Diff_NoItemTrainer, GetSel_Diff_NoItemTrainer }, // idx 4
    { sText_Diff_PartyIVs,      NULL }, // idx 5
    { sText_Diff_TrainerIVs,    NULL }, // idx 6 — single-value
    { sText_Diff_PlayerEVs,     GetSel_Diff_PlayerEVs }, // idx 7 — single-value
    { sText_Diff_TrainerEVs,    NULL }, // idx 8 — single-value
    { sText_Diff_LessEscapes,   GetSel_Diff_LessEscapes  }, // idx 9
    { sText_Diff_EscapeRopeDig, GetSel_Diff_EscapeRopeDig}, // idx 10
};

static const struct ViewerBoolRow sBoolRows_Page6[] = {
    { sText_Chk_PkmnCenter,    GetSel_Chk_PkmnCenter  }, // idx 0
    { sText_Chk_PCHeal,        GetSel_Chk_PCHeal      }, // idx 1 — bool
    { sText_Chk_Expensive,     NULL                   }, // idx 2 — single-value
    { sText_Chk_EvoLimit,      NULL                   }, // idx 3 — single-value
    { sText_Chk_OneType,       NULL                   }, // idx 4 — single-value
    { sText_Chk_BaseStatEq,    NULL                   }, // idx 5 — single-value
    { sText_Chk_Mirror,        GetSel_Chk_Mirror      }, // idx 6 — bool
    { sText_Chk_MirrorThief,   GetSel_Chk_MirrorThief },  // idx 7 — bool
};



// Page descriptor with a per-page draw callback
struct ViewerPage
{
    void (*drawRow)(u8 visRow, u16 dataIndex);          // how to draw a row for this page
    const struct ViewerBoolRow *rows;                    // primary data table for this page
    u16 count;
};

// ---- Page 1 draw (simple bool rows) ----
static void Viewer_DrawRow_Page1(u8 visRow, u16 idx)
{
    const bool8 selected = (idx == sCurIndex);

    switch (idx)
    {
    case 0: // PKM MOVEPOOL
    {
        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_ModernMoves_Label);
        u8 sel = GetSel_ModernMoves();
        const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "ORIGINAL"
        const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "MODERN"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Original);
        int xr = GetStringRightAlignXOffset(1, sText_Modern, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_Modern);
        break;
    }
    case 1: // SYNCHRONIZE
    {
        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_Synchronize_Label);
        u8 sel = GetSel_Synchronize();
        const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "ORIGINAL"
        const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "MODERN"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Original);
        int xr = GetStringRightAlignXOffset(1, sText_Modern, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_Modern);
        break;
    }
    case 2: // STURDY
    {
        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_Sturdy_Label);
        u8 sel = GetSel_Sturdy();
        const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "ORIGINAL"
        const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "MODERN"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Original);
        int xr = GetStringRightAlignXOffset(1, sText_Modern, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_Modern);
        break;
    }
    case 3: // SITRUS BERRY
    {
        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_NewCitrus_Label);
        u8 sel = GetSel_NewCitrus();
        const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "ORIGINAL"
        const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "MODERN"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Original);
        int xr = GetStringRightAlignXOffset(1, sText_Modern, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_Modern);
        break;
    }
    default:
        {
            const struct ViewerBoolRow *row = &sBoolRows[idx];
            Viewer_DrawBoolRow(visRow, row->label, row->getSel(), (idx == sCurIndex));
            break;
        }
    }
}



// ---- Page 2 draw (Shiny Chance is single-value; others are bool) ----
static void Viewer_DrawRow_Page2(u8 visRow, u16 idx)
{
    const bool8 selected = (idx == sCurIndex);
    switch (idx)
    {
    case 0: // RTC TYPE
    {
        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_RTCType_Label);
        u8 sel = GetSel_Feature_RTCType();
        const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "RTC"
        const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "FakeRTC"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_RTC);
        int xr = GetStringRightAlignXOffset(1, sText_FakeRTC, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_FakeRTC);
        break;
    }
    case 1: // SHINY CHANCE
    {
        u8 sc = gSaveBlock1Ptr->tx_Features_ShinyChance;
        if (sc > 4) sc = 0;
        Viewer_DrawSingleValueRow(visRow, sText_ShinyChance_Label,
                                  sText_Challenges_ShinyChance_Strings[sc], selected);
        break;
    }
    case 4: // FRONTIER BANS
    {
        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_FrontierBans_Label);
        u8 sel = GetSel_Feature_FrontierBans();
        const u8 *leftStyle  = (sel == 1) ? sColorRightRed : sColorRightGray; // "BAN"
        const u8 *rightStyle = (sel == 0) ? sColorRightRed : sColorRightGray; // "UNBAN"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Frontier_Ban);
        int xr = GetStringRightAlignXOffset(1, sText_Frontier_Unban, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_Frontier_Unban);
        break;
    }
    default:
    {
        const struct ViewerBoolRow *row = &sBoolRows_Page2[idx];
        Viewer_DrawBoolRow(visRow, row->label, row->getSel(), selected);
        break;
    }
    }
}


// ---- Page 3 draw (all bool rows) ----
static void Viewer_DrawRow_Page3(u8 visRow, u16 idx)
{
    const struct ViewerBoolRow *row = &sBoolRows_Page3[idx];
    Viewer_DrawBoolRow(visRow, row->label, row->getSel(), (idx == sCurIndex));
}


// ---- Page 4 draw (all bool rows) ----
static void Viewer_DrawRow_Page4(u8 visRow, u16 idx)
{
    const bool8 selected = (idx == sCurIndex);
    switch (idx)
    {
    case 0:
    {
        u8 mode = GetNuzlockeModeIndex();
        const u8 *val = (mode == 1) ? sText_Nuz_Mode_Easy :
                        (mode == 2) ? sText_Nuz_Mode_Standard :
                        (mode == 3) ? sText_Nuz_Mode_Hardcore : sText_Nuz_Mode_Off;
        Viewer_DrawSingleValueRow(visRow, sText_Nuz_Mode, val, (idx == sCurIndex));
        break;
    }
    case 4: 
        {
            const int y = visRow * 16;
            Viewer_ClearRow(visRow, selected);
            AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                        sColorLeftActive, TEXT_SKIP_DRAW, sText_Nuz_Fainting);
            u8 sel = GetSel_Nuz_Deletion();
            const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "CEMETERY"
            const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "RELEASE"
            AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                        leftStyle, TEXT_SKIP_DRAW, sText_Nuz_Fainting_Cemetery);
            int xr = GetStringRightAlignXOffset(1, sText_Nuz_Fainting_Release, 198);
            AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                        rightStyle, TEXT_SKIP_DRAW, sText_Nuz_Fainting_Release);
            break;
        }
    default:
        {
            const struct ViewerBoolRow *row = &sBoolRows_Page4[idx - 1];
            Viewer_DrawBoolRow(visRow, row->label, row->getSel(), (idx == sCurIndex));
            break;
        }
    }
}


// ---- Page 5 draw (mix of single-value and bool) ----
static void Viewer_DrawRow_Page5(u8 visRow, u16 idx)
{
    const bool8 selected = (idx == sCurIndex);

    switch (idx)
    {
    case 0: // PARTY LIMIT
    {
        u8 v = GetSel_Diff_PartyLimit();
        if (v > 5) v = 0;
        Viewer_DrawSingleValueRow(visRow, sText_Diff_PartyLimit, sText_Diff_PartyLimit_Strings[v], selected);
        break;
    }
    case 1: // LEVEL CAP
    {
        u8 v = GetSel_Diff_LevelCap();
        if (v > 2) v = 0;
        Viewer_DrawSingleValueRow(visRow, sText_Diff_LevelCap, sText_Diff_LevelCap_Strings[v], selected);
        break;
    }
    case 2: // EXP MULTIPLIER
    {
        u8 v = GetSel_Diff_ExpMult();
        if (v > 3) v = 0;
        Viewer_DrawSingleValueRow(visRow, sText_Diff_ExpMult, sText_Diff_ExpMult_Strings[v], selected);
        break;
    }
    case 3: //Player items (YES / NO)
    {
        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_Diff_NoItemPlayer);
        u8 sel = GetSel_Diff_NoItemPlayer();
        const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "YES"
        const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "NO"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Yes);
        int xr = GetStringRightAlignXOffset(1, sText_No, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_No);
        break;
    }
    case 4: //Trainer items (YES / NO)
    {
        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_Diff_NoItemTrainer);
        u8 sel = GetSel_Diff_NoItemTrainer();
        const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "YES"
        const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "NO"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Yes);
        int xr = GetStringRightAlignXOffset(1, sText_No, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_No);
        break;
    }
    case 5: //Player IVs (YES/NO/NO(HP))
    {
        u8 v = GetSel_Diff_PlayerIVs();
        if (v > 2) v = 0;
        Viewer_DrawSingleValueRow(visRow, sText_Diff_PartyIVs, sText_Diff_PlayerIVs_Strings[v], selected);
        break;
    }
    case 6: // TRAINER IVs (OFF/SCALE/HARD)
    {
        u8 v = GetSel_Diff_TrainerIVs();
        if (v > 2) v = 0;
        Viewer_DrawSingleValueRow(visRow, sText_Diff_TrainerIVs, sText_TrainerEV_Strings[v], selected);
        break;
    }
    case 7: // PLAYER EVs (Yes/No)
    {

        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_Diff_PlayerEVs);
        u8 sel = GetSel_Diff_PlayerEVs();
        const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "YES"
        const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "NO"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Yes);
        int xr = GetStringRightAlignXOffset(1, sText_No, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_No);
        break;
    }
    case 8: // TRAINER EVs (Off/Scale/Hard/Extreme)
    {
        u8 v = GetSel_Diff_TrainerEVs();
        if (v > 3) v = 0;
        Viewer_DrawSingleValueRow(visRow, sText_Diff_TrainerEVs, sText_TrainerEV_Strings[v], selected);
        break;
    }
    case 10: // Escape Rope & Dig (Yes/No)
    {

        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_Diff_EscapeRopeDig);
        u8 sel = GetSel_Diff_EscapeRopeDig();
        const u8 *leftStyle  = (sel == 1) ? sColorRightRed : sColorRightGray; // "YES"
        const u8 *rightStyle = (sel == 0) ? sColorRightRed : sColorRightGray; // "NO"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Yes);
        int xr = GetStringRightAlignXOffset(1, sText_No, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_No);
        break;
    }
    default:
    {
        // All remaining are simple bool rows; reuse the common renderer
        const struct ViewerBoolRow *row = &sBoolRows_Page5[idx];
        Viewer_DrawBoolRow(visRow, row->label, row->getSel(), selected);
        break;
    }
    }
}



// ---- Page 6 draw (mix of single-value and bool) ----
static void Viewer_DrawRow_Page6(u8 visRow, u16 idx)
{
    const bool8 selected = (idx == sCurIndex);

    switch (idx)
    {
    case 0: //Pokecenter challenge (YES / NO)
    {
        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_Chk_PkmnCenter);
        u8 sel = GetSel_Chk_PkmnCenter();
        const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "YES"
        const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "NO"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Yes);
        int xr = GetStringRightAlignXOffset(1, sText_No, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_No);
        break;
    }
    case 1: //PC Heals (YES / NO)
    {
        const int y = visRow * 16;
        Viewer_ClearRow(visRow, selected);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y + 1, 0, 0,
                                     sColorLeftActive, TEXT_SKIP_DRAW, sText_Chk_PCHeal);
        u8 sel = GetSel_Chk_PCHeal();
        const u8 *leftStyle  = (sel == 0) ? sColorRightRed : sColorRightGray; // "YES"
        const u8 *rightStyle = (sel == 1) ? sColorRightRed : sColorRightGray; // "NO"
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 104, y, 0, 0,
                                     leftStyle, TEXT_SKIP_DRAW, sText_Yes);
        int xr = GetStringRightAlignXOffset(1, sText_No, 198);
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, xr, y, 0, 0,
                                     rightStyle, TEXT_SKIP_DRAW, sText_No);
        break;
    }
    case 2: // PRICES (Expensive)
    {
        u8 v = GetSel_Chk_Expensive(); // 0..3
        Viewer_DrawSingleValueRow(visRow, sText_Chk_Expensive, sText_Chk_Expensive_Strings[v], selected);
        break;
    }
    case 3: // EVOLUTION LIMIT
    {
        u8 v = GetSel_Chk_EvoLimit(); // 0..2
        Viewer_DrawSingleValueRow(visRow, sText_Chk_EvoLimit, sText_Chk_EvoLimit_Strings[v], selected);
        break;
    }
    case 4: // ONE TYPE CHALLENGE (single-value: OFF or a type name)
    {
        u8 v = gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge;
        const u8 *val = (v < 19) ? sTypeNames[v] : sText_TypeOff;
        Viewer_DrawSingleValueRow(visRow, sText_Chk_OneType, val, selected);
        break;
    }
    case 5: // BASE STAT EQUALIZER
    {
        u8 v = GetSel_Chk_BaseStatEq(); // 0..3
        Viewer_DrawSingleValueRow(visRow, sText_Chk_BaseStatEq, sText_Chk_BaseStatEq_Strings[v], selected);
        break;
    }
    default:
    {
        // All other rows are simple bools (0/1)
        const struct ViewerBoolRow *row = &sBoolRows_Page6[idx];
        Viewer_DrawBoolRow(visRow, row->label, row->getSel(), selected);
        break;
    }
    }
}



static const struct ViewerPage sPages[VIEWER_PAGE_COUNT] =
{
    { Viewer_DrawRow_Page1, sBoolRows,        ARRAY_COUNT(sBoolRows)        }, // Page 1
    { Viewer_DrawRow_Page2, sBoolRows_Page2,  ARRAY_COUNT(sBoolRows_Page2)  }, // Page 2
    { Viewer_DrawRow_Page3, sBoolRows_Page3,  ARRAY_COUNT(sBoolRows_Page3)  }, // Page 3
    { Viewer_DrawRow_Page4, sBoolRows_Page4,  ARRAY_COUNT(sBoolRows_Page4) + 1 }, // Page 4 (header+subs)
    { Viewer_DrawRow_Page5, sBoolRows_Page5,  ARRAY_COUNT(sBoolRows_Page5)  }, // Page 5
    { Viewer_DrawRow_Page6, sBoolRows_Page6,  ARRAY_COUNT(sBoolRows_Page6)  }, // Page 6
};



// ---- Scrolling state ----
#define VIEWER_VISIBLE_ROWS 5  // 80px tall window / 16px per row
static u8 sTopIndex;           // index of the first row currently visible

static void Viewer_RedrawList(void)
{
    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));

    const struct ViewerPage *pg = &sPages[sPage];
    u32 total = pg->count;
    u32 vis   = VIEWER_VISIBLE_ROWS;

    if (sTopIndex > 0 && sTopIndex + vis > total)
        sTopIndex = (total > vis) ? (total - vis) : 0;

    for (u32 i = 0; i < vis; i++)
    {
        u32 idx = sTopIndex + i;
        if (idx >= total)
            break;

        if (pg->drawRow)
        pg->drawRow(i, idx);
    }

    // If this page is empty, just leave the window cleared (blank).
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}




// ---- Entry point from field ----------------------------------------------------

void Task_ChallengeViewer(u8 taskId)
{
    gMain.savedCallback = CB2_ReturnToFieldContinueScript; // return straight to field
    SetMainCallback2(CB2_InitChallengeViewer);
    DestroyTask(taskId);
}

// ---- Boot sequence (mirrors menu init; trimmed) --------------------------------

void CB2_InitChallengeViewer(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;

    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);

        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sViewerBgTemplates, ARRAY_COUNT(sViewerBgTemplates));
        ResetBgPositions();

        InitWindows(sViewerWinTemplates);
        DeactivateAllTextPrinters();

        // Window/Blend regs consistent with menu path.
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0 | WININ_WIN1_BG0 | WININ_WIN0_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG1);
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
        // Load the current window frame tile graphics into BG1 at base tile 0x1A2.
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;

    case 4:
        // 1) Backdrop color (palette slot 0)
        LoadPalette(sOptionMenuBg_Pal, 0, sizeof(sOptionMenuBg_Pal));
        // 2) Window frame palette (0x70)
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, 0x70, 0x20);
        // 3) **Menu text palette (index 16)** — this is what colors the text the same way
        LoadPalette(sOptionMenuText_Pal, 16, sizeof(sOptionMenuText_Pal));
        gMain.state++;
        break;


    case 5:
        // Build the BG1 rectangles (frames) just like the menu.
        DrawBgWindowFrames();

        // Put window tilemaps and draw text in top and description boxes.
        PutWindowTilemap(WIN_TOPBAR);
        PutWindowTilemap(WIN_OPTIONS);
        PutWindowTilemap(WIN_DESCRIPTION);

        sPage = VIEWER_PAGE_MODE;
        sTopIndex = 0;
        sCurIndex = 0;   
        Viewer_RedrawList();


        DrawTopBar();
        DrawDescription();

        gMain.state++;
        break;

    case 6:
        // Fade in & switch to main loop
        CreateTask(Task_ViewerFadeIn, 0);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(Viewer_VBlankCB);
        SetMainCallback2(Viewer_MainCB2);
        gMain.state++;
        break;

    case 7:
        return;
    }
}

// ---- Draw helpers -------------------------------------------------------------

static void DrawBgWindowFrames(void)
{
    // OPTION TEXTS window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  2,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  2, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  2,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  3,  1, 16,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  3,  1, 16,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 13,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 13, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 13,  1,  1,  7);

    // DESCRIPTION window frame
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

static void DrawTopBar(void)
{
    // simple white-on-dark like other menu text
    FillWindowPixelBuffer(WIN_TOPBAR, PIXEL_FILL(1));

    // Center “CHALLENGE VIEWER” only
    {
        s32 w = GetStringWidth(FONT_SMALL, sViewerTopLeft, 0);
        s32 x = (240 - w) / 2;
        if (x < 0) x = 0;
        AddTextPrinterParameterized4(
            WIN_TOPBAR, FONT_SMALL, 5, 1, 0, 0,
            sColorRightRed, TEXT_SKIP_DRAW, sViewerTopLeft);
    }

    // Right side hint: Exit + Scroll
    {
        // "A/B: Exit  Up/Down: Scroll"
        static const u8 sViewerExitScrollHint[] = _("Heart & Soul");
        s32 w = GetStringWidth(FONT_SMALL, sViewerExitScrollHint, 0);
        s32 x = 232 - w; // stay a few px from the right edge
        if (x < 0) x = 0;
        AddTextPrinterParameterized4(
            WIN_TOPBAR, FONT_SMALL, x, 1, 0, 0,
            sColorLeftGray, TEXT_SKIP_DRAW, sViewerExitScrollHint);
    }

    CopyWindowToVram(WIN_TOPBAR, COPYWIN_FULL);
}


static void DrawDescription(void)
{
    FillWindowPixelBuffer(WIN_DESCRIPTION, PIXEL_FILL(1));
    // Use the same gray triplet you use elsewhere (menu palette)
    AddTextPrinterParameterized4(
        WIN_DESCRIPTION, FONT_NORMAL, 8, 1, 0, 0,
        sColorLeftGray, TEXT_SKIP_DRAW, sViewerDesc);
    CopyWindowToVram(WIN_DESCRIPTION, COPYWIN_FULL);
}


// ---- Main loop / tasks --------------------------------------------------------

static void Viewer_MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void Viewer_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_ViewerFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_ViewerInput;
}

static void Task_ViewerInput(u8 taskId)
{
    if (JOY_NEW(START_BUTTON))
    {
        gMain.savedCallback = CB2_ReturnToFieldContinueScript;
        SetMainCallback2(CB2_InitTxRandomizerChallengesMenu);
        DestroyTask(taskId);
    }

    if (JOY_NEW(A_BUTTON) || JOY_NEW(B_BUTTON))
    {
        gTasks[taskId].func = Task_ViewerFadeOutBegin;
        return;
    }

    // Page switch first so scroll resets appropriately.
    if (JOY_NEW(R_BUTTON))
    {
        if (sPage + 1 < VIEWER_PAGE_COUNT)
        {
            sPage++;
            sTopIndex = 0;
            sCurIndex = 0;
            Viewer_RedrawList();
        }
        return;
    }
    if (JOY_NEW(L_BUTTON))
    {
        if (sPage > 0)
        {
            sPage--;
            sTopIndex = 0;
            sCurIndex = 0;
            Viewer_RedrawList();
        }
        return;
    }

    // Existing vertical scroll
    u32 total = sPages[sPage].count;

        // Move cursor and auto-scroll
    if (JOY_NEW(DPAD_UP) || JOY_REPEAT(DPAD_UP))
    {
        if (sCurIndex > 0)
        {
            sCurIndex--;
            if (sCurIndex < sTopIndex)
                sTopIndex = sCurIndex;
            Viewer_RedrawList();
        }
        return;
    }
    if (JOY_NEW(DPAD_DOWN) || JOY_REPEAT(DPAD_DOWN))
    {
        const struct ViewerPage *pg = &sPages[sPage];
        if (pg->count > 0 && sCurIndex + 1 < pg->count)
        {
            sCurIndex++;
            if (sCurIndex >= sTopIndex + VIEWER_VISIBLE_ROWS)
                sTopIndex = sCurIndex - VIEWER_VISIBLE_ROWS + 1;
            Viewer_RedrawList();
        }
        return;
    }

}


static void Task_ViewerFadeOutBegin(u8 taskId)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_ViewerFadeOut;
}

static void Task_ViewerFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}
