.set LOCALID_ATTENDANT, 1

SlateportCity_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_BattleTentCorridor_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SlateportCity_BattleTentCorridor_OnWarp
	.byte 0

	@ This is Slateport Tent's version of the Battle Factory Pre-Battle Room

SlateportCity_BattleTentCorridor_OnWarp:
	map_script_2 VAR_TEMP_1, 0, SlateportCity_BattleTentCorridor_EventScript_SetUpObjects
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_SetUpObjects::
	setvar VAR_TEMP_1, 1
	goto_if_ne VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth
	setobjectxy LOCALID_ATTENDANT, 2, 2
	turnobject LOCALID_ATTENDANT, DIR_SOUTH
SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

SlateportCity_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, SlateportCity_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_EnterCorridor::
	goto_if_eq VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantEnter
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerEnter
	waitmovement 0
	goto_if_eq VAR_0x8006, 2, SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge
	slateporttent_generaterentalmons
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_HoldMonsChooseFromSelection, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	slateporttent_rentmons
	waitstate
SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	@opendoor 2, 1
	@waitdooranim
	applymovement LOCALID_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantExit
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerExit
	waitmovement 0
	@closedoor 2, 1
	@waitdooranim
	warp MAP_SLATEPORT_CITY_BATTLE_TENT_BATTLE_ROOM, 4, 4
	waitstate
	end

SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle::
	factory_setopponentmons
	factory_resethelditems
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LetUsRestoreMons, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	call_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent
	call_if_eq VAR_RESULT, 2, SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, TRUE
	switch VAR_RESULT
	case 0, SlateportCity_BattleTentCorridor_EventScript_AskSwapMon
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge
	case 2, SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge

SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case YES, SlateportCity_BattleTentCorridor_EventScript_PauseChallenge
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_RetireFromChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case 0, SlateportCity_BattleTent_EventScript_WarpToLobbyLost
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskSwapMon::
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LikeToSwapMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	case YES, SlateportCity_BattleTentCorridor_EventScript_SwapMons
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_SwapMons::
	fadescreen FADE_TO_BLACK
	slateporttent_swapmons
	waitstate
	goto_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_YourSwapIsComplete, MSGBOX_DEFAULT
	goto SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor2ndOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor3rdOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_PauseChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_SavingDataPleaseWait
	waitmessage
	slateporttent_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge::
	special SavePlayerParty
	factory_setparties 0
	goto SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SlateportCity_BattleTentCorridor_Movement_PlayerExit:
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantExit:
	walk_up
	set_invisible
	step_end

@ Leftover text from when this was a Contest Hall in R/S
@ Unused
SlateportCity_ContestHall_Text_AdviceForContests:
	.string "¿Quieres un buen consejo\n"
	.string "para los CONTESTS?\p"
	.string "Usar un movimiento tras otro\n"
	.string "tipo de movimiento a veces te da\l"
	.string "más atención.\p"
	.string "Si sabes lo que haces,\n"
	.string "ganarás muchos puntos de atractivo.\p"
	.string "Claro, tus rivales podrían intentar\n"
	.string "arruinar la exhibición de tu POKéMON.$"

@ Unused
SlateportCity_ContestHall_Text_MyPapaIsContestJudge:
	.string "Mi papá es JUEZ de CONTESTS.\p"
	.string "Me pregunto qué seré de mayor,\n"
	.string "¿un JUEZ o un LÍDER de GIMNASIO?$"

@ Unused
SlateportCity_ContestHall_Text_ImLikeMajorlyCheesed:
	.string "Oye, tío, estoy súper molesto,\n"
	.string "ya sabes. O sea, solo quería\l"
	.string "saber por qué mi POKéMON\l"
	.string "nunca gana, ¿sabes, o sea, eh?\p"
	.string "Así que le di mi opinión al JUEZ,\n"
	.string "ya sabes, que es gratis.\p"
	.string "¡Y no quiso escucharme, o sea, eh!\n"
	.string "¡O sea, un bajón total, tío!\p"
	.string "¡Oye, tú! ¡Cállate, ¿sabes?\n"
	.string "¡Toma esto, ya sabes!$"

