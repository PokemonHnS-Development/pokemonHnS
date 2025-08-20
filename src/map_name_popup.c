#include "global.h"
#include "battle_pyramid.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "menu.h"
#include "map_name_popup.h"
#include "palette.h"
#include "region_map.h"
#include "start_menu.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "constants/battle_frontier.h"
#include "constants/layouts.h"
#include "constants/region_map_sections.h"
#include "constants/weather.h"

// enums
enum MapPopUp_Themes
{
    MAPPOPUP_THEME_WOOD,
    MAPPOPUP_THEME_CHERRY,
    MAPPOPUP_THEME_STONE,
    MAPPOPUP_THEME_FALL,
    MAPPOPUP_THEME_UNDERWATER,
    MAPPOPUP_THEME_STONE2,
    MAPPOPUP_THEME_CLIFF,
    MAPPOPUP_THEME_JOHTO_ROUTE,
    MAPPOPUP_THEME_KANTO_ROUTE,
    MAPPOPUP_THEME_HISTORIC,
    MAPPOPUP_THEME_CITY,
    MAPPOPUP_THEME_TOWN,
};

// static functions
static void Task_MapNamePopUpWindow(u8 taskId);
static void ShowMapNamePopUpWindow(void);
static void LoadMapNamePopUpWindowBg(void);

// EWRAM
static EWRAM_DATA u8 sPopupTaskId = 0;

// .rodata
static const u8 sMapPopUp_Table[][960] =
{
    [MAPPOPUP_THEME_WOOD]       = INCBIN_U8("graphics/map_popup/woods.4bpp"),
    [MAPPOPUP_THEME_CHERRY]     = INCBIN_U8("graphics/map_popup/cherry.4bpp"),
    [MAPPOPUP_THEME_FALL]      = INCBIN_U8("graphics/map_popup/fall.4bpp"),
    [MAPPOPUP_THEME_STONE]      = INCBIN_U8("graphics/map_popup/stone.4bpp"),
    [MAPPOPUP_THEME_STONE2]     = INCBIN_U8("graphics/map_popup/stone2.4bpp"),
    [MAPPOPUP_THEME_UNDERWATER] = INCBIN_U8("graphics/map_popup/ocean.4bpp"),
    [MAPPOPUP_THEME_CLIFF]     = INCBIN_U8("graphics/map_popup/cliff.4bpp"),
    [MAPPOPUP_THEME_JOHTO_ROUTE]     = INCBIN_U8("graphics/map_popup/johto.4bpp"),
    [MAPPOPUP_THEME_KANTO_ROUTE]     = INCBIN_U8("graphics/map_popup/kanto.4bpp"),
    [MAPPOPUP_THEME_HISTORIC]     = INCBIN_U8("graphics/map_popup/historic.4bpp"),
    [MAPPOPUP_THEME_CITY]     = INCBIN_U8("graphics/map_popup/city.4bpp"),
    [MAPPOPUP_THEME_TOWN]     = INCBIN_U8("graphics/map_popup/town.4bpp"),       
};

static const u8 sMapPopUp_OutlineTable[][960] =
{
    [MAPPOPUP_THEME_WOOD]       = INCBIN_U8("graphics/map_popup/woods_outline.4bpp"),
    [MAPPOPUP_THEME_CHERRY]     = INCBIN_U8("graphics/map_popup/cherry_outline.4bpp"),
    [MAPPOPUP_THEME_FALL]      = INCBIN_U8("graphics/map_popup/fall_outline.4bpp"),
    [MAPPOPUP_THEME_STONE]      = INCBIN_U8("graphics/map_popup/stone_outline.4bpp"),
    [MAPPOPUP_THEME_STONE2]     = INCBIN_U8("graphics/map_popup/stone2_outline.4bpp"),
    [MAPPOPUP_THEME_UNDERWATER] = INCBIN_U8("graphics/map_popup/ocean_outline.4bpp"),
    [MAPPOPUP_THEME_CLIFF]     = INCBIN_U8("graphics/map_popup/cliff_outline.4bpp"),
    [MAPPOPUP_THEME_JOHTO_ROUTE]     = INCBIN_U8("graphics/map_popup/johto_outline.4bpp"),
    [MAPPOPUP_THEME_KANTO_ROUTE]     = INCBIN_U8("graphics/map_popup/kanto_outline.4bpp"),
    [MAPPOPUP_THEME_HISTORIC]     = INCBIN_U8("graphics/map_popup/historic_outline.4bpp"),
    [MAPPOPUP_THEME_CITY]     = INCBIN_U8("graphics/map_popup/city_outline.4bpp"),
    [MAPPOPUP_THEME_TOWN]     = INCBIN_U8("graphics/map_popup/town_outline.4bpp"),
};

