.set LOCALID_WOMAN, 8
.set LOCALID_GRUNT_1, 10
.set LOCALID_GRUNT_2, 11
.set LOCALID_GRUNT_3, 12
.set LOCALID_GRUNT_4, 13
.set LOCALID_MAXIE, 14
.set LOCALID_SCOTT, 16
.set LOCALID_JIRACHI, 18

MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

MossdeepCity_OnTransition:
	callnative SetTimeBasedEncounters
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

MossdeepCity_EventScript_Evo::
	msgbox MossdeepCity_EventScript_Evo_Text, MSGBOX_NPC
	end

MossdeepCity_EventScript_Evo_Text:
	.string "El POKéMON EEVEE evoluciona\n"
	.string "de muchas formas distintas.\p"
	.string "Con THUNDER STONE, FIRE STONE,\n"
	.string "WATER STONE... Como, por\l"
	.string "ejemplo, ELECTABUZZ y MAGMAR.\p"
	.string "Ellos también usan STONES.$"

MossdeepCity_EventScript_Evo2::
	msgbox MossdeepCity_EventScript_Evo2_Text, MSGBOX_NPC
	end

MossdeepCity_EventScript_Evo2_Text:
	.string "A mi esposa le encanta EEVEE.\p"
	.string "Sabe todas las formas en que\n"
	.string "evoluciona. Como, al LLEVAR una\l"
	.string "WATER STONE o una LEAF STONE.\p"
	.string "¡Sí, LLEVAR, no usar!\n"
	.string "¿Lo sabías? Yo no.\p"
	.string "O estar FELIZ de día o de noche.\p"
	.string "¡O ser lindo al usar un\n"
	.string "movimiento tipo HADA!\p"
	.string "...\p"
	.string "¿Sabes dónde hay EEVEE?\n"
	.string "Quizá capture uno para ella.\p"
	.string "¡Le va a encantar!$"

MossdeepCity_EventScript_PokefanF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone::
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone::
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy::
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM::
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl::
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman::
	goto_if_set FLAG_JIRACHI, MossdeepCity_EventScript_Woman2
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman2::
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock2, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	closemessage
	goto_if_set FLAG_JIRACHI, MossdeepCity_EventScript_WhiteRockEnd
	goto_if_unset FLAG_EXTRA_LEGENDARIES, MossdeepCity_EventScript_WhiteRockEnd
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_EventScript_Jirachi
	end

MossdeepCity_EventScript_WhiteRockEnd::
	end

MossdeepCity_EventScript_Jirachi::
	lockall
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_EventScript_JirachiMoves
	applymovement LOCALID_WOMAN, MossdeepCity_EventScript_JirachiMoves2
	waitmovement 0
	msgbox MossdeepCity_Text_ItsAWhiteRock2, MSGBOX_DEFAULT
	waitmessage
	waitse
	playmoncry SPECIES_JIRACHI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_JIRACHI, 50
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	applymovement LOCALID_JIRACHI, MossdeepCity_EventScript_JirachiMoves3
	waitmovement 0
	msgbox MossdeepCity_Text_ItsAWhiteRock3, MSGBOX_DEFAULT
	closemessage
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MossdeepCity_EventScript_JirachiWon
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MossdeepCity_EventScript_JirachiWon
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MossdeepCity_EventScript_JirachiRan
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MossdeepCity_EventScript_JirachiRan
	release
	end

MossdeepCity_EventScript_JirachiWon::
	setflag FLAG_JIRACHI
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	releaseall
	end

MossdeepCity_EventScript_JirachiRan::
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	applymovement LOCALID_JIRACHI, MossdeepCity_EventScript_JirachiMoves4
	waitmovement 0
	releaseall
	end

MossdeepCity_EventScript_JirachiMoves:
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	jump_in_place_up
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_EventScript_JirachiMoves2:
	emote_exclamation_mark
	delay_16
	delay_16
	delay_16
	jump_in_place_right
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_EventScript_JirachiMoves3:
	delay_16
	delay_16
	delay_16
	set_visible
	walk_down
	step_end

MossdeepCity_EventScript_JirachiMoves4:
	set_invisible
	walk_up
	step_end

MossdeepCity_Text_ItsAWhiteRock2:
	.string "Algo...\p"
	.string "...\p"
	.string "Algo se está moviendo...\n"
	.string "...$"

MossdeepCity_Text_ItsAWhiteRock3:
	.string "¡Algo te saltó desde\n"
	.string "detrás de la roca blanca!$"

MossdeepCity_EventScript_GymSign::
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign::
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign::
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_CELADON_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter::
	lockall
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	delay 30
	setvar VAR_GARBAGEVAR, 2
	setflag FLAG_GARBAGEFLAG
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter:
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter:
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter:
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man::
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock::
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock::
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt::
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott::
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe:
	.string "STEVEN me dio esto, pero no\n"
	.string "sé para qué sirve.\p"
	.string "Creo que se llama KING'S ROCK.\n"
	.string "¿Lo quieres?$"

MossdeepCity_Text_YouCanKeepIt:
	.string "¿Por qué lo querrías?\n"
	.string "Eres raro.\p"
	.string "Quédatelo, pero que sea un secreto\n"
	.string "para STEVEN.$"

