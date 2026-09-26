Route117_PokemonDayCare_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route117_PokemonDayCare_OnTransition
	.byte 0

Route117_PokemonDayCare_OnTransition:
	setflag FLAG_LANDMARK_POKEMON_DAYCARE
	end

Route117_PokemonDayCare_Incense::
	msgbox Route117_PokemonDayCare_Incense_Text, MSGBOX_NPC
	end

Route117_PokemonDayCare_Incense_Text:
	.string "Ciertos POKéMON solo se obtienen\n"
	.string "si se crían con un objeto llamado\l"
	.string "INCENSOS. Hay 2 tipos.\p"
	.string "¿Cuántos POKéMON se pueden obtener?\n"
	.string "Bueno, ahora 9 POKéMON distintos\l"
	.string "se obtienen usando INCENSOS.$"
