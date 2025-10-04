#include "global.h"
#include "option_plus_menu.h"
#include "main.h"
#include "menu.h"
#include "scanline_effect.h"
#include "palette.h"
#include "sprite.h"
#include "task.h"
#include "malloc.h"
#include "rtc.h"
#include "bg.h"
#include "gpu_regs.h"
#include "window.h"
#include "text.h"
#include "text_window.h"
#include "international_string_util.h"
#include "strings.h"
#include "gba/m4a_internal.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "event_data.h"
#include "sound.h"

enum
{
    MENU_MAIN,
    MENU_CUSTOM,
    MENU_SOUND,
    MENU_COUNT,
};

// Menu items
enum
{
    MENUITEM_MAIN_TEXTSPEED,
    MENUITEM_MAIN_BATTLESCENE,
    MENUITEM_MAIN_BATTLESTYLE,
    MENUITEM_MAIN_BUTTONMODE,
    MENUITEM_MAIN_FOLLOWER,
    MENUITEM_MAIN_LARGE_FOLLOWER,
    MENUITEM_MAIN_MATCHCALL,
    MENUITEM_MAIN_AUTORUN,
    MENUITEM_MAIN_AUTORUN_SURF,
    MENUITEM_MAIN_AUTORUN_DIVE,
    MENUITEM_CUSTOM_FISHING,
    MENUITEM_MAIN_EVEN_FASTER_JOY,
    MENUITEM_MAIN_UNIT_TYPE,
    MENUITEM_MAIN_SKIP_INTRO,
    MENUITEM_MAIN_FRAMETYPE,
    MENUITEM_MAIN_DIFFICULTY,
    MENUITEM_MAIN_COUNT,
};

//Menu options 2
enum
{
    MENUITEM_BATTLE_SPLIT,
    MENUITEM_BATTLE_FAST_INTRO,
    MENUITEM_BATTLE_FAST_BATTLES,
    MENUITEM_BATTLE_NEW_BACKGROUNDS,
    MENUITEM_BATTLE_BALL_PROMPT,
    MENUITEM_BATTLE_TYPE_EFFECTIVE,
    MENUITEM_BATTLE_RUN_TYPE,
    MENUITEM_BATTLE_LR_RUN,
    MENUITEM_BATTLE_COUNT,
};

// Menu sounds
enum
{
    MENUITEM_SOUND_SOUND,
    MENUITEM_SOUND_MUSIC,
    MENUITEM_SOUND_BIKE_MUSIC,
    MENUITEM_SOUND_SURF_MUSIC,
    MENUITEM_SOUND_WILD_MON_MUSIC,
    MENUITEM_SOUND_BATTLE_TRAINER_MUSIC,
    MENUITEM_SOUND_BATTLE_FRONTIER_TRAINER_MUSIC,
    MENUITEM_SOUND_EFFECTS,
    MENUITEM_SOUND_COUNT,
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
    u8 submenu;
    u8 sel[MENUITEM_MAIN_COUNT];
    u8 sel_battle[MENUITEM_BATTLE_COUNT];
    u8 sel_sound[MENUITEM_SOUND_COUNT];
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
static void Task_OptionMenuSave(u8 taskId);
static void Task_OptionMenuFadeOut(u8 taskId);
static void ScrollMenu(int direction);
static void ScrollAll(int direction); // to bottom or top
static int GetMiddleX(const u8 *txt1, const u8 *txt2, const u8 *txt3);
static int XOptions_ProcessInput(int x, int selection);
static int ProcessInput_Options_Two(int selection);
static int ProcessInput_Options_Three(int selection);
static int ProcessInput_Options_Four(int selection);
static int ProcessInput_Options_Six(int selection);
static int ProcessInput_Options_Eleven(int selection);
static int ProcessInput_Sound(int selection);
static int ProcessInput_FrameType(int selection);
static int ProcessInput_BattleStyle(int selection);
static int ProcessInput_Difficulty(int selection);
static const u8 *const OptionTextDescription(void);
static const u8 *const OptionTextRight(u8 menuItem);
static u8 MenuItemCount(void);
static void DrawDescriptionText(void);
static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style, bool8 active);
static void DrawChoices_Options_Four(const u8 *const *const strings, int selection, int y, bool8 active);
static void DrawChoices_Options_Six(const u8 *const *const strings, int selection, int y, bool8 active);
static void ReDrawAll(void);
static void DrawChoices_TextSpeed(int selection, int y);
static void DrawChoices_Difficulty(int selection, int y);
static void DrawChoices_BattleScene(int selection, int y);
static void DrawChoices_BattleStyle(int selection, int y);
static void DrawChoices_Sound(int selection, int y);
static void DrawChoices_ButtonMode(int selection, int y);
static void DrawChoices_Follower(int selection, int y);
static void DrawChoices_LargeFollower(int selection, int y);
static void DrawChoices_Autorun(int selection, int y);
static void DrawChoices_FrameType(int selection, int y);
static void DrawChoices_MatchCall(int selection, int y);
static void DrawChoices_Style(int selection, int y);
static void DrawChoices_TypeEffective(int selection, int y);
static void DrawChoices_Fishing(int selection, int y);
static void DrawChoices_FastIntro(int selection, int y);
static void DrawChoices_FastBattles(int selection, int y);
static void DrawChoices_BikeMusic(int selection, int y);
static void DrawChoices_EvenFasterJoy(int selection, int y);
static void DrawChoices_SurfMusic(int selection, int y);
static void DrawChoices_Wild_Battle_Music(int selection, int y);
static void DrawChoices_Trainer_Battle_Music(int selection, int y);
static void DrawChoices_Frontier_Trainer_Battle_Music(int selection, int y);
static void DrawChoices_Sound_Effects(int selection, int y);
static void DrawChoices_Skip_Intro(int selection, int y);
static void DrawChoices_LR_Run(int selection, int y);
static void DrawChoices_Ball_Prompt(int selection, int y);
static void DrawChoices_Unit_Type(int selection, int y);
static void DrawChoices_Music(int selection, int y);
static void DrawChoices_New_Backgrounds(int selection, int y);
static void DrawChoices_Run_Type(int selection, int y);
static void DrawChoices_Autorun_Surf(int selection, int y);
static void DrawChoices_Autorun_Dive(int selection, int y);
static void DrawBgWindowFrames(void);

// EWRAM vars
EWRAM_DATA static struct OptionMenu *sOptions = NULL;

// const data
static const u8 sEqualSignGfx[] = INCBIN_U8("graphics/interface/option_menu_equals_sign.4bpp"); // note: this is only used in the Japanese release
static const u16 sOptionMenuBg_Pal[] = {RGB(14, 20, 24)};
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

// Menu draw and input functions 
struct // MENU_MAIN
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsMain[MENUITEM_MAIN_COUNT] =
{
    [MENUITEM_MAIN_TEXTSPEED]               = {DrawChoices_TextSpeed,        ProcessInput_Options_Four},
    [MENUITEM_MAIN_BATTLESCENE]             = {DrawChoices_BattleScene,      ProcessInput_Options_Two},
    [MENUITEM_MAIN_DIFFICULTY]              = {DrawChoices_Difficulty,       ProcessInput_Difficulty},
    [MENUITEM_MAIN_BATTLESTYLE]             = {DrawChoices_BattleStyle,      ProcessInput_BattleStyle},
    [MENUITEM_MAIN_BUTTONMODE]              = {DrawChoices_ButtonMode,       ProcessInput_Options_Three},
    [MENUITEM_MAIN_FOLLOWER]                = {DrawChoices_Follower,         ProcessInput_Options_Two},
    [MENUITEM_MAIN_LARGE_FOLLOWER]          = {DrawChoices_LargeFollower,    ProcessInput_Options_Two},
    [MENUITEM_MAIN_AUTORUN]                 = {DrawChoices_Autorun,          ProcessInput_Options_Two},
    [MENUITEM_MAIN_AUTORUN_SURF]            = {DrawChoices_Autorun_Surf,     ProcessInput_Options_Two},  
    [MENUITEM_MAIN_AUTORUN_DIVE]            = {DrawChoices_Autorun_Dive,     ProcessInput_Options_Two},  
    [MENUITEM_MAIN_MATCHCALL]               = {DrawChoices_MatchCall,        ProcessInput_Options_Two},
    [MENUITEM_CUSTOM_FISHING]               = {DrawChoices_Fishing,          ProcessInput_Options_Two},
    [MENUITEM_MAIN_EVEN_FASTER_JOY]         = {DrawChoices_EvenFasterJoy,    ProcessInput_Options_Two},
    [MENUITEM_MAIN_SKIP_INTRO]              = {DrawChoices_Skip_Intro,       ProcessInput_Options_Two}, 
    [MENUITEM_MAIN_UNIT_TYPE]               = {DrawChoices_Unit_Type,        ProcessInput_Options_Two},  
    [MENUITEM_MAIN_FRAMETYPE]               = {DrawChoices_FrameType,        ProcessInput_FrameType},
};