static const u16 sMapPopUp_PaletteTable[][16] =
{
    [MAPPOPUP_THEME_WOOD]       = INCBIN_U16("graphics/map_popup/woods.gbapal"),
    [MAPPOPUP_THEME_CHERRY]     = INCBIN_U16("graphics/map_popup/cherry_outline.gbapal"),
    [MAPPOPUP_THEME_FALL]      = INCBIN_U16("graphics/map_popup/fall_outline.gbapal"),    
    [MAPPOPUP_THEME_STONE]      = INCBIN_U16("graphics/map_popup/stone_outline.gbapal"),
    [MAPPOPUP_THEME_STONE2]     = INCBIN_U16("graphics/map_popup/stone2_outline.gbapal"),
    [MAPPOPUP_THEME_UNDERWATER] = INCBIN_U16("graphics/map_popup/ocean_outline.gbapal"),
    [MAPPOPUP_THEME_CLIFF]     = INCBIN_U16("graphics/map_popup/cliff_outline.gbapal"),
    [MAPPOPUP_THEME_JOHTO_ROUTE]     = INCBIN_U16("graphics/map_popup/johto_outline.gbapal"),
    [MAPPOPUP_THEME_KANTO_ROUTE]     = INCBIN_U16("graphics/map_popup/kanto_outline.gbapal"),
    [MAPPOPUP_THEME_HISTORIC]     = INCBIN_U16("graphics/map_popup/historic_outline.gbapal"),
    [MAPPOPUP_THEME_CITY]     = INCBIN_U16("graphics/map_popup/city_outline.gbapal"),
    [MAPPOPUP_THEME_TOWN]     = INCBIN_U16("graphics/map_popup/town_outline.gbapal"),

};

static const u16 sMapPopUp_Palette_Underwater[16] = INCBIN_U16("graphics/map_popup/underwater.gbapal");

