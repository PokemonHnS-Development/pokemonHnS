#include "global.h"
#include "event_data.h"
#include "item.h"
#include "tx_randomizer_and_challenges.h"
#include "party_menu.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "constants/items.h"
#include "constants/party_menu.h"
#include "constants/region_map_sections.h"

// Generic functions
bool8 AreFeaturesActivated(void)
{
    if (gSaveBlock1Ptr->tx_Features_ShinyChance
        || gSaveBlock1Ptr->tx_Features_WildMonDropItems
        || gSaveBlock1Ptr->tx_Mode_AlternateSpawns
        || gSaveBlock1Ptr->tx_Mode_InfiniteTMs
        || gSaveBlock1Ptr->tx_Mode_PoisonSurvive
        || gSaveBlock1Ptr->tx_Features_EasierFeebas)
        return TRUE;

    return FALSE;
}

bool8 IsRandomizerActivated(void)
{
    if (gSaveBlock1Ptr->tx_Random_Chaos
        || gSaveBlock1Ptr->tx_Random_WildPokemon
        || gSaveBlock1Ptr->tx_Random_Similar
        || gSaveBlock1Ptr->tx_Random_MapBased
        || gSaveBlock1Ptr->tx_Random_IncludeLegendaries
        || gSaveBlock1Ptr->tx_Random_Type
        || gSaveBlock1Ptr->tx_Random_TypeEffectiveness
        || gSaveBlock1Ptr->tx_Random_Abilities
        || gSaveBlock1Ptr->tx_Random_Moves
        || gSaveBlock1Ptr->tx_Random_Trainer
        || gSaveBlock1Ptr->tx_Random_Evolutions
        || gSaveBlock1Ptr->tx_Random_EvolutionMethods
        || gSaveBlock1Ptr->tx_Random_Items)
        return TRUE;

    return FALSE;
}

bool8 IsRandomItemsActivated(void)
{
    return gSaveBlock1Ptr->tx_Random_Items;
}

bool8 IsDifficultyOptionsActivated(void)
{
    if (gSaveBlock1Ptr->tx_Challenges_PartyLimit
        || gSaveBlock1Ptr->tx_Challenges_LevelCap
        || gSaveBlock1Ptr->tx_Challenges_ExpMultiplier
        || gSaveBlock1Ptr->tx_Challenges_NoItemPlayer
        || gSaveBlock1Ptr->tx_Challenges_NoItemTrainer
        || gSaveBlock1Ptr->tx_Challenges_PkmnCenter
        || gSaveBlock1Ptr->tx_Difficulty_EscapeRopeDig)
        return TRUE;

    return FALSE;
}

bool8 IsOneTypeChallengeActive(void)
{
    return (gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge != TX_CHALLENGE_TYPE_OFF);
}

bool8 AreAnyChallengesActive(void)
{
    if (gSaveBlock1Ptr->tx_Challenges_EvoLimit
        || gSaveBlock1Ptr->tx_Challenges_BaseStatEqualizer
        || gSaveBlock1Ptr->tx_Challenges_Mirror
        || gSaveBlock1Ptr->tx_Challenges_Mirror_Thief
        || gSaveBlock1Ptr->tx_Challenges_MaxPartyIVs
        || gSaveBlock1Ptr->tx_Features_LimitDifficulty
        || IsOneTypeChallengeActive())
        return TRUE;

    return FALSE;
}

bool8 IsNuzlockeActive(void)
{
    if (!FlagGet(FLAG_SYS_POKEMON_GET))     //Nuzlocke has not started
        return FALSE;
    if (!FlagGet(FLAG_ADVENTURE_STARTED))   //Nuzlocke has not started
        return FALSE;
    //if (FlagGet(FLAG_IS_CHAMPION))          //Player is champion and Nuzlocke stopped
    //    return FALSE;
    if (FlagGet(FLAG_DEFEATED_RED))          //Player is defeats Red and Nuzlocke stopped
        return FALSE;

    return gSaveBlock1Ptr->tx_Challenges_Nuzlocke;
}

