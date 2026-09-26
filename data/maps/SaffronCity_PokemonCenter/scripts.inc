.set LOCALID_NURSE, 1

SaffronCity_PokemonCenter_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_PokemonCenter_OnTransition
	.byte 0

SaffronCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_SAFFRON_CITY
	end

SaffronCity_PokemonCenter_EventScript_Teacher::
	msgbox SaffronCity_PokemonCenter1F_Text_Teacher, MSGBOX_NPC	
	end

SaffronCity_PokemonCenter_EventScript_Fisher::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_PokemonCenter_EventScript_FisherReturnedMachinePart
	msgbox SaffronCity_PokemonCenter1F_Text_Fisher, MSGBOX_NPC	
	end
SaffronCity_PokemonCenter_EventScript_FisherReturnedMachinePart::
	msgbox SaffronCity_PokemonCenter1F_Text_Fisher_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_PokemonCenter_EventScript_Youngster::
	msgbox SaffronCity_PokemonCenter1F_Text_Youngster, MSGBOX_NPC
	end

SaffronCity_PokemonCenter1F_Text_Teacher:
	.string "¿Cómo son los CENTROS POKéMON\n"
	.string "de JOHTO?\p"
	.string "...Ya veo. No son tan distintos\n"
	.string "a los de KANTO.\p"
	.string "¡Puedo ir a JOHTO sin\n"
	.string "preocuparme entonces!$"

SaffronCity_PokemonCenter1F_Text_Fisher:
	.string "Acabo de pasar por el\n"
	.string "TÚNEL ROCA.\p"
	.string "Hubo cierto alboroto en la\n"
	.string "CENTRAL ELÉCTRICA.$"

SaffronCity_PokemonCenter1F_Text_Fisher_ReturnedPart:
	.string "Hay una cueva rara en CERULEAN.\p"
	.string "Como HIKER pro, debería ir,\n"
	.string "pero ese lugar me asusta hasta a mí.$"

SaffronCity_PokemonCenter1F_Text_Youngster:
	.string "Sede de SILPH CO. y la\n"
	.string "estación del MAGNET TRAIN\l"
	.string "son lo mejor de SAFFRON.$"