// -1 in the size excludes MAPSEC_NONE.
// The MAPSEC values for Kanto (between MAPSEC_DYNAMIC and MAPSEC_AQUA_HIDEOUT) are also excluded,
// and this is then handled by subtracting KANTO_MAPSEC_COUNT here and in LoadMapNamePopUpWindowBg.
static const u8 sMapSectionToThemeId[MAPSEC_COUNT - KANTO_MAPSEC_COUNT - 1] =
{
    [MAPSEC_NEW_BARK_TOWN] = MAPPOPUP_THEME_TOWN,
    [MAPSEC_VIOLET_CITY] = MAPPOPUP_THEME_HISTORIC,
    [MAPSEC_AZALEA_TOWN] = MAPPOPUP_THEME_TOWN,
    [MAPSEC_GOLDENROD_CITY] = MAPPOPUP_THEME_CITY,
    [MAPSEC_ECRUTEAK_CITY] = MAPPOPUP_THEME_HISTORIC,
    [MAPSEC_OLIVINE_CITY] = MAPPOPUP_THEME_CITY,
    [MAPSEC_CIANWOOD_CITY] = MAPPOPUP_THEME_TOWN,
    [MAPSEC_SAFARI_ZONE_GATE] = MAPPOPUP_THEME_CLIFF,
    [MAPSEC_MAHOGANY_TOWN] = MAPPOPUP_THEME_TOWN,
    [MAPSEC_BLACKTHORN_CITY] = MAPPOPUP_THEME_HISTORIC,
    [MAPSEC_CHERRYGROVE_CITY] = MAPPOPUP_THEME_CHERRY,
    [MAPSEC_FORTREE_CITY] = MAPPOPUP_THEME_FALL,
    [MAPSEC_LILYCOVE_CITY] = MAPPOPUP_THEME_CHERRY,
    [MAPSEC_MOSSDEEP_CITY] = MAPPOPUP_THEME_FALL,
    [MAPSEC_SOOTOPOLIS_CITY] = MAPPOPUP_THEME_CHERRY,
    [MAPSEC_INDIGO_PLATEAU] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_26] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_27] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_28] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_29] = MAPPOPUP_THEME_JOHTO_ROUTE,
    [MAPSEC_ROUTE_30] = MAPPOPUP_THEME_CHERRY,
    [MAPSEC_ROUTE_31] = MAPPOPUP_THEME_CHERRY,
    [MAPSEC_ROUTE_32] = MAPPOPUP_THEME_CLIFF,
    [MAPSEC_ROUTE_33] = MAPPOPUP_THEME_CLIFF,
    [MAPSEC_ROUTE_34] = MAPPOPUP_THEME_JOHTO_ROUTE,
    [MAPSEC_ROUTE_35] = MAPPOPUP_THEME_JOHTO_ROUTE,
    [MAPSEC_ROUTE_36] = MAPPOPUP_THEME_JOHTO_ROUTE,
    [MAPSEC_ROUTE_37] = MAPPOPUP_THEME_FALL,
    [MAPSEC_ROUTE_38] = MAPPOPUP_THEME_FALL,
    [MAPSEC_ROUTE_39] = MAPPOPUP_THEME_FALL,
    [MAPSEC_ROUTE_40] = MAPPOPUP_THEME_UNDERWATER,
    [MAPSEC_ROUTE_41] = MAPPOPUP_THEME_UNDERWATER,
    [MAPSEC_ROUTE_42] = MAPPOPUP_THEME_JOHTO_ROUTE,
    [MAPSEC_ROUTE_43] = MAPPOPUP_THEME_CLIFF,
    [MAPSEC_ROUTE_44] = MAPPOPUP_THEME_JOHTO_ROUTE,
    [MAPSEC_ROUTE_45] = MAPPOPUP_THEME_CLIFF,
    [MAPSEC_ROUTE_46] = MAPPOPUP_THEME_JOHTO_ROUTE,
    [MAPSEC_ROUTE_47] = MAPPOPUP_THEME_CLIFF,
    [MAPSEC_ROUTE_48] = MAPPOPUP_THEME_CLIFF,

    [MAPSEC_ROUTE_1] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_2] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_3] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_4] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_5] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_6] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_7] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_8] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_9] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_10] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_11] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_12] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_13] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_14] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_15] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_16] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_17] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_18] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_19] = MAPPOPUP_THEME_UNDERWATER,
    [MAPSEC_ROUTE_20] = MAPPOPUP_THEME_UNDERWATER,
    [MAPSEC_ROUTE_21] = MAPPOPUP_THEME_UNDERWATER,
    [MAPSEC_ROUTE_22] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_23] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_24] = MAPPOPUP_THEME_KANTO_ROUTE,
    [MAPSEC_ROUTE_25] = MAPPOPUP_THEME_KANTO_ROUTE,

    [MAPSEC_PALLET_TOWN] = MAPPOPUP_THEME_TOWN,
    [MAPSEC_VIRIDIAN_CITY] = MAPPOPUP_THEME_CITY,
    [MAPSEC_PEWTER_CITY] = MAPPOPUP_THEME_CITY,
    [MAPSEC_CERULEAN_CITY] = MAPPOPUP_THEME_CITY,
    [MAPSEC_VERMILION_CITY] = MAPPOPUP_THEME_CITY,
    [MAPSEC_LAVENDER_TOWN] = MAPPOPUP_THEME_HISTORIC,
    [MAPSEC_CELADON_CITY] = MAPPOPUP_THEME_CITY,
    [MAPSEC_SAFFRON_CITY] = MAPPOPUP_THEME_CITY,
    [MAPSEC_FUCHSIA_CITY] = MAPPOPUP_THEME_CITY,
    [MAPSEC_CINNABAR_ISLAND] = MAPPOPUP_THEME_UNDERWATER,

    [MAPSEC_VIRIDIAN_FOREST] = MAPPOPUP_THEME_WOOD,
    [MAPSEC_MT_MOON] = MAPPOPUP_THEME_STONE,
    [MAPSEC_DIGLETTS_CAVE] = MAPPOPUP_THEME_STONE,
    [MAPSEC_ROCK_TUNNEL] = MAPPOPUP_THEME_STONE,
    [MAPSEC_SEAFOAM_ISLANDS] = MAPPOPUP_THEME_UNDERWATER,
    [MAPSEC_CERULEAN_CAVE] = MAPPOPUP_THEME_STONE,


    [MAPSEC_DARK_CAVE] = MAPPOPUP_THEME_STONE2,
    [MAPSEC_UNION_CAVE] = MAPPOPUP_THEME_STONE2,
    [MAPSEC_ILEX_FOREST] = MAPPOPUP_THEME_WOOD,
    [MAPSEC_NATIONAL_PARK] = MAPPOPUP_THEME_JOHTO_ROUTE,
    [MAPSEC_WHIRL_ISLANDS] = MAPPOPUP_THEME_STONE2,
    [MAPSEC_CLIFF_CAVE] = MAPPOPUP_THEME_STONE,
    [MAPSEC_MT_MORTAR] = MAPPOPUP_THEME_STONE2,
    [MAPSEC_LAKE_OF_RAGE] = MAPPOPUP_THEME_CLIFF,
    [MAPSEC_ICE_PATH] = MAPPOPUP_THEME_STONE2,
    [MAPSEC_MT_SILVER] = MAPPOPUP_THEME_STONE,
    [MAPSEC_TOHJO_FALLS] = MAPPOPUP_THEME_STONE,
    [MAPSEC_SPROUT_TOWER] = MAPPOPUP_THEME_HISTORIC,
    [MAPSEC_SLOWPOKE_WELL] = MAPPOPUP_THEME_STONE2,
    [MAPSEC_BURNED_TOWER] = MAPPOPUP_THEME_HISTORIC,
    [MAPSEC_OLIVINE_LIGHTHOUSE] = MAPPOPUP_THEME_CITY,
    [MAPSEC_TIN_TOWER] = MAPPOPUP_THEME_HISTORIC,
    [MAPSEC_GRANITE_CAVE] = MAPPOPUP_THEME_STONE,
    [MAPSEC_MT_CHIMNEY] = MAPPOPUP_THEME_STONE,
    [MAPSEC_SAFARI_ZONE] = MAPPOPUP_THEME_JOHTO_ROUTE,
    [MAPSEC_BATTLE_FRONTIER] = MAPPOPUP_THEME_CHERRY,
    [MAPSEC_DRAGONS_DEN] = MAPPOPUP_THEME_HISTORIC,
    [MAPSEC_RUINS_OF_ALPH] = MAPPOPUP_THEME_CLIFF,
    [MAPSEC_ABANDONED_SHIP] = MAPPOPUP_THEME_WOOD,
    [MAPSEC_SS_AQUA] = MAPPOPUP_THEME_UNDERWATER,
    [MAPSEC_EMBEDDED_TOWER] = MAPPOPUP_THEME_HISTORIC,
    [MAPSEC_EMBEDDED_TOWER2] = MAPPOPUP_THEME_HISTORIC,
    [MAPSEC_MT_PYRE] = MAPPOPUP_THEME_STONE,
    [MAPSEC_AQUA_HIDEOUT_OLD] = MAPPOPUP_THEME_STONE,

    [MAPSEC_SEAFLOOR_CAVERN] = MAPPOPUP_THEME_STONE,
    [MAPSEC_UNDERWATER_SEAFLOOR_CAVERN] = MAPPOPUP_THEME_STONE2,
    [MAPSEC_VICTORY_ROAD] = MAPPOPUP_THEME_STONE,
    [MAPSEC_BIRTH_ISLAND] = MAPPOPUP_THEME_UNDERWATER,
    [MAPSEC_SOUTHERN_ISLAND] = MAPPOPUP_THEME_UNDERWATER,
    [MAPSEC_FARAWAY_ISLAND] = MAPPOPUP_THEME_UNDERWATER,
    [MAPSEC_SHOAL_CAVE] = MAPPOPUP_THEME_STONE, 

};

