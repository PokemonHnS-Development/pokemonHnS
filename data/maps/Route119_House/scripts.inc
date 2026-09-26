Route119_House_MapScripts::
	.byte 0

Route119_House_EventScript_Woman::
	msgbox Route119_House_Text_RumorAboutCaveOfOrigin, MSGBOX_NPC
	end

Route119_House_EventScript_Wingull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox Route119_House_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route119_House_Text_RumorAboutCaveOfOrigin:
	.string "Oí de una cueva llamada la CUEVA\n"
	.string "DEL ORIGEN.\p"
	.string "Dicen que ahí reviven los espíritus\n"
	.string "de los POKéMON. ¿Será eso\l"
	.string "posible realmente?$"

Route119_House_Text_Wingull:
	.string "WINGULL: ¡Pihyoh!$"

