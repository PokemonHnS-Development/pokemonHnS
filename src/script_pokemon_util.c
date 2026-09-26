#include "global.h"
#include "battle.h"
#include "battle_gfx_sfx_util.h"
#include "battle_setup.h" //tx_randomizer_and_challenges
#include "berry.h"
#include "data.h"
#include "daycare.h"
#include "decompress.h"
#include "event_data.h"
#include "international_string_util.h"
#include "item.h" //tx_randomizer_and_challenges
#include "link.h"
#include "link_rfu.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "script.h"
#include "sprite.h"
#include "string_util.h"
#include "tv.h"
#include "constants/items.h"
#include "constants/battle_frontier.h"
#include "tx_randomizer_and_challenges.h"
#include "script_pokemon_util.h"
#include "starter_choose.h"

static void CB2_ReturnFromChooseHalfParty(void);
static void CB2_ReturnFromChooseBattleFrontierParty(void);

void HealPlayerParty(void)
{
    u8 i, j;
    u8 ppBonuses;
    u8 arg[4];

    // restore HP.
    for(i = 0; i < gPlayerPartyCount; i++)
    {
        u16 maxHP = GetMonData(&gPlayerParty[i], MON_DATA_MAX_HP);
        arg[0] = maxHP;
        arg[1] = maxHP >> 8;
        SetMonData(&gPlayerParty[i], MON_DATA_HP, arg);
        ppBonuses = GetMonData(&gPlayerParty[i], MON_DATA_PP_BONUSES);

        // restore PP.
        for(j = 0; j < MAX_MON_MOVES; j++)
        {
            arg[0] = CalculatePPWithBonus(GetMonData(&gPlayerParty[i], MON_DATA_MOVE1 + j), ppBonuses, j);
            SetMonData(&gPlayerParty[i], MON_DATA_PP1 + j, arg);
        }

        // since status is u32, the four 0 assignments here are probably for safety to prevent undefined data from reaching SetMonData.
        arg[0] = 0;
        arg[1] = 0;
        arg[2] = 0;
        arg[3] = 0;
        SetMonData(&gPlayerParty[i], MON_DATA_STATUS, arg);
    }
}

