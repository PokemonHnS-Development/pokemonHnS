#include "fieldmap.h"

// Whether a palette has a night version, located at ((x + 9) % 16).pal
#define SWAP_PAL(x) ((x) < NUM_PALS_IN_PRIMARY ? 1 << (x) : 1 << ((x) - NUM_PALS_IN_PRIMARY))

// NOTE: Instead of using LIGHT_PAL, 
// consider taking a look at the .pla files
// to mark colors as lights, instead.
// The old method *should* still work, however.
// See the README for details.

// Whether a palette has lights
// the color indices to blend are stored in the palette's color 0
#define LIGHT_PAL(x) ((x) < NUM_PALS_IN_PRIMARY ? 1 << (x) : 1 << ((x) - NUM_PALS_IN_PRIMARY))

const struct Tileset gTileset_General =
{
    .isCompressed = TRUE,
    //.swapPalettes = SWAP_PAL(4),
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_General,
    .palettes = gTilesetPalettes_General,
    .metatiles = gMetatiles_General,
    .metatileAttributes = gMetatileAttributes_General,
    .callback = InitTilesetAnim_HoennGeneral,
};

const struct Tileset gTileset_Petalburg =
{
    .isCompressed = TRUE,
    .swapPalettes = SWAP_PAL(9),
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Petalburg,
    .palettes = gTilesetPalettes_Petalburg,
    .metatiles = gMetatiles_Petalburg,
    .metatileAttributes = gMetatileAttributes_Petalburg,
    .callback = InitTilesetAnim_Petalburg,
};

const struct Tileset gTileset_Rustboro =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Rustboro,
    .palettes = gTilesetPalettes_Rustboro,
    .metatiles = gMetatiles_Rustboro,
    .metatileAttributes = gMetatileAttributes_Rustboro,
    .callback = InitTilesetAnim_Rustboro,
};

const struct Tileset gTileset_Dewford =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Dewford,
    .palettes = gTilesetPalettes_Dewford,
    .metatiles = gMetatiles_Dewford,
    .metatileAttributes = gMetatileAttributes_Dewford,
    .callback = InitTilesetAnim_Dewford,
};

const struct Tileset gTileset_Slateport =
{
    .isCompressed = TRUE,
    //.swapPalettes = SWAP_PAL(6),
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Slateport,
    .palettes = gTilesetPalettes_Slateport,
    .metatiles = gMetatiles_Slateport,
    .metatileAttributes = gMetatileAttributes_Slateport,
    .callback = InitTilesetAnim_Slateport,
};

const struct Tileset gTileset_Mauville =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Mauville,
    .palettes = gTilesetPalettes_Mauville,
    .metatiles = gMetatiles_Mauville,
    .metatileAttributes = gMetatileAttributes_Mauville,
    .callback = InitTilesetAnim_Mauville,
};

const struct Tileset gTileset_Lavaridge =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Lavaridge,
    .palettes = gTilesetPalettes_Lavaridge,
    .metatiles = gMetatiles_Lavaridge,
    .metatileAttributes = gMetatileAttributes_Lavaridge,
    .callback = InitTilesetAnim_Lavaridge,
};

const struct Tileset gTileset_Fallarbor =
{
    .isCompressed = TRUE,
    .swapPalettes = SWAP_PAL(7),
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Fallarbor,
    .palettes = gTilesetPalettes_Fallarbor,
    .metatiles = gMetatiles_Fallarbor,
    .metatileAttributes = gMetatileAttributes_Fallarbor,
    .callback = InitTilesetAnim_Fallarbor,
};

const struct Tileset gTileset_Fortree =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Fortree,
    .palettes = gTilesetPalettes_Fortree,
    .metatiles = gMetatiles_Fortree,
    .metatileAttributes = gMetatileAttributes_Fortree,
    .callback = InitTilesetAnim_Fortree,
};

const struct Tileset gTileset_Lilycove =
{
    .isCompressed = TRUE,
    //.swapPalettes = SWAP_PAL(6),
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Lilycove,
    .palettes = gTilesetPalettes_Lilycove,
    .metatiles = gMetatiles_Lilycove,
    .metatileAttributes = gMetatileAttributes_Lilycove,
    .callback = InitTilesetAnim_Lilycove,
};

const struct Tileset gTileset_Mossdeep =
{
    .isCompressed = TRUE,
    //.swapPalettes = SWAP_PAL(8),
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Mossdeep,
    .palettes = gTilesetPalettes_Mossdeep,
    .metatiles = gMetatiles_Mossdeep,
    .metatileAttributes = gMetatileAttributes_Mossdeep,
    .callback = InitTilesetAnim_Mossdeep,
};

const struct Tileset gTileset_EverGrande =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_EverGrande,
    .palettes = gTilesetPalettes_EverGrande,
    .metatiles = gMetatiles_EverGrande,
    .metatileAttributes = gMetatileAttributes_EverGrande,
    .callback = InitTilesetAnim_EverGrande,
    .swapPalettes = SWAP_PAL(8),
};

const struct Tileset gTileset_Pacifidlog =
{
    .isCompressed = TRUE,
    .swapPalettes = SWAP_PAL(9),
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Pacifidlog,
    .palettes = gTilesetPalettes_Pacifidlog,
    .metatiles = gMetatiles_Pacifidlog,
    .metatileAttributes = gMetatileAttributes_Pacifidlog,
    .callback = InitTilesetAnim_Pacifidlog,
};

const struct Tileset gTileset_Sootopolis =
{
    .isCompressed = TRUE,
    //.swapPalettes = SWAP_PAL(6),
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Sootopolis,
    .palettes = gTilesetPalettes_Sootopolis,
    .metatiles = gMetatiles_Sootopolis,
    .metatileAttributes = gMetatileAttributes_Sootopolis,
    .callback = InitTilesetAnim_Sootopolis,
};

const struct Tileset gTileset_BattleFrontierOutsideWest =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattleFrontierOutsideWest,
    .palettes = gTilesetPalettes_BattleFrontierOutsideWest,
    .metatiles = gMetatiles_BattleFrontierOutsideWest,
    .metatileAttributes = gMetatileAttributes_BattleFrontierOutsideWest,
    .callback = InitTilesetAnim_BattleFrontierOutsideWest,
};

const struct Tileset gTileset_BattleFrontierOutsideEast =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattleFrontierOutsideEast,
    .palettes = gTilesetPalettes_BattleFrontierOutsideEast,
    .metatiles = gMetatiles_BattleFrontierOutsideEast,
    .metatileAttributes = gMetatileAttributes_BattleFrontierOutsideEast,
    .callback = InitTilesetAnim_BattleFrontierOutsideEast,
};

