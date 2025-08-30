#include "global.h"
#include "main.h"
#include "text.h"
#include "menu.h"
#include "malloc.h"
#include "gpu_regs.h"
#include "palette.h"
#include "party_menu.h"
#include "trig.h"
#include "overworld.h"
#include "event_data.h"
#include "secret_base.h"
#include "string_util.h"
#include "international_string_util.h"
#include "strings.h"
#include "text_window.h"
#include "constants/songs.h"
#include "m4a.h"
#include "field_effect.h"
#include "field_specials.h"
#include "fldeff.h"
#include "region_map.h"
#include "constants/region_map_sections.h"
#include "heal_location.h"
#include "constants/field_specials.h"
#include "constants/heal_locations.h"
#include "constants/map_types.h"
#include "constants/rgb.h"
#include "constants/weather.h"
#include "constants/flags.h"

/*
 *  This file handles region maps generally, and the map used when selecting a fly destination.
 *  Specific features of other region map uses are handled elsewhere
 *
 *  For the region map in the pokenav, see pokenav_region_map.c
 *  For the region map in the pokedex, see pokdex_area_screen.c/pokedex_area_region_map.c
 *  For the region map that can be viewed on the wall of pokemon centers, see field_region_map.c
 *
 */

#define MAP_WIDTH 28
#define MAP_HEIGHT 15
#define MAPCURSOR_X_MIN 1
#define MAPCURSOR_Y_MIN 2
#define MAPCURSOR_X_MAX (MAPCURSOR_X_MIN + MAP_WIDTH - 1)
#define MAPCURSOR_Y_MAX (MAPCURSOR_Y_MIN + MAP_HEIGHT - 1)

#define FLYDESTICON_RED_OUTLINE 6


#include "data/region_map/region_map_entries.h"        // defines gRegionMapEntries (JK)

// ✅ each of these must DEFINE its own array:
//    sRegionMap_MapSectionLayout_JK[15][28]
//    sRegionMap_MapSectionLayout_Johto[15][28]
#include "data/region_map/region_map_layout.h"
#include "data/region_map/region_map_layout_johto.h"

const struct RegionMapLocation gRegionMapEntries_Johto[] = {
    [MAPSEC_VIOLET_CITY] = { 7, 5, 1, 1, sMapName_VIOLET_CITY},
    [MAPSEC_AZALEA_TOWN] = { 6, 12, 1, 1, sMapName_AZALEA_TOWN},
    [MAPSEC_GOLDENROD_CITY] = { 5, 7, 1, 2, sMapName_GOLDENROD_CITY},
    [MAPSEC_ECRUTEAK_CITY] = { 6, 3, 1, 1, sMapName_ECRUTEAK_CITY},
    [MAPSEC_OLIVINE_CITY] = { 3, 6, 1, 1, sMapName_OLIVINE_CITY},
    [MAPSEC_CIANWOOD_CITY] = { 1, 9, 1, 1, sMapName_CIANWOOD_CITY},
    [MAPSEC_SAFARI_ZONE_GATE] = { 0, 7, 1, 1, sMapName_SAFARI_ZONE_GATE},
    [MAPSEC_MAHOGANY_TOWN] = { 9, 3, 1, 1, sMapName_MAHOGANY_TOWN},
    [MAPSEC_BLACKTHORN_CITY] = { 12, 3, 1, 1, sMapName_BLACKTHORN_CITY},
    [MAPSEC_CHERRYGROVE_CITY] = { 9, 11, 1, 1, sMapName_CHERRYGROVE_CITY},
    [MAPSEC_INDIGO_PLATEAU] = { 16, 2, 1, 2, sMapName_INDIGO_PLATEAU},
    [MAPSEC_ROUTE_26] = { 16, 7, 1, 4, sMapName_ROUTE_26},
    [MAPSEC_ROUTE_27] = { 14, 11, 3, 1, sMapName_ROUTE_27},
    [MAPSEC_ROUTE_28] = { 15, 7, 1, 1, sMapName_ROUTE_28},
    [MAPSEC_ROUTE_29] = { 10, 11, 3, 1, sMapName_ROUTE_29},
    [MAPSEC_ROUTE_30] = { 9, 6, 1, 5, sMapName_ROUTE_30},
    [MAPSEC_ROUTE_31] = { 8, 5, 2, 1, sMapName_ROUTE_31},
    [MAPSEC_ROUTE_32] = { 7, 6, 1, 5, sMapName_ROUTE_32},
    [MAPSEC_ROUTE_33] = { 7, 12, 1, 1, sMapName_ROUTE_33},
    [MAPSEC_ROUTE_34] = { 5, 9, 1, 2, sMapName_ROUTE_34},
    [MAPSEC_ROUTE_35] = { 5, 6, 1, 1, sMapName_ROUTE_35},
    [MAPSEC_ROUTE_36] = { 6, 5, 1, 1, sMapName_ROUTE_36},
    [MAPSEC_ROUTE_37] = { 6, 4, 1, 1, sMapName_ROUTE_37},
    [MAPSEC_ROUTE_38] = { 4, 3, 2, 1, sMapName_ROUTE_38},
    [MAPSEC_ROUTE_39] = { 3, 3, 1, 3, sMapName_ROUTE_39},
    [MAPSEC_ROUTE_40] = { 2, 6, 1, 3, sMapName_ROUTE_40},
    [MAPSEC_ROUTE_41] = { 2, 9, 1, 1, sMapName_ROUTE_41},
    [MAPSEC_ROUTE_42] = { 7, 3, 2, 1, sMapName_ROUTE_42},
    [MAPSEC_ROUTE_43] = { 9, 2, 1, 1, sMapName_ROUTE_43},
    [MAPSEC_ROUTE_44] = { 10, 3, 2, 1, sMapName_ROUTE_44},
    [MAPSEC_ROUTE_45] = { 12, 4, 1, 5, sMapName_ROUTE_45},
    [MAPSEC_ROUTE_46] = { 11, 8, 1, 3, sMapName_ROUTE_46},
    [MAPSEC_ROUTE_47] = { 0, 9, 1, 1, sMapName_ROUTE_47},
    [MAPSEC_ROUTE_48] = { 0, 8, 1, 1, sMapName_ROUTE_48},
    [MAPSEC_SAFARI_ZONE] = { 0, 6, 1, 1, sMapName_SAFARI_ZONE},
    [MAPSEC_VICTORY_ROAD] = { 16, 4, 1, 4, sMapName_VICTORY_ROAD},
    [MAPSEC_PALLET_TOWN] = { 19, 11, 1, 1, sMapName_PALLET_TOWN},
    [MAPSEC_VIRIDIAN_CITY] = { 19, 7, 1, 1, sMapName_VIRIDIAN_CITY},
    [MAPSEC_PEWTER_CITY] = { 19, 2, 1, 1, sMapName_PEWTER_CITY},
    [MAPSEC_CERULEAN_CITY] = { 24, 2, 1, 1, sMapName_CERULEAN_CITY},
    [MAPSEC_LAVENDER_TOWN] = { 27, 5, 1, 1, sMapName_LAVENDER_TOWN},
    [MAPSEC_VERMILION_CITY] = { 24, 7, 1, 1, sMapName_VERMILION_CITY},
    [MAPSEC_CELADON_CITY] = { 22, 5, 1, 1, sMapName_CELADON_CITY},
    [MAPSEC_FUCHSIA_CITY] = { 24, 11, 1, 1, sMapName_FUCHSIA_CITY},
    [MAPSEC_SOUTHERN_ISLAND] = { 9, 14, 1, 1, sMapName_SOUTHERN_ISLAND},
    [MAPSEC_FARAWAY_ISLAND] = { 9, 14, 1, 1, sMapName_FARAWAY_ISLAND},
    [MAPSEC_BIRTH_ISLAND] = { 9, 14, 1, 1, sMapName_BIRTH_ISLAND},
    [MAPSEC_CINNABAR_ISLAND] = { 19, 13, 1, 1, sMapName_CINNABAR_ISLAND},
    [MAPSEC_SAFFRON_CITY] = { 24, 5, 1, 1, sMapName_SAFFRON_CITY},
    [MAPSEC_ROUTE_10_POKECENTER] = { 27, 3, 1, 1, sMapName_ROUTE_10},
    [MAPSEC_ROUTE_1] = { 19, 8, 1, 3, sMapName_ROUTE_1},
    [MAPSEC_ROUTE_2] = { 19, 3, 1, 4, sMapName_ROUTE_2},
    [MAPSEC_ROUTE_3] = { 20, 2, 2, 1, sMapName_ROUTE_3},
    [MAPSEC_ROUTE_4] = { 22, 2, 2, 1, sMapName_ROUTE_4},
    [MAPSEC_ROUTE_5] = { 24, 3, 1, 2, sMapName_ROUTE_5},
    [MAPSEC_ROUTE_6] = { 24, 6, 1, 1, sMapName_ROUTE_6},
    [MAPSEC_ROUTE_7] = { 23, 5, 1, 1, sMapName_ROUTE_7},
    [MAPSEC_ROUTE_8] = { 25, 5, 2, 1, sMapName_ROUTE_8},
    [MAPSEC_ROUTE_9] = { 25, 2, 3, 1, sMapName_ROUTE_9},
    [MAPSEC_ROUTE_10] = { 27, 3, 1, 1, sMapName_ROUTE_10},
    [MAPSEC_ROUTE_11] = { 25, 5, 2, 1, sMapName_ROUTE_11},
    [MAPSEC_ROUTE_12] = { 27, 6, 1, 4, sMapName_ROUTE_12},
    [MAPSEC_ROUTE_13] = { 26, 10, 2, 1, sMapName_ROUTE_13},
    [MAPSEC_ROUTE_14] = { 26, 11, 1, 1, sMapName_ROUTE_14},
    [MAPSEC_ROUTE_15] = { 25, 11, 1, 1, sMapName_ROUTE_15},
    [MAPSEC_ROUTE_16] = { 21, 5, 1, 1, sMapName_ROUTE_16},
    [MAPSEC_ROUTE_17] = { 21, 6, 1, 6, sMapName_ROUTE_17},
    [MAPSEC_ROUTE_18] = { 22, 11, 2, 1, sMapName_ROUTE_18},
    [MAPSEC_ROUTE_19] = { 22, 12, 3, 2, sMapName_ROUTE_19},
    [MAPSEC_ROUTE_20] = { 20, 13, 2, 1, sMapName_ROUTE_20},
    [MAPSEC_ROUTE_21] = { 19, 12, 1, 1, sMapName_ROUTE_21},
    [MAPSEC_ROUTE_22] = { 17, 7, 2, 1, sMapName_ROUTE_22},
    [MAPSEC_ROUTE_24] = { 24, 0, 1, 2, sMapName_ROUTE_24},
    [MAPSEC_ROUTE_25] = { 25, 0, 1, 1, sMapName_ROUTE_25},
    [MAPSEC_VIRIDIAN_FOREST] = { 19, 4, 1, 2, sMapName_VIRIDIAN_FOREST},
    [MAPSEC_MT_MOON] = { 21, 2, 2, 1, sMapName_MT__MOON},
    [MAPSEC_S_S_ANNE] = { 13, 15, 1, 1, sMapName_S_S__ANNE},
    [MAPSEC_UNDERGROUND_PATH_2] = { 24, 5, 1, 1, sMapName_UNDERGROUND_PATH},
    [MAPSEC_DIGLETTS_CAVE] = { 20, 3, 6, 4, sMapName_DIGLETT_S_CAVE},
    [MAPSEC_ROCKET_HIDEOUT] = { 9, 3, 1, 1, sMapName_ROCKET_HIDEOUT},
    [MAPSEC_SILPH_CO] = { 24, 5, 1, 1, sMapName_SILPH_CO_},
    [MAPSEC_ROCK_TUNNEL] = { 27, 3, 1, 1, sMapName_ROCK_TUNNEL},
    [MAPSEC_SEAFOAM_ISLANDS] = { 22, 13, 1, 1, sMapName_SEAFOAM_ISLANDS},
    [MAPSEC_POKEMON_TOWER] = { 27, 5, 1, 1, sMapName_POK__MON_TOWER},
    [MAPSEC_CERULEAN_CAVE] = { 23, 1, 1, 1, sMapName_CERULEAN_CAVE},
    [MAPSEC_POWER_PLANT] = { 27, 3, 1, 1, sMapName_POWER_PLANT},
    [MAPSEC_NEW_BARK_TOWN] = { 13, 11, 1, 1, sMapName_NEW_BARK_TOWN},
    [MAPSEC_INDIGO_PLATEAU2] = { 16, 2, 1, 2, sMapName_},
    [MAPSEC_UNDERGROUND_PATH] = { 24, 5, 1, 1, sMapName_},
    [MAPSEC_DARK_CAVE] = { 10, 5, 1, 1, sMapName_DARK_CAVE},
    [MAPSEC_UNION_CAVE] = { 7, 11, 1, 2, sMapName_UNION_CAVE},
    [MAPSEC_ILEX_FOREST] = { 5, 11, 1, 2, sMapName_ILEX_FOREST},
    [MAPSEC_NATIONAL_PARK] = { 5, 5, 1, 1, sMapName_NATIONAL_PARK},
    [MAPSEC_WHIRL_ISLANDS] = { 2, 9, 1, 1, sMapName_WHIRL_ISLANDS},
    [MAPSEC_CLIFF_CAVE] = { 0, 9, 1, 1, sMapName_CLIFF_CAVE},
    [MAPSEC_MT_MORTAR] = { 10, 3, 1, 1, sMapName_MT_MORTAR},
    [MAPSEC_LAKE_OF_RAGE] = { 9, 1, 1, 1, sMapName_LAKE_OF_RAGE},
    [MAPSEC_ICE_PATH] = { 11, 2, 2, 1, sMapName_ICE_PATH},
    [MAPSEC_MT_SILVER] = { 14, 7, 1, 1, sMapName_MT__SILVER},
    [MAPSEC_TOHJO_FALLS] = { 14, 10, 1, 1, sMapName_TOHJO_FALLS},
    [MAPSEC_SPROUT_TOWER] = { 7, 5, 1, 1, sMapName_SPROUT_TOWER},
    [MAPSEC_SLOWPOKE_WELL] = { 6, 12, 1, 1, sMapName_SLOWPOKE_WELL},
    [MAPSEC_BURNED_TOWER] = { 6, 3, 1, 1, sMapName_BURNED_TOWER},
    [MAPSEC_TIN_TOWER] = { 6, 2, 1, 1, sMapName_TIN_TOWER},
    [MAPSEC_DRAGONS_DEN] = { 12, 2, 1, 1, sMapName_Dragon_s_Den},
    [MAPSEC_RUINS_OF_ALPH] = { 6, 6, 1, 1, sMapName_Ruins_of_Alph},
    [MAPSEC_SS_AQUA] = { 9, 14, 10, 1, sMapName_S_S__AQUA},
    [MAPSEC_EMBEDDED_TOWER] = { 1, 10, 1, 1, sMapName_EMBEDDED_TOWER},
    [MAPSEC_OLIVINE_LIGHTHOUSE] = { 3, 6, 1, 1, sMapName_LIGHTHOUSE},
    [MAPSEC_BATTLE_FRONTIER] = { 1, 17, 1, 1, sMapName_},
    [MAPSEC_FORTREE_CITY] = { 1, 17, 1, 1, sMapName_},
    [MAPSEC_LILYCOVE_CITY] = { 2, 17, 1, 1, sMapName_},
    [MAPSEC_MOSSDEEP_CITY] = { 3, 17, 1, 1, sMapName_},
    [MAPSEC_SOOTOPOLIS_CITY] = { 3, 17, 1, 1, sMapName_},
};


