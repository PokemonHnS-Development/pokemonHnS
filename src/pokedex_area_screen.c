#include "global.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "pokedex.h"
#include "pokedex_area_screen.h"
#include "region_map.h"
#include "roamer.h"
#include "sound.h"
#include "string_util.h"
#include "trig.h"
#include "pokedex_area_region_map.h"
#include "wild_encounter.h"
#include "constants/region_map_sections.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/flags.h"

#define MAP_WIDTH 28
#define MAP_HEIGHT 15
#define MAPCURSOR_X_MIN 1
#define MAPCURSOR_Y_MIN 2
#define MAPCURSOR_X_MAX (MAPCURSOR_X_MIN + MAP_WIDTH - 1)
#define MAPCURSOR_Y_MAX (MAPCURSOR_Y_MIN + MAP_HEIGHT - 1)

#include "data/region_map/region_map_layout.h"         // combined JK layout: sRegionMap_MapSectionLayout
#include "data/region_map/region_map_layout_johto.h"   // johto-only layout: sRegionMap_MapSectionLayout_Johto

// There are two types of indicators for the area screen to show where a Pokémon can occur:
// - Area glows, which highlight any of the maps in MAP_GROUP_TOWNS_AND_ROUTES that have the species.
//   These are a tilemap with colored rectangular areas that blends in and out. The positions of the
//   rectangles is determined by the positions of the matching MAPSEC values on the region map layout.
// - Area markers, which highlight any of the maps in MAP_GROUP_DUNGEONS or MAP_GROUP_SPECIAL_AREA that
//   have the species. These are circular sprites that flash twice. The positions of the sprites is
//   determined by the data for the corresponding MAPSEC in gRegionMapEntries.

// Only maps in the following map groups have their encounters considered for the area screen
#define MAP_GROUP_TOWNS_AND_ROUTES MAP_GROUP(NEW_BARK_TOWN)
#define MAP_GROUP_DUNGEONS MAP_GROUP(DARK_CAVE_SOUTH_SIDE)
#define MAP_GROUP_SPECIAL_AREA MAP_GROUP(SAFARI_ZONE_TOP_LEFT)

#define AREA_SCREEN_WIDTH 32
#define AREA_SCREEN_HEIGHT 20

#define GLOW_FULL      0xFFFF
#define GLOW_EDGE_R    (1 << 0)
#define GLOW_EDGE_L    (1 << 1)
#define GLOW_EDGE_B    (1 << 2)
#define GLOW_EDGE_T    (1 << 3)
#define GLOW_CORNER_TL (1 << 4)
#define GLOW_CORNER_BL (1 << 5)
#define GLOW_CORNER_TR (1 << 6)
#define GLOW_CORNER_BR (1 << 7)

#define GLOW_PALETTE 10

#define TAG_AREA_MARKER 2
#define TAG_AREA_UNKNOWN 3

#define MAX_AREA_HIGHLIGHTS 64 // Maximum number of rectangular route highlights
#define MAX_AREA_MARKERS 32 // Maximum number of circular spot highlights

struct OverworldArea
{
    u8 mapGroup;
    u8 mapNum;
    u16 regionMapSectionId;
};

struct
{
    /*0x000*/ void (*callback)(void); // unused
    /*0x004*/ MainCallback prev; // unused
    /*0x008*/ MainCallback next; // unused
    /*0x00C*/ u16 state; // unused
    /*0x00E*/ u16 species;
    /*0x010*/ struct OverworldArea overworldAreasWithMons[MAX_AREA_HIGHLIGHTS];
    /*0x110*/ u16 numOverworldAreas;
    /*0x112*/ u16 numSpecialAreas;
    /*0x114*/ u16 drawAreaGlowState;
    /*0x116*/ u16 areaGlowTilemap[AREA_SCREEN_WIDTH * AREA_SCREEN_HEIGHT];
    /*0x616*/ u16 markerTimer;
    /*0x618*/ u16 glowTimer;
    /*0x61A*/ u16 areaShadeBldArgLo;
    /*0x61C*/ u16 areaShadeBldArgHi;
    /*0x61E*/ bool8 showingMarkers;
    /*0x61F*/ u8 markerFlashCounter;
    /*0x620*/ u16 specialAreaRegionMapSectionIds[MAX_AREA_MARKERS];
    /*0x660*/ struct Sprite *areaMarkerSprites[MAX_AREA_MARKERS];
    /*0x6E0*/ u16 numAreaMarkerSprites;
    /*0x6E2*/ u16 alteringCaveCounter;
    /*0x6E4*/ u16 alteringCaveId;
    /*0x6E6*/ u8 areaViewTimeMode;    // 0 = day, 1 = night
    /*0x6E7*/ u8 indDaySpriteId;      // sprite ID of the day-mode indicator (MAX_SPRITES = not created)
    /*0x6E8*/ u8 indNightSpriteId;    // sprite ID of the night-mode indicator
    /*0x6E9*/ u8 _pad6E9;             // alignment padding
    /*0x6EA*/ u16 _pad6EA;            // alignment padding
    /*0x6EC*/ u8 *screenSwitchState;
    /*0x6EC*/ struct RegionMap regionMap;
    /*0xF70*/ u8 charBuffer[64];
    /*0xFB0*/ struct Sprite * areaUnknownSprites[3];
    /*0xFBC*/ u8 areaUnknownGraphicsBuffer[0x600];
    // Cached encounter results for the *alternate* time mode so that toggling
    // day↔night is a fast array swap rather than a full header re-scan.
    // Populated once during DrawAreaGlow and kept live across toggles.
    /*0x15BC*/ struct OverworldArea overworldAreasWithMons_alt[MAX_AREA_HIGHLIGHTS];
    /*0x16BC*/ u16 numOverworldAreas_alt;
    /*0x16BE*/ u16 specialAreaRegionMapSectionIds_alt[MAX_AREA_MARKERS];
    /*0x16FE*/ u16 numSpecialAreas_alt;
    // Pre-built glow tilemap for the alternate time mode, swapped on toggle
    // so BuildAreaGlowTilemap is never called in the hot toggle path.
    /*0x1700*/ u16 areaGlowTilemap_alt[AREA_SCREEN_WIDTH * AREA_SCREEN_HEIGHT];
} static EWRAM_DATA *sPokedexAreaScreen = NULL;

// ApplyTimeModeToAreaMapPalette reads the untinted palette directly from ROM via
// GetPokedexAreaMapPal(), so no EWRAM cache is needed.

static void FindMapsWithMon(u16);
static void BuildAreaGlowTilemap(void);
static void SetAreaHasMon(u16, u16);
static void SetSpecialMapHasMon(u16, u16);
static u16 GetRegionMapSectionId(u8, u8);
static bool8 MapHasSpecies(const struct WildPokemonHeader *, u16);
static bool8 MonListHasSpecies(const struct WildPokemonInfo *, u16, u16);
static void DoAreaGlow(void);
static void Task_ShowPokedexAreaScreen(u8);
static void CreateAreaMarkerSprites(void);
static void LoadAreaUnknownGraphics(void);
static void CreateAreaUnknownSprites(void);
static void Task_HandlePokedexAreaScreenInput(u8);
static void ResetPokedexAreaMapBg(void);
static void DestroyAreaScreenSprites(void);
static void LoadHGSSScreenSelectBarSubmenu(void);
static void CreateAreaIndicatorSprites(void);
static void ContinueTimeModeRefresh(u8);
static void ApplyTimeModeToAreaMapPalette(void);

// Defined in src/script.c; refreshes VAR_TIME_BASED_ENCOUNTER from the RTC.
extern void SetTimeBasedEncounters(void);

static const u32 sAreaGlow_Pal[] = INCBIN_U32("graphics/pokedex/area_glow.gbapal");
static const u32 sAreaGlow_Gfx[] = INCBIN_U32("graphics/pokedex/area_glow.4bpp.lz");
static const u32 sPokedexPlusHGSS_ScreenSelectBarSubmenu_Tilemap[] = INCBIN_U32("graphics/pokedex/hgss/HGSS_SelectBar.bin.lz");

static const u16 sSpeciesHiddenFromAreaScreen[] = { SPECIES_WYNAUT };

// Return the region-map section at (x,y) tiles on the Pokédex area screen.
// Uses the same layout as the Pokédex art: flag set => combined; unset => johto.
static inline u16 DexGetMapSecAt(u16 x, u16 y)
{
    const bool32 isCombined = FlagGet(FLAG_VISITED_KANTO);
    const u8 (*grid)[MAP_WIDTH] = isCombined
        ? sRegionMap_MapSectionLayout
        : sRegionMap_MapSectionLayout_Johto;

    // Use a different X-origin for Johto (+1 tile), Y-origin is the same.
    const u16 originX = isCombined ? MAPCURSOR_X_MIN : (MAPCURSOR_X_MIN);
    const u16 originY = MAPCURSOR_Y_MIN;

    if (x < originX || x >= originX + MAP_WIDTH
     || y < originY || y >= originY + MAP_HEIGHT)
        return MAPSEC_NONE;

    return grid[y - originY][x - originX];
}

// Find the bounding box of a region-map section on the *active* Pokédex layout.
// Returns TRUE if the section exists on this layout.
static bool8 Dex_FindLayoutRect(u16 mapSecId, u16 *outX, u16 *outY, u16 *outW, u16 *outH)
{
    const bool32 isCombined = FlagGet(FLAG_VISITED_KANTO);
    const u8 (*grid)[MAP_WIDTH] = isCombined
        ? sRegionMap_MapSectionLayout          // combined JK layout
        : sRegionMap_MapSectionLayout_Johto;   // Johto-only layout

    u16 minx = MAP_WIDTH, miny = MAP_HEIGHT, maxx = 0, maxy = 0;
    bool8 found = FALSE;

    for (u16 y = 0; y < MAP_HEIGHT; y++)
        for (u16 x = 0; x < MAP_WIDTH; x++)
            if (grid[y][x] == mapSecId) {
                found = TRUE;
                if (x < minx) minx = x;
                if (y < miny) miny = y;
                if (x > maxx) maxx = x;
                if (y > maxy) maxy = y;
            }

    if (!found) return FALSE;

    *outX = minx;
    *outY = miny;
    *outW = (maxx - minx) + 1;
    *outH = (maxy - miny) + 1;
    return TRUE;
}

