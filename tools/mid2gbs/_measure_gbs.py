#!/usr/bin/env python3
"""Measure the total GBS-unit duration of each channel in a .s file."""
import re, sys

path = sys.argv[1] if len(sys.argv) > 1 else "sound/songs/gbs/music/gbs_hg_pokeathlonstart.s"

with open(path) as f:
    text = f.read()

# Split into per-channel blocks by mainloop label
blocks = re.split(r'(?=\w+_Ch\d+\.mainloop:)', text)

for block in blocks:
    m = re.match(r'(\w+_Ch\d+)\.mainloop:', block)
    if not m:
        continue
    label = m.group(1)
    total = 0
    for line in block.splitlines():
        line = line.split('@')[0].strip()  # strip comments
        # note X, N  |  rest N  |  drum_note X, N
        nm = re.match(r'note\s+\w+,\s*(\d+)', line)
        rm = re.match(r'rest\s+(\d+)', line)
        dm = re.match(r'drum_note\s+\d+,\s*(\d+)', line)
        if nm:
            total += int(nm.group(1))
        elif rm:
            total += int(rm.group(1))
        elif dm:
            total += int(dm.group(1))
    print(f"{label}: {total} GBS units  ({total / 16:.2f} bars of 4/4 at 1/16th grid)")
