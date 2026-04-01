import mido, sys

path = sys.argv[1] if len(sys.argv) > 1 else "sound/songs/midi/ref_for_new_gbs_sounds/mus_hg_gbs_safari_zone.mid"
track_idx = int(sys.argv[2]) if len(sys.argv) > 2 else None
n_notes = int(sys.argv[3]) if len(sys.argv) > 3 else 20

mid = mido.MidiFile(path)
print(f"ticks/beat: {mid.ticks_per_beat}")

tempo_us = 500000
for track in mid.tracks:
    for msg in track:
        if msg.type == 'set_tempo':
            tempo_us = msg.tempo
            break
print(f"BPM: {60_000_000 / tempo_us:.1f}  tempo_us: {tempo_us}")
print(f"Tracks: {len(mid.tracks)}")
for i, t in enumerate(mid.tracks):
    print(f"  [{i}] {t.name}")

note_names = ['C','C#','D','D#','E','F','F#','G','G#','A','A#','B']

tracks_to_show = [track_idx] if track_idx is not None else range(len(mid.tracks))
for i in tracks_to_show:
    track = mid.tracks[i]
    print(f"\n--- Track {i}: {track.name} ---")
    abs_tick = 0
    count = 0
    pending = {}  # note -> on_tick
    events = []
    for msg in track:
        abs_tick += msg.time
        if msg.type == 'note_on' and msg.velocity > 0:
            pending[msg.note] = abs_tick
        elif msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0):
            on_tick = pending.pop(msg.note, abs_tick)
            dur_ticks = abs_tick - on_tick
            t_s = mido.tick2second(on_tick, mid.ticks_per_beat, tempo_us)
            name = note_names[msg.note % 12]
            octave = msg.note // 12 - 1
            events.append((on_tick, t_s, name, octave, msg.note, dur_ticks))
    events.sort()
    for on_tick, t_s, name, octave, pitch, dur in events[:n_notes]:
        dur_s = mido.tick2second(dur, mid.ticks_per_beat, tempo_us)
        print(f"  t={t_s:.3f}s  tick={on_tick:5d}  {name}{octave} (midi {pitch:3d})  dur={dur_ticks} ticks / {dur_s:.3f}s")