bool8 IsNuzlockeNicknamingActive(void)
{
    if (!gSaveBlock1Ptr->tx_Challenges_Nuzlocke)
        return FALSE;
    //if (FlagGet(FLAG_IS_CHAMPION))
    //    return FALSE;
    if (FlagGet(FLAG_DEFEATED_RED))          //Player is defeats Red and Nuzlocke stopped
        return FALSE;

    return gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming;
}

bool8 IsPokecenterChallengeActivated(void)
{
    return gSaveBlock1Ptr->tx_Challenges_PkmnCenter;
}

bool8 HMsOverwriteOptionActive(void)
{
    return (gSaveBlock1Ptr->tx_Challenges_Nuzlocke 
            || gSaveBlock1Ptr->tx_Challenges_Mirror 
            || gSaveBlock1Ptr->tx_Random_Moves
            || IsOneTypeChallengeActive());
}

// Nuzlocke code
//Restes: I think this list are the places where the nuzlocke encounter is active.
//Only locations with wild encounters should be here.
//After the first encounter, no more encounters will be possible.
//Egg hatching counts as encounter, plus hatching locations that are not in the list
//below is impossible.
//Eg. Hatching in Pewter City is impossible, as there aren't encounters there, and it's
//not on the list.
const u8 NuzlockeLUT[] = 
{
    //Johto Routes
    [MAPSEC_ROUTE_26] = 0x0,
    [MAPSEC_ROUTE_27] = 0x1,
    [MAPSEC_ROUTE_28] = 0x2,
    [MAPSEC_ROUTE_29] = 0x3,
    [MAPSEC_ROUTE_30] = 0x4,
    [MAPSEC_ROUTE_31] = 0x5,
    [MAPSEC_ROUTE_32] = 0x6,
    [MAPSEC_ROUTE_33] = 0x7,
    [MAPSEC_ROUTE_34] = 0x8,
    [MAPSEC_ROUTE_35] = 0x9,
    [MAPSEC_ROUTE_36] = 0xA,
    [MAPSEC_ROUTE_37] = 0xB,
    [MAPSEC_ROUTE_38] = 0xC,
    [MAPSEC_ROUTE_39] = 0xD,
    [MAPSEC_ROUTE_40] = 0xE,
    [MAPSEC_ROUTE_41] = 0xF,
    [MAPSEC_ROUTE_42] = 0x10,
    [MAPSEC_ROUTE_43] = 0x11,
    [MAPSEC_ROUTE_44] = 0x12,
    [MAPSEC_ROUTE_45] = 0x13,
    [MAPSEC_ROUTE_46] = 0x14,
    [MAPSEC_ROUTE_47] = 0x15,
    [MAPSEC_ROUTE_48] = 0x16,
    //Dungeons
    [MAPSEC_DARK_CAVE] = 0x17,
    [MAPSEC_UNION_CAVE] = 0x18,
    [MAPSEC_ILEX_FOREST] = 0x19,
    [MAPSEC_NATIONAL_PARK] = 0x1A,
    [MAPSEC_WHIRL_ISLANDS] = 0x1B,
    [MAPSEC_CLIFF_CAVE] = 0x1C,
    [MAPSEC_MT_MORTAR] = 0x1D,
    [MAPSEC_LAKE_OF_RAGE] = 0x1E,
    [MAPSEC_ICE_PATH] = 0x1F,
    [MAPSEC_MT_SILVER] = 0x20,
    [MAPSEC_TOHJO_FALLS] = 0x21,
    [MAPSEC_SAFARI_ZONE_GATE] = 0x22,
    //Cities and towns: Johto
    [MAPSEC_AZALEA_TOWN] = 0x23,
    [MAPSEC_MAHOGANY_TOWN] = 0x24,
    [MAPSEC_NEW_BARK_TOWN] = 0x25,
    [MAPSEC_CHERRYGROVE_CITY] = 0x26,
    [MAPSEC_CIANWOOD_CITY] = 0x27,
    [MAPSEC_VIOLET_CITY] = 0x28,
    [MAPSEC_OLIVINE_CITY] = 0x29,
    //Cities and towns: Kanto
    [MAPSEC_PALLET_TOWN] = 0x2A,
    [MAPSEC_VIRIDIAN_CITY] = 0x2B,
    [MAPSEC_VERMILION_CITY] = 0x2C,
    [MAPSEC_CERULEAN_CITY] = 0x2D,
    [MAPSEC_LAVENDER_TOWN] = 0x2E,
    [MAPSEC_SAFFRON_CITY] = 0x2F,
    [MAPSEC_FUCHSIA_CITY] = 0x30,
    //More dungeons
    [MAPSEC_DRAGONS_DEN] = 0x31,
    [MAPSEC_RUINS_OF_ALPH] = 0x32,
    [MAPSEC_GOLDENROD_CITY] = 0x33,
    [MAPSEC_ECRUTEAK_CITY] = 0x34,
    [MAPSEC_EMBEDDED_TOWER] = 0x35,
    [MAPSEC_ROCKET_HIDEOUT] = 0x36,
    [MAPSEC_ROCK_TUNNEL] = 0x37,
    [MAPSEC_MT_MOON] = 0x38,
    [MAPSEC_DIGLETTS_CAVE] = 0x39,
    [MAPSEC_SEAFOAM_ISLANDS] = 0x3A,
    [MAPSEC_CINNABAR_ISLAND] = 0x3B,
    [MAPSEC_VIRIDIAN_FOREST] = 0x3C,
    [MAPSEC_TIN_TOWER] = 0x3D,
    [MAPSEC_VICTORY_ROAD] = 0x3E,
    [MAPSEC_SPROUT_TOWER] = 0x3F,
    [MAPSEC_SLOWPOKE_WELL] = 0x3F,
    [MAPSEC_ARTISAN_CAVE] = 0x40,
    [MAPSEC_DESERT_UNDERPASS] = 0x41, //Unused, hoenn
    [MAPSEC_ALTERING_CAVE_FRLG] = 0x42, //Unused, hoenn
    [MAPSEC_SAFARI_ZONE_AREA5] = 0x43, //Unused, hoenn
    [MAPSEC_SAFARI_ZONE_AREA6] = 0x44, //Unused, hoenn
    //Kanto Routes
    [MAPSEC_ROUTE_1] = 0X46,
    [MAPSEC_ROUTE_2] = 0x47,
    [MAPSEC_ROUTE_3] = 0x48,
    [MAPSEC_ROUTE_4] = 0x49,
    [MAPSEC_ROUTE_5] = 0x4A,
    [MAPSEC_ROUTE_6] = 0x4B,
    [MAPSEC_ROUTE_7] = 0x4C,
    [MAPSEC_ROUTE_8] = 0x4D,
    [MAPSEC_ROUTE_9] = 0x4E,
    [MAPSEC_ROUTE_10] = 0x4F,
    [MAPSEC_ROUTE_11] = 0x50,
    [MAPSEC_ROUTE_12] = 0x51,
    [MAPSEC_ROUTE_13] = 0x52,
    [MAPSEC_ROUTE_14] = 0x53,
    [MAPSEC_ROUTE_15] = 0x54,
    [MAPSEC_ROUTE_16] = 0x55,
    [MAPSEC_ROUTE_17] = 0x56,
    [MAPSEC_ROUTE_18] = 0x57,
    [MAPSEC_ROUTE_19] = 0x58,
    [MAPSEC_ROUTE_20] = 0x59,
    [MAPSEC_ROUTE_21] = 0x5A,
    [MAPSEC_ROUTE_22] = 0x5B,
    [MAPSEC_ROUTE_23] = 0x5C,
    [MAPSEC_ROUTE_24] = 0x5D,
    [MAPSEC_ROUTE_25] = 0x5E
};

