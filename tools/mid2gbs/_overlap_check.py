#!/usr/bin/env python3
"""Check note overlap between two MIDI tracks."""
import sys
import mido

mid = mido.MidiFile(sys.argv[1])
tpb = mid.ticks_per_beat
a_idx = int(sys.argv[2])
b_idx = int(sys.argv[3])

def get_notes(track_idx):
    notes = []
    t = 0
    for msg in mid.tracks[track_idx]:
        t += msg.time
        if msg.type == 'note_on' and msg.velocity > 0:
            notes.append(t)
    return sorted(set(notes))

ta = get_notes(a_idx)
tb = get_notes(b_idx)

sa, sb = set(ta), set(tb)

# Exact overlaps
exact = sa & sb
# Near overlaps (within 6 ticks = half a GBS unit at tpb=48)
near = [(a, b, abs(a-b)) for a in ta for b in tb if 0 < abs(a-b) <= 6]

# What fraction of tb notes conflict with ta (exact or near)?
conflicting_b = len({b for _, b, _ in near} | (sb & sa))
bpm = 120.0

print(f"Track {a_idx}: {len(ta)} notes")
print(f"Track {b_idx}: {len(tb)} notes")
print(f"Track {b_idx} entry: tick {tb[0]} = {tb[0]/tpb/2:.2f}s")
print(f"")
print(f"Exact same-tick overlaps: {len(exact)}")
print(f"Near overlaps (within 6 ticks): {len(near)}")
print(f"Track {b_idx} notes with any conflict: {conflicting_b} / {len(tb)} ({100*conflicting_b/len(tb):.0f}%)")
print(f"Track {b_idx} notes WITHOUT conflict: {len(tb) - conflicting_b} / {len(tb)} ({100*(len(tb)-conflicting_b)/len(tb):.0f}%)")
print()
print("First 20 exact overlaps:")
for t in sorted(exact)[:20]:
    print(f"  tick={t}  t={t/tpb/2:.3f}s")
