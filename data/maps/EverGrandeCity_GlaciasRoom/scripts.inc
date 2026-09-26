EverGrandeCity_GlaciasRoom_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_GlaciasRoom_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, EverGrandeCity_GlaciasRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_GlaciasRoom_OnWarp
	.byte 0

EverGrandeCity_GlaciasRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_GlaciasRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_GlaciasRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_GlaciasRoom_OnFrame:
	map_script_2 VAR_GARBAGEVAR, 2, EverGrandeCity_GlaciasRoom_EventScript_WalkInCloseDoor
	.2byte 0

EverGrandeCity_GlaciasRoom_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_GARBAGEVAR, 3
	releaseall
	end

EverGrandeCity_GlaciasRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_BRUNO, EverGrandeCity_GlaciasRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_GARBAGEVAR, 3, EverGrandeCity_GlaciasRoom_EventScript_CloseDoor
	end

EverGrandeCity_GlaciasRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

EverGrandeCity_GlaciasRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

EverGrandeCity_GlaciasRoom_EventScript_Glacia::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_BRUNO, EverGrandeCity_GlaciasRoom_EventScript_PostBattleSpeech
	goto_if_set FLAG_GLACIA_REMATCH, EverGrandeCity_GlaciasRoom_EventScript_GlaciaRematch
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox EverGrandeCity_GlaciasRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GLACIA, EverGrandeCity_GlaciasRoom_Text_Defeat
	goto EverGrandeCity_GlaciasRoom_EventScript_Defeated
	end

EverGrandeCity_GlaciasRoom_EventScript_GlaciaRematch::
	msgbox EverGrandeCity_GlaciasRoom_Text_IntroSpeech2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LUCY_BF_BRAIN, EverGrandeCity_GlaciasRoom_Text_Defeat2
	goto EverGrandeCity_GlaciasRoom_EventScript_Defeated
	end

EverGrandeCity_GlaciasRoom_EventScript_PostBattleSpeech::
	msgbox EverGrandeCity_GlaciasRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_GlaciasRoom_EventScript_Defeated::
	setflag FLAG_DEFEATED_ELITE_4_BRUNO
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_GlaciasRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_GlaciasRoom_Text_IntroSpeech:
	.string "Bienvenido, soy GLACIA\n"
	.string "del ALTO MANDO.\p"
	.string "Viajé desde lejos a HOENN\n"
	.string "para pulir mis técnicas de hielo.\p"
	.string "Solo he visto retos de\n"
	.string "ENTRENADORES y POKéMON débiles.\p"
	.string "¿Y tú?\p"
	.string "¡Me encantaría poder\n"
	.string "darlo todo contra ti!$"

EverGrandeCity_GlaciasRoom_Text_IntroSpeech2:
	.string "Bienvenido, soy GLACIA. No me\n"
	.string "presentaré otra vez, ya me conoces.\p"
	.string "No he tenido retos desde que\n"
	.string "luché contra ti y tus POKéMON.\p"
	.string "¿Y tú?\n"
	.string "¿Has pulido tus habilidades?\p"
	.string "¡Me encantaría poder\n"
	.string "darlo todo contra ti!\p"
	.string "Pero esta vez... ¡yo ganaré!$"

EverGrandeCity_GlaciasRoom_Text_Defeat:
	.string "Tú y tus POKéMON...\n"
	.string "¡Qué ardiente es su espíritu!\p"
	.string "Ese calor lo consume todo.\p"
	.string "No me sorprende que mi hielo\n"
	.string "no haya podido dañarlos.$"

EverGrandeCity_GlaciasRoom_Text_Defeat2:
	.string "¡Tu espíritu sigue ardiendo! Pero\p"
	.string "me quedé fría otra vez...$"

EverGrandeCity_GlaciasRoom_Text_PostBattleSpeech:
	.string "Avanza a la siguiente sala.\p"
	.string "Y allí, confirma el lado temible\n"
	.string "de la LIGA POKéMON.$"
