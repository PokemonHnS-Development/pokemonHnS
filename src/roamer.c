#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "random.h"
#include "roamer.h"
#include "pokedex.h"

// Despite having a variable to track it, the roamer is
// hard-coded to only ever be in map group 0
#define ROAMER_MAP_GROUP 0

enum
{
    MAP_GRP, // map group
    MAP_NUM, // map number
};

#define ROAMER (&gSaveBlock1Ptr->roamer)
EWRAM_DATA static u8 sLocationHistory[3][2] = {0};
EWRAM_DATA static u8 sRoamerLocation[2] = {0};

#define ___ MAP_NUM(MAP_UNDEFINED) // For empty spots in the location table

// Note: There are two potential softlocks that can occur with this table if its maps are
//       changed in particular ways. They can be avoided by ensuring the following:
//       - There must be at least 2 location sets that start with a different map,
//         i.e. every location set cannot start with the same map. This is because of
//         the while loop in RoamerMoveToOtherLocationSet.
//       - Each location set must have at least 3 unique maps. This is because of
//         the while loop in RoamerMove. In this loop the first map in the set is
//         ignored, and an additional map is ignored if the roamer was there recently.
//       - Additionally, while not a softlock, it's worth noting that if for any
//         map in the location table there is not a location set that starts with
//         that map then the roamer will be significantly less likely to move away
//         from that map when it lands there.
static const u8 sRoamerLocations[][6] = 
{
    { MAP_NUM(MAP_ROUTE29), MAP_NUM(MAP_ROUTE30), MAP_NUM(MAP_ROUTE46), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE30), MAP_NUM(MAP_ROUTE29), MAP_NUM(MAP_ROUTE31), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE31), MAP_NUM(MAP_ROUTE30), MAP_NUM(MAP_ROUTE29), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE32), MAP_NUM(MAP_ROUTE31), MAP_NUM(MAP_ROUTE33), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE33), MAP_NUM(MAP_ROUTE32), MAP_NUM(MAP_ROUTE34), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE34), MAP_NUM(MAP_ROUTE33), MAP_NUM(MAP_ROUTE35), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE35), MAP_NUM(MAP_ROUTE34), MAP_NUM(MAP_ROUTE36), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE36), MAP_NUM(MAP_ROUTE31), MAP_NUM(MAP_ROUTE32), MAP_NUM(MAP_ROUTE35), MAP_NUM(MAP_ROUTE37), ___ },
    { MAP_NUM(MAP_ROUTE37), MAP_NUM(MAP_ROUTE36), MAP_NUM(MAP_ROUTE38), MAP_NUM(MAP_ROUTE42), ___, ___ },
    { MAP_NUM(MAP_ROUTE38), MAP_NUM(MAP_ROUTE37), MAP_NUM(MAP_ROUTE39), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE39), MAP_NUM(MAP_ROUTE48), MAP_NUM(MAP_ROUTE35), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE42), MAP_NUM(MAP_ROUTE37), MAP_NUM(MAP_ROUTE38), MAP_NUM(MAP_ROUTE43), MAP_NUM(MAP_ROUTE44), ___ },
    { MAP_NUM(MAP_ROUTE43), MAP_NUM(MAP_ROUTE42), MAP_NUM(MAP_ROUTE44), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE44), MAP_NUM(MAP_ROUTE42), MAP_NUM(MAP_ROUTE45), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE45), MAP_NUM(MAP_ROUTE44), MAP_NUM(MAP_ROUTE46), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE46), MAP_NUM(MAP_ROUTE45), MAP_NUM(MAP_ROUTE29), ___, ___, ___ },
    { ___, ___, ___, ___, ___, ___ },
};

#undef ___
#define NUM_LOCATION_SETS (ARRAY_COUNT(sRoamerLocations) - 1)
#define NUM_LOCATIONS_PER_SET (ARRAY_COUNT(sRoamerLocations[0]))

void ClearRoamerData(void)
{
    memset(ROAMER, 0, sizeof(*ROAMER));
    ROAMER->species = SPECIES_RAIKOU;
}

void ClearRoamerLocationData(void)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(sLocationHistory); i++)
    {
        sLocationHistory[i][MAP_GRP] = 0;
        sLocationHistory[i][MAP_NUM] = 0;
    }

    sRoamerLocation[MAP_GRP] = 0;
    sRoamerLocation[MAP_NUM] = 0;
}

static void CreateInitialRoamerMon(bool16 createEntei)
{
    if (!createEntei)
        ROAMER->species = SPECIES_RAIKOU;
    else
        ROAMER->species = SPECIES_ENTEI;

    CreateMon(&gEnemyParty[0], ROAMER->species, 60, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    ROAMER->level = 40;
    ROAMER->status = 0;
    ROAMER->active = TRUE;
    ROAMER->ivs = GetMonData(&gEnemyParty[0], MON_DATA_IVS);
    ROAMER->personality = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY);
    ROAMER->hp = GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP);
    ROAMER->cool = GetMonData(&gEnemyParty[0], MON_DATA_COOL);
    ROAMER->beauty = GetMonData(&gEnemyParty[0], MON_DATA_BEAUTY);
    ROAMER->cute = GetMonData(&gEnemyParty[0], MON_DATA_CUTE);
    ROAMER->smart = GetMonData(&gEnemyParty[0], MON_DATA_SMART);
    ROAMER->tough = GetMonData(&gEnemyParty[0], MON_DATA_TOUGH);
    sRoamerLocation[MAP_GRP] = ROAMER_MAP_GROUP;
    sRoamerLocation[MAP_NUM] = sRoamerLocations[Random() % NUM_LOCATION_SETS][0];
}

