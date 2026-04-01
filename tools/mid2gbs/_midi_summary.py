#!/usr/bin/env python3
"""Show one summary line per track for a MIDI: track index, first note time, first pitch, pitch range, note count."""
import mido, sys, glob, os

note_names = ['C','C#','D','D#','E','F','F#','G','G#','A','A#','B']

def analyze(path):
    mid = mido.MidiFile(path)
    tempo_us = 500000
    for track in mid.tracks:
        for msg in track:
            if msg.type == 'set_tempo':
                tempo_us = msg.tempo
                break
    bpm = 60_000_000 / tempo_us
    print(f"{os.path.basename(path)}  BPM={bpm:.0f}  tracks={len(mid.tracks)}")
    for i, track in enumerate(mid.tracks):
        abs_tick = 0
        pitches = []
        first_tick = None
        for msg in track:
            abs_tick += msg.time
            if msg.type == 'note_on' and msg.velocity > 0:
                pitches.append(msg.note)
                if first_tick is None:
                    first_tick = abs_tick
        if not pitches:
            print(f"  [{i}] (empty)")
            continue
        first_s = mido.tick2second(first_tick, mid.ticks_per_beat, tempo_us)
        lo = min(pitches); hi = max(pitches)
        lo_n = f"{note_names[lo%12]}{lo//12-1}"; hi_n = f"{note_names[hi%12]}{hi//12-1}"
        first_n = f"{note_names[pitches[0]%12]}{pitches[0]//12-1}"
        print(f"  [{i}] first={first_s:.2f}s  first_note={first_n}  range={lo_n}-{hi_n}  count={len(pitches)}")
    print()

paths = sys.argv[1:] if len(sys.argv) > 1 else sorted(glob.glob("sound/songs/midi/hgss_midi_for_gbs/*.mid"))
for p in paths:
    analyze(p)