static const u8 sText_PyramidFloor1[] = _("PYRAMID FLOOR 1");
static const u8 sText_PyramidFloor2[] = _("PYRAMID FLOOR 2");
static const u8 sText_PyramidFloor3[] = _("PYRAMID FLOOR 3");
static const u8 sText_PyramidFloor4[] = _("PYRAMID FLOOR 4");
static const u8 sText_PyramidFloor5[] = _("PYRAMID FLOOR 5");
static const u8 sText_PyramidFloor6[] = _("PYRAMID FLOOR 6");
static const u8 sText_PyramidFloor7[] = _("PYRAMID FLOOR 7");
static const u8 sText_Pyramid[] = _("PYRAMID");

static const u8 * const sBattlePyramid_MapHeaderStrings[FRONTIER_STAGES_PER_CHALLENGE + 1] =
{
    sText_PyramidFloor1,
    sText_PyramidFloor2,
    sText_PyramidFloor3,
    sText_PyramidFloor4,
    sText_PyramidFloor5,
    sText_PyramidFloor6,
    sText_PyramidFloor7,
    sText_Pyramid,
};

static bool8 UNUSED StartMenu_ShowMapNamePopup(void)
{
    HideStartMenu();
    ShowMapNamePopup();
    return TRUE;
}

// States and data defines for Task_MapNamePopUpWindow
enum {
    STATE_SLIDE_IN,
    STATE_WAIT,
    STATE_SLIDE_OUT,
    STATE_UNUSED,
    STATE_ERASE,
    STATE_END,
    STATE_PRINT, // For some reason the first state is numerically last.
};