//tx_randomizer_and_challenges
u8 NuzlockeFlagSet(u16 mapsec) // @Kurausukun
{
    u8 id = NuzlockeLUT[mapsec];
    u8 * ptr = &gSaveBlock1Ptr->NuzlockeEncounterFlags[id / 8];
    u8 i;
    if (ptr)
        * ptr |= 1 << (id & 7);

    #ifndef NDEBUG
    MgbaPrintf(MGBA_LOG_DEBUG, "NuzlockeFlagSet Id=%d", id);
    for (i=0; i<9; i++)
        MgbaPrintf(MGBA_LOG_DEBUG, "gSaveBlock1Ptr->NuzlockeEncounterFlags[%d] = %d" , i, gSaveBlock1Ptr->NuzlockeEncounterFlags[i]);
    #endif

    return 0;
}
u8 NuzlockeFlagClear(u16 mapsec) // @Kurausukun
{
    u8 id = NuzlockeLUT[mapsec];
    u8 * ptr = &gSaveBlock1Ptr->NuzlockeEncounterFlags[id / 8];
    if (ptr)
        * ptr &= ~(1 << (id & 7));
    return 0;
}
u8 NuzlockeFlagGet(u16 mapsec) // @Kurausukun
{
    u8 id = NuzlockeLUT[mapsec];
    u8 * ptr = &gSaveBlock1Ptr->NuzlockeEncounterFlags[id / 8];

    #ifndef NDEBUG
    MgbaPrintf(MGBA_LOG_DEBUG, "NuzlockeFlagGet Id=%d", id);
    #endif

    if (!ptr)
        return 0;

    if (!(((*ptr) >> (id & 7)) & 1))
        return 0;
    return 1;
}

