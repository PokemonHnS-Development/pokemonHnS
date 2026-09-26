.set LOCALID_ATTENDANT, 1
.set LOCALID_NURSE, 2
.set LOCALID_GIRL, 4
.set LOCALID_MAN, 5

TrainerHill_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerHill_Entrance_OnResume
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, TrainerHill_Entrance_OnReturn
	map_script MAP_SCRIPT_ON_TRANSITION, TrainerHill_Entrance_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, TrainerHill_Entrance_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerHill_Entrance_OnFrame
	.byte 0

TrainerHill_Entrance_OnTransition:
	clearflag FLAG_LIMIT_TO_50
	calculatemonstats
	setflag FLAG_TEMP_HIDE_FOLLOWER
	setflag FLAG_LANDMARK_TRAINER_HILL
	getplayerxy VAR_TEMP_D, VAR_RESULT
	end

@ Unused
TrainerHill_Entrance_OnWarp:
	end

TrainerHill_Entrance_OnResume:
	trainerhill_resumetimer
	setvar VAR_TEMP_0, 0
	trainerhill_getusingereader
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_TryFaceAttendant  @ VAR_RESULT always FALSE here
	setobjectxy OBJ_EVENT_ID_PLAYER, 9, 6
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_TryFaceAttendant::
	trainerhill_getwon
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant::
	end

TrainerHill_Entrance_OnReturn:
	addobject LOCALID_NURSE
	addobject LOCALID_ATTENDANT
	addobject LOCALID_MAN
	addobject LOCALID_GIRL
	end

TrainerHill_Entrance_OnLoad:
	call_if_eq VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_OpenCounterDoor
	end

TrainerHill_Entrance_EventScript_OpenCounterDoor::
	setmetatile 17, 10, METATILE_TrainerHill_GreenFloorTile, FALSE
	return

TrainerHill_Entrance_OnFrame:
	map_script_2 VAR_TEMP_0, 0, TrainerHill_Entrance_EventScript_ExitChallenge
	map_script_2 VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_ExitElevator
	map_script_2 VAR_TEMP_5, 1, TrainerHill_Entrance_EventScript_EntryTrigger
	map_script_2 VAR_TEMP_1, 1, TrainerHill_EventScript_WarpToEntranceCounter
	.2byte 0

TrainerHill_Entrance_EventScript_ExitElevator::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerExitElevator
	waitmovement 0
	setmetatile 17, 10, METATILE_TrainerHill_CounterDoor, TRUE
	special DrawWholeMapView
	playse SE_CLICK
	waitse
	setvar VAR_TEMP_D, 0
	releaseall
	end

TrainerHill_Entrance_EventScript_ExitChallenge::
	setvar VAR_TEMP_0, 1
	trainerhill_getstatus
	switch VAR_RESULT
	case TRAINER_HILL_PLAYER_STATUS_LOST, TrainerHill_Entrance_EventScript_ExitChallengeLost
	case TRAINER_HILL_PLAYER_STATUS_ECARD_SCANNED, TrainerHill_Entrance_EventScript_ExitChallengeECard
	case TRAINER_HILL_PLAYER_STATUS_NORMAL, TrainerHill_Entrance_EventScript_EndExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeLost::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_TooBadTremendousEffort, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_PlayerExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeECard::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_MovedReceptionHereForSwitch, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_PlayerExitChallenge::
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	special HealPlayerParty
	releaseall
TrainerHill_Entrance_EventScript_EndExitChallenge::
	end

TrainerHill_Entrance_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TrainerHill_Entrance_EventScript_Attendant::
	lock
	faceplayer
	trainerhill_inchallenge
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_ThanksForPlaying
	msgbox TrainerHill_Entrance_Text_HopeYouGiveItYourBest, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AttendantEnd

TrainerHill_Entrance_EventScript_ThanksForPlaying::
	msgbox TrainerHill_Entrance_Text_ThankYouForPlaying, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AttendantEnd::
	release
	end

