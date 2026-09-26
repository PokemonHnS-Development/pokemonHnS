EverGrandeCity_PhoebesRoom_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_PhoebesRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_PhoebesRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_PhoebesRoom_OnFrame
	.byte 0

EverGrandeCity_PhoebesRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_PhoebesRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_PhoebesRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_PhoebesRoom_OnFrame:
	map_script_2 VAR_GARBAGEVAR, 1, EverGrandeCity_PhoebesRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_PhoebesRoom_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_GARBAGEVAR, 2
	releaseall
	end

EverGrandeCity_PhoebesRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_KOGA, EverGrandeCity_PhoebesRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_GARBAGEVAR, 2, EverGrandeCity_PhoebesRoom_EventScript_CloseDoor
	end

EverGrandeCity_PhoebesRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_PhoebesRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_PhoebesRoom_EventScript_Phoebe::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_KOGA, EverGrandeCity_PhoebesRoom_EventScript_PostBattleSpeech
	goto_if_set FLAG_PHOEBE_REMATCH, EverGrandeCity_PhoebesRoom_EventScript_PhoebeRematch
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_PhoebesRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PHOEBE, EverGrandeCity_PhoebesRoom_Text_Defeat
	goto EverGrandeCity_PhoebesRoom_EventScript_Defeated
	end

EverGrandeCity_PhoebesRoom_EventScript_PhoebeRematch::
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_PhoebesRoom_Text_IntroSpeech2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LUCY_BF_BRAIN, EverGrandeCity_PhoebesRoom_Text_Defeat2
	goto EverGrandeCity_PhoebesRoom_EventScript_Defeated
	end

EverGrandeCity_PhoebesRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_PhoebesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PhoebesRoom_EventScript_Defeated::
	setflag FLAG_DEFEATED_ELITE_4_KOGA
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_PhoebesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PhoebesRoom_Text_IntroSpeech:
	.string "¡Ahahaha!\p"
	.string "Soy PHOEBE, del ALTO MANDO.\n"
	.string "Entrené en el MONTE CENIZA.\p"
	.string "Así aprendí a comunicarme con los\n"
	.string "POKéMON tipo FANTASMA.\p"
	.string "Sí, el vínculo que creé con ellos\n"
	.string "es extremadamente fuerte.\p"
	.string "¡Ven, intenta ver si puedes hacerle\n"
	.string "daño a mis POKéMON!$"

EverGrandeCity_PhoebesRoom_Text_IntroSpeech2:
	.string "¡Ahahaha! ¡Tú otra vez!\p"
	.string "Soy PHOEBE, del ALTO MANDO.\n"
	.string "¡El vínculo con mis POKéMON\l"
	.string "se ha vuelto aún más fuerte!\p"
	.string "Intenta ver si puedes hacerle\n"
	.string "daño a mis POKéMON.\p"
	.string "¡Porque no será como la última vez!$"

EverGrandeCity_PhoebesRoom_Text_Defeat:
	.string "Oh, rayos.\n"
	.string "He perdido.$"

EverGrandeCity_PhoebesRoom_Text_Defeat2:
	.string "Oh, rayos...\n"
	.string "Pasó de nuevo.$"

EverGrandeCity_PhoebesRoom_Text_PostBattleSpeech:
	.string "Tú y tus POKéMON también tienen\n"
	.string "un vínculo definitivo.\p"
	.string "No lo reconocí, así que es natural\n"
	.string "que haya perdido.\p"
	.string "Sí, quiero ver hasta dónde te lleva\n"
	.string "ese vínculo.\p"
	.string "Adelante, ve a la siguiente sala.$"