struct // MENU_CUSTOM
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsCustom[MENUITEM_BATTLE_COUNT] =
{

    [MENUITEM_BATTLE_FAST_INTRO]       = {DrawChoices_FastIntro,          ProcessInput_Options_Two},
    [MENUITEM_BATTLE_SPLIT]            = {DrawChoices_Style,              ProcessInput_Options_Two},
    [MENUITEM_BATTLE_TYPE_EFFECTIVE]   = {DrawChoices_TypeEffective,      ProcessInput_Options_Two},
    [MENUITEM_BATTLE_FAST_BATTLES]     = {DrawChoices_FastBattles,        ProcessInput_Options_Two},
    [MENUITEM_BATTLE_RUN_TYPE]         = {DrawChoices_Run_Type,           ProcessInput_Options_Four},
    [MENUITEM_BATTLE_LR_RUN]           = {DrawChoices_LR_Run,             ProcessInput_Options_Two},
    [MENUITEM_BATTLE_BALL_PROMPT]      = {DrawChoices_Ball_Prompt,        ProcessInput_Options_Two},
    [MENUITEM_BATTLE_NEW_BACKGROUNDS]  = {DrawChoices_New_Backgrounds,    ProcessInput_Options_Two},
};

struct // MENU_SOUND
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
} static const sItemFunctionsSound[MENUITEM_SOUND_COUNT] =
{
    [MENUITEM_SOUND_SOUND]                         = {DrawChoices_Sound,                                 ProcessInput_Options_Two},
    [MENUITEM_SOUND_MUSIC]                         = {DrawChoices_Music,                                 ProcessInput_Options_Two},
    [MENUITEM_SOUND_BIKE_MUSIC]                    = {DrawChoices_BikeMusic,                             ProcessInput_Options_Two},
    [MENUITEM_SOUND_SURF_MUSIC]                    = {DrawChoices_SurfMusic,                             ProcessInput_Options_Two},
    [MENUITEM_SOUND_WILD_MON_MUSIC]                = {DrawChoices_Wild_Battle_Music,                     ProcessInput_Options_Six},
    [MENUITEM_SOUND_BATTLE_TRAINER_MUSIC]          = {DrawChoices_Trainer_Battle_Music,                  ProcessInput_Options_Six},
    [MENUITEM_SOUND_BATTLE_FRONTIER_TRAINER_MUSIC] = {DrawChoices_Frontier_Trainer_Battle_Music,         ProcessInput_Options_Six},
    [MENUITEM_SOUND_EFFECTS]                       = {DrawChoices_Sound_Effects,                         ProcessInput_Options_Three},
};

// Menu left side option names text
static const u8 sText_OptionTypeEffective[]       = _("SHOW EFFECTIVE");
static const u8 sText_OptionFishing[]             = _("EASIER FISHING");
static const u8 sText_OptionFastIntro[]           = _("FAST INTRO");
static const u8 sText_OptionLargeFollower[]       = _("BIG FOLLOWERS");
static const u8 sText_OptionFastBattles[]         = _("FAST BATTLES");
static const u8 sText_OptionEvenFasterJoy[]       = _("EVEN FASTER JOY");
static const u8 sText_OptionSkipIntro[]           = _("SKIP INTRO");
static const u8 sText_OptionLR_Run[]              = _("RUN PROMPT");
static const u8 sText_OptionBallPrompt[]          = _("BALL PROMPT");
static const u8 sText_OptionUnitType[]            = _("UNIT SYSTEM");
static const u8 sText_OptionNewBackgrounds[]      = _("BATTLE TERRAIN");
static const u8 sText_OptionRunType[]             = _("QUICK RUN");
static const u8 sText_AutorunEnable_Surf[]        = _("AUTORUN (SURF)");
static const u8 sText_AutorunEnable_Dive[]        = _("AUTORUN (DIVE)");
static const u8 *const sOptionMenuItemsNamesMain[MENUITEM_MAIN_COUNT] =
{
    [MENUITEM_MAIN_TEXTSPEED]           = gText_TextSpeed,
    [MENUITEM_MAIN_BATTLESCENE]         = gText_BattleScene,
    [MENUITEM_MAIN_DIFFICULTY]          = gText_OptionDifficulty,
    [MENUITEM_MAIN_BATTLESTYLE]         = gText_BattleStyle,
    [MENUITEM_MAIN_BUTTONMODE]          = gText_ButtonMode,
    [MENUITEM_MAIN_FOLLOWER]            = gText_FollowerEnable,
    [MENUITEM_MAIN_LARGE_FOLLOWER]      = sText_OptionLargeFollower,
    [MENUITEM_MAIN_AUTORUN]             = gText_AutorunEnable,
    [MENUITEM_MAIN_AUTORUN_SURF]        = sText_AutorunEnable_Surf,
    [MENUITEM_MAIN_AUTORUN_DIVE]        = sText_AutorunEnable_Dive,
    [MENUITEM_MAIN_MATCHCALL]           = gText_OptionMatchCalls,
    [MENUITEM_CUSTOM_FISHING]           = sText_OptionFishing,
    [MENUITEM_MAIN_EVEN_FASTER_JOY]     = sText_OptionEvenFasterJoy,
    [MENUITEM_MAIN_SKIP_INTRO]          = sText_OptionSkipIntro,
    [MENUITEM_MAIN_UNIT_TYPE]           = sText_OptionUnitType,
    [MENUITEM_MAIN_FRAMETYPE]           = gText_Frame,
};

static const u8 *const sOptionMenuItemsNamesCustom[MENUITEM_BATTLE_COUNT] =
{
    [MENUITEM_BATTLE_FAST_INTRO]       = sText_OptionFastIntro,
    [MENUITEM_BATTLE_SPLIT]            = gText_OptionStyle,
    [MENUITEM_BATTLE_TYPE_EFFECTIVE]   = sText_OptionTypeEffective,
    [MENUITEM_BATTLE_FAST_BATTLES]     = sText_OptionFastBattles,
    [MENUITEM_BATTLE_RUN_TYPE]         = sText_OptionRunType,
    [MENUITEM_BATTLE_LR_RUN]           = sText_OptionLR_Run,
    [MENUITEM_BATTLE_BALL_PROMPT]      = sText_OptionBallPrompt,
    [MENUITEM_BATTLE_NEW_BACKGROUNDS]  = sText_OptionNewBackgrounds,
};

static const u8 sText_OptionMusic[]                  = _("MUSIC");
static const u8 sText_OptionSurfMusic[]              = _("SURF MUSIC");
static const u8 sText_OptionBikeMusic[]              = _("BIKE MUSIC");
static const u8 sText_OptionWildMonMusic[]           = _("WILD MUSIC");
static const u8 sText_OptionTrainerBattleMusic[]     = _("TRAINER MUSIC");
static const u8 sText_OptionFrontierTrainerBattleMusic[]     = _("FRONTIER MUSIC");
static const u8 sText_OptionSoundEffects[]           = _("SOUND EFFECTS");
static const u8 *const sOptionMenuItemsNamesSound[MENUITEM_SOUND_COUNT] =
{
    [MENUITEM_SOUND_SOUND]                           = gText_Sound,
    [MENUITEM_SOUND_MUSIC]                           = sText_OptionMusic,
    [MENUITEM_SOUND_BIKE_MUSIC]                      = sText_OptionBikeMusic,
    [MENUITEM_SOUND_SURF_MUSIC]                      = sText_OptionSurfMusic,
    [MENUITEM_SOUND_WILD_MON_MUSIC]                  = sText_OptionWildMonMusic,
    [MENUITEM_SOUND_BATTLE_TRAINER_MUSIC]            = sText_OptionTrainerBattleMusic,
    [MENUITEM_SOUND_BATTLE_FRONTIER_TRAINER_MUSIC]   = sText_OptionFrontierTrainerBattleMusic,
    [MENUITEM_SOUND_EFFECTS]                         = sText_OptionSoundEffects,
};

/* REPLACED TO LIMIT SOUND OPTIONS
static const u8 *const OptionTextRight(u8 menuItem)
{
    switch (sOptions->submenu)
    {
    case MENU_MAIN:     return sOptionMenuItemsNamesMain[menuItem];
    case MENU_CUSTOM:   return sOptionMenuItemsNamesCustom[menuItem];
    case MENU_SOUND:    return sOptionMenuItemsNamesSound[menuItem];
    }
}
*/
static const u8 *const OptionTextRight(u8 menuItem)
{
    static const u8 sText_Empty[] = _("");
    switch (sOptions->submenu)
    {
    case MENU_MAIN:
        if (menuItem < MENUITEM_MAIN_DIFFICULTY)
            return sOptionMenuItemsNamesMain[menuItem];
        break;
    case MENU_CUSTOM:
        if (menuItem < MENUITEM_BATTLE_COUNT)
            return sOptionMenuItemsNamesCustom[menuItem];
        break;
    case MENU_SOUND:
        if (menuItem < 2) // 
            return sOptionMenuItemsNamesSound[menuItem];
        break;
    }
    return sText_Empty;
}


