CaveOfOrigin_UnusedRubySapphireMap1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, CaveOfOrigin_UnusedRubySapphireMap1_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SetTimeEncounters
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

CaveOfOrigin_UnusedRubySapphireMap1_OnLoad:
	call_if_unset FLAG_REGI_DOORS_OPENED, CaveOfOrigin_UnusedRubySapphireMap1_CloseRegiEntrance
	end

CaveOfOrigin_UnusedRubySapphireMap1_CloseRegiEntrance::
	setmetatile 14, 14, METATILE_General_RockWall_RockBase, TRUE
	setmetatile 14, 15, METATILE_General_RockWall_SandBase, TRUE
	return

CaveOfOrigin_UnusedRubySapphireMap1_Scientist1::
	msgbox CaveOfOrigin_UnusedRubySapphireMap1_Scientist1_Text, MSGBOX_NPC
	release
	end

CaveOfOrigin_UnusedRubySapphireMap1_Scientist2::
	msgbox CaveOfOrigin_UnusedRubySapphireMap1_Scientist2_Text, MSGBOX_NPC
	release
	end

CaveOfOrigin_UnusedRubySapphireMap1_Scientist3::
	msgbox CaveOfOrigin_UnusedRubySapphireMap1_Scientist3_Text, MSGBOX_NPC
	release
	end

CaveOfOrigin_UnusedRubySapphireMap1_Kirlia::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KIRLIA, CRY_MODE_NORMAL
	msgbox CaveOfOrigin_UnusedRubySapphireMap1_Kirlia_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CaveOfOrigin_UnusedRubySapphireMap1_Scientist1_Text:
	.string "He visto este tipo de rocas\n"
	.string "en otros sitios, como en RUTA 132.\p"
	.string "¿Qué significan estas formaciones\n"
	.string "de roca?\p"
	.string "Estoy seguro de que son artificiales.\n"
	.string "¿Tienes alguna pista?$"

CaveOfOrigin_UnusedRubySapphireMap1_Scientist2_Text:
	.string "Cada vez que hay tormenta, algunos\n"
	.string "rayos caen en esta pequeña isla.\l"
	.string "¿No es sospechoso?\p"
	.string "Creemos que aquí vive un POKéMON\n"
	.string "que se alimenta solo de los\l"
	.string "rayos.$"

CaveOfOrigin_UnusedRubySapphireMap1_Scientist3_Text:
	.string "Investigamos un extraño\n"
	.string "fenómeno que ocurre desde hace\l"
	.string "unos meses. Esta isla no tiene\l"
	.string "humanos, así que lo que pasa\l"
	.string "aquí es muy misterioso,\l"
	.string "por decir lo menos.\p"
	.string "KIRI también busca pistas.\n"
	.string "Debemos resolver este misterio.$"

CaveOfOrigin_UnusedRubySapphireMap1_Kirlia_Text:
	.string "KIRI: ¡Kir!$"