TrainerHill_Entrance_EventScript_EntryTrigger::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_Closed
	msgbox TrainerHill_Entrance_Text_WelcomeToTrainerHill, MSGBOX_DEFAULT
	trainerhill_getsaved
	call_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveGame
	trainerhill_allfloorsused
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_AllFloorsUsed
	msgbox TrainerHill_Entrance_Text_TrainersUpToFloorX, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers

TrainerHill_Entrance_EventScript_AllFloorsUsed::
	msgbox TrainerHill_Entrance_Text_TrainersInEveryRoom, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AskChallengeTrainers::
	message TrainerHill_Entrance_Text_LikeToChallengeTrainers
	waitmessage
	multichoice 15, 6, MULTI_YESNOINFO, FALSE
	switch VAR_RESULT
	case 0, TrainerHill_Entrance_EventScript_ChooseChallenge
	case 1, TrainerHill_Entrance_EventScript_CancelEntry
	case 2, TrainerHill_Entrance_EventScript_Info
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Info::
	msgbox TrainerHill_Entrance_Text_ExplainTrainerHill, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers
	end

TrainerHill_Entrance_EventScript_ChooseChallenge::
	multichoice 13, 2, MULTI_TAG_MATCH_TYPE, FALSE
	switch VAR_RESULT
	case 4, TrainerHill_Entrance_EventScript_CancelEntry
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	trainerhill_setmode VAR_RESULT
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 1
	setvar VAR_TEMP_5, 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	msgbox TrainerHill_Entrance_Text_TimeProgessGetSetGo, MSGBOX_DEFAULT
	trainerhill_start
	releaseall
	end

TrainerHill_Entrance_EventScript_CancelEntry::
	setvar VAR_TEMP_5, 0
	msgbox TrainerHill_Entrance_Text_PleaseVisitUsAgain, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_EventScript_SaveGame::
	msgbox TrainerHill_Entrance_Text_SaveGameBeforeEnter, MSGBOX_DEFAULT
	trainerhill_setsaved
	setvar VAR_TEMP_5, 1
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveFailed
	trainerhill_setsaved
	return

TrainerHill_Entrance_EventScript_SaveFailed::
	trainerhill_clearsaved
	goto TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Closed::
	msgbox TrainerHill_Entrance_Text_StillGettingReady, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_Movement_PlayerFaceAttendant:
	face_right
	step_end

TrainerHill_Entrance_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

@ Unused
TrainerHill_Entrance_Movement_FaceUp:
	face_up
	step_end

TrainerHill_Entrance_Movement_PlayerExitElevator:
	walk_down
	walk_down
	step_end

TrainerHill_Entrance_EventScript_Records::
	lockall
	fadescreen FADE_TO_BLACK
	special ShowTrainerHillRecords
	waitstate
	releaseall
	end

TrainerHill_Entrance_EventScript_Man::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ManTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_ManTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_CantWaitToTestTheWaters, MSGBOX_NPC
	end


TrainerHill_Entrance_EventScript_Man2::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ManTrainerHillClosed2
	msgbox TrainerHill_Entrance_Text_Money, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_ManTrainerHillClosed2::
	msgbox TrainerHill_Entrance_Text_HereToGetMoney, MSGBOX_NPC
	end

TrainerHill_Entrance_Text_HereToGetMoney:
    .string "¡Vine a ganar dinero!\n"
    .string "¿Por qué? ¡Porque al llegar a la\l"
    .string "cima te dan un premio!\p"
    .string "Me pregunto cuándo abrirán.\n"
    .string "¡No puedo esperar!$"

TrainerHill_Entrance_Text_Money:
    .string "Cada vez que llegues a la cima,\n"
    .string "ganarás algo de dinero.\p"
    .string "¡Oí que puedes ganar hasta 1.000.000¥\n"
    .string "si terminas en diez minutos!\p"
    .string "Pero si tardas más, el premio\n"
    .string "será menor…$"

TrainerHill_Entrance_EventScript_Girl::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_GirlTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_GirlTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	@goto_if_set FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ExpandedPokemart
	pokemart TrainerHill_Entrance_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

TrainerHill_Entrance_EventScript_Clerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Basic:
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_NONE
	release
	end