// Menu left side text conditions
static bool8 CheckConditions(int selection)
{
    switch (sOptions->submenu)
    {
    case MENU_MAIN:
        switch(selection)
        {
        case MENUITEM_MAIN_TEXTSPEED:         return TRUE;
        case MENUITEM_MAIN_BATTLESCENE:       return TRUE;
        case MENUITEM_MAIN_DIFFICULTY:        return TRUE;
        case MENUITEM_MAIN_BATTLESTYLE:       return TRUE;
        case MENUITEM_MAIN_BUTTONMODE:        return TRUE;
        case MENUITEM_MAIN_FRAMETYPE:         return TRUE;
        case MENUITEM_MAIN_FOLLOWER:          return TRUE;
        case MENUITEM_MAIN_LARGE_FOLLOWER:    return TRUE;
        case MENUITEM_MAIN_AUTORUN:           return TRUE;
        case MENUITEM_MAIN_AUTORUN_SURF:      return TRUE;
        case MENUITEM_MAIN_AUTORUN_DIVE:      return TRUE;
        case MENUITEM_MAIN_COUNT:             return TRUE;
        case MENUITEM_MAIN_MATCHCALL:         return TRUE;
        case MENUITEM_CUSTOM_FISHING:         return TRUE;
        case MENUITEM_MAIN_EVEN_FASTER_JOY:   return TRUE;
        case MENUITEM_MAIN_SKIP_INTRO:        return TRUE;
        case MENUITEM_MAIN_UNIT_TYPE:         return TRUE;
        }
    case MENU_CUSTOM:
        switch(selection)
        {
        case MENUITEM_BATTLE_FAST_INTRO:      return TRUE;
        case MENUITEM_BATTLE_SPLIT:           return TRUE;
        case MENUITEM_BATTLE_TYPE_EFFECTIVE:  return TRUE;
        case MENUITEM_BATTLE_FAST_BATTLES:    return TRUE;
        case MENUITEM_BATTLE_RUN_TYPE:        return TRUE;
        case MENUITEM_BATTLE_LR_RUN:          return sOptions->sel_battle[MENUITEM_BATTLE_RUN_TYPE] == 1 || sOptions->sel_battle[MENUITEM_BATTLE_RUN_TYPE] == 3;
        case MENUITEM_BATTLE_BALL_PROMPT:     return TRUE;
        case MENUITEM_BATTLE_COUNT:           return TRUE;
        case MENUITEM_BATTLE_NEW_BACKGROUNDS: return TRUE;
        }
    /* REPLACED TO LIMIT SOUND OPTIONS   
    case MENU_SOUND:
        switch(selection)
        {
        case MENUITEM_SOUND_SOUND:                            return TRUE;
        case MENUITEM_SOUND_MUSIC:                            return TRUE;
        case MENUITEM_SOUND_SURF_MUSIC:                       return TRUE;
        case MENUITEM_SOUND_BIKE_MUSIC:                       return TRUE;
        case MENUITEM_SOUND_WILD_MON_MUSIC:                   return TRUE;
        case MENUITEM_SOUND_BATTLE_TRAINER_MUSIC:             return TRUE;
        case MENUITEM_SOUND_BATTLE_FRONTIER_TRAINER_MUSIC:    return TRUE;
        case MENUITEM_SOUND_EFFECTS:                          return TRUE;
        }
    */
    case MENU_SOUND:
        switch(selection)
        {
        case MENUITEM_SOUND_SOUND:
        case MENUITEM_SOUND_MUSIC:
            return TRUE;
        default:
            return FALSE; // hide others
        }


    }
}

// Descriptions
static const u8 sText_Empty[]                   = _("");
static const u8 sText_Desc_Save[]               = _("Save your settings.");
static const u8 sText_Desc_TextSpeed[]          = _("Choose one of the four text-display\nspeeds.");
static const u8 sText_Desc_BattleScene_On[]     = _("Show the POKéMON animations\nand attack animations.");
static const u8 sText_Desc_BattleScene_Off[]    = _("Skip the POKéMON animations\nand attack animations.");
static const u8 sText_Desc_Difficulty_Easy[]    = _("Change the difficulty to EASY.\nEverything is easier.");
static const u8 sText_Desc_Difficulty_Normal[]  = _("Change the difficulty to NORMAL.\nVanilla experience.");
static const u8 sText_Desc_Difficulty_Hard[]    = _("Change the difficulty to HARD.\nIncludes extra challenges.");
static const u8 sText_Desc_BattleStyle_Shift[]  = _("Get the option to switch your\nPOKéMON after the enemies faints.");
static const u8 sText_Desc_BattleStyle_Set[]    = _("No free switch after fainting the\nenemies POKéMON.");
static const u8 sText_Desc_ButtonMode[]         = _("All buttons work as normal.");
static const u8 sText_Desc_ButtonMode_LR[]      = _("On some screens the L and R buttons\nact as left and right.");
static const u8 sText_Desc_ButtonMode_LA[]      = _("The L button acts as another A\nbutton for one-handed play.");
static const u8 sText_Desc_FrameType[]          = _("Choose the frame surrounding the\nwindows.");
static const u8 sText_Desc_FollowerOn[]            = _("Let the first POKéMON in your\nparty follow you.");
static const u8 sText_Desc_FollowerOff[]           = _("Walk alone.");
static const u8 sText_Desc_FollowerLargeOn[]       = _("Enable large {PKMN} followers.\nCan cause graphical issues.");
static const u8 sText_Desc_FollowerLargeOff[]      = _("Disable large {PKMN} followers.\nRecommended.");
static const u8 sText_Desc_AutorunOn[]             = _("Run without pressing B.");
static const u8 sText_Desc_AutorunOff[]            = _("Press and hold B to run.");
static const u8 sText_Desc_AutorunSurfOn[]         = _("Surf faster without pressing B.");
static const u8 sText_Desc_AutorunSurfOff[]        = _("Press and hold B to surf faster.");
static const u8 sText_Desc_AutorunDiveOn[]         = _("Surf underwater faster\nwithout pressing B.");
static const u8 sText_Desc_AutorunDiveOff[]        = _("Press and hold B to surf\nunderwater faster.");
static const u8 sText_Desc_FishingOn[]             = _("Automatically reel while fishing.");
static const u8 sText_Desc_FishingOff[]            = _("Manually reel while fishing.\nFish like you always fished!");
static const u8 sText_Desc_EvenFasterJoyOn[]       = _("NURSE JOY heals you extremely fast.\nFor those who cannot wait.");
static const u8 sText_Desc_EvenFasterJoyOff[]      = _("NURSE JOY heals you fast, but\nwith the usual animation.");
static const u8 sText_Desc_SkipIntroOn[]           = _("Skips the Copyright screen and\nintro. Applies to soft-resets.");
static const u8 sText_Desc_SkipIntroOff[]          = _("Shows the Copyright screen and\nthe game's introduction.");
static const u8 sText_Desc_OverworldCallsOn[]      = _("TRAINERs will be able to call you,\noffering rematches and info.");
static const u8 sText_Desc_OverworldCallsOff[]     = _("You will not receive calls.\nSpecial events will still occur.");
static const u8 sText_Desc_Units_Imperial[]        = _("Display BERRY and POKéMON weight\nand size in pounds and inches.");
static const u8 sText_Desc_Units_Metric[]          = _("Display BERRY and POKéMON weight\nand size in kilograms and meters.");
static const u8 *const sOptionMenuItemDescriptionsMain[MENUITEM_MAIN_COUNT][3] =
{
    [MENUITEM_MAIN_TEXTSPEED]   = {sText_Desc_TextSpeed,            sText_Empty,                sText_Empty},
    [MENUITEM_MAIN_BATTLESCENE] = {sText_Desc_BattleScene_On,       sText_Desc_BattleScene_Off, sText_Empty},
    [MENUITEM_MAIN_DIFFICULTY]  = {sText_Desc_Difficulty_Easy,      sText_Desc_Difficulty_Normal, sText_Desc_Difficulty_Hard},
    [MENUITEM_MAIN_BATTLESTYLE] = {sText_Desc_BattleStyle_Shift,    sText_Desc_BattleStyle_Set, sText_Empty},
    [MENUITEM_MAIN_BUTTONMODE]  = {sText_Desc_ButtonMode,           sText_Desc_ButtonMode_LR,   sText_Desc_ButtonMode_LA},
    [MENUITEM_MAIN_FRAMETYPE]   = {sText_Desc_FrameType,            sText_Empty,                sText_Empty},
    [MENUITEM_MAIN_FOLLOWER]    = {sText_Desc_FollowerOn,           sText_Desc_FollowerOff},
    [MENUITEM_MAIN_LARGE_FOLLOWER]    = {sText_Desc_FollowerLargeOn,           sText_Desc_FollowerLargeOff},
    [MENUITEM_MAIN_AUTORUN]     = {sText_Desc_AutorunOn,            sText_Desc_AutorunOff},
    [MENUITEM_MAIN_AUTORUN_SURF]     = {sText_Desc_AutorunSurfOn,            sText_Desc_AutorunSurfOff},
    [MENUITEM_MAIN_AUTORUN_DIVE]     = {sText_Desc_AutorunDiveOn,            sText_Desc_AutorunDiveOff},
    [MENUITEM_MAIN_MATCHCALL]   = {sText_Desc_OverworldCallsOn,     sText_Desc_OverworldCallsOff},
    [MENUITEM_CUSTOM_FISHING]     = {sText_Desc_FishingOn,            sText_Desc_FishingOff},
    [MENUITEM_MAIN_EVEN_FASTER_JOY]     = {sText_Desc_EvenFasterJoyOn,            sText_Desc_EvenFasterJoyOff},
    [MENUITEM_MAIN_SKIP_INTRO]     = {sText_Desc_SkipIntroOn,            sText_Desc_SkipIntroOff},
    [MENUITEM_MAIN_UNIT_TYPE]     = {sText_Desc_Units_Metric,            sText_Desc_Units_Imperial},
};

