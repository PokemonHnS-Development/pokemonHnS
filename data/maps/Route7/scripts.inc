Route7_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route7_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route7_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route7_EventScript_Sign::
	msgbox Route7_Text_UndergroundPathSign, MSGBOX_SIGN
	end

Route7_EventScript_Door::
	msgbox Route7_Text_LockedDoor, MSGBOX_SIGN
	end

Route7_Text_UndergroundPathSign:
	.string "¿Qué es este volante?\p"
	.string "... Entrenadores rudos han\n"
	.string "estado peleando en la\l"
	.string "RUTA SUBTERRÁNEA.\p"
	.string "Por quejas de los residentes,\n"
	.string "la RUTA SUBTERRÁNEA se ha\l"
	.string "sellado indefinidamente.\p"
	.string "POLICÍA DE CELADON$"

Route7_Text_LockedDoor:
	.string "Está cerrado...$"