void NuzlockeDeletePartyMon(u8 position)
{
    if (!gSaveBlock1Ptr->tx_Nuzlocke_Deletion)
    {
        struct Pokemon *pokemon = &gPlayerParty[position];
        u8 val[1] = {TRUE};
        
        SetMonData(pokemon, MON_DATA_NUZLOCKE_RIBBON, val);
        CopyMonToPC(&gPlayerParty[position]);
    }
    PurgeMonOrBoxMon(TOTAL_BOXES_COUNT, position);
}

void NuzlockeDeletePartyMonOption(u8 position)
{
    struct Pokemon *pokemon = &gPlayerParty[position];
    u8 val[1] = {TRUE};
        
    SetMonData(pokemon, MON_DATA_NUZLOCKE_RIBBON, val);
    CopyMonToPC(&gPlayerParty[position]);
    PurgeMonOrBoxMon(TOTAL_BOXES_COUNT, position);
}

void NuzlockeDeleteFaintedPartyPokemon(void) // @Kurausukun
{
    u8 i;
    struct Pokemon *pokemon;
    u32 monItem;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        pokemon = &gPlayerParty[i];
        if (GetMonData(pokemon, MON_DATA_SANITY_HAS_SPECIES, NULL) && !GetMonData(pokemon, MON_DATA_IS_EGG, NULL))
        {
            if (GetMonAilment(pokemon) == AILMENT_FNT)
            {
                monItem = GetMonData(pokemon, MON_DATA_HELD_ITEM, NULL);

                if (monItem != ITEM_NONE)
                {
                    AddBagItem(monItem, 1);
                    SetMonData(pokemon, MON_DATA_HELD_ITEM, ITEM_NONE);
                }
                if ((gSaveBlock1Ptr->tx_Features_PkmnDeath) && (!IsNuzlockeActive()))
                    NuzlockeDeletePartyMonOption(i);
                else
                    NuzlockeDeletePartyMon(i);
            }
        }
    }
    CompactPartySlots();
}

// Difficulty
u8 GetMaxPartySize(void)
{
    return (6 - gSaveBlock1Ptr->tx_Challenges_PartyLimit);
}

