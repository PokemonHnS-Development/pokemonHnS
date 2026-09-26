Route110_TrickHousePuzzle4_MapScripts::
	.byte 0

Route110_TrickHousePuzzle4_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0, Route110_TrickHousePuzzle4_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle4_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle4_EventScript_Cora::
	trainerbattle_single TRAINER_GRUNT_28, Route110_TrickHousePuzzle4_Text_CoraIntro, Route110_TrickHousePuzzle4_Text_CoraDefeat
	msgbox Route110_TrickHousePuzzle4_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Yuji::
	trainerbattle_single TRAINER_YUJI, Route110_TrickHousePuzzle4_Text_YujiIntro, Route110_TrickHousePuzzle4_Text_YujiDefeat
	msgbox Route110_TrickHousePuzzle4_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA, Route110_TrickHousePuzzle4_Text_PaulaIntro, Route110_TrickHousePuzzle4_Text_PaulaDefeat
	msgbox Route110_TrickHousePuzzle4_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} anotó el código secreto\n"
	.string "en la puerta.\p"
	.string "“TRICK MASTER es genial”.\n"
	.string "… … … … … … … …\p"
	.string "¡La cerradura se abrió!$"

Route110_TrickHousePuzzle4_Text_CoraIntro:
	.string "Es mucha molestia pensar en esto.\n"
	.string "¡Solo quería luchar!$"

Route110_TrickHousePuzzle4_Text_CoraDefeat:
	.string "Aunque perdí, ¡luchar sigue siendo\n"
	.string "lo que más me gusta!$"

Route110_TrickHousePuzzle4_Text_CoraPostBattle:
	.string "¿No estás de acuerdo? Irías a\n"
	.string "cualquier lugar si hay ENTRENADORES.$"

Route110_TrickHousePuzzle4_Text_YujiIntro:
	.string "¡Je! ¡Rocas como estas las quito\n"
	.string "con un solo dedo!$"

Route110_TrickHousePuzzle4_Text_YujiDefeat:
	.string "Puedo empujar rocas, pero no puedo\n"
	.string "resolver el acertijo…$"

Route110_TrickHousePuzzle4_Text_YujiPostBattle:
	.string "No basta con ser fuerte…\n"
	.string "Hay que usar la cabeza. ¡Sé listo!$"

Route110_TrickHousePuzzle4_Text_PaulaIntro:
	.string "La TRICK HOUSE es cada vez más\n"
	.string "complicada, ¿verdad?$"

Route110_TrickHousePuzzle4_Text_PaulaDefeat:
	.string "¡Aaak!$"

Route110_TrickHousePuzzle4_Text_PaulaPostBattle:
	.string "¿Alguien ha llegado al final?$"

