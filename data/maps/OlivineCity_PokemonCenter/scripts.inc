.set LOCALID_NURSE, 1

OlivineCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_PokemonCenter_OnTransition
	.byte 0

OlivineCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_OLIVINE_CITY
	end

OlivineCity_EventScript_Fisher::
	lock
	faceplayer
	msgbox OlivineCity_Text_PokecenterFisher, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Teacher::
	lock
	faceplayer
	msgbox OlivineCity_Text_PokecenterTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_PokecenterFisher:
	.string "El MARINERO del CAFÉ OLIVO\n"
	.string "de al lado es muy generoso.\p"
	.string "Le enseñó FUERZA a mi POKéMON.\p"
	.string "Ahora mueve rocas enormes\n"
	.string "sin ningún esfuerzo.$"

OlivineCity_Text_PokecenterTeacher:
	.string "Hay alguien en CIUDAD ORQUIDEA\n"
	.string "al otro lado del mar.\p"
	.string "Siempre presume de sus\n"
	.string "raros POKéMON.$"