static const u16 sSpeciesHiddenFromAreaScreenModern[] = { 
   //SPECIES_BULBASAUR, 
   //SPECIES_IVYSAUR, 
   //SPECIES_VENUSAUR, 
   //SPECIES_CHARMANDER, 
   //SPECIES_CHARMELEON, 
   //SPECIES_CHARIZARD, 
   //SPECIES_SQUIRTLE, 
   //SPECIES_WARTORTLE, 
   //SPECIES_BLASTOISE, 
   //SPECIES_CATERPIE, 
   //SPECIES_METAPOD, 
   //SPECIES_BUTTERFREE, 
   //SPECIES_WEEDLE, 
   //SPECIES_KAKUNA, 
   //SPECIES_BEEDRILL, 
   //SPECIES_PIDGEY, 
   //SPECIES_PIDGEOTTO, 
   //SPECIES_PIDGEOT, 
   //SPECIES_RATTATA, 
   //SPECIES_RATICATE, 
   //SPECIES_SPEAROW, 
   //SPECIES_FEAROW, 
   //SPECIES_EKANS, 
   //SPECIES_ARBOK, 
    //SPECIES_PIKACHU, 
   //SPECIES_RAICHU, 
    //SPECIES_SANDSHREW, 
    //SPECIES_SANDSLASH, 
   //SPECIES_NIDORAN_F, 
   //SPECIES_NIDORINA, 
   //SPECIES_NIDOQUEEN, 
   //SPECIES_NIDORAN_M, 
   //SPECIES_NIDORINO, 
   //SPECIES_NIDOKING, 
   //SPECIES_CLEFAIRY, 
   //SPECIES_CLEFABLE, 
    //SPECIES_VULPIX, 
   //SPECIES_NINETALES, 
    //SPECIES_JIGGLYPUFF, 
   //SPECIES_WIGGLYTUFF, 
    //SPECIES_ZUBAT, 
    //SPECIES_GOLBAT, 
    //SPECIES_ODDISH, 
    //SPECIES_GLOOM, 
   //SPECIES_VILEPLUME, 
   //SPECIES_PARAS, 
   //SPECIES_PARASECT, 
   //SPECIES_VENONAT, 
   //SPECIES_VENOMOTH, 
   //SPECIES_DIGLETT, 
   //SPECIES_DUGTRIO, 
   //SPECIES_MEOWTH, 
   //SPECIES_PERSIAN, 
    //SPECIES_PSYDUCK, 
    //SPECIES_GOLDUCK, 
   //SPECIES_MANKEY, 
   //SPECIES_PRIMEAPE, 
   //SPECIES_GROWLITHE, 
   //SPECIES_ARCANINE, 
   //SPECIES_POLIWAG, 
   //SPECIES_POLIWHIRL, 
   //SPECIES_POLIWRATH, 
    //SPECIES_ABRA, 
    //SPECIES_KADABRA, 
   //SPECIES_ALAKAZAM, 
    //SPECIES_MACHOP, 
    //SPECIES_MACHOKE, 
    //SPECIES_MACHAMP, 
   //SPECIES_BELLSPROUT, 
   //SPECIES_WEEPINBELL, 
   //SPECIES_VICTREEBEL, 
    //SPECIES_TENTACOOL, 
    //SPECIES_TENTACRUEL, 
    //SPECIES_GEODUDE, 
    //SPECIES_GRAVELER, 
   //SPECIES_GOLEM, 
   //SPECIES_PONYTA, 
   //SPECIES_RAPIDASH, 
   //SPECIES_SLOWPOKE, 
   //SPECIES_SLOWBRO, 
    //SPECIES_MAGNEMITE, 
    //SPECIES_MAGNETON, 
   //SPECIES_FARFETCHD, 
    //SPECIES_DODUO, 
    //SPECIES_DODRIO, 
   //SPECIES_SEEL, 
   //SPECIES_DEWGONG, 
    //SPECIES_GRIMER, 
   //SPECIES_MUK, 
   //SPECIES_SHELLDER, 
   //SPECIES_CLOYSTER, 
   //SPECIES_GASTLY, 
   //SPECIES_HAUNTER, 
   //SPECIES_GENGAR, 
   //SPECIES_ONIX, 
   //SPECIES_DROWZEE, 
   //SPECIES_HYPNO, 
   //SPECIES_KRABBY, 
   //SPECIES_KINGLER, 
    //SPECIES_VOLTORB, 
    //SPECIES_ELECTRODE, 
   //SPECIES_EXEGGCUTE, 
   //SPECIES_EXEGGUTOR, 
   //SPECIES_CUBONE, 
   //SPECIES_MAROWAK, 
   //SPECIES_HITMONLEE, 
   //SPECIES_HITMONCHAN, 
   //SPECIES_LICKITUNG, 
    //SPECIES_KOFFING, 
   //SPECIES_WEEZING, 
    //SPECIES_RHYHORN, 
   //SPECIES_RHYDON, 
   //SPECIES_CHANSEY, 
   //SPECIES_TANGELA, 
   //SPECIES_KANGASKHAN, 
    //SPECIES_HORSEA, 
   //SPECIES_SEADRA, 
    //SPECIES_GOLDEEN, 
    //SPECIES_SEAKING, 
    //SPECIES_STARYU, 
   //SPECIES_STARMIE, 
   //SPECIES_MR_MIME, 
   //SPECIES_SCYTHER, 
   //SPECIES_JYNX, 
   //SPECIES_ELECTABUZZ, 
   //SPECIES_MAGMAR, 
    //SPECIES_PINSIR, 
   //SPECIES_TAUROS, 
    //SPECIES_MAGIKARP, 
    //SPECIES_GYARADOS, 
   //SPECIES_LAPRAS, 
    //SPECIES_DITTO, 
   //SPECIES_EEVEE, 
   //SPECIES_VAPOREON, 
   //SPECIES_JOLTEON, 
   //SPECIES_FLAREON, 
   //SPECIES_PORYGON, 
   //SPECIES_OMANYTE, 
   //SPECIES_OMASTAR, 
   //SPECIES_KABUTO, 
   //SPECIES_KABUTOPS, 
   //SPECIES_AERODACTYL, 
   //SPECIES_SNORLAX, 
   //SPECIES_ARTICUNO, 
   //SPECIES_ZAPDOS, 
   //SPECIES_MOLTRES, 
   //SPECIES_DRATINI, 
   //SPECIES_DRAGONAIR, 
   //SPECIES_DRAGONITE, 
   //SPECIES_CHIKORITA, 
   //SPECIES_BAYLEEF, 
   //SPECIES_MEGANIUM, 
   //SPECIES_CYNDAQUIL, 
   //SPECIES_QUILAVA, 
   //SPECIES_TYPHLOSION, 
   //SPECIES_TOTODILE, 
   //SPECIES_CROCONAW, 
   //SPECIES_FERALIGATR, 
   //SPECIES_SENTRET, 
   //SPECIES_FURRET, 
    //SPECIES_HOOTHOOT, 
   //SPECIES_NOCTOWL, 
    //SPECIES_LEDYBA, 
   //SPECIES_LEDIAN, 
    //SPECIES_SPINARAK, 
   //SPECIES_ARIADOS, 
   //SPECIES_CROBAT, 
    //SPECIES_CHINCHOU, 
   //SPECIES_LANTURN, 
   //SPECIES_PICHU, 
   //SPECIES_CLEFFA, 
   //SPECIES_IGGLYBUFF, 
   //SPECIES_TOGEPI, 
   //SPECIES_TOGETIC, 
    //SPECIES_NATU, 
    //SPECIES_XATU, 
    //SPECIES_MAREEP, 
   //SPECIES_FLAAFFY, 
   //SPECIES_AMPHAROS, 
   //SPECIES_BELLOSSOM, 
    //SPECIES_MARILL, 
   //SPECIES_AZUMARILL, 
   //SPECIES_SUDOWOODO, 
   //SPECIES_POLITOED, 
   //SPECIES_HOPPIP, 
   //SPECIES_SKIPLOOM, 
   //SPECIES_JUMPLUFF, 
    //SPECIES_AIPOM, 
    //SPECIES_SUNKERN, 
   //SPECIES_SUNFLORA, 
   //SPECIES_YANMA, 
    //SPECIES_WOOPER, 
    //SPECIES_QUAGSIRE, 
   //SPECIES_ESPEON, 
   //SPECIES_UMBREON, 
   //SPECIES_MURKROW, 
   //SPECIES_SLOWKING, 
   //SPECIES_MISDREAVUS, 
    //SPECIES_UNOWN, 
    //SPECIES_WOBBUFFET, 
    //SPECIES_GIRAFARIG, 
    //SPECIES_PINECO, 
   //SPECIES_FORRETRESS, 
   //SPECIES_DUNSPARCE, 
    //SPECIES_GLIGAR, 
   //SPECIES_STEELIX, 
    //SPECIES_SNUBBULL, 
   //SPECIES_GRANBULL, 
   //SPECIES_QWILFISH, 
   //SPECIES_SCIZOR, 
    //SPECIES_SHUCKLE, 
    //SPECIES_HERACROSS, 
   //SPECIES_SNEASEL, 
    //SPECIES_TEDDIURSA, 
   //SPECIES_URSARING, 
    //SPECIES_SLUGMA, 
   //SPECIES_MAGCARGO, 
   //SPECIES_SWINUB, 
   //SPECIES_PILOSWINE, 
    //SPECIES_CORSOLA, 
    //SPECIES_REMORAID, 
    //SPECIES_OCTILLERY, 
   //SPECIES_DELIBIRD, 
   //SPECIES_MANTINE, 
    //SPECIES_SKARMORY, 
    //SPECIES_HOUNDOUR, 
   //SPECIES_HOUNDOOM, 
    //SPECIES_KINGDRA, 
    //SPECIES_PHANPY, 
   //SPECIES_DONPHAN, 
   //SPECIES_PORYGON2, 
    //SPECIES_STANTLER, 
    //SPECIES_SMEARGLE, 
   //SPECIES_TYROGUE, 
   //SPECIES_HITMONTOP, 
   //SPECIES_SMOOCHUM, 
   //SPECIES_ELEKID, 
   //SPECIES_MAGBY, 
    //SPECIES_MILTANK, 
    /*SPECIES_BLISSEY, 
    SPECIES_LARVITAR, 
    SPECIES_PUPITAR, 
    SPECIES_TYRANITAR, 
    //SPECIES_TREECKO, 
    SPECIES_GROVYLE, 
    SPECIES_SCEPTILE, 
    //SPECIES_TORCHIC, 
    SPECIES_COMBUSKEN, 
    SPECIES_BLAZIKEN, 
    //SPECIES_MUDKIP, 
    SPECIES_MARSHTOMP, 
    SPECIES_SWAMPERT, */
    /*SPECIES_POOCHYENA, 
    SPECIES_MIGHTYENA, 
    SPECIES_ZIGZAGOON, 
    SPECIES_LINOONE, 
    SPECIES_WURMPLE, 
    SPECIES_SILCOON, 
    SPECIES_BEAUTIFLY, 
    SPECIES_CASCOON, 
    SPECIES_DUSTOX, 
    SPECIES_LOTAD, 
    SPECIES_LOMBRE, 
    SPECIES_LUDICOLO, 
    SPECIES_SEEDOT, 
    SPECIES_NUZLEAF, 
    SPECIES_SHIFTRY, 
    SPECIES_NINCADA, 
    SPECIES_NINJASK, 
    SPECIES_SHEDINJA, 
    SPECIES_TAILLOW, 
    SPECIES_SWELLOW, 
    SPECIES_SHROOMISH, 
    SPECIES_BRELOOM, 
    SPECIES_SPINDA, 
    SPECIES_WINGULL, 
    SPECIES_PELIPPER, 
    SPECIES_SURSKIT, 
    SPECIES_MASQUERAIN, 
    SPECIES_WAILMER, 
    SPECIES_WAILORD, 
    SPECIES_SKITTY, 
    SPECIES_DELCATTY, 
    SPECIES_KECLEON, 
    SPECIES_BALTOY, 
    SPECIES_CLAYDOL, 
    SPECIES_NOSEPASS, 
    SPECIES_TORKOAL, 
    SPECIES_SABLEYE, 
    SPECIES_BARBOACH, 
    SPECIES_WHISCASH, 
    SPECIES_LUVDISC, 
    SPECIES_CORPHISH, 
    SPECIES_CRAWDAUNT, 
    SPECIES_FEEBAS, 
    SPECIES_MILOTIC, 
    SPECIES_CARVANHA, 
    SPECIES_SHARPEDO, 
    SPECIES_TRAPINCH, 
    SPECIES_VIBRAVA, 
    SPECIES_FLYGON, 
    SPECIES_MAKUHITA, 
    SPECIES_HARIYAMA, 
    SPECIES_ELECTRIKE, 
    SPECIES_MANECTRIC, 
    SPECIES_NUMEL, 
    SPECIES_CAMERUPT, 
    SPECIES_SPHEAL, 
    SPECIES_SEALEO, 
    SPECIES_WALREIN, 
    SPECIES_CACNEA, 
    SPECIES_CACTURNE, 
    SPECIES_SNORUNT, 
    SPECIES_GLALIE, 
    SPECIES_LUNATONE, 
    SPECIES_SOLROCK, 
    SPECIES_AZURILL, 
    SPECIES_SPOINK, 
    SPECIES_GRUMPIG, 
    SPECIES_PLUSLE, 
    SPECIES_MINUN, 
    SPECIES_MAWILE, 
    SPECIES_MEDITITE, 
    SPECIES_MEDICHAM, 
    SPECIES_SWABLU, 
    SPECIES_ALTARIA, 
    SPECIES_WYNAUT, 
    SPECIES_DUSKULL, 
    SPECIES_DUSCLOPS, 
    SPECIES_ROSELIA, 
    SPECIES_SLAKOTH, 
    SPECIES_VIGOROTH, 
    SPECIES_SLAKING, 
    SPECIES_GULPIN, 
    SPECIES_SWALOT, 
    SPECIES_TROPIUS, 
    SPECIES_WHISMUR, 
    SPECIES_LOUDRED, 
    SPECIES_EXPLOUD, 
    SPECIES_CLAMPERL, 
    SPECIES_HUNTAIL, 
    SPECIES_GOREBYSS, 
    SPECIES_ABSOL, 
    SPECIES_SHUPPET, 
    SPECIES_BANETTE, 
    SPECIES_SEVIPER, 
    SPECIES_ZANGOOSE, 
    SPECIES_RELICANTH, 
    SPECIES_ARON, 
    SPECIES_LAIRON, 
    SPECIES_AGGRON, 
    SPECIES_CASTFORM, 
    SPECIES_VOLBEAT, 
    SPECIES_ILLUMISE, 
    SPECIES_LILEEP, 
    SPECIES_CRADILY, 
    SPECIES_ANORITH, 
    SPECIES_ARMALDO, 
    SPECIES_RALTS, 
    SPECIES_KIRLIA, 
    SPECIES_GARDEVOIR, 
    SPECIES_BAGON, 
    SPECIES_SHELGON, 
    SPECIES_SALAMENCE, 
    SPECIES_BELDUM, 
    SPECIES_METANG, 
    SPECIES_METAGROSS, 
    SPECIES_CHIMECHO,  
    SPECIES_MIME_JR, 
    SPECIES_MUNCHLAX, 
    SPECIES_BONSLY, 
    SPECIES_MANTYKE, 
    SPECIES_HAPPINY, 
    SPECIES_CHINGLING, 
    //SPECIES_BUDEW, 
    //SPECIES_ROSERADE, 
    SPECIES_DUSKNOIR, 
    SPECIES_AMBIPOM, 
    SPECIES_ELECTIVIRE, 
    SPECIES_FROSLASS, 
    SPECIES_GALLADE, 
    //SPECIES_GLISCOR, 
    SPECIES_HONCHKROW, 
    SPECIES_LICKILICKY, 
    SPECIES_MAGMORTAR, 
    SPECIES_MAGNEZONE, 
    SPECIES_MAMOSWINE, 
    SPECIES_MISMAGIUS, 
    SPECIES_PORYGON_Z, 
    SPECIES_PROBOPASS, 
    SPECIES_RHYPERIOR, 
    SPECIES_TANGROWTH, 
    SPECIES_TOGEKISS, 
    SPECIES_WEAVILE, 
    SPECIES_YANMEGA, 
    SPECIES_LEAFEON, 
    SPECIES_GLACEON, 
    SPECIES_SYLVEON, 
    SPECIES_ANNIHILAPE, 
    //SPECIES_FARIGIRAF, 
    SPECIES_DUDUNSPARCE,
    SPECIES_WYRDEER,
    SPECIES_URSALUNA,
    SPECIES_URSALUNA_BLOODMOON,
    SPECIES_KLEAVOR*/
};

