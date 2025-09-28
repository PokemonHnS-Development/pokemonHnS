#include "global.h"
#include "time_events.h"
#include "event_data.h"
#include "field_weather.h"
#include "pokemon.h"
#include "random.h"
#include "overworld.h"
#include "rtc.h"
#include "script.h"
#include "task.h"
#include "pokemon_storage_system.h"
#include "load_save.h"

static u32 GetMirageRnd(void)
{
    u32 hi = VarGet(VAR_MIRAGE_RND_H);
    u32 lo = VarGet(VAR_MIRAGE_RND_L);
    return (hi << 16) | lo;
}

static void SetMirageRnd(u32 rnd)
{
    VarSet(VAR_MIRAGE_RND_H, rnd >> 16);
    VarSet(VAR_MIRAGE_RND_L, rnd);
}

// unused
void InitMirageRnd(void)
{
    SetMirageRnd((Random() << 16) | Random());
}

void UpdateMirageRnd(u16 days)
{
    s32 rnd = GetMirageRnd();
    while (days)
    {
        rnd = ISO_RANDOMIZE2(rnd);
        days--;
    }
    SetMirageRnd(rnd);
}

bool32 IsMirageIslandPresent(void)
{
    u32 hi = gSaveBlock1Ptr->vars[VAR_MIRAGE_RND_H - VARS_START];
    u32 lo = gSaveBlock1Ptr->vars[VAR_MIRAGE_RND_L - VARS_START];
    u32 rnd = ((hi << 16) | lo) >> 16;
    bool32 species;
    u32 personality;
    int i, j;
    struct Pokemon * curMon = &gPlayerParty[0];
    struct Pokemon * partyEnd = &gPlayerParty[PARTY_SIZE];

    for (i = 0; i < PARTY_SIZE; i++)
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == SPECIES_MEW)
            return TRUE;

    do
    {
        species = curMon->box.hasSpecies;
        if (!species) 
            break;
        personality = curMon->box.personality & 0xFFFF;
        if (personality == rnd)
            return TRUE;
    } while (++curMon < partyEnd);

    struct BoxPokemon * curBoxMon = &(gPokemonStoragePtr->boxes[0][0]);
    struct BoxPokemon * boxMonEnd = &(gPokemonStoragePtr->boxes[TOTAL_BOXES_COUNT][IN_BOX_COUNT]);

    do {
        species = curBoxMon->hasSpecies;
        if (species) {
            personality = curBoxMon->personality & 0xffff;
            if (personality == rnd) {
                return TRUE;
            }
        }
    } while (++curBoxMon < boxMonEnd);

    return FALSE;
}

void UpdateShoalTideFlag(void)
{
    static const u8 tide[] =
    {
        1, // 00
        1, // 01
        1, // 02
        0, // 03
        0, // 04
        0, // 05
        0, // 06
        0, // 07
        0, // 08
        1, // 09
        1, // 10
        1, // 11
        1, // 12
        1, // 13
        1, // 14
        0, // 15
        0, // 16
        0, // 17
        0, // 18
        0, // 19
        0, // 20
        1, // 21
        1, // 22
        1, // 23
    };

    if (IsMapTypeOutdoors(GetLastUsedWarpMapType()))
    {
        RtcCalcLocalTime();
        if (tide[gLocalTime.hours])
            FlagSet(FLAG_SYS_LAKE_OF_RAGE_TIDE);
        else
            FlagClear(FLAG_SYS_LAKE_OF_RAGE_TIDE);
    }
}

static void Task_WaitWeather(u8 taskId)
{
    if (IsWeatherChangeComplete())
    {
        ScriptContext_Enable();
        DestroyTask(taskId);
    }
}

void WaitWeather(void)
{
    CreateTask(Task_WaitWeather, 80);
}

void InitBirchState(void)
{
    *GetVarPointer(VAR_BIRCH_STATE) = 0;
}

void UpdateBirchState(u16 days)
{
    u16 *state = GetVarPointer(VAR_BIRCH_STATE);
    *state += days;
    *state %= 7;
}