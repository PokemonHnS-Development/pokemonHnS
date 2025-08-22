#ifndef GUARD_BARD_MUSIC_H
#define GUARD_BARD_MUSIC_H

// The maximum number of BardSoundTemplates/BardSounds there can be for each easy chat word.
#define MAX_BARD_SOUNDS_PER_WORD 6

// The number of pitch tables there are for each pitch table size (see sPitchTables).
#define NUM_BARD_PITCH_TABLES_PER_SIZE 5

// This struct describes which phoneme song to play for the sound, and whether to
// make any adjustments to its length or volume. Very few sounds make any adjustments.
struct BardSoundTemplate
{
    u8 songId;
    s8 lengthAdjustment;
    u16 unused; // Only set on EC_WORD_WAAAH, and never read.
    s16 volume;
};

// This is the length and pitch to play the phoneme song at.
// These will be calculated in 'CalcWordSounds'.
struct BardSound
{
    u16 length;
    u16 pitch;
};

struct BardSong
{
    u8 lyricsIndex;
    u8 soundIndex;
    u8 timer;
    u8 state;
    s16 length; // Length of the sound for the word currently being sung (i.e. the sum of 'length' in all the current word's phonemes).
    u16 volume;
    s16 pitch;
    s16 voiceInflection;
    u16 lyrics[NUM_BARD_SONG_WORDS];
    struct BardSound sounds[MAX_BARD_SOUNDS_PER_WORD];
    const struct BardSoundTemplate *soundTemplates;
};

struct HnS_BardSound
{
    /*0x00*/ u8 songLengthId;
    /*0x01*/ s8 songLengthOffset;
    /*0x02*/ u16 unused;
    /*0x04*/ s16 volume;
    /*0x06*/ u16 unused2;
};

struct HnS_BardPhoneme
{
    /*0x00*/ u16 length;
    /*0x02*/ u16 pitch;
};

struct HnS_BardSong
{
    /*0x00*/ u8 currWord;
    /*0x01*/ u8 currPhoneme;
    /*0x02*/ u8 phonemeTimer;
    /*0x03*/ u8 state;
    /*0x04*/ s16 length;
    /*0x06*/ u16 volume;
    /*0x08*/ s16 pitch;
    /*0x0A*/ s16 voiceInflection;
    /*0x0C*/ u16 lyrics[NUM_BARD_SONG_WORDS];
    /*0x18*/ struct HnS_BardPhoneme phonemes[NUM_BARD_SONG_WORDS];
    /*0x30*/ const struct BardSound *sound;
};

extern const u16 gNumBardWords_Species;
extern const u16 gNumBardWords_Moves;

const struct BardSoundTemplate *GetWordSoundTemplates(u16 easyChatWord);
void CalcWordSounds(struct BardSong *song, u16 pitchTableIndex);
void HnS_GetWordPhonemes(struct HnS_BardSong *song, u16 word);

#endif //GUARD_BARD_MUSIC_H
