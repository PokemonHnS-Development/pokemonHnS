#include "constants/species.h"
#include "global.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "pokedex.h"
#include "pokemon.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "starter_choose.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "trainer_pokemon_sprites.h"
#include "trig.h"
#include "window.h"
#include "constants/songs.h"
#include "constants/rgb.h"
#include "tx_randomizer_and_challenges.h"
#include "script_pokemon_util.h"
#include "random.h"
#include "field_effect.h"


#define STARTER_MON_COUNT   3

// Position of the sprite of the selected starter Pokémon
#define STARTER_PKMN_POS_X (DISPLAY_WIDTH / 2)
#define STARTER_PKMN_POS_Y 64

#define TAG_POKEBALL_SELECT 0x1000
#define TAG_STARTER_CIRCLE  0x1001

static void CB2_StarterChoose(void);
static void ClearStarterLabel(void);
static void Task_StarterChoose(u8 taskId);
static void Task_HandleStarterChooseInput(u8 taskId);
static void Task_WaitForStarterSprite(u8 taskId);
static void Task_AskConfirmStarter(u8 taskId);
static void Task_HandleConfirmStarterInput(u8 taskId);
static void Task_DeclineStarter(u8 taskId);
static void Task_MoveStarterChooseCursor(u8 taskId);
static void Task_CreateStarterLabel(u8 taskId);
static void CreateStarterPokemonLabel(u8 selection);
static u8 CreatePokemonFrontSprite(u16 species, u8 x, u8 y);
static u8 CreatePokemonFrontSpriteChikorita(u16 species, u8 x, u8 y);
static u8 CreatePokemonFrontSpriteCyndaquil(u16 species, u8 x, u8 y);
static u8 CreatePokemonFrontSpriteTotodile(u16 species, u8 x, u8 y);
static void SpriteCB_SelectionHand(struct Sprite *sprite);
static void SpriteCB_Pokeball(struct Sprite *sprite);
static void SpriteCB_StarterPokemon(struct Sprite *sprite);

static u16 sStarterLabelWindowId;

const u16 gBirchBagGrass_Pal[] = INCBIN_U16("graphics/starter_choose/tiles.gbapal");
static const u16 sPokeballSelection_Pal[] = INCBIN_U16("graphics/starter_choose/pokeball_selection.gbapal");
static const u16 sStarterCircle_Pal[] = INCBIN_U16("graphics/starter_choose/starter_circle.gbapal");
const u32 gBirchBagTilemap[] = INCBIN_U32("graphics/starter_choose/birch_bag.bin.lz");
const u32 gBirchGrassTilemap[] = INCBIN_U32("graphics/starter_choose/birch_grass.bin.lz");
const u32 gBirchBagGrass_Gfx[] = INCBIN_U32("graphics/starter_choose/tiles.4bpp.lz");
const u32 gPokeballSelection_Gfx[] = INCBIN_U32("graphics/starter_choose/pokeball_selection.4bpp.lz");
static const u32 sStarterCircle_Gfx[] = INCBIN_U32("graphics/starter_choose/starter_circle.4bpp.lz");

EWRAM_DATA static u16 sStarterList[3] = {0};

static const struct WindowTemplate sWindowTemplates[] =
{
    {
        .bg = 0,
        .tilemapLeft = 3,
        .tilemapTop = 15,
        .width = 24,
        .height = 4,
        .paletteNum = 14,
        .baseBlock = 0x0200
    },
    DUMMY_WIN_TEMPLATE,
};

static const struct WindowTemplate sWindowTemplate_ConfirmStarter =
{
    .bg = 0,
    .tilemapLeft = 24,
    .tilemapTop = 9,
    .width = 5,
    .height = 4,
    .paletteNum = 14,
    .baseBlock = 0x0260
};

static const struct WindowTemplate sWindowTemplate_StarterLabel =
{
    .bg = 0,
    .tilemapLeft = 0,
    .tilemapTop = 0,
    .width = 13,
    .height = 4,
    .paletteNum = 14,
    .baseBlock = 0x0274
};

static const u8 sPokeballCoords[STARTER_MON_COUNT][2] =
{
    {60, 64},
    {120, 88},
    {180, 64},
};

static const u8 sStarterLabelCoords[STARTER_MON_COUNT][2] =
{
    {0, 9},
    {16, 10},
    {8, 4},
};