// Custom {PKMN}
static const u8 sText_Desc_StyleOn[]               = _("PHYSICAL and SPECIAL MOVES\nare MOVE specific.");
static const u8 sText_Desc_StyleOff[]              = _("PHYSICAL and SPECIAL MOVES\ndepend on the POKéMON TYPE.");
static const u8 sText_Desc_TypeEffectiveOn[]       = _("TYPE effectiveness will be\nshown in battles.");
static const u8 sText_Desc_TypeEffectiveOff[]      = _("TYPE effectiveness won't be\nshown in battles.");
static const u8 sText_Desc_FastIntroOn[]           = _("Skip the sliding animation\nand enter battles faster.");
static const u8 sText_Desc_FastIntroOff[]          = _("Battles load at the usual speed.");
static const u8 sText_Desc_FastBattleOn[]          = _("Skips all delays in battles, which\nmakes them faster.");
static const u8 sText_Desc_FastBattleOff[]         = _("Manual delay skipping. You can\npress A or B to skip delays.");
static const u8 sText_Desc_Run_Type_Off[]          = _("No quick running from battles.");
static const u8 sText_Desc_Run_Type_LR[]           = _("Hold {L_BUTTON}+{R_BUTTON}, then {A_BUTTON} to run from\nbattles before they start.");
static const u8 sText_Desc_Run_Type_B[]            = _("Press {B_BUTTON} to move the cursor to the RUN\noption after the battle started.");
static const u8 sText_Desc_Run_Type_B_2[]          = _("Hold {B_BUTTON} to run from battles before\nthey start.");
static const u8 sText_Desc_LR_Run_On[]             = _("Enables a prompt to show that you\ncan run away from battles.");
static const u8 sText_Desc_LR_Run_Off[]            = _("Disables said prompt to flee.\nButton combo still works.");
static const u8 sText_Desc_Ball_Prompt_On[]        = _("Use POKéBALLS pressing {R_BUTTON} in battle.\n Hold {L_BUTTON}/{R_BUTTON} to swap POKéBALLS.");
static const u8 sText_Desc_Ball_Prompt_Off[]       = _("Disables the prompt to use\nPOKéBALLS quickly.");
static const u8 sText_Desc_NewBackgrounds_Old[]    = _("Original battle terrain backgrounds.");
static const u8 sText_Desc_NewBackgrounds_New[]    = _("Modernized battle terrain\nbackgrounds, similar to GEN IV.");
static const u8 *const sOptionMenuItemDescriptionsCustom[MENUITEM_BATTLE_COUNT][4] =
{

    [MENUITEM_BATTLE_FAST_INTRO]          = {sText_Desc_FastIntroOn,              sText_Desc_FastIntroOff},
    [MENUITEM_BATTLE_FAST_BATTLES]        = {sText_Desc_FastBattleOn,             sText_Desc_FastBattleOff},
    [MENUITEM_BATTLE_SPLIT]               = {sText_Desc_StyleOn,                  sText_Desc_StyleOff},
    [MENUITEM_BATTLE_TYPE_EFFECTIVE]      = {sText_Desc_TypeEffectiveOn,          sText_Desc_TypeEffectiveOff},
    [MENUITEM_BATTLE_LR_RUN]              = {sText_Desc_LR_Run_On,                sText_Desc_LR_Run_Off},
    [MENUITEM_BATTLE_BALL_PROMPT]         = {sText_Desc_Ball_Prompt_On,           sText_Desc_Ball_Prompt_Off},
    [MENUITEM_BATTLE_NEW_BACKGROUNDS]     = {sText_Desc_NewBackgrounds_Old,       sText_Desc_NewBackgrounds_New},
    [MENUITEM_BATTLE_RUN_TYPE]            = {sText_Desc_Run_Type_Off,             sText_Desc_Run_Type_LR,             sText_Desc_Run_Type_B,         sText_Desc_Run_Type_B_2},
};

static const u8 sText_Desc_SoundMono[]                       = _("Sound is the same in all speakers.\nRecommended for original hardware.");
static const u8 sText_Desc_SoundStereo[]                     = _("Play the left and right audio channel\nseperatly. Great with headphones.");
static const u8 sText_Desc_Music_On[]                        = _("Enables music playback.\nChange maps to take effect.");
static const u8 sText_Desc_Music_Off[]                       = _("Disables music playback.\nChange maps to take effect.");
static const u8 sText_Desc_BikeMusicOn[]                     = _("Enables BIKE music.");
static const u8 sText_Desc_BikeMusicOff[]                    = _("Disables BIKE music.");
static const u8 sText_Desc_SurfMusicOn[]                     = _("Enables SURF music.");
static const u8 sText_Desc_SurfMusicOff[]                    = _("Disables SURF music.");
static const u8 sText_Desc_WildMonMusic_Hoenn[]              = _("Default music from Hoenn.");
static const u8 sText_Desc_WildMonMusic_Kanto_Old[]          = _("Music from Fire Red and Leaf Green.");
static const u8 sText_Desc_WildMonMusic_Sinnoh[]             = _("Music from Diamond, Pearl and\nPlatinum.");
static const u8 sText_Desc_WildMonMusic_Johto[]              = _("Music from Heart Gold and Soul Silver,\nbut from Johto.");
static const u8 sText_Desc_WildMonMusic_Kanto_New[]          = _("Music from Heart Gold and Soul Silver,\nbut from Kanto.");
static const u8 sText_Desc_WildMonMusic_Random[]             = _("Randomizes music from all available\ngames.");
static const u8 sText_Desc_SoundEffects_Gen3[]               = _("Default sound effects from GEN III.");
static const u8 sText_Desc_SoundEffects_DP[]                 = _("Sound effects from Diamond, Pearl\nand Platinum.");
static const u8 sText_Desc_SoundEffects_HGSS[]               = _("Sound effects from Heart Gold and\nSoul Silver.");

static const u8 *const sOptionMenuItemDescriptionsSound[MENUITEM_SOUND_COUNT][6] =
{
    [MENUITEM_SOUND_SOUND]          = {sText_Desc_SoundMono,              sText_Desc_SoundStereo,                 sText_Empty,                         sText_Empty,                       sText_Empty,                           sText_Empty},
    [MENUITEM_SOUND_MUSIC]          = {sText_Desc_Music_On,               sText_Desc_Music_Off,                   sText_Empty,                         sText_Empty,                       sText_Empty,                           sText_Empty},
    [MENUITEM_SOUND_BIKE_MUSIC]     = {sText_Desc_BikeMusicOn,            sText_Desc_BikeMusicOff,                sText_Empty,                         sText_Empty,                       sText_Empty,                           sText_Empty},
    [MENUITEM_SOUND_SURF_MUSIC]     = {sText_Desc_SurfMusicOn,            sText_Desc_SurfMusicOff,                sText_Empty,                         sText_Empty,                       sText_Empty,                           sText_Empty},
    [MENUITEM_SOUND_WILD_MON_MUSIC] = {sText_Desc_WildMonMusic_Hoenn,     sText_Desc_WildMonMusic_Kanto_Old,      sText_Desc_WildMonMusic_Sinnoh,      sText_Desc_WildMonMusic_Johto,     sText_Desc_WildMonMusic_Kanto_New,     sText_Desc_WildMonMusic_Random},
    [MENUITEM_SOUND_BATTLE_TRAINER_MUSIC] = {sText_Desc_WildMonMusic_Hoenn,     sText_Desc_WildMonMusic_Kanto_Old,      sText_Desc_WildMonMusic_Sinnoh,      sText_Desc_WildMonMusic_Johto,     sText_Desc_WildMonMusic_Kanto_New,     sText_Desc_WildMonMusic_Random},
    [MENUITEM_SOUND_BATTLE_FRONTIER_TRAINER_MUSIC] = {sText_Desc_WildMonMusic_Hoenn,     sText_Desc_WildMonMusic_Kanto_Old,      sText_Desc_WildMonMusic_Sinnoh,      sText_Desc_WildMonMusic_Johto,     sText_Desc_WildMonMusic_Kanto_New,     sText_Desc_WildMonMusic_Random},
    [MENUITEM_SOUND_EFFECTS]        = {sText_Desc_SoundEffects_Gen3,     sText_Desc_SoundEffects_DP,      sText_Desc_SoundEffects_HGSS,      sText_Empty,     sText_Empty,     sText_Empty},
};

// Disabled Descriptions
static const u8 sText_Desc_Disabled_Textspeed[]     = _("Only active if xyz.");
static const u8 sText_Desc_Disabled_BattleHPBar[]   = _("Only active if xyz.");
static const u8 *const sOptionMenuItemDescriptionsDisabledMain[MENUITEM_MAIN_COUNT] =
{
    [MENUITEM_MAIN_TEXTSPEED]   = sText_Desc_Disabled_Textspeed,
    [MENUITEM_MAIN_BATTLESCENE] = sText_Empty,
    [MENUITEM_MAIN_DIFFICULTY]  = sText_Empty,
    [MENUITEM_MAIN_BATTLESTYLE] = sText_Empty,
    [MENUITEM_MAIN_BUTTONMODE]  = sText_Empty,
    [MENUITEM_MAIN_FRAMETYPE]   = sText_Empty,
    [MENUITEM_MAIN_FOLLOWER]    = sText_Desc_Disabled_BattleHPBar,
    [MENUITEM_MAIN_LARGE_FOLLOWER]    = sText_Desc_Disabled_BattleHPBar,
    [MENUITEM_MAIN_AUTORUN]     = sText_Empty,
    [MENUITEM_MAIN_AUTORUN_SURF]     = sText_Empty,
    [MENUITEM_MAIN_AUTORUN_DIVE]     = sText_Empty,
    [MENUITEM_MAIN_MATCHCALL]   = sText_Empty,
    [MENUITEM_CUSTOM_FISHING]     = sText_Empty,
    [MENUITEM_MAIN_EVEN_FASTER_JOY]     = sText_Empty,
    [MENUITEM_MAIN_SKIP_INTRO]     = sText_Empty,
};