const struct Tileset gTileset_Building =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_InsideBuilding,
    .palettes = gTilesetPalettes_InsideBuilding,
    .metatiles = gMetatiles_InsideBuilding,
    .metatileAttributes = gMetatileAttributes_InsideBuilding,
    .callback = InitTilesetAnim_Building,
};

const struct Tileset gTileset_Shop =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Shop,
    .palettes = gTilesetPalettes_Shop,
    .metatiles = gMetatiles_Shop,
    .metatileAttributes = gMetatileAttributes_Shop,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonCenter =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonCenter,
    .palettes = gTilesetPalettes_PokemonCenter,
    .metatiles = gMetatiles_PokemonCenter,
    .metatileAttributes = gMetatileAttributes_PokemonCenter,
    .callback = NULL,
};

const struct Tileset gTileset_Cave =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave,
    .palettes = gTilesetPalettes_Cave,
    .metatiles = gMetatiles_Cave,
    .metatileAttributes = gMetatileAttributes_Cave,
    .callback = InitTilesetAnim_Cave,
};

const struct Tileset gTileset_PokemonSchool =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonSchool,
    .palettes = gTilesetPalettes_PokemonSchool,
    .metatiles = gMetatiles_PokemonSchool,
    .metatileAttributes = gMetatileAttributes_PokemonSchool,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonFanClub =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonFanClub,
    .palettes = gTilesetPalettes_PokemonFanClub,
    .metatiles = gMetatiles_PokemonFanClub,
    .metatileAttributes = gMetatileAttributes_PokemonFanClub,
    .callback = NULL,
};

const struct Tileset gTileset_Unused1 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Unused1,
    .palettes = gTilesetPalettes_Unused1,
    .metatiles = gMetatiles_Unused1,
    .metatileAttributes = gMetatileAttributes_Unused1,
    .callback = NULL,
};

const struct Tileset gTileset_MeteorFalls =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MeteorFalls,
    .palettes = gTilesetPalettes_MeteorFalls,
    .metatiles = gMetatiles_MeteorFalls,
    .metatileAttributes = gMetatileAttributes_MeteorFalls,
    .callback = NULL,
};

const struct Tileset gTileset_OceanicMuseum =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_OceanicMuseum,
    .palettes = gTilesetPalettes_OceanicMuseum,
    .metatiles = gMetatiles_OceanicMuseum,
    .metatileAttributes = gMetatileAttributes_OceanicMuseum,
    .callback = NULL,
};

const struct Tileset gTileset_CableClub =
{
    .isCompressed = FALSE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CableClub,
    .palettes = gTilesetPalettes_CableClub,
    .metatiles = gMetatiles_CableClub,
    .metatileAttributes = gMetatileAttributes_CableClub,
    .callback = NULL,
};

const struct Tileset gTileset_SeashoreHouse =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeashoreHouse,
    .palettes = gTilesetPalettes_SeashoreHouse,
    .metatiles = gMetatiles_SeashoreHouse,
    .metatileAttributes = gMetatileAttributes_SeashoreHouse,
    .callback = NULL,
};

const struct Tileset gTileset_PrettyPetalFlowerShop =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PrettyPetalFlowerShop,
    .palettes = gTilesetPalettes_PrettyPetalFlowerShop,
    .metatiles = gMetatiles_PrettyPetalFlowerShop,
    .metatileAttributes = gMetatileAttributes_PrettyPetalFlowerShop,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonDayCare =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonDayCare,
    .palettes = gTilesetPalettes_PokemonDayCare,
    .metatiles = gMetatiles_PokemonDayCare,
    .metatileAttributes = gMetatileAttributes_PokemonDayCare,
    .callback = NULL,
};

const struct Tileset gTileset_Facility =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Facility,
    .palettes = gTilesetPalettes_Facility,
    .metatiles = gMetatiles_Facility,
    .metatileAttributes = gMetatileAttributes_Facility,
    .callback = NULL,
};

const struct Tileset gTileset_BikeShop =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BikeShop,
    .palettes = gTilesetPalettes_BikeShop,
    .metatiles = gMetatiles_BikeShop,
    .metatileAttributes = gMetatileAttributes_BikeShop,
    .callback = InitTilesetAnim_BikeShop,
};

const struct Tileset gTileset_RusturfTunnel =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RusturfTunnel,
    .palettes = gTilesetPalettes_RusturfTunnel,
    .metatiles = gMetatiles_RusturfTunnel,
    .metatileAttributes = gMetatileAttributes_RusturfTunnel,
    .callback = NULL,
};

const struct Tileset gTileset_SecretBaseBrownCave =
{
    .isCompressed = FALSE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SecretBaseBrownCave,
    .palettes = gTilesetPalettes_SecretBaseBrownCave,
    .metatiles = gMetatiles_SecretBaseSecondary,
    .metatileAttributes = gMetatileAttributes_SecretBaseSecondary,
    .callback = NULL,
};

const struct Tileset gTileset_SecretBaseTree =
{
    .isCompressed = FALSE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SecretBaseTree,
    .palettes = gTilesetPalettes_SecretBaseTree,
    .metatiles = gMetatiles_SecretBaseSecondary,
    .metatileAttributes = gMetatileAttributes_SecretBaseSecondary,
    .callback = NULL,
};

const struct Tileset gTileset_SecretBaseShrub =
{
    .isCompressed = FALSE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SecretBaseShrub,
    .palettes = gTilesetPalettes_SecretBaseShrub,
    .metatiles = gMetatiles_SecretBaseSecondary,
    .metatileAttributes = gMetatileAttributes_SecretBaseSecondary,
    .callback = NULL,
};

const struct Tileset gTileset_SecretBaseBlueCave =
{
    .isCompressed = FALSE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SecretBaseBlueCave,
    .palettes = gTilesetPalettes_SecretBaseBlueCave,
    .metatiles = gMetatiles_SecretBaseSecondary,
    .metatileAttributes = gMetatileAttributes_SecretBaseSecondary,
    .callback = NULL,
};

const struct Tileset gTileset_SecretBaseYellowCave =
{
    .isCompressed = FALSE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SecretBaseYellowCave,
    .palettes = gTilesetPalettes_SecretBaseYellowCave,
    .metatiles = gMetatiles_SecretBaseSecondary,
    .metatileAttributes = gMetatileAttributes_SecretBaseSecondary,
    .callback = NULL,
};