@ Unused
SlateportCity_ContestHall_Text_ExplainTorment:
	.string "Es la MT41, ¿sabes?\n"
	.string "¡Es TORMENTO, me escuchas?\p"
	.string "No deja que el rival use el\n"
	.string "mismo movimiento dos veces, ¿ves?\p"
	.string "Oye, escucha, ¡yo no voy a\n"
	.string "usar TORMENTO contigo!$"

@ Unused
SlateportCity_ContestHall_Text_MCStepUpTakePartInContest:
	.string "MC: ¡Vaya, vaya!\n"
	.string "¿No es ese un POKéMON estupendo?\p"
	.string "¡Por favor! ¡Acércate y participa\n"
	.string "en nuestros espléndidos CONTESTS!\p"
	.string "¡Te irá bien! ¡Estoy seguro!\n"
	.string "¡Mis ojos nunca me han fallado!$"

@ Unused
SlateportCity_ContestHall_Text_JudgeWouldntDoToMissContest:
	.string "JUEZ: ¡Hola, hola!\n"
	.string "¡Veo que eres un ENTRENADOR!\p"
	.string "Entonces, no puedes perderte\n"
	.string "¡un POKéMON CONTEST!\p"
	.string "¡Consigue el PASE de CONTEST en\n"
	.string "CIUDAD VERDANTURF y participa!$"

@ Unused
SlateportCity_ContestHall_Text_ItsAppealTime:
	.string "¡Es hora del atractivo!\n"
	.string "¿Con qué debería empezar?$"

@ Unused
SlateportCity_ContestHall_Text_DidntPayAttentionToAppeal:
	.string "No le prestaron mucha atención\n"
	.string "al atractivo de mi POKéMON…\p"
	.string "Humph, ese JUEZ no reconoce\n"
	.string "algo bueno cuando lo ve.$"

@ Unused
SlateportCity_ContestHall_Text_RewardWithSageAdvice:
	.string "¡Hola! Debes ser un gran fan para\n"
	.string "estar tan cerca de la acción.\p"
	.string "Premiaré tu entusiasmo con\n"
	.string "este consejo sabio.\p"
	.string "Si un movimiento sale muy bien,\n"
	.string "el público se emocionará.\p"
	.string "El POKéMON que haga su atractivo\n"
	.string "cuando todos estén emocionados...\p"
	.string "¡Bueno, pensarías que algo bueno\n"
	.string "pasará!$"

@ Unused
SlateportCity_ContestHall_Text_MoreFreakedOutThanMon:
	.string "¡No puedo! Estoy más asustado\n"
	.string "que mi propio POKéMON.\p"
	.string "¡Tiemblo y mi corazón va a mil!$"

@ Unused
SlateportCity_ContestHall_Text_BattleAndContestAlike:
	.string "Una batalla y un CONCURSO no son\n"
	.string "lo mismo, pero se parecen.\p"
	.string "Debes esforzarte y confiar en el\n"
	.string "POKéMON que has criado.$"

@ Unused
SlateportCity_ContestHall_Text_MonLooksOnTopOfGame:
	.string "Ese POKéMON parece estar en su\n"
	.string "mejor momento, ¿eh?\p"
	.string "Un POKéMON que destaca en el\n"
	.string "juicio secundario parece estar más\l"
	.string "relajado al hacer atractivos.$"

@ Unused
SlateportCity_ContestHall_Text_MyMonBetterThanThatLot:
	.string "¿Ves ese espectáculo tan triste?\p"
	.string "¡Je, mi POKéMON es mucho mejor\n"
	.string "que todos esos!$"

@ Unused
SlateportCity_ContestHall_Text_GetUrgeToMoveWithMon:
	.string "¿No sientes ganas de moverte con\n"
	.string "el POKéMON si hace un atractivo\l"
	.string "muy energético?$"

@ Unused
SlateportCity_ContestHall_Text_HyperRankStage:
	.string "CONCURSOS POKéMON\n"
	.string "¡ESCENARIO RANGO HIPER!$"

