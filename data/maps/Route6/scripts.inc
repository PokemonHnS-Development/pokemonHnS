Route6_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route6_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route6_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route6_EventScript_Rex::
	trainerbattle_single TRAINER_REX PokefanM_Text_RexSeen, PokefanM_Text_RexBeaten
	msgbox PokefanM_Text_RexAfter, MSGBOX_AUTOCLOSE
	end

Route6_EventScript_Allan::
	trainerbattle_single TRAINER_ALLAN PokefanM_Text_AllanSeen, PokefanM_Text_AllanBeaten
	msgbox PokefanM_Text_AllanAfter, MSGBOX_AUTOCLOSE
	end

Route6_EventScript_Pokefan::
	msgbox Route6_Text_PokefanM, MSGBOX_NPC
	end

Route6_EventScript_Sign::
	msgbox Route6_Text_UndergroundPathSign, MSGBOX_SIGN
	end

Route6_Text_PokefanM:
	.string "El camino está cerrado hasta que\n"
	.string "se resuelva el problema en la\l"
	.string "CENTRAL ELÉCTRICA.$"

Route6_Text_UndergroundPathSign:
	.string "CAMINO SUBTERRÁNEO\p"
	.string "CIUDAD CERULEAN - CIUDAD VERMILION$"

PokefanM_Text_RexSeen:
	.string "¡Mi STANTLER es el más lindo del\n"
	.string "mundo!$"

PokefanM_Text_RexBeaten:
	.string "¡Mi STANTLER!$"

PokefanM_Text_RexAfter:
	.string "¡Mira qué adorable es mi\n"
	.string "STANTLER!\p"
	.string "¿No es tan lindo que te\n"
	.string "derrite el corazón?$"

PokefanM_Text_AllanSeen:
	.string "¡Mi GRANBULL es el más lindo del\n"
	.string "mundo!$"

PokefanM_Text_AllanBeaten:
	.string "¡Mi GRANBULL!$"

PokefanM_Text_AllanAfter:
	.string "¡Mira qué adorable es mi\n"
	.string "GRANBULL!\p"
	.string "¿No es tan lindo que te\n"
	.string "derrite el corazón?$"