const struct Tileset gTileset_SecretBaseRedCave =
{
    .isCompressed = FALSE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SecretBaseRedCave,
    .palettes = gTilesetPalettes_SecretBaseRedCave,
    .metatiles = gMetatiles_SecretBaseSecondary,
    .metatileAttributes = gMetatileAttributes_SecretBaseSecondary,
    .callback = NULL,
};

const struct Tileset gTileset_InsideOfTruck =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_InsideOfTruck,
    .palettes = gTilesetPalettes_InsideOfTruck,
    .metatiles = gMetatiles_InsideOfTruck,
    .metatileAttributes = gMetatileAttributes_InsideOfTruck,
    .callback = NULL,
};

const struct Tileset gTileset_Unused2 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Unused2,
    .palettes = gTilesetPalettes_Unused2,
    .metatiles = gMetatiles_Unused2,
    .metatileAttributes = gMetatileAttributes_Unused2,
    .callback = NULL,
};

const struct Tileset gTileset_Contest =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Contest,
    .palettes = gTilesetPalettes_Contest,
    .metatiles = gMetatiles_Contest,
    .metatileAttributes = gMetatileAttributes_Contest,
    .callback = NULL,
};

const struct Tileset gTileset_LilycoveMuseum =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_LilycoveMuseum,
    .palettes = gTilesetPalettes_LilycoveMuseum,
    .metatiles = gMetatiles_LilycoveMuseum,
    .metatileAttributes = gMetatileAttributes_LilycoveMuseum,
    .callback = NULL,
};

const struct Tileset gTileset_BrendansMaysHouse =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BrendansMaysHouse,
    .palettes = gTilesetPalettes_BrendansMaysHouse,
    .metatiles = gMetatiles_BrendansMaysHouse,
    .metatileAttributes = gMetatileAttributes_BrendansMaysHouse,
    .callback = NULL,
};

const struct Tileset gTileset_Lab =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Lab,
    .palettes = gTilesetPalettes_Lab,
    .metatiles = gMetatiles_Lab,
    .metatileAttributes = gMetatileAttributes_Lab,
    .callback = NULL,
};

const struct Tileset gTileset_Underwater =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Underwater,
    .palettes = gTilesetPalettes_Underwater,
    .metatiles = gMetatiles_Underwater,
    .metatileAttributes = gMetatileAttributes_Underwater,
    .callback = InitTilesetAnim_Underwater,
};

const struct Tileset gTileset_PetalburgGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PetalburgGym,
    .palettes = gTilesetPalettes_PetalburgGym,
    .metatiles = gMetatiles_PetalburgGym,
    .metatileAttributes = gMetatileAttributes_PetalburgGym,
    .callback = NULL,
};

const struct Tileset gTileset_SootopolisGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SootopolisGym,
    .palettes = gTilesetPalettes_SootopolisGym,
    .metatiles = gMetatiles_SootopolisGym,
    .metatileAttributes = gMetatileAttributes_SootopolisGym,
    .callback = InitTilesetAnim_SootopolisGym,
};

const struct Tileset gTileset_GenericBuilding =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GenericBuilding,
    .palettes = gTilesetPalettes_GenericBuilding,
    .metatiles = gMetatiles_GenericBuilding,
    .metatileAttributes = gMetatileAttributes_GenericBuilding,
    .callback = NULL,
};

const struct Tileset gTileset_MauvilleGameCorner =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MauvilleGameCorner,
    .palettes = gTilesetPalettes_MauvilleGameCorner,
    .metatiles = gMetatiles_MauvilleGameCorner,
    .metatileAttributes = gMetatileAttributes_MauvilleGameCorner,
    .callback = NULL,
};

const struct Tileset gTileset_RustboroGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RustboroGym,
    .palettes = gTilesetPalettes_RustboroGym,
    .metatiles = gMetatiles_RustboroGym,
    .metatileAttributes = gMetatileAttributes_RustboroGym,
    .callback = NULL,
};

const struct Tileset gTileset_DewfordGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_DewfordGym,
    .palettes = gTilesetPalettes_DewfordGym,
    .metatiles = gMetatiles_DewfordGym,
    .metatileAttributes = gMetatileAttributes_DewfordGym,
    .callback = NULL,
};

const struct Tileset gTileset_MauvilleGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MauvilleGym,
    .palettes = gTilesetPalettes_MauvilleGym,
    .metatiles = gMetatiles_MauvilleGym,
    .metatileAttributes = gMetatileAttributes_MauvilleGym,
    .callback = InitTilesetAnim_MauvilleGym,
};

const struct Tileset gTileset_LavaridgeGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_LavaridgeGym,
    .palettes = gTilesetPalettes_LavaridgeGym,
    .metatiles = gMetatiles_LavaridgeGym,
    .metatileAttributes = gMetatileAttributes_LavaridgeGym,
    .callback = NULL,
};

const struct Tileset gTileset_TrickHousePuzzle =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_TrickHousePuzzle,
    .palettes = gTilesetPalettes_TrickHousePuzzle,
    .metatiles = gMetatiles_TrickHousePuzzle,
    .metatileAttributes = gMetatileAttributes_TrickHousePuzzle,
    .callback = NULL,
};

const struct Tileset gTileset_FortreeGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_FortreeGym,
    .palettes = gTilesetPalettes_FortreeGym,
    .metatiles = gMetatiles_FortreeGym,
    .metatileAttributes = gMetatileAttributes_FortreeGym,
    .callback = NULL,
};

const struct Tileset gTileset_MossdeepGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MossdeepGym,
    .palettes = gTilesetPalettes_MossdeepGym,
    .metatiles = gMetatiles_MossdeepGym,
    .metatileAttributes = gMetatileAttributes_MossdeepGym,
    .callback = NULL,
};

const struct Tileset gTileset_InsideShip =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_InsideShip,
    .palettes = gTilesetPalettes_InsideShip,
    .metatiles = gMetatiles_InsideShip,
    .metatileAttributes = gMetatileAttributes_InsideShip,
    .callback = NULL,
};

const struct Tileset gTileset_SecretBase =
{
    .isCompressed = FALSE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_SecretBase,
    .palettes = gTilesetPalettes_SecretBase,
    .metatiles = gMetatiles_SecretBasePrimary,
    .metatileAttributes = gMetatileAttributes_SecretBasePrimary,
    .callback = NULL,
};

const struct Tileset * const gTilesetPointer_SecretBase = &gTileset_SecretBase;
const struct Tileset * const gTilesetPointer_SecretBaseRedCave = &gTileset_SecretBaseRedCave;