static const u16 sMovingRegionMapSections[3] =
{
    MAPSEC_MARINE_CAVE,
    MAPSEC_UNDERWATER_MARINE_CAVE,
    MAPSEC_TERRA_CAVE
};

static const u16 sFeebasData[][3] =
{
    {SPECIES_FEEBAS, MAP_GROUP(ROUTE119), MAP_NUM(ROUTE119)},
    {NUM_SPECIES}
};

static const u16 sHiddenPokemon[][3] =
{
    {SPECIES_HOUNDOUR, MAP_GROUP(SAFARI_ZONE_NORTHWEST), MAP_NUM(SAFARI_ZONE_NORTHWEST)},
    {SPECIES_HOOTHOOT, MAP_GROUP(SAFARI_ZONE_NORTHWEST), MAP_NUM(SAFARI_ZONE_NORTHWEST)},
    {SPECIES_LEDYBA, MAP_GROUP(SAFARI_ZONE_NORTHWEST), MAP_NUM(SAFARI_ZONE_NORTHWEST)},
    {SPECIES_SPINARAK, MAP_GROUP(SAFARI_ZONE_NORTHWEST), MAP_NUM(SAFARI_ZONE_NORTHWEST)},
    {SPECIES_SUNKERN, MAP_GROUP(SAFARI_ZONE_NORTHWEST), MAP_NUM(SAFARI_ZONE_NORTHWEST)},
    {SPECIES_SNUBBULL, MAP_GROUP(SAFARI_ZONE_NORTHWEST), MAP_NUM(SAFARI_ZONE_NORTHWEST)},
    {NUM_SPECIES}
};

static const u16 sLandmarkData[][2] =
{
    {MAPSEC_SKY_PILLAR,       FLAG_LANDMARK_SKY_PILLAR},
    {MAPSEC_SEAFLOOR_CAVERN,  FLAG_LANDMARK_SEAFLOOR_CAVERN},
    {MAPSEC_ALTERING_CAVE,    FLAG_LANDMARK_ALTERING_CAVE},
    {MAPSEC_MIRAGE_TOWER,     FLAG_LANDMARK_MIRAGE_TOWER},
    {MAPSEC_DESERT_UNDERPASS, FLAG_LANDMARK_DESERT_UNDERPASS},
    {MAPSEC_ARTISAN_CAVE,     FLAG_LANDMARK_ARTISAN_CAVE},
    {MAPSEC_NONE}
};

