#include "global.h"
#include "random.h"
#include "new_game.h" //tx_randomizer_and_challenges
#include "tx_randomizer_and_challenges.h"

EWRAM_DATA static u8 sUnknown = 0;
EWRAM_DATA static u32 sRandCount = 0;

// IWRAM common
u32 gRngValue;
u32 gRng2Value;

u16 Random(void)
{
    gRngValue = ISO_RANDOMIZE1(gRngValue);
    sRandCount++;
    return gRngValue >> 16;
}

void SeedRng(u16 seed)
{
    gRngValue = seed;
    sUnknown = 0;
}

void SeedRng2(u16 seed)
{
    gRng2Value = seed;
}

u16 Random2(void)
{
    gRng2Value = ISO_RANDOMIZE1(gRng2Value);
    return gRng2Value >> 16;
}

// ---------------------------------------------------------------------------
// SFC32 local random — isolated from the global LCG.
// ---------------------------------------------------------------------------

static void SFC32_Seed(struct Sfc32State *state, u32 seed)
{
    u32 i;
    state->a = 0;
    state->b = 0;
    state->c = seed;
    state->ctr = 1;
    for (i = 0; i < 16; i++)
        _SFC32_Next(state);
}

struct Sfc32State LocalRandomSeed(u32 seed)
{
    struct Sfc32State result;
    SFC32_Seed(&result, seed);
    return result;
}

//tx_randomizer_and_challenges
u16 RandomSeeded(u16 value, u8 seeded)
{
    u16 otId, result;

    if (gSaveBlock1Ptr->tx_Random_Chaos && !seeded)
    {
        result = Random();
    }
    else
    {
        otId = GetTrainerId(gSaveBlock2Ptr->playerTrainerId);
        result = ISO_RANDOMIZE1(otId + value) >> 16;
    }
    return result;
}
#define I_MAX 5
u16 RandomSeededModulo(u32 value, u16 modulo)
{
    u32 otId;
    u32 RAND_MAX;
    u32 result = 0;
    u8 i = 0;

    if (gSaveBlock1Ptr->tx_Random_Chaos)
        value = Random();

    otId = GetTrainerId(gSaveBlock2Ptr->playerTrainerId);
    RAND_MAX = 0xFFFFFFFF - (0xFFFFFFFF % modulo);

    do
    {
        result = ISO_RANDOMIZE1(otId + value + result);
    }
    while ((result >= RAND_MAX) && (++i != I_MAX));

    return (result % modulo);
}
void ShuffleListU8(u8 *list, u8 count, u8 seed)
{
    u16 i;

    for (i = (count - 1); i > 0; i--)
    {
        u16 j = RandomSeeded(seed, TRUE) % (i + 1);
        u16 arr = list[j];
        list[j] = list[i];
        list[i] = arr;
    }
}
void ShuffleListU16(u16 *list, u16 count, u32 seed)
{
    u16 i;

    for (i = (count - 1); i > 0; i--)
    {
        u16 j = RandomSeeded(seed, TRUE) % (i + 1);
        u16 arr = list[j];
        list[j] = list[i];
        list[i] = arr;
    }
}

// Returns a random index according to a list of weights
u8 RandomWeightedIndex(u8 *weights, u8 length) 
{
    u32 i;
    u16 random_value;
    u16 weightSum = 0;
    for (i = 0; i < length; i++)
        weightSum += weights[i];
    random_value = Random() % weightSum;
    weightSum = 0;
    for (i = 0; i < length; i++) 
    {
        weightSum += weights[i];
        if (random_value <= weightSum)
            return i;
    }
}