u8 GetCurrentBadgeCount(void)
{
    u16 i, badgeCount = 0;
    for (i = FLAG_BADGE01_GET; i < FLAG_BADGE01_GET + NUM_BADGES; i++) //count badges
    {
        if (FlagGet(i))
            badgeCount++;
    }
    return badgeCount;
}

enum LevelCap {
    LEVEL_CAP_NO_BADGES,
    LEVEL_CAP_BADGE_1,
    LEVEL_CAP_BADGE_2,
    LEVEL_CAP_BADGE_3,
    LEVEL_CAP_BADGE_4,
    LEVEL_CAP_BADGE_5,
    LEVEL_CAP_BADGE_6,
    LEVEL_CAP_BADGE_7,
    LEVEL_CAP_BADGE_8
};
static const u8 sLevelCapTable_Normal[] = //HNS UPDATED
{
    [LEVEL_CAP_NO_BADGES]   = 10, 
    [LEVEL_CAP_BADGE_1]     = 16, 
    [LEVEL_CAP_BADGE_2]     = 21,
    [LEVEL_CAP_BADGE_3]     = 25,
    [LEVEL_CAP_BADGE_4]     = 31,
    [LEVEL_CAP_BADGE_5]     = 36,
    [LEVEL_CAP_BADGE_6]     = 38,
    [LEVEL_CAP_BADGE_7]     = 45,
    [LEVEL_CAP_BADGE_8]     = 56,
};
static const u8 sLevelCapTable_Hard[] = //HNS UPDATED
{
    [LEVEL_CAP_NO_BADGES]   = 8,
    [LEVEL_CAP_BADGE_1]     = 15,
    [LEVEL_CAP_BADGE_2]     = 20,
    [LEVEL_CAP_BADGE_3]     = 23,
    [LEVEL_CAP_BADGE_4]     = 29,
    [LEVEL_CAP_BADGE_5]     = 33,
    [LEVEL_CAP_BADGE_6]     = 37,
    [LEVEL_CAP_BADGE_7]     = 42,
    [LEVEL_CAP_BADGE_8]     = 54,
};

static const u8 sLevelCapTable_Normal_Caps_And_Hard_Mode[] =//UNCHANGED FROM M.E. 
{
    [LEVEL_CAP_NO_BADGES]   = 16, //+1
    [LEVEL_CAP_BADGE_1]     = 21, //+2
    [LEVEL_CAP_BADGE_2]     = 26, //+2
    [LEVEL_CAP_BADGE_3]     = 32, //+3
    [LEVEL_CAP_BADGE_4]     = 34, //+3
    [LEVEL_CAP_BADGE_5]     = 36, //+3
    [LEVEL_CAP_BADGE_6]     = 48, //+6
    [LEVEL_CAP_BADGE_7]     = 52, //+6
    [LEVEL_CAP_BADGE_8]     = 64, //+6
};

static const u8 sLevelCapTable_Hard_Caps_And_Hard_Mode[] = //UNCHANGED FROM M.E. 
{
    [LEVEL_CAP_NO_BADGES]   = 13, //+1
    [LEVEL_CAP_BADGE_1]     = 18, //+2
    [LEVEL_CAP_BADGE_2]     = 22, //+2
    [LEVEL_CAP_BADGE_3]     = 27, //+3
    [LEVEL_CAP_BADGE_4]     = 30, //+3
    [LEVEL_CAP_BADGE_5]     = 32, //+3
    [LEVEL_CAP_BADGE_6]     = 47, //+6
    [LEVEL_CAP_BADGE_7]     = 47, //+6
    [LEVEL_CAP_BADGE_8]     = 61, //+6
};
#define TX_CHALLENGE_LEVEL_CAP_DEBUG 0
#define KANTO_MAX_LEVEL 70