#define POPUP_OFFSCREEN_Y  40
#define POPUP_SLIDE_SPEED  2

#define tState         data[0]
#define tOnscreenTimer data[1]
#define tYOffset       data[2]
#define tIncomingPopUp data[3]
#define tPrintTimer    data[4]

void ShowMapNamePopup(void)
{
    if (FlagGet(FLAG_HIDE_MAP_NAME_POPUP) != TRUE)
    {
        if (!FuncIsActiveTask(Task_MapNamePopUpWindow))
        {
            // New pop up window
            sPopupTaskId = CreateTask(Task_MapNamePopUpWindow, 90);
            SetGpuReg(REG_OFFSET_BG0VOFS, POPUP_OFFSCREEN_Y);
            gTasks[sPopupTaskId].tState = STATE_PRINT;
            gTasks[sPopupTaskId].tYOffset = POPUP_OFFSCREEN_Y;
        }
        else
        {
            // There's already a pop up window running.
            // Hurry the old pop up offscreen so the new one can appear.
            if (gTasks[sPopupTaskId].tState != STATE_SLIDE_OUT)
                gTasks[sPopupTaskId].tState = STATE_SLIDE_OUT;
            gTasks[sPopupTaskId].tIncomingPopUp = TRUE;
        }
    }
}

static void Task_MapNamePopUpWindow(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->tState)
    {
    case STATE_PRINT:
        // Wait, then create and print the pop up window
        if (++task->tPrintTimer > 30)
        {
            task->tState = STATE_SLIDE_IN;
            task->tPrintTimer = 0;
            ShowMapNamePopUpWindow();
        }
        break;
    case STATE_SLIDE_IN:
        // Slide the window onscreen.
        task->tYOffset -= POPUP_SLIDE_SPEED;
        if (task->tYOffset <= 0 )
        {
            task->tYOffset = 0;
            task->tState = STATE_WAIT;
            gTasks[sPopupTaskId].data[1] = 0;
        }
        break;
    case STATE_WAIT:
        // Wait while the window is fully onscreen.
        if (++task->tOnscreenTimer > 120)
        {
            task->tOnscreenTimer = 0;
            task->tState = STATE_SLIDE_OUT;
        }
        break;
    case STATE_SLIDE_OUT:
        // Slide the window offscreen.
        task->tYOffset += POPUP_SLIDE_SPEED;
        if (task->tYOffset >= POPUP_OFFSCREEN_Y)
        {
            task->tYOffset = POPUP_OFFSCREEN_Y;
            if (task->tIncomingPopUp)
            {
                // A new pop up window is incoming,
                // return to the first state to show it.
                task->tState = STATE_PRINT;
                task->tPrintTimer = 0;
                task->tIncomingPopUp = FALSE;
            }
            else
            {
                task->tState = STATE_ERASE;
                return;
            }
        }
        break;
    case STATE_ERASE:
        ClearStdWindowAndFrame(GetMapNamePopUpWindowId(), TRUE);
        task->tState = STATE_END;
        break;
    case STATE_END:
        HideMapNamePopUpWindow();
        return;
    }
    SetGpuReg(REG_OFFSET_BG0VOFS, task->tYOffset);
}

