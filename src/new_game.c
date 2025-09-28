#include "global.h"
#include "new_game.h"
#include "random.h"
#include "pokemon.h"
#include "roamer.h"
#include "pokemon_size_record.h"
#include "script.h"
#include "lottery_corner.h"
#include "play_time.h"
#include "mauville_old_man.h"
#include "match_call.h"
#include "lilycove_lady.h"
#include "load_save.h"
#include "pokeblock.h"
#include "dewford_trend.h"
#include "berry.h"
#include "rtc.h"
#include "easy_chat.h"
#include "event_data.h"
#include "money.h"
#include "trainer_hill.h"
#include "tv.h"
#include "coins.h"
#include "text.h"
#include "overworld.h"
#include "mail.h"
#include "battle_records.h"
#include "item.h"
#include "pokedex.h"
#include "apprentice.h"
#include "frontier_util.h"
#include "pokedex.h"
#include "save.h"
#include "link_rfu.h"
#include "main.h"
#include "contest.h"
#include "item_menu.h"
#include "pokemon_storage_system.h"
#include "pokemon_jump.h"
#include "decoration_inventory.h"
#include "secret_base.h"
#include "player_pc.h"
#include "field_specials.h"
#include "berry_powder.h"
#include "mystery_gift.h"
#include "union_room_chat.h"
#include "constants/items.h"
#include "tx_randomizer_and_challenges.h"

extern const u8 EventScript_ResetAllMapFlags[];

static void ClearFrontierRecord(void);
static void WarpToTruck(void);
static void ResetMiniGamesRecords(void);

EWRAM_DATA bool8 gDifferentSaveFile = FALSE;
EWRAM_DATA bool8 gEnableContestDebugging = FALSE;

static const struct ContestWinner sContestWinnerPicDummy =
{
    .monName = _(""),
    .trainerName = _("")
};

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

u32 GetTrainerId(u8 *trainerId)
{
    return (trainerId[3] << 24) | (trainerId[2] << 16) | (trainerId[1] << 8) | (trainerId[0]);
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < TRAINER_ID_LENGTH; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = (Random() << 16) | GetGeneratedTrainerIdLower();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

// L=A isnt set here for some reason.
static void SetDefaultOptions(void)
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_STEREO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SHIFT; //HnS
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsDifficulty = 1;
    gSaveBlock2Ptr->optionsfollowerEnable = 0;
    gSaveBlock2Ptr->optionsfollowerLargeEnable = 0;
    gSaveBlock2Ptr->optionsautoRun = 1;
    gSaveBlock2Ptr->optionsAutorunDive = 1;
    gSaveBlock2Ptr->optionsAutorunSurf = 1;
    gSaveBlock2Ptr->optionsDisableMatchCall = 0;
    gSaveBlock2Ptr->optionStyle = 0;
    gSaveBlock2Ptr->optionTypeEffective = 0;
    gSaveBlock2Ptr->optionsFishing = 1;
    gSaveBlock2Ptr->optionsFastIntro = 1;
    gSaveBlock2Ptr->optionsFastBattle = 0; //HnS
    gSaveBlock2Ptr->optionsBikeMusic = 0;
    gSaveBlock2Ptr->optionsEvenFasterJoy = 1;
    gSaveBlock2Ptr->optionsSurfMusic = 0;
    gSaveBlock2Ptr->optionsWildBattleMusic = 3;
    gSaveBlock2Ptr->optionsTrainerBattleMusic = 3; //JOHTO ONLY BB
    gSaveBlock2Ptr->optionsFrontierTrainerBattleMusic = 3; //JOHTO ONLY BB
    gSaveBlock2Ptr->optionsSoundEffects = 2; //JOHTO ONLY BB
    gSaveBlock2Ptr->optionsSkipIntro = 1;
    gSaveBlock2Ptr->optionsLRtoRun = 0;
    gSaveBlock2Ptr->optionsBallPrompt = 0; //HnS
    gSaveBlock2Ptr->optionsUnitSystem = 0;
    gSaveBlock2Ptr->optionsMusicOnOff = 0;
    gSaveBlock2Ptr->optionsNewBackgrounds = 1; //HnS
    gSaveBlock2Ptr->optionsRunType = 1;
}

static void ClearPokedexFlags(void)
{
    gUnusedPokedexU8 = 0;
    memset(&gSaveBlock2Ptr->pokedex.owned, 0, sizeof(gSaveBlock2Ptr->pokedex.owned));
    memset(&gSaveBlock2Ptr->pokedex.seen, 0, sizeof(gSaveBlock2Ptr->pokedex.seen));
}

void ClearAllContestWinnerPics(void)
{
    s32 i;

    ClearContestWinnerPicsInContestHall();

    // Clear Museum paintings
    for (i = MUSEUM_CONTEST_WINNERS_START; i < NUM_CONTEST_WINNERS; i++)
        gSaveBlock1Ptr->contestWinners[i] = sContestWinnerPicDummy;
}

static void ClearFrontierRecord(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->frontier, sizeof(gSaveBlock2Ptr->frontier));

    gSaveBlock2Ptr->frontier.opponentNames[0][0] = EOS;
    gSaveBlock2Ptr->frontier.opponentNames[1][0] = EOS;
}

static void WarpToTruck(void)
{
    SaveData_TxRandomizerAndChallenges();
    SetWarpDestination(MAP_GROUP(NEW_BARK_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(NEW_BARK_TOWN_PLAYERS_HOUSE_2F), 1, 0, 0);
    WarpIntoMap();
}

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ResetPokedexScrollPositions();
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagScrollPositions();
    ResetPokeblockScrollPositions();
}

