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

void PlayTimeCounter_Start(void)
{
    sPlayTimeCounterState = RUNNING;

    if (gSaveBlock2Ptr->playTimeHours > 999)
        PlayTimeCounter_SetToMax();
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

    if (gSaveBlock2Ptr->playTimeHours > 999)
        PlayTimeCounter_SetToMax();
}

void PlayTimeCounter_SetToMax(void)
{
    sPlayTimeCounterState = MAXED_OUT;

    gSaveBlock2Ptr->playTimeHours = 999;
    gSaveBlock2Ptr->playTimeMinutes = 59;
    gSaveBlock2Ptr->playTimeSeconds = 59;
    gSaveBlock2Ptr->playTimeVBlanks = 59;
}
