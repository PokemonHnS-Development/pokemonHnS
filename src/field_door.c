#include "global.h"
#include "event_data.h"
#include "field_camera.h"
#include "fieldmap.h"
#include "metatile_behavior.h"
#include "task.h"
#include "constants/songs.h"
#include "constants/metatile_labels.h"


enum {
    DOOR_SOUND_NORMAL,
    DOOR_SOUND_SLIDING,
};

enum {
    DOOR_SIZE_1x1,
    DOOR_SIZE_1x2,
};

struct DoorAnimFrame
{
    u8 duration;
    u16 tileOffset;
};

struct DoorGraphics
{
    u16 metatileId;
    u8 sound;
    u8 size;
    const u8 *tiles;
    const u8 *paletteNums;
};

static void DrawClosedDoorTiles(const struct DoorGraphics *gfx, int x, int y);
static void CopyDoorTilesToVram(const u8 *tiles);
static void DrawCurrentDoorAnimFrame(const struct DoorGraphics *gfx, int x, int y, const u8 *paletteNums);
static void BuildDoorTiles(u16 *tiles, u16 tileNum, const u8 *paletteNums);
static bool32 AnimateDoorFrame(const struct DoorGraphics *gfx, const struct DoorAnimFrame *frames, s16 *data);
static const struct DoorAnimFrame *GetLastDoorAnimFrame(const struct DoorAnimFrame *frames);
static s8 GetDoorSoundType(const struct DoorGraphics *gfx, int x, int y);

static bool8 ShouldUseMultiCorridorDoor(void);