enum {
    TAG_CURSOR,
    TAG_PLAYER_ICON,
    TAG_FLY_ICON,
};

struct MultiNameFlyDest
{
    const u8 *const *name;
    u16 mapSecId;
    u16 flag;
};

static EWRAM_DATA struct RegionMap *sRegionMap = NULL;

static EWRAM_DATA struct {
    void (*callback)(void);
    u16 state;
    u16 mapSecId;
    struct RegionMap regionMap;
    u8 tileBuffer[0x1c0];
    u8 nameBuffer[0x26]; // never read
    bool8 choseFlyLocation;
} *sFlyMap = NULL;

static bool32 sDrawFlyDestTextWindow;

static u8 ProcessRegionMapInput_Full(void);
static u8 MoveRegionMapCursor_Full(void);
static u8 ProcessRegionMapInput_Zoomed(void);
static u8 MoveRegionMapCursor_Zoomed(void);
static void CalcZoomScrollParams(s16 scrollX, s16 scrollY, s16 c, s16 d, u16 e, u16 f, u8 rotation);
static u16 GetMapSecIdAt(u16 x, u16 y);
static void RegionMap_SetBG2XAndBG2Y(s16 x, s16 y);
static void InitMapBasedOnPlayerLocation(void);
static void RegionMap_InitializeStateBasedOnSSTidalLocation(void);
static u8 GetMapsecType(u16 mapSecId);
static u16 CorrectSpecialMapSecId_Internal(u16 mapSecId);
static u16 GetTerraOrMarineCaveMapSecId(void);
static void GetMarineCaveCoords(u16 *x, u16 *y);
static bool32 IsPlayerInAquaHideout(u8 mapSecId);
static void GetPositionOfCursorWithinMapSec(void);
static bool8 RegionMap_IsMapSecIdInNextRow(u16 y);
static void SpriteCB_CursorMapFull(struct Sprite *sprite);
static void FreeRegionMapCursorSprite(void);
static void HideRegionMapPlayerIcon(void);
static void UnhideRegionMapPlayerIcon(void);
static void SpriteCB_PlayerIconMapZoomed(struct Sprite *sprite);
static void SpriteCB_PlayerIconMapFull(struct Sprite *sprite);
static void SpriteCB_PlayerIcon(struct Sprite *sprite);
static void VBlankCB_FlyMap(void);
static void CB2_FlyMap(void);
static void SetFlyMapCallback(void callback(void));
static void DrawFlyDestTextWindow(void);
static void LoadFlyDestIcons(void);
static void CreateFlyDestIcons(void);
static void TryCreateRedOutlineFlyDestIcons(void);
static void SpriteCB_FlyDestIcon(struct Sprite *sprite);
static void CB_FadeInFlyMap(void);
static void CB_HandleFlyMapInput(void);
static void CB_ExitFlyMap(void);

static const u16 sRegionMapCursorPal[] = INCBIN_U16("graphics/pokenav/region_map/cursor.gbapal");
static const u32 sRegionMapCursorSmallGfxLZ[] = INCBIN_U32("graphics/pokenav/region_map/cursor_small.4bpp.lz");
static const u32 sRegionMapCursorLargeGfxLZ[] = INCBIN_U32("graphics/pokenav/region_map/cursor_large.4bpp.lz");
static const u16 sRegionMapBg_Pal[] = INCBIN_U16("graphics/pokenav/region_map/map.gbapal");
static const u32 sRegionMapBg_GfxLZ[] = INCBIN_U32("graphics/pokenav/region_map/map.8bpp.lz");
static const u32 sRegionMapBg_TilemapLZ[] = INCBIN_U32("graphics/pokenav/region_map/map.bin.lz");
static const u16 sRegionMapPlayerIcon_BrendanPal[] = INCBIN_U16("graphics/pokenav/region_map/brendan_icon.gbapal");
static const u8 sRegionMapPlayerIcon_BrendanGfx[] = INCBIN_U8("graphics/pokenav/region_map/brendan_icon.4bpp");
static const u16 sRegionMapPlayerIcon_MayPal[] = INCBIN_U16("graphics/pokenav/region_map/may_icon.gbapal");
static const u8 sRegionMapPlayerIcon_MayGfx[] = INCBIN_U8("graphics/pokenav/region_map/may_icon.4bpp");

//HnS
// Combined Johto+Kanto (current art)
static const u16 sRegionMapBg_Pal_JK[]      = INCBIN_U16("graphics/pokenav/region_map/map.gbapal");
static const u32 sRegionMapBg_GfxLZ_JK[]    = INCBIN_U32("graphics/pokenav/region_map/map.8bpp.lz");
static const u32 sRegionMapBg_TilemapLZ_JK[] = INCBIN_U32("graphics/pokenav/region_map/map.bin.lz");

// Johto-only (TEMP: reuse combined; swap these paths when your solo map is ready)
static const u16 sRegionMapBg_Pal_Johto[]      = INCBIN_U16("graphics/pokenav/region_map/map.gbapal");
static const u32 sRegionMapBg_GfxLZ_Johto[]    = INCBIN_U32("graphics/pokenav/region_map/johtomap.8bpp.lz");
static const u32 sRegionMapBg_TilemapLZ_Johto[] = INCBIN_U32("graphics/pokenav/region_map/johtomap.bin.lz");

//HnS
// Variant selection
enum MapVariant { MAPVAR_JOHTO, MAPVAR_JOHTO_KANTO };
static u8 sMapVariant;


// Active pointers that all callers use
static const u8  (*sActiveRegionLayout)[MAP_WIDTH];
static const struct RegionMapLocation *sActiveEntries;
static const u16 *sActiveMapPal;
static const u32 *sActiveMapGfxLZ;
static const u32 *sActiveMapTilemapLZ;

static void GetMapSecRectFromLayout(u16 mapSecId, u16 *x, u16 *y, u16 *width, u16 *height)
{
    u16 minx = MAP_WIDTH,  miny = MAP_HEIGHT;
    u16 maxx = 0,          maxy = 0;
    bool32 found = FALSE;

    for (u16 yy = 0; yy < MAP_HEIGHT; yy++)
    {
        for (u16 xx = 0; xx < MAP_WIDTH; xx++)
        {
            if (sActiveRegionLayout[yy][xx] == mapSecId)
            {
                found = TRUE;
                if (xx < minx) minx = xx;
                if (yy < miny) miny = yy;
                if (xx > maxx) maxx = xx;
                if (yy > maxy) maxy = yy;
            }
        }
    }

    if (found)
    {
        *x = minx;
        *y = miny;
        *width  = (maxx - minx) + 1;
        *height = (maxy - miny) + 1;
    }
    else
    {
        // Fallback to entries table if the section isn't present on this layout.
        const struct RegionMapLocation *tbl = sActiveEntries ? sActiveEntries : gRegionMapEntries;
        *x = tbl[mapSecId].x;
        *y = tbl[mapSecId].y;
        *width  = tbl[mapSecId].width;
        *height = tbl[mapSecId].height;
    }
}

//HnS
static void ChooseMapVariant(void)
{
    if (FlagGet(FLAG_VISITED_KANTO)) {
        // Combined JK
        sActiveEntries      = gRegionMapEntries;              // combined entries
        sActiveRegionLayout = sRegionMap_MapSectionLayout; // combined grid
        sActiveMapGfxLZ     = sRegionMapBg_GfxLZ_JK;
        sActiveMapTilemapLZ = sRegionMapBg_TilemapLZ_JK;
        sActiveMapPal       = sRegionMapBg_Pal_JK;
    } else {
        // Johto-only
        sActiveEntries      = gRegionMapEntries_Johto;        // johto entries
        sActiveRegionLayout = sRegionMap_MapSectionLayout_Johto;
        sActiveMapGfxLZ     = sRegionMapBg_GfxLZ_Johto;
        sActiveMapTilemapLZ = sRegionMapBg_TilemapLZ_Johto;
        sActiveMapPal       = sRegionMapBg_Pal_Johto;         // or shared, your call
    }
}


static inline void RegionMapEnsureVariantSelected(void)
{
    // If you prefer, you can just call ChooseMapVariant() unconditionally here;
    // it’s cheap and covers cases where the flag changes mid-session.
    if (sActiveEntries == NULL || sActiveRegionLayout == NULL)
        ChooseMapVariant();
}

// Returns the entries table that matches the ART currently selected.
static inline const struct RegionMapLocation *ActiveEntriesByArt(void)
{
    // If the active layout is the combined JK grid, use combined entries;
    // otherwise use the Johto-only entries.
    return (sActiveRegionLayout == sRegionMap_MapSectionLayout)
         ? gRegionMapEntries
         : gRegionMapEntries_Johto;
}


struct FlyDest { u16 flag; u16 mapSec; };

// Fill with YOUR exact flags+mapsecs (examples shown)
static const struct FlyDest sFlyDests_Johto[] = {
    { FLAG_VISITED_NEWBARK_TOWN,   MAPSEC_NEW_BARK_TOWN },
    { FLAG_VISITED_CHERRYGROVE_CITY,    MAPSEC_CHERRYGROVE_CITY },
    { FLAG_VISITED_VIOLET_CITY,         MAPSEC_VIOLET_CITY },
    { FLAG_VISITED_AZALEA_TOWN,         MAPSEC_AZALEA_TOWN },
    { FLAG_VISITED_GOLDENROD_CITY,         MAPSEC_GOLDENROD_CITY },
    { FLAG_VISITED_ECRUTEAK_CITY,         MAPSEC_ECRUTEAK_CITY },
    { FLAG_VISITED_OLIVINE_CITY,         MAPSEC_OLIVINE_CITY },
    { FLAG_VISITED_CIANWOOD_CITY,         MAPSEC_CIANWOOD_CITY },
    { FLAG_VISITED_SAFARI_ZONE_GATE,         MAPSEC_SAFARI_ZONE_GATE },
    { FLAG_VISITED_MAHOGANY_TOWN,         MAPSEC_MAHOGANY_TOWN },
    { FLAG_VISITED_LAKE_OF_RAGE,         MAPSEC_LAKE_OF_RAGE },
    { FLAG_VISITED_BLACKTHORN_CITY,         MAPSEC_BLACKTHORN_CITY },
    { 0xFFFF, MAPSEC_NONE }, // terminator
};

static const struct FlyDest sFlyDests_JK[] = {
    { FLAG_VISITED_NEWBARK_TOWN,   MAPSEC_NEW_BARK_TOWN },
    { FLAG_VISITED_CHERRYGROVE_CITY,    MAPSEC_CHERRYGROVE_CITY },
    { FLAG_VISITED_VIOLET_CITY,         MAPSEC_VIOLET_CITY },
    { FLAG_VISITED_AZALEA_TOWN,         MAPSEC_AZALEA_TOWN },
    { FLAG_VISITED_GOLDENROD_CITY,         MAPSEC_GOLDENROD_CITY },
    { FLAG_VISITED_ECRUTEAK_CITY,         MAPSEC_ECRUTEAK_CITY },
    { FLAG_VISITED_OLIVINE_CITY,         MAPSEC_OLIVINE_CITY },
    { FLAG_VISITED_CIANWOOD_CITY,         MAPSEC_CIANWOOD_CITY },
    { FLAG_VISITED_SAFARI_ZONE_GATE,         MAPSEC_SAFARI_ZONE_GATE },
    { FLAG_VISITED_MAHOGANY_TOWN,         MAPSEC_MAHOGANY_TOWN },
    { FLAG_VISITED_LAKE_OF_RAGE,         MAPSEC_LAKE_OF_RAGE },
    { FLAG_VISITED_BLACKTHORN_CITY,         MAPSEC_BLACKTHORN_CITY },
    { FLAG_VISITED_PALLET_TOWN,         MAPSEC_PALLET_TOWN },
    { FLAG_VISITED_VIRIDIAN_CITY,         MAPSEC_VIRIDIAN_CITY },
    { FLAG_VISITED_PEWTER_CITY,         MAPSEC_PEWTER_CITY },
    { FLAG_VISITED_CERULEAN_CITY,         MAPSEC_CERULEAN_CITY },
    { FLAG_VISITED_VERMILION_CITY,         MAPSEC_VERMILION_CITY },
    { FLAG_VISITED_LAVENDER_TOWN,         MAPSEC_LAVENDER_TOWN },
    { FLAG_VISITED_CELADON_CITY,         MAPSEC_CELADON_CITY },
    { FLAG_VISITED_SAFFRON_CITY,         MAPSEC_SAFFRON_CITY },
    { FLAG_VISITED_FUCHSIA_CITY,         MAPSEC_FUCHSIA_CITY },
    { FLAG_VISITED_CINNABAR_ISLAND,         MAPSEC_CINNABAR_ISLAND },
    { FLAG_VISITED_INDIGO_PLATEAU,         MAPSEC_INDIGO_PLATEAU },
    { FLAG_VISITED_MT_SILVER,         MAPSEC_MT_SILVER },
    { 0xFFFF, MAPSEC_NONE }, // terminator
};

