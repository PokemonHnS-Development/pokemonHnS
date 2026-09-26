MtPyre_6F_MapScripts::
	.byte 0

MtPyre_6F_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_6F_EventScript_RematchValerie
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_6F_EventScript_RegisterValerie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VALERIE_1
	release
	end

MtPyre_6F_EventScript_RematchValerie::
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_EventScript_Cedric::
	trainerbattle_single TRAINER_GRUNT_8, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_Text_ValerieIntro:
	.string "Cuando estoy aquí...\n"
	.string "un poder curioso fluye en mí...$"

MtPyre_6F_Text_ValerieDefeat:
	.string "El poder se está agotando...$"

MtPyre_6F_Text_ValeriePostBattle:
	.string "Tal vez el poder sea de los espíritus\n"
	.string "de POKéMON que duermen aquí...$"

MtPyre_6F_Text_ValerieRegister:
	.string "Fufufu... Perdí el combate, pero...\n"
	.string "tengo esta pequeña habilidad...\p"
	.string "Sin tocar jamás tu POKéNAV...\n"
	.string "¡Hiyah!$"

MtPyre_6F_Text_ValerieRematchIntro:
	.string "Detrás de ti...\n"
	.string "¿Qué es eso...$"

MtPyre_6F_Text_ValerieRematchDefeat:
	.string "Algo se desvaneció...$"

MtPyre_6F_Text_ValeriePostRematch:
	.string "Los POKéMON que descansan aquí...\n"
	.string "a veces, juegan...$"

MtPyre_6F_Text_CedricIntro:
	.string "¿Perdiste el rumbo?\n"
	.string "¡No temas, que yo estoy aquí!$"

MtPyre_6F_Text_CedricDefeat:
	.string "¿No estabas perdido?$"

MtPyre_6F_Text_CedricPostBattle:
	.string "Pensé que un ENTRENADOR perdido\n"
	.string "estaría paniqueado y sería fácil.\p"
	.string "Fue sucio, no lo haré de nuevo…$"

