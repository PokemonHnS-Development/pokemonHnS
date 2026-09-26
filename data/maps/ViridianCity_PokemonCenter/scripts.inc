.set LOCALID_NURSE, 1

ViridianCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_PokemonCenter_OnTransition
	.byte 0

ViridianCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_VIRIDIAN_CITY
	end

ViridianCity_PokemonCenter_EventScript_CooltrainerM::
	goto_if_set FLAG_HIDE_CINNABAR_BLUE, VirianCity_EventScript_GymGrampsBlue
	msgbox ViridianCity_PokemonCenter_Text_1FCooltrainerM, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_EventScript_CooltrainerMBlue::
	msgbox ViridianCity_PokemonCenter_Text_1FCooltrainerM_BlueReturned, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_EventScript_CooltrainerF::
	msgbox ViridianCity_PokemonCenter_Text_1FCooltrainerF, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_EventScript_BugCatcher::
	msgbox ViridianCity_PokemonCenter_Text_1FBugCatcher, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_Text_1FCooltrainerM:
	.string "¿Dónde estará el LÍDER del\n"
	.string "GIMNASIO VERDIANTE? Quiero retarlo.$"

ViridianCity_PokemonCenter_Text_1FCooltrainerM_BlueReturned:
	.string "No hay ENTRENADORES en el\n"
	.string "GIMNASIO VERDIANTE.\p"
	.string "El LÍDER dice que su política es\n"
	.string "ganar sin tener subordinados.$"

ViridianCity_PokemonCenter_Text_1FCooltrainerF:
	.string "Oí que el GIMNASIO de CANNON\n"
	.string "desapareció.\p"
	.string "Me pregunto qué pasó con BLAINE,\n"
	.string "el LÍDER del GIMNASIO.$"

ViridianCity_PokemonCenter_Text_1FBugCatcher:
	.string "Mi sueño es ser LÍDER de GIMNASIO.$"
