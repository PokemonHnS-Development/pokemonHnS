.set LOCALID_NURSE, 1

VermilionCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_PokemonCenter_OnTransition
	.byte 0

VermilionCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_VERMILION_CITY
	end

VermilionPokeCenter_EventScript_FishingGuru::
	goto_if_set FLAG_HIDE_VERMILION_SNORLAX, VermilionPokeCenter_EventScript_FishingGuru2
	msgbox VermilionCity_PokemonCenter1F_Text_FishingGuru, MSGBOX_NPC
	end

VermilionPokeCenter_EventScript_FishingGuru2::
	msgbox VermilionCity_PokemonCenter1F_Text_FishingGuru_FoughtSnorlax, MSGBOX_NPC
	end

VermilionPokeCenter_EventScript_Sailor::
	msgbox VermilionCity_PokemonCenter1F_Text_Sailor, MSGBOX_NPC
	end

VermilionPokeCenter_EventScript_Bugcatcher::
	msgbox VermilionCity_PokemonCenter1F_Text_BugCatcher, MSGBOX_NPC
	end

VermilionCity_PokemonCenter1F_Text_FishingGuru:
	.string "Un POKéMON duerme frente a la\n"
	.string "CUEVA DIGLETT.\p"
	.string "Es una gran oportunidad de\n"
	.string "atraparlo, ¿pero cómo despertarlo?$"

VermilionCity_PokemonCenter1F_Text_FishingGuru_FoughtSnorlax:
	.string "Había un POKéMON durmiendo\n"
	.string "frente a la CUEVA DIGLETT.\l"
	.string "Pero parece que ha\p"
	.string "desaparecido.$"

VermilionCity_PokemonCenter1F_Text_Sailor:
	.string "El BARCO RÁPIDO es ideal para\n"
	.string "conocer y luchar con entrenadores.$"

VermilionCity_PokemonCenter1F_Text_BugCatcher:
	.string "¿Oh? Tienes algunas MEDALLAS que\n"
	.string "no había visto antes.\p"
	.string "Ya entiendo. Las conseguiste en\n"
	.string "JOHTO.$"
