#include "global.h"
#include "pokemon.h"
#include "strings.h"
#include "random.h"
#include "text.h"
#include "event_data.h"
#include "region_map.h"
#include "constants/species.h"
#include "constants/items.h"
#include "constants/abilities.h"
#include "data/text/wonder_trade_OT_names.h"
#include "constants/region_map_sections.h"
#include "item.h"
#include "rtc.h"
#include "overworld.h"
#include "constants/item.h"
#include "constants/hold_effects.h"
#include "mail.h"
#include "constants/pokemon.h"
#include "party_menu.h"
#include "field_weather.h"
#include "constants/weather.h"
#include "battle.h" // A workaround to include the expansion's constants/form_change_types.h without breaking Pret/Pokeemerald compatibility.
#include "string_util.h"
#include "daycare.h"
#include "wonder_trade.h"

extern struct Evolution gEvolutionTable[][EVOS_PER_MON];

// This file's functions.
static u16 PickRandomSpecies(void);
static u8 GetWonderTradeOT(u8 *name);
static u16 GetWonderTradeEvolutionTargetSpecies(struct Pokemon *mon);
static u32 GetEvolutionSpecies(u16 speciesId);
static bool32 IsSpeciesFamilyMegaEvolutionCompatible(u16 species, u16 heldStone);
static u16 GetValidHeldItemForSpecies(u16 speciesId);

struct WonderTrade {
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u16 species;
    u8 ivs[NUM_STATS];
    u8 abilityNum;
    u32 otId;
    u8 conditions[CONTEST_CATEGORIES_COUNT];
    u32 personality;
    u16 heldItem;
    u8 mailNum;
    u8 otName[TRAINER_NAME_LENGTH + 1];
    u8 otGender;
    u8 sheen;
    u16 requestedSpecies;
};

#ifndef RHH_EXPANSION
// This is a list of items that are not used in vanilla.
// Feel free to delete it and remove the check that uses it,
// if you use the pokeemerald-expansion.
static const u16 sIsInvalidItem[] = {
    [ITEM_03D]            = TRUE,
    [ITEM_03E]            = TRUE,
    [ITEM_048]            = TRUE,
    [ITEM_057]            = TRUE,
    [ITEM_058]            = TRUE,
    [ITEM_059]            = TRUE,
    [ITEM_05A]            = TRUE,
    [ITEM_05B]            = TRUE,
    [ITEM_05C]            = TRUE,
    [ITEM_063]            = TRUE,
    [ITEM_064]            = TRUE,
    [ITEM_065]            = TRUE,
    [ITEM_066]            = TRUE,
    [ITEM_069]            = TRUE,
    [ITEM_072]            = TRUE,
    [ITEM_073]            = TRUE,
    [ITEM_074]            = TRUE,
    [ITEM_075]            = TRUE,
    [ITEM_076]            = TRUE,
    [ITEM_077]            = TRUE,
    [ITEM_UNUSED_BERRY_1] = TRUE,
    [ITEM_UNUSED_BERRY_2] = TRUE,
    [ITEM_UNUSED_BERRY_3] = TRUE,
    [ITEM_0F0]            = TRUE,
    [ITEM_0F0]            = TRUE,
    [ITEM_0F1]            = TRUE,
    [ITEM_0F2]            = TRUE,
    [ITEM_0F3]            = TRUE,
    [ITEM_0F4]            = TRUE,
    [ITEM_0F5]            = TRUE,
    [ITEM_0F6]            = TRUE,
    [ITEM_0F7]            = TRUE,
    [ITEM_0F8]            = TRUE,
    [ITEM_0F9]            = TRUE,
    [ITEM_0FA]            = TRUE,
    [ITEM_0FB]            = TRUE,
    [ITEM_0FC]            = TRUE,
    [ITEM_0FD]            = TRUE,
    [ITEM_10B]            = TRUE,
    [ITEM_15B]            = TRUE,
    [ITEM_15C]            = TRUE,
};
#endif

