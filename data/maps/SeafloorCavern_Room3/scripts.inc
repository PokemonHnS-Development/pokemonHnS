SeafloorCavern_Room3_MapScripts::
	.byte 0

SeafloorCavern_Room3_EventScript_Shelly::
	trainerbattle_single TRAINER_GRANT, SeafloorCavern_Room3_Text_ShellyIntro, SeafloorCavern_Room3_Text_ShellyDefeat
	msgbox SeafloorCavern_Room3_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_EventScript_Grunt5::
	trainerbattle_single TRAINER_VANCE, SeafloorCavern_Room3_Text_Grunt5Intro, SeafloorCavern_Room3_Text_Grunt5Defeat
	msgbox SeafloorCavern_Room3_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_Text_ShellyIntro:
	.string "¡Ahajajaja!\p"
	.string "¿Cómo llegaste aquí sin\n"
	.string "un submarino?\l"
	.string "¡Qué niño tan impresionante!\p"
	.string "Pero... no puedo dejar que\n"
	.string "estés entrometiéndote aquí.\p"
	.string "Y quiero venganza por lo que\n"
	.string "pasó en el INST. CLIMA...\p"
	.string "¡Te daré una probadita de dolor!\n"
	.string "¡Resígnate a ello!$"

SeafloorCavern_Room3_Text_ShellyDefeat:
	.string "¡Ahajajaja!\p"
	.string "¡Ay!$"

SeafloorCavern_Room3_Text_ShellyPostBattle:
	.string "¡Ahajajaja!\n"
	.string "Eres demasiado fuerte.\p"
	.string "Es una pena que no seas\n"
	.string "miembro del TEAM AQUA.\p"
	.string "Podrías haber disfrutado el fabuloso\n"
	.string "mundo que el JEFE prometió\l"
	.string "si fueras uno de nosotros…$"

SeafloorCavern_Room3_Text_Grunt5Intro:
	.string "Para hacer realidad nuestro sueño\n"
	.string "necesitamos el poder POKéMON.\p"
	.string "Pero entrometidos como tú usan\n"
	.string "el poder de los POKéMON para\l"
	.string "molestarnos ¡hasta en un lugar así!\p"
	.string "¡La vida no funciona como\n"
	.string "queremos!$"

SeafloorCavern_Room3_Text_Grunt5Defeat:
	.string "¡Gwah!$"

SeafloorCavern_Room3_Text_Grunt5PostBattle:
	.string "Sabes, no nos atrevemos a cuestionar\n"
	.string "los motivos de nuestro líder.\p"
	.string "Pero tú, un simple mocoso,\n"
	.string "te enfrentas a nuestro JEFE.\p"
	.string "Tal vez...\n"
	.string "debes ser alguien especial...$"

