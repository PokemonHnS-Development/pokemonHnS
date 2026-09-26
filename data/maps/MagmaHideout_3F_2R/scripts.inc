MagmaHideout_3F_2R_MapScripts::
	.byte 0

MagmaHideout_3F_2R_EventScript_Grunt10::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_10, MagmaHideout_3F_2R_Text_Grunt10Intro, MagmaHideout_3F_2R_Text_Grunt10Defeat
	msgbox MagmaHideout_3F_2R_Text_Grunt10PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_2R_Text_Grunt10Intro:
	.string "Entiendo todo lo que dice nuestro\n"
	.string "líder. ¿Pero sabes qué?\p"
	.string "Hacer cosas como despertar a un\n"
	.string "POKéMON antiguo y robarle\l"
	.string "el METEORITO a alguien...\p"
	.string "Creo que vamos demasiado lejos.\n"
	.string "¿Tú qué opinas?$"

MagmaHideout_3F_2R_Text_Grunt10Defeat:
	.string "Sí, creo que estamos haciendo algo\n"
	.string "mal de alguna manera.$"

MagmaHideout_3F_2R_Text_Grunt10PostBattle:
	.string "Perder contra ti me aclaró la mente.\p"
	.string "La próxima vez que vea al líder,\n"
	.string "le preguntaré sobre lo que hacemos.$"

