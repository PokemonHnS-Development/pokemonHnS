	.include "asm/macros.inc"

	.section .rodata
	.align 1

gbs_sfx_phonebeep_Ch5:
	gbs_switch 4
	duty_cycle 2
	square_note 20, 14, 8, 1803
	square_note 28, 0, 0, 0
	sound_ret

	.align 4
	.global gbs_sfx_phonebeep_Header
gbs_sfx_phonebeep_Header:
	.byte 1	@ NumTrks
	.byte 0	@ NumBlks
	.byte 0	@ Priority
	.byte 0	@ Reverb

	.int voicegroup000

	.int gbs_sfx_phonebeep_Ch5
