#ifndef GUARD_FIELD_DOOR_H
#define GUARD_FIELD_DOOR_H

void FieldSetDoorOpened(int x, int y);
void FieldSetDoorClosed(int x, int y);
s8 FieldAnimateDoorClose(int x, int y);
s8 FieldAnimateDoorOpen(int x, int y);
bool8 FieldIsDoorAnimationRunning(void);
u16 GetDoorSoundEffect(int x, int y);

#endif //GUARD_FIELD_DOOR_H