static const u16 sRegionMap_SpecialPlaceLocations[][2] =
{
    {MAPSEC_UNDERWATER_105,             MAPSEC_ROUTE_30},
    {MAPSEC_SPROUT_TOWER,             MAPSEC_DARK_CAVE},
    #ifdef BUGFIX
    {MAPSEC_UNDERWATER_125,             MAPSEC_UNION_CAVE},
    #else
    {MAPSEC_UNDERWATER_125,             MAPSEC_CLIFF_CAVE}, // BUG: Map will incorrectly display the name of Route 129 when diving on Route 125 (for Marine Cave only)
    #endif
    {MAPSEC_SLOWPOKE_WELL,             MAPSEC_ILEX_FOREST},
    {MAPSEC_BURNED_TOWER,             MAPSEC_NATIONAL_PARK},
    {MAPSEC_OLIVINE_LIGHTHOUSE,             MAPSEC_WHIRL_ISLANDS},
    {MAPSEC_UNDERWATER_129,             MAPSEC_CLIFF_CAVE},
    {MAPSEC_TIN_TOWER,      MAPSEC_SOOTOPOLIS_CITY},
    {MAPSEC_UNDERWATER_SEAFLOOR_CAVERN, MAPSEC_WHIRL_ISLANDS},
    {MAPSEC_AQUA_HIDEOUT,               MAPSEC_LILYCOVE_CITY},
    {MAPSEC_AQUA_HIDEOUT_OLD,           MAPSEC_LILYCOVE_CITY},
    {MAPSEC_MAGMA_HIDEOUT,              MAPSEC_ROUTE_37},
    {MAPSEC_UNDERWATER_SEALED_CHAMBER,  MAPSEC_TOHJO_FALLS},
    {MAPSEC_DRAGONS_DEN,            MAPSEC_ROUTE_29},
    {MAPSEC_JAGGED_PASS,                MAPSEC_ROUTE_37},
    {MAPSEC_MT_PYRE,                    MAPSEC_ROUTE_47},
    {MAPSEC_SKY_PILLAR,                 MAPSEC_LAKE_OF_RAGE},
    {MAPSEC_MIRAGE_TOWER,               MAPSEC_ROUTE_36},
    {MAPSEC_TRAINER_HILL,               MAPSEC_ROUTE_36},
    {MAPSEC_DESERT_UNDERPASS,           MAPSEC_ROUTE_39},
    {MAPSEC_ALTERING_CAVE,              MAPSEC_ROUTE_28},
    {MAPSEC_ARTISAN_CAVE,               MAPSEC_ROUTE_28},
    {MAPSEC_ABANDONED_SHIP,             MAPSEC_ROUTE_33},
    {MAPSEC_NONE,                       MAPSEC_NONE}
};

static const u16 sMarineCaveMapSecIds[] =
{
    MAPSEC_MARINE_CAVE,
    MAPSEC_UNDERWATER_MARINE_CAVE,
    MAPSEC_UNDERWATER_MARINE_CAVE
};

static const u16 sTerraOrMarineCaveMapSecIds[ABNORMAL_WEATHER_LOCATIONS] =
{
    [ABNORMAL_WEATHER_ROUTE_114_NORTH - 1] = MAPSEC_ROUTE_39,
    [ABNORMAL_WEATHER_ROUTE_114_SOUTH - 1] = MAPSEC_ROUTE_39,
    [ABNORMAL_WEATHER_ROUTE_115_WEST  - 1] = MAPSEC_ROUTE_40,
    [ABNORMAL_WEATHER_ROUTE_115_EAST  - 1] = MAPSEC_ROUTE_40,
    [ABNORMAL_WEATHER_ROUTE_116_NORTH - 1] = MAPSEC_ROUTE_41,
    [ABNORMAL_WEATHER_ROUTE_116_SOUTH - 1] = MAPSEC_ROUTE_41,
    [ABNORMAL_WEATHER_ROUTE_118_EAST  - 1] = MAPSEC_ROUTE_43,
    [ABNORMAL_WEATHER_ROUTE_118_WEST  - 1] = MAPSEC_ROUTE_43,
    [ABNORMAL_WEATHER_ROUTE_105_NORTH - 1] = MAPSEC_ROUTE_30,
    [ABNORMAL_WEATHER_ROUTE_105_SOUTH - 1] = MAPSEC_ROUTE_30,
    [ABNORMAL_WEATHER_ROUTE_125_WEST  - 1] = MAPSEC_UNION_CAVE,
    [ABNORMAL_WEATHER_ROUTE_125_EAST  - 1] = MAPSEC_UNION_CAVE,
    [ABNORMAL_WEATHER_ROUTE_127_NORTH - 1] = MAPSEC_NATIONAL_PARK,
    [ABNORMAL_WEATHER_ROUTE_127_SOUTH - 1] = MAPSEC_NATIONAL_PARK,
    [ABNORMAL_WEATHER_ROUTE_129_WEST  - 1] = MAPSEC_CLIFF_CAVE,
    [ABNORMAL_WEATHER_ROUTE_129_EAST  - 1] = MAPSEC_CLIFF_CAVE
};

#define MARINE_CAVE_COORD(location)(ABNORMAL_WEATHER_##location - MARINE_CAVE_LOCATIONS_START)

static const struct UCoords16 sMarineCaveLocationCoords[MARINE_CAVE_LOCATIONS] =
{
    [MARINE_CAVE_COORD(ROUTE_105_NORTH)] = {0, 10},
    [MARINE_CAVE_COORD(ROUTE_105_SOUTH)] = {0, 12},
    [MARINE_CAVE_COORD(ROUTE_125_WEST)]  = {24, 3},
    [MARINE_CAVE_COORD(ROUTE_125_EAST)]  = {25, 4},
    [MARINE_CAVE_COORD(ROUTE_127_NORTH)] = {25, 6},
    [MARINE_CAVE_COORD(ROUTE_127_SOUTH)] = {25, 7},
    [MARINE_CAVE_COORD(ROUTE_129_WEST)]  = {24, 10},
    [MARINE_CAVE_COORD(ROUTE_129_EAST)]  = {24, 10}
};

static const u8 sMapSecAquaHideoutOld[] =
{
    MAPSEC_AQUA_HIDEOUT_OLD
};

static const struct OamData sRegionMapCursorOam =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 1
};

static const union AnimCmd sRegionMapCursorAnim1[] =
{
    ANIMCMD_FRAME(0, 20),
    ANIMCMD_FRAME(4, 20),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd sRegionMapCursorAnim2[] =
{
    ANIMCMD_FRAME( 0, 10),
    ANIMCMD_FRAME(16, 10),
    ANIMCMD_FRAME(32, 10),
    ANIMCMD_FRAME(16, 10),
    ANIMCMD_JUMP(0)
};

static const union AnimCmd *const sRegionMapCursorAnimTable[] =
{
    sRegionMapCursorAnim1,
    sRegionMapCursorAnim2
};

static const struct SpritePalette sRegionMapCursorSpritePalette =
{
    .data = sRegionMapCursorPal,
    .tag = TAG_CURSOR
};

static const struct SpriteTemplate sRegionMapCursorSpriteTemplate =
{
    .tileTag = TAG_CURSOR,
    .paletteTag = TAG_CURSOR,
    .oam = &sRegionMapCursorOam,
    .anims = sRegionMapCursorAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_CursorMapFull
};

static const struct OamData sRegionMapPlayerIconOam =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 2
};

static const union AnimCmd sRegionMapPlayerIconAnim1[] =
{
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_END
};

static const union AnimCmd *const sRegionMapPlayerIconAnimTable[] =
{
    sRegionMapPlayerIconAnim1
};

// Event islands that don't appear on map. (Southern Island does)
static const u8 sMapSecIdsOffMap[] =
{
    MAPSEC_SOUTHERN_ISLAND,
    MAPSEC_BIRTH_ISLAND,
    MAPSEC_FARAWAY_ISLAND,
    MAPSEC_NAVEL_ROCK
};

static const u16 sRegionMapFramePal[] = INCBIN_U16("graphics/pokenav/region_map/frame.gbapal");
static const u32 sRegionMapFrameGfxLZ[] = INCBIN_U32("graphics/pokenav/region_map/frame.4bpp.lz");
static const u32 sRegionMapFrameTilemapLZ[] = INCBIN_U32("graphics/pokenav/region_map/frame.bin.lz");
static const u16 sFlyTargetIcons_Pal[] = INCBIN_U16("graphics/pokenav/region_map/fly_target_icons.gbapal");
static const u32 sFlyTargetIcons_Gfx[] = INCBIN_U32("graphics/pokenav/region_map/fly_target_icons.4bpp.lz");

static const u8 sMapHealLocations[][3] =
{
    [MAPSEC_NEW_BARK_TOWN] = {MAP_GROUP(NEW_BARK_TOWN), MAP_NUM(NEW_BARK_TOWN), HEAL_LOCATION_NEW_BARK_TOWN},
    [MAPSEC_VIOLET_CITY] = {MAP_GROUP(VIOLET_CITY), MAP_NUM(VIOLET_CITY), HEAL_LOCATION_VIOLET_CITY},
    [MAPSEC_AZALEA_TOWN] = {MAP_GROUP(AZALEA_TOWN), MAP_NUM(AZALEA_TOWN), HEAL_LOCATION_AZALEA_TOWN},
    [MAPSEC_GOLDENROD_CITY] = {MAP_GROUP(GOLDENROD_CITY), MAP_NUM(GOLDENROD_CITY), HEAL_LOCATION_GOLDENROD_CITY},
    [MAPSEC_ECRUTEAK_CITY] = {MAP_GROUP(ECRUTEAK_CITY), MAP_NUM(ECRUTEAK_CITY), HEAL_LOCATION_ECRUTEAK_CITY},
    [MAPSEC_OLIVINE_CITY] = {MAP_GROUP(OLIVINE_CITY), MAP_NUM(OLIVINE_CITY), HEAL_LOCATION_OLIVINE_CITY},
    [MAPSEC_CIANWOOD_CITY] = {MAP_GROUP(CIANWOOD_CITY), MAP_NUM(CIANWOOD_CITY), HEAL_LOCATION_CIANWOOD_CITY},
    [MAPSEC_SAFARI_ZONE_GATE] = {MAP_GROUP(SAFARI_ZONE_GATE), MAP_NUM(SAFARI_ZONE_GATE), HEAL_LOCATION_SAFARI_ZONE_GATE},
    [MAPSEC_MAHOGANY_TOWN] = {MAP_GROUP(MAHOGANYTOWN), MAP_NUM(MAHOGANYTOWN), HEAL_LOCATION_MAHOGANYTOWN},
    [MAPSEC_BLACKTHORN_CITY] = {MAP_GROUP(BLACKTHORN_CITY), MAP_NUM(BLACKTHORN_CITY), HEAL_LOCATION_BLACKTHORN_CITY},
    [MAPSEC_CHERRYGROVE_CITY] = {MAP_GROUP(CHERRYGROVE_CITY), MAP_NUM(CHERRYGROVE_CITY), HEAL_LOCATION_CHERRYGROVE_CITY},
    [MAPSEC_ROUTE_26] = {MAP_GROUP(ROUTE26NORTH), MAP_NUM(ROUTE26NORTH), HEAL_LOCATION_ROUTE26NORTH},
    [MAPSEC_ROUTE_26] = {MAP_GROUP(ROUTE26), MAP_NUM(ROUTE26), HEAL_LOCATION_ROUTE26NORTH},
    /*
    [MAPSEC_FORTREE_CITY] = {MAP_GROUP(FORTREE_CITY), MAP_NUM(FORTREE_CITY), HEAL_LOCATION_FORTREE_CITY},
    [MAPSEC_LILYCOVE_CITY] = {MAP_GROUP(LILYCOVE_CITY), MAP_NUM(LILYCOVE_CITY), HEAL_LOCATION_LILYCOVE_CITY},
    [MAPSEC_MOSSDEEP_CITY] = {MAP_GROUP(MOSSDEEP_CITY), MAP_NUM(MOSSDEEP_CITY), HEAL_LOCATION_MOSSDEEP_CITY},
    [MAPSEC_SOOTOPOLIS_CITY] = {MAP_GROUP(SOOTOPOLIS_CITY), MAP_NUM(SOOTOPOLIS_CITY), HEAL_LOCATION_SOOTOPOLIS_CITY},
    [MAPSEC_INDIGO_PLATEAU] = {MAP_GROUP(INDIGO_PLATEAU), MAP_NUM(INDIGO_PLATEAU), HEAL_LOCATION_EVER_GRANDE_CITY},
    */
    [MAPSEC_ROUTE_27] = {MAP_GROUP(ROUTE27), MAP_NUM(ROUTE27), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_28] = {MAP_GROUP(ROUTE28), MAP_NUM(ROUTE28), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_29] = {MAP_GROUP(ROUTE29), MAP_NUM(ROUTE29), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_30] = {MAP_GROUP(ROUTE30), MAP_NUM(ROUTE30), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_31] = {MAP_GROUP(ROUTE31), MAP_NUM(ROUTE31), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_32] = {MAP_GROUP(ROUTE32), MAP_NUM(ROUTE32), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_33] = {MAP_GROUP(ROUTE33), MAP_NUM(ROUTE33), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_34] = {MAP_GROUP(ROUTE34), MAP_NUM(ROUTE34), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_35] = {MAP_GROUP(ROUTE35), MAP_NUM(ROUTE35), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_36] = {MAP_GROUP(ROUTE36), MAP_NUM(ROUTE36), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_37] = {MAP_GROUP(ROUTE37), MAP_NUM(ROUTE37), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_38] = {MAP_GROUP(ROUTE38), MAP_NUM(ROUTE38), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_39] = {MAP_GROUP(ROUTE39), MAP_NUM(ROUTE39), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_40] = {MAP_GROUP(ROUTE40), MAP_NUM(ROUTE40), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_41] = {MAP_GROUP(ROUTE41), MAP_NUM(ROUTE41), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_42] = {MAP_GROUP(ROUTE42), MAP_NUM(ROUTE42), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_43] = {MAP_GROUP(ROUTE43), MAP_NUM(ROUTE43), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_44] = {MAP_GROUP(ROUTE44), MAP_NUM(ROUTE44), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_45] = {MAP_GROUP(ROUTE45), MAP_NUM(ROUTE45), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_46] = {MAP_GROUP(ROUTE46), MAP_NUM(ROUTE46), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_47] = {MAP_GROUP(ROUTE47), MAP_NUM(ROUTE47), HEAL_LOCATION_NONE},
    [MAPSEC_ROUTE_48] = {MAP_GROUP(ROUTE48), MAP_NUM(ROUTE48), HEAL_LOCATION_NONE},
    [MAPSEC_DARK_CAVE] = {MAP_GROUP(ROUTE124), MAP_NUM(ROUTE124), HEAL_LOCATION_NONE},
    [MAPSEC_UNION_CAVE] = {MAP_GROUP(ROUTE125), MAP_NUM(ROUTE125), HEAL_LOCATION_NONE},
    [MAPSEC_ILEX_FOREST] = {MAP_GROUP(ROUTE126), MAP_NUM(ROUTE126), HEAL_LOCATION_NONE},
    [MAPSEC_NATIONAL_PARK] = {MAP_GROUP(ROUTE127), MAP_NUM(ROUTE127), HEAL_LOCATION_NONE},
    [MAPSEC_WHIRL_ISLANDS] = {MAP_GROUP(ROUTE128), MAP_NUM(ROUTE128), HEAL_LOCATION_NONE},
    [MAPSEC_CLIFF_CAVE] = {MAP_GROUP(ROUTE129), MAP_NUM(ROUTE129), HEAL_LOCATION_NONE},
    [MAPSEC_MT_MORTAR] = {MAP_GROUP(ROUTE130), MAP_NUM(ROUTE130), HEAL_LOCATION_NONE},
    [MAPSEC_LAKE_OF_RAGE] = {MAP_GROUP(LAKE_OF_RAGE), MAP_NUM(LAKE_OF_RAGE), HEAL_LOCATION_LAKE_OF_RAGE},
    [MAPSEC_ICE_PATH] = {MAP_GROUP(ROUTE132), MAP_NUM(ROUTE132), HEAL_LOCATION_NONE},
    [MAPSEC_MT_SILVER] = {MAP_GROUP(MT_SILVER_OUTSIDE), MAP_NUM(MT_SILVER_OUTSIDE), HEAL_LOCATION_MT_SILVER},
    [MAPSEC_TOHJO_FALLS] = {MAP_GROUP(ROUTE134), MAP_NUM(ROUTE134), HEAL_LOCATION_NONE},
    [MAPSEC_PALLET_TOWN] = {MAP_GROUP(PALLET_TOWN), MAP_NUM(PALLET_TOWN), HEAL_LOCATION_PALLET_TOWN},
    [MAPSEC_VIRIDIAN_CITY] = {MAP_GROUP(VIRIDIAN_CITY), MAP_NUM(VIRIDIAN_CITY), HEAL_LOCATION_VIRIDIAN_CITY},
    [MAPSEC_PEWTER_CITY] = {MAP_GROUP(PEWTER_CITY), MAP_NUM(PEWTER_CITY), HEAL_LOCATION_PEWTER_CITY},
    [MAPSEC_CERULEAN_CITY] = {MAP_GROUP(CERULEAN_CITY), MAP_NUM(CERULEAN_CITY), HEAL_LOCATION_CERULEAN_CITY},
    [MAPSEC_VERMILION_CITY] = {MAP_GROUP(VERMILION_CITY), MAP_NUM(VERMILION_CITY), HEAL_LOCATION_VERMILION_CITY},
    [MAPSEC_LAVENDER_TOWN] = {MAP_GROUP(LAVENDER_TOWN), MAP_NUM(LAVENDER_TOWN), HEAL_LOCATION_LAVENDER_TOWN},
    [MAPSEC_CELADON_CITY] = {MAP_GROUP(CELADON_CITY), MAP_NUM(CELADON_CITY), HEAL_LOCATION_CELADON_CITY},
    [MAPSEC_SAFFRON_CITY] = {MAP_GROUP(SAFFRON_CITY), MAP_NUM(SAFFRON_CITY), HEAL_LOCATION_SAFFRON_CITY},
    [MAPSEC_FUCHSIA_CITY] = {MAP_GROUP(FUCHSIA_CITY), MAP_NUM(FUCHSIA_CITY), HEAL_LOCATION_FUCHSIA_CITY},
    [MAPSEC_SOUTHERN_ISLAND] = {MAP_GROUP(SOUTHERN_ISLAND_EXTERIOR), MAP_NUM(SOUTHERN_ISLAND_EXTERIOR), HEAL_LOCATION_NONE},
    [MAPSEC_BIRTH_ISLAND] = {MAP_GROUP(BIRTH_ISLAND_EXTERIOR), MAP_NUM(BIRTH_ISLAND_EXTERIOR), HEAL_LOCATION_NONE},
    [MAPSEC_FARAWAY_ISLAND] = {MAP_GROUP(FARAWAY_ISLAND_ENTRANCE), MAP_NUM(FARAWAY_ISLAND_ENTRANCE), HEAL_LOCATION_NONE},
    [MAPSEC_CINNABAR_ISLAND] = {MAP_GROUP(CINNABAR_ISLAND), MAP_NUM(CINNABAR_ISLAND), HEAL_LOCATION_CINNABAR_ISLAND},

};

