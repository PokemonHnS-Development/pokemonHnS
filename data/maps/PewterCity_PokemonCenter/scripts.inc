.set LOCALID_NURSE, 1

PewterCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PewterCity_PokemonCenter_OnTransition
	.byte 0

PewterCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_PEWTER_CITY
	end

PewterCity_PokemonCenter_EventScript_Teacher::
	msgbox PewterCity_PokemonCenter1F_Text_Teacher, MSGBOX_NPC
	end

PewterCity_PokemonCenter_EventScript_BugCatcher::
	msgbox PewterCity_PokemonCenter1F_Text_BugCatcher, MSGBOX_NPC
	end

PewterCity_PokemonCenter1F_Text_Teacher:
	.string "...Sí, el GYM de CINNABAR ya no está.\p"
	.string "Me dejó muy sorprendido.\p"
	.string "...¿Sí? Estoy al teléfono. ¡Vete!$"

PewterCity_PokemonCenter1F_Text_Jigglypuff:
	.string "JIGGLYPUFF: Puu pupuu.$"

PewterCity_PokemonCenter1F_Text_BugCatcher:
	.string "Muchos POKéMON se duermen si oyen a\n"
	.string "un JIGGLYPUFF cantar.\p"
	.string "Hay varios movimientos que solo se\n"
	.string "usan mientras el POKéMON duerme.$"