const struct Tileset gTileset_EliteFour =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_EliteFour,
    .palettes = gTilesetPalettes_EliteFour,
    .metatiles = gMetatiles_EliteFour,
    .metatileAttributes = gMetatileAttributes_EliteFour,
    .callback = InitTilesetAnim_EliteFour,
};

const struct Tileset gTileset_BattleFrontier =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattleFrontier,
    .palettes = gTilesetPalettes_BattleFrontier,
    .metatiles = gMetatiles_BattleFrontier,
    .metatileAttributes = gMetatileAttributes_BattleFrontier,
    .callback = NULL,
};

const struct Tileset gTileset_BattlePalace =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattlePalace,
    .palettes = gTilesetPalettes_BattlePalace,
    .metatiles = gMetatiles_BattlePalace,
    .metatileAttributes = gMetatileAttributes_BattlePalace,
    .callback = NULL,
};

const struct Tileset gTileset_BattleDome =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattleDome,
    .palettes = gTilesetPalettes_BattleDome,
    .metatiles = gMetatiles_BattleDome,
    .metatileAttributes = gMetatileAttributes_BattleDome,
    .callback = InitTilesetAnim_BattleDome,
};

const struct Tileset gTileset_BattleFactory =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattleFactory,
    .palettes = gTilesetPalettes_BattleFactory,
    .metatiles = gMetatiles_BattleFactory,
    .metatileAttributes = gMetatileAttributes_BattleFactory,
    .callback = NULL,
};

const struct Tileset gTileset_BattlePike =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattlePike,
    .palettes = gTilesetPalettes_BattlePike,
    .metatiles = gMetatiles_BattlePike,
    .metatileAttributes = gMetatileAttributes_BattlePike,
    .callback = NULL,
};

const struct Tileset gTileset_BattleArena =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattleArena,
    .palettes = gTilesetPalettes_BattleArena,
    .metatiles = gMetatiles_BattleArena,
    .metatileAttributes = gMetatileAttributes_BattleArena,
    .callback = NULL,
};

const struct Tileset gTileset_BattlePyramid =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattlePyramid,
    .palettes = gTilesetPalettes_BattlePyramid,
    .metatiles = gMetatiles_BattlePyramid,
    .metatileAttributes = gMetatileAttributes_BattlePyramid,
    .callback = InitTilesetAnim_BattlePyramid,
};

const struct Tileset gTileset_MirageTower =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MirageTower,
    .palettes = gTilesetPalettes_MirageTower,
    .metatiles = gMetatiles_MirageTower,
    .metatileAttributes = gMetatileAttributes_MirageTower,
    .callback = NULL,
};

const struct Tileset gTileset_MossdeepGameCorner =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MossdeepGameCorner,
    .palettes = gTilesetPalettes_MossdeepGameCorner,
    .metatiles = gMetatiles_MossdeepGameCorner,
    .metatileAttributes = gMetatileAttributes_MossdeepGameCorner,
    .callback = NULL,
};

const struct Tileset gTileset_IslandHarbor =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_IslandHarbor,
    .palettes = gTilesetPalettes_IslandHarbor,
    .metatiles = gMetatiles_IslandHarbor,
    .metatileAttributes = gMetatileAttributes_IslandHarbor,
    .callback = NULL,
};

const struct Tileset gTileset_TrainerHill =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_TrainerHill,
    .palettes = gTilesetPalettes_TrainerHill,
    .metatiles = gMetatiles_TrainerHill,
    .metatileAttributes = gMetatileAttributes_TrainerHill,
    .callback = NULL,
};

const struct Tileset gTileset_NavelRock =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_NavelRock,
    .palettes = gTilesetPalettes_NavelRock,
    .metatiles = gMetatiles_NavelRock,
    .metatileAttributes = gMetatileAttributes_NavelRock,
    .callback = NULL,
};

const struct Tileset gTileset_BattleFrontierRankingHall =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattleFrontierRankingHall,
    .palettes = gTilesetPalettes_BattleFrontierRankingHall,
    .metatiles = gMetatiles_BattleFrontierRankingHall,
    .metatileAttributes = gMetatileAttributes_BattleFrontierRankingHall,
    .callback = NULL,
};

const struct Tileset gTileset_BattleTent =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattleTent,
    .palettes = gTilesetPalettes_BattleTent,
    .metatiles = gMetatiles_BattleTent,
    .metatileAttributes = gMetatileAttributes_BattleTent,
    .callback = NULL,
};

const struct Tileset gTileset_MysteryEventsHouse =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MysteryEventsHouse,
    .palettes = gTilesetPalettes_MysteryEventsHouse,
    .metatiles = gMetatiles_MysteryEventsHouse,
    .metatileAttributes = gMetatileAttributes_MysteryEventsHouse,
    .callback = NULL,
};

const struct Tileset gTileset_UnionRoom =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_UnionRoom,
    .palettes = gTilesetPalettes_UnionRoom,
    .metatiles = gMetatiles_UnionRoom,
    .metatileAttributes = gMetatileAttributes_UnionRoom,
    .callback = NULL,
};

const struct Tileset gTileset_Johto_General =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_General,
    .palettes = gTilesetPalettes_Johto_General,
    .metatiles = gMetatiles_Johto_General,
    .metatileAttributes = gMetatileAttributes_Johto_General,
    .callback = InitTilesetAnim_General,
};

const struct Tileset gTileset_Kanto_PokemonCenter =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Kanto_PokemonCenter,
    .palettes = gTilesetPalettes_Kanto_PokemonCenter,
    .metatiles = gMetatiles_Kanto_PokemonCenter,
    .metatileAttributes = gMetatileAttributes_Kanto_PokemonCenter,
    .callback = NULL,
};

const struct Tileset gTileset_Kanto_Building =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Kanto_Building,
    .palettes = gTilesetPalettes_Kanto_Building,
    .metatiles = gMetatiles_Kanto_Building,
    .metatileAttributes = gMetatileAttributes_Kanto_Building,
    .callback = NULL,
};

const struct Tileset gTileset_CherrygroveCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CherrygroveCity,
    .palettes = gTilesetPalettes_CherrygroveCity,
    .metatiles = gMetatiles_CherrygroveCity,
    .metatileAttributes = gMetatileAttributes_CherrygroveCity,
    .callback = NULL,
};

const struct Tileset gTileset_Unused3 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Unused3,
    .palettes = gTilesetPalettes_Unused3,
    .metatiles = gMetatiles_Unused3,
    .metatileAttributes = gMetatileAttributes_Unused3,
    .callback = NULL,
};