// Disabled Custom
static const u8 sText_Desc_Disabled_LR_Run[]   = _("Only active if L+R is selected above.");
static const u8 *const sOptionMenuItemDescriptionsDisabledCustom[MENUITEM_BATTLE_COUNT] =
{
    [MENUITEM_BATTLE_FAST_INTRO]          = sText_Empty,
    [MENUITEM_BATTLE_FAST_BATTLES]        = sText_Empty,
    [MENUITEM_BATTLE_SPLIT]               = sText_Empty,
    [MENUITEM_BATTLE_TYPE_EFFECTIVE]      = sText_Empty,
    [MENUITEM_BATTLE_LR_RUN]              = sText_Desc_Disabled_LR_Run,
    [MENUITEM_BATTLE_BALL_PROMPT]         = sText_Empty,
    [MENUITEM_BATTLE_NEW_BACKGROUNDS]     = sText_Empty,
    [MENUITEM_BATTLE_RUN_TYPE]            = sText_Empty,
};

static const u8 *const sOptionMenuItemDescriptionsDisabledSound[MENUITEM_SOUND_COUNT] =
{
    [MENUITEM_SOUND_SOUND]          = sText_Empty,
    [MENUITEM_SOUND_MUSIC]          = sText_Empty,
    [MENUITEM_SOUND_BIKE_MUSIC]     = sText_Empty,
    [MENUITEM_SOUND_SURF_MUSIC]     = sText_Empty,
    [MENUITEM_SOUND_WILD_MON_MUSIC] = sText_Empty,
    [MENUITEM_SOUND_BATTLE_TRAINER_MUSIC] = sText_Empty,
    [MENUITEM_SOUND_BATTLE_FRONTIER_TRAINER_MUSIC] = sText_Empty,
    [MENUITEM_SOUND_EFFECTS]        = sText_Empty,
};

static const u8 *const OptionTextDescription(void)
{
    u8 menuItem = sOptions->menuCursor[sOptions->submenu];
    u8 selection;

    switch (sOptions->submenu)
    {
    case MENU_MAIN:
        if (!CheckConditions(menuItem))
            return sOptionMenuItemDescriptionsDisabledMain[menuItem];
        selection = sOptions->sel[menuItem];
        if (menuItem == MENUITEM_MAIN_TEXTSPEED || menuItem == MENUITEM_MAIN_FRAMETYPE)
            selection = 0;
        return sOptionMenuItemDescriptionsMain[menuItem][selection];
    case MENU_CUSTOM:
        if (!CheckConditions(menuItem))
            return sOptionMenuItemDescriptionsDisabledCustom[menuItem];
        selection = sOptions->sel_battle[menuItem];
        return sOptionMenuItemDescriptionsCustom[menuItem][selection];
    case MENU_SOUND:
        if (!CheckConditions(menuItem))
            return sOptionMenuItemDescriptionsDisabledSound[menuItem];
        selection = sOptions->sel_sound[menuItem];
        return sOptionMenuItemDescriptionsSound[menuItem][selection];
    }
}


/* REPLACED TO LIMIT SOUND OPTIONS 
static u8 MenuItemCount(void)
{
    switch (sOptions->submenu)
    {
    case MENU_MAIN:     return MENUITEM_MAIN_COUNT;
    case MENU_CUSTOM:   return MENUITEM_BATTLE_COUNT;
    case MENU_SOUND:    return MENUITEM_SOUND_COUNT;
    }
}*/

static u8 MenuItemCount(void)
{
    switch (sOptions->submenu)
    {
    case MENU_MAIN:     return MENUITEM_MAIN_DIFFICULTY;
    case MENU_CUSTOM:   return MENUITEM_BATTLE_COUNT;
    case MENU_SOUND:    return MENUITEM_SOUND_BATTLE_TRAINER_MUSIC; // only show up to MUSIC
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

static const u8 sText_TopBar_Main[]         = _("OPTIONS");
static const u8 sText_TopBar_Main_Right[]   = _("{R_BUTTON}");
static const u8 sText_TopBar_Custom[]       = _("BATTLE OPTIONS");
static const u8 sText_TopBar_Custom_Left[]  = _("{L_BUTTON}");
static const u8 sText_TopBar_Sound[]        = _("SOUND");
static void DrawTopBarText(void)
{
    const u8 color[3] = { TEXT_DYNAMIC_COLOR_6, TEXT_COLOR_WHITE, TEXT_COLOR_OPTIONS_GRAY_FG };

    FillWindowPixelBuffer(WIN_TOPBAR, PIXEL_FILL(15));
    switch (sOptions->submenu)
    {
        case MENU_MAIN:
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 105, 1, color, 0, sText_TopBar_Main);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 222, 1, color, 0, sText_TopBar_Main_Right);
            break;
        case MENU_CUSTOM:
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 94, 1, color, 0, sText_TopBar_Custom);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 2, 1, color, 0, sText_TopBar_Custom_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 222, 1, color, 0, sText_TopBar_Main_Right);
            break;
        case MENU_SOUND:
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 106, 1, color, 0, sText_TopBar_Sound);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 2, 1, color, 0, sText_TopBar_Custom_Left);
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
        case MENU_MAIN:
            if (sItemFunctionsMain[id].drawChoices != NULL)
                sItemFunctionsMain[id].drawChoices(sOptions->sel[id], y);
            break;
        case MENU_CUSTOM:
            if (sItemFunctionsCustom[id].drawChoices != NULL)
                sItemFunctionsCustom[id].drawChoices(sOptions->sel_battle[id], y);
            break;

        /*REPLACED TO LIMIT SOUND OPTIONS
        case MENU_SOUND:
            if (sItemFunctionsSound[id].drawChoices != NULL)
                sItemFunctionsSound[id].drawChoices(sOptions->sel_sound[id], y);
            break;
        */
       case MENU_SOUND:
            if (id >= 2) // skip hidden ones
                return;
            if (sItemFunctionsSound[id].drawChoices != NULL)
                sItemFunctionsSound[id].drawChoices(sOptions->sel_sound[id], y);
            break;

        
    }
}

static void HighlightOptionMenuItem(void)
{
    int cursor = sOptions->visibleCursor[sOptions->submenu];

    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(Y_DIFF, 224));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(cursor * Y_DIFF + 24, cursor * Y_DIFF + 40));
}