#include "data/pokedex_area_glow.h"

static const struct PokedexAreaMapTemplate sPokedexAreaMapTemplate =
{
    .bg = 3,
    .offset = 0,
    .mode = 0,
    .unk = 2,
};

static const u8 sAreaMarkerTiles[];
static const struct SpriteSheet sAreaMarkerSpriteSheet =
{
    .data = sAreaMarkerTiles, .size = 0x80, .tag = TAG_AREA_MARKER
};

static const u16 sAreaMarkerPalette[];
static const struct SpritePalette sAreaMarkerSpritePalette =
{
    .data = sAreaMarkerPalette, .tag = TAG_AREA_MARKER
};

static const struct OamData sAreaMarkerOamData =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 1
};

static const struct SpriteTemplate sAreaMarkerSpriteTemplate =
{
    .tileTag = TAG_AREA_MARKER,
    .paletteTag = TAG_AREA_MARKER,
    .oam = &sAreaMarkerOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static const u16 sAreaMarkerPalette[] = INCBIN_U16("graphics/pokedex/area_marker.gbapal");
static const u8 sAreaMarkerTiles[] = INCBIN_U8("graphics/pokedex/area_marker.4bpp");

// Day / night indicator graphics.  Each PNG is 32x32 storing a stacked 64x16
// graphic: top 32x16 = left half, bottom 32x16 = right half.  Two 32x16 sprites
// are placed side-by-side on screen; the right sprite uses tileNum + 8.
#define TAG_AREA_DAY_IND   4
#define TAG_AREA_NIGHT_IND 5

static const u8  sDayIndicatorTiles[]   = INCBIN_U8("graphics/pokedex/area_indicator_day.4bpp");
static const u8  sNightIndicatorTiles[] = INCBIN_U8("graphics/pokedex/area_indicator_night.4bpp");

// Each half of the 64x16 indicator is a 32x16 OAM object.
static const struct OamData sIndicatorOamData =
{
    .shape    = SPRITE_SHAPE(32x16),
    .size     = SPRITE_SIZE(32x16),
    .priority = 0,
};
// Both indicator templates share TAG_AREA_UNKNOWN's palette, which is loaded
// before the fade-in begins so no mid-fade palette flash occurs.
static const struct SpriteTemplate sDayIndicatorTemplate =
{
    .tileTag     = TAG_AREA_DAY_IND,
    .paletteTag  = TAG_AREA_UNKNOWN,
    .oam         = &sIndicatorOamData,
    .anims       = gDummySpriteAnimTable,
    .images      = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback    = SpriteCallbackDummy,
};
static const struct SpriteTemplate sNightIndicatorTemplate =
{
    .tileTag     = TAG_AREA_NIGHT_IND,
    .paletteTag  = TAG_AREA_UNKNOWN,
    .oam         = &sIndicatorOamData,
    .anims       = gDummySpriteAnimTable,
    .images      = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback    = SpriteCallbackDummy,
};

static const struct SpritePalette sAreaUnknownSpritePalette =
{
    .data = gPokedexAreaScreenAreaUnknown_Pal, .tag = TAG_AREA_UNKNOWN
};

static const struct OamData sAreaUnknownOamData =
{
    .shape = SPRITE_SHAPE(32x32),
    .size = SPRITE_SIZE(32x32),
    .priority = 1
};

static const struct SpriteTemplate sAreaUnknownSpriteTemplate =
{
    .tileTag = TAG_AREA_UNKNOWN,
    .paletteTag = TAG_AREA_UNKNOWN,
    .oam = &sAreaUnknownOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static void ResetDrawAreaGlowState(void)
{
    sPokedexAreaScreen->drawAreaGlowState = 0;
}

static bool8 DrawAreaGlow(void)
{
    switch (sPokedexAreaScreen->drawAreaGlowState)
    {
    case 0:
        // Scan the alternate time mode first so its results land in the active
        // arrays, which we then copy straight into the _alt cache.  Flipping
        // back and re-scanning for the real current mode leaves the active
        // arrays correct and both caches populated — all within a single frame.
        sPokedexAreaScreen->areaViewTimeMode ^= 1;
        FindMapsWithMon(sPokedexAreaScreen->species);
        CpuCopy32(sPokedexAreaScreen->overworldAreasWithMons,
                  sPokedexAreaScreen->overworldAreasWithMons_alt,
                  sizeof(sPokedexAreaScreen->overworldAreasWithMons_alt));
        sPokedexAreaScreen->numOverworldAreas_alt = sPokedexAreaScreen->numOverworldAreas;
        CpuCopy16(sPokedexAreaScreen->specialAreaRegionMapSectionIds,
                  sPokedexAreaScreen->specialAreaRegionMapSectionIds_alt,
                  sizeof(sPokedexAreaScreen->specialAreaRegionMapSectionIds_alt));
        sPokedexAreaScreen->numSpecialAreas_alt = sPokedexAreaScreen->numSpecialAreas;
        // Also pre-build the alt glow tilemap while the alt encounter data is
        // still in the active arrays, then copy it into the alt cache.
        BuildAreaGlowTilemap();
        CpuCopy16(sPokedexAreaScreen->areaGlowTilemap,
                  sPokedexAreaScreen->areaGlowTilemap_alt,
                  sizeof(sPokedexAreaScreen->areaGlowTilemap_alt));
        // Restore the real mode and populate the active arrays.
        sPokedexAreaScreen->areaViewTimeMode ^= 1;
        FindMapsWithMon(sPokedexAreaScreen->species);
        break;
    case 1:
        BuildAreaGlowTilemap();
        break;
    case 2:
        DecompressAndCopyTileDataToVram(2, sAreaGlow_Gfx, 0, 0, 0);
        LoadBgTilemap(2, sPokedexAreaScreen->areaGlowTilemap, sizeof(sPokedexAreaScreen->areaGlowTilemap), 0);
        break;
    case 3:
        if (!FreeTempTileDataBuffersIfPossible())
        {
            CpuCopy32(sAreaGlow_Pal, &gPlttBufferUnfaded[BG_PLTT_ID(GLOW_PALETTE)], sizeof(sAreaGlow_Pal));
            sPokedexAreaScreen->drawAreaGlowState++;
        }
        return TRUE;
    case 4:
        ChangeBgY(2, -BG_SCREEN_SIZE, BG_COORD_SET);
        break;
    default:
        return FALSE;
    }

    sPokedexAreaScreen->drawAreaGlowState++;
    return TRUE;
}

static void FindMapsWithMon(u16 species)
{
    u16 i;
    struct Roamer *roamer;

    sPokedexAreaScreen->alteringCaveCounter = 0;
    sPokedexAreaScreen->alteringCaveId = VarGet(VAR_ALTERING_CAVE_WILD_SET);
    if (sPokedexAreaScreen->alteringCaveId >= NUM_ALTERING_CAVE_TABLES)
        sPokedexAreaScreen->alteringCaveId = 0;

    roamer = &gSaveBlock1Ptr->roamer;
    if (species != roamer->species)
    {
        sPokedexAreaScreen->numOverworldAreas = 0;
        sPokedexAreaScreen->numSpecialAreas = 0;

        //hides the pkm that are part from the list from above. Certain pkm will still overlap, but it's a solution for now
        if (gSaveBlock1Ptr->tx_Mode_AlternateSpawns == 0)
        {
            for (i = 0; i < ARRAY_COUNT(sSpeciesHiddenFromAreaScreenModern); i++)
            {
                if (VarGet(VAR_TIME_BASED_ENCOUNTER) >= 0 && VarGet(VAR_TIME_BASED_ENCOUNTER) <= 2)
                    if (sSpeciesHiddenFromAreaScreenModern[i] == species)
                        return;
            }
            for (i = 0; sHiddenPokemon[i][0] != NUM_SPECIES; i++)
            {
                if (species == sHiddenPokemon[i][0])
                {
                    switch (sHiddenPokemon[i][1])
                    {
                    case MAP_GROUP_TOWNS_AND_ROUTES:
                        SetAreaHasMon(sHiddenPokemon[i][1], sHiddenPokemon[i][2]);
                        return;
                    case MAP_GROUP_DUNGEONS:
                    case MAP_GROUP_SPECIAL_AREA:
                        SetSpecialMapHasMon(sHiddenPokemon[i][1], sHiddenPokemon[i][2]);
                        return;
                    }
                }
            }
        }
        // Check if this species should be hidden from the area map.
        // This only applies to Wynaut, to hide the encounters on Mirage Island.
        for (i = 0; i < ARRAY_COUNT(sSpeciesHiddenFromAreaScreen); i++)
        {
            if (sSpeciesHiddenFromAreaScreen[i] == species)
                return;
        }

        // Add Pokémon with special encounter circumstances (i.e. not listed
        // in the regular wild encounter table) to the area map.
        // This only applies to Feebas on Route 119, but it was clearly set
        // up to allow handling others.
        for (i = 0; sFeebasData[i][0] != NUM_SPECIES; i++)
        {
            if (species == sFeebasData[i][0])
            {
                switch (sFeebasData[i][1])
                {
                case MAP_GROUP_TOWNS_AND_ROUTES:
                    SetAreaHasMon(sFeebasData[i][1], sFeebasData[i][2]);
                    break;
                case MAP_GROUP_DUNGEONS:
                case MAP_GROUP_SPECIAL_AREA:
                    SetSpecialMapHasMon(sFeebasData[i][1], sFeebasData[i][2]);
                    break;
                }
            }
        }

        // Add regular species to the area map
        {
            u16 slotIndex = 0;
            for (i = 0; gWildMonHeaders[i].mapGroup != MAP_GROUP(UNDEFINED); i++)
            {
                // Track which time-slot offset we're at within a run of same-map headers.
                // Consecutive headers sharing mapGroup+mapNum are day/night variants:
                //   slotIndex 0 = day table, slotIndex 1 = night table.
                if (i > 0
                    && gWildMonHeaders[i].mapGroup == gWildMonHeaders[i-1].mapGroup
                    && gWildMonHeaders[i].mapNum   == gWildMonHeaders[i-1].mapNum)
                    slotIndex++;
                else
                    slotIndex = 0;

                // When the time system is active, only process the header for the
                // currently viewed time mode.  Single-slot maps (slotIndex always
                // stays 0 because the next entry belongs to a different map) are
                // always shown in both day and night views.
                if (VarGet(VAR_TIME_BASED_ENCOUNTER) >= 1)
                {
                    bool8 isMultiSlot = (slotIndex > 0)
                        || (gWildMonHeaders[i+1].mapGroup != MAP_GROUP(UNDEFINED)
                            && gWildMonHeaders[i].mapGroup == gWildMonHeaders[i+1].mapGroup
                            && gWildMonHeaders[i].mapNum   == gWildMonHeaders[i+1].mapNum);
                    if (isMultiSlot && slotIndex != sPokedexAreaScreen->areaViewTimeMode)
                        continue;
                }

                if (MapHasSpecies(&gWildMonHeaders[i], species))
                {
                    switch (gWildMonHeaders[i].mapGroup)
                    {
                    case MAP_GROUP_TOWNS_AND_ROUTES:
                        SetAreaHasMon(gWildMonHeaders[i].mapGroup, gWildMonHeaders[i].mapNum);
                        break;
                    case MAP_GROUP_DUNGEONS:
                    case MAP_GROUP_SPECIAL_AREA:
                        SetSpecialMapHasMon(gWildMonHeaders[i].mapGroup, gWildMonHeaders[i].mapNum);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        // This is the roamer's species, show where the roamer is currently
        sPokedexAreaScreen->numSpecialAreas = 0;
        if (roamer->active)
        {
            GetRoamerLocation(&sPokedexAreaScreen->overworldAreasWithMons[0].mapGroup, &sPokedexAreaScreen->overworldAreasWithMons[0].mapNum);
            sPokedexAreaScreen->overworldAreasWithMons[0].regionMapSectionId = Overworld_GetMapHeaderByGroupAndId(sPokedexAreaScreen->overworldAreasWithMons[0].mapGroup, sPokedexAreaScreen->overworldAreasWithMons[0].mapNum)->regionMapSectionId;
            sPokedexAreaScreen->numOverworldAreas = 1;
        }
        else
        {
            sPokedexAreaScreen->numOverworldAreas = 0;
        }
    }
}

static void SetAreaHasMon(u16 mapGroup, u16 mapNum)
{
    if (sPokedexAreaScreen->numOverworldAreas < MAX_AREA_HIGHLIGHTS)
    {
        sPokedexAreaScreen->overworldAreasWithMons[sPokedexAreaScreen->numOverworldAreas].mapGroup = mapGroup;
        sPokedexAreaScreen->overworldAreasWithMons[sPokedexAreaScreen->numOverworldAreas].mapNum = mapNum;
        sPokedexAreaScreen->overworldAreasWithMons[sPokedexAreaScreen->numOverworldAreas].regionMapSectionId = CorrectSpecialMapSecId(Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum)->regionMapSectionId);
        sPokedexAreaScreen->numOverworldAreas++;
    }
}

static void SetSpecialMapHasMon(u16 mapGroup, u16 mapNum)
{
    int i;

    if (sPokedexAreaScreen->numSpecialAreas < MAX_AREA_MARKERS)
    {
        u16 regionMapSectionId = GetRegionMapSectionId(mapGroup, mapNum);
        if (regionMapSectionId < MAPSEC_NONE)
        {
            // Don't highlight the area if it's a moving area (Marine/Terra Cave)
            for (i = 0; i < ARRAY_COUNT(sMovingRegionMapSections); i++)
            {
                if (regionMapSectionId == sMovingRegionMapSections[i])
                    return;
            }

            // Don't highlight the area if it's an undiscovered landmark (e.g. Sky Pillar)
            for (i = 0; sLandmarkData[i][0] != MAPSEC_NONE; i++)
            {
                if (regionMapSectionId == sLandmarkData[i][0] && !FlagGet(sLandmarkData[i][1]))
                    return;
            }

            // Check if this special area is already being tracked
            for (i = 0; i < sPokedexAreaScreen->numSpecialAreas; i++)
            {
                if (sPokedexAreaScreen->specialAreaRegionMapSectionIds[i] == regionMapSectionId)
                    break;
            }

            if (i == sPokedexAreaScreen->numSpecialAreas)
            {
                // New special area
                sPokedexAreaScreen->specialAreaRegionMapSectionIds[i] = regionMapSectionId;
                sPokedexAreaScreen->numSpecialAreas++;
            }
        }
    }
}

static u16 GetRegionMapSectionId(u8 mapGroup, u8 mapNum)
{
    return Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum)->regionMapSectionId;
}

static bool8 MapHasSpecies(const struct WildPokemonHeader *info, u16 species)
{
    // If this is a header for Altering Cave, skip it if it's not the current Altering Cave encounter set
    if (GetRegionMapSectionId(info->mapGroup, info->mapNum) == MAPSEC_ALTERING_CAVE)
    {
        sPokedexAreaScreen->alteringCaveCounter++;
        if (sPokedexAreaScreen->alteringCaveCounter != sPokedexAreaScreen->alteringCaveId + 1)
            return FALSE;
    }

    if (MonListHasSpecies(info->landMonsInfo, species, LAND_WILD_COUNT))
        return TRUE;
    if (MonListHasSpecies(info->waterMonsInfo, species, WATER_WILD_COUNT))
        return TRUE;
// When searching the fishing encounters, this incorrectly uses the size of the land encounters.
// As a result it's reading out of bounds of the fishing encounters tables.
#ifdef BUGFIX
    if (MonListHasSpecies(info->fishingMonsInfo, species, FISH_WILD_COUNT))
#else
    if (MonListHasSpecies(info->fishingMonsInfo, species, LAND_WILD_COUNT))
#endif
        return TRUE;
    if (MonListHasSpecies(info->rockSmashMonsInfo, species, ROCK_WILD_COUNT))
        return TRUE;
    return FALSE;
}

static bool8 MonListHasSpecies(const struct WildPokemonInfo *info, u16 species, u16 size)
{
    u16 i;
    if (info != NULL)
    {
        for (i = 0; i < size; i++)
        {
            if (info->wildPokemon[i].species == species)
                return TRUE;
        }
    }
    return FALSE;
}

static void BuildAreaGlowTilemap(void)
{
    u16 i, y, x, j;

    // Reset tilemap
    for (i = 0; i < ARRAY_COUNT(sPokedexAreaScreen->areaGlowTilemap); i++)
        sPokedexAreaScreen->areaGlowTilemap[i] = 0;

    // For each area with this species, scan the region map layout and find any locations that have a matching mapsec.
    // Add a "full glow" indicator for these matching spaces.
    for (i = 0; i < sPokedexAreaScreen->numOverworldAreas; i++)
    {
        j = 0;
        for (y = 0; y < AREA_SCREEN_HEIGHT; y++)
        {
            for (x = 0; x < AREA_SCREEN_WIDTH; x++)
            {
                if (DexGetMapSecAt(x, y) == sPokedexAreaScreen->overworldAreasWithMons[i].regionMapSectionId)
                    sPokedexAreaScreen->areaGlowTilemap[j] = GLOW_FULL;
                j++;
            }
        }
    }

    // Scan the tilemap. For every "full glow" indicator added above, fill in its edges and corners.
    j = 0;
    for (y = 0; y < AREA_SCREEN_HEIGHT; y++)
    {
        for (x = 0; x < AREA_SCREEN_WIDTH; x++)
        {
            if (sPokedexAreaScreen->areaGlowTilemap[j] == GLOW_FULL)
            {
                // The "tile != GLOW_FULL" check is pointless in all of these conditionals,
                // since there's no harm in OR'ing 0xFFFF with anything else.

                // Edges
                if (x != 0 && sPokedexAreaScreen->areaGlowTilemap[j - 1] != GLOW_FULL)
                    sPokedexAreaScreen->areaGlowTilemap[j - 1] |= GLOW_EDGE_L;
                if (x != AREA_SCREEN_WIDTH - 1 && sPokedexAreaScreen->areaGlowTilemap[j + 1] != GLOW_FULL)
                    sPokedexAreaScreen->areaGlowTilemap[j + 1] |= GLOW_EDGE_R;
                if (y != 0 && sPokedexAreaScreen->areaGlowTilemap[j - AREA_SCREEN_WIDTH] != GLOW_FULL)
                    sPokedexAreaScreen->areaGlowTilemap[j - AREA_SCREEN_WIDTH] |= GLOW_EDGE_T;
                if (y != AREA_SCREEN_HEIGHT - 1 && sPokedexAreaScreen->areaGlowTilemap[j + AREA_SCREEN_WIDTH] != GLOW_FULL)
                    sPokedexAreaScreen->areaGlowTilemap[j + AREA_SCREEN_WIDTH] |= GLOW_EDGE_B;

                // Corners
                if (x != 0 && y != 0 && sPokedexAreaScreen->areaGlowTilemap[j - AREA_SCREEN_WIDTH - 1] != GLOW_FULL)
                    sPokedexAreaScreen->areaGlowTilemap[j - AREA_SCREEN_WIDTH - 1] |= GLOW_CORNER_TL;
                if (x != AREA_SCREEN_WIDTH - 1 && y != 0 && sPokedexAreaScreen->areaGlowTilemap[j - AREA_SCREEN_WIDTH + 1] != GLOW_FULL)
                    sPokedexAreaScreen->areaGlowTilemap[j - AREA_SCREEN_WIDTH + 1] |= GLOW_CORNER_TR;
                if (x != 0 && y != AREA_SCREEN_HEIGHT - 1 && sPokedexAreaScreen->areaGlowTilemap[j + AREA_SCREEN_WIDTH - 1] != GLOW_FULL)
                    sPokedexAreaScreen->areaGlowTilemap[j + AREA_SCREEN_WIDTH - 1] |= GLOW_CORNER_BL;
                if (x != AREA_SCREEN_WIDTH - 1 && y != AREA_SCREEN_HEIGHT - 1 && sPokedexAreaScreen->areaGlowTilemap[j + AREA_SCREEN_WIDTH + 1] != GLOW_FULL)
                    sPokedexAreaScreen->areaGlowTilemap[j + AREA_SCREEN_WIDTH + 1] |= GLOW_CORNER_BR;
            }

            j++;
        }
    }

    // Scan the tilemap again. Replace the "full tile" indicators with the actual tile id,
    // and remove corner flags when they're overlapped by an edge.
    for (i = 0; i < ARRAY_COUNT(sPokedexAreaScreen->areaGlowTilemap); i++)
    {
        if (sPokedexAreaScreen->areaGlowTilemap[i] == GLOW_FULL)
        {
            sPokedexAreaScreen->areaGlowTilemap[i] = GLOW_TILE_FULL;
            sPokedexAreaScreen->areaGlowTilemap[i] |= (GLOW_PALETTE << 12);
        }
        else if (sPokedexAreaScreen->areaGlowTilemap[i])
        {
            // Get rid of overlapping flags.
            // This is pointless, as sAreaGlowTilemapMapping can handle overlaps.
            if (sPokedexAreaScreen->areaGlowTilemap[i] & GLOW_EDGE_L)
                sPokedexAreaScreen->areaGlowTilemap[i] &= ~(GLOW_CORNER_TL | GLOW_CORNER_BL);
            if (sPokedexAreaScreen->areaGlowTilemap[i] & GLOW_EDGE_R)
                sPokedexAreaScreen->areaGlowTilemap[i] &= ~(GLOW_CORNER_TR | GLOW_CORNER_BR);
            if (sPokedexAreaScreen->areaGlowTilemap[i] & GLOW_EDGE_T)
                sPokedexAreaScreen->areaGlowTilemap[i] &= ~(GLOW_CORNER_TR | GLOW_CORNER_TL);
            if (sPokedexAreaScreen->areaGlowTilemap[i] & GLOW_EDGE_B)
                sPokedexAreaScreen->areaGlowTilemap[i] &= ~(GLOW_CORNER_BR | GLOW_CORNER_BL);

            // Assign tile id
            sPokedexAreaScreen->areaGlowTilemap[i] = sAreaGlowTilemapMapping[sPokedexAreaScreen->areaGlowTilemap[i]];
            sPokedexAreaScreen->areaGlowTilemap[i] |= (GLOW_PALETTE << 12);
        }
    }
}

static void StartAreaGlow(void)
{
    if (sPokedexAreaScreen->numSpecialAreas && sPokedexAreaScreen->numOverworldAreas == 0)
        sPokedexAreaScreen->showingMarkers = TRUE;
    else
        sPokedexAreaScreen->showingMarkers = FALSE;

    sPokedexAreaScreen->markerTimer = 0;
    sPokedexAreaScreen->glowTimer = 0;
    sPokedexAreaScreen->areaShadeBldArgLo = 0;
    sPokedexAreaScreen->areaShadeBldArgHi = 64;
    sPokedexAreaScreen->markerFlashCounter = 1;
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG2 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_ALL);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 16));
    DoAreaGlow();
}

static void DoAreaGlow(void)
{
    u16 x, y;
    u16 i;

    if (!sPokedexAreaScreen->showingMarkers)
    {
        // Showing area glow
        if (sPokedexAreaScreen->markerTimer == 0)
        {
            sPokedexAreaScreen->glowTimer++;
            if (sPokedexAreaScreen->glowTimer & 1)
                sPokedexAreaScreen->areaShadeBldArgLo = (sPokedexAreaScreen->areaShadeBldArgLo + 4) & 0x7f;
            else
                sPokedexAreaScreen->areaShadeBldArgHi = (sPokedexAreaScreen->areaShadeBldArgHi + 4) & 0x7f;

            x = gSineTable[sPokedexAreaScreen->areaShadeBldArgLo] >> 4;
            y = gSineTable[sPokedexAreaScreen->areaShadeBldArgHi] >> 4;
            SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(x, y));
            sPokedexAreaScreen->markerTimer = 0;
            if (sPokedexAreaScreen->glowTimer == 64)
            {
                // Done glowing, reset and try to switch to the special area markers
                sPokedexAreaScreen->glowTimer = 0;
                if (sPokedexAreaScreen->numSpecialAreas != 0)
                    sPokedexAreaScreen->showingMarkers = TRUE;
            }
        }
        else
            sPokedexAreaScreen->markerTimer--;
    }
    else
    {
        // Showing special area markers
        sPokedexAreaScreen->markerTimer++;
        if (sPokedexAreaScreen->markerTimer > 12)
        {
            sPokedexAreaScreen->markerTimer = 0;

            // Flash the marker
            // With a max of 4, the marker will disappear twice
            sPokedexAreaScreen->markerFlashCounter++;
            for (i = 0; i < sPokedexAreaScreen->numSpecialAreas; i++)
                sPokedexAreaScreen->areaMarkerSprites[i]->invisible = sPokedexAreaScreen->markerFlashCounter & 1;

            if (sPokedexAreaScreen->markerFlashCounter > 4)
            {
                // Done flashing, reset and try to switch to the area glow
                sPokedexAreaScreen->markerFlashCounter = 1;
                if (sPokedexAreaScreen->numOverworldAreas != 0)
                    sPokedexAreaScreen->showingMarkers = FALSE;
            }
        }
    }
}

