.set LOCALID_NURSE, 1

AzaleaTown_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_Pokecenter_OnTransition
	.byte 0

AzaleaTown_Pokecenter_OnTransition::
	setrespawn HEAL_LOCATION_AZALEA_TOWN
	end

AzaleaPokeCenter_EventScript_Gentleman::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokeCenter_EventScript_Fisher::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_FishingGuru, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokeCenter_EventScript_PokefanF::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokecenter_Text_Gentleman:
	.string "¿Tus POKéMON saben MOs?\p"
	.string "Esos movimientos sirven aunque\n"
	.string "tu POKéMON se haya debilitado.$"

AzaleaPokecenter_Text_UnusedPCExplanation:
	.string "BILL creó el sistema para guardar\n"
	.string "POKéMON en la PC.\p"
	.string "La PC de BILL guarda hasta 30\n"
	.string "POKéMON por BOX.$"

AzaleaPokecenter_Text_FishingGuru:
	.string "La PC de BILL guarda hasta 30\n"
	.string "POKéMON por BOX.$"

AzaleaPokecenter_Text_PokefanF:
	.string "¿Sabes sobre las BAYAS?\p"
	.string "Ábrelas, vacíalas y ponles un\n"
	.string "dispositivo especial.\p"
	.string "Así podrás capturar POKéMON.\p"
	.string "Antes de las POKé BALLS,\n"
	.string "todos usaban BAYAS.$"
