.set LOCALID_NURSE, 1

CeruleanCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCity_PokemonCenter_OnTransition
	.byte 0

CeruleanCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_CERULEAN_CITY
	end

CeruleanCity_PokemonCenter_EventScript_Nerd::
	msgbox CeruleanCity_PokemonCenter1F_Text_SuperNerd, MSGBOX_NPC
	end

CeruleanCity_PokemonCenter_EventScript_Guy::
	msgbox CeruleanCity_PokemonCenter1F_Text_GymGuide, MSGBOX_NPC
	end

CeruleanCity_PokemonCenter1F_Text_SuperNerd:
	.string "Para luchar, prefiero usar\n"
	.string "POKéMON que he criado, aunque\p"
	.string "sean más débiles que algunos\n"
	.string "POKéMON recién capturados.$"

CeruleanCity_PokemonCenter1F_Text_GymGuide:
	.string "El MAGNET TRAIN viaja a más de\n"
	.string "540 km/h. Une KANTO y JOHTO\l"
	.string "en muy poco tiempo.\p"
	.string "Hace que JOHTO sea accesible.$"
