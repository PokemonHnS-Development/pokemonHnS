EverGrandeCity_DrakesRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_DrakesRoom_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_DrakesRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_SidneysRoom_OnWarp
	.byte 0

@ Unused, Drake uses Sidneys identical OnWarp for some reason
EverGrandeCity_DrakesRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_DrakesRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_DrakesRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_DrakesRoom_OnFrame:
	map_script_2 VAR_GARBAGEVAR, 3, EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_DrakesRoom_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_GARBAGEVAR, 4
	releaseall
	end

EverGrandeCity_DrakesRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_KAREN, EverGrandeCity_DrakesRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_GARBAGEVAR, 4, EverGrandeCity_DrakesRoom_EventScript_CloseDoor
	end

EverGrandeCity_DrakesRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_DrakesRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_DrakesRoom_EventScript_Drake::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_KAREN, EverGrandeCity_DrakesRoom_EventScript_PostBattleSpeech
	goto_if_set FLAG_DRAKE_REMATCH, EverGrandeCity_DrakesRoom_EventScript_DrakeRematch
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_DrakesRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_KIP, EverGrandeCity_DrakesRoom_Text_Defeat
	goto EverGrandeCity_DrakesRoom_EventScript_Defeated
	end

EverGrandeCity_DrakesRoom_EventScript_DrakeRematch::
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_DrakesRoom_Text_IntroSpeech2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_KIP2, EverGrandeCity_DrakesRoom_Text_Defeat2
	goto EverGrandeCity_DrakesRoom_EventScript_Defeated
	end

EverGrandeCity_DrakesRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_DrakesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_DrakesRoom_EventScript_Defeated::
	setvar VAR_0x8004, FANCOUNTER_DEFEATED_DRAKE
	special Script_TryGainNewFanFromCounter
	setflag FLAG_DEFEATED_ELITE_4_KAREN
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_DrakesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_DrakesRoom_Text_IntroSpeech:
	.string "Soy el último del ALTO MANDO de la\n"
	.string "LIGA POKéMON, ¡DRAKE, maestro DRAGÓN!\p"
	.string "En estado natural, los POKéMON son\n"
	.string "seres salvajes. Son libres.\p"
	.string "A veces, nos estorban.\n"
	.string "A veces, nos ayudan.\p"
	.string "Para luchar con POKéMON como\n"
	.string "compañeros, ¿sabes qué se requiere?\p"
	.string "¿Sabes qué es lo necesario?\p"
	.string "Si no lo sabes, ¡jamás podrás\n"
	.string "vencerme!$"

EverGrandeCity_DrakesRoom_Text_IntroSpeech2:
	.string "Soy el último del ALTO MANDO de la\n"
	.string "LIGA POKéMON, ¡DRAKE, maestro DRAGÓN!\p"
	.string "¿Cómo están tus POKéMON compañeros?\n"
	.string "¿Te ayudaron a hacerte más fuerte?\p"
	.string "¡Seguro que sí!\p"
	.string "Pareces encendido. ¿Los otros\n"
	.string "miembros del ALTO MANDO te\p"
	.string "agotaron? ¡No flaquees ahora!\p"
	.string "¡Vénceme! ¡A bailar!$"

EverGrandeCity_DrakesRoom_Text_Defeat:
	.string "Soberbio, debo decirlo.$"

EverGrandeCity_DrakesRoom_Text_Defeat2:
	.string "¡Ja, ja, ja!\n"
	.string "¡No puedo evitar reír!\p"
	.string "Increíble. Soberbio.\n"
	.string "Realmente eres el mejor.$"

EverGrandeCity_DrakesRoom_Text_PostBattleSpeech:
	.string "Mereces todo el crédito por llegar\n"
	.string "tan lejos como ENTRENADOR POKéMON.\p"
	.string "Parece que sabes lo que se requiere.\p"
	.string "Sí, un ENTRENADOR necesita un\n"
	.string "corazón virtuoso.\p"
	.string "Los POKéMON tocan los buenos corazones\n"
	.string "y distinguen el bien del mal.\p"
	.string "Tocan los buenos corazones de los\n"
	.string "ENTRENADORES y se hacen fuertes.\p"
	.string "¡Ve! ¡Sigue adelante!\n"
	.string "¡El CAMPEÓN te espera!$"