u8 GetCurrentPartyLevelCap(void)
{
    u8 badgeCount = GetCurrentBadgeCount();

    // Safety clamp in case badgeCount ever drifts out of range
    if (badgeCount > LEVEL_CAP_BADGE_8)
        badgeCount = LEVEL_CAP_BADGE_8;

    // Debug override
    if (TX_CHALLENGE_LEVEL_CAP_DEBUG != 0)
        return TX_CHALLENGE_LEVEL_CAP_DEBUG;

    switch (gSaveBlock1Ptr->tx_Challenges_LevelCap)
    {
    case 0: // Level caps OFF
        return MAX_LEVEL;

    case 1: // Normal HnS caps
    case 2: // Hard   HnS caps
        // Post-E4 overrides when caps are ON
        if (FlagGet(FLAG_IS_KANTO_CHAMPION))
            return MAX_LEVEL;        // after Kanto E4, no cap
        if (FlagGet(FLAG_IS_CHAMPION))
            return KANTO_MAX_LEVEL;  // after first E4, cap = 70

        if (gSaveBlock1Ptr->tx_Challenges_LevelCap == 1)
            return sLevelCapTable_Normal[badgeCount];
        else
            return sLevelCapTable_Hard[badgeCount];

    default:
        // Fallback: treat unknown setting as "no cap"
        return MAX_LEVEL;
    }
}


// Scaling IVs and EVs
static const u8 sIV_Table[] = 
{
    [LEVEL_CAP_NO_BADGES]   = 7,
    [LEVEL_CAP_BADGE_1]     = 10,
    [LEVEL_CAP_BADGE_2]     = 13,
    [LEVEL_CAP_BADGE_3]     = 16,
    [LEVEL_CAP_BADGE_4]     = 19,
    [LEVEL_CAP_BADGE_5]     = 22,
    [LEVEL_CAP_BADGE_6]     = 25,
    [LEVEL_CAP_BADGE_7]     = 28,
    [LEVEL_CAP_BADGE_8]     = 31,
};
static const u8 sEV_Table[] = 
{
    [LEVEL_CAP_NO_BADGES]   = 12,
    [LEVEL_CAP_BADGE_1]     = 24,
    [LEVEL_CAP_BADGE_2]     = 36,
    [LEVEL_CAP_BADGE_3]     = 48,
    [LEVEL_CAP_BADGE_4]     = 60,
    [LEVEL_CAP_BADGE_5]     = 72,
    [LEVEL_CAP_BADGE_6]     = 80,
    [LEVEL_CAP_BADGE_7]     = 100,
    [LEVEL_CAP_BADGE_8]     = 128,
};
u8 GetCurrentTrainerIVs(void)
{
    u8 badgeCount = GetCurrentBadgeCount();

    switch (gSaveBlock1Ptr->tx_Challenges_TrainerScalingIVs)
    {
    case 1:     return sIV_Table[badgeCount];
    default:    return MAX_PER_STAT_IVS;
    }
}
u8 GetCurrentTrainerEVs(void)
{
    u8 badgeCount = GetCurrentBadgeCount();

    switch (gSaveBlock1Ptr->tx_Challenges_TrainerScalingEVs)
    {
    case 1:     return sEV_Table[badgeCount];
    case 2:     return 128;
    case 3:     return 252;
    default:    return 0;
    }
}

// Challenges