static const u16 sIsValidSpecies[] =
{
    SPECIES_BULBASAUR,
    SPECIES_CHARMANDER,
    SPECIES_SQUIRTLE,
    SPECIES_CATERPIE,
    SPECIES_WEEDLE,
    SPECIES_PIDGEY,
    SPECIES_RATTATA,
    SPECIES_SPEAROW,
    SPECIES_EKANS,
    SPECIES_SANDSHREW,
    SPECIES_NIDORAN_F,
    SPECIES_NIDORAN_M,
    SPECIES_VULPIX,
    SPECIES_ZUBAT,
    SPECIES_ODDISH,
    SPECIES_PARAS,
    SPECIES_VENONAT,
    SPECIES_DIGLETT,
    SPECIES_MEOWTH,
    SPECIES_PSYDUCK,
    SPECIES_MANKEY,
    SPECIES_GROWLITHE,
    SPECIES_POLIWAG,
    SPECIES_ABRA,
    SPECIES_MACHOP,
    SPECIES_BELLSPROUT,
    SPECIES_TENTACOOL,
    SPECIES_GEODUDE,
    SPECIES_PONYTA,
    SPECIES_SLOWPOKE,
    SPECIES_MAGNEMITE,
    SPECIES_FARFETCHD,
    SPECIES_DODUO,
    SPECIES_SEEL,
    SPECIES_GRIMER,
    SPECIES_SHELLDER,
    SPECIES_GASTLY,
    SPECIES_ONIX,
    SPECIES_DROWZEE,
    SPECIES_KRABBY,
    SPECIES_VOLTORB,
    SPECIES_EXEGGCUTE,
    SPECIES_CUBONE,
    SPECIES_LICKITUNG,
    SPECIES_KOFFING,
    SPECIES_RHYHORN,
    SPECIES_TANGELA,
    SPECIES_KANGASKHAN,
    SPECIES_HORSEA,
    SPECIES_GOLDEEN,
    SPECIES_STARYU,
    SPECIES_SCYTHER,
    SPECIES_PINSIR,
    SPECIES_TAUROS,
    SPECIES_MAGIKARP,
    SPECIES_LAPRAS,
    SPECIES_DITTO,
    SPECIES_EEVEE,
    SPECIES_PORYGON,
    SPECIES_OMANYTE,
    SPECIES_KABUTO,
    SPECIES_DRATINI,
    SPECIES_CHIKORITA,
    SPECIES_CYNDAQUIL,
    SPECIES_TOTODILE,
    SPECIES_SENTRET,
    SPECIES_HOOTHOOT,
    SPECIES_LEDYBA,
    SPECIES_SPINARAK,
    SPECIES_CHINCHOU,
    SPECIES_PICHU,
    SPECIES_CLEFFA,
    SPECIES_IGGLYBUFF,
    SPECIES_TOGEPI,
    SPECIES_NATU,
    SPECIES_MAREEP,
    SPECIES_HOPPIP,
    SPECIES_AIPOM,
    SPECIES_SUNKERN,
    SPECIES_YANMA,
    SPECIES_WOOPER,
    SPECIES_MURKROW,
    SPECIES_MISDREAVUS,
    SPECIES_GIRAFARIG,
    SPECIES_PINECO,
    SPECIES_DUNSPARCE,
    SPECIES_GLIGAR,
    SPECIES_SNUBBULL,
    SPECIES_QWILFISH,
    SPECIES_SHUCKLE,
    SPECIES_HERACROSS,
    SPECIES_SNEASEL,
    SPECIES_TEDDIURSA,
    SPECIES_SLUGMA,
    SPECIES_SWINUB,
    SPECIES_CORSOLA,
    SPECIES_REMORAID,
    SPECIES_DELIBIRD,
    SPECIES_SKARMORY,
    SPECIES_HOUNDOUR,
    SPECIES_PHANPY,
    SPECIES_STANTLER,
    SPECIES_SMEARGLE,
    SPECIES_TYROGUE,
    SPECIES_SMOOCHUM,
    SPECIES_ELEKID,
    SPECIES_MAGBY,
    SPECIES_MILTANK,
    SPECIES_LARVITAR,
    SPECIES_TREECKO,
    SPECIES_TORCHIC,
    SPECIES_MUDKIP,
    SPECIES_POOCHYENA,
    SPECIES_ZIGZAGOON,
    SPECIES_WURMPLE,
    SPECIES_LOTAD,
    SPECIES_SEEDOT,
    SPECIES_NINCADA,
    SPECIES_TAILLOW,
    SPECIES_SHROOMISH,
    SPECIES_SPINDA,
    SPECIES_WINGULL,
    SPECIES_SURSKIT,
    SPECIES_WAILMER,
    SPECIES_SKITTY,
    SPECIES_KECLEON,
    SPECIES_BALTOY,
    SPECIES_NOSEPASS,
    SPECIES_TORKOAL,
    SPECIES_SABLEYE,
    SPECIES_BARBOACH,
    SPECIES_LUVDISC,
    SPECIES_CORPHISH,
    SPECIES_FEEBAS,
    SPECIES_CARVANHA,
    SPECIES_TRAPINCH,
    SPECIES_MAKUHITA,
    SPECIES_ELECTRIKE,
    SPECIES_NUMEL,
    SPECIES_SPHEAL,
    SPECIES_CACNEA,
    SPECIES_SNORUNT,
    SPECIES_LUNATONE,
    SPECIES_SOLROCK,
    SPECIES_AZURILL,
    SPECIES_SPOINK,
    SPECIES_PLUSLE,
    SPECIES_MINUN,
    SPECIES_MAWILE,
    SPECIES_MEDITITE,
    SPECIES_SWABLU,
    SPECIES_WYNAUT,
    SPECIES_DUSKULL,
    SPECIES_SLAKOTH,
    SPECIES_GULPIN,
    SPECIES_TROPIUS,
    SPECIES_WHISMUR,
    SPECIES_CLAMPERL,
    SPECIES_ABSOL,
    SPECIES_SHUPPET,
    SPECIES_SEVIPER,
    SPECIES_ZANGOOSE,
    SPECIES_ARON,
    SPECIES_CASTFORM,
    SPECIES_VOLBEAT,
    SPECIES_ILLUMISE,
    SPECIES_LILEEP,
    SPECIES_ANORITH,
    SPECIES_RALTS,
    SPECIES_BAGON,
    SPECIES_BELDUM,
    SPECIES_BONSLY,
    SPECIES_BUDEW,
    SPECIES_CHINGLING,
    SPECIES_HAPPINY,
    SPECIES_MANTYKE,
    SPECIES_MIME_JR,
    SPECIES_MUNCHLAX,
};

static const u16 sIsValidSpeciesVanilla[] =
{
    SPECIES_SANDSHREW,
    SPECIES_VULPIX,
    SPECIES_ZUBAT,
    SPECIES_ODDISH,
    SPECIES_PSYDUCK,
    SPECIES_ABRA,
    SPECIES_MACHOP,
    SPECIES_TENTACOOL,
    SPECIES_GEODUDE,
    SPECIES_MAGNEMITE,
    SPECIES_DODUO,
    SPECIES_GRIMER,
    SPECIES_VOLTORB,
    SPECIES_KOFFING,
    SPECIES_RHYHORN,
    SPECIES_HORSEA,
    SPECIES_GOLDEEN,
    SPECIES_STARYU,
    SPECIES_MAGIKARP,
    SPECIES_CHINCHOU,
    SPECIES_PICHU,
    SPECIES_IGGLYBUFF,
    SPECIES_NATU,
    SPECIES_GIRAFARIG,
    SPECIES_HERACROSS,
    SPECIES_SLUGMA,
    SPECIES_CORSOLA,
    SPECIES_SKARMORY,
    SPECIES_PHANPY,
    SPECIES_TREECKO,
    SPECIES_TORCHIC,
    SPECIES_MUDKIP,
    SPECIES_POOCHYENA,
    SPECIES_ZIGZAGOON,
    SPECIES_WURMPLE,
    SPECIES_LOTAD,
    SPECIES_SEEDOT,
    SPECIES_NINCADA,
    SPECIES_TAILLOW,
    SPECIES_SHROOMISH,
    SPECIES_SPINDA,
    SPECIES_WINGULL,
    SPECIES_SURSKIT,
    SPECIES_WAILMER,
    SPECIES_SKITTY,
    SPECIES_KECLEON,
    SPECIES_BALTOY,
    SPECIES_NOSEPASS,
    SPECIES_TORKOAL,
    SPECIES_SABLEYE,
    SPECIES_BARBOACH,
    SPECIES_LUVDISC,
    SPECIES_CORPHISH,
    SPECIES_FEEBAS,
    SPECIES_CARVANHA,
    SPECIES_TRAPINCH,
    SPECIES_MAKUHITA,
    SPECIES_ELECTRIKE,
    SPECIES_NUMEL,
    SPECIES_SPHEAL,
    SPECIES_CACNEA,
    SPECIES_SNORUNT,
    SPECIES_LUNATONE,
    SPECIES_SOLROCK,
    SPECIES_AZURILL,
    SPECIES_SPOINK,
    SPECIES_PLUSLE,
    SPECIES_MINUN,
    SPECIES_MAWILE,
    SPECIES_MEDITITE,
    SPECIES_SWABLU,
    SPECIES_WYNAUT,
    SPECIES_DUSKULL,
    SPECIES_SLAKOTH,
    SPECIES_GULPIN,
    SPECIES_TROPIUS,
    SPECIES_WHISMUR,
    SPECIES_CLAMPERL,
    SPECIES_SHUPPET,
    SPECIES_SEVIPER,
    SPECIES_ZANGOOSE,
    SPECIES_ARON,
    SPECIES_CASTFORM,
    SPECIES_VOLBEAT,
    SPECIES_ILLUMISE,
    SPECIES_LILEEP,
    SPECIES_ANORITH,
    SPECIES_RALTS,
    SPECIES_BAGON,
    SPECIES_BELDUM,
    SPECIES_BUDEW,
    SPECIES_CHINGLING,
};

