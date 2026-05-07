#!/usr/bin/env python3
"""
midi_to_gbs.py  –  Convert a MIDI .mid file to a GBS .s assembly file for pokemonHnS.

All MIDI files in sound/songs/midi/hgss_midi_for_gbs/ have TPB=48, so
--note-unit 12 is correct for all of them (1 GBS unit = 12 MIDI ticks = 1/16th note).

Usage:
    python3 tools/midi_to_gbs.py <file.mid> --name <symbol> [options] --out <output.s>

Example:
    python3 tools/midi_to_gbs.py sound/songs/midi/hgss_midi_for_gbs/mus_hg_gbs_cinnabar.mid \\
        --name gbs_cinnabar --ch1 0 --ch2 2 --duty2 3 --vibrato-extent 2 \\
        --out sound/songs/gbs/music/gbs_cinnabar.s

Inspect a MIDI file without generating output:
    python3 tools/midi_to_gbs.py <file.mid> --info

Batch regeneration of all songs:
    python3 tools/_regen_gbs.py

──────────────────────────────────────────────────────────────────────
Channel assignment
──────────────────────────────────────────────────────────────────────
Auto-assignment sorts tracks by average pitch (highest → Ch1, lowest → Ch3)
and detects noise by MIDI program 56/57/61. Always override manually using
--ch1/--ch2/--ch3/--ch4, since midi2agb-generated files emit all tracks
as program 0, defeating auto-detection.

    Ch1 (Square 1)  →  lead melody (highest avg pitch)
    Ch2 (Square 2)  →  harmony or counter-melody
    Ch3 (Wave)      →  bass line (lowest avg pitch)
    Ch4 (Noise)     →  percussion (merged from one or more tracks)

──────────────────────────────────────────────────────────────────────
Options
──────────────────────────────────────────────────────────────────────
  --name STR            GBS symbol prefix (e.g. gbs_cinnabar).
                        Defaults to filename with mus_hg_gbs_/mus_hg_ stripped.
  --out FILE            Output .s file path. Omit to print to stdout.
  --ch1 T[,T...]        Track index (or comma-separated indices) for Ch1 (Square 1). Multiple tracks are merged.
  --ch2 T[,T...]        Track index (or comma-separated indices) for Ch2 (Square 2). Multiple tracks are merged.
  --ch3 T[,T...]        Track index (or comma-separated indices) for Ch3 (Wave). Multiple tracks are merged.
  --ch4 T[,T...]        Comma-separated track indices for Ch4 (Noise). Merged.
  --note-unit N         MIDI ticks per GBS unit. Default 12 (TPB=48 standard).
  --duty1 N             Ch1 square wave duty cycle: 0=12.5% 1=25% 2=50% 3=75%.
                        Default 2 (50%).
  --duty2 N             Ch2 square wave duty cycle. Default 2 (50%).
                        Use 3 for a hollow/nasal tone (matches original cinnabar).
  --vibrato-extent N    Vibrato depth for both square channels. Default 1.
                        Use 2 for more pronounced vibrato (matches original cinnabar).
  --ch1-shift N         Semitones to transpose Ch1 (Square 1) notes up (+) or down (-).
                        Use multiples of 12 to shift by whole octaves (default 0).
  --ch2-vol N           Volume offset for Ch2 (Square 2). Added to the initial note_type volume
                        and every volume_envelope emitted for Ch2. Clamped to 1-15 (default 0).
  --ch2-shift N         Semitones to transpose Ch2 (Square 2) notes up (+) or down (-).
                        Use multiples of 12 to shift by whole octaves (default 0).
  --ch3-shift N         Semitones to transpose Ch3 (Wave) notes up (+) or down (-).
                        Use multiples of 12 to shift by whole octaves (default 0).
  --switch1 N           gbs_switch value used for Ch1 output (default 0 = Pulse 1).
                        gbs_sfx_readtext and most common SFX steal Pulse 1 (gbs_switch 4
                        → hw ch1 = gbs_switch 0). Use --switch1 1 (Pulse 2) to keep a
                        2-channel melody safe from sfx_readtext interruption. Use
                        --switch1 2 (Wave) for full isolation (e.g. newbarktown style).
  --switch2 N           gbs_switch value used for Ch2 output (default 1 = Pulse 2).
  --switch3 N           gbs_switch value used for Ch3 output (default 2 = Wave).
  --info                Print track table (program, notes, pitch range, avg, end tick)
                        and exit without generating output.

──────────────────────────────────────────────────────────────────────
How the emitter works
──────────────────────────────────────────────────────────────────────
Uses an event-stream approach: MIDI note events are iterated in order.
  - Gaps between note-off and next note-on → rest commands (preserves staccato).
  - Consecutive same-pitch notes with a gap → separate note commands (re-attacks).
  - Per-note velocity → volume_envelope commands when the GBS volume changes.
  - Octave commands emitted only when the octave changes.
  - Notes longer than 15 GBS units are split into chained note commands.  
"""

