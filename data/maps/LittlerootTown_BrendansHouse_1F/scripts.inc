.set LOCALID_MOM, 1
.set LOCALID_RIVAL_MOM, 4
.set LOCALID_RIVAL, 7

LittlerootTown_BrendansHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_BrendansHouse_1F_OnFrame
	.byte 0

LittlerootTown_BrendansHouse_1F_OnLoad:
	call_if_lt VAR_GARBAGEVAR, 6, LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes::
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, TRUE
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, TRUE
	return

LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, TRUE
	return

LittlerootTown_BrendansHouse_1F_OnTransition:
	call_if_eq VAR_GARBAGEVAR, 3, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor
	call_if_eq VAR_GARBAGEVAR, 5, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs
	call_if_eq VAR_GARBAGEVAR, 6, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs::
	setobjectxyperm LOCALID_MOM, 8, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV::
	setobjectxyperm LOCALID_MOM, 4, 5
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor::
	setobjectxyperm LOCALID_MOM, 9, 8
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
@ The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro
LittlerootTown_BrendansHouse_1F_OnFrame:
	map_script_2 VAR_GARBAGEVAR, 3, LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_GARBAGEVAR, 5, LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_GARBAGEVAR, 6, LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_GARBAGEVAR, 1, LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_GARBAGEVAR, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock::
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_MOM, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 7, 1
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs:
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn::
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, MALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport::
	lockall
	setvar VAR_0x8004, MALE
	setvar VAR_0x8005, LOCALID_MOM
	goto PlayersHouse_1F_EventScript_PetalburgGymReportMale
	end

LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor::
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVAL_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_RIVAL_MOM, LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_GARBAGEVAR, 2
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_GoSeeRoom::
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, MALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival0::
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival1::
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival::
	playse SE_EXIT
	delay 10
	addobject LOCALID_RIVAL
	delay 30
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call_if_ne VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2
	msgbox RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVAL
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	delay 30
	setvar VAR_GARBAGEVAR, 3
	setvar VAR_GARBAGEVAR, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1:
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1:
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

PlayersHouse_1F_Text_IsntItNiceInHere:
	.string "MAMÁ: ¿Ves, {PLAYER}?\n"
	.string "¿No es lindo aquí también?$"

PlayersHouse_1F_Text_MoversPokemonGoSetClock:
	.string "Los POKéMON del mudancero hacen\n"
	.string "todo el trabajo y la limpieza.\l"
	.string "¡Es muy conveniente!\p"
	.string "{PLAYER}, tu cuarto está arriba.\n"
	.string "¡Ve a verlo, cariño!\p"
	.string "PAPÁ te compró un reloj nuevo por\n"
	.string "nuestra mudanza.\l"
	.string "¡No olvides ajustarlo!$"

PlayersHouse_1F_Text_ArentYouInterestedInRoom:
	.string "MAMÁ: ¿Y bien, {PLAYER}?\p"
	.string "¿No te interesa ver tu propio\n"
	.string "cuarto?$"

PlayersHouse_1F_Text_GoSetTheClock:
	.string "MAMÁ: {PLAYER}.\p"
	.string "Ajusta el reloj de tu cuarto, cielo.$"

PlayersHouse_1F_Text_OhComeQuickly:
	.string "MAMÁ: ¡Oh! {PLAYER}, {PLAYER}!\n"
	.string "¡Rápido! ¡Ven pronto!$"

PlayersHouse_1F_Text_MaybeDadWillBeOn:
	.string "MAMÁ: ¡Mira! ¡Es el GIMNASIO PETALIA!\n"
	.string "¡Quizá aparezca PAPÁ!$"

PlayersHouse_1F_Text_ItsOverWeMissedHim:
	.string "MAMÁ: Oh... Ya terminó.\p"
	.string "Creo que PAPÁ salió, pero lo perdimos.\n"
	.string "Qué mal.$"

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor:
	.string "Ah, sí.\n"
	.string "Un amigo de PAPÁ vive en el pueblo.\p"
	.string "Se llama PROF. BIRCH.\p"
	.string "Vive justo al lado, así que ve a\n"
	.string "presentarte con él.$"

PlayersHouse_1F_Text_SeeYouHoney:
	.string "MAMÁ: ¡Nos vemos, cariño!$"

PlayersHouse_1F_Text_DidYouMeetProfBirch:
	.string "MAMÁ: ¿Te presentaste al\n"
	.string "PROF. BIRCH?$"

PlayersHouse_1F_Text_YouShouldRestABit:
	.string "MAMÁ: ¿Cómo estás, {PLAYER}?\n"
	.string "Te ves algo cansado.\p"
	.string "Creo que deberías descansar.$"

