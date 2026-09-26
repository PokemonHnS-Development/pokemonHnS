BlackthornCity_House1_MapScripts::
	.byte 0

BlackthornCity_House1EventScript_Granny::
	msgbox BlackthornCity_House1_Text_Granny, MSGBOX_NPC
	end

BlackthornCity_House1EventScript_Dratini::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DRATINI, CRY_MODE_NORMAL
	msgbox BlackthornCity_House1_Text_Dratini, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BlackthornCity_House1_Text_Granny:
	.string "Un clan de entrenadores que dominan\n"
	.string "dragones vive aquí en\l"
	.string "BLACKTHORN.\p"
	.string "Por eso hay muchas leyendas\n"
	.string "de dragones en este pueblo.$"

BlackthornCity_House1_Text_Dratini:
	.string "DRATINI: ¡Draa!$"