const struct Tileset gTileset_Johto_Building =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_Building,
    .palettes = gTilesetPalettes_Johto_Building,
    .metatiles = gMetatiles_Johto_Building,
    .metatileAttributes = gMetatileAttributes_Johto_Building,
    .callback = NULL,
};

const struct Tileset gTileset_MahoganyTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MahoganyTown,
    .palettes = gTilesetPalettes_MahoganyTown,
    .metatiles = gMetatiles_MahoganyTown,
    .metatileAttributes = gMetatileAttributes_MahoganyTown,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_Default =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Default,
    .palettes = gTilesetPalettes_Cave_Default,
    .metatiles = gMetatiles_Cave_Default,
    .metatileAttributes = gMetatileAttributes_Cave_Default,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_Sandy =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Sandy,
    .palettes = gTilesetPalettes_Cave_Sandy,
    .metatiles = gMetatiles_Cave_Sandy,
    .metatileAttributes = gMetatileAttributes_Cave_Sandy,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_Green =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Green,
    .palettes = gTilesetPalettes_Cave_Green,
    .metatiles = gMetatiles_Cave_Green,
    .metatileAttributes = gMetatileAttributes_Cave_Green,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_Ice =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Ice,
    .palettes = gTilesetPalettes_Cave_Ice,
    .metatiles = gMetatiles_Cave_Ice,
    .metatileAttributes = gMetatileAttributes_Cave_Ice,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_Gray =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_Gray,
    .palettes = gTilesetPalettes_Cave_Gray,
    .metatiles = gMetatiles_Cave_Gray,
    .metatileAttributes = gMetatileAttributes_Cave_Gray,
    .callback = NULL,
};

const struct Tileset gTileset_PowerPlant_GeneratorRoom =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PowerPlant_GeneratorRoom,
    .palettes = gTilesetPalettes_PowerPlant_GeneratorRoom,
    .metatiles = gMetatiles_PowerPlant_GeneratorRoom,
    .metatileAttributes = gMetatileAttributes_PowerPlant_GeneratorRoom,
    .callback = NULL,
};

const struct Tileset gTileset_RuinsOfAlph_B1F =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RuinsOfAlph_B1F,
    .palettes = gTilesetPalettes_RuinsOfAlph_B1F,
    .metatiles = gMetatiles_RuinsOfAlph_B1F,
    .metatileAttributes = gMetatileAttributes_RuinsOfAlph_B1F,
    .callback = NULL,
};

const struct Tileset gTileset_DragonsDen_Shrine =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_DragonsDen_Shrine,
    .palettes = gTilesetPalettes_DragonsDen_Shrine,
    .metatiles = gMetatiles_DragonsDen_Shrine,
    .metatileAttributes = gMetatileAttributes_DragonsDen_Shrine,
    .callback = NULL,
};

const struct Tileset gTileset_IndigoPlateau =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_IndigoPlateau,
    .palettes = gTilesetPalettes_IndigoPlateau,
    .metatiles = gMetatiles_IndigoPlateau,
    .metatileAttributes = gMetatileAttributes_IndigoPlateau,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonCenter_White =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonCenter_White,
    .palettes = gTilesetPalettes_PokemonCenter_White,
    .metatiles = gMetatiles_PokemonCenter_White,
    .metatileAttributes = gMetatileAttributes_PokemonCenter_White,
    .callback = NULL,
};

const struct Tileset gTileset_Gate_Standard =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Gate_Standard,
    .palettes = gTilesetPalettes_Gate_Standard,
    .metatiles = gMetatiles_Gate_Standard,
    .metatileAttributes = gMetatileAttributes_Gate_Standard,
    .callback = NULL,
};

const struct Tileset gTileset_SaffronCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SaffronCity,
    .palettes = gTilesetPalettes_SaffronCity,
    .metatiles = gMetatiles_SaffronCity,
    .metatileAttributes = gMetatileAttributes_SaffronCity,
    .callback = NULL,
};

const struct Tileset gTileset_OlivineCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_OlivineCity,
    .palettes = gTilesetPalettes_OlivineCity,
    .metatiles = gMetatiles_OlivineCity,
    .metatileAttributes = gMetatileAttributes_OlivineCity,
    .callback = NULL,
};

const struct Tileset gTileset_House_Lab =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_House_Lab,
    .palettes = gTilesetPalettes_House_Lab,
    .metatiles = gMetatiles_House_Lab,
    .metatileAttributes = gMetatileAttributes_House_Lab,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianCity,
    .palettes = gTilesetPalettes_ViridianCity,
    .metatiles = gMetatiles_ViridianCity,
    .metatileAttributes = gMetatileAttributes_ViridianCity,
    .callback = NULL,
};

const struct Tileset gTileset_EcruteakTheater =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_EcruteakTheater,
    .palettes = gTilesetPalettes_EcruteakTheater,
    .metatiles = gMetatiles_EcruteakTheater,
    .metatileAttributes = gMetatileAttributes_EcruteakTheater,
    .callback = InitTilesetAnim_ecruteak_theater,
};

const struct Tileset gTileset_PortIndoor =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PortIndoor,
    .palettes = gTilesetPalettes_PortIndoor,
    .metatiles = gMetatiles_PortIndoor,
    .metatileAttributes = gMetatileAttributes_PortIndoor,
    .callback = NULL,
};

const struct Tileset gTileset_Cafe =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cafe,
    .palettes = gTilesetPalettes_Cafe,
    .metatiles = gMetatiles_Cafe,
    .metatileAttributes = gMetatileAttributes_Cafe,
    .callback = NULL,
};

const struct Tileset gTileset_JohtoMart =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_JohtoMart,
    .palettes = gTilesetPalettes_JohtoMart,
    .metatiles = gMetatiles_JohtoMart,
    .metatileAttributes = gMetatileAttributes_JohtoMart,
    .callback = NULL,
};

const struct Tileset gTileset_House_2 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_House_2,
    .palettes = gTilesetPalettes_House_2,
    .metatiles = gMetatiles_House_2,
    .metatileAttributes = gMetatileAttributes_House_2,
    .callback = NULL,
};

const struct Tileset gTileset_KantoMart =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_KantoMart,
    .palettes = gTilesetPalettes_KantoMart,
    .metatiles = gMetatiles_KantoMart,
    .metatileAttributes = gMetatileAttributes_KantoMart,
    .callback = NULL,
};

const struct Tileset gTileset_PlayersHouse =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PlayersHouse,
    .palettes = gTilesetPalettes_PlayersHouse,
    .metatiles = gMetatiles_PlayersHouse,
    .metatileAttributes = gMetatileAttributes_PlayersHouse,
    .callback = NULL,
};