u8 ScriptGiveMon(u16 species, u8 level, u16 item, u32 unused1, u32 unused2, u8 unused3)
{
    u16 nationalDexNum;
    int sentToPc;
    u8 heldItem[2];
    struct Pokemon mon;

    // Starter flags are numbers because Random starters also work!
    // The flag FORCE_SHINY is immediately cleared so it can't affect the rest of the game.
    // Starter flags are not used anymore after that, and it's immediately cleared as well.
    if (FlagGet(FLAG_SHINY_STARTER_1)) //Torchic
        {
            FlagSet(FLAG_FORCE_SHINY);
            CreateMon(&mon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
            FlagClear(FLAG_FORCE_SHINY);
            FlagClear(FLAG_SHINY_STARTER_1);
        }
    else if (FlagGet(FLAG_SHINY_STARTER_2)) //Treecko
        {
            FlagSet(FLAG_FORCE_SHINY);
            CreateMon(&mon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
            FlagClear(FLAG_FORCE_SHINY);
            FlagClear(FLAG_SHINY_STARTER_2);
        }
    else if (FlagGet(FLAG_SHINY_STARTER_3)) //Mudkip
        {
            FlagSet(FLAG_FORCE_SHINY);
            CreateMon(&mon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
            FlagClear(FLAG_FORCE_SHINY);
            FlagClear(FLAG_SHINY_STARTER_3);
        }
    else if ((!FlagGet(FLAG_SHINY_STARTER_3) || !FlagGet(FLAG_SHINY_STARTER_2) || !FlagGet(FLAG_SHINY_STARTER_1)) 
            && !FlagGet(FLAG_HIDE_SILVER_NEWBARKTOWN))
    // This is here because even if the starter doesn't pass the previous checks (so, it's not shiny) there's the 1/8192 (or 1/4096, 1/2048, 1/1024, 1/512, depending on 
    // the player's choice) chance that it could become shiny anyway, as the preview is not connected to the personality that the game creates.
    // To prevent it, if the SHINY_STARTER_X flag hasn't been set, and "Silver is still looking at Elm's lab" flag hasn't been also set, it just blocks the starter from becoming
    // shiny. The flag NO_SHINY is immediately cleared to prevent other POKéMON from becoming not shiny.
    {
        FlagSet(FLAG_NO_SHINY);
        CreateMon(&mon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
        FlagClear(FLAG_NO_SHINY);
    }

    // Special case added to HnS, as it doesn't handle starters the same way as Emerald does (via Birch's bag)
    // The flag used is the one that enables the "POKéMON" option in the menu system
    // So, this is only run once: when you haven't got the "POKéMON" option yet, and when RANDOM STARTER and ONE TYPE CHALLENGE are enabled.
    // That's why it's set after obtaining the starter. Afterwards, it never works again as the flag never gets disabled, as it should.
    // All the shiny code above doesn't affect HnS, but it's set anyway in case someone uses the code
    if (((gSaveBlock1Ptr->tx_Random_Starter) == 1) && (FlagGet(FLAG_SYS_POKEMON_GET) == FALSE) ||
        IsOneTypeChallengeActive() && (FlagGet(FLAG_SYS_POKEMON_GET) == FALSE))
    {
        species = GetStarterPokemon(VarGet(VAR_STARTER_MON));
        //Fixes Missigno appearing in Monotype Dragon runs, as the game lacks Dragon species
        if (IsOneTypeChallengeActive() && (gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge == TYPE_DRAGON) && (species == 0))
            CreateMon(&mon, SPECIES_DRATINI, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
        //Fixes the infamous and popular cult classic horror story "The Topepi of Terror" when selecting a starter.
        //Bug might happen if you still catch a Togepi in the wild before getting the expected Togepi egg in Violet City.
        //First, if in Normal or Fairy type Monotype run and you see a Togepi, it gets re-rolled into CLEFFA. 
        //Doesn't take into account randomizer because it's not relevant here.
        else if (IsOneTypeChallengeActive() 
        && ((gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge == TYPE_NORMAL) || (gSaveBlock1Ptr->tx_Challenges_OneTypeChallenge == TYPE_FAIRY)  
        && (species == SPECIES_TOGEPI)))
            CreateMon(&mon, SPECIES_CLEFFA, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
        //If not playing a Normal or Fairy type Monorun, but you're using Random Starters and a Togepi is set as a starter, re-roll into CLEFFA.
        else if ((gSaveBlock1Ptr->tx_Random_Starter == TRUE) && (species == SPECIES_TOGEPI))
            CreateMon(&mon, SPECIES_CLEFFA, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
        else
            CreateMon(&mon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    }
     //If the static randomizer is on, and you got your first Pokémon already, givemons will be randomized
    else if ((gSaveBlock1Ptr->tx_Random_Static) && (FlagGet(FLAG_SYS_POKEMON_GET) == TRUE))
    {
        species = GetSpeciesRandomSeeded(species, TX_RANDOM_T_STATIC, 0);
        CreateMon(&mon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    }
    else
        CreateMon(&mon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    heldItem[0] = item;
    heldItem[1] = item >> 8;
    SetMonData(&mon, MON_DATA_HELD_ITEM, heldItem);
    sentToPc = GiveMonToPlayer(&mon);
    nationalDexNum = SpeciesToNationalPokedexNum(species);

    // Don't set Pokédex flag for MON_CANT_GIVE
    switch(sentToPc)
    {
    case MON_GIVEN_TO_PARTY:
    case MON_GIVEN_TO_PC:
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
        break;
    }
    return sentToPc;
}

u8 ScriptGiveEgg(u16 species)
{
    struct Pokemon mon;
    u8 isEgg;

    CreateEgg(&mon, species, TRUE);
    isEgg = TRUE;
    SetMonData(&mon, MON_DATA_IS_EGG, &isEgg);

    return GiveMonToPlayer(&mon);
}

void HasEnoughMonsForDoubleBattle(void)
{
    switch (GetMonsStateToDoubles())
    {
    case PLAYER_HAS_TWO_USABLE_MONS:
        gSpecialVar_Result = PLAYER_HAS_TWO_USABLE_MONS;
        break;
    case PLAYER_HAS_ONE_MON:
        gSpecialVar_Result = PLAYER_HAS_ONE_MON;
        break;
    case PLAYER_HAS_ONE_USABLE_MON:
        gSpecialVar_Result = PLAYER_HAS_ONE_USABLE_MON;
        break;
    }
}

static bool8 CheckPartyMonHasHeldItem(u16 item)
{
    int i;

    for(i = 0; i < PARTY_SIZE; i++)
    {
        u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG);
        if (species != SPECIES_NONE && species != SPECIES_EGG && GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM) == item)
            return TRUE;
    }
    return FALSE;
}

bool8 DoesPartyHaveEnigmaBerry(void)
{
    bool8 hasItem = CheckPartyMonHasHeldItem(ITEM_ENIGMA_BERRY);
    if (hasItem == TRUE)
        GetBerryNameByBerryType(ItemIdToBerryType(ITEM_ENIGMA_BERRY), gStringVar1);

    return hasItem;
}

void CreateScriptedWildMon(u16 species, u8 level, u16 item)
{
    u8 heldItem[2];
    //tx_randomizer_and_challenges
    if (gSaveBlock1Ptr->tx_Random_Static)
        species = GetSpeciesRandomSeeded(species, TX_RANDOM_T_STATIC, 0);
    if (gSaveBlock1Ptr->tx_Random_Items)
        item = RandomItemId(item);

    ZeroEnemyPartyMons();
    CreateMon(&gEnemyParty[0], species, level, USE_RANDOM_IVS, 0, 0, OT_ID_PLAYER_ID, 0);
    if (item)
    {
        heldItem[0] = item;
        heldItem[1] = item >> 8;
        SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, heldItem);
    }
    SetNuzlockeChecks(); //tx_randomizer_and_challenges
}

//HnS
u32 GenerateShinyPersonalityForOtId(u32 otId)
{
    u32 personality;
    do {
        personality = Random32(); // or a deterministic value if you want
    } while ((HIHALF(otId) ^ LOHALF(otId) ^ HIHALF(personality) ^ LOHALF(personality)) >= 8);
    return personality;
}


void CreateShinyScriptedMon(u16 species, u8 level, u16 item)
{
    u8 heldItem[2];
    if (gSaveBlock1Ptr->tx_Random_Static)
        species = GetSpeciesRandomSeeded(species, TX_RANDOM_T_STATIC, 0);
    if (gSaveBlock1Ptr->tx_Random_Items)
        item = RandomItemId(item);
    ZeroEnemyPartyMons();

    u32 otId = gSaveBlock2Ptr->playerTrainerId[0]
             | (gSaveBlock2Ptr->playerTrainerId[1] << 8)
             | (gSaveBlock2Ptr->playerTrainerId[2] << 16)
             | (gSaveBlock2Ptr->playerTrainerId[3] << 24);

    u32 shinyPersonality = GenerateShinyPersonalityForOtId(otId);

    CreateMon(&gEnemyParty[0], species, level, USE_RANDOM_IVS, TRUE, shinyPersonality, OT_ID_PLAYER_ID, 0);

    if (item) {
        heldItem[0] = item;
        heldItem[1] = item >> 8;
        SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, heldItem);
    }
    SetNuzlockeChecks();
}

void ScriptSetMonMoveSlot(u8 monIndex, u16 move, u8 slot)
{
// Allows monIndex to go out of bounds of gPlayerParty. Doesn't occur in vanilla
#ifdef BUGFIX
    if (monIndex >= PARTY_SIZE)
#else
    if (monIndex > PARTY_SIZE)
#endif
        monIndex = gPlayerPartyCount - 1;

    SetMonMoveSlot(&gPlayerParty[monIndex], move, slot);
}

// Note: When control returns to the event script, gSpecialVar_Result will be
// TRUE if the party selection was successful.
void ChooseHalfPartyForBattle(void)
{
    gMain.savedCallback = CB2_ReturnFromChooseHalfParty;
    VarSet(VAR_FRONTIER_FACILITY, FACILITY_MULTI_OR_EREADER);
    InitChooseHalfPartyForBattle(0);
}

static void CB2_ReturnFromChooseHalfParty(void)
{
    switch (gSelectedOrderFromParty[0])
    {
    case 0:
        gSpecialVar_Result = FALSE;
        break;
    default:
        gSpecialVar_Result = TRUE;
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ChoosePartyForBattleFrontier(void)
{
    gMain.savedCallback = CB2_ReturnFromChooseBattleFrontierParty;
    InitChooseHalfPartyForBattle(gSpecialVar_0x8004 + 1);
}

static void CB2_ReturnFromChooseBattleFrontierParty(void)
{
    switch (gSelectedOrderFromParty[0])
    {
    case 0:
        gSpecialVar_Result = FALSE;
        break;
    default:
        gSpecialVar_Result = TRUE;
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ReducePlayerPartyToSelectedMons(void)
{
    struct Pokemon party[MAX_FRONTIER_PARTY_SIZE];
    int i;

    CpuFill32(0, party, sizeof party);

    // copy the selected Pokémon according to the order.
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
        if (gSelectedOrderFromParty[i]) // as long as the order keeps going (did the player select 1 mon? 2? 3?), do not stop
            party[i] = gPlayerParty[gSelectedOrderFromParty[i] - 1]; // index is 0 based, not literal

    CpuFill32(0, gPlayerParty, sizeof gPlayerParty);

    // overwrite the first 4 with the order copied to.
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
        gPlayerParty[i] = party[i];

    CalculatePlayerPartyCount();
}