void HideMapNamePopUpWindow(void)
{
    if (FuncIsActiveTask(Task_MapNamePopUpWindow))
    {
        ClearStdWindowAndFrame(GetMapNamePopUpWindowId(), TRUE);
        RemoveMapNamePopUpWindow();
        SetGpuReg_ForcedBlank(REG_OFFSET_BG0VOFS, 0);
        DestroyTask(sPopupTaskId);
    }
}

static void ShowMapNamePopUpWindow(void)
{
    u8 mapDisplayHeader[24];
    u8 *withoutPrefixPtr;
    u8 x;
    const u8 *mapDisplayHeaderSource;

    if (InBattlePyramid())
    {
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP)
        {
            withoutPrefixPtr = &(mapDisplayHeader[3]);
            mapDisplayHeaderSource = sBattlePyramid_MapHeaderStrings[FRONTIER_STAGES_PER_CHALLENGE];
        }
        else
        {
            withoutPrefixPtr = &(mapDisplayHeader[3]);
            mapDisplayHeaderSource = sBattlePyramid_MapHeaderStrings[gSaveBlock2Ptr->frontier.curChallengeBattleNum];
        }
        StringCopy(withoutPrefixPtr, mapDisplayHeaderSource);
    }
    else
    {
        withoutPrefixPtr = &(mapDisplayHeader[3]);
        GetMapName(withoutPrefixPtr, gMapHeader.regionMapSectionId, 0);
    }
    AddMapNamePopUpWindow();
    LoadMapNamePopUpWindowBg();
    x = GetStringCenterAlignXOffset(FONT_NARROW, withoutPrefixPtr, 80);
    mapDisplayHeader[0] = EXT_CTRL_CODE_BEGIN;
    mapDisplayHeader[1] = EXT_CTRL_CODE_HIGHLIGHT;
    mapDisplayHeader[2] = TEXT_COLOR_TRANSPARENT;
    AddTextPrinterParameterized(GetMapNamePopUpWindowId(), FONT_NARROW, mapDisplayHeader, x, 3, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(GetMapNamePopUpWindowId(), COPYWIN_FULL);
}

