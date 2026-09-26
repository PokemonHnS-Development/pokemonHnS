#include "global.h"
#include "play_time.h"
#include "rtc_include.h"
#include "rtc.h"

enum
{
    STOPPED,
    RUNNING,
    MAXED_OUT
};

static u8 sPlayTimeCounterState;

void PlayTimeCounter_Reset(void)
{
    sPlayTimeCounterState = STOPPED;

    gSaveBlock2Ptr->playTimeHours = 0;
    gSaveBlock2Ptr->playTimeMinutes = 0;
    gSaveBlock2Ptr->playTimeSeconds = 0;
    gSaveBlock2Ptr->playTimeVBlanks = 0;
}

// Roll play time back to 00:01:00 and keep the counter RUNNING.
static void PlayTimeCounter_Rollover(void)
{
    gSaveBlock2Ptr->playTimeHours   = 0;
    gSaveBlock2Ptr->playTimeMinutes = 1;
    gSaveBlock2Ptr->playTimeSeconds = 0;
    gSaveBlock2Ptr->playTimeVBlanks = 0;
    sPlayTimeCounterState = RUNNING;
}

void PlayTimeCounter_Start(void)
{
    // --- MIGRATION for existing maxed-out saves ---
    // Unfreeze any save that was previously stuck at MAXED_OUT or >= 999:59.
    if (sPlayTimeCounterState == MAXED_OUT
        || gSaveBlock2Ptr->playTimeHours > 999
        || (gSaveBlock2Ptr->playTimeHours == 999 && gSaveBlock2Ptr->playTimeMinutes >= 59))
    {
        PlayTimeCounter_Rollover();
    }

    sPlayTimeCounterState = RUNNING;
}


void PlayTimeCounter_Stop(void)
{
    sPlayTimeCounterState = STOPPED;
}

void PlayTimeCounter_Update(void)
{
    if (sPlayTimeCounterState != RUNNING)
        return;

    gSaveBlock2Ptr->playTimeVBlanks++;

    if (gSaveBlock2Ptr->playTimeVBlanks < 60)
        return;

    gSaveBlock2Ptr->playTimeVBlanks = 0;
    gSaveBlock2Ptr->playTimeSeconds++;

    if (gSaveBlock1Ptr->tx_Features_RTCType == 1)
        RtcAdvanceTime(0, 0, 24); //Every 1 second in real life, advance "rtc" by 0 hours, 0 minutes, 24 seconds

    if (gSaveBlock2Ptr->playTimeSeconds < 60)
        return;

    gSaveBlock2Ptr->playTimeSeconds = 0;
    gSaveBlock2Ptr->playTimeMinutes++;

    if (gSaveBlock2Ptr->playTimeMinutes < 60)
        return;

    gSaveBlock2Ptr->playTimeMinutes = 0;
    gSaveBlock2Ptr->playTimeHours++;

    if (gSaveBlock2Ptr->playTimeHours > 999 || (gSaveBlock2Ptr->playTimeHours == 999 && gSaveBlock2Ptr->playTimeMinutes >= 59))
    {
        PlayTimeCounter_Rollover();
    }
}

// Replace old "set to max" logic
void PlayTimeCounter_SetToMax(void)
{
    // Previously set MAXED_OUT (which stalls FAKE RTC).
    // Now: rollover and keep running.
    PlayTimeCounter_Rollover();
}