void NewGameInitData(void)
{
    bool8 HardPrev = FlagGet(FLAG_DIFFICULTY_HARD);
    bool8 TMPrev = FlagGet(FLAG_FINITE_TMS);
    bool8 UnlimitedWT = FlagGet(FLAG_UNLIMITIED_WONDERTRADE);
    bool8 EnableMints = FlagGet(FLAG_MINTS_ENABLED);
    bool8 EnableExtraLegendaries = FlagGet(FLAG_EXTRA_LEGENDARIES);

    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
        RtcReset();

    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetPokedex();
    ClearFrontierRecord();
    ClearSav1();
    ClearAllMail();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    ClearTVShowData();
    ResetGabbyAndTy();
    ClearSecretBases();
    ClearBerryTrees();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    SetCoins(0);
    ResetLinkContestBoolean();
    ResetGameStats();
    ClearAllContestWinnerPics();
    ClearPlayerLinkBattleRecords();
    InitSeedotSizeRecord();
    InitLotadSizeRecord();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    ClearRoamerData();
    ClearRoamerLocationData();
    gSaveBlock1Ptr->registeredItem = ITEM_NONE;
    gSaveBlock1Ptr->registeredLongItem = 0;
    ClearBag();
    NewGameInitPCItems();
    ClearPokeblocks();
    ClearDecorationInventories();
    InitEasyChatPhrases();
    SetMauvilleOldMan();
    InitDewfordTrend();
    ResetFanClub();
    ResetLotteryCorner();
    WarpToTruck();
    RunScriptImmediately(EventScript_ResetAllMapFlags);
    ResetMiniGamesRecords();
    InitUnionRoomChatRegisteredTexts();
    InitLilycoveLady();
    ResetAllApprenticeData();
    ClearRankingHallRecords();
    InitMatchCallCounters();
    ClearMysteryGift();
    WipeTrainerNameRecords();
    ResetTrainerHillResults();
    ResetContestLinkResults();
    RandomizeTypeEffectivenessListEWRAM(Random32());
    if ((gSaveBlock1Ptr->tx_Features_PkmnDeath) && (gSaveBlock1Ptr->tx_Challenges_Nuzlocke))
        gSaveBlock1Ptr->tx_Features_PkmnDeath = 0;

    HardPrev ? FlagSet(FLAG_DIFFICULTY_HARD) : FlagClear(FLAG_DIFFICULTY_HARD);
    TMPrev ? FlagSet(FLAG_FINITE_TMS) : FlagClear(FLAG_FINITE_TMS);
    UnlimitedWT ? FlagSet(FLAG_UNLIMITIED_WONDERTRADE) : FlagClear(FLAG_UNLIMITIED_WONDERTRADE);
    EnableMints ? FlagSet(FLAG_MINTS_ENABLED) : FlagClear(FLAG_MINTS_ENABLED);
    EnableExtraLegendaries ? FlagSet(FLAG_EXTRA_LEGENDARIES) : FlagClear(FLAG_EXTRA_LEGENDARIES);

    gSaveBlock1Ptr->versionIdMagic = SAVE_MAGIC_NUM;
    gSaveBlock1Ptr->versionId = SAVE_VERSION;

    /*if (difficultyPrev == DIFFICULTY_EASY)
        VarSet(VAR_DIFFICULTY, DIFFICULTY_EASY);
    else if (difficultyPrev == DIFFICULTY_NORMAL)
        VarSet(VAR_DIFFICULTY, DIFFICULTY_NORMAL);
    else if (difficultyPrev == DIFFICULTY_HARD)
        VarSet(VAR_DIFFICULTY, DIFFICULTY_HARD);*/
    
}
void CheckIfChallengesAreActive(void)
{
    if (((gSaveBlock1Ptr->tx_Challenges_Nuzlocke) == 1)
    || (gSaveBlock1Ptr->tx_Challenges_EvoLimit == 1)
    || (gSaveBlock1Ptr->tx_Challenges_BaseStatEqualizer == 1)
    || (gSaveBlock1Ptr->tx_Challenges_Mirror == 1)
    || (gSaveBlock1Ptr->tx_Challenges_Mirror_Thief == 1)
    || (gSaveBlock1Ptr->tx_Challenges_PkmnCenter == 1)
    || (IsOneTypeChallengeActive()))
        FlagSet(FLAG_NO_WT_BECAUSE_CHALLENGE);       
}

void CheckIfRandomizerIsActive(void)
{
    if (((gSaveBlock1Ptr->tx_Random_Chaos == 1)
        || (gSaveBlock1Ptr->tx_Random_WildPokemon == 1)
        || (gSaveBlock1Ptr->tx_Random_Similar == 1)
        || (gSaveBlock1Ptr->tx_Random_MapBased == 1)
        || (gSaveBlock1Ptr->tx_Random_IncludeLegendaries == 1)
        || (gSaveBlock1Ptr->tx_Random_Type == 1)
        || (gSaveBlock1Ptr->tx_Random_TypeEffectiveness == 1)
        || (gSaveBlock1Ptr->tx_Random_Abilities == 1)
        || (gSaveBlock1Ptr->tx_Random_Moves == 1)
        || (gSaveBlock1Ptr->tx_Random_Trainer == 1)
        || (gSaveBlock1Ptr->tx_Random_Evolutions == 1)
        || (gSaveBlock1Ptr->tx_Random_EvolutionMethods == 1)
        || (gSaveBlock1Ptr->tx_Random_Items == 1)))
            FlagSet(FLAG_WT_ENABLED_RANDOMIZER);
}

static void ResetMiniGamesRecords(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    ResetPokemonJumpRecords();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}