static const u8 *const sEverGrandeCityNames[] =
{
    gText_PokemonLeague,
    gText_PokemonCenter
};

static const struct MultiNameFlyDest sMultiNameFlyDestinations[] =
{/*
    {
        .name = sEverGrandeCityNames,
        .mapSecId = MAPSEC_INDIGO_PLATEAU,
        .flag = FLAG_LANDMARK_POKEMON_LEAGUE
    }
    */
};

static const struct BgTemplate sFlyMapBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1
    },
    {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 28,
        .screenSize = 2,
        .paletteMode = 1,
        .priority = 2
    }
};

static const struct WindowTemplate sFlyMapWindowTemplates[] =
{
    {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 17,
        .width = 12,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x01
    },
    {
        .bg = 0,
        .tilemapLeft = 17,
        .tilemapTop = 15,
        .width = 12,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x19
    },
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 18,
        .width = 14,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x49
    },
    DUMMY_WIN_TEMPLATE
};

static const struct SpritePalette sFlyTargetIconsSpritePalette =
{
    .data = sFlyTargetIcons_Pal,
    .tag = TAG_FLY_ICON
};

static const u16 sRedOutlineFlyDestinations[][2] =
{/*
    {
        FLAG_VISITED_FUCHSIA_CITY,
        MAPSEC_BATTLE_FRONTIER
    },
    */
    {
        -1,
        MAPSEC_NONE
    }
};

static const struct OamData sFlyDestIcon_OamData =
{
    .shape = SPRITE_SHAPE(8x8),
    .size = SPRITE_SIZE(8x8),
    .priority = 2
};

static const union AnimCmd sFlyDestIcon_Anim_8x8CanFly[] =
{
    ANIMCMD_FRAME( 0, 5),
    ANIMCMD_END
};

static const union AnimCmd sFlyDestIcon_Anim_16x8CanFly[] =
{
    ANIMCMD_FRAME( 1, 5),
    ANIMCMD_END
};

static const union AnimCmd sFlyDestIcon_Anim_8x16CanFly[] =
{
    ANIMCMD_FRAME( 3, 5),
    ANIMCMD_END
};

static const union AnimCmd sFlyDestIcon_Anim_8x8CantFly[] =
{
    ANIMCMD_FRAME( 5, 5),
    ANIMCMD_END
};

static const union AnimCmd sFlyDestIcon_Anim_16x8CantFly[] =
{
    ANIMCMD_FRAME( 6, 5),
    ANIMCMD_END
};

static const union AnimCmd sFlyDestIcon_Anim_8x16CantFly[] =
{
    ANIMCMD_FRAME( 8, 5),
    ANIMCMD_END
};

// Only used by Battle Frontier
static const union AnimCmd sFlyDestIcon_Anim_RedOutline[] =
{
    ANIMCMD_FRAME(10, 5),
    ANIMCMD_END
};

static const union AnimCmd *const sFlyDestIcon_Anims[] =
{
    [SPRITE_SHAPE(8x8)]       = sFlyDestIcon_Anim_8x8CanFly,
    [SPRITE_SHAPE(16x8)]      = sFlyDestIcon_Anim_16x8CanFly,
    [SPRITE_SHAPE(8x16)]      = sFlyDestIcon_Anim_8x16CanFly,
    [SPRITE_SHAPE(8x8)  + 3]  = sFlyDestIcon_Anim_8x8CantFly,
    [SPRITE_SHAPE(16x8) + 3]  = sFlyDestIcon_Anim_16x8CantFly,
    [SPRITE_SHAPE(8x16) + 3]  = sFlyDestIcon_Anim_8x16CantFly,
    [FLYDESTICON_RED_OUTLINE] = sFlyDestIcon_Anim_RedOutline
};