static u16 PickRandomSpecies() // picks only base forms
{
    u16 species = sIsValidSpecies[Random() % NELEMS(sIsValidSpecies)];
    u16 speciesVanilla = sIsValidSpeciesVanilla[Random() % NELEMS(sIsValidSpeciesVanilla)];
    if (gSaveBlock1Ptr->tx_Mode_AlternateSpawns == 1)
        return species;
    if ((gSaveBlock1Ptr->tx_Mode_AlternateSpawns == 0) && (FlagGet(FLAG_SYS_GAME_CLEAR) == TRUE))
        return species;
    else if (gSaveBlock1Ptr->tx_Mode_AlternateSpawns == 0)
        return speciesVanilla;
}

static u8 GetWonderTradeOT(u8 *name)
{
    u8 randGender = (Random() % 2); // 0 for male, 1 for female
    u8 numOTNames = 250;
    u8 selectedName = Random() %numOTNames;
    u8 i;
    if (randGender == MALE) // male OT selected
    {
        randGender = 0;
        for (i = 0; i < 8; ++i)
        {
            name[i] = maleWTNames[selectedName][i];
        }
        name[8] = EOS;
    }
    else                    // female OT selected
    {
        randGender = 0xFF;
        for (i = 0; i < 8; ++i)
        {
            name[i] = femaleWTNames[selectedName][i];
        }
        name[8] = EOS;
    }
    return randGender;
}

void CreateWonderTradePokemon(void)
{
    u16 wonderTradeSpecies = PickRandomSpecies();
    u8 playerMonLevel = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_LEVEL);
    u8 chanceToEvolve = Random() % 99;
    u16 newHeldItem = ITEM_NONE;
    u16 playerMonHeldItem = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_HELD_ITEM);
    u32 i;
#ifdef RHH_EXPANSION
    u8 abilityNum;
#endif
    u8 monName[POKEMON_NAME_LENGTH + 1];
    u8 otName[PLAYER_NAME_LENGTH + 1];
    u8 genderOT = GetWonderTradeOT(otName);
    u8 metLocation = METLOC_IN_GAME_TRADE;
    struct WonderTrade sWonderTrades[] =
    {
        [0] = {
            .nickname = _(""),
            .species = wonderTradeSpecies,
            .ivs = {(Random() % 32), (Random() % 32), (Random() % 32), (Random() % 32), (Random() % 32), (Random() % 32)},
            .abilityNum = (Random() % 2), // Can't use NUM_NORMAL_ABILITY_SLOTS because it's not present in Pret/Pokeemerald.
            .otId = 0, // Handled by CreateMon->CreateBoxMon.
            .conditions = {0, 0, 0, 0, 0},
            .personality = 0, // Handled by CreateMon->CreateBoxMon.
            .heldItem = newHeldItem,
            .mailNum = -1,
            .otName = _("ERROR"),
            .otGender = FEMALE, // Decided by the personality generated in CreateMon->CreateBoxMon.
            .sheen = 0,
            .requestedSpecies = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES)
        },
    };
    struct WonderTrade *wonderTrade = &sWonderTrades[0];

    // Creates the base of a Pokémon in the first slot of a nonexistent enemy's party.
    CreateMon(&gEnemyParty[0], wonderTradeSpecies, playerMonLevel, USE_RANDOM_IVS, FALSE, 0, OT_ID_PRESET, ((Random() << 16) | Random()));

    // 10% chance of having the generated Wonder Traded 'mon carry an item.
    if ((Random() % 99) < 10)
        newHeldItem = GetValidHeldItemForSpecies(wonderTradeSpecies);

    if (playerMonHeldItem == ITEM_NONE)
    {
        for (i = 0; i < EVOS_PER_MON; i++)
        {
            if (gEvolutionTable[wonderTradeSpecies][i].method == EVO_TRADE_ITEM && Random() % 100 < 50)
            {
                // 30% chance for the in coming Pokémon to hold the item they need to evolve if they need one
                if (Random() % 100 <= 29)
                {
                    newHeldItem = gEvolutionTable[wonderTradeSpecies][i].param;
                    SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, &newHeldItem);
                }
            }
        }
    }

    if (chanceToEvolve > 69) // 30% to evolve into the highest stage.
    {
        // 1st pass.
        wonderTradeSpecies = GetWonderTradeEvolutionTargetSpecies(&gEnemyParty[0]);
        SetMonData(&gEnemyParty[0], MON_DATA_SPECIES, &wonderTradeSpecies);
        // 2nd pass.
        wonderTradeSpecies = GetWonderTradeEvolutionTargetSpecies(&gEnemyParty[0]);
        SetMonData(&gEnemyParty[0], MON_DATA_SPECIES, &wonderTradeSpecies);
    }
    else if (chanceToEvolve >= 19 && chanceToEvolve <= 69) // 50% to evolve once.
    {
        wonderTradeSpecies = GetWonderTradeEvolutionTargetSpecies(&gEnemyParty[0]);
        SetMonData(&gEnemyParty[0], MON_DATA_SPECIES, &wonderTradeSpecies);
    }