#define tState data[0]

void ShowPokedexAreaScreen(u16 species, u8 *screenSwitchState)
{
    u8 taskId;

    // Ensure VAR_TIME_BASED_ENCOUNTER reflects the real current time.
    // The var is zeroed by ClearTempFieldEventData on every map load; indoor maps
    // have no OnTransition script that re-sets it, so without this call the area
    // screen would see 0 and suppress both the day/night indicators and START toggling.
    SetTimeBasedEncounters();

    sPokedexAreaScreen = AllocZeroed(sizeof(*sPokedexAreaScreen));
    sPokedexAreaScreen->species = species;
    sPokedexAreaScreen->screenSwitchState = screenSwitchState;
    screenSwitchState[0] = 0;

    // Open on whichever time mode is currently active in-game.
    sPokedexAreaScreen->areaViewTimeMode = (VarGet(VAR_TIME_BASED_ENCOUNTER) == 2) ? 1 : 0;
    sPokedexAreaScreen->indDaySpriteId   = MAX_SPRITES; // sentinel: indicator sprites not yet created
    sPokedexAreaScreen->indNightSpriteId = MAX_SPRITES;

    taskId = CreateTask(Task_ShowPokedexAreaScreen, 0);
    gTasks[taskId].tState = 0;
}

static void Task_ShowPokedexAreaScreen(u8 taskId)
{
    switch (gTasks[taskId].tState)
    {
    case 0:
        ResetSpriteData();
        FreeAllSpritePalettes();
        HideBg(3);
        HideBg(2);
        HideBg(0);
        break;
    case 1:
        SetBgAttribute(3, BG_ATTR_CHARBASEINDEX, 3);
        LoadPokedexAreaMapGfx(&sPokedexAreaMapTemplate);
        StringFill(sPokedexAreaScreen->charBuffer, CHAR_SPACE, 16);
        break;
    case 2:
        if (TryShowPokedexAreaMap() == TRUE)
            return;
        PokedexAreaMapChangeBgY(-8);
        break;
    case 3:
        ResetDrawAreaGlowState();
        break;
    case 4:
        if (DrawAreaGlow())
            return;
        break;
    case 5:
        ShowRegionMapForPokedexAreaScreen(&sPokedexAreaScreen->regionMap);
        CreateRegionMapPlayerIcon(1, 1);
        PokedexAreaScreen_UpdateRegionMapVariablesAndVideoRegs(0, -8);
        break;
    case 6:
        CreateAreaMarkerSprites();
        break;
    case 7:
        LoadAreaUnknownGraphics();
        break;
    case 8:
        CreateAreaUnknownSprites();
        // Pre-tint gPlttBufferUnfaded for night mode so BeginNormalPaletteFade
        // fades toward the correct tinted colors rather than the raw map palette.
        // BlendPalettes reads unfaded and writes faded; copy faded back as the new target.
        if (sPokedexAreaScreen->areaViewTimeMode == 1)
        {
            BlendPalettes((1 << 7) | (1 << 8), 8, RGB(2, 4, 10));
            CpuCopy32(&gPlttBufferFaded[BG_PLTT_ID(7)], &gPlttBufferUnfaded[BG_PLTT_ID(7)], 32 * sizeof(u16));
            // BlendPalettes wrote the tinted result into gPlttBufferFaded, which the
            // VBlank DMA would transfer to hardware -- causing a one-frame flash of the
            // half-tinted map at the top of the screen before BeginNormalPaletteFade
            // (next state) resets faded to black.  Restore faded to black here so the
            // screen stays dark; gPlttBufferUnfaded already holds the correct tinted
            // target for the subsequent fade-in.
            CpuFill16(0, &gPlttBufferFaded[BG_PLTT_ID(7)], 32 * sizeof(u16));
        }
        break;
    case 9:
        BeginNormalPaletteFade(PALETTES_ALL & ~(0x14), 0, 16, 0, RGB_BLACK);
        break;
    case 10:
        LoadHGSSScreenSelectBarSubmenu();
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG0 | BLDCNT_TGT2_ALL);
        StartAreaGlow();
        ShowBg(2);
        ShowBg(3); // TryShowPokedexAreaMap will have done this already
        SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON);
        CreateAreaIndicatorSprites(); // show stone sprite indicator if time system is active
        break;
    case 11:
        gTasks[taskId].func = Task_HandlePokedexAreaScreenInput;
        gTasks[taskId].tState = 0;
        return;
    }

    gTasks[taskId].tState++;
}

