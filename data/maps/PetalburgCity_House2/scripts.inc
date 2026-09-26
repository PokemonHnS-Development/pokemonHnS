PetalburgCity_House2_MapScripts::
	.byte 0

PetalburgCity_House2_EventScript_Woman::
	msgbox PetalburgCity_House2_Text_NormanBecameGymLeader, MSGBOX_NPC
	end

PetalburgCity_House2_EventScript_SchoolKid::
	msgbox PetalburgCity_House2_Text_BattledNormanOnce, MSGBOX_NPC
	end

PetalburgCity_House2_Text_NormanBecameGymLeader:
	.string "NORMAN es el nuevo LÍDER de\n"
	.string "GIMNASIO del pueblo.\p"
	.string "Creo que llamó a su familia desde\n"
	.string "un lugar muy lejano.$"

PetalburgCity_House2_Text_BattledNormanOnce:
	.string "Luché contra NORMAN una vez, pero\n"
	.string "era demasiado fuerte.\p"
	.string "¿Cómo lo diría?\p"
	.string "Siento que él vive solo para\n"
	.string "los POKéMON.$"