const struct Tileset gTileset_Kanto_General =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Kanto_General,
    .palettes = gTilesetPalettes_Kanto_General,
    .metatiles = gMetatiles_Kanto_General,
    .metatileAttributes = gMetatileAttributes_Kanto_General,
    .callback = InitTilesetAnim_General,
};

const struct Tileset gTileset_Route38_Farmland =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Route38_Farmland,
    .palettes = gTilesetPalettes_Route38_Farmland,
    .metatiles = gMetatiles_Route38_Farmland,
    .metatileAttributes = gMetatileAttributes_Route38_Farmland,
    .callback = NULL,
};

const struct Tileset gTileset_NewBarkTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_NewBarkTown,
    .palettes = gTilesetPalettes_NewBarkTown,
    .metatiles = gMetatiles_NewBarkTown,
    .metatileAttributes = gMetatileAttributes_NewBarkTown,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianForest =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianForest,
    .palettes = gTilesetPalettes_ViridianForest,
    .metatiles = gMetatiles_ViridianForest,
    .metatileAttributes = gMetatileAttributes_ViridianForest,
    .callback = NULL,
};

const struct Tileset gTileset_RuinsOfAlph_Outside =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RuinsOfAlph_Outside,
    .palettes = gTilesetPalettes_RuinsOfAlph_Outside,
    .metatiles = gMetatiles_RuinsOfAlph_Outside,
    .metatileAttributes = gMetatileAttributes_RuinsOfAlph_Outside,
    .callback = NULL,
};

const struct Tileset gTileset_TrainerSchool =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_TrainerSchool,
    .palettes = gTilesetPalettes_TrainerSchool,
    .metatiles = gMetatiles_TrainerSchool,
    .metatileAttributes = gMetatileAttributes_TrainerSchool,
    .callback = NULL,
};

const struct Tileset gTileset_Goldenrod_Underground_Storage =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Goldenrod_Underground_Storage,
    .palettes = gTilesetPalettes_Goldenrod_Underground_Storage,
    .metatiles = gMetatiles_Goldenrod_Underground_Storage,
    .metatileAttributes = gMetatileAttributes_Goldenrod_Underground_Storage,
    .callback = NULL,
};

const struct Tileset gTileset_AzaleaTown_Gym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_azalea_town_gym,
    .palettes = gTilesetPalettes_azalea_town_gym,
    .metatiles = gMetatiles_azalea_town_gym,
    .metatileAttributes = gMetatileAttributes_azalea_town_gym,
    .callback = InitTilesetAnim_AzaleaTown_Gym,
};

const struct Tileset gTileset_Goldenrod =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Goldenrod,
    .palettes = gTilesetPalettes_Goldenrod,
    .metatiles = gMetatiles_Goldenrod,
    .metatileAttributes = gMetatileAttributes_Goldenrod,
    .callback = NULL,
};

const struct Tileset gTileset_NationalPark =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_NationalPark,
    .palettes = gTilesetPalettes_NationalPark,
    .metatiles = gMetatiles_NationalPark,
    .metatileAttributes = gMetatileAttributes_NationalPark,
    .callback = InitTilesetAnim_NationalPark,
};

const struct Tileset gTileset_GoldenrodUndergroundTunnel =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GoldenrodUndergroundTunnel,
    .palettes = gTilesetPalettes_GoldenrodUndergroundTunnel,
    .metatiles = gMetatiles_GoldenrodUndergroundTunnel,
    .metatileAttributes = gMetatileAttributes_GoldenrodUndergroundTunnel,
    .callback = NULL,
};

const struct Tileset gTileset_GoldenrodUndergroundRocket =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GoldenrodUndergroundRocket,
    .palettes = gTilesetPalettes_GoldenrodUndergroundRocket,
    .metatiles = gMetatiles_GoldenrodUndergroundRocket,
    .metatileAttributes = gMetatileAttributes_GoldenrodUndergroundRocket,
    .callback = NULL,
};

const struct Tileset gTileset_GoldenrodCity_TrainStation =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GoldenrodCity_TrainStation,
    .palettes = gTilesetPalettes_GoldenrodCity_TrainStation,
    .metatiles = gMetatiles_GoldenrodCity_TrainStation,
    .metatileAttributes = gMetatileAttributes_GoldenrodCity_TrainStation,
    .callback = NULL,
};

const struct Tileset gTileset_GameCorner =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GameCorner,
    .palettes = gTilesetPalettes_GameCorner,
    .metatiles = gMetatiles_GameCorner,
    .metatileAttributes = gMetatileAttributes_GameCorner,
    .callback = NULL,
};

const struct Tileset gTileset_DepartmentStore =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_DepartmentStore,
    .palettes = gTilesetPalettes_DepartmentStore,
    .metatiles = gMetatiles_DepartmentStore,
    .metatileAttributes = gMetatileAttributes_DepartmentStore,
    .callback = NULL,
};

const struct Tileset gTileset_CianwoodCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CianwoodCity,
    .palettes = gTilesetPalettes_CianwoodCity,
    .metatiles = gMetatiles_CianwoodCity,
    .metatileAttributes = gMetatileAttributes_CianwoodCity,
    .callback = NULL,
};

const struct Tileset gTileset_SafariZone_Entrance =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SafariZone_Entrance,
    .palettes = gTilesetPalettes_SafariZone_Entrance,
    .metatiles = gMetatiles_SafariZone_Entrance,
    .metatileAttributes = gMetatileAttributes_SafariZone_Entrance,
    .callback = NULL,
};

const struct Tileset gTileset_Johto_NorthEast =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_NorthEast,
    .palettes = gTilesetPalettes_Johto_NorthEast,
    .metatiles = gMetatiles_Johto_NorthEast,
    .metatileAttributes = gMetatileAttributes_Johto_NorthEast,
    .callback = InitTilesetAnim_General,
};

const struct Tileset gTileset_Blackthorn =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Blackthorn,
    .palettes = gTilesetPalettes_Blackthorn,
    .metatiles = gMetatiles_Blackthorn,
    .metatileAttributes = gMetatileAttributes_Blackthorn,
    .callback = NULL,
};

const struct Tileset gTileset_BlackthornGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BlackthornGym,
    .palettes = gTilesetPalettes_BlackthornGym,
    .metatiles = gMetatiles_BlackthornGym,
    .metatileAttributes = gMetatileAttributes_BlackthornGym,
    .callback = InitTilesetAnim_Lavaridge,
};

