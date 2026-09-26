#ifndef GUARD_RANDOM_H
#define GUARD_RANDOM_H

extern u32 gRngValue;
extern u32 gRng2Value;

//Returns a 16-bit pseudorandom number
u16 Random(void);
u16 Random2(void);
//tx_randomizer_and_challenges
u16 RandomSeeded(u16 value, u8 seeded);
u16 RandomSeededModulo(u32 value, u16 modulo);
void ShuffleListU8(u8 *list, u8 count, u8 seed);
void ShuffleListU16(u16 *list, u16 count, u32 seed);
u8 RandomWeightedIndex(u8 *weights, u8 length);

//Returns a 32-bit pseudorandom number
#define Random32() (Random() | (Random() << 16))

// The number 1103515245 comes from the example implementation of rand and srand
// in the ISO C standard.
#define ISO_RANDOMIZE1(val)(1103515245 * (val) + 24691)
#define ISO_RANDOMIZE2(val)(1103515245 * (val) + 12345)

//Sets the initial seed value of the pseudorandom number generator
void SeedRng(u16 seed);
void SeedRng2(u16 seed);

#endif // GUARD_RANDOM_H