void CB2_InitOptionPlusMenu(void)
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
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
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
        sOptions = AllocZeroed(sizeof(*sOptions));
        sOptions->sel[MENUITEM_MAIN_TEXTSPEED]           = gSaveBlock2Ptr->optionsTextSpeed;
        sOptions->sel[MENUITEM_MAIN_BATTLESCENE]         = gSaveBlock2Ptr->optionsBattleSceneOff;
        sOptions->sel[MENUITEM_MAIN_DIFFICULTY]          = gSaveBlock2Ptr->optionsDifficulty;
        sOptions->sel[MENUITEM_MAIN_BATTLESTYLE]         = gSaveBlock2Ptr->optionsBattleStyle;
        sOptions->sel[MENUITEM_MAIN_BUTTONMODE]          = gSaveBlock2Ptr->optionsButtonMode;
        sOptions->sel[MENUITEM_MAIN_FOLLOWER]            = gSaveBlock2Ptr->optionsfollowerEnable;
        sOptions->sel[MENUITEM_MAIN_LARGE_FOLLOWER]      = gSaveBlock2Ptr->optionsfollowerLargeEnable;
        sOptions->sel[MENUITEM_MAIN_AUTORUN]             = gSaveBlock2Ptr->optionsautoRun;
        sOptions->sel[MENUITEM_MAIN_AUTORUN_SURF]        = gSaveBlock2Ptr->optionsAutorunSurf;
        sOptions->sel[MENUITEM_MAIN_AUTORUN_DIVE]        = gSaveBlock2Ptr->optionsAutorunDive;
        sOptions->sel[MENUITEM_MAIN_FRAMETYPE]           = gSaveBlock2Ptr->optionsWindowFrameType;
        sOptions->sel[MENUITEM_MAIN_MATCHCALL]           = gSaveBlock2Ptr->optionsDisableMatchCall;
        sOptions->sel[MENUITEM_CUSTOM_FISHING]           = gSaveBlock2Ptr->optionsFishing;
        sOptions->sel[MENUITEM_MAIN_EVEN_FASTER_JOY]     = gSaveBlock2Ptr->optionsEvenFasterJoy;
        sOptions->sel[MENUITEM_MAIN_SKIP_INTRO]          = gSaveBlock2Ptr->optionsSkipIntro;
        sOptions->sel[MENUITEM_MAIN_UNIT_TYPE]           = gSaveBlock2Ptr->optionsUnitSystem;

        sOptions->sel_battle[MENUITEM_BATTLE_FAST_INTRO]        = gSaveBlock2Ptr->optionsFastIntro;
        sOptions->sel_battle[MENUITEM_BATTLE_FAST_BATTLES]      = gSaveBlock2Ptr->optionsFastBattle;
        sOptions->sel_battle[MENUITEM_BATTLE_SPLIT]             = gSaveBlock2Ptr->optionStyle;
        sOptions->sel_battle[MENUITEM_BATTLE_TYPE_EFFECTIVE]    = gSaveBlock2Ptr->optionTypeEffective;
        sOptions->sel_battle[MENUITEM_BATTLE_LR_RUN]            = gSaveBlock2Ptr->optionsLRtoRun;
        sOptions->sel_battle[MENUITEM_BATTLE_BALL_PROMPT]       = gSaveBlock2Ptr->optionsBallPrompt;
        sOptions->sel_battle[MENUITEM_BATTLE_NEW_BACKGROUNDS]   = gSaveBlock2Ptr->optionsNewBackgrounds;
        sOptions->sel_battle[MENUITEM_BATTLE_RUN_TYPE]          = gSaveBlock2Ptr->optionsRunType;

        sOptions->sel_sound[MENUITEM_SOUND_SOUND]                             = gSaveBlock2Ptr->optionsSound;
        sOptions->sel_sound[MENUITEM_SOUND_MUSIC]                             = gSaveBlock2Ptr->optionsMusicOnOff;
        sOptions->sel_sound[MENUITEM_SOUND_BIKE_MUSIC]                        = gSaveBlock2Ptr->optionsBikeMusic;
        sOptions->sel_sound[MENUITEM_SOUND_SURF_MUSIC]                        = gSaveBlock2Ptr->optionsSurfMusic;
        sOptions->sel_sound[MENUITEM_SOUND_WILD_MON_MUSIC]                    = gSaveBlock2Ptr->optionsWildBattleMusic;
        sOptions->sel_sound[MENUITEM_SOUND_BATTLE_TRAINER_MUSIC]              = gSaveBlock2Ptr->optionsTrainerBattleMusic;
        sOptions->sel_sound[MENUITEM_SOUND_BATTLE_FRONTIER_TRAINER_MUSIC]     = gSaveBlock2Ptr->optionsFrontierTrainerBattleMusic;
        sOptions->sel_sound[MENUITEM_SOUND_EFFECTS]                           = gSaveBlock2Ptr->optionsSoundEffects;

        sOptions->submenu = MENU_MAIN;

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
        
        sOptions->arrowTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 240 / 2, 20, 110, MENUITEM_MAIN_COUNT - 1, 110, 110, 0);

        for (i = 0; i < min(OPTIONS_ON_SCREEN, MenuItemCount()); i++)
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

static void Task_OptionMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_OptionMenuProcessInput;
}