const struct Tileset gTileset_PewterCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PewterCity,
    .palettes = gTilesetPalettes_PewterCity,
    .metatiles = gMetatiles_PewterCity,
    .metatileAttributes = gMetatileAttributes_PewterCity,
    .callback = NULL,
};

const struct Tileset gTileset_PalletTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PalletTown,
    .palettes = gTilesetPalettes_PalletTown,
    .metatiles = gMetatiles_PalletTown,
    .metatileAttributes = gMetatileAttributes_PalletTown,
    .callback = NULL,
};

const struct Tileset gTileset_CeruleanCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanCity,
    .palettes = gTilesetPalettes_CeruleanCity,
    .metatiles = gMetatiles_CeruleanCity,
    .metatileAttributes = gMetatileAttributes_CeruleanCity,
    .callback = NULL,
};

const struct Tileset gTileset_LavenderTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_LavenderTown,
    .palettes = gTilesetPalettes_LavenderTown,
    .metatiles = gMetatiles_LavenderTown,
    .metatileAttributes = gMetatileAttributes_LavenderTown,
    .callback = NULL,
};

const struct Tileset gTileset_Fuchsia =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Fuchsia,
    .palettes = gTilesetPalettes_Fuchsia,
    .metatiles = gMetatiles_Fuchsia,
    .metatileAttributes = gMetatileAttributes_Fuchsia,
    .callback = NULL,
};

const struct Tileset gTileset_CeladonCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeladonCity,
    .palettes = gTilesetPalettes_CeladonCity,
    .metatiles = gMetatiles_CeladonCity,
    .metatileAttributes = gMetatileAttributes_CeladonCity,
    .callback = InitTilesetAnim_CeladonCity,
};

const struct Tileset gTileset_ViridianCity_Gym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianCity_Gym,
    .palettes = gTilesetPalettes_ViridianCity_Gym,
    .metatiles = gMetatiles_ViridianCity_Gym,
    .metatileAttributes = gMetatileAttributes_ViridianCity_Gym,
    .callback = NULL,
};

const struct Tileset gTileset_Museum =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Museum,
    .palettes = gTilesetPalettes_Museum,
    .metatiles = gMetatiles_Museum,
    .metatileAttributes = gMetatileAttributes_Museum,
    .callback = NULL,
};

const struct Tileset gTileset_CeruleanCity_Gym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanCity_Gym,
    .palettes = gTilesetPalettes_CeruleanCity_Gym,
    .metatiles = gMetatiles_CeruleanCity_Gym,
    .metatileAttributes = gMetatileAttributes_CeruleanCity_Gym,
    .callback = NULL,
};

const struct Tileset gTileset_SaffronCity_Gym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SaffronCity_Gym,
    .palettes = gTilesetPalettes_SaffronCity_Gym,
    .metatiles = gMetatiles_SaffronCity_Gym,
    .metatileAttributes = gMetatileAttributes_SaffronCity_Gym,
    .callback = NULL,
};

const struct Tileset gTileset_SilphCo =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SilphCo,
    .palettes = gTilesetPalettes_SilphCo,
    .metatiles = gMetatiles_SilphCo,
    .metatileAttributes = gMetatileAttributes_SilphCo,
    .callback = InitTilesetAnim_SilphCo,
};

const struct Tileset gTileset_CeladonApartments =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeladonApartments,
    .palettes = gTilesetPalettes_CeladonApartments,
    .metatiles = gMetatiles_CeladonApartments,
    .metatileAttributes = gMetatileAttributes_CeladonApartments,
    .callback = NULL,
};

const struct Tileset gTileset_FuchsiaCity_Gym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_FuchsiaCity_Gym,
    .palettes = gTilesetPalettes_FuchsiaCity_Gym,
    .metatiles = gMetatiles_FuchsiaCity_Gym,
    .metatileAttributes = gMetatileAttributes_FuchsiaCity_Gym,
    .callback = NULL,
};

const struct Tileset gTileset_VermilionCity_Gym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_VermilionCity_Gym,
    .palettes = gTilesetPalettes_VermilionCity_Gym,
    .metatiles = gMetatiles_VermilionCity_Gym,
    .metatileAttributes = gMetatileAttributes_VermilionCity_Gym,
    .callback = NULL,
};

const struct Tileset gTileset_SoulHouse =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SoulHouse,
    .palettes = gTilesetPalettes_SoulHouse,
    .metatiles = gMetatiles_SoulHouse,
    .metatileAttributes = gMetatileAttributes_SoulHouse,
    .callback = NULL,
};

const struct Tileset gTileset_ssaqua =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ssaqua,
    .palettes = gTilesetPalettes_ssaqua,
    .metatiles = gMetatiles_ssaqua,
    .metatileAttributes = gMetatileAttributes_ssaqua,
    .callback = NULL,
};

const struct Tileset gTileset_Barn =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Barn,
    .palettes = gTilesetPalettes_Barn,
    .metatiles = gMetatiles_Barn,
    .metatileAttributes = gMetatileAttributes_Barn,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonLeague =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonLeague,
    .palettes = gTilesetPalettes_PokemonLeague,
    .metatiles = gMetatiles_PokemonLeague,
    .metatileAttributes = gMetatileAttributes_PokemonLeague,
    .callback = NULL,
};

const struct Tileset gTileset_SaffronCity_FightingDojoVIP =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SaffronCity_FightingDojoVIP,
    .palettes = gTilesetPalettes_SaffronCity_FightingDojoVIP,
    .metatiles = gMetatiles_SaffronCity_FightingDojoVIP,
    .metatileAttributes = gMetatileAttributes_SaffronCity_FightingDojoVIP,
    .callback = NULL,
};

const struct Tileset gTileset_Vermilion =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Vermilion,
    .palettes = gTilesetPalettes_Vermilion,
    .metatiles = gMetatiles_Vermilion,
    .metatileAttributes = gMetatileAttributes_Vermilion,
    .callback = NULL,
};

const struct Tileset gTileset_SafariZoneJohto =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SafariZoneJohto,
    .palettes = gTilesetPalettes_SafariZoneJohto,
    .metatiles = gMetatiles_SafariZoneJohto,
    .metatileAttributes = gMetatileAttributes_SafariZoneJohto,
    .callback = NULL,
};

const struct Tileset gTileset_Johto_South =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_South,
    .palettes = gTilesetPalettes_Johto_South,
    .metatiles = gMetatiles_Johto_South,
    .metatileAttributes = gMetatileAttributes_Johto_South,
    .callback = InitTilesetAnim_General,
};

const struct Tileset gTileset_VioletCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_VioletCity,
    .palettes = gTilesetPalettes_VioletCity,
    .metatiles = gMetatiles_VioletCity,
    .metatileAttributes = gMetatileAttributes_VioletCity,
    .callback = NULL,
};