PlayersHouse_1F_Text_YouShouldRestABit_PokecenterChallenge:
	.string "MAMÁ: Lo siento, cariño, ¡estás\n"
	.string "en el reto del POKéCENTER!$"

PlayersHouse_1F_Text_TakeCareHoney:
	.string "MAMÁ: ¡Cuídate mucho, cariño!$"

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom:
	.string "MAMÁ: ¿Ah? ¿PAPÁ te dio esa MEDALLA?\p"
	.string "¡Toma algo de parte de tu MAMÁ!$"

PlayersHouse_1F_Text_DontPushYourselfTooHard:
	.string "No te esfuerces tanto, cielo.\n"
	.string "Siempre puedes volver a casa.\p"
	.string "¡Tú puedes, cariño!$"

PlayersHouse_1F_Text_IsThatAPokenav:
	.string "MAMÁ: ¿Qué es eso? ¿Un POKéNAV?\n"
	.string "¿Te lo dio alguien de DEVON?\p"
	.string "Bueno, ¿qué tal si registras\n"
	.string "a tu mamá?\p"
	.string "... ... ...$"

PlayersHouse_1F_Text_RegisteredMom:
	.string "Registré a MAMÁ\n"
	.string "en el POKéNAV.$"

PlayersHouse_1F_Text_Vigoroth1:
	.string "¡Fugiiiiih!$"

PlayersHouse_1F_Text_Vigoroth2:
	.string "Huggoh, uggo uggo…$"

PlayersHouse_1F_Text_ReportFromPetalburgGym:
	.string "ENTREVISTADOR: ...Traemos este\n"
	.string "reporte desde el GIMNASIO PETALBURG.$"

PlayersHouse_1F_Text_TheresAMovieOnTV:
	.string "Hay una película en la TV.\p"
	.string "Dos hombres bailan sobre un gran\n"
	.string "teclado de piano.\p"
	.string "¡Mejor me voy!$"

PlayersHouse_1F_Text_RunningShoesManual:
	.string "Es el manual de instrucciones de las\n"
	.string "ZAPATILLAS DE CORRER.\p"
	.string "“Pulsa B para correr mientras uses\n"
	.string "tus ZAPATILLAS DE CORRER.\p"
	.string "“¡Átate las ZAPATILLAS DE CORRER y\n"
	.string "sal a correr!”$"

PlayersHouse_1F_Text_TicketFromBrineyCameForYou:
	.string "PAPÁ: ¿Hm?\p"
	.string "¡Hey, es {PLAYER}!\p"
	.string "Ha pasado tiempo, pero te ves...\n"
	.string "más fuerte, de alguna manera.\p"
	.string "Esa es la impresión que me das.\n"
	.string "¡Pero tu padre no se ha rendido!\p"
	.string "Ah, sí, tengo algo para ti.\n"
	.string "Llegó para ti de alguien llamado\l"
	.string "SR. BRINEY.$"

PlayersHouse_1F_Text_PortsInSlateportLilycove:
	.string "PAPÁ: ¿Hm, un TICKET de ferry?\p"
	.string "Si mal recuerdo, hay puertos de\n"
	.string "ferry en FONDAHUELA y VERDANTID.$"

PlayersHouse_1F_Text_BetterGetBackToGym:
	.string "Debo volver al GIMNASIO PETALBURG.\p"
	.string "MAMÁ, gracias por cuidar la casa\n"
	.string "mientras no estoy.$"

PlayersHouse_1F_Text_DadShouldStayLonger:
	.string "MAMÁ: Ese PAPÁ tuyo...\p"
	.string "Vuelve a casa tras mucho tiempo,\n"
	.string "pero solo habla de POKéMON.\p"
	.string "Debería relajarse y quedarse más.$"

PlayersHouse_1F_Text_IsThatABreakingStory:
	.string "MAMÁ: ¿Es una noticia de última hora?$"

PlayersHouse_1F_Text_LatiEmergencyNewsFlash:
	.string "¡Traemos este flash de noticias\n"
	.string "de emergencia!\p"
	.string "En varias zonas de HOENN, hay\n"
	.string "reportes de un POKéMON de color\l"
	.string "BZZT... volando.\p"
	.string "La identidad de este POKéMON es\n"
	.string "desconocida por ahora.\p"
	.string "Volvemos ahora a la programación\n"
	.string "habitual de cine.$"

PlayersHouse_1F_Text_WhatColorDidTheySay:
	.string "MAMÁ: {PLAYER}, ¿escuchaste eso?\p"
	.string "¿De qué color dijo el locutor\n"
	.string "que era ese POKéMON?$"

PlayersHouse_1F_Text_StillUnknownPokemon:
	.string "MAMÁ: ¡Vaya, qué increíble!\n"
	.string "Aún existen POKéMON desconocidos.$"