#define TILE_TOP_EDGE_START 0x21D
#define TILE_TOP_EDGE_END   0x228
#define TILE_LEFT_EDGE_TOP  0x229
#define TILE_RIGHT_EDGE_TOP 0x22A
#define TILE_LEFT_EDGE_MID  0x22B
#define TILE_RIGHT_EDGE_MID 0x22C
#define TILE_LEFT_EDGE_BOT  0x22D
#define TILE_RIGHT_EDGE_BOT 0x22E
#define TILE_BOT_EDGE_START 0x22F
#define TILE_BOT_EDGE_END   0x23A

static void DrawMapNamePopUpFrame(u8 bg, u8 x, u8 y, u8 deltaX, u8 deltaY, u8 unused)
{
    s32 i;

    // Draw top edge
    for (i = 0; i < 1 + TILE_TOP_EDGE_END - TILE_TOP_EDGE_START; i++)
        FillBgTilemapBufferRect(bg, TILE_TOP_EDGE_START + i, i - 1 + x, y - 1, 1, 1, 14);

    // Draw sides
    FillBgTilemapBufferRect(bg, TILE_LEFT_EDGE_TOP,       x - 1,     y, 1, 1, 14);
    FillBgTilemapBufferRect(bg, TILE_RIGHT_EDGE_TOP, deltaX + x,     y, 1, 1, 14);
    FillBgTilemapBufferRect(bg, TILE_LEFT_EDGE_MID,       x - 1, y + 1, 1, 1, 14);
    FillBgTilemapBufferRect(bg, TILE_RIGHT_EDGE_MID, deltaX + x, y + 1, 1, 1, 14);
    FillBgTilemapBufferRect(bg, TILE_LEFT_EDGE_BOT,       x - 1, y + 2, 1, 1, 14);
    FillBgTilemapBufferRect(bg, TILE_RIGHT_EDGE_BOT, deltaX + x, y + 2, 1, 1, 14);

    // Draw bottom edge
    for (i = 0; i < 1 + TILE_BOT_EDGE_END - TILE_BOT_EDGE_START; i++)
        FillBgTilemapBufferRect(bg, TILE_BOT_EDGE_START + i, i - 1 + x, y + deltaY, 1, 1, 14);
}

static void LoadMapNamePopUpWindowBg(void)
{
    u8 popUpThemeId;
    u8 popupWindowId = GetMapNamePopUpWindowId();
    u16 regionMapSectionId = gMapHeader.regionMapSectionId;
 
    if (regionMapSectionId >= KANTO_MAPSEC_START)
    {
        if (regionMapSectionId > KANTO_MAPSEC_END)
            regionMapSectionId -= KANTO_MAPSEC_COUNT;
        else
            regionMapSectionId = 0; // Discard kanto region sections;
    }
    popUpThemeId = sMapSectionToThemeId[regionMapSectionId];

    LoadBgTiles(GetWindowAttribute(popupWindowId, WINDOW_BG), sMapPopUp_OutlineTable[popUpThemeId], 0x400, 0x21D);
    CallWindowFunction(popupWindowId, DrawMapNamePopUpFrame);
    PutWindowTilemap(popupWindowId);
    if (gMapHeader.weather == WEATHER_UNDERWATER_BUBBLES)
        LoadPalette(&sMapPopUp_Palette_Underwater, BG_PLTT_ID(14), sizeof(sMapPopUp_Palette_Underwater));
    else
        LoadPalette(sMapPopUp_PaletteTable[popUpThemeId], BG_PLTT_ID(14), sizeof(sMapPopUp_PaletteTable[0]));
    BlitBitmapToWindow(popupWindowId, sMapPopUp_Table[popUpThemeId], 0, 0, 80, 24);
}