static void Task_HandlePokedexAreaScreenInput(u8 taskId)
{
    DoAreaGlow();
    switch (gTasks[taskId].tState)
    {
    default:
        gTasks[taskId].tState = 0;
        // fall through
    case 0:
        if (gPaletteFade.active)
            return;
        // Fade-in just completed — restore BG 7+8 from ROM, re-apply any night
        // tint (idempotent for day mode), and sync the OBJ area-marker palette.
        // Night mode: BG 7+8 unfaded was pre-tinted so the fade targeted the
        // correct colors; ApplyTimeModeToAreaMapPalette re-tints both buffers.
        // Day mode: no pre-tint was applied; function restores ROM palette and
        // skips tinting, leaving both buffers clean.
        ApplyTimeModeToAreaMapPalette();
        break;
    case 1:
        // If a multi-frame time-mode refresh is in progress, advance it and wait.
        if (gTasks[taskId].data[2] != 0)
        {
            ContinueTimeModeRefresh(taskId);
            return;
        }
        if (JOY_NEW(START_BUTTON))
        {
            // Toggle day/night encounter view.  Play failure sound if the time
            // system is not active for this save.
            if (VarGet(VAR_TIME_BASED_ENCOUNTER) == 0)
            {
                PlaySE(SE_FAILURE);
                return;
            }
            sPokedexAreaScreen->areaViewTimeMode ^= 1; // 0 (day) <-> 1 (night)
            PlaySE(SE_DEX_PAGE);
            gTasks[taskId].data[2] = 1; // kick off multi-frame refresh
            return;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            // This was originally intended to go back to the info screen (Original Emerald Behavior),
            // gTasks[taskId].data[1] = 1;
            // PlaySE(SE_DEX_PAGE);
            gTasks[taskId].data[1] = 3;
            PlaySE(SE_PC_OFF);
        }
        else if (JOY_NEW(DPAD_LEFT) || (JOY_NEW(L_BUTTON) && gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_LR))
        {
            gTasks[taskId].data[1] = 1;
            PlaySE(SE_DEX_PAGE);
        }
        else if (JOY_NEW(DPAD_RIGHT) || (JOY_NEW(R_BUTTON) && gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_LR))
        {
            if (!GetSetPokedexFlag(SpeciesToNationalPokedexNum(sPokedexAreaScreen->species), FLAG_GET_CAUGHT))
            {
                PlaySE(SE_FAILURE);
                return;
            }
            gTasks[taskId].data[1] = 2;
            PlaySE(SE_DEX_PAGE);
        }
        else
            return;
        break;
    case 2:
        BeginNormalPaletteFade(PALETTES_ALL & ~(0x14), 0, 0, 16, RGB_BLACK);
        break;
    case 3:
        if (gPaletteFade.active)
            return;
        DestroyAreaScreenSprites();
        sPokedexAreaScreen->screenSwitchState[0] = gTasks[taskId].data[1];
        ResetPokedexAreaMapBg();
        DestroyTask(taskId);
        FreePokedexAreaMapBgNum();
        FREE_AND_SET_NULL(sPokedexAreaScreen);
        return;
    }

    gTasks[taskId].tState++;
}

