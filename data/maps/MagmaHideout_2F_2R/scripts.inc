MagmaHideout_2F_2R_MapScripts::
	.byte 0

MagmaHideout_2F_2R_EventScript_Grunt15::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_15, MagmaHideout_2F_2R_Text_Grunt15Intro, MagmaHideout_2F_2R_Text_Grunt15Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt15PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_6, MagmaHideout_2F_2R_Text_Grunt6Intro, MagmaHideout_2F_2R_Text_Grunt6Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_7, MagmaHideout_2F_2R_Text_Grunt7Intro, MagmaHideout_2F_2R_Text_Grunt7Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt7PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_8, MagmaHideout_2F_2R_Text_Grunt8Intro, MagmaHideout_2F_2R_Text_Grunt8Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_Text_Grunt15Intro:
	.string "No tengo nada contra ti.\n"
	.string "¡Solo sigo órdenes!$"

MagmaHideout_2F_2R_Text_Grunt15Defeat:
	.string "Puede que haya perdido, pero…$"

MagmaHideout_2F_2R_Text_Grunt15PostBattle:
	.string "¡Cavamos algo increíble!\n"
	.string "¡Y tenemos el ORBE AZUL!\p"
	.string "Solo falta que nuestro líder…\n"
	.string "Fufufu… ¡Fwahahaha!$"

MagmaHideout_2F_2R_Text_Grunt6Intro:
	.string "No soporto el calor. Debí\n"
	.string "unirme al TEAM AQUA…$"

MagmaHideout_2F_2R_Text_Grunt6Defeat:
	.string "Sí, puede que no sea apto para\n"
	.string "el TEAM MAGMA…$"

MagmaHideout_2F_2R_Text_Grunt6PostBattle:
	.string "¿No extrañas el mar estando\n"
	.string "en un lugar como este?$"

MagmaHideout_2F_2R_Text_Grunt7Intro:
	.string "A veces se oyen temblores.\p"
	.string "¿Será el volcán agitándose?\n"
	.string "¿O será GROU…\p"
	.string "¡Ups!\n"
	.string "¡No, no, olvida lo que dije!$"

MagmaHideout_2F_2R_Text_Grunt7Defeat:
	.string "Eres un luchador ardiente.\n"
	.string "¡Como un volcán!$"

MagmaHideout_2F_2R_Text_Grunt7PostBattle:
	.string "Tuviste suerte esta vez,\n"
	.string "pero eso no importa.\p"
	.string "¡La meta del TEAM MAGMA está\n"
	.string "por cumplirse!$"

MagmaHideout_2F_2R_Text_Grunt8Intro:
	.string "Uno de los nuestros estaba loco\n"
	.string "porque perdió su EMBLEMA MAGMA…\p"
	.string "¡Espera un momento!\n"
	.string "¿Fuiste tú quien lo encontró?$"

MagmaHideout_2F_2R_Text_Grunt8Defeat:
	.string "Me cuesta creer esto…$"

MagmaHideout_2F_2R_Text_Grunt8PostBattle:
	.string "Tengo el presentimiento de que\n"
	.string "nuestro plan terminará en fracaso…$"

