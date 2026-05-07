#!/usr/bin/env python3
"""One-shot batch regeneration of all GBS music files."""
import subprocess, sys, os
os.chdir(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))

M = "sound/songs/midi/hgss_midi_for_gbs"
N = "sound/songs/midi"
O = "sound/songs/gbs/music"
PY = sys.executable

"""
You may be wondering why I have `--switch1 1 --switch2 0 --ch3-shift=12` for nearly every song:
- The ch3 Bass that comes from the track in the MIDI files is often 1 octave too low-pitched when comparing 
  the GBS output in game to the original MIDI files. By using `--ch3-shift=12`, the ch3 Bass will be shifted up by 1 octave.
- The way SFX work using GBS, is that when they are played they play on Ch1, If the melody is on Ch1, then 
  the SFX will cut out the melody when they play. I could just put melody on Ch2, but I prefer the melody being 
  on Ch1 in the generated file, so by using `--switch1 1 --switch2 0`, Ch1 will play using Ch2 instead, and vice versa, 
  causing the SFX to interrupt the Ch2 harmony/supporting instead of the Ch1 melody.
  
So far I've only converted HGSS GB Sounds, but if I convert more songs in the future that aren't 'GB Sounds', I may not 
want to use these flags for all of them, so I specify them per-song instead of as a global default.
"""

jobs = [
    # If a song is commented out probably don't regenerate it, since it may have been hand-tweaked after generation.
    # (f"{M}/cinnabar.mid",           "gbs_hg_cinnabar",      "--ch1 0 --ch2 1 --duty2 3 --vibrato-extent 2 --fade 7 --switch1 1 --switch2 0"),
    # (f"{M}/pokeathlon_before.mid",  "gbs_hg_pokeathlonbefore",  "--ch1 0 --ch2 1 --ch3 2 --ch4 3,4,5 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/pokeathlon_end.mid",     "gbs_hg_pokeathlonend",     "--ch1 0 --ch2 4,1 --ch3 2 --ch4 5,6,7 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/pokeathlon_event.mid",   "gbs_hg_pokeathlonevent",   "--ch1 0 --ch2 2,3 --ch3 1 --ch4 5,6,7,8 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/pokeathlon_finals.mid",  "gbs_hg_pokeathlonfinals",  "--ch1 4,0 --ch2 6,3,1 --ch3 2 --ch4 8,9,10 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/pokeathlon_lobby.mid",   "gbs_hg_pokeathlonlobby",   "--ch1 0,5 --ch2 1 --ch3 2 --ch4 3,4 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/pokeathlon_results.mid", "gbs_hg_pokeathlonresults", "--ch1 0 --ch2 1 --ch3 2 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/pokeathlon_start.mid",   "gbs_hg_pokeathlonstart",   "--ch1 0,3,6 --ch2 1,4 --ch3 2 --ch4 5,7,8,9 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/route47.mid",            "gbs_hg_route47",           "--ch1 0,3,4 --ch2 2 --ch3 5 --ch4 6 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/safari_zone.mid",        "gbs_hg_safarizone",        "--ch1 0 --ch2 2 --ch3 7 --ch4 8,9 --ch3-shift 24 --switch1 1 --switch2 0"),
    # (f"{M}/safari_zone_gate.mid",   "gbs_hg_safarizonegate",    "--ch1 0,2 --ch2 7 --ch3 5,3 --ch4 6,8 --ch2-vol=-5 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/route24.mid",            "gbs_hg_route24",           "--ch1 0 --ch2 1,4 --ch3 2 --ch4 3,5,6 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/cerulean.mid",           "gbs_hg_cerulean",          "--ch1 0,4 --ch2 1,6 --ch3 2 --ch4 5,7,8,9 --duty2 3 --vibrato-extent 2 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/mt_moon_square.mid",     "gbs_hg_mt_moon_square",    "--ch1 0 --ch2 1 --switch1 1 --switch2 0"),
    # (f"{M}/poke_mart.mid",          "gbs_hg_poke_mart",         "--ch1 0,4 --ch2 1 --ch3 2 --ch4 3 --switch1 1 --switch2 0 --ch3-shift=12"),
    # (f"{M}/end.mid",                "gbs_hg_end",               "--ch1 0 --ch2 1 --switch1 1 --switch2 0"),
    # (f"{M}/viridian_forest.mid",    "gbs_hg_viridian_forest",   "--ch1 0,4,5 --ch2 1,6,9,11 --ch3 3,7,8 --ch4 10 --switch1 1 --switch2 0"),
    # TESTING Non GB Sounds track:: (f"{M}/SEQ_GS_PT_VICTORY.mid",  "gbs_hg_n_pt_victory",      "--ch1 0,1 --ch2 7,5 --ch3 2 --ch4 3,4 --switch1 1 --switch2 0 --ch3-shift=24"),
] 

ok = 0
for midi, name, flags in jobs:
    cmd = [PY, "tools/mid2gbs/midi_to_gbs.py", midi, "--name", name] + flags.split() + ["--note-unit", "12", "--out", f"{O}/{name}.s"]
    r = subprocess.run(cmd, capture_output=True, text=True)
    lines = [l for l in (r.stdout + r.stderr).splitlines() if l.strip()]
    msg = lines[-1] if lines else "(no output)"
    print(msg)
    if r.returncode == 0:
        ok += 1

print(f"\n{ok}/{len(jobs)} files written.")
