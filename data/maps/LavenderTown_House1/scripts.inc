LavenderTown_House1_MapScripts::
	.byte 0

LavenderTown_House1_EventScript_Girl::
	msgbox LavenderTown_House1_Text_Girl, MSGBOX_NPC
	end

LavenderTown_House1_EventScript_Guy::
	msgbox LavenderTown_House1_Text_Guy, MSGBOX_NPC
	end

LavenderTown_House1_EventScript_Marowak::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MAROWAK, CRY_MODE_NORMAL
	msgbox LavenderTown_House1_Text_Marowak, MSGBOX_DEFAULT
	waitmoncry
	msgbox LavenderTown_House1_Text_Marowak2, MSGBOX_DEFAULT
	closemessage
	release
	end

LavenderTown_House1_Text_Girl:
	.string "¿Puedes creerlo?\p"
	.string "Hay gente que se aburre de cuidar\n"
	.string "a los POKéMON.\p"
	.string "EL ABUELO acoge a POKéMON sin hogar\n"
	.string "y los cuida.$"
LavenderTown_House1_Text_Guy:
	.string "EL SR. FUJI vive aquí, pero no está.\n"
	.string "Debe estar en la\l"
	.string "CASA DE LAS ALMAS.$"
LavenderTown_House1_Text_Marowak:
	.string ".............................$"

LavenderTown_House1_Text_Marowak2:
	.string "El MAROWAK está tranquilo, aunque\n"
	.string "parece muy feliz.$"