@TrainerHill_Entrance_EventScript_ExpandedPokemart::
@	pokemart TrainerHill_Entrance_Pokemart_Expanded
@	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
@	release
@	end
@
@	.align 2
@TrainerHill_Entrance_Pokemart_Expanded:
@	.2byte ITEM_X_SPEED
@	.2byte ITEM_X_SPECIAL
@	.2byte ITEM_X_ATTACK
@	.2byte ITEM_X_DEFEND
@	.2byte ITEM_DIRE_HIT
@	.2byte ITEM_GUARD_SPEC
@	.2byte ITEM_X_ACCURACY
@	.2byte ITEM_NONE
@	release
@	end

TrainerHill_Entrance_Text_StillGettingReady:
	.string "Esta es la COLINA ENTRENADOR,\n"
	.string "donde podrás hacer batallas dobles\l"
	.string "con muchos ENTRENADORES.\p"
	.string "Lamentablemente, aún no estamos\n"
	.string "listos. ¡Vuelve más tarde!$"

TrainerHill_Entrance_Text_WelcomeToTrainerHill:
	.string "¡Bienvenido!\p"
	.string "Esta es la COLINA ENTRENADOR,\n"
	.string "donde podrás hacer batallas dobles\l"
	.string "con muchos ENTRENADORES!$"

TrainerHill_Entrance_Text_SaveGameBeforeEnter:
	.string "¿Es tu primera visita aquí?\p"
	.string "Antes de entrar, por favor guarda\n"
	.string "tu partida.$"

TrainerHill_Entrance_Text_TrainersUpToFloorX:
	.string "Veamos…\n"
	.string "Los ENTRENADORES ahora están…\p"
	.string "Hasta el piso nro. {STR_VAR_1}.$"

TrainerHill_Entrance_Text_TrainersInEveryRoom:
	.string "Veamos…\n"
	.string "Los ENTRENADORES ahora están…\p"
	.string "Parece que hay ENTRENADORES en\n"
	.string "cada habitación.$"

TrainerHill_Entrance_Text_LikeToChallengeTrainers:
	.string "¿Quieres desafiar a los\n"
	.string "ENTRENADORES que esperan?$"

TrainerHill_Entrance_Text_TimeProgessGetSetGo:
	.string "Mediré tu progreso.\n"
	.string "¡Mucha suerte!\p"
	.string "En sus marcas...\p"
	.string "Listos...\p"
	.string "¡Ya!$"

TrainerHill_Entrance_Text_PleaseVisitUsAgain:
	.string "¡Por favor, visítanos de nuevo!$"

TrainerHill_Entrance_Text_TooBadTremendousEffort:
	.string "Fue una lástima.\p"
	.string "Creo que hiciste un esfuerzo\n"
	.string "tremendo en tus batallas.\p"
	.string "¡Vuelve e inténtalo otra vez!$"

TrainerHill_Entrance_Text_HopeYouGiveItYourBest:
	.string "Espero que des lo mejor de ti.$"

TrainerHill_Entrance_Text_MovedReceptionHereForSwitch:
	.string "Cuando los ENTRENADORES cambian,\n"
	.string "el movimiento es caótico.\p"
	.string "Para evitar el caos, movimos el\n"
	.string "mostrador de recepción aquí.\p"
	.string "Siento los inconvenientes.$"

TrainerHill_Entrance_Text_ThankYouForPlaying:
	.string "¡Gracias por jugar!$"

TrainerHill_Entrance_Text_ExplainTrainerHill:
	.string "En TRAINER HILL hacemos un\n"
	.string "evento llamado Contrarreloj.\p"
	.string "Es una carrera que mide cuánto\n"
	.string "tardas en llegar al dueño en\l"
	.string "la azotea desde este mostrador.\p"
	.string "Los mejores tiempos están en el\n"
	.string "Tablero de Tiempos; compite\l"
	.string "con tus amigos.\p"
	.string "En las batallas del camino,\n"
	.string "no ganarás puntos de Exp. ni\l"
	.string "dinero.$"