MossdeepCity_Text_StevensHouseOverThere:
	.string "¡La casa de STEVEN está allá mismo!$"

MossdeepCity_Text_WhatToDoWithWeirdRock:
	.string "¡Sí, tú también lo crees! ¿Qué se\n"
	.string "hace con una roca tan rara?$"

MossdeepCity_Text_WailmerWatching:
	.string "Cerca de SALGADO verás\n"
	.string "WAILMER salvajes.\p"
	.string "Se llama, eh...\n"
	.string "¿Cómo era...?\p"
	.string "WAI, WAI, WAI...\p"
	.string "¡Vigila a WAILMER!$"

MossdeepCity_Text_SpaceCenterReceivedLetter:
	.string "El CENTRO ESPACIAL de la isla ha\n"
	.string "lanzado cohetes enormes.\p"
	.string "Hay un gran alboroto por una carta\n"
	.string "que recibieron hace poco.$"

MossdeepCity_Text_SpaceCenterLaunchingRockets:
	.string "El CENTRO ESPACIAL de la isla ha\n"
	.string "lanzado cohetes enormes.$"

MossdeepCity_Text_MossdeepTargetedByMagma:
	.string "Un amigo MARINERO me dijo que el\n"
	.string "TEAM AQUA llegó a CIUDAD VERANO.\p"
	.string "¡Y que alguien apareció y los\n"
	.string "derrotó por completo!\p"
	.string "Pero SALGADO ha sido el blanco del\n"
	.string "TEAM MAGMA.\p"
	.string "Si quieres saber qué planean,\n"
	.string "ve al CENTRO ESPACIAL.$"

MossdeepCity_Text_FeelReliefOnLand:
	.string "Soy MARINERO, así que el mar es\n"
	.string "lo más importante para mí.\p"
	.string "¿Pero sabes? Al volver a tierra\n"
	.string "tras un viaje, ¡siento alivio!$"

MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
	.string "¿No sería genial?\p"
	.string "¿Que el mundo entero estuviera\n"
	.string "lleno de plantas y flores como aquí?$"

MossdeepCity_Text_LifeNeedsSeaToLive:
	.string "Toda vida necesita el mar, aunque\n"
	.string "viva en la tierra.\p"
	.string "Al terminar su ciclo, la vida se\n"
	.string "vuelve suelo y vuelve a la tierra.\p"
	.string "Y el mar siempre está conectado a\n"
	.string "la tierra.\p"
	.string "Sí, como esta misma costa.$"

MossdeepCity_Text_SurfExhilarating:
	.string "Viajar en barco está bien.\p"
	.string "Pero cruzar el mar con POKéMON\n"
	.string "usando SURF...\p"
	.string "¡Eso sí es un viaje emocionante!\n"
	.string "¿No estás de acuerdo, joven?$"

MossdeepCity_Text_SpecialSpaceCenterRock:
	.string "Esta roca es especial para la gente\n"
	.string "del CENTRO ESPACIAL.\p"
	.string "La pusieron aquí deseando que sus\n"
	.string "cohetes vuelen seguros.\p"
	.string "¿Qué usas tú para pedir deseos?\n"
	.string "¿Le pides a una estrella?\p"
	.string "Yo uso una etiqueta de deseos.\n"
	.string "Eso es lo que hago.$"

MossdeepCity_Text_SpecialSpaceCenterRock2:
	.string "¡¿Qué fue eso?! ¡Ese no era mi deseo!$"

MossdeepCity_Text_ItsAWhiteRock:
	.string "Es una roca blanca.\p"
	.string "Emana una energía misteriosa…$"

MossdeepCity_Text_GymSign:
	.string "GIMNASIO POKéMON DE CIUDAD FONDO\n"
	.string "LÍDERES: LIZA Y TATE\p"
	.string "“¡La combinación mística!”$"

MossdeepCity_Text_CitySign:
	.string "CIUDAD FONDO\n"
	.string "“Lema: ¡Aprecia a los POKéMON!”$"

MossdeepCity_Text_SpaceCenterSign:
	.string "CENTRO ESPACIAL DE CIUDAD FONDO\n"
	.string "“El lugar más cercano al espacio.”$"

MossdeepCity_Text_ScottSomethingWrongWithTown:
	.string "SCOTT: {PLAYER}{KUN}, ¿todo bien?\n"
	.string "¡Me va genial!\p"
	.string "Oí que el LÍDER del GIMNASIO de\n"
	.string "MOSSDEEP es fuerte, así que vine\l"
	.string "a verlo por mí mismo.\p"
	.string "Pero hay algo raro en\n"
	.string "este pueblo.\p"
	.string "Hablan de una carta de advertencia\n"
	.string "y del CENTRO ESPACIAL…\p"
	.string "Aunque no creo que tenga nada que\n"
	.string "ver conmigo.$"

MossdeepCity_Text_SootopolisNewGymLeader:
	.string "Ahh… Se siente genial que las olas\n"
	.string "bañen mis pies…\p"
	.string "Hablando de olas, ¿conoces la\n"
	.string "ciudad isla de CALORÍA?\p"
	.string "Creo que el GIMNASIO de allí tiene\n"
	.string "un nuevo LÍDER.\p"
	.string "Dicen que ese LÍDER fue el mentor\n"
	.string "de WALLACE.$"
