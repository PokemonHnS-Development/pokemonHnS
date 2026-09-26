Route110_TrickHousePuzzle6_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle6_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHousePuzzle6_OnWarp
	.byte 0

Route110_TrickHousePuzzle6_OnTransition:
	special RotatingGate_InitPuzzle
	end

Route110_TrickHousePuzzle6_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, Route110_TrickHousePuzzle6_EventScript_InitPuzzle
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_5
Route110_TrickHousePuzzle6_EventScript_InitPuzzle::
	special RotatingGate_InitPuzzleAndGraphics
	end

Route110_TrickHousePuzzle6_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_6_STATE, 0, Route110_TrickHousePuzzle6_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle6_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_6_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle6_EventScript_Sophia::
	trainerbattle_single TRAINER_SOPHIA, Route110_TrickHousePuzzle6_Text_SophiaIntro, Route110_TrickHousePuzzle6_Text_SophiaDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SophiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Benny::
	trainerbattle_single TRAINER_BENNY, Route110_TrickHousePuzzle6_Text_BennyIntro, Route110_TrickHousePuzzle6_Text_BennyDefeat
	msgbox Route110_TrickHousePuzzle6_Text_BennyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Sebastian::
	trainerbattle_single TRAINER_SEBASTIAN, Route110_TrickHousePuzzle6_Text_SebastianIntro, Route110_TrickHousePuzzle6_Text_SebastianDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SebastianPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} anotó el código secreto\n"
	.string "en la puerta.\p"
	.string "“TRICK MASTER es mi vida”.\n"
	.string "… … … … … … … …\p"
	.string "¡La cerradura se abrió!$"

Route110_TrickHousePuzzle6_Text_SophiaIntro:
	.string "Al oír que había una casa extraña,\n"
	.string "tenía que venir a verla.$"

Route110_TrickHousePuzzle6_Text_SophiaDefeat:
	.string "¡He encontrado un TRAINER fuerte!$"

Route110_TrickHousePuzzle6_Text_SophiaPostBattle:
	.string "Me divierto mucho explorando\n"
	.string "este lugar.\p"
	.string "¡Es un desafío que vale la pena\n"
	.string "repetir!$"

Route110_TrickHousePuzzle6_Text_BennyIntro:
	.string "Tal vez mi POKéMON ave pueda\n"
	.string "volar sobre el muro…$"

Route110_TrickHousePuzzle6_Text_BennyDefeat:
	.string "¡Gwaaah! ¡Lo arruiné!$"

Route110_TrickHousePuzzle6_Text_BennyPostBattle:
	.string "Ehehehe… Creo que perdí por\n"
	.string "intentar hacer trampa.$"

Route110_TrickHousePuzzle6_Text_SebastianIntro:
	.string "Me marean estas puertas\n"
	.string "giratorias…$"

Route110_TrickHousePuzzle6_Text_SebastianDefeat:
	.string "Todo da vueltas y vueltas.\n"
	.string "Ya no puedo más...$"

Route110_TrickHousePuzzle6_Text_SebastianPostBattle:
	.string "No pareces afectado en absoluto.\n"
	.string "¿O es que finges calma?$"