#ifdef RHH_EXPANSION
    // 10% chance of giving the incoming Pokémon their HA, if they have one
    if (gSpeciesInfo[wonderTradeSpecies].abilities[2] != ABILITY_NONE && (Random() % 99) < 50)
    {
        if ((Random() % 99) < 10)
        {
            abilityNum = 2;
            SetMonData(&gEnemyParty[0], MON_DATA_ABILITY_NUM, &abilityNum);
        }
    }
#endif

    SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, &newHeldItem);
    SetMonData(&gEnemyParty[0], MON_DATA_HP_IV, &wonderTrade->ivs[0]);
    SetMonData(&gEnemyParty[0], MON_DATA_ATK_IV, &wonderTrade->ivs[1]);
    SetMonData(&gEnemyParty[0], MON_DATA_DEF_IV, &wonderTrade->ivs[2]);
    SetMonData(&gEnemyParty[0], MON_DATA_SPEED_IV, &wonderTrade->ivs[3]);
    SetMonData(&gEnemyParty[0], MON_DATA_SPATK_IV, &wonderTrade->ivs[4]);
    SetMonData(&gEnemyParty[0], MON_DATA_SPDEF_IV, &wonderTrade->ivs[5]);
#ifdef RHH_EXPANSION
    StringCopy(monName, GetSpeciesName(wonderTradeSpecies));
#else
    GetSpeciesName(monName, wonderTradeSpecies);
#endif
    SetMonData(&gEnemyParty[0], MON_DATA_NICKNAME, monName);
    SetMonData(&gEnemyParty[0], MON_DATA_OT_NAME, otName);
    SetMonData(&gEnemyParty[0], MON_DATA_BEAUTY, &wonderTrade->conditions[1]);
    SetMonData(&gEnemyParty[0], MON_DATA_CUTE, &wonderTrade->conditions[2]);
    SetMonData(&gEnemyParty[0], MON_DATA_COOL, &wonderTrade->conditions[0]);
    SetMonData(&gEnemyParty[0], MON_DATA_SMART, &wonderTrade->conditions[3]);
    SetMonData(&gEnemyParty[0], MON_DATA_TOUGH, &wonderTrade->conditions[4]);
    SetMonData(&gEnemyParty[0], MON_DATA_SHEEN, &wonderTrade->sheen);
    SetMonData(&gEnemyParty[0], MON_DATA_OT_GENDER, &genderOT);
    SetMonData(&gEnemyParty[0], MON_DATA_MET_LOCATION, &metLocation);
    CalculateMonStats(&gEnemyParty[0]);
}