static const struct SpriteTemplate sFlyDestIconSpriteTemplate =
{
    .tileTag = TAG_FLY_ICON,
    .paletteTag = TAG_FLY_ICON,
    .oam = &sFlyDestIcon_OamData,
    .anims = sFlyDestIcon_Anims,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

void InitRegionMap(struct RegionMap *regionMap, bool8 zoomed)
{
    InitRegionMapData(regionMap, NULL, zoomed);
    while (LoadRegionMapGfx());
}

void InitRegionMapData(struct RegionMap *regionMap, const struct BgTemplate *template, bool8 zoomed)
{
    ChooseMapVariant();  // ensure sActive* pointers/arrays are set for PokeNav too
    sRegionMap = regionMap;
    sRegionMap->initStep = 0;
    sRegionMap->zoomed = zoomed;
    sRegionMap->inputCallback = zoomed == TRUE ? ProcessRegionMapInput_Zoomed : ProcessRegionMapInput_Full;
    if (template != NULL)
    {
        sRegionMap->bgNum = template->bg;
        sRegionMap->charBaseIdx = template->charBaseIndex;
        sRegionMap->mapBaseIdx = template->mapBaseIndex;
        sRegionMap->bgManaged = TRUE;
    }
    else
    {
        sRegionMap->bgNum = 2;
        sRegionMap->charBaseIdx = 2;
        sRegionMap->mapBaseIdx = 28;
        sRegionMap->bgManaged = FALSE;
    }
}

void ShowRegionMapForPokedexAreaScreen(struct RegionMap *regionMap)
{
    sRegionMap = regionMap;
    InitMapBasedOnPlayerLocation();
    sRegionMap->playerIconSpritePosX = sRegionMap->cursorPosX;
    sRegionMap->playerIconSpritePosY = sRegionMap->cursorPosY;
}

bool8 LoadRegionMapGfx(void)
{
    ChooseMapVariant();
    switch (sRegionMap->initStep)
    {
    case 0:
        if (sRegionMap->bgManaged)
            DecompressAndCopyTileDataToVram(sRegionMap->bgNum, sActiveMapGfxLZ, 0, 0, 0);
        else
            LZ77UnCompVram(sActiveMapGfxLZ, (u16 *)BG_CHAR_ADDR(2));
        break;
    case 1:
        if (sRegionMap->bgManaged)
        {
            if (!FreeTempTileDataBuffersIfPossible())
                DecompressAndCopyTileDataToVram(sRegionMap->bgNum, sActiveMapTilemapLZ, 0, 0, 1);
        }
        else
        {
            LZ77UnCompVram(sActiveMapTilemapLZ, (u16 *)BG_SCREEN_ADDR(28));
        }
        break;
    case 2:
        if (!FreeTempTileDataBuffersIfPossible())
            LoadPalette(sActiveMapPal, BG_PLTT_ID(7), 3 * PLTT_SIZE_4BPP);
        break;
    case 3:
        LZ77UnCompWram(sRegionMapCursorSmallGfxLZ, sRegionMap->cursorSmallImage);
        break;
    case 4:
        LZ77UnCompWram(sRegionMapCursorLargeGfxLZ, sRegionMap->cursorLargeImage);
        break;
    case 5:
        InitMapBasedOnPlayerLocation();
        sRegionMap->playerIconSpritePosX = sRegionMap->cursorPosX;
        sRegionMap->playerIconSpritePosY = sRegionMap->cursorPosY;
        sRegionMap->mapSecId = CorrectSpecialMapSecId_Internal(sRegionMap->mapSecId);
        sRegionMap->mapSecType = GetMapsecType(sRegionMap->mapSecId);
        GetMapName(sRegionMap->mapSecName, sRegionMap->mapSecId, MAP_NAME_LENGTH);
        break;
    case 6:
        if (sRegionMap->zoomed == FALSE)
        {
            CalcZoomScrollParams(0, 0, 0, 0, 0x100, 0x100, 0);
        }
        else
        {
            sRegionMap->scrollX = sRegionMap->cursorPosX * 8 - 0x34;
            sRegionMap->scrollY = sRegionMap->cursorPosY * 8 - 0x44;
            sRegionMap->zoomedCursorPosX = sRegionMap->cursorPosX;
            sRegionMap->zoomedCursorPosY = sRegionMap->cursorPosY;
            CalcZoomScrollParams(sRegionMap->scrollX, sRegionMap->scrollY, 0x38, 0x48, 0x80, 0x80, 0);
        }
        break;
    case 7:
        GetPositionOfCursorWithinMapSec();
        UpdateRegionMapVideoRegs();
        sRegionMap->cursorSprite = NULL;
        sRegionMap->playerIconSprite = NULL;
        sRegionMap->cursorMovementFrameCounter = 0;
        sRegionMap->blinkPlayerIcon = FALSE;
        if (sRegionMap->bgManaged)
        {
            SetBgAttribute(sRegionMap->bgNum, BG_ATTR_SCREENSIZE, 2);
            SetBgAttribute(sRegionMap->bgNum, BG_ATTR_CHARBASEINDEX, sRegionMap->charBaseIdx);
            SetBgAttribute(sRegionMap->bgNum, BG_ATTR_MAPBASEINDEX, sRegionMap->mapBaseIdx);
            SetBgAttribute(sRegionMap->bgNum, BG_ATTR_WRAPAROUND, 1);
            SetBgAttribute(sRegionMap->bgNum, BG_ATTR_PALETTEMODE, 1);
        }
        sRegionMap->initStep++;
        return FALSE;
    default:
        return FALSE;
    }
    sRegionMap->initStep++;
    return TRUE;
}

void BlendRegionMap(u16 color, u32 coeff)
{
    BlendPalettes(0x380, coeff, color);
    CpuCopy16(&gPlttBufferFaded[BG_PLTT_ID(7)], &gPlttBufferUnfaded[BG_PLTT_ID(7)], 3 * PLTT_SIZE_4BPP);
}

void FreeRegionMapIconResources(void)
{
    if (sRegionMap->cursorSprite != NULL)
    {
        DestroySprite(sRegionMap->cursorSprite);
        FreeSpriteTilesByTag(sRegionMap->cursorTileTag);
        FreeSpritePaletteByTag(sRegionMap->cursorPaletteTag);
    }
    if (sRegionMap->playerIconSprite != NULL)
    {
        DestroySprite(sRegionMap->playerIconSprite);
        FreeSpriteTilesByTag(sRegionMap->playerIconTileTag);
        FreeSpritePaletteByTag(sRegionMap->playerIconPaletteTag);
    }
}

u8 DoRegionMapInputCallback(void)
{
    return sRegionMap->inputCallback();
}

static u8 ProcessRegionMapInput_Full(void)
{
    u8 input;

    input = MAP_INPUT_NONE;
    sRegionMap->cursorDeltaX = 0;
    sRegionMap->cursorDeltaY = 0;
    if (JOY_HELD(DPAD_UP) && sRegionMap->cursorPosY > MAPCURSOR_Y_MIN)
    {
        sRegionMap->cursorDeltaY = -1;
        input = MAP_INPUT_MOVE_START;
    }
    if (JOY_HELD(DPAD_DOWN) && sRegionMap->cursorPosY < MAPCURSOR_Y_MAX)
    {
        sRegionMap->cursorDeltaY = +1;
        input = MAP_INPUT_MOVE_START;
    }
    if (JOY_HELD(DPAD_LEFT) && sRegionMap->cursorPosX > MAPCURSOR_X_MIN)
    {
        sRegionMap->cursorDeltaX = -1;
        input = MAP_INPUT_MOVE_START;
    }
    if (JOY_HELD(DPAD_RIGHT) && sRegionMap->cursorPosX < MAPCURSOR_X_MAX)
    {
        sRegionMap->cursorDeltaX = +1;
        input = MAP_INPUT_MOVE_START;
    }
    if (JOY_NEW(A_BUTTON))
    {
        input = MAP_INPUT_A_BUTTON;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        input = MAP_INPUT_B_BUTTON;
    }
    if (input == MAP_INPUT_MOVE_START)
    {
        sRegionMap->cursorMovementFrameCounter = 4;
        sRegionMap->inputCallback = MoveRegionMapCursor_Full;
    }
    return input;
}

static u8 MoveRegionMapCursor_Full(void)
{
    u16 mapSecId;

    if (sRegionMap->cursorMovementFrameCounter != 0)
        return MAP_INPUT_MOVE_CONT;

    if (sRegionMap->cursorDeltaX > 0)
    {
        sRegionMap->cursorPosX++;
    }
    if (sRegionMap->cursorDeltaX < 0)
    {
        sRegionMap->cursorPosX--;
    }
    if (sRegionMap->cursorDeltaY > 0)
    {
        sRegionMap->cursorPosY++;
    }
    if (sRegionMap->cursorDeltaY < 0)
    {
        sRegionMap->cursorPosY--;
    }

    mapSecId = GetMapSecIdAt(sRegionMap->cursorPosX, sRegionMap->cursorPosY);
    sRegionMap->mapSecType = GetMapsecType(mapSecId);
    if (mapSecId != sRegionMap->mapSecId)
    {
        sRegionMap->mapSecId = mapSecId;
        GetMapName(sRegionMap->mapSecName, sRegionMap->mapSecId, MAP_NAME_LENGTH);
    }
    GetPositionOfCursorWithinMapSec();
    sRegionMap->inputCallback = ProcessRegionMapInput_Full;
    return MAP_INPUT_MOVE_END;
}

static u8 ProcessRegionMapInput_Zoomed(void)
{
    u8 input;

    input = MAP_INPUT_NONE;
    sRegionMap->zoomedCursorDeltaX = 0;
    sRegionMap->zoomedCursorDeltaY = 0;
    if (JOY_HELD(DPAD_UP) && sRegionMap->scrollY > -0x34)
    {
        sRegionMap->zoomedCursorDeltaY = -1;
        input = MAP_INPUT_MOVE_START;
    }
    if (JOY_HELD(DPAD_DOWN) && sRegionMap->scrollY < 0x3c)
    {
        sRegionMap->zoomedCursorDeltaY = +1;
        input = MAP_INPUT_MOVE_START;
    }
    if (JOY_HELD(DPAD_LEFT) && sRegionMap->scrollX > -0x2c)
    {
        sRegionMap->zoomedCursorDeltaX = -1;
        input = MAP_INPUT_MOVE_START;
    }
    if (JOY_HELD(DPAD_RIGHT) && sRegionMap->scrollX < 0xac)
    {
        sRegionMap->zoomedCursorDeltaX = +1;
        input = MAP_INPUT_MOVE_START;
    }
    if (JOY_NEW(A_BUTTON))
    {
        input = MAP_INPUT_A_BUTTON;
    }
    if (JOY_NEW(B_BUTTON))
    {
        input = MAP_INPUT_B_BUTTON;
    }
    if (input == MAP_INPUT_MOVE_START)
    {
        sRegionMap->inputCallback = MoveRegionMapCursor_Zoomed;
        sRegionMap->zoomedCursorMovementFrameCounter = 0;
    }
    return input;
}

static u8 MoveRegionMapCursor_Zoomed(void)
{
    u16 x;
    u16 y;
    u16 mapSecId;

    sRegionMap->scrollY += sRegionMap->zoomedCursorDeltaY;
    sRegionMap->scrollX += sRegionMap->zoomedCursorDeltaX;
    RegionMap_SetBG2XAndBG2Y(sRegionMap->scrollX, sRegionMap->scrollY);
    sRegionMap->zoomedCursorMovementFrameCounter++;
    if (sRegionMap->zoomedCursorMovementFrameCounter == 8)
    {
        x = (sRegionMap->scrollX + 0x2c) / 8 + 1;
        y = (sRegionMap->scrollY + 0x34) / 8 + 2;
        if (x != sRegionMap->zoomedCursorPosX || y != sRegionMap->zoomedCursorPosY)
        {
            sRegionMap->zoomedCursorPosX = x;
            sRegionMap->zoomedCursorPosY = y;
            mapSecId = GetMapSecIdAt(x, y);
            sRegionMap->mapSecType = GetMapsecType(mapSecId);
            if (mapSecId != sRegionMap->mapSecId)
            {
                sRegionMap->mapSecId = mapSecId;
                GetMapName(sRegionMap->mapSecName, sRegionMap->mapSecId, MAP_NAME_LENGTH);
            }
            GetPositionOfCursorWithinMapSec();
        }
        sRegionMap->zoomedCursorMovementFrameCounter = 0;
        sRegionMap->inputCallback = ProcessRegionMapInput_Zoomed;
        return MAP_INPUT_MOVE_END;
    }
    return MAP_INPUT_MOVE_CONT;
}

void SetRegionMapDataForZoom(void)
{
    if (sRegionMap->zoomed == FALSE)
    {
        sRegionMap->scrollY = 0;
        sRegionMap->scrollX = 0;
        sRegionMap->unk_040 = 0;
        sRegionMap->unk_03c = 0;
        sRegionMap->unk_060 = sRegionMap->cursorPosX * 8 - 0x34;
        sRegionMap->unk_062 = sRegionMap->cursorPosY * 8 - 0x44;
        sRegionMap->unk_044 = (sRegionMap->unk_060 << 8) / 16;
        sRegionMap->unk_048 = (sRegionMap->unk_062 << 8) / 16;
        sRegionMap->zoomedCursorPosX = sRegionMap->cursorPosX;
        sRegionMap->zoomedCursorPosY = sRegionMap->cursorPosY;
        sRegionMap->unk_04c = 0x10000;
        sRegionMap->unk_050 = -0x800;
    }
    else
    {
        sRegionMap->unk_03c = sRegionMap->scrollX * 0x100;
        sRegionMap->unk_040 = sRegionMap->scrollY * 0x100;
        sRegionMap->unk_060 = 0;
        sRegionMap->unk_062 = 0;
        sRegionMap->unk_044 = -(sRegionMap->unk_03c / 16);
        sRegionMap->unk_048 = -(sRegionMap->unk_040 / 16);
        sRegionMap->cursorPosX = sRegionMap->zoomedCursorPosX;
        sRegionMap->cursorPosY = sRegionMap->zoomedCursorPosY;
        sRegionMap->unk_04c = 0x8000;
        sRegionMap->unk_050 = 0x800;
    }
    sRegionMap->unk_06e = 0;
    FreeRegionMapCursorSprite();
    HideRegionMapPlayerIcon();
}

bool8 UpdateRegionMapZoom(void)
{
    bool8 retVal;

    if (sRegionMap->unk_06e >= 16)
    {
        return FALSE;
    }
    sRegionMap->unk_06e++;
    if (sRegionMap->unk_06e == 16)
    {
        sRegionMap->unk_044 = 0;
        sRegionMap->unk_048 = 0;
        sRegionMap->scrollX = sRegionMap->unk_060;
        sRegionMap->scrollY = sRegionMap->unk_062;
        sRegionMap->unk_04c = (sRegionMap->zoomed == FALSE) ? (128 << 8) : (256 << 8);
        sRegionMap->zoomed = !sRegionMap->zoomed;
        sRegionMap->inputCallback = (sRegionMap->zoomed == FALSE) ? ProcessRegionMapInput_Full : ProcessRegionMapInput_Zoomed;
        CreateRegionMapCursor(sRegionMap->cursorTileTag, sRegionMap->cursorPaletteTag);
        UnhideRegionMapPlayerIcon();
        retVal = FALSE;
    }
    else
    {
        sRegionMap->unk_03c += sRegionMap->unk_044;
        sRegionMap->unk_040 += sRegionMap->unk_048;
        sRegionMap->scrollX = sRegionMap->unk_03c >> 8;
        sRegionMap->scrollY = sRegionMap->unk_040 >> 8;
        sRegionMap->unk_04c += sRegionMap->unk_050;
        if ((sRegionMap->unk_044 < 0 && sRegionMap->scrollX < sRegionMap->unk_060) || (sRegionMap->unk_044 > 0 && sRegionMap->scrollX > sRegionMap->unk_060))
        {
            sRegionMap->scrollX = sRegionMap->unk_060;
            sRegionMap->unk_044 = 0;
        }
        if ((sRegionMap->unk_048 < 0 && sRegionMap->scrollY < sRegionMap->unk_062) || (sRegionMap->unk_048 > 0 && sRegionMap->scrollY > sRegionMap->unk_062))
        {
            sRegionMap->scrollY = sRegionMap->unk_062;
            sRegionMap->unk_048 = 0;
        }
        if (sRegionMap->zoomed == FALSE)
        {
            if (sRegionMap->unk_04c < (128 << 8))
            {
                sRegionMap->unk_04c = (128 << 8);
                sRegionMap->unk_050 = 0;
            }
        }
        else
        {
            if (sRegionMap->unk_04c > (256 << 8))
            {
                sRegionMap->unk_04c = (256 << 8);
                sRegionMap->unk_050 = 0;
            }
        }
        retVal = TRUE;
    }
    CalcZoomScrollParams(sRegionMap->scrollX, sRegionMap->scrollY, 0x38, 0x48, sRegionMap->unk_04c >> 8, sRegionMap->unk_04c >> 8, 0);
    return retVal;
}

static void CalcZoomScrollParams(s16 scrollX, s16 scrollY, s16 c, s16 d, u16 e, u16 f, u8 rotation)
{
    s32 var1;
    s32 var2;
    s32 var3;
    s32 var4;

    sRegionMap->bg2pa = e * gSineTable[rotation + 64] >> 8;
    sRegionMap->bg2pc = e * -gSineTable[rotation] >> 8;
    sRegionMap->bg2pb = f * gSineTable[rotation] >> 8;
    sRegionMap->bg2pd = f * gSineTable[rotation + 64] >> 8;

    var1 = (scrollX << 8) + (c << 8);
    var2 = d * sRegionMap->bg2pb + sRegionMap->bg2pa * c;
    sRegionMap->bg2x = var1 - var2;

    var3 = (scrollY << 8) + (d << 8);
    var4 = sRegionMap->bg2pd * d + sRegionMap->bg2pc * c;
    sRegionMap->bg2y = var3 - var4;

    sRegionMap->needUpdateVideoRegs = TRUE;
}

static void RegionMap_SetBG2XAndBG2Y(s16 x, s16 y)
{
    sRegionMap->bg2x = (x << 8) + 0x1c00;
    sRegionMap->bg2y = (y << 8) + 0x2400;
    sRegionMap->needUpdateVideoRegs = TRUE;
}

void UpdateRegionMapVideoRegs(void)
{
    if (sRegionMap->needUpdateVideoRegs)
    {
        SetGpuReg(REG_OFFSET_BG2PA, sRegionMap->bg2pa);
        SetGpuReg(REG_OFFSET_BG2PB, sRegionMap->bg2pb);
        SetGpuReg(REG_OFFSET_BG2PC, sRegionMap->bg2pc);
        SetGpuReg(REG_OFFSET_BG2PD, sRegionMap->bg2pd);
        SetGpuReg(REG_OFFSET_BG2X_L, sRegionMap->bg2x);
        SetGpuReg(REG_OFFSET_BG2X_H, sRegionMap->bg2x >> 16);
        SetGpuReg(REG_OFFSET_BG2Y_L, sRegionMap->bg2y);
        SetGpuReg(REG_OFFSET_BG2Y_H, sRegionMap->bg2y >> 16);
        sRegionMap->needUpdateVideoRegs = FALSE;
    }
}

void PokedexAreaScreen_UpdateRegionMapVariablesAndVideoRegs(s16 x, s16 y)
{
    CalcZoomScrollParams(x, y, 0x38, 0x48, 0x100, 0x100, 0);
    UpdateRegionMapVideoRegs();
    if (sRegionMap->playerIconSprite != NULL)
    {
        sRegionMap->playerIconSprite->x2 = -x;
        sRegionMap->playerIconSprite->y2 = -y;
    }
}

static u16 GetMapSecIdAt(u16 x, u16 y)
{
    if (y < MAPCURSOR_Y_MIN || y > MAPCURSOR_Y_MAX || x < MAPCURSOR_X_MIN || x > MAPCURSOR_X_MAX)
    {
        return MAPSEC_NONE;
    }
    y -= MAPCURSOR_Y_MIN;
    x -= MAPCURSOR_X_MIN;
    return sActiveRegionLayout[y][x];  // NEW: variant-aware grid
}

static void InitMapBasedOnPlayerLocation(void)
{
    // 1) Pick the map variant for THIS screen (sets sActiveRegionLayout & sActiveEntries)
    ChooseMapVariant();

    const struct MapHeader *mapHeader;
    u16 mapWidth, mapHeight;
    u16 x, y;
    u16 dimensionScale;
    u16 xOnMap;
    struct WarpData *warp;

    // S.S. Tidal special handling
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(SS_TIDAL_CORRIDOR)
     && (gSaveBlock1Ptr->location.mapNum == MAP_NUM(SS_TIDAL_CORRIDOR)
      || gSaveBlock1Ptr->location.mapNum == MAP_NUM(SS_TIDAL_LOWER_DECK)
      || gSaveBlock1Ptr->location.mapNum == MAP_NUM(SS_TIDAL_ROOMS)))
    {
        RegionMap_InitializeStateBasedOnSSTidalLocation();
        return;
    }

    // 2) Determine current section and world coords inside its map
    switch (GetMapTypeByGroupAndId(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
    {
    default:
    case MAP_TYPE_TOWN:
    case MAP_TYPE_CITY:
    case MAP_TYPE_ROUTE:
    case MAP_TYPE_UNDERWATER:
    case MAP_TYPE_OCEAN_ROUTE:
        sRegionMap->mapSecId = gMapHeader.regionMapSectionId;
        sRegionMap->playerIsInCave = FALSE;
        mapWidth  = gMapHeader.mapLayout->width;
        mapHeight = gMapHeader.mapLayout->height;
        x = gSaveBlock1Ptr->pos.x;
        y = gSaveBlock1Ptr->pos.y;
        if (sRegionMap->mapSecId == MAPSEC_UNDERWATER_SEAFLOOR_CAVERN
         || sRegionMap->mapSecId == MAPSEC_UNDERWATER_MARINE_CAVE)
            sRegionMap->playerIsInCave = TRUE;
        break;

    case MAP_TYPE_UNDERGROUND:
    case MAP_TYPE_UNKNOWN:
        if (gMapHeader.allowEscaping)
        {
            mapHeader = Overworld_GetMapHeaderByGroupAndId(gSaveBlock1Ptr->escapeWarp.mapGroup, gSaveBlock1Ptr->escapeWarp.mapNum);
            sRegionMap->mapSecId = mapHeader->regionMapSectionId;
            sRegionMap->playerIsInCave = TRUE;
            mapWidth  = mapHeader->mapLayout->width;
            mapHeight = mapHeader->mapLayout->height;
            x = gSaveBlock1Ptr->escapeWarp.x;
            y = gSaveBlock1Ptr->escapeWarp.y;
        }
        else
        {
            sRegionMap->mapSecId = gMapHeader.regionMapSectionId;
            sRegionMap->playerIsInCave = TRUE;
            mapWidth = mapHeight = 1;
            x = y = 1;
        }
        break;

    case MAP_TYPE_SECRET_BASE:
        mapHeader = Overworld_GetMapHeaderByGroupAndId((u16)gSaveBlock1Ptr->dynamicWarp.mapGroup, (u16)gSaveBlock1Ptr->dynamicWarp.mapNum);
        sRegionMap->mapSecId = mapHeader->regionMapSectionId;
        sRegionMap->playerIsInCave = TRUE;
        mapWidth  = mapHeader->mapLayout->width;
        mapHeight = mapHeader->mapLayout->height;
        x = gSaveBlock1Ptr->dynamicWarp.x;
        y = gSaveBlock1Ptr->dynamicWarp.y;
        break;

    case MAP_TYPE_INDOOR:
        sRegionMap->mapSecId = gMapHeader.regionMapSectionId;
        if (sRegionMap->mapSecId != MAPSEC_DYNAMIC)
        {
            warp = &gSaveBlock1Ptr->escapeWarp;
            mapHeader = Overworld_GetMapHeaderByGroupAndId(warp->mapGroup, warp->mapNum);
        }
        else
        {
            warp = &gSaveBlock1Ptr->dynamicWarp;
            mapHeader = Overworld_GetMapHeaderByGroupAndId(warp->mapGroup, warp->mapNum);
            sRegionMap->mapSecId = mapHeader->regionMapSectionId;
        }

        sRegionMap->playerIsInCave = IsPlayerInAquaHideout(sRegionMap->mapSecId);
        mapWidth  = mapHeader->mapLayout->width;
        mapHeight = mapHeader->mapLayout->height;
        x = warp->x;
        y = warp->y;
        break;
    }

    xOnMap = x;

    // 3) Get the section rect from the *active layout grid* (matches the art on screen)
    //    If the section isn’t present on this layout, fall back to the active entries table.
    u16 ex = 0, ey = 0, ew = 1, eh = 1;
    {
        u16 minx = MAP_WIDTH, miny = MAP_HEIGHT, maxx = 0, maxy = 0;
        bool32 found = FALSE;
        for (u16 yy = 0; yy < MAP_HEIGHT; yy++)
        {
            for (u16 xx = 0; xx < MAP_WIDTH; xx++)
            {
                if (sActiveRegionLayout[yy][xx] == sRegionMap->mapSecId)
                {
                    found = TRUE;
                    if (xx < minx) minx = xx;
                    if (yy < miny) miny = yy;
                    if (xx > maxx) maxx = xx;
                    if (yy > maxy) maxy = yy;
                }
            }
        }
        if (found)
        {
            ex = minx; ey = miny; ew = (maxx - minx) + 1; eh = (maxy - miny) + 1;
        }
        else
        {
            const struct RegionMapLocation *e = &sActiveEntries[sRegionMap->mapSecId];
            ex = e->x; ey = e->y; ew = e->width ? e->width : 1; eh = e->height ? e->height : 1;
        }
    }

    // 4) Convert world coords to local tile coords within the section rect
    dimensionScale = ew ? (mapWidth / ew) : 1;
    if (dimensionScale == 0) dimensionScale = 1;
    x /= dimensionScale;
    if (ew && x >= ew) x = ew - 1;

    dimensionScale = eh ? (mapHeight / eh) : 1;
    if (dimensionScale == 0) dimensionScale = 1;
    y /= dimensionScale;
    if (eh && y >= eh) y = eh - 1;

    // 5) Section-specific splits
    switch (sRegionMap->mapSecId)
    {
    case MAPSEC_ROUTE_39:
        if (y != 0)
            x = 0;
        break;
    case MAPSEC_ILEX_FOREST:
    case MAPSEC_SLOWPOKE_WELL:
        x = 0;
        if (gSaveBlock1Ptr->pos.x > 32) x++;
        if (gSaveBlock1Ptr->pos.x > 51) x++;

        y = 0;
        if (gSaveBlock1Ptr->pos.y > 37) y++;
        if (gSaveBlock1Ptr->pos.y > 56) y++;
        break;
    case MAPSEC_ROUTE_46:
        x = 0;
        if (xOnMap > 14) x++;
        if (xOnMap > 28) x++;
        if (xOnMap > 54) x++;
        break;
    case MAPSEC_UNDERWATER_MARINE_CAVE:
        GetMarineCaveCoords(&sRegionMap->cursorPosX, &sRegionMap->cursorPosY);
        return;
    }

    // 6) Final on-screen placement (tile → pixel with origin)
    sRegionMap->cursorPosX = ex + x + MAPCURSOR_X_MIN;
    sRegionMap->cursorPosY = ey + y + MAPCURSOR_Y_MIN;
}


static void RegionMap_InitializeStateBasedOnSSTidalLocation(void)
{
    // 1) Pick the variant for THIS screen so layout matches art
    ChooseMapVariant();

    u16 x = 0, y = 0;
    u8 mapGroup, mapNum;
    s16 xOnMap, yOnMap;
    const struct MapHeader *mapHeader;
    u16 mapSecId;

    switch (GetSSTidalLocation(&mapGroup, &mapNum, &xOnMap, &yOnMap))
    {
    case SS_TIDAL_LOCATION_SLATEPORT:
        mapSecId = MAPSEC_MAHOGANY_TOWN;
        break;
    case SS_TIDAL_LOCATION_LILYCOVE:
        mapSecId = MAPSEC_LILYCOVE_CITY;
        break;
    case SS_TIDAL_LOCATION_ROUTE124:
        mapSecId = MAPSEC_DARK_CAVE;
        break;
    case SS_TIDAL_LOCATION_ROUTE131:
        mapSecId = MAPSEC_LAKE_OF_RAGE;
        break;

    default: // Currents: compute local (x,y) inside the section using the ACTIVE layout
        mapHeader = Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum);
        mapSecId  = mapHeader->regionMapSectionId;

        // Get section rect from active layout (fallback to entries if absent)
        {
            u16 ex = 0, ey = 0, ew = 1, eh = 1;
            u16 minx = MAP_WIDTH, miny = MAP_HEIGHT, maxx = 0, maxy = 0;
            bool32 found = FALSE;

            for (u16 yy = 0; yy < MAP_HEIGHT; yy++)
            {
                for (u16 xx = 0; xx < MAP_WIDTH; xx++)
                {
                    if (sActiveRegionLayout[yy][xx] == mapSecId)
                    {
                        found = TRUE;
                        if (xx < minx) minx = xx;
                        if (yy < miny) miny = yy;
                        if (xx > maxx) maxx = xx;
                        if (yy > maxy) maxy = yy;
                    }
                }
            }
            if (found)
            {
                ex = minx; ey = miny; ew = (maxx - minx) + 1; eh = (maxy - miny) + 1;
            }
            else
            {
                const struct RegionMapLocation *e = &sActiveEntries[mapSecId];
                ex = e->x; ey = e->y; ew = e->width ? e->width : 1; eh = e->height ? e->height : 1;
            }

            // Convert world coords to local tile coords within the section rect
            u16 dim = ew ? (mapHeader->mapLayout->width / ew) : 1;
            if (dim == 0) dim = 1;
            x = (u16)(xOnMap / dim);
            if (ew && x >= ew) x = ew - 1;

            dim = eh ? (mapHeader->mapLayout->height / eh) : 1;
            if (dim == 0) dim = 1;
            y = (u16)(yOnMap / dim);
            if (eh && y >= eh) y = eh - 1;

            // Stash the rect for final placement
            // (We recompute below for clarity; you can hoist ex/ey if you prefer.)
        }
        break;
    }

    sRegionMap->playerIsInCave = FALSE;
    sRegionMap->mapSecId = mapSecId;

    // Final on-screen placement using the ACTIVE layout rect
    {
        u16 ex = 0, ey = 0, ew = 1, eh = 1;
        u16 minx = MAP_WIDTH, miny = MAP_HEIGHT, maxx = 0, maxy = 0;
        bool32 found = FALSE;

        for (u16 yy = 0; yy < MAP_HEIGHT; yy++)
        {
            for (u16 xx = 0; xx < MAP_WIDTH; xx++)
            {
                if (sActiveRegionLayout[yy][xx] == mapSecId)
                {
                    found = TRUE;
                    if (xx < minx) minx = xx;
                    if (yy < miny) miny = yy;
                    if (xx > maxx) maxx = xx;
                    if (yy > maxy) maxy = yy;
                }
            }
        }
        if (found)
        {
            ex = minx; ey = miny; ew = (maxx - minx) + 1; eh = (maxy - miny) + 1;
        }
        else
        {
            const struct RegionMapLocation *e = &sActiveEntries[mapSecId];
            ex = e->x; ey = e->y; ew = e->width ? e->width : 1; eh = e->height ? e->height : 1;
        }

        sRegionMap->cursorPosX = ex + x + MAPCURSOR_X_MIN;
        sRegionMap->cursorPosY = ey + y + MAPCURSOR_Y_MIN;
    }
}



static u8 GetMapsecType(u16 mapSecId)
{
    switch (mapSecId)
    {
    case MAPSEC_NONE:
        return MAPSECTYPE_NONE;
    case MAPSEC_NEW_BARK_TOWN:
        return FlagGet(FLAG_VISITED_NEWBARK_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_VIOLET_CITY:
        return FlagGet(FLAG_VISITED_VIOLET_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_AZALEA_TOWN:
        return FlagGet(FLAG_VISITED_AZALEA_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_GOLDENROD_CITY:
        return FlagGet(FLAG_VISITED_GOLDENROD_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_ECRUTEAK_CITY:
        return FlagGet(FLAG_VISITED_ECRUTEAK_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_OLIVINE_CITY:
        return FlagGet(FLAG_VISITED_OLIVINE_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_CIANWOOD_CITY:
        return FlagGet(FLAG_VISITED_CIANWOOD_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_SAFARI_ZONE_GATE:
        return FlagGet(FLAG_VISITED_SAFARI_ZONE_GATE) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_MAHOGANY_TOWN:
        return FlagGet(FLAG_VISITED_MAHOGANY_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_BLACKTHORN_CITY:
        return FlagGet(FLAG_VISITED_BLACKTHORN_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_CHERRYGROVE_CITY:
        return FlagGet(FLAG_VISITED_CHERRYGROVE_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_VIRIDIAN_CITY:
        return FlagGet(FLAG_VISITED_VIRIDIAN_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_SAFFRON_CITY:
        return FlagGet(FLAG_VISITED_SAFFRON_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_CELADON_CITY:
        return FlagGet(FLAG_VISITED_CELADON_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_LAVENDER_TOWN:
        return FlagGet(FLAG_VISITED_LAVENDER_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_INDIGO_PLATEAU:
        return FlagGet(FLAG_VISITED_INDIGO_PLATEAU) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_FUCHSIA_CITY:
        return FlagGet(FLAG_VISITED_FUCHSIA_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_CERULEAN_CITY:
        return FlagGet(FLAG_VISITED_CERULEAN_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_PEWTER_CITY:
        return FlagGet(FLAG_VISITED_PEWTER_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_VERMILION_CITY:
        return FlagGet(FLAG_VISITED_VERMILION_CITY) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_PALLET_TOWN:
        return FlagGet(FLAG_VISITED_PALLET_TOWN) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_CINNABAR_ISLAND:
        return FlagGet(FLAG_VISITED_CINNABAR_ISLAND) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_LAKE_OF_RAGE:
        return FlagGet(FLAG_VISITED_LAKE_OF_RAGE) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_MT_SILVER:
        return FlagGet(FLAG_VISITED_MT_SILVER) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    case MAPSEC_ROUTE_26:
        return FlagGet(FLAG_VISITED_RECEPTION_GATE) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
    default:
        return MAPSECTYPE_ROUTE;
    }
}

u16 GetRegionMapSecIdAt(u16 x, u16 y)
{
    return GetMapSecIdAt(x, y);
}

static u16 CorrectSpecialMapSecId_Internal(u16 mapSecId)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sMarineCaveMapSecIds); i++)
    {
        if (sMarineCaveMapSecIds[i] == mapSecId)
        {
            return GetTerraOrMarineCaveMapSecId();
        }
    }
    for (i = 0; sRegionMap_SpecialPlaceLocations[i][0] != MAPSEC_NONE; i++)
    {
        if (sRegionMap_SpecialPlaceLocations[i][0] == mapSecId)
        {
            return sRegionMap_SpecialPlaceLocations[i][1];
        }
    }
    return mapSecId;
}

static u16 GetTerraOrMarineCaveMapSecId(void)
{
    s16 idx;

    idx = VarGet(VAR_ABNORMAL_WEATHER_LOCATION) - 1;

    if (idx < 0 || idx > ABNORMAL_WEATHER_LOCATIONS - 1)
        idx = 0;

    return sTerraOrMarineCaveMapSecIds[idx];
}

static void GetMarineCaveCoords(u16 *x, u16 *y)
{
    u16 idx;

    idx = VarGet(VAR_ABNORMAL_WEATHER_LOCATION);
    if (idx < MARINE_CAVE_LOCATIONS_START || idx > ABNORMAL_WEATHER_LOCATIONS)
    {
        idx = MARINE_CAVE_LOCATIONS_START;
    }
    idx -= MARINE_CAVE_LOCATIONS_START;

    *x = sMarineCaveLocationCoords[idx].x + MAPCURSOR_X_MIN;
    *y = sMarineCaveLocationCoords[idx].y + MAPCURSOR_Y_MIN;
}

// Probably meant to be an "IsPlayerInIndoorDungeon" function, but in practice it only has the one mapsec
// Additionally, because the mapsec doesnt exist in Emerald, this function always returns FALSE
static bool32 IsPlayerInAquaHideout(u8 mapSecId)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sMapSecAquaHideoutOld); i++)
    {
        if (sMapSecAquaHideoutOld[i] == mapSecId)
            return TRUE;
    }
    return FALSE;
}

u16 CorrectSpecialMapSecId(u16 mapSecId)
{
    return CorrectSpecialMapSecId_Internal(mapSecId);
}

static void GetPositionOfCursorWithinMapSec(void)
{
    u16 x;
    u16 y;
    u16 posWithinMapSec;

    if (sRegionMap->mapSecId == MAPSEC_NONE)
    {
        sRegionMap->posWithinMapSec = 0;
        return;
    }
    if (!sRegionMap->zoomed)
    {
        x = sRegionMap->cursorPosX;
        y = sRegionMap->cursorPosY;
    }
    else
    {
        x = sRegionMap->zoomedCursorPosX;
        y = sRegionMap->zoomedCursorPosY;
    }
    posWithinMapSec = 0;
    while (1)
    {
        if (x <= MAPCURSOR_X_MIN)
        {
            if (RegionMap_IsMapSecIdInNextRow(y))
            {
                y--;
                x = MAPCURSOR_X_MAX + 1;
            }
            else
            {
                break;
            }
        }
        else
        {
            x--;
            if (GetMapSecIdAt(x, y) == sRegionMap->mapSecId)
            {
                posWithinMapSec++;
            }
        }
    }
    sRegionMap->posWithinMapSec = posWithinMapSec;
}

static bool8 RegionMap_IsMapSecIdInNextRow(u16 y)
{
    u16 x;

    if (y-- == 0)
    {
        return FALSE;
    }
    for (x = MAPCURSOR_X_MIN; x <= MAPCURSOR_X_MAX; x++)
    {
        if (GetMapSecIdAt(x, y) == sRegionMap->mapSecId)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static void SpriteCB_CursorMapFull(struct Sprite *sprite)
{
    if (sRegionMap->cursorMovementFrameCounter != 0)
    {
        sprite->x += 2 * sRegionMap->cursorDeltaX;
        sprite->y += 2 * sRegionMap->cursorDeltaY;
        sRegionMap->cursorMovementFrameCounter--;
    }
}

static void SpriteCB_CursorMapZoomed(struct Sprite *sprite)
{

}

void CreateRegionMapCursor(u16 tileTag, u16 paletteTag)
{
    u8 spriteId;
    struct SpriteTemplate template;
    struct SpritePalette palette;
    struct SpriteSheet sheet;

    palette = sRegionMapCursorSpritePalette;
    template = sRegionMapCursorSpriteTemplate;
    sheet.tag = tileTag;
    template.tileTag = tileTag;
    sRegionMap->cursorTileTag = tileTag;
    palette.tag = paletteTag;
    template.paletteTag = paletteTag;
    sRegionMap->cursorPaletteTag = paletteTag;
    if (!sRegionMap->zoomed)
    {
        sheet.data = sRegionMap->cursorSmallImage;
        sheet.size = sizeof(sRegionMap->cursorSmallImage);
        template.callback = SpriteCB_CursorMapFull;
    }
    else
    {
        sheet.data = sRegionMap->cursorLargeImage;
        sheet.size = sizeof(sRegionMap->cursorLargeImage);
        template.callback = SpriteCB_CursorMapZoomed;
    }
    LoadSpriteSheet(&sheet);
    LoadSpritePalette(&palette);
    spriteId = CreateSprite(&template, 0x38, 0x48, 0);
    if (spriteId != MAX_SPRITES)
    {
        sRegionMap->cursorSprite = &gSprites[spriteId];
        if (sRegionMap->zoomed == TRUE)
        {
            sRegionMap->cursorSprite->oam.size = SPRITE_SIZE(32x32);
            sRegionMap->cursorSprite->x -= 8;
            sRegionMap->cursorSprite->y -= 8;
            StartSpriteAnim(sRegionMap->cursorSprite, 1);
        }
        else
        {
            sRegionMap->cursorSprite->oam.size = SPRITE_SIZE(16x16);
            sRegionMap->cursorSprite->x = 8 * sRegionMap->cursorPosX + 4;
            sRegionMap->cursorSprite->y = 8 * sRegionMap->cursorPosY + 4;
        }
        sRegionMap->cursorSprite->data[1] = 2;
        sRegionMap->cursorSprite->data[2] = OBJ_PLTT_ID(IndexOfSpritePaletteTag(paletteTag)) + 1;
        sRegionMap->cursorSprite->data[3] = TRUE;
    }
}

static void FreeRegionMapCursorSprite(void)
{
    if (sRegionMap->cursorSprite != NULL)
    {
        DestroySprite(sRegionMap->cursorSprite);
        FreeSpriteTilesByTag(sRegionMap->cursorTileTag);
        FreeSpritePaletteByTag(sRegionMap->cursorPaletteTag);
    }
}

static void UNUSED SetUnkCursorSpriteData(void)
{
    sRegionMap->cursorSprite->data[3] = TRUE;
}

static void UNUSED ClearUnkCursorSpriteData(void)
{
    sRegionMap->cursorSprite->data[3] = FALSE;
}

void CreateRegionMapPlayerIcon(u16 tileTag, u16 paletteTag)
{
    u8 spriteId;
    struct SpriteSheet sheet = {sRegionMapPlayerIcon_BrendanGfx, 0x80, tileTag};
    struct SpritePalette palette = {sRegionMapPlayerIcon_BrendanPal, paletteTag};
    struct SpriteTemplate template = {tileTag, paletteTag, &sRegionMapPlayerIconOam, sRegionMapPlayerIconAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy};

    if (IsEventIslandMapSecId(gMapHeader.regionMapSectionId))
    {
        sRegionMap->playerIconSprite = NULL;
        return;
    }
    if (gSaveBlock2Ptr->playerGender == FEMALE)
    {
        sheet.data = sRegionMapPlayerIcon_MayGfx;
        palette.data = sRegionMapPlayerIcon_MayPal;
    }
    LoadSpriteSheet(&sheet);
    LoadSpritePalette(&palette);
    spriteId = CreateSprite(&template, 0, 0, 1);
    sRegionMap->playerIconSprite = &gSprites[spriteId];
    if (!sRegionMap->zoomed)
    {
        sRegionMap->playerIconSprite->x = sRegionMap->playerIconSpritePosX * 8 + 4;
        sRegionMap->playerIconSprite->y = sRegionMap->playerIconSpritePosY * 8 + 4;
        sRegionMap->playerIconSprite->callback = SpriteCB_PlayerIconMapFull;
    }
    else
    {
        sRegionMap->playerIconSprite->x = sRegionMap->playerIconSpritePosX * 16 - 0x30;
        sRegionMap->playerIconSprite->y = sRegionMap->playerIconSpritePosY * 16 - 0x42;
        sRegionMap->playerIconSprite->callback = SpriteCB_PlayerIconMapZoomed;
    }
}

static void HideRegionMapPlayerIcon(void)
{
    if (sRegionMap->playerIconSprite != NULL)
    {
        sRegionMap->playerIconSprite->invisible = TRUE;
        sRegionMap->playerIconSprite->callback = SpriteCallbackDummy;
    }
}

static void UnhideRegionMapPlayerIcon(void)
{
    if (sRegionMap->playerIconSprite != NULL)
    {
        if (sRegionMap->zoomed == TRUE)
        {
            sRegionMap->playerIconSprite->x = sRegionMap->playerIconSpritePosX * 16 - 0x30;
            sRegionMap->playerIconSprite->y = sRegionMap->playerIconSpritePosY * 16 - 0x42;
            sRegionMap->playerIconSprite->callback = SpriteCB_PlayerIconMapZoomed;
            sRegionMap->playerIconSprite->invisible = FALSE;
        }
        else
        {
            sRegionMap->playerIconSprite->x = sRegionMap->playerIconSpritePosX * 8 + 4;
            sRegionMap->playerIconSprite->y = sRegionMap->playerIconSpritePosY * 8 + 4;
            sRegionMap->playerIconSprite->x2 = 0;
            sRegionMap->playerIconSprite->y2 = 0;
            sRegionMap->playerIconSprite->callback = SpriteCB_PlayerIconMapFull;
            sRegionMap->playerIconSprite->invisible = FALSE;
        }
    }
}

#define sY       data[0]
#define sX       data[1]
#define sVisible data[2]
#define sTimer   data[7]

static void SpriteCB_PlayerIconMapZoomed(struct Sprite *sprite)
{
    sprite->x2 = -2 * sRegionMap->scrollX;
    sprite->y2 = -2 * sRegionMap->scrollY;
    sprite->sY = sprite->y + sprite->y2 + sprite->centerToCornerVecY;
    sprite->sX = sprite->x + sprite->x2 + sprite->centerToCornerVecX;
    if (sprite->sY < -8 || sprite->sY > DISPLAY_HEIGHT + 8 || sprite->sX < -8 || sprite->sX > DISPLAY_WIDTH + 8)
        sprite->sVisible = FALSE;
    else
        sprite->sVisible = TRUE;

    if (sprite->sVisible == TRUE)
        SpriteCB_PlayerIcon(sprite);
    else
        sprite->invisible = TRUE;
}

static void SpriteCB_PlayerIconMapFull(struct Sprite *sprite)
{
    SpriteCB_PlayerIcon(sprite);
}

static void SpriteCB_PlayerIcon(struct Sprite *sprite)
{
    if (sRegionMap->blinkPlayerIcon)
    {
        if (++sprite->sTimer > 16)
        {
            sprite->sTimer = 0;
            sprite->invisible = sprite->invisible ? FALSE : TRUE;
        }
    }
    else
    {
        sprite->invisible = FALSE;
    }
}

void TrySetPlayerIconBlink(void)
{
    if (sRegionMap->playerIsInCave)
        sRegionMap->blinkPlayerIcon = TRUE;
}

#undef sY
#undef sX
#undef sVisible
#undef sTimer

u8 *GetMapName(u8 *dest, u16 regionMapId, u16 padLength)
{
    // SAFE: if no Region Map UI has selected a variant yet, fall back to combined table.
    const struct RegionMapLocation *tbl =
        (sActiveEntries != NULL) ? sActiveEntries : gRegionMapEntries;

    u8 *str;

    if (regionMapId == MAPSEC_SECRET_BASE)
    {
        str = GetSecretBaseMapName(dest);
    }
    else if (regionMapId < MAPSEC_NONE)
    {
        str = StringCopy(dest, tbl[regionMapId].name);
    }
    else
    {
        if (padLength == 0) padLength = 18;
        return StringFill(dest, CHAR_SPACE, padLength);
    }

    if (padLength != 0)
    {
        u16 i;
        for (i = str - dest; i < padLength; i++)
            *str++ = CHAR_SPACE;
        *str = EOS;
    }
    return str;
}



// TODO: probably needs a better name
u8 *GetMapNameGeneric(u8 *dest, u16 mapSecId)
{
    switch (mapSecId)
    {
    case MAPSEC_DYNAMIC:
        return StringCopy(dest, gText_Ferry);
    case MAPSEC_SECRET_BASE:
        return StringCopy(dest, gText_SecretBase);
    default:
        return GetMapName(dest, mapSecId, 0);
    }
}

u8 *GetMapNameHandleAquaHideout(u8 *dest, u16 mapSecId)
{
    if (mapSecId == MAPSEC_AQUA_HIDEOUT_OLD)
        return StringCopy(dest, gText_Hideout);
    else
        return GetMapNameGeneric(dest, mapSecId);
}

static void GetMapSecDimensions(u16 mapSecId, u16 *x, u16 *y, u16 *width, u16 *height)
{
    GetMapSecRectFromLayout(mapSecId, x, y, width, height);
}

bool8 IsRegionMapZoomed(void)
{
    return sRegionMap->zoomed;
}

bool32 IsEventIslandMapSecId(u8 mapSecId)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sMapSecIdsOffMap); i++)
    {
        if (mapSecId == sMapSecIdsOffMap[i])
            return TRUE;
    }
    return FALSE;
}

void CB2_OpenFlyMap(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG3HOFS, 0);
        SetGpuReg(REG_OFFSET_BG3VOFS, 0);
        sFlyMap = Alloc(sizeof(*sFlyMap));
        if (sFlyMap == NULL)
        {
            SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
        }
        else
        {
            ResetPaletteFade();
            ResetSpriteData();
            FreeSpriteTileRanges();
            FreeAllSpritePalettes();
            gMain.state++;
        }
        break;
    case 1:
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(1, sFlyMapBgTemplates, ARRAY_COUNT(sFlyMapBgTemplates));
        gMain.state++;
        break;
    case 2:
        InitWindows(sFlyMapWindowTemplates);
        DeactivateAllTextPrinters();
        gMain.state++;
        break;
    case 3:
        LoadUserWindowBorderGfx(0, 0x65, BG_PLTT_ID(13));
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 4:
        InitRegionMap(&sFlyMap->regionMap, FALSE);
        CreateRegionMapCursor(TAG_CURSOR, TAG_CURSOR);
        CreateRegionMapPlayerIcon(TAG_PLAYER_ICON, TAG_PLAYER_ICON);
        sFlyMap->mapSecId = sFlyMap->regionMap.mapSecId;
        StringFill(sFlyMap->nameBuffer, CHAR_SPACE, MAP_NAME_LENGTH);
        sDrawFlyDestTextWindow = TRUE;
        DrawFlyDestTextWindow();
        gMain.state++;
        break;
    case 5:
        LZ77UnCompVram(sRegionMapFrameGfxLZ, (u16 *)BG_CHAR_ADDR(3));
        gMain.state++;
        break;
    case 6:
        LZ77UnCompVram(sRegionMapFrameTilemapLZ, (u16 *)BG_SCREEN_ADDR(30));
        gMain.state++;
        break;
    case 7:
        LoadPalette(sRegionMapFramePal, BG_PLTT_ID(1), sizeof(sRegionMapFramePal));
        PutWindowTilemap(2);
        FillWindowPixelBuffer(2, PIXEL_FILL(0));
        AddTextPrinterParameterized(2, FONT_NORMAL, gText_FlyToWhere, 0, 1, 0, NULL);
        ScheduleBgCopyTilemapToVram(0);
        gMain.state++;
        break;
    case 8:
        LoadFlyDestIcons();
        gMain.state++;
        break;
    case 9:
        BlendPalettes(PALETTES_ALL, 16, 0);
        SetVBlankCallback(VBlankCB_FlyMap);
        gMain.state++;
        break;
    case 10:
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        SetFlyMapCallback(CB_FadeInFlyMap);
        SetMainCallback2(CB2_FlyMap);
        gMain.state++;
        break;
    }
}

static void VBlankCB_FlyMap(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_FlyMap(void)
{
    sFlyMap->callback();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
}

static void SetFlyMapCallback(void callback(void))
{
    sFlyMap->callback = callback;
    sFlyMap->state = 0;
}

static void DrawFlyDestTextWindow(void)
{
    u16 i;
    bool32 namePrinted;
    const u8 *name;

    if (sFlyMap->regionMap.mapSecType > MAPSECTYPE_NONE && sFlyMap->regionMap.mapSecType <= MAPSECTYPE_BATTLE_FRONTIER)
    {
        namePrinted = FALSE;
        for (i = 0; i < ARRAY_COUNT(sMultiNameFlyDestinations); i++)
        {
            if (sFlyMap->regionMap.mapSecId == sMultiNameFlyDestinations[i].mapSecId)
            {
                if (FlagGet(sMultiNameFlyDestinations[i].flag))
                {
                    StringLength(sMultiNameFlyDestinations[i].name[sFlyMap->regionMap.posWithinMapSec]);
                    namePrinted = TRUE;
                    ClearStdWindowAndFrameToTransparent(0, FALSE);
                    DrawStdFrameWithCustomTileAndPalette(1, FALSE, 101, 13);
                    AddTextPrinterParameterized(1, FONT_NORMAL, sFlyMap->regionMap.mapSecName, 0, 1, 0, NULL);
                    name = sMultiNameFlyDestinations[i].name[sFlyMap->regionMap.posWithinMapSec];
                    AddTextPrinterParameterized(1, FONT_NORMAL, name, GetStringRightAlignXOffset(FONT_NORMAL, name, 96), 17, 0, NULL);
                    ScheduleBgCopyTilemapToVram(0);
                    sDrawFlyDestTextWindow = TRUE;
                }
                break;
            }
        }
        if (!namePrinted)
        {
            if (sDrawFlyDestTextWindow == TRUE)
            {
                ClearStdWindowAndFrameToTransparent(1, FALSE);
                DrawStdFrameWithCustomTileAndPalette(0, FALSE, 101, 13);
            }
            else
            {
                // Window is already drawn, just empty it
                FillWindowPixelBuffer(0, PIXEL_FILL(1));
            }
            AddTextPrinterParameterized(0, FONT_NORMAL, sFlyMap->regionMap.mapSecName, 0, 1, 0, NULL);
            ScheduleBgCopyTilemapToVram(0);
            sDrawFlyDestTextWindow = FALSE;
        }
    }
    else
    {
        // Selection is on MAPSECTYPE_NONE, draw empty fly destination text window
        if (sDrawFlyDestTextWindow == TRUE)
        {
            ClearStdWindowAndFrameToTransparent(1, FALSE);
            DrawStdFrameWithCustomTileAndPalette(0, FALSE, 101, 13);
        }
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        CopyWindowToVram(0, COPYWIN_GFX);
        ScheduleBgCopyTilemapToVram(0);
        sDrawFlyDestTextWindow = FALSE;
    }
}


static void LoadFlyDestIcons(void)
{
    ChooseMapVariant();
    struct SpriteSheet sheet;

    LZ77UnCompWram(sFlyTargetIcons_Gfx, sFlyMap->tileBuffer);
    sheet.data = sFlyMap->tileBuffer;
    sheet.size = sizeof(sFlyMap->tileBuffer);
    sheet.tag = TAG_FLY_ICON;
    LoadSpriteSheet(&sheet);
    LoadSpritePalette(&sFlyTargetIconsSpritePalette);
    CreateFlyDestIcons();
    TryCreateRedOutlineFlyDestIcons();
}

// Sprite data for SpriteCB_FlyDestIcon
#define sIconMapSec   data[0]
#define sFlickerTimer data[1]

static void CreateFlyDestIcons(void)
{
    ChooseMapVariant();
    const struct FlyDest *list = FlagGet(FLAG_VISITED_KANTO) ? sFlyDests_JK : sFlyDests_Johto;

    for (u16 i = 0; list[i].mapSec != MAPSEC_NONE; i++)
    {
        u16 mapSecId = list[i].mapSec;
        u16 x, y, width, height;
        u16 shape;
        u8 spriteId;

        GetMapSecDimensions(mapSecId, &x, &y, &width, &height);
        x = (x + MAPCURSOR_X_MIN) * 8 + 4;
        y = (y + MAPCURSOR_Y_MIN) * 8 + 4;

        if (width == 2)       shape = SPRITE_SHAPE(16x8);
        else if (height == 2) shape = SPRITE_SHAPE(8x16);
        else                  shape = SPRITE_SHAPE(8x8);

        spriteId = CreateSprite(&sFlyDestIconSpriteTemplate, x, y, 10);
        if (spriteId != MAX_SPRITES)
        {
            gSprites[spriteId].oam.shape = shape;
            if (FlagGet(list[i].flag))
                gSprites[spriteId].callback = SpriteCB_FlyDestIcon;
            else
                shape += 3;

            StartSpriteAnim(&gSprites[spriteId], shape);
            gSprites[spriteId].sIconMapSec = mapSecId;
        }
    }
}


// Draw a red outline box on the mapsec if its corresponding flag has been set
// Only used for Battle Frontier, but set up to handle more
static void TryCreateRedOutlineFlyDestIcons(void)
{
    u16 i;
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 mapSecId;
    u8 spriteId;

    for (i = 0; sRedOutlineFlyDestinations[i][1] != MAPSEC_NONE; i++)
    {
        if (FlagGet(sRedOutlineFlyDestinations[i][0]))
        {
            mapSecId = sRedOutlineFlyDestinations[i][1];
            GetMapSecDimensions(mapSecId, &x, &y, &width, &height);
            x = (x + MAPCURSOR_X_MIN) * 8;
            y = (y + MAPCURSOR_Y_MIN) * 8;
            spriteId = CreateSprite(&sFlyDestIconSpriteTemplate, x, y, 10);
            if (spriteId != MAX_SPRITES)
            {
                gSprites[spriteId].oam.size = SPRITE_SIZE(16x16);
                gSprites[spriteId].callback = SpriteCB_FlyDestIcon;
                StartSpriteAnim(&gSprites[spriteId], FLYDESTICON_RED_OUTLINE);
                gSprites[spriteId].sIconMapSec = mapSecId;
            }
        }
    }
}

// Flickers fly destination icon color (by hiding the fly icon sprite) if the cursor is currently on it
static void SpriteCB_FlyDestIcon(struct Sprite *sprite)
{
    if (sFlyMap->regionMap.mapSecId == sprite->sIconMapSec)
    {
        if (++sprite->sFlickerTimer > 16)
        {
            sprite->sFlickerTimer = 0;
            sprite->invisible = sprite->invisible ? FALSE : TRUE;
        }
    }
    else
    {
        sprite->sFlickerTimer = 16;
        sprite->invisible = FALSE;
    }
}

#undef sIconMapSec
#undef sFlickerTimer

static void CB_FadeInFlyMap(void)
{
    switch (sFlyMap->state)
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        sFlyMap->state++;
        break;
    case 1:
        if (!UpdatePaletteFade())
        {
            SetFlyMapCallback(CB_HandleFlyMapInput);
        }
        break;
    }
}

static void CB_HandleFlyMapInput(void)
{
    if (sFlyMap->state == 0)
    {
        switch (DoRegionMapInputCallback())
        {
        case MAP_INPUT_NONE:
        case MAP_INPUT_MOVE_START:
        case MAP_INPUT_MOVE_CONT:
            break;
        case MAP_INPUT_MOVE_END:
            DrawFlyDestTextWindow();
            break;
        case MAP_INPUT_A_BUTTON:
            if (sFlyMap->regionMap.mapSecType == MAPSECTYPE_CITY_CANFLY || sFlyMap->regionMap.mapSecType == MAPSECTYPE_BATTLE_FRONTIER)
            {
                m4aSongNumStart(SE_SELECT);
                sFlyMap->choseFlyLocation = TRUE;
                SetFlyMapCallback(CB_ExitFlyMap);
            }
            break;
        case MAP_INPUT_B_BUTTON:
            m4aSongNumStart(SE_SELECT);
            sFlyMap->choseFlyLocation = FALSE;
            SetFlyMapCallback(CB_ExitFlyMap);
            break;
        }
    }
}

static void CB_ExitFlyMap(void)
{
    switch (sFlyMap->state)
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        sFlyMap->state++;
        break;
    case 1:
        if (!UpdatePaletteFade())
        {
            FreeRegionMapIconResources();
            if (sFlyMap->choseFlyLocation)
            {
                switch (sFlyMap->regionMap.mapSecId)
                {
                case MAPSEC_SOUTHERN_ISLAND:
                    SetWarpDestinationToHealLocation(HEAL_LOCATION_SOUTHERN_ISLAND_EXTERIOR);
                    break;
                case MAPSEC_BATTLE_FRONTIER:
                    SetWarpDestinationToHealLocation(HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST);
                    break;
                case MAPSEC_NEW_BARK_TOWN:
                    SetWarpDestinationToHealLocation(HEAL_LOCATION_NEW_BARK_TOWN);
                    break;
                case MAPSEC_INDIGO_PLATEAU:
                    SetWarpDestinationToHealLocation(HEAL_LOCATION_INDIGO_PLATEAU);
                    break;
                default:
                    if (sMapHealLocations[sFlyMap->regionMap.mapSecId][2] != HEAL_LOCATION_NONE)
                        SetWarpDestinationToHealLocation(sMapHealLocations[sFlyMap->regionMap.mapSecId][2]);
                    else
                        SetWarpDestinationToMapWarp(sMapHealLocations[sFlyMap->regionMap.mapSecId][0], sMapHealLocations[sFlyMap->regionMap.mapSecId][1], WARP_ID_NONE);
                    break;
                }
                ReturnToFieldFromFlyMapSelect();
            }
            else
            {
                SetMainCallback2(CB2_ReturnToPartyMenuFromFlyMap);
            }
            TRY_FREE_AND_SET_NULL(sFlyMap);
            FreeAllWindowBuffers();
        }
        break;
    }
}

// added 7/23/21, luma~
u8* GetMapName_HandleVersion(u8* dest, u16 mapsec, u8 version) {
	switch (version)
    {
	default:
		if ((mapsec & 255) == METLOC_SPECIAL_EGG) {
			return StringCopy(dest, gRegionMapEntries[214].name);
		}
		else if ((mapsec & 255) == METLOC_IN_GAME_TRADE) {
			return StringCopy(dest, gRegionMapEntries[215].name);
		}
		else if ((mapsec & 255) == METLOC_FATEFUL_ENCOUNTER) {
			return StringCopy(dest, gRegionMapEntries[216].name);
		}
		else {
			return GetMapNameGeneric(dest, mapsec & 255);
		}
		// TODO: expand R/S Aqua Hideout placeholder
	case 1 ... 6: // R/S/E/FR/LG/WB
		if (mapsec == 253) {
			return StringCopy(dest, gRegionMapEntries[214].name);
		}
		else if (mapsec == 254) {
			return StringCopy(dest, gRegionMapEntries[215].name);
		}
		else if (mapsec == 255) {
			return StringCopy(dest, gRegionMapEntries[216].name);
		}
		else if (mapsec < 213) {
			return StringCopy(dest, gRegionMapEntries[mapsec].name);
		}
		// TODO: expand R/S Aqua Hideout placeholder
    }
}