static const u8 sDoorAnimTiles_Littleroot[] = INCBIN_U8("graphics/door_anims/littleroot.4bpp");
static const u16 sDoorNullPalette1[16] = {};
static const u8 sDoorAnimTiles_BirchsLab[] = INCBIN_U8("graphics/door_anims/birchs_lab.4bpp");
static const u16 sDoorNullPalette2[16] = {};
static const u8 sDoorAnimTiles_FallarborLightRoof[] = INCBIN_U8("graphics/door_anims/fallarbor_light_roof.4bpp");
static const u16 sDoorNullPalette3[16] = {};
static const u8 sDoorAnimTiles_Lilycove[] = INCBIN_U8("graphics/door_anims/lilycove.4bpp");
static const u16 sDoorNullPalette4[16] = {};
static const u8 sDoorAnimTiles_LilycoveWooden[] = INCBIN_U8("graphics/door_anims/lilycove_wooden.4bpp");
static const u16 sDoorNullPalette5[16] = {};
static const u8 sDoorAnimTiles_General[] = INCBIN_U8("graphics/door_anims/general.4bpp");
static const u16 sDoorNullPalette6[16] = {};
static const u8 sDoorAnimTiles_PokeCenter[] = INCBIN_U8("graphics/door_anims/johtopokecenter.4bpp");
static const u8 sDoorAnimTiles_Gym[] = INCBIN_U8("graphics/door_anims/johtogym.4bpp");
static const u8 sDoorAnimTiles_PokeMart[] = INCBIN_U8("graphics/door_anims/poke_mart.4bpp");
static const u8 sDoorAnimTiles_RustboroTan[] = INCBIN_U8("graphics/door_anims/rustboro_tan.4bpp");
static const u16 sDoorNullPalette7[16] = {};
static const u8 sDoorAnimTiles_RustboroGray[] = INCBIN_U8("graphics/door_anims/rustboro_gray.4bpp");
static const u16 sDoorNullPalette8[16] = {};
static const u8 sDoorAnimTiles_Oldale[] = INCBIN_U8("graphics/door_anims/oldale.4bpp");
static const u8 sFiller1[0x5900] = {};
static const u8 sDoorAnimTiles_UnusedTops[] = INCBIN_U8("graphics/door_anims/unused_top.4bpp");
static const u8 sFiller2[0x140] = {};
static const u8 sDoorAnimTiles_UnusedBottoms[] = INCBIN_U8("graphics/door_anims/unused_bottom.4bpp");
static const u16 sDoorNullPalette11[16] = {};
static const u8 sDoorAnimTiles_Mauville[] = INCBIN_U8("graphics/door_anims/mauville.4bpp");
static const u16 sDoorNullPalette12[16] = {};
static const u8 sDoorAnimTiles_Verdanturf[] = INCBIN_U8("graphics/door_anims/verdanturf.4bpp");
static const u16 sDoorNullPalette13[16] = {};
static const u8 sDoorAnimTiles_Slateport[] = INCBIN_U8("graphics/door_anims/slateport.4bpp");
static const u16 sDoorNullPalette14[16] = {};
static const u8 sDoorAnimTiles_Dewford[] = INCBIN_U8("graphics/door_anims/dewford.4bpp");
static const u16 sDoorNullPalette15[16] = {};
static const u8 sDoorAnimTiles_Contest[] = INCBIN_U8("graphics/door_anims/contest.4bpp");
static const u16 sDoorNullPalette16[16] = {};
static const u8 sDoorAnimTiles_Mossdeep[] = INCBIN_U8("graphics/door_anims/mossdeep.4bpp");
static const u16 sDoorNullPalette17[16] = {};
static const u8 sDoorAnimTiles_SootopolisPeakedRoof[] = INCBIN_U8("graphics/door_anims/sootopolis_peaked_roof.4bpp");
static const u16 sDoorNullPalette18[16] = {};
static const u8 sDoorAnimTiles_Sootopolis[] = INCBIN_U8("graphics/door_anims/sootopolis.4bpp");
static const u16 sDoorNullPalette19[16] = {};
static const u8 sDoorAnimTiles_PokemonLeague[] = INCBIN_U8("graphics/door_anims/pokemon_league.4bpp");
static const u16 sDoorNullPalette20[16] = {};
static const u8 sDoorAnimTiles_Pacifidlog[] = INCBIN_U8("graphics/door_anims/pacifidlog.4bpp");
static const u16 sDoorNullPalette21[16] = {};
static const u8 sDoorAnimTiles_PetalburgGym[] = INCBIN_U8("graphics/door_anims/petalburg_gym.4bpp");
static const u16 sDoorNullPalette22[16] = {};
static const u8 sDoorAnimTiles_CyclingRoad[] = INCBIN_U8("graphics/door_anims/cycling_road.4bpp");
static const u16 sDoorNullPalette23[16] = {};
static const u8 sDoorAnimTiles_LilycoveDeptStore[] = INCBIN_U8("graphics/door_anims/lilycove_dept_store.4bpp");
static const u16 sDoorNullPalette24[16] = {};
static const u8 sDoorAnimTiles_SafariZone[] = INCBIN_U8("graphics/door_anims/safari_zone.4bpp");
static const u16 sDoorNullPalette25[16] = {};
static const u8 sDoorAnimTiles_MossdeepSpaceCenter[] = INCBIN_U8("graphics/door_anims/mossdeep_space_center.4bpp");
static const u16 sDoorNullPalette26[16] = {};
static const u8 sDoorAnimTiles_CableClub[] = INCBIN_U8("graphics/door_anims/cable_club.4bpp");
static const u16 sDoorNullPalette27[16] = {};
static const u8 sDoorAnimTiles_AbandonedShip[] = INCBIN_U8("graphics/door_anims/abandoned_ship.4bpp");
static const u16 sDoorNullPalette28[16] = {};
static const u8 sDoorAnimTiles_FallarborDarkRoof[] = INCBIN_U8("graphics/door_anims/fallarbor_dark_roof.4bpp");
static const u16 sDoorNullPalette29[16] = {};
static const u8 sDoorAnimTiles_AbandonedShipRoom[] = INCBIN_U8("graphics/door_anims/abandoned_ship_room.4bpp");
static const u16 sDoorNullPalette30[16] = {};
static const u8 sDoorAnimTiles_LilycoveDeptStoreElevator[] = INCBIN_U8("graphics/door_anims/lilycove_dept_store_elevator.4bpp");
static const u16 sDoorNullPalette31[16] = {};
static const u8 sDoorAnimTiles_BattleTowerOld[] = INCBIN_U8("graphics/door_anims/battle_tower_old.4bpp");
static const u16 sDoorNullPalette32[16] = {};
static const u8 sDoorAnimTiles_BattleTowerElevator[] = INCBIN_U8("graphics/door_anims/battle_tower_elevator.4bpp");
static const u16 sDoorNullPalette33[16] = {};
static const u8 sDoorAnimTiles_UnusedBattleFrontier[] = INCBIN_U8("graphics/door_anims/unused_battle_frontier.4bpp");
static const u16 sDoorNullPalette34[16] = {};
static const u8 sDoorAnimTiles_BattleDome[] = INCBIN_U8("graphics/door_anims/battle_dome.4bpp");
static const u16 sDoorNullPalette35[16] = {};
static const u8 sDoorAnimTiles_BattleFactory[] = INCBIN_U8("graphics/door_anims/battle_factory.4bpp");
static const u16 sDoorNullPalette36[16] = {};
static const u8 sDoorAnimTiles_BattleTower[] = INCBIN_U8("graphics/door_anims/battle_tower.4bpp");
static const u16 sDoorNullPalette37[16] = {};
static const u8 sDoorAnimTiles_BattleArena[] = INCBIN_U8("graphics/door_anims/battle_arena.4bpp");
static const u16 sDoorNullPalette38[16] = {};
static const u8 sDoorAnimTiles_BattleArenaLobby[] = INCBIN_U8("graphics/door_anims/battle_arena_lobby.4bpp");
static const u16 sDoorNullPalette39[16] = {};
static const u8 sDoorAnimTiles_BattleDomeLobby[] = INCBIN_U8("graphics/door_anims/battle_dome_lobby.4bpp");
static const u16 sDoorNullPalette40[16] = {};
static const u8 sDoorAnimTiles_BattlePalaceLobby[] = INCBIN_U8("graphics/door_anims/battle_palace_lobby.4bpp");
static const u8 sDoorAnimTiles_BattleTent[] = INCBIN_U8("graphics/door_anims/battle_tent.4bpp");
static const u16 sDoorNullPalette41[16] = {};
static const u8 sDoorAnimTiles_BattleDomeCorridor[] = INCBIN_U8("graphics/door_anims/battle_dome_corridor.4bpp");
static const u16 sDoorNullPalette42[16] = {};
static const u8 sDoorAnimTiles_BattleTowerMultiCorridor[] = INCBIN_U8("graphics/door_anims/battle_tower_multi_corridor.4bpp");
static const u16 sDoorNullPalette43[16] = {};
static const u8 sDoorAnimTiles_BattleFrontier[] = INCBIN_U8("graphics/door_anims/battle_frontier.4bpp");
static const u16 sDoorNullPalette44[16] = {};
static const u8 sDoorAnimTiles_BattleFrontierSliding[] = INCBIN_U8("graphics/door_anims/battle_frontier_sliding.4bpp");
static const u16 sDoorNullPalette45[16] = {};
static const u8 sDoorAnimTiles_BattleDomePreBattleRoom[] = INCBIN_U8("graphics/door_anims/battle_dome_pre_battle_room.4bpp");
static const u16 sDoorNullPalette46[16] = {};
static const u8 sDoorAnimTiles_BattleTentInterior[] = INCBIN_U8("graphics/door_anims/battle_tent_interior.4bpp");
static const u16 sDoorNullPalette47[16] = {};
static const u8 sDoorAnimTiles_TrainerHillLobbyElevator[] = INCBIN_U8("graphics/door_anims/trainer_hill_lobby_elevator.4bpp");
static const u16 sDoorNullPalette48[16] = {};
static const u8 sDoorAnimTiles_TrainerHillRoofElevator[] = INCBIN_U8("graphics/door_anims/trainer_hill_roof_elevator.4bpp");
static const u16 sDoorNullPalette49[16] = {};
static const u8 sDoorAnimTiles_Goldenrod[] = INCBIN_U8("graphics/door_anims/goldenrod.4bpp");
static const u16 sDoorNullPalette50[16] = {};
static const u8 sDoorAnimTiles_NewBarkTown_Door_Yellow[] = INCBIN_U8("graphics/door_anims/NewBarkTown_Door_Yellow.4bpp");
static const u16 sDoorNullPalette51[16] = {};
static const u8 sDoorAnimTiles_NewBarkTown_Door_Blue[] = INCBIN_U8("graphics/door_anims/cerulean.4bpp");
static const u16 sDoorNullPalette52[16] = {};
static const u8 sDoorAnimTiles_NewBarkTown_Door_Red[] = INCBIN_U8("graphics/door_anims/NewBarkTown_Door_Red.4bpp");
static const u16 sDoorNullPalette53[16] = {};
static const u8 sDoorAnimTiles_Azalea[] = INCBIN_U8("graphics/door_anims/NewBarkTown_Door_Yellow.4bpp");
static const u16 sDoorNullPalette54[16] = {};
static const u8 sDoorAnimTiles_Cianwood[] = INCBIN_U8("graphics/door_anims/cianwood.4bpp");
static const u16 sDoorNullPalette55[16] = {};
static const u8 sDoorAnimTiles_Viridian[] = INCBIN_U8("graphics/door_anims/viridian.4bpp");
static const u16 sDoorNullPalette56[16] = {};
static const u8 sDoorAnimTiles_Pewter[] = INCBIN_U8("graphics/door_anims/pewter.4bpp");
static const u16 sDoorNullPalette57[16] = {};
static const u8 sDoorAnimTiles_Cerulean[] = INCBIN_U8("graphics/door_anims/cerulean.4bpp");
static const u16 sDoorNullPalette58[16] = {};
static const u8 sDoorAnimTiles_Vermilion[] = INCBIN_U8("graphics/door_anims/vermilion.4bpp");
static const u16 sDoorNullPalette59[16] = {};
static const u8 sDoorAnimTiles_Lavender[] = INCBIN_U8("graphics/door_anims/lavender.4bpp");
static const u16 sDoorNullPalette60[16] = {};
static const u8 sDoorAnimTiles_Saffron[] = INCBIN_U8("graphics/door_anims/saffron.4bpp");
static const u16 sDoorNullPalette61[16] = {};
static const u8 sDoorAnimTiles_Fuchsia[] = INCBIN_U8("graphics/door_anims/fuchsia.4bpp");
static const u16 sDoorNullPalette62[16] = {};
static const u8 sDoorAnimTiles_NewBarkTown_Door_Grey[] = INCBIN_U8("graphics/door_anims/NewBarkTown_Door_Grey.4bpp");
static const u16 sDoorNullPalette63[16] = {};
static const u8 sDoorAnimTiles_JohtoSafariZone_Door[] = INCBIN_U8("graphics/door_anims/safari_zone.4bpp");
static const u16 sDoorNullPalette64[16] = {};
static const u8 sDoorAnimTiles_CherryGrove_Door[] = INCBIN_U8("graphics/door_anims/NewBarkTown_Door_Red.4bpp");
static const u16 sDoorNullPalette65[16] = {};
static const u8 sDoorAnimTiles_VioletCity_Dojo_Door[] = INCBIN_U8("graphics/door_anims/dojo_door.4bpp");
static const u16 sDoorNullPalette66[16] = {};
static const u8 sDoorAnimTiles_EcruteakCity_Dojo_Door[] = INCBIN_U8("graphics/door_anims/dojo_door_ecruteak.4bpp");
static const u16 sDoorNullPalette67[16] = {};
static const u8 sDoorAnimTiles_OlivineCity_Door[] = INCBIN_U8("graphics/door_anims/olivine.4bpp");
static const u16 sDoorNullPalette68[16] = {};
static const u8 sDoorAnimTiles_Fuchsia_Red_Door[] = INCBIN_U8("graphics/door_anims/johtosafari_zone.4bpp");
static const u16 sDoorNullPalette69[16] = {};
static const u8 sDoorAnimTiles_BlackthornCity_Door[] = INCBIN_U8("graphics/door_anims/blackthorn_city.4bpp");
static const u16 sDoorNullPalette70[16] = {};
static const u8 sDoorAnimTiles_DeptStoreElevator[] = INCBIN_U8("graphics/door_anims/dept_store_elevator.4bpp");
static const u16 sDoorNullPalette71[16] = {};
static const u8 sDoorAnimTiles_RocketElevator[] = INCBIN_U8("graphics/door_anims/rocket_elevator.4bpp");
static const u16 sDoorNullPalette72[16] = {};
static const u8 sDoorAnimTiles_SSAqua[] = INCBIN_U8("graphics/door_anims/ssaqua.4bpp");
static const u16 sDoorNullPalette73[16] = {};