import sys
import mido
import argparse
import math
from collections import defaultdict

# ── pitch tables ──────────────────────────────────────────────────────────────
PITCH_NAMES = ['C_', 'Cs', 'D_', 'Ds', 'E_', 'F_', 'Fs', 'G_', 'Gs', 'A_', 'As', 'B_']

def midi_note_to_gbs(midi_pitch):
    """Return (octave, pitch_name) for a MIDI note number (0-127)."""
    octave = (midi_pitch // 12)
    # GBS octave: verified against se_select.s (midi 103 = Gn6 → octave 6)
    gbs_octave = octave - 2
    pitch = midi_pitch % 12
    name = PITCH_NAMES[pitch]
    gbs_octave = max(1, min(8, gbs_octave))
    return gbs_octave, name

def midi_vel_to_gbs_vol(vel):
    """Map MIDI velocity 0-127 to GBS volume 1-15."""
    return max(1, round(vel / 127 * 15))


# ── MIDI parsing ──────────────────────────────────────────────────────────────
def parse_midi_track(track, ticks_per_beat):
    """
    Return a list of (abs_tick, duration_ticks, midi_pitch, velocity) tuples,
    resolved into absolute time, with duration = note-off − note-on.
    Notes that are still on at track end are force-closed there.
    """
    notes = []
    pending = {}   # pitch → (abs_tick, velocity)
    abs_tick = 0
    max_tick = 0

    for msg in track:
        abs_tick += msg.time
        max_tick = abs_tick
        if msg.type == 'note_on' and msg.velocity > 0:
            pending[msg.note] = (abs_tick, msg.velocity)
        elif msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0):
            if msg.note in pending:
                on_tick, vel = pending.pop(msg.note)
                notes.append((on_tick, abs_tick - on_tick, msg.note, vel))

    # close any still-pending notes
    for pitch, (on_tick, vel) in pending.items():
        notes.append((on_tick, max_tick - on_tick, pitch, vel))

    notes.sort(key=lambda n: n[0])
    return notes, max_tick


def get_track_program(track):
    """Return the first program_change value seen in a track, or -1."""
    for msg in track:
        if msg.type == 'program_change':
            return msg.program
    return -1


# ── quantisation ─────────────────────────────────────────────────────────────
def quantise(ticks, unit):
    """Round ticks to nearest unit, minimum 1 unit."""
    return max(1, round(ticks / unit))


