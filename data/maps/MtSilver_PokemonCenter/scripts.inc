.set LOCALID_NURSE, 1

MtSilver_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_PokemonCenter_OnTransition
	.byte 0

MtSilver_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_MT_SILVER
	end

MtSilver_PokemonCenter_EventScript_Meara::
	msgbox MtSilver_PokemonCenter_Text_Meara, MSGBOX_NPC
	end

MtSilver_PokemonCenter_Text_Meara:
	.string "Soy investigador del museo de\n"
	.string "CIUDAD PLATEA.\p"
	.string "Se hallaron muchos artefactos\n"
	.string "en esta zona, así que\l"
	.string "vine aquí a investigar.\p"
	.string "No hay registros de una civilización\n"
	.string "en la montaña, pero los\l"
	.string "artefactos son casi seguro\l"
	.string "artificiales.\p"
	.string "Es realmente misterioso.$"
