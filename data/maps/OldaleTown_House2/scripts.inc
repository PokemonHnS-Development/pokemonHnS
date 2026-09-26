OldaleTown_House2_MapScripts::
	.byte 0

OldaleTown_House2_EventScript_Woman::
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp:
	.string "Al luchar, los POKéMON suben de\n"
	.string "nivel y se vuelven más fuertes.$"

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "Si tus POKéMON se vuelven más\n"
	.string "fuertes, podrás llegar mucho más\l"
	.string "lejos de aquí.$"

