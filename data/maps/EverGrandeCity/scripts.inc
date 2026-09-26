EverGrandeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

EverGrandeCity_OnTransition:
	callnative SetTimeBasedEncounters
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

EverGrandeCity_EventScript_VictoryRoadSign::
	msgbox EverGrandeCity_Text_EnteringVictoryRoad, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_CitySign::
	msgbox EverGrandeCity_Text_CitySign, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_PokemonLeagueSign::
	msgbox EverGrandeCity_Text_EnteringPokemonLeague, MSGBOX_SIGN
	end

EverGrandeCity_EventScript_SetVisitedEverGrande::
	setflag FLAG_VISITED_INDIGO_PLATEAU
	setvar VAR_TEMP_1, 1
	end

EverGrandeCity_Text_EnteringVictoryRoad:
	.string "ENTRANDO A LA VÍA VICTORIA$"

EverGrandeCity_Text_EnteringPokemonLeague:
	.string "ENTRANDO A LA LIGA POKéMON\n"
	.string "PUERTA CENTRAL$"

EverGrandeCity_Text_CitySign:
	.string "CIUDAD VERIDIANO\p"
	.string "El paraíso de las flores, el mar\n"
	.string "y los POKéMON.$"