#ifdef RHH_EXPANSION
static u16 GetWonderTradeEvolutionTargetSpecies(struct Pokemon *mon)
{
    int i, j;
    u16 targetSpecies = 0;
    u16 partnerSpecies = GetMonData(mon, MON_DATA_SPECIES);
    u32 partnerPersonality = GetMonData(mon, MON_DATA_PERSONALITY);
    u16 upperPersonality = partnerPersonality >> 16;
    u8 partnerLevel = GetMonData(mon, MON_DATA_LEVEL);
    u16 rndEeveevolutionChance = Random() % 8;
    u16 rndAlcrememeEvoChance = Random() % 9;
    u16 currentMap = ((gSaveBlock1Ptr->location.mapGroup) << 8 | gSaveBlock1Ptr->location.mapNum);
    u16 partnerHeldItem = GetMonData(mon, MON_DATA_HELD_ITEM);
    u16 playerSpecies = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES);
    u16 partnerHoldEffect = ItemId_GetHoldEffect(partnerHeldItem);

    // partnerSpecies-specific exceptions.
    if (partnerSpecies == SPECIES_NINCADA && partnerLevel >= 20)
    {
        if ((Random() % 2) == 0)
            targetSpecies = SPECIES_NINJASK;
        else
            targetSpecies = SPECIES_SHEDINJA;
        return targetSpecies;
    }
    else if (partnerSpecies == SPECIES_EEVEE && partnerLevel >= 25)
    {
        if (rndEeveevolutionChance == 0)
            targetSpecies = SPECIES_VAPOREON;
        else if (rndEeveevolutionChance == 1)
            targetSpecies = SPECIES_JOLTEON;
        else if (rndEeveevolutionChance == 2)
            targetSpecies = SPECIES_FLAREON;
        else if (rndEeveevolutionChance == 3)
            targetSpecies = SPECIES_ESPEON;
        else if (rndEeveevolutionChance == 4)
            targetSpecies = SPECIES_UMBREON;
        else if (rndEeveevolutionChance == 5)
            targetSpecies = SPECIES_LEAFEON;
        else if (rndEeveevolutionChance == 6)
            targetSpecies = SPECIES_GLACEON;
        else if (rndEeveevolutionChance == 7)
            targetSpecies = SPECIES_SYLVEON;
        return targetSpecies;
    }
    else if (partnerSpecies == SPECIES_MILCERY && partnerLevel >= 25)
    {
        if (rndAlcrememeEvoChance == 0)
            targetSpecies = SPECIES_ALCREMIE;
        else if (rndAlcrememeEvoChance == 1)
            targetSpecies = SPECIES_ALCREMIE_RUBY_CREAM;
        else if (rndAlcrememeEvoChance == 2)
            targetSpecies = SPECIES_ALCREMIE_MATCHA_CREAM;
        else if (rndAlcrememeEvoChance == 3)
            targetSpecies = SPECIES_ALCREMIE_MINT_CREAM;
        else if (rndAlcrememeEvoChance == 4)
            targetSpecies = SPECIES_ALCREMIE_LEMON_CREAM;
        else if (rndAlcrememeEvoChance == 5)
            targetSpecies = SPECIES_ALCREMIE_SALTED_CREAM;
        else if (rndAlcrememeEvoChance == 6)
            targetSpecies = SPECIES_ALCREMIE_RUBY_SWIRL;
        else if (rndAlcrememeEvoChance == 7)
            targetSpecies = SPECIES_ALCREMIE_CARAMEL_SWIRL;
        else if (rndAlcrememeEvoChance == 8)
            targetSpecies = SPECIES_ALCREMIE_RAINBOW_SWIRL;
        return targetSpecies;
    }

    for (i = 0; i < 5; i++)
    {
        switch (gEvolutionTable[partnerSpecies][i].method)
        {
        case EVO_FRIENDSHIP:
            if ((partnerSpecies == SPECIES_PICHU || partnerSpecies == SPECIES_CLEFFA || partnerSpecies == SPECIES_IGGLYBUFF
              || partnerSpecies == SPECIES_TOGEPI || partnerSpecies == SPECIES_AZURILL || partnerSpecies == SPECIES_BUDEW
              || partnerSpecies == SPECIES_BUNEARY || partnerSpecies == SPECIES_SWOOBAT || partnerSpecies == SPECIES_SWADLOON)
              && partnerLevel >= 16)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            else if (partnerSpecies == SPECIES_MEOWTH_ALOLAN && partnerLevel >= 28)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            else if ((partnerSpecies == SPECIES_GOLBAT || partnerSpecies == SPECIES_CHANSEY
                   || partnerSpecies == SPECIES_MUNCHLAX) && partnerLevel >= 35)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_LEVEL:
            if (partnerSpecies == SPECIES_SLOWPOKE && partnerLevel >= 37)
            {
                if ((Random() % 2) == 0)
                    targetSpecies = SPECIES_SLOWBRO;
                else
                    targetSpecies = SPECIES_SLOWKING;
            }
            else if (partnerSpecies == SPECIES_TOXEL && partnerLevel >= 30)
            {
                if (GetNature(mon) == NATURE_HARDY || GetNature(mon) == NATURE_BRAVE
                 || GetNature(mon) == NATURE_ADAMANT || GetNature(mon) == NATURE_NAUGHTY
                 || GetNature(mon) == NATURE_DOCILE || GetNature(mon) == NATURE_IMPISH
                 || GetNature(mon) == NATURE_LAX || GetNature(mon) == NATURE_HASTY
                 || GetNature(mon) == NATURE_JOLLY || GetNature(mon) == NATURE_NAIVE
                 || GetNature(mon) == NATURE_RASH || GetNature(mon) == NATURE_SASSY
                 || GetNature(mon) == NATURE_QUIRKY)
                    targetSpecies = SPECIES_TOXTRICITY;
                else
                    targetSpecies = SPECIES_TOXTRICITY_LOW_KEY;
            }
            else if (gEvolutionTable[partnerSpecies][i].param <= partnerLevel)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            break;
        case EVO_LEVEL_ATK_GT_DEF:
            if (gEvolutionTable[partnerSpecies][i].param <= partnerLevel)
            {
                if (GetMonData(mon, MON_DATA_ATK, 0) > GetMonData(mon, MON_DATA_DEF, 0))
                    targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            break;
        case EVO_LEVEL_ATK_EQ_DEF:
            if (gEvolutionTable[partnerSpecies][i].param <= partnerLevel)
            {
                if (GetMonData(mon, MON_DATA_ATK, 0) == GetMonData(mon, MON_DATA_DEF, 0))
                    targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            break;
        case EVO_LEVEL_ATK_LT_DEF:
            if (gEvolutionTable[partnerSpecies][i].param <= partnerLevel)
            {
                if (GetMonData(mon, MON_DATA_ATK, 0) < GetMonData(mon, MON_DATA_DEF, 0))
                    targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            break;
        case EVO_LEVEL_SILCOON:
            if (gEvolutionTable[partnerSpecies][i].param <= partnerLevel && (upperPersonality % 10) <= 4)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_LEVEL_CASCOON:
            if (gEvolutionTable[partnerSpecies][i].param <= partnerLevel && (upperPersonality % 10) > 4)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_BEAUTY:
            if (partnerLevel >= 30)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_ITEM:
            if (partnerSpecies == SPECIES_GLOOM && partnerLevel >= 36)
            {
                if ((Random() % 2) == 0)
                    targetSpecies = SPECIES_VILEPLUME;
                else
                    targetSpecies = SPECIES_BELLOSSOM;
            }
            else if (partnerSpecies == SPECIES_WEEPINBELL && partnerLevel >= 36)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if ((partnerSpecies == SPECIES_VULPIX || partnerSpecies == SPECIES_GROWLITHE) && partnerLevel >= 32)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if ((partnerSpecies == SPECIES_SHELLDER || partnerSpecies == SPECIES_STARYU) && partnerLevel >= 43)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if ((partnerSpecies == SPECIES_NIDORINA || partnerSpecies == SPECIES_NIDORINO || partnerSpecies == SPECIES_EXEGGCUTE) && partnerLevel >= 26)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if ((partnerSpecies == SPECIES_JIGGLYPUFF || partnerSpecies == SPECIES_CLEFAIRY || partnerSpecies == SPECIES_SKITTY) && partnerLevel >= 38)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if ((partnerSpecies == SPECIES_LOMBRE || partnerSpecies == SPECIES_NUZLEAF) && partnerLevel >= 38)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if (partnerSpecies == SPECIES_POLIWHIRL && partnerLevel >= 44)
            {
                if ((Random() % 2) == 0)
                    targetSpecies = SPECIES_POLIWRATH;
                else
                    targetSpecies = SPECIES_POLITOED;
            }
            else if (partnerSpecies == SPECIES_PIKACHU && partnerLevel >= 27)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if (partnerSpecies == SPECIES_SUNKERN && partnerLevel >= 15)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if ((partnerSpecies == SPECIES_MURKROW || partnerSpecies == SPECIES_MISDREAVUS
                   || partnerSpecies == SPECIES_MUNNA || partnerSpecies == SPECIES_DOUBLADE
                   || partnerSpecies == SPECIES_SINISTEA || partnerSpecies == SPECIES_SANDSHREW_ALOLAN
                   || partnerSpecies == SPECIES_VULPIX_ALOLAN || partnerSpecies == SPECIES_SINISTEA_ANTIQUE)
                   && partnerLevel >= 25)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if ((partnerSpecies == SPECIES_PANSAGE || partnerSpecies == SPECIES_PANSEAR
                   || partnerSpecies == SPECIES_PANPOUR || partnerSpecies == SPECIES_COTTONEE
                   || partnerSpecies == SPECIES_PETILIL || partnerSpecies == SPECIES_MINCCINO
                   || partnerSpecies == SPECIES_FLOETTE || partnerSpecies == SPECIES_FLOETTE_YELLOW_FLOWER
                   || partnerSpecies == SPECIES_FLOETTE_ORANGE_FLOWER || partnerSpecies == SPECIES_FLOETTE_BLUE_FLOWER
                   || partnerSpecies == SPECIES_FLOETTE_WHITE_FLOWER) && partnerLevel >= 15)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if ((partnerSpecies == SPECIES_EELEKTRIK || partnerSpecies == SPECIES_LAMPENT
                   || partnerSpecies == SPECIES_HELIOPTILE || partnerSpecies == SPECIES_CHARJABUG
                   || partnerSpecies == SPECIES_DARUMAKA_GALARIAN) && partnerLevel >= 35)
            {
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            else if (partnerSpecies == SPECIES_APPLIN && partnerLevel >= 30)
            {
                if ((Random() % 2) == 0)
                    targetSpecies = SPECIES_FLAPPLE;
                else
                    targetSpecies = SPECIES_APPLETUN;
            }
            else if (partnerSpecies == SPECIES_SLOWPOKE_GALARIAN && partnerLevel >= 37)
            {
                if ((Random() % 2) == 0)
                    targetSpecies = SPECIES_SLOWBRO_GALARIAN;
                else
                    targetSpecies = SPECIES_SLOWKING_GALARIAN;
            }
            break;
        case EVO_ITEM_FEMALE:
            if (GetMonGender(mon) == MON_FEMALE && partnerSpecies == SPECIES_SNORUNT && partnerLevel >= 35)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_ITEM_MALE:
            if (GetMonGender(mon) == MON_MALE && partnerSpecies == SPECIES_KIRLIA && partnerLevel >= 35)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_MOVE:
            if (MonKnowsMove(mon, gEvolutionTable[partnerSpecies][i].param))
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_FRIENDSHIP_MOVE_TYPE:
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (gBattleMoves[GetMonData(mon, MON_DATA_MOVE1 + j, NULL)].type == gEvolutionTable[partnerSpecies][i].param)
                {
                    targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
                    break;
                }
            }
            break;
        case EVO_LEVEL_DARK_TYPE_MON_IN_PARTY:
            if (gEvolutionTable[partnerSpecies][i].param <= partnerLevel)
            {
                for (j = 0; j < PARTY_SIZE; j++)
                {
                    u16 currSpecies = GetMonData(&gPlayerParty[j], MON_DATA_SPECIES, NULL);
                    if (gSpeciesInfo[currSpecies].types[0] == TYPE_DARK
                     || gSpeciesInfo[currSpecies].types[1] == TYPE_DARK)
                    {
                        targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
                        break;
                    }
                }
            }
            break;
        case EVO_LEVEL_RAIN:
            j = GetCurrentWeather();
            if (j == WEATHER_RAIN || j == WEATHER_RAIN_THUNDERSTORM || j == WEATHER_DOWNPOUR)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_MAPSEC:
            if (gMapHeader.regionMapSectionId == gEvolutionTable[partnerSpecies][i].param)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_SPECIFIC_MAP:
            if (currentMap == gEvolutionTable[partnerSpecies][i].param)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_SPECIFIC_MON_IN_PARTY:
            for (j = 0; j < PARTY_SIZE; j++)
            {
                if (GetMonData(&gPlayerParty[j], MON_DATA_SPECIES) == gEvolutionTable[partnerSpecies][i].param)
                    targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            break;
        case EVO_TRADE:
            targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_TRADE_ITEM:
            if (gEvolutionTable[partnerSpecies][i].param == partnerHeldItem)
            {
                partnerHeldItem = ITEM_NONE;
                SetMonData(mon, MON_DATA_HELD_ITEM, &partnerHeldItem);
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            break;
        case EVO_TRADE_SPECIFIC_MON:
            if (gEvolutionTable[partnerSpecies][i].param == playerSpecies && partnerHoldEffect != HOLD_EFFECT_PREVENT_EVOLVE)
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_LEVEL_FOG:
            j = GetCurrentWeather();
            if (gEvolutionTable[partnerSpecies][i].param <= partnerLevel && (j == WEATHER_FOG_HORIZONTAL || j == WEATHER_FOG_DIAGONAL))
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            break;
        case EVO_LEVEL_NATURE_AMPED:
            if (gEvolutionTable[partnerSpecies][i].param <= partnerLevel)
            {
                u8 nature = GetNature(mon);
                switch (nature)
                {
                case NATURE_HARDY:
                case NATURE_BRAVE:
                case NATURE_ADAMANT:
                case NATURE_NAUGHTY:
                case NATURE_DOCILE:
                case NATURE_IMPISH:
                case NATURE_LAX:
                case NATURE_HASTY:
                case NATURE_JOLLY:
                case NATURE_NAIVE:
                case NATURE_RASH:
                case NATURE_SASSY:
                case NATURE_QUIRKY:
                    targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
                    break;
                }
            }
            break;
        case EVO_LEVEL_NATURE_LOW_KEY:
            if (gEvolutionTable[partnerSpecies][i].param <= partnerLevel)
            {
                u8 nature = GetNature(mon);
                switch (nature)
                {
                case NATURE_LONELY:
                case NATURE_BOLD:
                case NATURE_RELAXED:
                case NATURE_TIMID:
                case NATURE_SERIOUS:
                case NATURE_MODEST:
                case NATURE_MILD:
                case NATURE_QUIET:
                case NATURE_BASHFUL:
                case NATURE_CALM:
                case NATURE_GENTLE:
                case NATURE_CAREFUL:
                    targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
                    break;
                }
            }
            break;
        case EVO_ITEM_HOLD:
            if (partnerHeldItem == gEvolutionTable[partnerSpecies][i].param)
            {
                partnerHeldItem = 0;
                SetMonData(mon, MON_DATA_HELD_ITEM, &partnerHeldItem);
                targetSpecies = gEvolutionTable[partnerSpecies][i].targetSpecies;
            }
            break;
        }
    }

    return (targetSpecies == 0) ? partnerSpecies : targetSpecies;
}
#else
static u16 GetWonderTradeEvolutionTargetSpecies(struct Pokemon *mon)
{
    int i, j;
    u16 targetSpecies = 0;
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u32 personality = GetMonData(mon, MON_DATA_PERSONALITY);
    u16 upperPersonality = personality >> 16;
    u8 level = GetMonData(mon, MON_DATA_LEVEL);
    u16 rndEeveevolutionChance = Random() % 7;
    u16 HeldItem = GetMonData(mon, MON_DATA_HELD_ITEM);

    if (species == SPECIES_EEVEE || species == SPECIES_NINCADA)
    {
        if (species == SPECIES_NINCADA && level >= 20)
        {
            if ((Random() % 2) == 0)
                targetSpecies = SPECIES_NINJASK;
            else
                targetSpecies = SPECIES_SHEDINJA;
            return targetSpecies;
        }
        else if (species == SPECIES_EEVEE && level >= 25)
        {
            if (rndEeveevolutionChance == 0)
                targetSpecies = SPECIES_VAPOREON;
            else if (rndEeveevolutionChance == 1)
                targetSpecies = SPECIES_JOLTEON;
            else if (rndEeveevolutionChance == 2)
                targetSpecies = SPECIES_FLAREON;
            else if (rndEeveevolutionChance == 3)
                targetSpecies = SPECIES_ESPEON;
            else if (rndEeveevolutionChance == 4)
                targetSpecies = SPECIES_UMBREON;
            else if (rndEeveevolutionChance == 5)
                targetSpecies = SPECIES_LEAFEON;
            else if (rndEeveevolutionChance == 6)
                targetSpecies = SPECIES_GLACEON;
            else if (rndEeveevolutionChance == 7)
                targetSpecies = SPECIES_SYLVEON;
            return targetSpecies;
        }
    }

    for (i = 0; i < 5; i++)
    {
        switch (gEvolutionTable[species][i].method)
        {
        case EVO_FRIENDSHIP:
            if ((species == SPECIES_PICHU || species == SPECIES_CLEFFA || species == SPECIES_IGGLYBUFF
              || species == SPECIES_TOGEPI || species == SPECIES_AZURILL || species == SPECIES_BUDEW) && level >= 16)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            else if ((species == SPECIES_GOLBAT || species == SPECIES_CHANSEY  || species == SPECIES_MUNCHLAX) && level >= 35)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            break;
        case EVO_LEVEL:
            if (species == SPECIES_SLOWPOKE && level >= 37)
            {
                if ((Random() % 2) == 0)
                    targetSpecies = SPECIES_SLOWBRO;
                else
                    targetSpecies = SPECIES_SLOWKING;
            }
            else if (gEvolutionTable[species][i].param <= level)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            break;
        case EVO_LEVEL_ATK_GT_DEF:
            if (gEvolutionTable[species][i].param <= level)
            {
                if (GetMonData(mon, MON_DATA_ATK, 0) > GetMonData(mon, MON_DATA_DEF, 0))
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            break;
        case EVO_LEVEL_ATK_EQ_DEF:
            if (gEvolutionTable[species][i].param <= level)
            {
                if (GetMonData(mon, MON_DATA_ATK, 0) == GetMonData(mon, MON_DATA_DEF, 0))
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            break;
        case EVO_LEVEL_ATK_LT_DEF:
            if (gEvolutionTable[species][i].param <= level)
            {
                if (GetMonData(mon, MON_DATA_ATK, 0) < GetMonData(mon, MON_DATA_DEF, 0))
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            break;
        case EVO_LEVEL_SILCOON:
            if (gEvolutionTable[species][i].param <= level && (upperPersonality % 10) <= 4)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            break;
        case EVO_LEVEL_CASCOON:
            if (gEvolutionTable[species][i].param <= level && (upperPersonality % 10) > 4)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            break;
        case EVO_BEAUTY:
            if (level >= 30)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            break;
        case EVO_ITEM:
            if (species == SPECIES_GLOOM && level >= 36)
            {
                if ((Random() % 2) == 0)
                    targetSpecies = SPECIES_VILEPLUME;
                else
                    targetSpecies = SPECIES_BELLOSSOM;
            }
            else if (species == SPECIES_WEEPINBELL && level >= 36)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            else if ((species == SPECIES_VULPIX || species == SPECIES_GROWLITHE) && level >= 32)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            else if ((species == SPECIES_SHELLDER || species == SPECIES_STARYU) && level >= 43)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            else if ((species == SPECIES_NIDORINA || species == SPECIES_NIDORINO || species == SPECIES_EXEGGCUTE) && level >= 26)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            else if ((species == SPECIES_JIGGLYPUFF || species == SPECIES_CLEFAIRY || species == SPECIES_SKITTY) && level >= 38)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            else if ((species == SPECIES_LOMBRE || species == SPECIES_NUZLEAF) && level >= 38)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            else if (species == SPECIES_POLIWHIRL && level >= 44)
            {
                if ((Random() % 2) == 0)
                    targetSpecies = SPECIES_POLIWRATH;
                else
                    targetSpecies = SPECIES_POLITOED;
            }
            else if (species == SPECIES_PIKACHU && level >= 27)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            else if (species == SPECIES_SUNKERN && level >= 15)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            break;
        case EVO_TRADE_ITEM:
            if ((species == SPECIES_ONIX || species == SPECIES_SEADRA) && level >= 40)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            else if (species == SPECIES_SCYTHER && level >= 26)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            else if (species == SPECIES_PORYGON && level >= 21)
            {
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            else if (species == SPECIES_CLAMPERL && level >= 22)
            {
                if ((Random() % 2) == 0)
                    targetSpecies = SPECIES_HUNTAIL;
                else
                    targetSpecies = SPECIES_GOREBYSS;
            }
            break;
        case EVO_LEVEL_FEMALE:
            if (GetMonGender(mon) == MON_FEMALE && species == SPECIES_KIRLIA && level >= 35)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            break;
        case EVO_LEVEL_MALE:
            if (GetMonGender(mon) == MON_MALE && species == SPECIES_SNORUNT && level >= 35)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            break;
        case EVO_LEVEL_FEMALE_MORNING:
            UpdateTimeOfDay();
            {
            if (GetMonGender(mon) == MON_FEMALE && species == SPECIES_KIRLIA && gLocalTime.hours >= 6 && gLocalTime.hours < 9 && level >= 35)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            
            }
            break;
        case EVO_LEVEL_MALE_MORNING:
            UpdateTimeOfDay();
            {
            if (GetMonGender(mon) == MON_MALE && species == SPECIES_SNORUNT && gLocalTime.hours >= 6 && gLocalTime.hours < 9 && level >= 35)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            break;
        case EVO_LEVEL_NIGHT:
            UpdateTimeOfDay();
            if (gLocalTime.hours >= 0 && gLocalTime.hours < 7 && gEvolutionTable[species][i].param <= level)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            if (gLocalTime.hours >= 20 && gLocalTime.hours < 24 && gEvolutionTable[species][i].param <= level)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            break;
        case EVO_LEVEL_DAY:
            UpdateTimeOfDay();
            if (gLocalTime.hours >= 7 && gLocalTime.hours < 20 && gEvolutionTable[species][i].param <= level)
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            break;
        case EVO_ITEM_HOLD_NIGHT:
            if (gLocalTime.hours >= 0 && gLocalTime.hours < 7 && HeldItem == gEvolutionTable[species][i].param)
            {
                HeldItem = 0;
                SetMonData(mon, MON_DATA_HELD_ITEM, &HeldItem);
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            if (gLocalTime.hours >= 20 && gLocalTime.hours < 24 && HeldItem == gEvolutionTable[species][i].param)
            {
                HeldItem = 0;
                SetMonData(mon, MON_DATA_HELD_ITEM, &HeldItem);
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            break;
        case EVO_ITEM_HOLD_DAY:
            if (gLocalTime.hours >= 7 && gLocalTime.hours < 20 && HeldItem == gEvolutionTable[species][i].param)
            {
                HeldItem = 0;
                SetMonData(mon, MON_DATA_HELD_ITEM, &HeldItem);
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            }
            break;
        case EVO_MOVE:
            if (MonKnowsMove(mon, gEvolutionTable[species][i].param))
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            break;
        case EVO_MOVE_TYPE:
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (gBattleMoves[GetMonData(mon, MON_DATA_MOVE1 + j, NULL)].type == gEvolutionTable[species][i].param)
                {
                    targetSpecies = gEvolutionTable[species][i].targetSpecies;
                    break;
                }
            }
            break;
        case EVO_ITEM_HOLD:
                HeldItem = 0;
                SetMonData(mon, MON_DATA_HELD_ITEM, &HeldItem);
                targetSpecies = gEvolutionTable[species][i].targetSpecies;
            break;
        }
    }

    if (targetSpecies == 0)
        return species;
    else
        return targetSpecies;
}
#endif

#if defined RHH_EXPANSION
static u32 GetEvolutionSpecies(u16 speciesId)
{
    u32 i;

    for (i = 0; i < EVOS_PER_MON; i++)
    {
        if (gEvolutionTable[speciesId][i].targetSpecies)
            return gEvolutionTable[speciesId][i].targetSpecies;
    }
    return SPECIES_NONE;
}

static bool32 IsSpeciesFamilyMegaEvolutionCompatible(u16 species, u16 heldStone)
{
    u32 i;
    const struct FormChange *formChanges = gFormChangeTablePointers[species];
    u16 nextEvo = GetEvolutionSpecies(species);

    for (i = 0; formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (formChanges[i].method == FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM && formChanges[i].param1 == heldStone)
            return TRUE;
    }

    if (nextEvo != SPECIES_NONE)
        return IsSpeciesFamilyMegaEvolutionCompatible(nextEvo, heldStone);

    return FALSE;
}
#endif

// Generates an item randomly for a Pokémon received via Wonder Trade to hold, with a few exceptions.
static u16 GetValidHeldItemForSpecies(u16 species)
{
    u16 item;
    u16 itemHoldEffect;
    u16 itemPocket;
    u8 itemImportance;

    ROLL:
        item = Random() % ITEMS_COUNT;

    itemHoldEffect = ItemId_GetHoldEffect(item);
    itemPocket = ItemId_GetPocket(item);
    itemImportance = ItemId_GetImportance(item);

    if (item == ITEM_NONE || item == ITEM_ENIGMA_BERRY)
        goto ROLL;
    else if (itemHoldEffect == HOLD_EFFECT_NONE)
        goto ROLL;
    else if (IS_ITEM_MAIL(item))
        goto ROLL;
    else if (itemPocket == POCKET_KEY_ITEMS || itemPocket == POCKET_TM_HM)
        goto ROLL;
#ifdef RHH_EXPANSION
    else if (item == ITEM_GRACIDEA
          || item == ITEM_RED_ORB
          || item == ITEM_BLUE_ORB
          || item == ITEM_ADAMANT_ORB
          || item == ITEM_LUSTROUS_ORB
          || item == ITEM_GRISEOUS_ORB
          || item == ITEM_ADAMANT_CRYSTAL
          || item == ITEM_LUSTROUS_GLOBE
          || item == ITEM_GRISEOUS_CORE)
        goto ROLL;
    else if ((itemHoldEffect == HOLD_EFFECT_MEMORY || itemHoldEffect == HOLD_EFFECT_DRIVE
           || itemHoldEffect == HOLD_EFFECT_PLATE || itemHoldEffect == HOLD_EFFECT_GEMS)
           && (gSpeciesInfo[species].types[0] != ItemId_GetHoldEffectParam(item)
            || gSpeciesInfo[species].types[1] != ItemId_GetHoldEffectParam(item)))
        goto ROLL;
    // Re-roll the item generated if it's a Mega Stone not compatible with the Pokémon that's being received.
    else if (itemHoldEffect == HOLD_EFFECT_MEGA_STONE && !IsSpeciesFamilyMegaEvolutionCompatible(species, item))
        goto ROLL;
    else if (itemHoldEffect == HOLD_EFFECT_Z_CRYSTAL || itemHoldEffect == HOLD_EFFECT_MASK)
        goto ROLL;
#else
    else if (sIsInvalidItem[item])
        goto ROLL;
#endif
    else if (itemImportance > 0)
        goto ROLL;

    return item;
}