static void ResetPokedexAreaMapBg(void)
{
    SetBgAttribute(3, BG_ATTR_CHARBASEINDEX, 0);
    SetBgAttribute(3, BG_ATTR_PALETTEMODE, 0);
}

// Creates the circular sprites to highlight special areas (like caves) where a Pokémon can be found
static void CreateAreaMarkerSprites(void)
{
    u8 spriteId;
    u16 i;
    u16 mapSecId;
    u16 numSprites = 0;

    LoadSpriteSheet(&sAreaMarkerSpriteSheet);
    LoadSpritePalette(&sAreaMarkerSpritePalette);

    // Screen origin for the 28x15 grid on this screen
    const u16 originX = MAPCURSOR_X_MIN;      // tile coords
    const u16 originY = MAPCURSOR_Y_MIN;      // tile coords
    // Y has an extra +8px shift on this screen (matches existing 28px base)
    const u16 extraYPixels = 8;

    for (i = 0; i < sPokedexAreaScreen->numSpecialAreas; i++)
    {
        mapSecId = sPokedexAreaScreen->specialAreaRegionMapSectionIds[i];

        // Get this section's rect from the *active* layout.
        u16 rx, ry, rw, rh;
        if (!Dex_FindLayoutRect(mapSecId, &rx, &ry, &rw, &rh))
            continue; // not on this layout (e.g., Kanto dungeon while viewing Johto) → skip

        // Convert rect center to screen pixels.
        // Center = (origin + rect) in tiles → pixels; add half-size to center multi-tile sections.
        s16 x = 8 * (originX + rx) + 4 + 4 * (rw - 1);
        s16 y = 8 * (originY + ry) + 4 + 4 * (rh - 1) + extraYPixels;

        spriteId = CreateSprite(&sAreaMarkerSpriteTemplate, x, y, 0);
        if (spriteId != MAX_SPRITES)
        {
            gSprites[spriteId].invisible = TRUE; // visibility is handled by the flash logic
            sPokedexAreaScreen->areaMarkerSprites[numSprites++] = &gSprites[spriteId];
        }
    }

    sPokedexAreaScreen->numAreaMarkerSprites = numSprites;
}


static void DestroyAreaScreenSprites(void)
{
    u16 i;

    // Destroy stone indicator sprites (each indicator is two side-by-side 32x16 sprites)
    if (sPokedexAreaScreen->indDaySpriteId != MAX_SPRITES)
    {
        DestroySprite(&gSprites[sPokedexAreaScreen->indDaySpriteId]);
        DestroySprite(&gSprites[sPokedexAreaScreen->indDaySpriteId + 1]);
        DestroySprite(&gSprites[sPokedexAreaScreen->indNightSpriteId]);
        DestroySprite(&gSprites[sPokedexAreaScreen->indNightSpriteId + 1]);
    }
    FreeSpriteTilesByTag(TAG_AREA_DAY_IND);
    FreeSpriteTilesByTag(TAG_AREA_NIGHT_IND);
    // Palette is shared with TAG_AREA_UNKNOWN; freed below with the rest of its resources.

    // Destroy area marker sprites
    FreeSpriteTilesByTag(TAG_AREA_MARKER);
    FreeSpritePaletteByTag(TAG_AREA_MARKER);
    for (i = 0; i < sPokedexAreaScreen->numAreaMarkerSprites; i++)
        DestroySprite(sPokedexAreaScreen->areaMarkerSprites[i]);

    // Destroy "Area Unknown" sprites
    FreeSpriteTilesByTag(TAG_AREA_UNKNOWN);
    FreeSpritePaletteByTag(TAG_AREA_UNKNOWN);
    for (i = 0; i < ARRAY_COUNT(sPokedexAreaScreen->areaUnknownSprites); i++)
    {
        if (sPokedexAreaScreen->areaUnknownSprites[i])
            DestroySprite(sPokedexAreaScreen->areaUnknownSprites[i]);
    }
}

static void LoadAreaUnknownGraphics(void)
{
    struct SpriteSheet spriteSheet = {
        .data = sPokedexAreaScreen->areaUnknownGraphicsBuffer,
        .size = sizeof(sPokedexAreaScreen->areaUnknownGraphicsBuffer),
        .tag = TAG_AREA_UNKNOWN,
    };
    LZ77UnCompWram(gPokedexAreaScreenAreaUnknown_Gfx, sPokedexAreaScreen->areaUnknownGraphicsBuffer);
    LoadSpriteSheet(&spriteSheet);
    LoadSpritePalette(&sAreaUnknownSpritePalette);
}

static void CreateAreaUnknownSprites(void)
{
    u16 i;

    if (sPokedexAreaScreen->numOverworldAreas || sPokedexAreaScreen->numSpecialAreas)
    {
        // The current species is present on the map, don't create any "Area Unknown" sprites
        for (i = 0; i < ARRAY_COUNT(sPokedexAreaScreen->areaUnknownSprites); i++)
            sPokedexAreaScreen->areaUnknownSprites[i] = NULL;
    }
    else
    {
        // The current species is absent on the map, try to create "Area Unknown" sprites
        for (i = 0; i < ARRAY_COUNT(sPokedexAreaScreen->areaUnknownSprites); i++)
        {
            u8 spriteId = CreateSprite(&sAreaUnknownSpriteTemplate, i * 32 + 160, 140, 0);
            if (spriteId != MAX_SPRITES)
            {
                gSprites[spriteId].oam.tileNum += i * 16;
                sPokedexAreaScreen->areaUnknownSprites[i] = &gSprites[spriteId];
            }
            else
            {
                // Failed to create sprite
                sPokedexAreaScreen->areaUnknownSprites[i] = NULL;
            }
        }
    }
}


static void LoadHGSSScreenSelectBarSubmenu(void)
{
    CopyToBgTilemapBuffer(1, sPokedexPlusHGSS_ScreenSelectBarSubmenu_Tilemap, 0, 0);
    CopyBgTilemapBufferToVram(1);
}