static void Task_OptionMenuProcessInput(u8 taskId)
{
    int i = 0;
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN , MenuItemCount());
    if (JOY_NEW(B_BUTTON))
    {
        gTasks[taskId].func = Task_OptionMenuSave;
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
                sOptions->visibleCursor[sOptions->submenu] = sOptions->menuCursor[sOptions->submenu] = optionsToDraw-2;
                ScrollAll(0);
                sOptions->visibleCursor[sOptions->submenu] = optionsToDraw-1;
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
        if (sOptions->visibleCursor[sOptions->submenu] == optionsToDraw-2) // don't advance visible cursor until scrolled to the bottom
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
                sOptions->visibleCursor[sOptions->submenu] = optionsToDraw-2;
                sOptions->menuCursor[sOptions->submenu] = MenuItemCount() - optionsToDraw-1;
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
        if (sOptions->submenu == MENU_MAIN)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsMain[cursor].processInput != NULL)
                {
                    sOptions->sel[cursor] = sItemFunctionsMain[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
        else if (sOptions->submenu == MENU_CUSTOM)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_battle[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsCustom[cursor].processInput != NULL)
                {
                    sOptions->sel_battle[cursor] = sItemFunctionsCustom[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_battle[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
        else if (sOptions->submenu == MENU_SOUND)
        {
            int cursor = sOptions->menuCursor[sOptions->submenu];
            u8 previousOption = sOptions->sel_sound[cursor];
            if (CheckConditions(cursor))
            {
                if (sItemFunctionsSound[cursor].processInput != NULL)
                {
                    sOptions->sel_sound[cursor] = sItemFunctionsSound[cursor].processInput(previousOption);
                    ReDrawAll();
                    DrawDescriptionText();
                }

                if (previousOption != sOptions->sel_sound[cursor])
                    DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
            }
        }
    }
    else if (JOY_NEW(R_BUTTON))
    {
        if (sOptions->submenu != MENU_SOUND)
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
#if DEBUG
    if (JOY_HELD(SELECT_BUTTON) && JOY_NEW(START_BUTTON))
    {
        if (VarGet(VAR_DEBUG_OPTIONS) == 1)
        {
            VarSet(VAR_DEBUG_OPTIONS, 0);
            PlaySE(SE_PC_OFF);
        }
        else
        {
            VarSet(VAR_DEBUG_OPTIONS, 1);
            PlaySE(SE_PC_ON);
        }
    }
#endif // DEBUG
}

static void Task_OptionMenuSave(u8 taskId)
{
    gSaveBlock2Ptr->optionsTextSpeed             = sOptions->sel[MENUITEM_MAIN_TEXTSPEED];
    gSaveBlock2Ptr->optionsBattleSceneOff        = sOptions->sel[MENUITEM_MAIN_BATTLESCENE];
    gSaveBlock2Ptr->optionsDifficulty            = sOptions->sel[MENUITEM_MAIN_DIFFICULTY];
    gSaveBlock2Ptr->optionsBattleStyle           = sOptions->sel[MENUITEM_MAIN_BATTLESTYLE]; 
    gSaveBlock2Ptr->optionsButtonMode            = sOptions->sel[MENUITEM_MAIN_BUTTONMODE];
    gSaveBlock2Ptr->optionsfollowerEnable        = sOptions->sel[MENUITEM_MAIN_FOLLOWER];
    gSaveBlock2Ptr->optionsfollowerLargeEnable   = sOptions->sel[MENUITEM_MAIN_LARGE_FOLLOWER];
    gSaveBlock2Ptr->optionsautoRun               = sOptions->sel[MENUITEM_MAIN_AUTORUN];
    gSaveBlock2Ptr->optionsAutorunSurf           = sOptions->sel[MENUITEM_MAIN_AUTORUN_SURF];
    gSaveBlock2Ptr->optionsAutorunDive           = sOptions->sel[MENUITEM_MAIN_AUTORUN_DIVE];
    gSaveBlock2Ptr->optionsDisableMatchCall      = sOptions->sel[MENUITEM_MAIN_MATCHCALL];
    gSaveBlock2Ptr->optionsWindowFrameType       = sOptions->sel[MENUITEM_MAIN_FRAMETYPE];
    gSaveBlock2Ptr->optionsFishing               = sOptions->sel[MENUITEM_CUSTOM_FISHING];
    gSaveBlock2Ptr->optionsEvenFasterJoy         = sOptions->sel[MENUITEM_MAIN_EVEN_FASTER_JOY];
    gSaveBlock2Ptr->optionsSkipIntro             = sOptions->sel[MENUITEM_MAIN_SKIP_INTRO];
    gSaveBlock2Ptr->optionsUnitSystem            = sOptions->sel[MENUITEM_MAIN_UNIT_TYPE];

    gSaveBlock2Ptr->optionsFastIntro        = sOptions->sel_battle[MENUITEM_BATTLE_FAST_INTRO];
    gSaveBlock2Ptr->optionsFastBattle       = sOptions->sel_battle[MENUITEM_BATTLE_FAST_BATTLES];
    gSaveBlock2Ptr->optionStyle             = sOptions->sel_battle[MENUITEM_BATTLE_SPLIT];
    gSaveBlock2Ptr->optionTypeEffective     = sOptions->sel_battle[MENUITEM_BATTLE_TYPE_EFFECTIVE];
    gSaveBlock2Ptr->optionsLRtoRun          = sOptions->sel_battle[MENUITEM_BATTLE_LR_RUN];
    gSaveBlock2Ptr->optionsBallPrompt       = sOptions->sel_battle[MENUITEM_BATTLE_BALL_PROMPT];
    gSaveBlock2Ptr->optionsNewBackgrounds   = sOptions->sel_battle[MENUITEM_BATTLE_NEW_BACKGROUNDS];
    gSaveBlock2Ptr->optionsRunType          = sOptions->sel_battle[MENUITEM_BATTLE_RUN_TYPE];
    
    gSaveBlock2Ptr->optionsSound            = sOptions->sel_sound[MENUITEM_SOUND_SOUND];
    gSaveBlock2Ptr->optionsMusicOnOff       = sOptions->sel_sound[MENUITEM_SOUND_MUSIC];
    gSaveBlock2Ptr->optionsBikeMusic        = sOptions->sel_sound[MENUITEM_SOUND_BIKE_MUSIC];
    gSaveBlock2Ptr->optionsSurfMusic        = sOptions->sel_sound[MENUITEM_SOUND_SURF_MUSIC];
    gSaveBlock2Ptr->optionsWildBattleMusic  = sOptions->sel_sound[MENUITEM_SOUND_WILD_MON_MUSIC];
    gSaveBlock2Ptr->optionsTrainerBattleMusic  = sOptions->sel_sound[MENUITEM_SOUND_BATTLE_TRAINER_MUSIC];
    gSaveBlock2Ptr->optionsFrontierTrainerBattleMusic  = sOptions->sel_sound[MENUITEM_SOUND_BATTLE_FRONTIER_TRAINER_MUSIC];
    gSaveBlock2Ptr->optionsSoundEffects  = sOptions->sel_sound[MENUITEM_SOUND_EFFECTS];

    //ADDED TO SET THESE TO DEFAULTS SINCE THEY WERE REMOVED
    gSaveBlock2Ptr->optionsBikeMusic = 0;
    gSaveBlock2Ptr->optionsSurfMusic = 0;
    gSaveBlock2Ptr->optionsWildBattleMusic = 3;
    gSaveBlock2Ptr->optionsTrainerBattleMusic = 3;
    gSaveBlock2Ptr->optionsFrontierTrainerBattleMusic = 3;
    gSaveBlock2Ptr->optionsSoundEffects = 2;


    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gTasks[taskId].func = Task_OptionMenuFadeOut;
}

static void Task_OptionMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        FREE_AND_SET_NULL(sOptions);
        SetMainCallback2(gMain.savedCallback);
    }
}

static void ScrollMenu(int direction)
{
    int menuItem, pos;
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN, MenuItemCount());

    if (direction == 0) // scroll down
        menuItem = sOptions->menuCursor[sOptions->submenu] + NUM_OPTIONS_FROM_BORDER, pos = optionsToDraw - 1;
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
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN, MenuItemCount());

    scrollCount = MenuItemCount() - optionsToDraw;

    // Move items up/down
    ScrollWindow(WIN_OPTIONS, direction, Y_DIFF * scrollCount, PIXEL_FILL(1));

    // Clear moved items
    if (direction == 0)
    {
        y = optionsToDraw - scrollCount;
        if (y < 0)
            y = optionsToDraw;
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
            menuItem = MenuItemCount() - 1 - i, pos = optionsToDraw - 1 - i;
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

static int ProcessInput_Options_Six(int selection)
{
    return XOptions_ProcessInput(6, selection);
}

static int ProcessInput_Options_Eleven(int selection)
{
    return XOptions_ProcessInput(11, selection);
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

static int ProcessInput_BattleStyle(int selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
        if ((gSaveBlock2Ptr->optionsDifficulty == 2) && (gSaveBlock1Ptr->tx_Features_LimitDifficulty == 1) && (FlagGet(FLAG_SYS_GAME_CLEAR)))
        {
            selection ^= 1;
        }
        else if ((gSaveBlock2Ptr->optionsDifficulty == 2) && (gSaveBlock1Ptr->tx_Features_LimitDifficulty == 1))
        {
            PlaySE(SE_FAILURE);
        }
        else
        {
            selection ^= 1;
        }

    return selection;
}

static int ProcessInput_Difficulty(int selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if ((gSaveBlock1Ptr->tx_Features_LimitDifficulty == 1) && (FlagGet(FLAG_SYS_GAME_CLEAR) == 0))
            PlaySE(SE_FAILURE);
        else if (++selection > (3 - 1))
            selection = 0;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if ((gSaveBlock1Ptr->tx_Features_LimitDifficulty == 1) && (FlagGet(FLAG_SYS_GAME_CLEAR) == 0))
            PlaySE(SE_FAILURE);
        else if (--selection < 0)
            selection = (3 - 1);
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

static void DrawChoices_Options_Six(const u8 *const *const strings, int selection, int y, bool8 active)
{
    static const u8 choiceOrders[][2] =
    {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5},
        {5, 0},
    };
    u8 styles[6] = {0};
    const u8 *order = choiceOrders[selection];
    styles[selection] = 1;

    DrawOptionMenuChoice(strings[order[0]], 104, y, styles[order[0]], active);
    DrawOptionMenuChoice(strings[order[1]], GetStringRightAlignXOffset(1, strings[order[1]], 198), y, styles[order[1]], active);
}

static void ReDrawAll(void)
{
    u8 menuItem = sOptions->menuCursor[sOptions->submenu] - sOptions->visibleCursor[sOptions->submenu];
    u8 i;
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN, MenuItemCount());

    if (MenuItemCount() <= OPTIONS_ON_SCREEN) // Draw or delete the scrolling arrows based on options in the menu
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
    for (i = 0; i < optionsToDraw; i++)
    {
        DrawChoices(menuItem+i, i * Y_DIFF);
        DrawLeftSideOptionText(menuItem+i, (i * Y_DIFF) + 1);
    }
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}

// Process Input functions ****SPECIFIC****
static const u8 sText_Faster[] = _("FASTER");
static const u8 sText_Instant[] = _("INSTANT");
static const u8 *const sTextSpeedStrings[] = {gText_TextSpeedSlow, gText_TextSpeedMid, gText_TextSpeedFast, sText_Faster};
static void DrawChoices_TextSpeed(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_TEXTSPEED);
    DrawChoices_Options_Four(sTextSpeedStrings, selection, y, active);
}

static void DrawChoices_BattleScene(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_BATTLESCENE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_Difficulty(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_DIFFICULTY);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(gText_Easy, gText_ButtonTypeNormal, gText_Hard);
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsDifficulty = 0; //Easy
        FlagClear(FLAG_DIFFICULTY_HARD);
    }
    else if (selection == 1)
    {
        gSaveBlock2Ptr->optionsDifficulty = 1; //Normal
        FlagClear(FLAG_DIFFICULTY_HARD);
    }
    else
    {
        gSaveBlock2Ptr->optionsDifficulty = 2; //Hard
        FlagSet(FLAG_DIFFICULTY_HARD);
    }

    DrawOptionMenuChoice(gText_Easy, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_ButtonTypeNormal, xMid, y, styles[1], active);
    DrawOptionMenuChoice(gText_Hard, GetStringRightAlignXOffset(1, gText_ButtonTypeLEqualsA, 198), y, styles[2], active);
}
static const u8 sText_Sound_WildMon_Hoenn[]       = _("HOENN");
static const u8 sText_Sound_WildMon_Kanto_Old[]   = _("KANTO 1");
static const u8 sText_Sound_WildMon_Sinnoh[]      = _("SINNOH");
static const u8 sText_Sound_WildMon_Johto[]       = _("JOHTO");
static const u8 sText_Sound_WildMon_Kanto_New[]   = _("KANTO 2");
static const u8 sText_Sound_WildMon_Random[]      = _("RANDOM");

static const u8 *const sText_Sound_WildMonBattleMusic_Strings[] = {sText_Sound_WildMon_Hoenn,  sText_Sound_WildMon_Kanto_Old,  sText_Sound_WildMon_Sinnoh,  sText_Sound_WildMon_Johto,  sText_Sound_WildMon_Kanto_New,   sText_Sound_WildMon_Random};
static void DrawChoices_Wild_Battle_Music(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_SOUND_WILD_MON_MUSIC);
    DrawChoices_Options_Six(sText_Sound_WildMonBattleMusic_Strings, selection, y, active);
    
    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsWildBattleMusic = 0; // Hoenn
    }
    else if (selection == 1)
    {
        gSaveBlock2Ptr->optionsWildBattleMusic = 1; // Kanto1
    }
    else if (selection == 2)
    {
        gSaveBlock2Ptr->optionsWildBattleMusic = 2; // Sinnoh
    }
    else if (selection == 3)
    {
        gSaveBlock2Ptr->optionsWildBattleMusic = 3; // Johto
    }
    else if (selection == 4)
    {
        gSaveBlock2Ptr->optionsWildBattleMusic = 4; // Kanto 2
    }
    else //(selection == 5)
    {
        gSaveBlock2Ptr->optionsWildBattleMusic = 5; // Random
    }
}

static void DrawChoices_Trainer_Battle_Music(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_SOUND_BATTLE_TRAINER_MUSIC);
    DrawChoices_Options_Six(sText_Sound_WildMonBattleMusic_Strings, selection, y, active);
    
    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsTrainerBattleMusic = 0; // Hoenn
    }
    else if (selection == 1)
    {
        gSaveBlock2Ptr->optionsTrainerBattleMusic = 1; // Kanto1
    }
    else if (selection == 2)
    {
        gSaveBlock2Ptr->optionsTrainerBattleMusic = 2; // Sinnoh
    }
    else if (selection == 3)
    {
        gSaveBlock2Ptr->optionsTrainerBattleMusic = 3; // Johto
    }
    else if (selection == 4)
    {
        gSaveBlock2Ptr->optionsTrainerBattleMusic = 4; // Kanto 2
    }
    else //(selection == 5)
    {
        gSaveBlock2Ptr->optionsTrainerBattleMusic = 5; // Random
    }
}

