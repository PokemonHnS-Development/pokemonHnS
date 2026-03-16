	.include "asm/macros.inc"

	.section .rodata
	.align 1

gbs_sfx_phoneclick_Ch5:
	gbs_switch 4
	duty_cycle 2
	square_note 4, 11, 8, 1915
	square_note 2, 2, 1, 1915
	square_note 16, 0, 0, 0
	sound_ret

	.align 4
	.global gbs_sfx_phoneclick_Header
gbs_sfx_phoneclick_Header:
	.byte 1	@ NumTrks
	.byte 0	@ NumBlks
	.byte 0	@ Priority
	.byte 0	@ Reverb

	.int voicegroup000

	.int gbs_sfx_phoneclick_Ch5