@ Unused
TrainerHill_Entrance_Text_NeedAtLeastTwoPokemon:
	.string "Lo siento, pero parece que solo\n"
	.string "tienes un POKéMON contigo.\p"
	.string "Necesitas al menos dos POKéMON\n"
	.string "para entrar en este evento.$"

TrainerHill_Roof_Text_YouFinallyCameBravo:
	.string "¡Hm! ¡Hm!\p"
	.string "¡Al fin viniste!\n"
	.string "¡Sí, ya llegaste!\p"
	.string "¡Espera! ¡No lo digas!\n"
	.string "¡Sé por qué viniste hasta aquí\l"
	.string "por tu cuenta!\p"
	.string "Querías verme, al dueño de la\n"
	.string "COLINA ENTRENADOR, porque...\p"
	.string "¡Quieres hacer un equipo conmigo!\n"
	.string "¡Wa-hoo!\p"
	.string "...¿Eh?\n"
	.string "¿No es eso?\p"
	.string "Bueno, te vi mientras subías.\n"
	.string "¡Tus batallas son maravillosas!$"

TrainerHill_Roof_Text_HaveTheMostMarvelousGift:
	.string "Para alguien tan maravilloso,\n"
	.string "tengo el regalo más maravilloso,\l"
	.string "¡y dinero por tu esfuerzo!$"

TrainerHill_Roof_Text_FullUpBeBackLaterForThis:
	.string "¡Oh, no, tienes todo lleno!\n"
	.string "¡Vuelve más tarde por esto!$"

TrainerHill_Roof_Text_GotHereMarvelouslyQuickly:
	.string "¡Oh, espera! ¿Acaso llegaste\n"
	.string "aquí maravillosamente rápido?\p"
	.string "¡Qué espléndido! ¡No hacía falta\n"
	.string "que te apresuraras tanto!\p"
	.string "Es encantador. ¡Actualizaré el\n"
	.string "Tablero de Tiempo en la recepción!$"

TrainerHill_Roof_Text_YouWerentVeryQuick:
	.string "Pero, oh...\n"
	.string "No fuiste muy rápido al llegar.$"

TrainerHill_Roof_Text_ArriveZippierNextTime:
	.string "Quizás me gustaría más que\n"
	.string "llegaras más veloz la próxima vez.\p"
	.string "¡Entonces me encantaría formar\n"
	.string "un equipo contigo!\p"
	.string "¡Hasta que nos veamos, amigo!$"

@ Unused
TrainerHill_Roof_Text_BuiltTrainerHillToFindPartner:
	.string "¡Hice la COLINA ENTRENADOR por\n"
	.string "una sola razón y nada más!\p"
	.string "¡Hallar al compañero ideal para\n"
	.string "formar un equipo conmigo!$"

TrainerHill_Entrance_Text_ChallengeTime:
	.string "{STR_VAR_1} min. {STR_VAR_2}.{STR_VAR_3} seg.$"

TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead:
	.string "¿Quién sabe qué ENTRENADORES\n"
	.string "y POKéMON habrá más adelante?\p"
	.string "¡Solo sé que quitaré del camino a\n"
	.string "cualquiera que se interponga!$"

TrainerHill_Entrance_Text_CantWaitToTestTheWaters:
	.string "Oí que ENTRENADORES fuertes vienen\n"
	.string "a TRAINER HILL de todas partes.\p"
	.string "¡Quiero probar mi nivel!\p"
	.string "¡Quitaré del camino a cualquiera\n"
	.string "que se interponga!$"

TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop:
	.string "¿Ves el tablero de tiempo de allá?\p"
	.string "Mis amigos y yo vemos quién llega\n"
	.string "a la cima en el menor tiempo.$"

TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen:
	.string "¿Sabes cuándo abrirán\n"
	.string "este lugar?\p"
	.string "¡Espero aquí para ser el primer\n"
	.string "desafiante de todos!$"

TrainerHill_Elevator_Text_ReturnToReception:
	.string "¿Te gustaría volver al\n"
	.string "mostrador de recepción?$"
