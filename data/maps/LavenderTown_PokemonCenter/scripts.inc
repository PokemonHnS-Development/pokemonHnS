.set LOCALID_NURSE, 1

LavenderTown_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavenderTown_PokemonCenter_OnTransition
	.byte 0

LavenderTown_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_LAVENDER_TOWN
	end

LavenderTown_PokemonCenter_EventScript_Gent::
	msgbox LavenderTown_PokemonCenter1F_Text_Gentleman, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_EventScript_Teacher::
	msgbox LavenderTown_PokemonCenter1F_Text_Teacher, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_EventScript_Youngster::
	goto_if_set FLAG_RETURNED_MACHINE_PART, LavenderTown_PokemonCenter_EventScript_YoungsterReturnedMachinePart
	msgbox LavenderTown_PokemonCenter1F_Text_Youngster, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_EventScript_YoungsterReturnedMachinePart::
	msgbox LavenderTown_PokemonCenter1F_Text_Youngster_ReturnedMachinePart, MSGBOX_NPC
	end

LavenderTown_PokemonCenter1F_Text_Gentleman:
	.string "Al norte de LAVENDER está el\n"
	.string "TÚNEL ROCA. Crúzalo para llegar a\l"
	.string "la CENTRAL ELÉCTRICA.$"

LavenderTown_PokemonCenter1F_Text_Teacher:
	.string "Hay un programa de radio que toca\n"
	.string "música de la POKé FLUTE.\p"
	.string "¿Eh? Tu radio necesita una MEJORA\n"
	.string "DE RADIO para sintonizarlo.\p"
	.string "¿Quizás la ESTACIÓN DE RADIO de\n"
	.string "aquí pueda darte una?$"

LavenderTown_PokemonCenter1F_Text_Youngster:
	.string "Si la CENTRAL ELÉCTRICA no funciona,\n"
	.string "el TREN MAGNÉTICO tampoco...\p"
	.string "También significa que la ESTACIÓN\n"
	.string "DE RADIO no puede transmitir...$"

LavenderTown_PokemonCenter1F_Text_Youngster_ReturnedMachinePart:
	.string "El DIRECTOR de la ESTACIÓN DE RADIO\n"
	.string "estaba muy feliz.\p"
	.string "Dijo que ya transmiten porque la\n"
	.string "CENTRAL ELÉCTRICA funciona\l"
	.string "bien otra vez.$"