// Creates two 64x16 indicator graphics in the bottom-left corner, each split
// into a left and right 32x16 sprite.  The right half uses tileNum + 8.
// Only the sprites matching the current areaViewTimeMode are made visible.
// Sprite IDs are consecutive: day_left, day_right, night_left, night_right.
static void CreateAreaIndicatorSprites(void)
{
    u8 spriteId;
    struct SpriteSheet sheet;
    bool8 dayInvis, nightInvis;

    if (VarGet(VAR_TIME_BASED_ENCOUNTER) == 0)
        return;

    // Day indicator — 32x32 PNG stores two stacked 32x16 halves (left on top, right below).
    // Palette shared with TAG_AREA_UNKNOWN (loaded before the fade)
    sheet = (struct SpriteSheet){ sDayIndicatorTiles, 0x200, TAG_AREA_DAY_IND };
    LoadSpriteSheet(&sheet);
    sPokedexAreaScreen->indDaySpriteId = CreateSprite(&sDayIndicatorTemplate, 20, 148, 0);
    spriteId = CreateSprite(&sDayIndicatorTemplate, 52, 148, 0); // right half
    if (spriteId != MAX_SPRITES)
        gSprites[spriteId].oam.tileNum += 8;

    // Night indicator
    sheet = (struct SpriteSheet){ sNightIndicatorTiles, 0x200, TAG_AREA_NIGHT_IND };
    LoadSpriteSheet(&sheet);
    sPokedexAreaScreen->indNightSpriteId = CreateSprite(&sNightIndicatorTemplate, 20, 148, 0);
    spriteId = CreateSprite(&sNightIndicatorTemplate, 52, 148, 0); // right half
    if (spriteId != MAX_SPRITES)
        gSprites[spriteId].oam.tileNum += 8;

    // Set initial visibility: only the current time-mode indicator is shown
    if (sPokedexAreaScreen->indDaySpriteId != MAX_SPRITES)
    {
        dayInvis   = (sPokedexAreaScreen->areaViewTimeMode != 0);
        nightInvis = (sPokedexAreaScreen->areaViewTimeMode == 0);
        gSprites[sPokedexAreaScreen->indDaySpriteId].invisible       = dayInvis;
        gSprites[sPokedexAreaScreen->indDaySpriteId + 1].invisible   = dayInvis;
        gSprites[sPokedexAreaScreen->indNightSpriteId].invisible     = nightInvis;
        gSprites[sPokedexAreaScreen->indNightSpriteId + 1].invisible = nightInvis;
    }
}

// Applies the correct day/night tint to the region-map BG palettes (slots 7+8).
// Always restores BG 7+8 from ROM (via GetPokedexAreaMapPal) before tinting so
// the function is idempotent and safe to call regardless of previous tinting.
static void ApplyTimeModeToAreaMapPalette(void)
{
    u8 markerSlot;

    // Always restore BG 7+8 from ROM directly so this function is idempotent
    // regardless of any previous tinting applied to gPlttBufferUnfaded/Faded.
    CpuCopy32(GetPokedexAreaMapPal(), &gPlttBufferUnfaded[BG_PLTT_ID(7)], 32 * sizeof(u16));
    CpuCopy32(GetPokedexAreaMapPal(), &gPlttBufferFaded[BG_PLTT_ID(7)], 32 * sizeof(u16));

    // Restore the area-marker sprite palette from unfaded (always clean) as a base.
    markerSlot = IndexOfSpritePaletteTag(TAG_AREA_MARKER);
    if (markerSlot != 0xFF)
        CpuCopy32(&gPlttBufferUnfaded[OBJ_PLTT_ID(markerSlot)], &gPlttBufferFaded[OBJ_PLTT_ID(markerSlot)], 16 * sizeof(u16));

    if (sPokedexAreaScreen->areaViewTimeMode == 1)
    {
        // Blend BG palette slots toward a dark cool blue for night mode.
        BlendPalettes((1 << 7) | (1 << 8), 8, RGB(2, 4, 10));
        // Keep unfaded in sync so future fades also target the tinted palette.
        CpuCopy32(&gPlttBufferFaded[BG_PLTT_ID(7)], &gPlttBufferUnfaded[BG_PLTT_ID(7)], 32 * sizeof(u16));
    }
    // Day mode: the cache copies above are already the correct unmodified palettes.
}

// Advances the multi-frame time-mode toggle refresh one step per frame.
// Called from Task_HandlePokedexAreaScreenInput while data[2] != 0.
// Three frames total:
//   Frame 1 — swap all pre-built caches (encounters + glow tilemap) and DMA.
//   Frame 2 — rebuild marker sprites and area-unknown sprites.
//   Frame 3 — restart glow animation, flip indicator sprites, apply palette tint.
static void ContinueTimeModeRefresh(u8 taskId)
{
    u16 i;

    switch (gTasks[taskId].data[2])
    {
    case 1:
        // Frame 1: swap the active and alt encounter caches (pre-computed at
        // initial load — no header re-scan needed), swap the pre-built glow
        // tilemaps, and DMA the correct one into VRAM.  Zero BLDALPHA first so
        // the old highlight disappears cleanly.
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 16));
        {
            u16 j, tmp16;
            struct OverworldArea tmpArea;

            // Swap overworld (route/town) encounter arrays.
            for (j = 0; j < MAX_AREA_HIGHLIGHTS; j++)
            {
                tmpArea = sPokedexAreaScreen->overworldAreasWithMons[j];
                sPokedexAreaScreen->overworldAreasWithMons[j] = sPokedexAreaScreen->overworldAreasWithMons_alt[j];
                sPokedexAreaScreen->overworldAreasWithMons_alt[j] = tmpArea;
            }
            tmp16 = sPokedexAreaScreen->numOverworldAreas;
            sPokedexAreaScreen->numOverworldAreas     = sPokedexAreaScreen->numOverworldAreas_alt;
            sPokedexAreaScreen->numOverworldAreas_alt = tmp16;

            // Swap special-area (dungeon/landmark) marker arrays.
            for (j = 0; j < MAX_AREA_MARKERS; j++)
            {
                tmp16 = sPokedexAreaScreen->specialAreaRegionMapSectionIds[j];
                sPokedexAreaScreen->specialAreaRegionMapSectionIds[j] = sPokedexAreaScreen->specialAreaRegionMapSectionIds_alt[j];
                sPokedexAreaScreen->specialAreaRegionMapSectionIds_alt[j] = tmp16;
            }
            tmp16 = sPokedexAreaScreen->numSpecialAreas;
            sPokedexAreaScreen->numSpecialAreas     = sPokedexAreaScreen->numSpecialAreas_alt;
            sPokedexAreaScreen->numSpecialAreas_alt = tmp16;

            // Swap pre-built glow tilemaps so no rebuild is needed.
            for (j = 0; j < AREA_SCREEN_WIDTH * AREA_SCREEN_HEIGHT; j++)
            {
                tmp16 = sPokedexAreaScreen->areaGlowTilemap[j];
                sPokedexAreaScreen->areaGlowTilemap[j] = sPokedexAreaScreen->areaGlowTilemap_alt[j];
                sPokedexAreaScreen->areaGlowTilemap_alt[j] = tmp16;
            }
        }
        // DMA the swapped tilemap into VRAM.  LoadBgTilemap schedules a direct
        // DMA — do NOT call CopyBgTilemapBufferToVram afterwards.
        LoadBgTilemap(2, sPokedexAreaScreen->areaGlowTilemap, sizeof(sPokedexAreaScreen->areaGlowTilemap), 0);
        gTasks[taskId].data[2] = 2;
        break;
    case 2:
        // Frame 2: destroy and recreate marker sprites and Area Unknown sprites.
        FreeSpriteTilesByTag(TAG_AREA_MARKER);
        FreeSpritePaletteByTag(TAG_AREA_MARKER);
        for (i = 0; i < sPokedexAreaScreen->numAreaMarkerSprites; i++)
            DestroySprite(sPokedexAreaScreen->areaMarkerSprites[i]);
        sPokedexAreaScreen->numAreaMarkerSprites = 0;
        CreateAreaMarkerSprites();

        // Area Unknown sprites: the decompressed graphics in areaUnknownGraphicsBuffer
        // never change between modes, so skip LZ77UnCompWram and just re-upload
        // the existing buffer to OBJ VRAM via LoadSpriteSheet.
        // NOTE: do NOT free TAG_AREA_UNKNOWN's palette — indicator sprites share it.
        FreeSpriteTilesByTag(TAG_AREA_UNKNOWN);
        for (i = 0; i < ARRAY_COUNT(sPokedexAreaScreen->areaUnknownSprites); i++)
        {
            if (sPokedexAreaScreen->areaUnknownSprites[i])
                DestroySprite(sPokedexAreaScreen->areaUnknownSprites[i]);
            sPokedexAreaScreen->areaUnknownSprites[i] = NULL;
        }
        {
            struct SpriteSheet spriteSheet = {
                .data = sPokedexAreaScreen->areaUnknownGraphicsBuffer,
                .size = sizeof(sPokedexAreaScreen->areaUnknownGraphicsBuffer),
                .tag  = TAG_AREA_UNKNOWN,
            };
            LoadSpriteSheet(&spriteSheet);
            // Palette is shared with the indicator sprites and is already loaded;
            // LoadSpritePalette is a no-op if the tag is already registered, but
            // call it anyway to be safe in case it was evicted.
            LoadSpritePalette(&sAreaUnknownSpritePalette);
        }
        CreateAreaUnknownSprites();
        gTasks[taskId].data[2] = 3;
        break;
    case 3:
        // Frame 3: restart glow animation, flip indicator sprites, apply palette tint.
        StartAreaGlow();
        if (sPokedexAreaScreen->indDaySpriteId != MAX_SPRITES)
        {
            bool8 dayInvis   = (sPokedexAreaScreen->areaViewTimeMode != 0);
            bool8 nightInvis = (sPokedexAreaScreen->areaViewTimeMode == 0);
            gSprites[sPokedexAreaScreen->indDaySpriteId].invisible       = dayInvis;
            gSprites[sPokedexAreaScreen->indDaySpriteId + 1].invisible   = dayInvis;
            gSprites[sPokedexAreaScreen->indNightSpriteId].invisible     = nightInvis;
            gSprites[sPokedexAreaScreen->indNightSpriteId + 1].invisible = nightInvis;
        }
        ApplyTimeModeToAreaMapPalette();
        gTasks[taskId].data[2] = 0; // refresh complete
        break;
    }
}