# ── GBS assembly emitter ──────────────────────────────────────────────────────
class GBSEmitter:
    def __init__(self, name, note_unit=12):
        self.name = name
        self.note_unit = note_unit
        self.lines = []

    def _w(self, text):
        self.lines.append(text)

    def header(self, midi_filename, tpb, bpm_hint):
        self._w(f'\t.include "asm/macros.inc"')
        self._w(f'')
        self._w(f'\t.section .rodata')
        self._w(f'\t.align 1')
        self._w(f'')
        self._w(f'@ Converted from {midi_filename}')
        self._w(f'@ BPM: {bpm_hint:.0f}  |  MIDI ticks/beat: {tpb}  |  GBS unit: {self.note_unit} ticks')
        self._w(f'@ Tick grid: 1 GBS unit = {self.note_unit} MIDI ticks')
        self._w(f'')

    def channel_header(self, ch, gbs_switch, bpm=120, is_noise=False,
                       duty=2, vibrato_extent=1, initial_vol=10, initial_fade=3):
        self._w(f'@ {"─"*60}')
        self._w(f'@ Ch{ch+1}: {"Square 1" if ch==0 else "Square 2" if ch==1 else "Wave" if ch==2 else "Noise"}')
        self._w(f'@ {"─"*60}')
        self._w(f'')
        self._w(f'{self.name}_Ch{ch+1}:')
        self._w(f'\tgbs_switch {gbs_switch}')
        if ch == 0:
            self._w(f'\ttempo {round(19074 / bpm)}')
            self._w(f'\tvolume 7, 7')
        if not is_noise:
            if ch <= 1:
                self._w(f'\tduty_cycle {duty}')
            if ch == 0:
                self._w(f'\tstereo_panning FALSE, TRUE')
            elif ch == 1:
                self._w(f'\tstereo_panning TRUE, FALSE')
            if ch <= 1:
                self._w(f'\tvibrato 16, {vibrato_extent}, 4')
            self._w(f'\tnote_type {self.note_unit}, {initial_vol}, {initial_fade}')
        else:
            self._w(f'\ttoggle_noise 0')
        self._w(f'')

    def emit_notes(self, notes, max_tick, ch_index, is_noise=False,
                   default_vol=10, default_fade=3, pitch_shift=0, vol_adjust=0):
        """
        Event-stream emitter: iterates MIDI events directly, preserving re-attacks
        and per-note velocity changes. Gaps between note-off and next note-on emit
        rests, giving accurate staccato/legato reproduction.
        """
        unit = self.note_unit
        name = self.name
        ch = ch_index + 1
        MAX_LEN = 15

        self._w(f'{name}_Ch{ch}.mainloop:')

        cur_octave = None
        cur_vol = max(1, min(15, default_vol + vol_adjust))
        cursor = 0  # current position in GBS units
        total_units = quantise(max_tick, unit)

        def emit_rest_run(length):
            remaining = length
            while remaining > 0:
                seg = min(remaining, MAX_LEN)
                self._w(f'\trest {seg}')
                remaining -= seg

        def emit_note_run(pname, length, tag=None):
            remaining = length
            first = True
            while remaining > 0:
                seg = min(remaining, MAX_LEN)
                comment = f'\t@ {tag}' if (tag and first) else ''
                if is_noise:
                    self._w(f'\tdrum_note 6, {seg}{comment}')
                else:
                    self._w(f'\tnote {pname}, {seg}{comment}')
                remaining -= seg
                first = False

        for note_event in sorted(notes, key=lambda n: n[0]):
            start, dur, pitch, vel = note_event[:4]
            track_tag = f'T{note_event[4]}' if len(note_event) > 4 else None
            q_start = round(start / unit)
            q_dur = max(1, round(dur / unit))

            # Handle overlap: if this note starts before cursor, trim it
            if q_start < cursor:
                q_dur = max(0, q_dur - (cursor - q_start))
                q_start = cursor
            if q_dur == 0:
                continue

            # Fill gap between cursor and note start with rests
            gap = q_start - cursor
            if gap > 0:
                emit_rest_run(gap)

            if not is_noise:
                # Emit volume_envelope if velocity-derived GBS vol changed
                new_vol = max(1, min(15, midi_vel_to_gbs_vol(vel) + vol_adjust))
                if new_vol != cur_vol:
                    self._w(f'\tvolume_envelope {new_vol}, {default_fade}')
                    cur_vol = new_vol

                # Emit octave command if changed
                oct_, pname = midi_note_to_gbs(pitch + pitch_shift)
                if oct_ != cur_octave:
                    self._w(f'\toctave {oct_}')
                    cur_octave = oct_
            else:
                pname = None

            emit_note_run(pname, q_dur, tag=track_tag)
            cursor = q_start + q_dur

        # Trailing rest to fill to end of loop
        trail = total_units - cursor
        if trail > 0:
            emit_rest_run(trail)

        self._w(f'')
        self._w(f'\tsound_loop 0, {name}_Ch{ch}.mainloop')
        self._w(f'')

    def footer(self, num_channels):
        name = self.name
        self._w(f'\t.align 4')
        self._w(f'\t.global {name}_Header')
        self._w(f'{name}_Header:')
        self._w(f'\t.byte {num_channels}\t@ NumTrks')
        self._w(f'\t.byte 0\t@ NumBlks')
        self._w(f'\t.byte 0\t@ Priority')
        self._w(f'\t.byte 0\t@ Reverb')
        self._w(f'')
        self._w(f'\t.int voicegroup000')
        self._w(f'')
        for i in range(num_channels):
            self._w(f'\t.int {name}_Ch{i+1}')

    def render(self):
        return '\n'.join(self.lines) + '\n'