static const u16 sStarterMon[STARTER_MON_COUNT] =
{
    SPECIES_CHIKORITA,
    SPECIES_CYNDAQUIL,
    SPECIES_TOTODILE,
};

static const struct BgTemplate sBgTemplates[3] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 7,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 6,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
};

static const u8 sTextColors[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY};

static const struct OamData sOam_Hand =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct OamData sOam_Pokeball =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const struct OamData sOam_StarterCircle =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_DOUBLE,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const u8 sCursorCoords[][2] =
{
    {60, 32},
    {120, 56},
    {180, 32},
};

static const union AnimCmd sAnim_Hand[] =
{
    ANIMCMD_FRAME(48, 30),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_Pokeball_Still[] =
{
    ANIMCMD_FRAME(0, 30),
    ANIMCMD_END,
};

static const union AnimCmd sAnim_Pokeball_Moving[] =
{
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(32, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(16, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(32, 4),
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_FRAME(16, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(32, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(16, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(32, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_StarterCircle[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_END,
};

static const union AnimCmd * const sAnims_Hand[] =
{
    sAnim_Hand,
};

static const union AnimCmd * const sAnims_Pokeball[] =
{
    sAnim_Pokeball_Still,
    sAnim_Pokeball_Moving,
};

static const union AnimCmd * const sAnims_StarterCircle[] =
{
    sAnim_StarterCircle,
};

static const union AffineAnimCmd sAffineAnim_StarterPokemon[] =
{
    AFFINEANIMCMD_FRAME(16, 16, 0, 0),
    AFFINEANIMCMD_FRAME(16, 16, 0, 15),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_StarterCircle[] =
{
    AFFINEANIMCMD_FRAME(20, 20, 0, 0),
    AFFINEANIMCMD_FRAME(20, 20, 0, 15),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd * const sAffineAnims_StarterPokemon = {sAffineAnim_StarterPokemon};
static const union AffineAnimCmd * const sAffineAnims_StarterCircle[] = {sAffineAnim_StarterCircle};

static const struct CompressedSpriteSheet sSpriteSheet_PokeballSelect[] =
{
    {
        .data = gPokeballSelection_Gfx,
        .size = 0x0800,
        .tag = TAG_POKEBALL_SELECT
    },
    {}
};

static const struct CompressedSpriteSheet sSpriteSheet_StarterCircle[] =
{
    {
        .data = sStarterCircle_Gfx,
        .size = 0x0800,
        .tag = TAG_STARTER_CIRCLE
    },
    {}
};

static const struct SpritePalette sSpritePalettes_StarterChoose[] =
{
    {
        .data = sPokeballSelection_Pal,
        .tag = TAG_POKEBALL_SELECT
    },
    {
        .data = sStarterCircle_Pal,
        .tag = TAG_STARTER_CIRCLE
    },
    {},
};

static const struct SpriteTemplate sSpriteTemplate_Hand =
{
    .tileTag = TAG_POKEBALL_SELECT,
    .paletteTag = TAG_POKEBALL_SELECT,
    .oam = &sOam_Hand,
    .anims = sAnims_Hand,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_SelectionHand
};

static const struct SpriteTemplate sSpriteTemplate_Pokeball =
{
    .tileTag = TAG_POKEBALL_SELECT,
    .paletteTag = TAG_POKEBALL_SELECT,
    .oam = &sOam_Pokeball,
    .anims = sAnims_Pokeball,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_Pokeball
};

static const struct SpriteTemplate sSpriteTemplate_StarterCircle =
{
    .tileTag = TAG_STARTER_CIRCLE,
    .paletteTag = TAG_STARTER_CIRCLE,
    .oam = &sOam_StarterCircle,
    .anims = sAnims_StarterCircle,
    .images = NULL,
    .affineAnims = sAffineAnims_StarterCircle,
    .callback = SpriteCB_StarterPokemon
};

// .text
u16 GetStarterPokemon(u16 chosenStarterId)
{
    //tx_randomizer_and_challenges
    u16 mon = sStarterMon[chosenStarterId];
    u16 i;

    if (chosenStarterId > STARTER_MON_COUNT)
        chosenStarterId = 0;
    //tx_randomizer_and_challenges
    if (IsOneTypeChallengeActive())
    {
        if (sStarterList[chosenStarterId] == 0)
            sStarterList[chosenStarterId] = PickRandomStarterForOneTypeChallenge(sStarterList, chosenStarterId);
        mon = sStarterList[chosenStarterId];
    }
    else if (gSaveBlock1Ptr->tx_Random_Starter)
    {
        if (sStarterList[chosenStarterId] == 0)
            sStarterList[chosenStarterId] = PickRandomStarter(sStarterList, chosenStarterId);
        mon = sStarterList[chosenStarterId];
    }

    #ifndef NDEBUG
        MgbaPrintf(MGBA_LOG_DEBUG, "new species[%d]", mon);
    #endif

    return mon;
}

static void VblankCB_StarterChoose(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

// Data for Task_StarterChoose
#define tStarterSelection   data[0]
#define tPkmnSpriteId       data[1]
#define tCircleSpriteId     data[2]

// Data for sSpriteTemplate_Pokeball
#define sTaskId data[0]
#define sBallId data[1]

void CB2_ChooseStarter(void)
{
    u8 taskId;
    u8 spriteId;

    SetVBlankCallback(NULL);

    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG3CNT, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);

    ChangeBgX(0, 0, BG_COORD_SET);
    ChangeBgY(0, 0, BG_COORD_SET);
    ChangeBgX(1, 0, BG_COORD_SET);
    ChangeBgY(1, 0, BG_COORD_SET);
    ChangeBgX(2, 0, BG_COORD_SET);
    ChangeBgY(2, 0, BG_COORD_SET);
    ChangeBgX(3, 0, BG_COORD_SET);
    ChangeBgY(3, 0, BG_COORD_SET);

    DmaFill16(3, 0, VRAM, VRAM_SIZE);
    DmaFill32(3, 0, OAM, OAM_SIZE);
    DmaFill16(3, 0, PLTT, PLTT_SIZE);

    LZ77UnCompVram(gBirchBagGrass_Gfx, (void *)VRAM);
    LZ77UnCompVram(gBirchBagTilemap, (void *)(BG_SCREEN_ADDR(6)));
    LZ77UnCompVram(gBirchGrassTilemap, (void *)(BG_SCREEN_ADDR(7)));

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
    InitWindows(sWindowTemplates);

    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(0, 0x2A8, BG_PLTT_ID(13));
    ClearScheduledBgCopiesToVram();
    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetAllPicSprites();

    LoadPalette(GetOverworldTextboxPalettePtr(), BG_PLTT_ID(14), PLTT_SIZE_4BPP);
    LoadPalette(gBirchBagGrass_Pal, BG_PLTT_ID(0), sizeof(gBirchBagGrass_Pal));
    LoadCompressedSpriteSheet(&sSpriteSheet_PokeballSelect[0]);
    LoadCompressedSpriteSheet(&sSpriteSheet_StarterCircle[0]);
    LoadSpritePalettes(sSpritePalettes_StarterChoose);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);

    EnableInterrupts(DISPSTAT_VBLANK);
    SetVBlankCallback(VblankCB_StarterChoose);
    SetMainCallback2(CB2_StarterChoose);

    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG1 | BLDCNT_TGT1_BG2 | BLDCNT_TGT1_BG3 | BLDCNT_TGT1_OBJ | BLDCNT_TGT1_BD | BLDCNT_EFFECT_DARKEN);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 7);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);

    ShowBg(0);
    ShowBg(2);
    ShowBg(3);

    taskId = CreateTask(Task_StarterChoose, 0);
    gTasks[taskId].tStarterSelection = 1;

    // Create hand sprite
    spriteId = CreateSprite(&sSpriteTemplate_Hand, 120, 56, 2);
    gSprites[spriteId].data[0] = taskId;

    // Create three Poké Ball sprites
    spriteId = CreateSprite(&sSpriteTemplate_Pokeball, sPokeballCoords[0][0], sPokeballCoords[0][1], 2);
    gSprites[spriteId].sTaskId = taskId;
    gSprites[spriteId].sBallId = 0;

    spriteId = CreateSprite(&sSpriteTemplate_Pokeball, sPokeballCoords[1][0], sPokeballCoords[1][1], 2);
    gSprites[spriteId].sTaskId = taskId;
    gSprites[spriteId].sBallId = 1;

    spriteId = CreateSprite(&sSpriteTemplate_Pokeball, sPokeballCoords[2][0], sPokeballCoords[2][1], 2);
    gSprites[spriteId].sTaskId = taskId;
    gSprites[spriteId].sBallId = 2;

    sStarterLabelWindowId = WINDOW_NONE;
}

static void CB2_StarterChoose(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void Task_StarterChoose(u8 taskId)
{
    CreateStarterPokemonLabel(gTasks[taskId].tStarterSelection);
    DrawStdFrameWithCustomTileAndPalette(0, FALSE, 0x2A8, 0xD);
    AddTextPrinterParameterized(0, FONT_NORMAL, gText_BirchInTrouble, 0, 1, 0, NULL);
    PutWindowTilemap(0);
    ScheduleBgCopyTilemapToVram(0);
    gTasks[taskId].func = Task_HandleStarterChooseInput;
}

static void Task_HandleStarterChooseInput(u8 taskId)
{
    u8 selection = gTasks[taskId].tStarterSelection;

    if (JOY_NEW(A_BUTTON))
    {
        u8 spriteId;

        ClearStarterLabel();

        // Create white circle background
        spriteId = CreateSprite(&sSpriteTemplate_StarterCircle, sPokeballCoords[selection][0], sPokeballCoords[selection][1], 1);
        gTasks[taskId].tCircleSpriteId = spriteId;

        // Create Pokémon sprites. It is now divided in 3 lines as every starter has it's own function so that their sprites are handled individually.
        // This allows individual control in the case of one starter being shiny but the rest not. 
        // Keeping this as one line makes all starters shiny as there is no individual control.
        if (selection == 1)
            spriteId = CreatePokemonFrontSpriteCyndaquil(GetStarterPokemon(1), sPokeballCoords[selection][0], sPokeballCoords[selection][1]);
        else if (selection == 0)
            spriteId = CreatePokemonFrontSpriteChikorita(GetStarterPokemon(0), sPokeballCoords[selection][0], sPokeballCoords[selection][1]);
        else if (selection == 2)
            spriteId = CreatePokemonFrontSpriteTotodile(GetStarterPokemon(2), sPokeballCoords[selection][0], sPokeballCoords[selection][1]);
        //spriteId = CreatePokemonFrontSprite(GetStarterPokemon(gTasks[taskId].tStarterSelection), sPokeballCoords[selection][0], sPokeballCoords[selection][1]);
        gSprites[spriteId].affineAnims = &sAffineAnims_StarterPokemon;
        gSprites[spriteId].callback = SpriteCB_StarterPokemon;

        gTasks[taskId].tPkmnSpriteId = spriteId;
        gTasks[taskId].func = Task_WaitForStarterSprite;
    }
    else if (JOY_NEW(DPAD_LEFT) && selection > 0)
    {
        gTasks[taskId].tStarterSelection--;
        gTasks[taskId].func = Task_MoveStarterChooseCursor;
    }
    else if (JOY_NEW(DPAD_RIGHT) && selection < STARTER_MON_COUNT - 1)
    {
        gTasks[taskId].tStarterSelection++;
        gTasks[taskId].func = Task_MoveStarterChooseCursor;
    }
}

static void Task_WaitForStarterSprite(u8 taskId)
{
    if (gSprites[gTasks[taskId].tCircleSpriteId].affineAnimEnded &&
        gSprites[gTasks[taskId].tCircleSpriteId].x == STARTER_PKMN_POS_X &&
        gSprites[gTasks[taskId].tCircleSpriteId].y == STARTER_PKMN_POS_Y)
    {
        gTasks[taskId].func = Task_AskConfirmStarter;
    }
}

static void Task_AskConfirmStarter(u8 taskId)
{
    PlayCry_Normal(GetStarterPokemon(gTasks[taskId].tStarterSelection), 0);
    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    AddTextPrinterParameterized(0, FONT_NORMAL, gText_ConfirmStarterChoice, 0, 1, 0, NULL);
    ScheduleBgCopyTilemapToVram(0);
    CreateYesNoMenu(&sWindowTemplate_ConfirmStarter, 0x2A8, 0xD, 0);
    gTasks[taskId].func = Task_HandleConfirmStarterInput;
}

static void Task_HandleConfirmStarterInput(u8 taskId)
{
    u8 spriteId;

    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:  // YES
        // Return the starter choice and exit.
        gSpecialVar_Result = gTasks[taskId].tStarterSelection;
        ResetAllPicSprites();
        SetMainCallback2(gMain.savedCallback);
        break;
    case 1:  // NO
    case MENU_B_PRESSED:
    // When pressing B or saying NO clears the SHINY_STARTER_X flag so it doesn't affect your next starter selection.
        FlagClear(FLAG_SHINY_STARTER_1);
        FlagClear(FLAG_SHINY_STARTER_2);
        FlagClear(FLAG_SHINY_STARTER_3);
        PlaySE(SE_SELECT);
        spriteId = gTasks[taskId].tPkmnSpriteId;
        FreeOamMatrix(gSprites[spriteId].oam.matrixNum);
        FreeAndDestroyMonPicSprite(spriteId);

        spriteId = gTasks[taskId].tCircleSpriteId;
        FreeOamMatrix(gSprites[spriteId].oam.matrixNum);
        DestroySprite(&gSprites[spriteId]);
        gTasks[taskId].func = Task_DeclineStarter;
        break;
    }
}

static void Task_DeclineStarter(u8 taskId)
{
    gTasks[taskId].func = Task_StarterChoose;
}

static void CreateStarterPokemonLabel(u8 selection)
{
    u8 categoryText[32];
    struct WindowTemplate winTemplate;
    const u8 *speciesName;
    s32 width;
    u8 labelLeft, labelRight, labelTop, labelBottom;

    u16 species = GetStarterPokemon(selection);
    CopyMonCategoryText(SpeciesToNationalPokedexNum(species), categoryText);
    speciesName = gSpeciesNames[species];

    winTemplate = sWindowTemplate_StarterLabel;
    winTemplate.tilemapLeft = sStarterLabelCoords[selection][0];
    winTemplate.tilemapTop = sStarterLabelCoords[selection][1];

    sStarterLabelWindowId = AddWindow(&winTemplate);
    FillWindowPixelBuffer(sStarterLabelWindowId, PIXEL_FILL(0));

    width = GetStringCenterAlignXOffset(FONT_NARROW, categoryText, 0x68);
    AddTextPrinterParameterized3(sStarterLabelWindowId, FONT_NARROW, width, 1, sTextColors, 0, categoryText);

    width = GetStringCenterAlignXOffset(FONT_NORMAL, speciesName, 0x68);
    AddTextPrinterParameterized3(sStarterLabelWindowId, FONT_NORMAL, width, 17, sTextColors, 0, speciesName);

    PutWindowTilemap(sStarterLabelWindowId);
    ScheduleBgCopyTilemapToVram(0);

    labelLeft = sStarterLabelCoords[selection][0] * 8 - 4;
    labelRight = (sStarterLabelCoords[selection][0] + 13) * 8 + 4;
    labelTop = sStarterLabelCoords[selection][1] * 8;
    labelBottom = (sStarterLabelCoords[selection][1] + 4) * 8;
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(labelLeft, labelRight));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(labelTop, labelBottom));
}

static void ClearStarterLabel(void)
{
    FillWindowPixelBuffer(sStarterLabelWindowId, PIXEL_FILL(0));
    ClearWindowTilemap(sStarterLabelWindowId);
    RemoveWindow(sStarterLabelWindowId);
    sStarterLabelWindowId = WINDOW_NONE;
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    ScheduleBgCopyTilemapToVram(0);
}

static void Task_MoveStarterChooseCursor(u8 taskId)
{
    ClearStarterLabel();
    gTasks[taskId].func = Task_CreateStarterLabel;
}

static void Task_CreateStarterLabel(u8 taskId)
{
    CreateStarterPokemonLabel(gTasks[taskId].tStarterSelection);
    gTasks[taskId].func = Task_HandleStarterChooseInput;
}

static u8 CreatePokemonFrontSpriteCyndaquil(u16 species, u8 x, u8 y)
{
    u8 spriteId;
    static u32 isShinyCyndaquil = 0;
    
    // Take a number between 0 and 8192 and compare it to the SHINY_ODDS selected. If it matches a number that could make a POKéMON shiny, forces a 
    // shiny sprite, only on the selected starter. Uses a static u32 because if not, the random number would be generated every time each starter is selected.
    if (isShinyCyndaquil == 0)
        isShinyCyndaquil = (Random()% 8192);

    if ((isShinyCyndaquil < SHINY_ODDS) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 0)) // 1/8192
    {
        FlagSet(FLAG_SHINY_STARTER_1);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 0, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyCyndaquil < 16) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 1)) // 1/4096
    {
        FlagSet(FLAG_SHINY_STARTER_1);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE); //the 1 before MON_PIC_AFFINE forces a shiny pic of the mon. 
    }                                                                                                     //Setting to 0 only affects og SHINY ODDS. Non-og SHINY_ODDS need a 1.
    else if ((isShinyCyndaquil < 32) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 2)) // 1/2048
    {
        FlagSet(FLAG_SHINY_STARTER_1);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyCyndaquil < 64) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 3)) // 1/1024
    {
        FlagSet(FLAG_SHINY_STARTER_1);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyCyndaquil < 128) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 4)) // 1/512
    {
        FlagSet(FLAG_SHINY_STARTER_1);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else
        spriteId = CreateMonPicSprite_Affine(species, 8, 0, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    gSprites[spriteId].oam.priority = 0;
    return spriteId;
}

static u8 CreatePokemonFrontSpriteChikorita(u16 species, u8 x, u8 y)
{
    u8 spriteId;
    static u32 isShinyChikorita = 0;

    if (isShinyChikorita == 0)
        isShinyChikorita = (Random()% 8192);

    if ((isShinyChikorita < SHINY_ODDS) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 0)) // 1/8192
    {
        FlagSet(FLAG_SHINY_STARTER_2);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 0, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyChikorita < 16) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 1)) // 1/4096
    {
        FlagSet(FLAG_SHINY_STARTER_2);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyChikorita < 32) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 2)) // 1/2048
    {
        FlagSet(FLAG_SHINY_STARTER_2);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyChikorita < 64) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 3)) // 1/1024
    {
        FlagSet(FLAG_SHINY_STARTER_2);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyChikorita < 128) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 4)) // 1/512
    {
        FlagSet(FLAG_SHINY_STARTER_2);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else
        spriteId = CreateMonPicSprite_Affine(species, 8, 0, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    gSprites[spriteId].oam.priority = 0;
    return spriteId;
}

static u8 CreatePokemonFrontSpriteTotodile(u16 species, u8 x, u8 y)
{
    u8 spriteId;
    static u32 isShinyTotodile = 0;

    if (isShinyTotodile == 0)
        isShinyTotodile = (Random()% 8192);

    if ((isShinyTotodile < SHINY_ODDS) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 0)) // 1/8192
    {
        FlagSet(FLAG_SHINY_STARTER_3);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 0, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyTotodile < 16) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 1)) // 1/4096
    {
        FlagSet(FLAG_SHINY_STARTER_3);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyTotodile < 32) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 2)) // 1/2048
    {
        FlagSet(FLAG_SHINY_STARTER_3);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyTotodile < 64) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 3)) // 1/1024
    {
        FlagSet(FLAG_SHINY_STARTER_3);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else if ((isShinyTotodile < 128) && (gSaveBlock1Ptr->tx_Features_ShinyChance == 4)) // 1/512
    {
        FlagSet(FLAG_SHINY_STARTER_3);
        spriteId = CreateMonPicSprite_Affine(species, TRUE, 1, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    }
    else
        spriteId = CreateMonPicSprite_Affine(species, 8, 0, MON_PIC_AFFINE_FRONT, x, y, 14, TAG_NONE);
    gSprites[spriteId].oam.priority = 0;
    return spriteId;
}


static void SpriteCB_SelectionHand(struct Sprite *sprite)
{
    // Float up and down above selected Poké Ball
    sprite->x = sCursorCoords[gTasks[sprite->data[0]].tStarterSelection][0];
    sprite->y = sCursorCoords[gTasks[sprite->data[0]].tStarterSelection][1];
    sprite->y2 = Sin(sprite->data[1], 8);
    sprite->data[1] = (u8)(sprite->data[1]) + 4;
}

static void SpriteCB_Pokeball(struct Sprite *sprite)
{
    // Animate Poké Ball if currently selected
    if (gTasks[sprite->sTaskId].tStarterSelection == sprite->sBallId)
        StartSpriteAnimIfDifferent(sprite, 1);
    else
        StartSpriteAnimIfDifferent(sprite, 0);
}

static void SpriteCB_StarterPokemon(struct Sprite *sprite)
{
    // Move sprite to upper center of screen
    if (sprite->x > STARTER_PKMN_POS_X)
        sprite->x -= 4;
    if (sprite->x < STARTER_PKMN_POS_X)
        sprite->x += 4;
    if (sprite->y > STARTER_PKMN_POS_Y)
        sprite->y -= 2;
    if (sprite->y < STARTER_PKMN_POS_Y)
        sprite->y += 2;
}