// DEBUG
void PrintTXSaveData(void)
{
    #ifndef NDEBUG
    
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_WildPokemon"          , gSaveBlock1Ptr->tx_Random_WildPokemon);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_Trainer"              , gSaveBlock1Ptr->tx_Random_Trainer);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_Similar"              , gSaveBlock1Ptr->tx_Random_Similar);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_MapBased"             , gSaveBlock1Ptr->tx_Random_MapBased);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_IncludeLegendaries"   , gSaveBlock1Ptr->tx_Random_IncludeLegendaries);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_Type"                 , gSaveBlock1Ptr->tx_Random_Type);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_Moves"                , gSaveBlock1Ptr->tx_Random_Moves);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_Abilities"            , gSaveBlock1Ptr->tx_Random_Abilities);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_Evolutions"           , gSaveBlock1Ptr->tx_Random_Evolutions);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_EvolutionMethods"     , gSaveBlock1Ptr->tx_Random_EvolutionMethods);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_TypeEffectiveness"    , gSaveBlock1Ptr->tx_Random_TypeEffectiveness);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_Items"                , gSaveBlock1Ptr->tx_Random_Items);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Random_Chaos"                , gSaveBlock1Ptr->tx_Random_Chaos);

    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_Nuzlocke"         , gSaveBlock1Ptr->tx_Challenges_Nuzlocke);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_NuzlockeHardcore" , gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Nuzlocke_SpeciesClause"      , gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Nuzlocke_ShinyClause"        , gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Nuzlocke_Nicknaming"         , gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming);

    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_PartyLimit"       , gSaveBlock1Ptr->tx_Challenges_PartyLimit);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_LevelCap"         , gSaveBlock1Ptr->tx_Challenges_LevelCap);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_ExpMultiplier"    , gSaveBlock1Ptr->tx_Challenges_ExpMultiplier);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_NoItemPlayer"     , gSaveBlock1Ptr->tx_Challenges_NoItemPlayer);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_NoItemTrainer"    , gSaveBlock1Ptr->tx_Challenges_NoItemTrainer);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_PkmnCenter"       , gSaveBlock1Ptr->tx_Challenges_PkmnCenter);

    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_EvoLimit"         , gSaveBlock1Ptr->tx_Challenges_EvoLimit);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_OneTypeChallenge" , gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_BaseStatEqualizer", gSaveBlock1Ptr->tx_Challenges_BaseStatEqualizer);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_Mirror"           , gSaveBlock1Ptr->tx_Challenges_Mirror);
    MgbaPrintf(MGBA_LOG_DEBUG, "%d tx_Challenges_Mirror_Thief"     , gSaveBlock1Ptr->tx_Challenges_Mirror_Thief);
    #endif
}