const struct Tileset gTileset_AzaleaTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_AzaleaTown,
    .palettes = gTilesetPalettes_AzaleaTown,
    .metatiles = gMetatiles_AzaleaTown,
    .metatileAttributes = gMetatileAttributes_AzaleaTown,
    .callback = NULL,
};

const struct Tileset gTileset_IlexForest =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_IlexForest,
    .palettes = gTilesetPalettes_IlexForest,
    .metatiles = gMetatiles_IlexForest,
    .metatileAttributes = gMetatileAttributes_IlexForest,
    .callback = NULL,
};

const struct Tileset gTileset_Ecruteak_City =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Ecruteak_City,
    .palettes = gTilesetPalettes_Ecruteak_City,
    .metatiles = gMetatiles_Ecruteak_City,
    .metatileAttributes = gMetatileAttributes_Ecruteak_City,
    .callback = NULL,
};

const struct Tileset gTileset_Johto_NorthWest =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Johto_NorthWest,
    .palettes = gTilesetPalettes_Johto_NorthWest,
    .metatiles = gMetatiles_Johto_NorthWest,
    .metatileAttributes = gMetatileAttributes_Johto_NorthWest,
    .callback = InitTilesetAnim_General,
};

const struct Tileset gTileset_BellchimeTrail =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BellchimeTrail,
    .palettes = gTilesetPalettes_BellchimeTrail,
    .metatiles = gMetatiles_BellchimeTrail,
    .metatileAttributes = gMetatileAttributes_BellchimeTrail,
    .callback = NULL,
};

const struct Tileset gTileset_WhirlIslands =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_WhirlIslands,
    .palettes = gTilesetPalettes_WhirlIslands,
    .metatiles = gMetatiles_WhirlIslands,
    .metatileAttributes = gMetatileAttributes_WhirlIslands,
    .callback = NULL,
};

const struct Tileset gTileset_Cave_DragonsDen =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave_DragonsDen,
    .palettes = gTilesetPalettes_Cave_DragonsDen,
    .metatiles = gMetatiles_Cave_DragonsDen,
    .metatileAttributes = gMetatileAttributes_Cave_DragonsDen,
    .callback = NULL,
};

const struct Tileset gTileset_Route32 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Route32,
    .palettes = gTilesetPalettes_Route32,
    .metatiles = gMetatiles_Route32,
    .metatileAttributes = gMetatileAttributes_Route32,
    .callback = NULL,
};

const struct Tileset gTileset_Lighthouse =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Lighthouse,
    .palettes = gTilesetPalettes_Lighthouse,
    .metatiles = gMetatiles_Lighthouse,
    .metatileAttributes = gMetatileAttributes_Lighthouse,
    .callback = NULL,
};

const struct Tileset gTileset_BurnedTower =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BurnedTower,
    .palettes = gTilesetPalettes_BurnedTower,
    .metatiles = gMetatiles_BurnedTower,
    .metatileAttributes = gMetatileAttributes_BurnedTower,
    .callback = NULL,
};

const struct Tileset gTileset_HallOfFame =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_HallOfFame,
    .palettes = gTilesetPalettes_HallOfFame,
    .metatiles = gMetatiles_HallOfFame,
    .metatileAttributes = gMetatileAttributes_HallOfFame,
    .callback = NULL,
};

const struct Tileset gTileset_KurtsHouse =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_KurtsHouse,
    .palettes = gTilesetPalettes_KurtsHouse,
    .metatiles = gMetatiles_KurtsHouse,
    .metatileAttributes = gMetatileAttributes_KurtsHouse,
    .callback = NULL,
};

const struct Tileset gTileset_CianwoodCity_Gym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CianwoodCity_Gym,
    .palettes = gTilesetPalettes_CianwoodCity_Gym,
    .metatiles = gMetatiles_CianwoodCity_Gym,
    .metatileAttributes = gMetatileAttributes_CianwoodCity_Gym,
    .callback = NULL,
};

const struct Tileset gTileset_EcruteakCity_Gym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_EcruteakCity_Gym,
    .palettes = gTilesetPalettes_EcruteakCity_Gym,
    .metatiles = gMetatiles_EcruteakCity_Gym,
    .metatileAttributes = gMetatileAttributes_EcruteakCity_Gym,
    .callback = NULL,
};

const struct Tileset gTileset_MtSilverSnow =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MtSilverSnow,
    .palettes = gTilesetPalettes_MtSilverSnow,
    .metatiles = gMetatiles_MtSilverSnow,
    .metatileAttributes = gMetatileAttributes_MtSilverSnow,
    .callback = NULL,
};

const struct Tileset gTileset_ShopRooftop =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ShopRooftop,
    .palettes = gTilesetPalettes_ShopRooftop,
    .metatiles = gMetatiles_ShopRooftop,
    .metatileAttributes = gMetatileAttributes_ShopRooftop,
    .callback = NULL,
};

const struct Tileset gTileset_BattleTower_Outside =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattleTower_Outside,
    .palettes = gTilesetPalettes_BattleTower_Outside,
    .metatiles = gMetatiles_BattleTower_Outside,
    .metatileAttributes = gMetatileAttributes_BattleTower_Outside,
    .callback = NULL,
};

const struct Tileset gTileset_BattleTowerInner =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BattleTowerInner,
    .palettes = gTilesetPalettes_BattleTowerInner,
    .metatiles = gMetatiles_BattleTowerInner,
    .metatileAttributes = gMetatileAttributes_BattleTowerInner,
    .callback = NULL,
};

const struct Tileset gTileset_RuinsOfAlphWriting =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RuinsOfAlphWriting,
    .palettes = gTilesetPalettes_RuinsOfAlphWriting,
    .metatiles = gMetatiles_RuinsOfAlphWriting,
    .metatileAttributes = gMetatileAttributes_RuinsOfAlphWriting,
    .callback = NULL,
};

const struct Tileset gTileset_CyclingRoad =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CyclingRoad,
    .palettes = gTilesetPalettes_CyclingRoad,
    .metatiles = gMetatiles_CyclingRoad,
    .metatileAttributes = gMetatileAttributes_CyclingRoad,
    .callback = NULL,
};

const struct Tileset gTileset_SeaCottage =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeaCottage,
    .palettes = gTilesetPalettes_SeaCottage,
    .metatiles = gMetatiles_SeaCottage,
    .metatileAttributes = gMetatileAttributes_SeaCottage,
    .callback = NULL,
};
