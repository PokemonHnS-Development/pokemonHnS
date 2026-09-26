.set LOCALID_NURSE, 1

MahoganyTown_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MahoganyTown_PokemonCenter_OnTransition
	.byte 0

MahoganyTown_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_MAHOGANYTOWN
	end

MahoganyTown_PokemonCenter_EventScript_Hiker::
	msgbox MahoganyTown_PokemonCenter_Text_PokefanM, MSGBOX_NPC
	end
	
MahoganyTown_PokemonCenter_EventScript_Boy::
	msgbox MahoganyTown_PokemonCenter_Text_Youngster, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_EventScript_Girl::
	msgbox MahoganyTown_PokemonCenter_Text_CooltrainerF, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_Text_PokefanM:
    .string "¿Qué es esto? ¿El TEAM ROCKET ha\n"
    .string "vuelto?\p"
    .string "Vi hombres de negro en el LAKE OF\n"
    .string "RAGE…$"

MahoganyTown_PokemonCenter_Text_Youngster:
    .string "Evito que mis POKéMON evolucionen\n"
    .string "muy pronto.\p"
    .string "Hago que aprendan ciertos ataques\n"
    .string "antes de evolucionar.$"

MahoganyTown_PokemonCenter_Text_CooltrainerF:
    .string "Los POKéMON son más fuertes al\n"
    .string "evolucionar,\p"
    .string "pero aprenden ataques más\n"
    .string "lentamente.$"