void TestRandomizerValues(u8 type)
{
    #ifndef NDEBUG
    u16 i, j;
    u8 real_j;
    u16 tmp;
    u16 array[10];
    u8 save_values[30];

    //save saveblock values
    save_values[0]  = gSaveBlock1Ptr->tx_Random_Chaos;
    save_values[1]  = gSaveBlock1Ptr->tx_Random_WildPokemon;
    save_values[2]  = gSaveBlock1Ptr->tx_Random_Similar;
    save_values[3]  = gSaveBlock1Ptr->tx_Random_MapBased;
    save_values[4]  = gSaveBlock1Ptr->tx_Random_IncludeLegendaries;
    save_values[5]  = gSaveBlock1Ptr->tx_Random_Type;
    save_values[6]  = gSaveBlock1Ptr->tx_Random_TypeEffectiveness;
    save_values[7]  = gSaveBlock1Ptr->tx_Random_Abilities;
    save_values[8]  = gSaveBlock1Ptr->tx_Random_Moves;
    save_values[9]  = gSaveBlock1Ptr->tx_Random_Trainer;
    save_values[10] = gSaveBlock1Ptr->tx_Random_Evolutions;
    save_values[11] = gSaveBlock1Ptr->tx_Random_EvolutionMethods;
    save_values[12] = gSaveBlock1Ptr->tx_Challenges_EvoLimit;
    save_values[13] = gSaveBlock1Ptr->tx_Challenges_Nuzlocke;
    save_values[14] = gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore;
    save_values[15] = gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge;
    save_values[16] = gSaveBlock1Ptr->tx_Challenges_PartyLimit;
    save_values[17] = gSaveBlock1Ptr->tx_Challenges_NoItemPlayer;
    save_values[18] = gSaveBlock1Ptr->tx_Challenges_NoItemTrainer;
    save_values[19] = gSaveBlock1Ptr->tx_Challenges_PkmnCenter;
    save_values[20] = gSaveBlock1Ptr->tx_Challenges_LessEscapes;
    save_values[21] = gSaveBlock1Ptr->tx_Challenges_BaseStatEqualizer;
    save_values[22] = gSaveBlock1Ptr->tx_Challenges_LevelCap;
    save_values[23] = gSaveBlock1Ptr->tx_Random_Items;
    save_values[24] = gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause;
    save_values[25] = gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause;
    save_values[26] = gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming;

    gSaveBlock1Ptr->tx_Random_WildPokemon           = TRUE;
    gSaveBlock1Ptr->tx_Random_Similar               = FALSE;
    gSaveBlock1Ptr->tx_Random_MapBased              = FALSE;
    gSaveBlock1Ptr->tx_Random_IncludeLegendaries    = FALSE;


    for (i=0; i<10; i++)
    {
        for (j=0; j<NUM_SPECIES; j++)
        {
        //tmp = RandomSeededModulo(j, NUM_SPECIES);
        tmp = GetSpeciesRandomSeeded(j, type, 0);
        
        real_j = j % 10;
        array[real_j] = tmp;
        if (real_j == 9)
            MgbaPrintf(MGBA_LOG_DEBUG, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", array[0],array[1],array[2],array[3],array[4],array[5],array[6],array[7],array[8],array[9]);
        }
    }




    //restore saveblock values
    gSaveBlock1Ptr->tx_Random_Chaos                 =   save_values[0];
    gSaveBlock1Ptr->tx_Random_WildPokemon           =   save_values[1];
    gSaveBlock1Ptr->tx_Random_Similar               =   save_values[2];
    gSaveBlock1Ptr->tx_Random_MapBased              =   save_values[3];
    gSaveBlock1Ptr->tx_Random_IncludeLegendaries    =   save_values[4];
    gSaveBlock1Ptr->tx_Random_Type                  =   save_values[5];
    gSaveBlock1Ptr->tx_Random_TypeEffectiveness     =   save_values[6];
    gSaveBlock1Ptr->tx_Random_Abilities             =   save_values[7];
    gSaveBlock1Ptr->tx_Random_Moves                 =   save_values[8];
    gSaveBlock1Ptr->tx_Random_Trainer               =   save_values[9];
    gSaveBlock1Ptr->tx_Random_Evolutions            =   save_values[10];
    gSaveBlock1Ptr->tx_Random_EvolutionMethods      =   save_values[11];
    gSaveBlock1Ptr->tx_Challenges_EvoLimit          =   save_values[12];
    gSaveBlock1Ptr->tx_Challenges_Nuzlocke          =   save_values[13];
    gSaveBlock1Ptr->tx_Challenges_NuzlockeHardcore  =   save_values[14];
    gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge  =   save_values[15];
    gSaveBlock1Ptr->tx_Challenges_PartyLimit        =   save_values[16];
    gSaveBlock1Ptr->tx_Challenges_NoItemPlayer      =   save_values[17];
    gSaveBlock1Ptr->tx_Challenges_NoItemTrainer     =   save_values[18];
    gSaveBlock1Ptr->tx_Challenges_PkmnCenter        =   save_values[19];
    gSaveBlock1Ptr->tx_Challenges_LessEscapes       =   save_values[20];
    gSaveBlock1Ptr->tx_Challenges_BaseStatEqualizer =   save_values[21];
    gSaveBlock1Ptr->tx_Challenges_LevelCap          =   save_values[22];
    gSaveBlock1Ptr->tx_Random_Items                 =   save_values[23];
    gSaveBlock1Ptr->tx_Nuzlocke_SpeciesClause       =   save_values[24];
    gSaveBlock1Ptr->tx_Nuzlocke_ShinyClause         =   save_values[25];
    gSaveBlock1Ptr->tx_Nuzlocke_Nicknaming          =   save_values[26];
    #endif
}
