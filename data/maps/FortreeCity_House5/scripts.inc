FortreeCity_House5_MapScripts::
	.byte 0

FortreeCity_House5_EventScript_PokefanF::
	msgbox FortreeCity_House5_Text_TreeHousesAreGreat, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Man::
	msgbox FortreeCity_House5_Text_AdaptedToNature, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House5_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House5_Text_TreeHousesAreGreat:
	.string "¡Las casas de FORTREE son geniales!\p"
	.string "Es el mejor pueblo para\n"
	.string "vivir con POKéMON.$"

FortreeCity_House5_Text_AdaptedToNature:
	.string "Gente y POKéMON se adaptaron a la\n"
	.string "naturaleza para sobrevivir.\p"
	.string "No hay que obligar a la naturaleza\n"
	.string "a adaptarse a nosotros.$"

FortreeCity_House5_Text_Zigzagoon:
	.string "ZIGZAGOON: ¡Bufuu!$"