#define CLOSED_DOOR_TILES_OFFSET 0xFFFF

static const struct DoorAnimFrame sDoorAnimFrames_OpenSmall[] = {
    {4, CLOSED_DOOR_TILES_OFFSET},
    {4, 0 * TILE_SIZE_4BPP},
    {4, 4 * TILE_SIZE_4BPP},
    {4, 8 * TILE_SIZE_4BPP},
    {}
};

static const struct DoorAnimFrame sDoorAnimFrames_OpenLarge[] = {
    {4, CLOSED_DOOR_TILES_OFFSET},
    {4, 0 * TILE_SIZE_4BPP},
    {4, 8 * TILE_SIZE_4BPP},
    {4, 16 * TILE_SIZE_4BPP},
    {}
};

static const struct DoorAnimFrame sDoorAnimFrames_CloseSmall[] = {
    {4, 8 * TILE_SIZE_4BPP},
    {4, 4 * TILE_SIZE_4BPP},
    {4, 0 * TILE_SIZE_4BPP},
    {4, CLOSED_DOOR_TILES_OFFSET},
    {}
};

static const struct DoorAnimFrame sDoorAnimFrames_CloseLarge[] = {
    {4, 16 * TILE_SIZE_4BPP},
    {4, 8 * TILE_SIZE_4BPP},
    {4, 0 * TILE_SIZE_4BPP},
    {4, CLOSED_DOOR_TILES_OFFSET},
    {}
};

