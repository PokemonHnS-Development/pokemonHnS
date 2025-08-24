#include "global.h"
#include "main.h"
#include "menu.h"
#include "bg.h"
#include "malloc.h"
#include "palette.h"
#include "pokedex_area_region_map.h"
#include "constants/flags.h"
#include "event_data.h"

static EWRAM_DATA u8 *sPokedexAreaMapBgNum = NULL;

static const u16 ALIGNED(4) sPokedexAreaMap_Pal[] = INCBIN_U16("graphics/pokedex/region_map.gbapal");
static const u32 sPokedexAreaMap_Gfx[] = INCBIN_U32("graphics/pokedex/region_map.8bpp.lz");
static const u32 sPokedexAreaMap_Tilemap[] = INCBIN_U32("graphics/pokedex/region_map.bin.lz");
static const u32 sPokedexAreaMapAffine_Gfx[] = INCBIN_U32("graphics/pokedex/region_map_affine.8bpp.lz");
static const u32 sPokedexAreaMapAffine_Tilemap[] = INCBIN_U32("graphics/pokedex/region_map_affine.bin.lz");
static const u32 sPokedexAreaMap_Gfx_Johto[]     = INCBIN_U32("graphics/pokedex/johto_region_map.8bpp.lz");
static const u32 sPokedexAreaMap_Tilemap_Johto[] = INCBIN_U32("graphics/pokedex/johto_region_map.bin.lz");

void LoadPokedexAreaMapGfx(const struct PokedexAreaMapTemplate *template)
{
    u8 mode;
    void * tilemap;
    const u32 *gfx, *tile;         // NEW
    const u16 *pal = sPokedexAreaMap_Pal; // or sPokedexAreaMap_Pal_Johto if you have one

    sPokedexAreaMapBgNum = Alloc(sizeof(sPokedexAreaMapBgNum));
    mode = template->mode;

    if (FlagGet(FLAG_VISITED_KANTO))
    {
        gfx  = sPokedexAreaMap_Gfx;       // existing combined art
        tile = sPokedexAreaMap_Tilemap;
        // pal = sPokedexAreaMap_Pal;     // keep or swap if you have a JK-specific palette
    }
    else
    {
        gfx  = sPokedexAreaMap_Gfx_Johto;     // NEW Johto art
        tile = sPokedexAreaMap_Tilemap_Johto;
    }
    if (mode == 0)
    {
        SetBgAttribute(template->bg, BG_ATTR_METRIC, 0);
        DecompressAndCopyTileDataToVram(template->bg, gfx, 0, template->offset, 0);    // use gfx
        tilemap = DecompressAndCopyTileDataToVram(template->bg, tile, 0, 0, 1);        // use tile
        AddValToTilemapBuffer(tilemap, template->offset, 32, 32, FALSE);
    }
    else
    {
        // This is never reached, only a mode of 0 is given
        SetBgAttribute(template->bg, BG_ATTR_METRIC, 2);
        SetBgAttribute(template->bg, BG_ATTR_TYPE, BG_TYPE_AFFINE);
        DecompressAndCopyTileDataToVram(template->bg, gfx, 0, template->offset, 0);
        tilemap = DecompressAndCopyTileDataToVram(template->bg, tile, 0, 0, 1);
        AddValToTilemapBuffer(tilemap, template->offset, 64, 64, TRUE);
    }

    ChangeBgX(template->bg, 0, BG_COORD_SET);
    ChangeBgY(template->bg, 0, BG_COORD_SET);
    SetBgAttribute(template->bg, BG_ATTR_PALETTEMODE, 1);
    CpuCopy32(pal, &gPlttBufferUnfaded[BG_PLTT_ID(7)], sizeof(sPokedexAreaMap_Pal)); // or sizeof(*pal-set)
    *sPokedexAreaMapBgNum = template->bg;
}

bool32 TryShowPokedexAreaMap(void)
{
    if (!FreeTempTileDataBuffersIfPossible())
    {
        ShowBg(*sPokedexAreaMapBgNum);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void FreePokedexAreaMapBgNum(void)
{
    TRY_FREE_AND_SET_NULL(sPokedexAreaMapBgNum);
}

void PokedexAreaMapChangeBgY(u32 move)
{
    ChangeBgY(*sPokedexAreaMapBgNum, move * 0x100, BG_COORD_SET);
}