# ── noise channel helper ──────────────────────────────────────────────────────
def merge_noise_tracks(track_notes_list, max_tick, unit):
    """Merge multiple percussion track note lists into a single hit timeline."""
    hit_slots = set()
    for notes in track_notes_list:
        for note in notes:
            slot = round(note[0] / unit)  # note[0] = abs_tick (works for 3- or 4-tuple)
            hit_slots.add(slot)
    total_units = math.ceil(max_tick / unit)
    return hit_slots, total_units


def emit_noise_channel(emitter, hit_slots, total_units):
    name = emitter.name
    ch = 4
    MAX_LEN = 15

    emitter._w(f'{name}_Ch{ch}.mainloop:')

    i = 0
    while i < total_units:
        if i in hit_slots:
            # Determine how long to sustain: 1 unit each
            emitter._w(f'\tdrum_note 6, 1')
            rest_len = 0
            j = i + 1
            while j < total_units and j not in hit_slots:
                rest_len += 1
                j += 1
            if rest_len > 0:
                # emit rests in chunks of MAX_LEN
                while rest_len > 0:
                    seg = min(rest_len, MAX_LEN)
                    emitter._w(f'\trest {seg}')
                    rest_len -= seg
            i = j
        else:
            # rest until next hit
            rest_len = 0
            j = i
            while j < total_units and j not in hit_slots:
                rest_len += 1
                j += 1
            while rest_len > 0:
                seg = min(rest_len, MAX_LEN)
                emitter._w(f'\trest {seg}')
                rest_len -= seg
            i = j

    emitter._w(f'')
    emitter._w(f'\tsound_loop 0, {name}_Ch{ch}.mainloop')
    emitter._w(f'')


# ── main ──────────────────────────────────────────────────────────────────────
def auto_assign_channels(midi_file):
    """
    Auto-assign MIDI tracks to GBS channels.
    Returns (ch1_idx, ch2_idx, ch3_idx, [ch4_idxs]) using 0-based track indices.
    Tracks with program 56/57/61 are noise. Others sorted by average pitch (high→low):
    highest → Ch1, next → Ch2, lowest → Ch3.
    """
    noise_programs = {56, 57, 61}
    melodic = []
    noise = []

    for i, track in enumerate(midi_file.tracks):
        if len(track) == 0:
            continue
        prog = get_track_program(track)
        notes, max_tick = parse_midi_track(track, midi_file.ticks_per_beat)
        if not notes:
            continue
        if prog in noise_programs:
            noise.append(i)
        else:
            avg_pitch = sum(n[2] for n in notes) / len(notes)
            melodic.append((avg_pitch, i))

    melodic.sort(reverse=True)  # highest avg pitch first

    ch1 = melodic[0][1] if len(melodic) > 0 else None
    ch2 = melodic[1][1] if len(melodic) > 1 else None
    ch3 = melodic[-1][1] if len(melodic) > 2 else None  # lowest pitch = bass
    return ch1, ch2, ch3, noise


def get_bpm(midi_file):
    for track in midi_file.tracks:
        for msg in track:
            if msg.type == 'set_tempo':
                return mido.tempo2bpm(msg.tempo)
    return 120.0


