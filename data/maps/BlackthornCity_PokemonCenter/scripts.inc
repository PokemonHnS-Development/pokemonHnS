.set LOCALID_NURSE, 1

BlackthornCity_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BlackthornCity_PokemonCenter_OnTransition
	.byte 0

BlackthornCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_BLACKTHORN_CITY
	end

BlackthornCity_PokemonCenter_EventScript_Gent::
	msgbox BlackthornCity_PokemonCenter1FGentlemanText, MSGBOX_NPC
	end

BlackthornCity_PokemonCenter_EventScript_Twin::
	msgbox BlackthornCity_PokemonCenter1FTwinText, MSGBOX_NPC
	end

BlackthornCity_PokemonCenter1FGentlemanText:
	.string "En lo profundo de la\n"
	.string "MESETA AÑIL está la LIGA POKéMON.\p"
	.string "Dicen que ahí se reúnen los mejores\n"
	.string "ENTRENADORES del país.$"

BlackthornCity_PokemonCenter1FTwinText:
	.string "Había un movimiento que tenía\n"
	.string "que enseñarle a mi POKéMON.\p"
	.string "Usé el BORRADOR DE MOV. para que\n"
	.string "olvidara una MO.$"