static void DrawChoices_Frontier_Trainer_Battle_Music(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_SOUND_BATTLE_FRONTIER_TRAINER_MUSIC);
    DrawChoices_Options_Six(sText_Sound_WildMonBattleMusic_Strings, selection, y, active);
    
    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsFrontierTrainerBattleMusic = 0; // Hoenn
    }
    else if (selection == 1)
    {
        gSaveBlock2Ptr->optionsFrontierTrainerBattleMusic = 1; // Kanto1
    }
    else if (selection == 2)
    {
        gSaveBlock2Ptr->optionsFrontierTrainerBattleMusic = 2; // Sinnoh
    }
    else if (selection == 3)
    {
        gSaveBlock2Ptr->optionsFrontierTrainerBattleMusic = 3; // Johto
    }
    else if (selection == 4)
    {
        gSaveBlock2Ptr->optionsFrontierTrainerBattleMusic = 4; // Kanto 2
    }
    else //(selection == 5)
    {
        gSaveBlock2Ptr->optionsFrontierTrainerBattleMusic = 5; // Random
    }
}

static const u8 sText_Sound_Effects_Gen3[]      = _("GEN 3");
static const u8 sText_Sound_Effects_DP[]        = _("DPL");
static const u8 sText_Sound_Effects_HGSS[]      = _("HGSS");

static void DrawChoices_Sound_Effects(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_SOUND_EFFECTS);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Sound_Effects_Gen3, sText_Sound_Effects_DP, sText_Sound_Effects_HGSS);
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsSoundEffects = 0; //Gen 3
    }
    else if (selection == 1)
    {
        gSaveBlock2Ptr->optionsSoundEffects = 1; //DPL
    }
    else
    {
        gSaveBlock2Ptr->optionsSoundEffects = 2; //HGSS
    }

    DrawOptionMenuChoice(sText_Sound_Effects_Gen3, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Sound_Effects_DP, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_Sound_Effects_HGSS, GetStringRightAlignXOffset(1, sText_Sound_Effects_DP, 198), y, styles[2], active);
}

static void DrawChoices_BattleStyle(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_BATTLESTYLE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleStyleShift, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleStyleSet, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleStyleSet, 198), y, styles[1], active);
}

static void DrawChoices_Sound(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_SOUND_SOUND);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_SoundMono, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_SoundStereo, GetStringRightAlignXOffset(FONT_NORMAL, gText_SoundStereo, 198), y, styles[1], active);
}

static void DrawChoices_ButtonMode(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_BUTTONMODE);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(gText_ButtonTypeNormal, gText_ButtonTypeLR, gText_ButtonTypeLEqualsA);
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_ButtonTypeNormal, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_ButtonTypeLR, xMid, y, styles[1], active);
    DrawOptionMenuChoice(gText_ButtonTypeLEqualsA, GetStringRightAlignXOffset(1, gText_ButtonTypeLEqualsA, 198), y, styles[2], active);
}

static void DrawChoices_FrameType(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_FRAMETYPE);
    u8 text[16];
    u8 n = selection + 1;
    u16 i;

    for (i = 0; gText_FrameTypeNumber[i] != EOS && i <= 5; i++)
        text[i] = gText_FrameTypeNumber[i];

    // Convert a number to decimal string
    if (n / 10 != 0)
    {
        text[i] = n / 10 + CHAR_0;
        i++;
        text[i] = n % 10 + CHAR_0;
        i++;
    }
    else
    {
        text[i] = n % 10 + CHAR_0;
        i++;
        text[i] = 0x77;
        i++;
    }

    text[i] = EOS;

    DrawOptionMenuChoice(gText_FrameType, 104, y, 0, active);
    DrawOptionMenuChoice(text, 128, y, 1, active);
}

static void DrawChoices_Follower(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_FOLLOWER);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_LargeFollower(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_LARGE_FOLLOWER);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsfollowerLargeEnable = 0; //on
    }
    else
    {
        gSaveBlock2Ptr->optionsfollowerLargeEnable = 1; //off
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}


static void DrawChoices_Autorun(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_AUTORUN);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsautoRun = 0;
    }
    else
    {
        gSaveBlock2Ptr->optionsautoRun = 1;
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_MatchCall(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_MATCHCALL);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_Style(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_SPLIT);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionStyle = 0; //Phy / sp split on
    }
    else
    {
        gSaveBlock2Ptr->optionStyle = 1; //Phy / sp split off
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_TypeEffective(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_TYPE_EFFECTIVE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionTypeEffective = 0; //Yes
    }
    else
    {
        gSaveBlock2Ptr->optionTypeEffective = 1; //No
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_Fishing(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_CUSTOM_FISHING);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsFishing = 0; //FRLG
    }
    else
    {
        gSaveBlock2Ptr->optionsFishing = 1; //Emerald
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_FastIntro(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_FAST_INTRO);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsFastIntro = 0; //On
    }
    else
    {
        gSaveBlock2Ptr->optionsFastIntro = 1; //Off
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_FastBattles(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_FAST_BATTLES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsFastBattle = 1; //on
    }
    else
    {
        gSaveBlock2Ptr->optionsFastBattle = 0; //Off
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_BikeMusic(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_SOUND_BIKE_MUSIC);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsBikeMusic = 0; //music on
    }
    else
    {
        gSaveBlock2Ptr->optionsBikeMusic = 1; //music off
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_EvenFasterJoy(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_EVEN_FASTER_JOY);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsEvenFasterJoy = 0; //extremely fast joy
        FlagSet(FLAG_EVEN_FASTER_JOY);
    }
    else
    {
        gSaveBlock2Ptr->optionsEvenFasterJoy = 1; //normal joy
        FlagClear(FLAG_EVEN_FASTER_JOY);
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_SurfMusic(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_SOUND_SURF_MUSIC);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsSurfMusic = 0; //music on
    }
    else
    {
        gSaveBlock2Ptr->optionsSurfMusic = 1; //music off
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_Skip_Intro(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_SKIP_INTRO);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsSkipIntro = 0; //Skips intro
    }
    else
    {
        gSaveBlock2Ptr->optionsSkipIntro = 1; //Doesn't skip intro
    }
    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_LR_Run(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_LR_RUN);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsLRtoRun = 0; //Shows prompt
    }
    else
    {
        gSaveBlock2Ptr->optionsLRtoRun = 1; //Doesn't show prompt
    }
    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_Ball_Prompt(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_BALL_PROMPT);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsBallPrompt = 0; //Shows PKBALL prompt
    }
    else
    {
        gSaveBlock2Ptr->optionsBallPrompt = 1; //Doesn't show PKBALL prompt
    }
    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static const u8 sText_Metric[]        = _("METRIC");
static const u8 sText_Imperial[]      = _("IMPERIAL");
static void DrawChoices_Unit_Type(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_UNIT_TYPE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsUnitSystem = 0; //METRIC
    }
    else
    {
        gSaveBlock2Ptr->optionsUnitSystem = 1; //IMPERIAL
    }
    DrawOptionMenuChoice(sText_Metric, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Imperial, GetStringRightAlignXOffset(1, sText_Imperial, 198), y, styles[1], active);
}

static void DrawChoices_Music(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_SOUND_MUSIC);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsMusicOnOff = 0; //Yes music
    }
    else
    {
        gSaveBlock2Ptr->optionsMusicOnOff = 1; //No music
    }
    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}
static const u8 sText_Old[]        = _("OLD");
static const u8 sText_New[]        = _("MODERN");
static void DrawChoices_New_Backgrounds(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_NEW_BACKGROUNDS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsNewBackgrounds = 0; //Old backgrounds
    }
    else
    {
        gSaveBlock2Ptr->optionsNewBackgrounds = 1; //New backgrounds
    }
    DrawOptionMenuChoice(sText_Old, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_New, GetStringRightAlignXOffset(1, sText_New, 198), y, styles[1], active);
}

static const u8 sText_No[]        = _("NO");
static const u8 sText_LR[]        = _("L+R+A");
static const u8 sText_B[]         = _("B->A");
static const u8 sText_B_2[]       = _("B");
static const u8 *const sRunTypeStrings[] = {sText_No, sText_LR, sText_B, sText_B_2};
static void DrawChoices_Run_Type(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_RUN_TYPE);
    DrawChoices_Options_Four(sRunTypeStrings, selection, y, active);

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsRunType = 0; //No
        sOptions->sel_battle[MENUITEM_BATTLE_LR_RUN]          = gSaveBlock2Ptr->optionsLRtoRun = 1;
    }
    else if (selection == 1)
    {
        gSaveBlock2Ptr->optionsRunType = 1; //LR
    }
    else if (selection == 2)
    {
        gSaveBlock2Ptr->optionsRunType = 2; //B->A
        sOptions->sel_battle[MENUITEM_BATTLE_LR_RUN]          = gSaveBlock2Ptr->optionsLRtoRun = 1;
    }
    else
    {
        gSaveBlock2Ptr->optionsRunType = 3; //Hold B (before battle)
    }
}

static void DrawChoices_Autorun_Surf(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_AUTORUN_SURF);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsAutorunSurf = 0; //yes
    }
    else
    {
        gSaveBlock2Ptr->optionsAutorunSurf = 1; //no
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
}

static void DrawChoices_Autorun_Dive(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MAIN_AUTORUN_DIVE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    if (selection == 0)
    {
        gSaveBlock2Ptr->optionsAutorunDive = 0; //yes
    }
    else
    {
        gSaveBlock2Ptr->optionsAutorunDive = 1; //no
    }

    DrawOptionMenuChoice(gText_BattleSceneOn, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleSceneOff, GetStringRightAlignXOffset(1, gText_BattleSceneOff, 198), y, styles[1], active);
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