def main():
    ap = argparse.ArgumentParser(description='Convert MIDI to GBS .s')
    ap.add_argument('midi', help='Input .mid file')
    ap.add_argument('--name', default=None, help='GBS symbol name prefix (e.g. gbs_pokeathlonend)')
    ap.add_argument('--out',  default=None, help='Output .s file (default: stdout)')
    ap.add_argument('--ch1',  default=None, help='Track index or comma-separated indices for Ch1 (Square 1)')
    ap.add_argument('--ch2',  default=None, help='Track index or comma-separated indices for Ch2 (Square 2)')
    ap.add_argument('--ch3',  default=None, help='Track index or comma-separated indices for Ch3 (Wave)')
    ap.add_argument('--ch4',  default=None, help='Comma-separated track indices for noise')
    ap.add_argument('--note-unit', type=int, default=12, dest='note_unit',
                    help='MIDI ticks per GBS unit (default 12)')
    ap.add_argument('--duty1', type=int, default=2,
                    help='Duty cycle for Ch1 square wave (0-3, default 2 = 50%%)')
    ap.add_argument('--duty2', type=int, default=2,
                    help='Duty cycle for Ch2 square wave (0-3, default 2 = 50%%)')
    ap.add_argument('--vibrato-extent', type=int, default=1, dest='vibrato_extent',
                    help='Vibrato depth for square channels (default 1)')
    ap.add_argument('--fade', type=int, default=3,
                    help='Envelope fade speed for note_type and volume_envelope (0-7, default 3; '
                         'higher = slower decay / more sustain)')
    ap.add_argument('--ch1-shift', type=int, default=0, dest='ch1_shift',
                    help='Semitones to transpose Ch1 (Square 1) notes up (+) or down (-). '
                         'Use multiples of 12 to shift by whole octaves (default 0)')
    ap.add_argument('--ch2-vol', type=int, default=0, dest='ch2_vol',
                    help='Volume offset for Ch2 (integer added to note_type and every '
                         'volume_envelope; clamped to 1-15, default 0)')
    ap.add_argument('--ch2-shift', type=int, default=0, dest='ch2_shift',
                    help='Semitones to transpose Ch2 (Square 2) notes up (+) or down (-). '
                         'Use multiples of 12 to shift by whole octaves (default 0)')
    ap.add_argument('--ch3-shift', type=int, default=0, dest='ch3_shift',
                    help='Semitones to transpose Ch3 (Wave) notes up (+) or down (-). '
                         'Use multiples of 12 to shift by whole octaves (default 0)')
    ap.add_argument('--switch1', type=int, default=0, dest='switch1',
                    help='gbs_switch value for Ch1 (default 0 = Pulse 1). '
                         'Use 1 (Pulse 2) to prevent sfx_readtext from cutting the lead melody. '
                         'Use 2 (Wave) for maximum isolation from common SFX.')
    ap.add_argument('--switch2', type=int, default=1, dest='switch2',
                    help='gbs_switch value for Ch2 (default 1 = Pulse 2).')
    ap.add_argument('--switch3', type=int, default=2, dest='switch3',
                    help='gbs_switch value for Ch3 (default 2 = Wave).')
    ap.add_argument('--info', action='store_true', help='Print track info and exit')
    args = ap.parse_args()

    mid = mido.MidiFile(args.midi)
    tpb = mid.ticks_per_beat
    bpm = get_bpm(mid)

    if args.info or True:  # always print info
        print(f'File: {args.midi}')
        print(f'Type: {mid.type}  |  Tracks: {len(mid.tracks)}  |  TPB: {tpb}  |  BPM: {bpm:.1f}')
        print()
        for i, track in enumerate(mid.tracks):
            notes, max_tick = parse_midi_track(track, tpb)
            prog = get_track_program(track)
            if notes:
                pitches = [n[2] for n in notes]
                print(f'  Track {i:2d}: {track.name!r:30s}  prog={prog:3d}  '
                      f'notes={len(notes):4d}  '
                      f'pitch={min(pitches)}-{max(pitches)}  '
                      f'avg={sum(pitches)/len(pitches):.1f}  '
                      f'end={max_tick}t')
            else:
                print(f'  Track {i:2d}: {track.name!r:30s}  prog={prog:3d}  (no notes)')

    if args.info:
        return

    # Derive output name from filename if not specified
    import os
    if args.name is None:
        base = os.path.splitext(os.path.basename(args.midi))[0]
        args.name = 'gbs_' + base.replace('mus_hg_gbs_', '').replace('mus_hg_', '')

    # Channel assignment
    def parse_ch_arg(val, auto_val):
        """Parse a track arg that may be int or comma-separated list."""
        if val is None:
            return auto_val
        parts = [int(x) for x in str(val).split(',')]
        return parts[0] if len(parts) == 1 else parts

    auto_ch1, auto_ch2, auto_ch3, auto_ch4 = auto_assign_channels(mid)
    ch1_idx = parse_ch_arg(args.ch1, auto_ch1)
    ch2_idx = parse_ch_arg(args.ch2, auto_ch2)
    ch3_idx = parse_ch_arg(args.ch3, auto_ch3)
    ch4_idxs = ([int(x) for x in args.ch4.split(',')] if args.ch4
                else auto_ch4)

    unit = args.note_unit

    print(f'\nChannel assignment:')
    print(f'  Ch1 (Square1) → track {ch1_idx}')
    print(f'  Ch2 (Square2) → track {ch2_idx}')
    print(f'  Ch3 (Wave)    → track {ch3_idx}')
    print(f'  Ch4 (Noise)   → tracks {ch4_idxs}')
    print(f'  GBS unit = {unit} ticks')

    emitter = GBSEmitter(args.name, note_unit=unit)
    midi_basename = os.path.basename(args.midi)
    emitter.header(midi_basename, tpb, bpm)

    # Parse all needed tracks
    def get_notes(idx):
        if idx is None:
            return [], 0
        if isinstance(idx, list):
            merged, max_t = [], 0
            for i in idx:
                n, mt = parse_midi_track(mid.tracks[i], tpb)
                merged.extend((start, dur, pitch, vel, i) for start, dur, pitch, vel in n)
                max_t = max(max_t, mt)
            merged.sort(key=lambda n: n[0])
            return merged, max_t
        notes, max_tick = parse_midi_track(mid.tracks[idx], tpb)
        return notes, max_tick

    ch1_notes, ch1_max = get_notes(ch1_idx)
    ch2_notes, ch2_max = get_notes(ch2_idx)
    ch3_notes, ch3_max = get_notes(ch3_idx)
    ch4_notes_list = [get_notes(i)[0] for i in ch4_idxs]
    all_max = max(ch1_max, ch2_max, ch3_max,
                  *(get_notes(i)[1] for i in ch4_idxs) if ch4_idxs else [0])

    num_channels = sum(1 for n in [ch1_notes, ch2_notes, ch3_notes] if n) + (1 if ch4_idxs else 0)

    def first_vol(notes):
        """GBS volume derived from first note's velocity, or default 10."""
        return midi_vel_to_gbs_vol(notes[0][3]) if notes else 10

    # Ch1
    if ch1_notes:
        emitter.channel_header(0, args.switch1, bpm=bpm, duty=args.duty1,
                               vibrato_extent=args.vibrato_extent,
                               initial_vol=first_vol(ch1_notes),
                               initial_fade=args.fade)
        emitter.emit_notes(ch1_notes, all_max, 0,
                           default_vol=first_vol(ch1_notes),
                           default_fade=args.fade,
                           pitch_shift=args.ch1_shift)

    # Ch2
    if ch2_notes:
        ch2_initial_vol = max(1, min(15, first_vol(ch2_notes) + args.ch2_vol))
        emitter.channel_header(1, args.switch2, duty=args.duty2,
                               vibrato_extent=args.vibrato_extent,
                               initial_vol=ch2_initial_vol,
                               initial_fade=args.fade)
        emitter.emit_notes(ch2_notes, all_max, 1,
                           default_vol=first_vol(ch2_notes),
                           default_fade=args.fade,
                           pitch_shift=args.ch2_shift,
                           vol_adjust=args.ch2_vol)

    # Ch3
    if ch3_notes:
        emitter.channel_header(2, args.switch3, initial_vol=first_vol(ch3_notes),
                               initial_fade=args.fade)
        emitter.emit_notes(ch3_notes, all_max, 2,
                           default_vol=first_vol(ch3_notes),
                           default_fade=args.fade,
                           pitch_shift=args.ch3_shift)

    # Ch4
    if ch4_idxs and ch4_notes_list:
        emitter.channel_header(3, 3, is_noise=True)
        hit_slots, total_units = merge_noise_tracks(ch4_notes_list, all_max, unit)
        emitter._w(f'{args.name}_Ch4.mainloop:')
        emit_noise_channel_inline(emitter, hit_slots, total_units, args.name)

    emitter.footer(num_channels)

    output = emitter.render()
    if args.out:
        with open(args.out, 'w') as f:
            f.write(output)
        print(f'\nWrote {args.out}')
    else:
        print('\n' + '='*60)
        print(output)


def emit_noise_channel_inline(emitter, hit_slots, total_units, name):
    MAX_LEN = 15
    ch = 4
    emitter._w(f'\tdrum_speed {emitter.note_unit}')
    i = 0
    while i < total_units:
        if i in hit_slots:
            emitter._w(f'\tdrum_note 6, 1')
            j = i + 1
            rest_len = 0
            while j < total_units and j not in hit_slots:
                rest_len += 1
                j += 1
            while rest_len > 0:
                seg = min(rest_len, MAX_LEN)
                emitter._w(f'\trest {seg}')
                rest_len -= seg
            i = j
        else:
            rest_len = 0
            j = i
            while j < total_units and j not in hit_slots:
                rest_len += 1
                j += 1
            while rest_len > 0:
                seg = min(rest_len, MAX_LEN)
                emitter._w(f'\trest {seg}')
                rest_len -= seg
            i = j
    emitter._w(f'')
    emitter._w(f'\tsound_loop 0, {name}_Ch{ch}.mainloop')
    emitter._w(f'')


if __name__ == '__main__':
    main()
