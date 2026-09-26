DewfordTown_House1_MapScripts::
	.byte 0

DewfordTown_House1_EventScript_Man::
	msgbox DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Woman::
	msgbox DewfordTown_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox DewfordTown_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland:
	.string "Es genial vivir en una isla pequeña\n"
	.string "como esta, en armonía con los\l"
	.string "POKéMON y la familia.$"

DewfordTown_House1_Text_LifeGoesSlowlyOnIsland:
	.string "Dejé el puerto de CIUDAD FONDO\n"
	.string "cuando me casé con mi esposo aquí.\p"
	.string "La vida pasa lento en esta isla.\n"
	.string "Pero estar rodeada del mar\l"
	.string "es también la felicidad.$"

DewfordTown_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: ¡Guguuh!$"