// gSpecialVar_0x8004 here corresponds to the options in the multichoice MULTI_TV_LATI (0 for 'Red', 1 for 'Blue')
void InitRoamer(void)
{
    ClearRoamerData();
    ClearRoamerLocationData();
    CreateInitialRoamerMon(gSpecialVar_0x8004);
}

void UpdateLocationHistoryForRoamer(void)
{
    sLocationHistory[2][MAP_GRP] = sLocationHistory[1][MAP_GRP];
    sLocationHistory[2][MAP_NUM] = sLocationHistory[1][MAP_NUM];

    sLocationHistory[1][MAP_GRP] = sLocationHistory[0][MAP_GRP];
    sLocationHistory[1][MAP_NUM] = sLocationHistory[0][MAP_NUM];

    sLocationHistory[0][MAP_GRP] = gSaveBlock1Ptr->location.mapGroup;
    sLocationHistory[0][MAP_NUM] = gSaveBlock1Ptr->location.mapNum;
}

void RoamerMoveToOtherLocationSet(void)
{
    u8 mapNum = 0;

    if (!ROAMER->active)
        return;

    sRoamerLocation[MAP_GRP] = ROAMER_MAP_GROUP;

    // Choose a location set that starts with a map
    // different from the roamer's current map
    while (1)
    {
        mapNum = sRoamerLocations[Random() % NUM_LOCATION_SETS][0];
        if (sRoamerLocation[MAP_NUM] != mapNum)
        {
            sRoamerLocation[MAP_NUM] = mapNum;
            return;
        }
    }
}

void RoamerMove(void)
{
    u8 locSet = 0;

    if ((Random() % 16) == 0)
    {
        RoamerMoveToOtherLocationSet();
    }
    else
    {
        if (!ROAMER->active)
            return;

        while (locSet < NUM_LOCATION_SETS)
        {
            // Find the location set that starts with the roamer's current map
            if (sRoamerLocation[MAP_NUM] == sRoamerLocations[locSet][0])
            {
                u8 mapNum;
                while (1)
                {
                    // Choose a new map (excluding the first) within this set
                    // Also exclude a map if the roamer was there 2 moves ago
                    mapNum = sRoamerLocations[locSet][(Random() % (NUM_LOCATIONS_PER_SET - 1)) + 1];
                    if (!(sLocationHistory[2][MAP_GRP] == ROAMER_MAP_GROUP
                       && sLocationHistory[2][MAP_NUM] == mapNum)
                       && mapNum != MAP_NUM(MAP_UNDEFINED))
                        break;
                }
                sRoamerLocation[MAP_NUM] = mapNum;
                return;
            }
            locSet++;
        }
    }
}

bool8 IsRoamerAt(u8 mapGroup, u8 mapNum)
{
    if (ROAMER->active && mapGroup == sRoamerLocation[MAP_GRP] && mapNum == sRoamerLocation[MAP_NUM])
        return TRUE;
    else
        return FALSE;
}

void CreateRoamerMonInstance(void)
{
    u32 status;
    struct Pokemon *mon = &gEnemyParty[0];
    ZeroEnemyPartyMons();
    CreateMonWithIVsPersonality(mon, ROAMER->species, ROAMER->level, ROAMER->ivs, ROAMER->personality);
// The roamer's status field is u8, but SetMonData expects status to be u32, so will set the roamer's status
// using the status field and the following 3 bytes (cool, beauty, and cute).
#ifdef BUGFIX
    status = ROAMER->status;
    SetMonData(mon, MON_DATA_STATUS, &status);
#else
    SetMonData(mon, MON_DATA_STATUS, &ROAMER->status);
#endif
    SetMonData(mon, MON_DATA_HP, &ROAMER->hp);
    SetMonData(mon, MON_DATA_COOL, &ROAMER->cool);
    SetMonData(mon, MON_DATA_BEAUTY, &ROAMER->beauty);
    SetMonData(mon, MON_DATA_CUTE, &ROAMER->cute);
    SetMonData(mon, MON_DATA_SMART, &ROAMER->smart);
    SetMonData(mon, MON_DATA_TOUGH, &ROAMER->tough);
}

bool8 TryStartRoamerEncounter(void)
{
    if (IsRoamerAt(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum) == TRUE && (Random() % 4) == 0)
    {
        CreateRoamerMonInstance();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void UpdateRoamerHPStatus(struct Pokemon *mon)
{
    ROAMER->hp = GetMonData(mon, MON_DATA_HP);
    ROAMER->status = GetMonData(mon, MON_DATA_STATUS);

    RoamerMoveToOtherLocationSet();
}

void SetRoamerInactive(void)
{
    ROAMER->active = FALSE;
}

void GetRoamerLocation(u8 *mapGroup, u8 *mapNum)
{
    *mapGroup = sRoamerLocation[MAP_GRP];
    *mapNum = sRoamerLocation[MAP_NUM];
}