static const u8 sDoorAnimPalettes_General[] = {2, 2, 2, 2, 2, 2, 2, 2};
static const u8 sDoorAnimPalettes_PokeCenter[] = {3, 3, 3, 3, 3, 3, 3, 3};
static const u8 sDoorAnimPalettes_Goldenrod[] = {10, 10, 10, 10, 10, 10, 10, 10};
static const u8 sDoorAnimPalettes_Gym[] = {3, 3, 3, 3, 3, 3, 3, 3};
static const u8 sDoorAnimPalettes_NewBarkTown_Door_Blue[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_NewBarkTown_Door_Yellow[] = {5, 5, 5, 5, 5, 5, 5, 5};
static const u8 sDoorAnimPalettes_SafariZoneJohto_Door[] = {9, 9, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_NewBarkTown_Door_Red[] = {8, 8, 8, 8, 8, 8, 8, 8};
static const u8 sDoorAnimPalettes_Azalea[] = {5, 5, 5, 5, 5, 5, 5, 5};
static const u8 sDoorAnimPalettes_Cianwood[] = {11, 11, 11, 11, 11, 11, 11, 11};
static const u8 sDoorAnimPalettes_Viridian[] = {8, 8, 8, 8, 8, 8, 8, 8};
static const u8 sDoorAnimPalettes_Pewter[] = {8, 8, 8, 8, 8, 8, 8, 8};
static const u8 sDoorAnimPalettes_Cerulean[] = {12, 12, 12, 12, 12, 12, 12, 12};
static const u8 sDoorAnimPalettes_Vermilion[] = {9, 9, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_Lavender[] = {9, 9, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_Saffron[] = {8, 8, 8, 8, 8, 8, 8, 8};
static const u8 sDoorAnimPalettes_Fuchsia[] = {8, 8, 8, 8, 8, 8, 8, 8};
static const u8 sDoorAnimPalettes_CherryGrove_Door_Red[] = {8, 8, 8, 8, 8, 8, 8, 8};
static const u8 sDoorAnimPalettes_VioletCity_Dojo_Door[] = {12, 12, 12, 12, 12, 12, 12, 12};
static const u8 sDoorAnimPalettes_EcruteakCity_Dojo_Door[] = {10, 10, 10, 10, 10, 10, 10, 10};
static const u8 sDoorAnimPalettes_OlivineCity_Door[] = {11, 11, 11, 11, 11, 11, 11, 11};
static const u8 sDoorAnimPalettes_Fuchsia_Red_Door[] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_BlackthornCity_Door[] = {7, 7, 7, 7, 7, 7, 7, 7,};
static const u8 sDoorAnimPalettes_DeptStore_Door[] = {8, 8, 8, 8, 8, 8, 8, 8,};
static const u8 sDoorAnimPalettes_Rocket_Door[] = {2, 2, 2, 2, 2, 2, 2, 2,};
static const u8 sDoorAnimPalettes_SSAqua[] = {7, 7, 7, 7, 7, 7, 7, 7,};


static const u8 sDoorAnimPalettes_PokeMart[] = {0, 0, 5, 5, 5, 5, 5, 5};
static const u8 sDoorAnimPalettes_Littleroot[] = {10, 10, 6, 6, 6, 6, 6, 6};
static const u8 sDoorAnimPalettes_BirchsLab[] = {8, 8, 8, 8, 8, 8, 8, 8};
static const u8 sDoorAnimPalettes_RustboroTan[] = {11, 11, 11, 11, 11, 11, 11, 11};
static const u8 sDoorAnimPalettes_RustboroGray[] = {10, 10, 10, 10, 10, 10, 10, 10};
static const u8 sDoorAnimPalettes_FallarborLightRoof[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_Lilycove[] = {8, 8, 8, 8, 8, 8, 8, 8};
static const u8 sDoorAnimPalettes_Oldale[] = {10, 10, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_Mossdeep[] = {9, 9, 12, 12, 12, 12, 12, 12};
static const u8 sDoorAnimPalettes_PokemonLeague[] = {8, 8, 8, 8, 8, 8, 8, 8};
static const u8 sDoorAnimPalettes_Pacifidlog[] = {9, 9, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_SootopolisPeakedRoof[] = {6, 6, 6, 6, 6, 6, 6, 6};
static const u8 sDoorAnimPalettes_Sootopolis[] = {6, 6, 6, 6, 6, 6, 6, 6};
static const u8 sDoorAnimPalettes_Dewford[] = {0, 0, 5, 5, 5, 5, 5, 5};
static const u8 sDoorAnimPalettes_Slateport[] = {6, 6, 1, 1, 1, 1, 1, 1};
static const u8 sDoorAnimPalettes_Mauville[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_Verdanturf[] = {6, 6, 5, 5, 5, 5, 5, 5};
static const u8 sDoorAnimPalettes_LilycoveWooden[] = {5, 5, 5, 5, 5, 5, 5, 5};
static const u8 sDoorAnimPalettes_Contest[] = {1, 1, 12, 12, 12, 12, 12, 12};
static const u8 sDoorAnimPalettes_PetalburgGym[] = {6, 6, 6, 6, 6, 6, 6, 6};
static const u8 sDoorAnimPalettes_CyclingRoad[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_LilycoveDeptStore[] = {5, 5, 5, 5, 12, 12, 12, 12};
static const u8 sDoorAnimPalettes_SafariZone[] = {9, 9, 9, 9, 11, 11, 11, 11};
static const u8 sDoorAnimPalettes_MossdeepSpaceCenter[] = {8, 8, 8, 8, 8, 8, 8, 8};
static const u8 sDoorAnimPalettes_CableClub[] = {6, 6, 6, 6, 6, 6, 6, 6};
static const u8 sDoorAnimPalettes_AbandonedShip[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_FallarborDarkRoof[] = {11, 11, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_AbandonedShipRoom[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_LilycoveDeptStoreElevator[] = {6, 6, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_BattleTowerOld[] = {9, 9, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_BattleTowerElevator[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_UnusedBattleFrontier[] = {9, 9, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_BattleDome[] = {9, 9, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_BattleFactory[] = {9, 9, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_BattleTower[] = {0, 0, 5, 5, 5, 5, 5, 5};
static const u8 sDoorAnimPalettes_BattleArena[] = {5, 5, 5, 5, 5, 5, 5, 5};
static const u8 sDoorAnimPalettes_BattleArenaLobby[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_BattleDomeLobby[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_BattlePalaceLobby[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_BattleTent[] = {1, 1, 5, 5, 5, 5, 5, 5};
static const u8 sDoorAnimPalettes_BattleDomeCorridor[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_BattleTowerMultiCorridor[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_Unused[] = {1, 1, 1, 1, 1, 1, 1, 1};
static const u8 sDoorAnimPalettes_BattleFrontier[] = {1, 1, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_BattleFrontier_Sliding[] = {1, 1, 1, 1, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_BattleDomePreBattleRoom[] = {9, 9, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_BattleTentInterior[] = {9, 9, 9, 9, 9, 9, 9, 9};
static const u8 sDoorAnimPalettes_TrainerHillLobbyElevator[] = {7, 7, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_TrainerHillRoofElevator[] = {9, 9, 7, 7, 7, 7, 7, 7};
static const u8 sDoorAnimPalettes_OaksLabDoor[] = {10, 10, 10, 10, 10, 10, 10, 10};


static const struct DoorGraphics sDoorGraphics[] =
{
    {METATILE_General_Door,                                 DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_General, sDoorAnimPalettes_General},
    {METATILE_General_Door_PokeCenter,                      DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_PokeCenter, sDoorAnimPalettes_PokeCenter},
    {METATILE_General_Door_Gym,                             DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_Gym, sDoorAnimPalettes_Gym},
    {METATILE_General_Door_PokeMart,                        DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_PokeMart, sDoorAnimPalettes_PokeMart},
    {METATILE_Petalburg_Door_Littleroot,                    DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_Littleroot, sDoorAnimPalettes_Littleroot},
    {METATILE_Petalburg_Door_BirchsLab,                     DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_BirchsLab, sDoorAnimPalettes_BirchsLab},
    {METATILE_Rustboro_Door_Tan,                            DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_RustboroTan, sDoorAnimPalettes_RustboroTan},
    {METATILE_Rustboro_Door_Gray,                           DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_RustboroGray, sDoorAnimPalettes_RustboroGray},
    {METATILE_Fallarbor_Door_LightRoof,                     DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_FallarborLightRoof, sDoorAnimPalettes_FallarborLightRoof},
    {METATILE_Petalburg_Door_Oldale,                        DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_Oldale, sDoorAnimPalettes_Oldale},
    {METATILE_Mauville_Door,                                DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_Mauville, sDoorAnimPalettes_Mauville},
    {METATILE_Mauville_Door_Verdanturf,                     DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_Verdanturf, sDoorAnimPalettes_Verdanturf},
    {METATILE_Slateport_Door,                               DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_Slateport, sDoorAnimPalettes_Slateport},
    {METATILE_Dewford_Door,                                 DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_Dewford, sDoorAnimPalettes_Dewford},
    {METATILE_General_Door_Contest,                         DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_Contest, sDoorAnimPalettes_Contest},
    {METATILE_Lilycove_Door,                                DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_Lilycove, sDoorAnimPalettes_Lilycove},
    {METATILE_Lilycove_Door_Wooden,                         DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_LilycoveWooden, sDoorAnimPalettes_LilycoveWooden},
    {METATILE_Mossdeep_Door,                                DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_Mossdeep, sDoorAnimPalettes_Mossdeep},
    {METATILE_Sootopolis_Door_PeakedRoof,                   DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_SootopolisPeakedRoof, sDoorAnimPalettes_SootopolisPeakedRoof},
    {METATILE_Sootopolis_Door,                              DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_Sootopolis, sDoorAnimPalettes_Sootopolis},
    {METATILE_EverGrande_Door_PokemonLeague,                DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_PokemonLeague, sDoorAnimPalettes_PokemonLeague},
    {METATILE_Pacifidlog_Door,                              DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_Pacifidlog, sDoorAnimPalettes_Pacifidlog},
    {METATILE_PetalburgGym_Door,                            DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_PetalburgGym, sDoorAnimPalettes_PetalburgGym},
    {METATILE_Mauville_Door_CyclingRoad,                    DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_CyclingRoad, sDoorAnimPalettes_CyclingRoad},
    {METATILE_Lilycove_Door_DeptStore,                      DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_LilycoveDeptStore, sDoorAnimPalettes_LilycoveDeptStore},
    {METATILE_Lilycove_Door_SafariZone,                     DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_SafariZone, sDoorAnimPalettes_SafariZone},
    {METATILE_Mossdeep_Door_SpaceCenter,                    DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_MossdeepSpaceCenter, sDoorAnimPalettes_MossdeepSpaceCenter},
    {METATILE_PokemonCenter_Door_CableClub,                 DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_CableClub, sDoorAnimPalettes_CableClub},
    {METATILE_InsideShip_IntactDoor_Bottom_Unlocked,        DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_AbandonedShip, sDoorAnimPalettes_AbandonedShip},
    {METATILE_Fallarbor_Door_DarkRoof,                      DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_FallarborDarkRoof, sDoorAnimPalettes_FallarborDarkRoof},
    {METATILE_InsideShip_IntactDoor_Bottom_Interior,        DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_AbandonedShipRoom, sDoorAnimPalettes_AbandonedShipRoom},
    {METATILE_Shop_Door_Elevator,                           DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_LilycoveDeptStoreElevator, sDoorAnimPalettes_LilycoveDeptStoreElevator},
    {METATILE_Dewford_Door_BattleTower,                     DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleTowerOld, sDoorAnimPalettes_BattleTowerOld},
    {METATILE_BattleFrontier_Door_Elevator,                 DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleTowerElevator, sDoorAnimPalettes_BattleTowerElevator},
    // The metatile for this door doesn't seem to correspond to a door in any Emerald tileset. Given the surrounding door animations, it was likely cut from the Battle Frontier.
    // From the palettes array we know it uses palette 9, and the door's shadow looks correct using either the Battle Tent or Battle Frontier Outside's 9th palette.
    {0x3B0,                                                 DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_UnusedBattleFrontier, sDoorAnimPalettes_UnusedBattleFrontier},
    {METATILE_BattleFrontierOutsideWest_Door_BattleDome,    DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleDome, sDoorAnimPalettes_BattleDome},
    {METATILE_BattleFrontierOutsideWest_Door_BattleFactory, DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleFactory, sDoorAnimPalettes_BattleFactory},
    {METATILE_BattleFrontierOutsideEast_Door_BattleTower,   DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleTower, sDoorAnimPalettes_BattleTower},
    {METATILE_BattleFrontierOutsideEast_Door_BattleArena,   DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_BattleArena, sDoorAnimPalettes_BattleArena},
    {METATILE_BattleArena_Door,                             DOOR_SOUND_NORMAL,   DOOR_SIZE_1x1, sDoorAnimTiles_BattleArenaLobby, sDoorAnimPalettes_BattleArenaLobby},
    {METATILE_BattleDome_Door_Lobby,                        DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleDomeLobby, sDoorAnimPalettes_BattleDomeLobby},
    {METATILE_BattlePalace_Door,                            DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_BattlePalaceLobby, sDoorAnimPalettes_BattlePalaceLobby},
    {METATILE_Slateport_Door_BattleTent,                    DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleTent, sDoorAnimPalettes_BattleTent},
    {METATILE_Mauville_Door_BattleTent,                     DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleTent, sDoorAnimPalettes_BattleTent},
    {METATILE_Fallarbor_Door_BattleTent,                    DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleTent, sDoorAnimPalettes_BattleTent},
    {METATILE_BattleDome_Door_Corridor,                     DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleDomeCorridor, sDoorAnimPalettes_BattleDomeCorridor},
    {METATILE_BattleFrontier_Door_MultiCorridor,            DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleTowerMultiCorridor, sDoorAnimPalettes_BattleTowerMultiCorridor},
    {METATILE_BattleFrontierOutsideWest_Door,               DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_BattleFrontier, sDoorAnimPalettes_BattleFrontier},
    {METATILE_BattleFrontierOutsideWest_Door_Sliding,       DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleFrontierSliding, sDoorAnimPalettes_BattleFrontier_Sliding},
    {METATILE_BattleDome_Door_PreBattleRoom,                DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleDomePreBattleRoom, sDoorAnimPalettes_BattleDomePreBattleRoom},
    {METATILE_BattleTent_Door,                              DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_BattleTentInterior, sDoorAnimPalettes_BattleTentInterior},
    {METATILE_TrainerHill_Door_Elevator_Lobby,              DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_TrainerHillLobbyElevator, sDoorAnimPalettes_TrainerHillLobbyElevator},
    {METATILE_Johto_General_Door,                           DOOR_SOUND_NORMAL,  DOOR_SIZE_1x1, sDoorAnimTiles_General, sDoorAnimPalettes_General},
    {METATILE_Johto_General_Door_Sliding,                   DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_PokeCenter, sDoorAnimPalettes_PokeCenter},
    {METATILE_Johto_General_Door_Gym,                       DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_Gym, sDoorAnimPalettes_Gym},
    {METATILE_Goldenrod_Goldenrod,                          DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_Goldenrod, sDoorAnimPalettes_Goldenrod},
    {METATILE_NewBarkTown_Door_Yellow,                       DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_NewBarkTown_Door_Yellow, sDoorAnimPalettes_NewBarkTown_Door_Yellow},
    {METATILE_NewBarkTown_Door_Red,                         DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_NewBarkTown_Door_Red, sDoorAnimPalettes_NewBarkTown_Door_Red},
    {METATILE_61_azalea_Azalea,                             DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_Azalea, sDoorAnimPalettes_Azalea},
    {METATILE_CianwoodSafariGate_Cianwood,                  DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_Cianwood, sDoorAnimPalettes_Cianwood},
    {METATILE_Viridian_2_Viridian,                          DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_Viridian, sDoorAnimPalettes_Viridian},
    {METATILE_Pewter_Pewter,                                DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_Pewter, sDoorAnimPalettes_Pewter},
    {METATILE_CeruleanCity_Cerulean,                        DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_Cerulean, sDoorAnimPalettes_Cerulean},
    {METATILE_Olivine_6_Vermilion,                         DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_Vermilion, sDoorAnimPalettes_Vermilion},
    {METATILE_LavenderTown_Lavender,                        DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_Lavender, sDoorAnimPalettes_Lavender},
    {METATILE_route34_11_Saffron,                           DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_Saffron, sDoorAnimPalettes_Saffron},
    {METATILE_Fuchsia_Fuchsia,                              DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_Fuchsia, sDoorAnimPalettes_Fuchsia},
    {METATILE_NewBarkTown_Door_Blue,                        DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_NewBarkTown_Door_Blue, sDoorAnimPalettes_NewBarkTown_Door_Blue},
    {METATILE_SafariZoneJohto_Safari,                        DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_JohtoSafariZone_Door, sDoorAnimPalettes_SafariZoneJohto_Door},
    {METATILE_Cherrygrove_Door_Red,                         DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_NewBarkTown_Door_Red, sDoorAnimPalettes_CherryGrove_Door_Red},
    {METATILE_VioletCity_Dojo_Door,                         DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_VioletCity_Dojo_Door, sDoorAnimPalettes_VioletCity_Dojo_Door},
    {METATILE_Ecruteak_City_Door,                         DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_EcruteakCity_Dojo_Door, sDoorAnimPalettes_EcruteakCity_Dojo_Door},    
    {METATILE_Olivine_6_Door,                             DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_OlivineCity_Door, sDoorAnimPalettes_OlivineCity_Door},
    {METATILE_Fuchsia_Red_Door,                           DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_Fuchsia_Red_Door, sDoorAnimPalettes_Fuchsia_Red_Door},
    {METATILE_Cave5_Door,                                 DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_VioletCity_Dojo_Door, sDoorAnimPalettes_VioletCity_Dojo_Door},
    {METATILE_Blackthorn_Door,                              DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_BlackthornCity_Door, sDoorAnimPalettes_BlackthornCity_Door},
    {METATILE_JohtoShop_Door,                              DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_DeptStoreElevator, sDoorAnimPalettes_DeptStore_Door},
    {METATILE_GreenHouses_Elevator,                              DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_RocketElevator, sDoorAnimPalettes_Rocket_Door},
    {METATILE_BattleTowerInner_Door,                              DOOR_SOUND_SLIDING, DOOR_SIZE_1x1, sDoorAnimTiles_RocketElevator, sDoorAnimPalettes_Rocket_Door},
    {METATILE_ssaqua_Door,                              DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_SSAqua, sDoorAnimPalettes_SSAqua},
    {METATILE_PalletTown_Door_Green,                    DOOR_SOUND_NORMAL, DOOR_SIZE_1x1, sDoorAnimTiles_BirchsLab, sDoorAnimPalettes_OaksLabDoor},
    {},
};

static void DrawDoor(const struct DoorGraphics *gfx, const struct DoorAnimFrame *frames, int x, int y)
{
    if (frames->tileOffset == CLOSED_DOOR_TILES_OFFSET)
        DrawClosedDoorTiles(gfx, x, y);
    else
    {
        CopyDoorTilesToVram(&gfx->tiles[frames->tileOffset]);
        DrawCurrentDoorAnimFrame(gfx, x, y, gfx->paletteNums);
    }
}

static void DrawClosedDoorTiles(const struct DoorGraphics *gfx, int x, int y)
{
    if (gfx->size == DOOR_SIZE_1x1)
        CurrentMapDrawMetatileAt(x, y);
    else
    {
        CurrentMapDrawMetatileAt(x, y);
        CurrentMapDrawMetatileAt(x, y - 1);
    }
}

// NOTE: The tiles of a door's animation must be copied to VRAM because they are
//       not already part of any given tileset. This means that if there are any
//       pre-existing tiles in this copied region that are visible when the door
//       animation is played, they will be overwritten.
#define DOOR_TILE_START (434)//(NUM_TILES_TOTAL - 8)

static void CopyDoorTilesToVram(const u8 *tiles)
{
    CpuFastCopy(tiles, (void *)(VRAM + TILE_OFFSET_4BPP(DOOR_TILE_START)), 8 * TILE_SIZE_4BPP);
}

static void DrawCurrentDoorAnimFrame(const struct DoorGraphics *gfx, int x, int y, const u8 *paletteNums)
{
    u16 tiles[8];
    if (gfx->size == DOOR_SIZE_1x1)
        BuildDoorTiles(tiles, DOOR_TILE_START, paletteNums);

    else
    {
        BuildDoorTiles(tiles, DOOR_TILE_START, paletteNums);
        DrawDoorMetatileAt(x, y - 1, tiles);
        BuildDoorTiles(tiles, DOOR_TILE_START + 4, &paletteNums[4]);
    }

    DrawDoorMetatileAt(x, y, tiles);
}

static void BuildDoorTiles(u16 *tiles, u16 tileNum, const u8 *paletteNums)
{
    int i;
    u16 tile;

    // Only the first 4 tiles of each metatile (bottom layer) actually use the door tiles
    for (i = 0; i < 4; i++)
    {
        tile = *(paletteNums++) << 12;
        tiles[i] = tile | (tileNum + i);
    }

    // The remaining tiles (top layer) always use tile 0 (with the same palette)
    for (; i < 8; i++)
    {
        tile = *(paletteNums++) << 12;
        tiles[i] = tile;
    }
}

#define tFramesHi data[0]
#define tFramesLo data[1]
#define tGfxHi    data[2]
#define tGfxLo    data[3]
#define tFrameId  data[4]
#define tCounter  data[5]
#define tX        data[6]
#define tY        data[7]

static void Task_AnimateDoor(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    const struct DoorAnimFrame *frames = (struct DoorAnimFrame *)((u16)tFramesHi << 16 | (u16)tFramesLo);
    const struct DoorGraphics *gfx = (struct DoorGraphics *)((u16)tGfxHi << 16 | (u16)tGfxLo);
    if (!AnimateDoorFrame(gfx, frames, data))
        DestroyTask(taskId);
}

static bool32 AnimateDoorFrame(const struct DoorGraphics *gfx, const struct DoorAnimFrame *frames, s16 *data)
{
    if (tCounter == 0)
        DrawDoor(gfx, &frames[tFrameId], tX, tY);

    if (tCounter == frames[tFrameId].duration)
    {
        tCounter = 0;
        tFrameId++;
        if (frames[tFrameId].duration == 0) // final frame has been reached
            return FALSE;
        else
            return TRUE;
    }

    tCounter++;
    return TRUE;
}

static const struct DoorGraphics *GetDoorGraphics(const struct DoorGraphics *gfx, u16 id)
{
    while (gfx->tiles != NULL)
    {
        if (gfx->metatileId == id)
            return gfx;
        gfx++;
    }
    return NULL;
}

static s8 StartDoorAnimationTask(const struct DoorGraphics *gfx, const struct DoorAnimFrame *frames, int x, int y)
{
    u8 taskId;
    s16 *data;
    if (FuncIsActiveTask(Task_AnimateDoor) == TRUE)
        return -1;

    taskId = CreateTask(Task_AnimateDoor, 80);
    data = gTasks[taskId].data;

    tX = x;
    tY = y;
    tFramesLo = (uintptr_t)frames;
    tFramesHi = (uintptr_t)frames >> 16;
    tGfxLo = (uintptr_t)gfx;
    tGfxHi = (uintptr_t)gfx >> 16;
    return taskId;
}

#undef tFramesHi
#undef tFramesLo
#undef tGfxHi
#undef tGfxLo
#undef tFrameId
#undef tCounter
#undef tX
#undef tY

static void DrawClosedDoor(const struct DoorGraphics *gfx, int x, int y)
{
    DrawClosedDoorTiles(gfx, x, y);
}

static void DrawOpenedDoor(const struct DoorGraphics *gfx, int x, int y)
{
    gfx = GetDoorGraphics(gfx, MapGridGetMetatileIdAt(x, y));
    if (gfx != NULL)
    {
        const struct DoorAnimFrame *frames = gfx->size == DOOR_SIZE_1x1 ? sDoorAnimFrames_OpenSmall : sDoorAnimFrames_OpenLarge;
        DrawDoor(gfx, GetLastDoorAnimFrame(frames), x, y);
    }
}

static const struct DoorAnimFrame *GetLastDoorAnimFrame(const struct DoorAnimFrame *frames)
{
    while (frames->duration != 0)
        frames++;
    return frames - 1;
}

static s8 AnimateDoorOpenInternal(const struct DoorGraphics *gfx, int x, int y)
{
    gfx = GetDoorGraphics(gfx, MapGridGetMetatileIdAt(x, y));
    if (gfx == NULL)
        return -1;
    else if (gfx->size == DOOR_SIZE_1x1)
        return StartDoorAnimationTask(gfx, sDoorAnimFrames_OpenSmall, x, y);
    else
        return StartDoorAnimationTask(gfx, sDoorAnimFrames_OpenLarge, x, y);
}

static s8 StartDoorCloseAnimation(const struct DoorGraphics *gfx, int x, int y)
{
    gfx = GetDoorGraphics(gfx, MapGridGetMetatileIdAt(x, y));
    if (gfx == NULL)
        return -1;
    else if (gfx->size == DOOR_SIZE_1x1)
        return StartDoorAnimationTask(gfx, sDoorAnimFrames_CloseSmall, x, y);
    else
        return StartDoorAnimationTask(gfx, sDoorAnimFrames_CloseLarge, x, y);
}

void FieldSetDoorOpened(int x, int y)
{
    if (MetatileBehavior_IsWarpDoor(MapGridGetMetatileBehaviorAt((s16)x, (s16)y)))
        DrawOpenedDoor(sDoorGraphics, x, y);
}

void FieldSetDoorClosed(int x, int y)
{
    if (MetatileBehavior_IsWarpDoor(MapGridGetMetatileBehaviorAt((s16)x, (s16)y)))
        DrawClosedDoor(sDoorGraphics, x, y);
}

s8 FieldAnimateDoorClose(int x, int y)
{
    if (!MetatileBehavior_IsWarpDoor(MapGridGetMetatileBehaviorAt((s16)x, (s16)y)))
        return -1;
    return StartDoorCloseAnimation(sDoorGraphics, x, y);
}

s8 FieldAnimateDoorOpen(int x, int y)
{
    if (!MetatileBehavior_IsWarpDoor(MapGridGetMetatileBehaviorAt((s16)x, (s16)y)))
        return -1;
    return AnimateDoorOpenInternal(sDoorGraphics, x, y);
}

bool8 FieldIsDoorAnimationRunning(void)
{
    return FuncIsActiveTask(Task_AnimateDoor);
}

u16 GetDoorSoundEffect(int x, int y)
{
    if (GetDoorSoundType(sDoorGraphics, x, y) == DOOR_SOUND_NORMAL)
        return SE_DOOR;
    else // DOOR_SOUND_SLIDING
        return SE_SLIDING_DOOR;
}

static s8 GetDoorSoundType(const struct DoorGraphics *gfx, int x, int y)
{
    gfx = GetDoorGraphics(gfx, MapGridGetMetatileIdAt(x, y));
    if (gfx == NULL)
        return -1;
    return gfx->sound;
}
