.set LOCALID_FAT_MAN, 1
.set LOCALID_MAN_1, 2
.set LOCALID_RICH_BOY, 3
.set LOCALID_GRUNT_1, 5
.set LOCALID_COOK, 6
.set LOCALID_OLD_WOMAN, 7
.set LOCALID_GIRL, 8
.set LOCALID_TY, 9
.set LOCALID_GABBY, 10
.set LOCALID_CAPT_STERN, 11
.set LOCALID_GRUNT_2, 18
.set LOCALID_GRUNT_3, 19
.set LOCALID_GRUNT_4, 26
.set LOCALID_GRUNT_5, 27
.set LOCALID_GRUNT_6, 28
.set LOCALID_GRUNT_7, 29
.set LOCALID_GRUNT_8, 30
.set LOCALID_GRUNT_9, 31
.set LOCALID_GRUNT_11, 33
.set LOCALID_SCOTT, 35

@ Note: LOCALID_SLATEPORT_ENERGY_GURU is a local id for this map used elsewhere. It's defined in event_objects.h

SlateportCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_OnFrame
	.byte 0

SlateportCity_OnTransition:
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 0
	call SlateportCity_EventScript_EnterSlateport
	call_if_eq VAR_GARBAGEVAR, 1, SlateportCity_EventScript_MovePeopleForSternInterview
	call_if_eq VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_SetReadyForScottScene
	end

SlateportCity_EventScript_EnterSlateport::
	setflag FLAG_VISITED_MAHOGANY_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_GARBAGEFLAG
	return

SlateportCity_EventScript_MovePeopleForSternInterview::
	setobjectxyperm LOCALID_CAPT_STERN, 28, 13
	setobjectxyperm LOCALID_OLD_WOMAN, 25, 13
	setobjectxyperm LOCALID_RICH_BOY, 25, 14
	setobjectxyperm LOCALID_COOK, 27, 16
	setobjectxyperm LOCALID_GIRL, 28, 16
	setobjectxyperm LOCALID_FAT_MAN, 29, 16
	setobjectxyperm LOCALID_MAN_1, 31, 14
	setobjectmovementtype LOCALID_CAPT_STERN, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_OLD_WOMAN, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT
	setobjectmovementtype LOCALID_RICH_BOY, MOVEMENT_TYPE_FACE_UP_AND_RIGHT
	setobjectmovementtype LOCALID_COOK, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_GIRL, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_FAT_MAN, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_MAN_1, MOVEMENT_TYPE_FACE_LEFT
	return

SlateportCity_EventScript_SetReadyForScottScene::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 30, SlateportCity_EventScript_MoveScottLeft
	setobjectxyperm LOCALID_SCOTT, 23, 27
	setobjectmovementtype LOCALID_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_EventScript_MoveScottLeft::
	setobjectxyperm LOCALID_SCOTT, 22, 27
	setobjectmovementtype LOCALID_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_OnFrame:
	map_script_2 VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_ScottScene
	.2byte 0

SlateportCity_EventScript_ScottScene::
	lockall
	addobject LOCALID_SCOTT
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Movement_PlayerFaceScott
	applymovement LOCALID_SCOTT, SlateportCity_Movement_ScottApproachPlayer
	waitmovement 0
	msgbox SlateportCity_Text_YouDroveTeamAquaAway, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 60
	msgbox SlateportCity_Text_MaybeThisTrainer, MSGBOX_DEFAULT
	applymovement LOCALID_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_Text_LetsRegisterEachOther, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SlateportCity_Text_RegisteredScott, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_SCOTT_MATCH_CALL
	msgbox SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, SlateportCity_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SCOTT
	setobjectxyperm LOCALID_SCOTT, 10, 12
	setobjectmovementtype LOCALID_SCOTT, MOVEMENT_TYPE_FACE_DOWN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 2
	addvar VAR_SCOTT_STATE, 1
	releaseall
	end

SlateportCity_Movement_PlayerFaceScott:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_ScottApproachPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_Movement_ScottExit:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_EventScript_EnergyGuru::
	lock
	faceplayer
	message SlateportCity_Text_EnergyGuruSellWhatYouNeed
	waitmessage
	pokemart SlateportCity_Pokemart_EnergyGuru
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_EnergyGuru:
	.2byte ITEM_PROTEIN
	.2byte ITEM_IRON
	.2byte ITEM_CARBOS
	.2byte ITEM_ZINC
	.2byte ITEM_CALCIUM
	.2byte ITEM_HP_UP
	.2byte ITEM_NONE
	release
	end

SlateportCity_EventScript_EffortRibbonWoman::
	lock
	faceplayer
	bufferleadmonspeciesname STR_VAR_1
	msgbox SlateportCity_Text_OhYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, LeadMonHasEffortRibbon
	call_if_eq VAR_RESULT, TRUE, SlateportCity_EventScript_MonHasEffortRibbon
	specialvar VAR_RESULT, Special_AreLeadMonEVsMaxedOut
	call_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_MonEVsNotMaxed
	msgbox SlateportCity_Text_PleaseGiveItThisEffortRibbon, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_Text_ReceivedEffortRibbon
	waitfanfare
	msgbox SlateportCity_Text_PutEffortRibbonOnMon, MSGBOX_DEFAULT
	special GiveLeadMonEffortRibbon
	release
	end

SlateportCity_EventScript_MonEVsNotMaxed::
	msgbox SlateportCity_Text_GoForItLittleHarder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_MonHasEffortRibbon::
	msgbox SlateportCity_Text_EffortRibbonLooksGoodOnIt, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Cook::
	lock
	faceplayer
	call_if_eq VAR_GARBAGEVAR, 1, SlateportCity_EventScript_CookSternInterview
	msgbox SlateportCity_Text_SeaweedFullOfLife, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_CookSternInterview::
	msgbox SlateportCity_Text_CaptainComeBackWithBigFish, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWoman::
	lock
	faceplayer
	call_if_eq VAR_GARBAGEVAR, 1, SlateportCity_EventScript_OldWomanSternInterview
	msgbox SlateportCity_Text_HowTownIsBornAndGrows, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWomanSternInterview::
	msgbox SlateportCity_Text_CaptSternBeingInterviewed, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Girl::
	lock
	faceplayer
	call_if_eq VAR_GARBAGEVAR, 1, SlateportCity_EventScript_GirlSternInterview
	goto_if_set FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_GirlSecretBase
	msgbox SlateportCity_Text_SlateportWonderfulPlace, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSternInterview::
	msgbox SlateportCity_Text_InterviewerSoCool, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSecretBase::
	msgbox SlateportCity_Text_BuyBricksSoDecorWontGetDirty, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoy::
	lock
	faceplayer
	call_if_eq VAR_GARBAGEVAR, 1, SlateportCity_EventScript_RichBoySternInterview
	msgbox SlateportCity_Text_GoingToCompeteInBattleTent, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoySternInterview::
	msgbox SlateportCity_Text_SternSaysDiscoveredSomething, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_FatMan::
	goto_if_eq VAR_GARBAGEVAR, 1, SlateportCity_EventScript_FatManSternInterview
	msgbox SlateportCity_Text_BushedHikingFromMauville, MSGBOX_NPC
	end

SlateportCity_EventScript_FatManSternInterview::
	msgbox SlateportCity_Text_AmIOnTV, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man1::
	lock
	faceplayer
	call_if_eq VAR_GARBAGEVAR, 1, SlateportCity_EventScript_Man1SternInterview
	msgbox SlateportCity_Text_EveryoneCallsHimCaptStern, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Man1SternInterview::
	msgbox SlateportCity_Text_CaptainsACelebrity, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1::
	lock
	faceplayer
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_EventScript_Woman1AquaGone
	msgbox SlateportCity_Text_WhatsLongLineOverThere, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1AquaGone::
	msgbox SlateportCity_Text_VisitedMuseumOften, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_BattleTentSign::
	msgbox SlateportCity_Text_BattleTentSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_SternsShipyardSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_SternsShipyardFerryComplete
	goto_if_set FLAG_BADGE07_GET, SlateportCity_EventScript_SternsShipyardNearsCompletion
	msgbox SlateportCity_Text_SternsShipyardWantedSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardNearsCompletion::
	msgbox SlateportCity_Text_SternsShipyardNearsCompletion, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardFerryComplete::
	msgbox SlateportCity_Text_SternsShipyardFerryComplete, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_PokemonFanClubSign::
	msgbox SlateportCity_Text_PokemonFanClubSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_OceanicMuseumSign::
	msgbox SlateportCity_Text_OceanicMuseumSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_CitySign::
	msgbox SlateportCity_Text_CitySign, MSGBOX_SIGN
	end

SlateportCity_EventScript_MarketSign::
	msgbox SlateportCity_Text_MarketSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_HarborSignFerryComplete
	msgbox SlateportCity_Text_HarborFerryUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_HarborSignFerryComplete::
	msgbox SlateportCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_NameRatersHouseSign::
	msgbox SlateportCity_Text_NameRatersHouseSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_Maniac::
	lock
	faceplayer
	call_if_eq VAR_GARBAGEVAR, 1, SlateportCity_EventScript_ManiacSternInterview
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

@ Unclear if the text here was meant to be different, but its not
SlateportCity_EventScript_ManiacSternInterview::
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman2::
	msgbox SlateportCity_Text_CantChangeTradeMonName, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor1::
	msgbox SlateportCity_Text_SeaIsSoWet, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor2::
	msgbox SlateportCity_Text_SinkOldBoats, MSGBOX_NPC
	end

SlateportCity_EventScript_PokefanF::
	msgbox SlateportCity_Text_BuyTooMuch, MSGBOX_NPC
	end

SlateportCity_EventScript_Man2::
	msgbox SlateportCity_Text_BattleTentBuiltRecently, MSGBOX_NPC
	end

SlateportCity_EventScript_AquaGrunt1::
	lock
	faceplayer
	msgbox SlateportCity_Text_QuitPushing, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt2::
	lock
	faceplayer
	msgbox SlateportCity_Text_AquaHasPolicy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt3::
	lock
	faceplayer
	msgbox SlateportCity_Text_BossIsBrilliant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt4::
	lock
	faceplayer
	msgbox SlateportCity_Text_WhatsNewSchemeIWonder, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt5::
	lock
	faceplayer
	msgbox SlateportCity_Text_ShouldTakeItAll, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_5, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt6::
	lock
	faceplayer
	msgbox SlateportCity_Text_DontButtIn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_6, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt7::
	lock
	faceplayer
	msgbox SlateportCity_Text_RemindsMeOfLongLineForGames, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_7, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt8::
	lock
	faceplayer
	msgbox SlateportCity_Text_WhyAreWeLiningUp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_8, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt9::
	lock
	faceplayer
	playse SE_PIN
	applymovement LOCALID_GRUNT_9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GRUNT_9, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_Text_WhatDoYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_Text_IllReadSignForYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	msgbox SlateportCity_Text_SaysSomethingLikeSeaIsEndless, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_Movement_DelayAquaGrunt:
	delay_16
	delay_16
	step_end

SlateportCity_EventScript_AquaGrunt10::
	msgbox SlateportCity_Text_ShouldveBroughtMyGameBoy, MSGBOX_SIGN
	end

SlateportCity_EventScript_AquaGrunt11::
	lock
	faceplayer
	msgbox SlateportCity_Text_HotSpringsAfterOperation, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_11, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_DollClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor_Dolls
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor_Dolls:
	.2byte DECOR_AZURILL_DOLL
	.2byte DECOR_MARILL_DOLL
	.2byte DECOR_SKITTY_DOLL
	.2byte DECOR_NONE
	release
	end

SlateportCity_EventScript_ComeBackWithSecretPower::
	msgbox gText_ComeBackWithSecretPower, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_DecorClerk::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_ComeBackWithSecretPower
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor:
	.2byte DECOR_RED_BRICK
	.2byte DECOR_BLUE_BRICK
	.2byte DECOR_YELLOW_BRICK
	.2byte DECOR_RED_BALLOON
	.2byte DECOR_BLUE_BALLOON
	.2byte DECOR_YELLOW_BALLOON
	.2byte DECOR_C_LOW_NOTE_MAT
	.2byte DECOR_D_NOTE_MAT
	.2byte DECOR_E_NOTE_MAT
	.2byte DECOR_F_NOTE_MAT
	.2byte DECOR_G_NOTE_MAT
	.2byte DECOR_A_NOTE_MAT
	.2byte DECOR_B_NOTE_MAT
	.2byte DECOR_C_HIGH_NOTE_MAT
	.2byte DECOR_NONE
	release
	end

SlateportCity_EventScript_PowerTMClerk::
	goto_if_set FLAG_FINITE_TMS, SlateportCity_EventScript_PowerTMClerkFinite
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SlateportCity_Pokemart_PowerTMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs:
	.2byte ITEM_SEA_INCENSE
	.2byte ITEM_LAX_INCENSE
	.2byte ITEM_NONE
	release
	end

SlateportCity_EventScript_PowerTMClerkFinite::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SlateportCity_Pokemart_PowerTMs2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs2:
	.2byte ITEM_TM_HIDDEN_POWER
	.2byte ITEM_TM_SECRET_POWER
	.2byte ITEM_SEA_INCENSE
	.2byte ITEM_LAX_INCENSE
	.2byte ITEM_NONE
	release
	end

@ Scene with Capt Sterns interview and Team Aqua announcing plans to steal Submarine
SlateportCity_EventScript_CaptStern::
	lockall
	msgbox SlateportCity_Text_SternMoveAheadWithExploration, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_GabbyWonderfulThanksForInterview, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GABBY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 10
	applymovement LOCALID_TY, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 25
	applymovement LOCALID_CAPT_STERN, SlateportCity_Movement_SternWatchGabbyAndTyExit
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Movement_PlayerFaceStern
	applymovement LOCALID_GABBY, SlateportCity_Movement_GabbyExit
	applymovement LOCALID_TY, SlateportCity_Movement_TyExit
	waitmovement 0
	removeobject LOCALID_GABBY
	removeobject LOCALID_TY
	msgbox SlateportCity_Text_SternWhewFirstInterview, MSGBOX_DEFAULT
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Text_OhPlayerWeMadeDiscovery, MSGBOX_DEFAULT
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox SlateportCity_Text_AquaWillAssumeControlOfSubmarine, MSGBOX_DEFAULT
	applymovement LOCALID_COOK, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_FAT_MAN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_OLD_WOMAN, SlateportCity_Movement_OldWomanConcern
	applymovement LOCALID_RICH_BOY, Common_Movement_QuestionMark
	applymovement LOCALID_MAN_1, SlateportCity_Movement_ManConcern
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SlateportCity_Text_SternWhatWasAllThat, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_CAPT_STERN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Text_FromHarborTryingToTakeSub, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CAPT_STERN, SlateportCity_Movement_SternEnterHarbor
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Movement_PlayerEnterHarbor
	waitmovement 0
	removeobject LOCALID_CAPT_STERN
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	setvar VAR_GARBAGEVAR, 2
	warp MAP_SLATEPORT_CITY_HARBOR, 11, 14
	waitstate
	releaseall
	end

SlateportCity_Movement_OldWomanConcern:
	delay_16
	delay_16
	emote_question_mark
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_ManConcern:
	emote_question_mark
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_GabbyExit:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_Movement_TyExit:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_Movement_Unused:
	walk_down
	walk_in_place_faster_up
	step_end

SlateportCity_Movement_SternEnterHarbor:
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_Movement_SternWatchGabbyAndTyExit:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_down
	walk_left
	step_end

SlateportCity_Movement_PlayerEnterHarbor:
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_right
	walk_up
	step_end

SlateportCity_Movement_PlayerFaceStern:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_EventScript_Ty::
	msgbox SlateportCity_Text_BigSmileForCamera, MSGBOX_SIGN
	end

SlateportCity_EventScript_Gabby::
	msgbox SlateportCity_Text_MostInvaluableExperience, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man3::
	msgbox SlateportCity_Text_WonderIfLighthouseStartlesPokemon, MSGBOX_NPC
	end

SlateportCity_EventScript_BerryPowderClerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POWDER_JAR, SlateportCity_EventScript_ReceivedPowderJar
	msgbox SlateportCity_Text_ExplainBerries, MSGBOX_DEFAULT
	giveitem ITEM_POWDER_JAR
	setflag FLAG_RECEIVED_POWDER_JAR
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ReceivedPowderJar::
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_ExplainBerryPowder
	msgbox SlateportCity_Text_BroughtMeSomeBerryPowder, MSGBOX_DEFAULT
	special DisplayBerryPowderVendorMenu
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ExplainBerryPowder::
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ChooseBerryPowderItem::
	message SlateportCity_Text_ExchangeWhatWithIt
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BERRY_POWDER_VENDOR
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, SlateportCity_EventScript_EnergyPowder
	case 1, SlateportCity_EventScript_EnergyRoot
	case 2, SlateportCity_EventScript_HealPowder
	case 3, SlateportCity_EventScript_RevivalHerb
	case 4, SlateportCity_EventScript_Protein
	case 5, SlateportCity_EventScript_Iron
	case 6, SlateportCity_EventScript_Carbos
	case 7, SlateportCity_EventScript_Calcium
	case 8, SlateportCity_EventScript_Zinc
	case 9, SlateportCity_EventScript_HPUp
	case 10, SlateportCity_EventScript_PPUp
	case 11, SlateportCity_EventScript_CancelPowderItemSelect
	case MULTI_B_PRESSED, SlateportCity_EventScript_CancelPowderItemSelect
	end

SlateportCity_EventScript_EnergyPowder::
	bufferitemname STR_VAR_1, ITEM_ENERGY_POWDER
	setvar VAR_0x8008, ITEM_ENERGY_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_EnergyRoot::
	bufferitemname STR_VAR_1, ITEM_ENERGY_ROOT
	setvar VAR_0x8008, ITEM_ENERGY_ROOT
	setvar VAR_0x8009, 80
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HealPowder::
	bufferitemname STR_VAR_1, ITEM_HEAL_POWDER
	setvar VAR_0x8008, ITEM_HEAL_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_RevivalHerb::
	bufferitemname STR_VAR_1, ITEM_REVIVAL_HERB
	setvar VAR_0x8008, ITEM_REVIVAL_HERB
	setvar VAR_0x8009, 300
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Protein::
	bufferitemname STR_VAR_1, ITEM_PROTEIN
	setvar VAR_0x8008, ITEM_PROTEIN
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Iron::
	bufferitemname STR_VAR_1, ITEM_IRON
	setvar VAR_0x8008, ITEM_IRON
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Carbos::
	bufferitemname STR_VAR_1, ITEM_CARBOS
	setvar VAR_0x8008, ITEM_CARBOS
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Calcium::
	bufferitemname STR_VAR_1, ITEM_CALCIUM
	setvar VAR_0x8008, ITEM_CALCIUM
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Zinc::
	bufferitemname STR_VAR_1, ITEM_ZINC
	setvar VAR_0x8008, ITEM_ZINC
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HPUp::
	bufferitemname STR_VAR_1, ITEM_HP_UP
	setvar VAR_0x8008, ITEM_HP_UP
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_PPUp::
	bufferitemname STR_VAR_1, ITEM_PP_UP
	setvar VAR_0x8008, ITEM_PP_UP
	setvar VAR_0x8009, 3000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_CancelPowderItemSelect::
	msgbox SlateportCity_Text_ComeBackToTradeBerryPowder, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_TryBuyBerryPowderItem::
	msgbox SlateportCity_Text_ExchangeBerryPowderForItem, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_EventScript_ChooseBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	specialvar VAR_RESULT, HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_NotEnoughBerryPowder
	giveitem VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_NoRoomForBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	special TakeBerryPowder
	special PrintPlayerBerryPowderAmount
	msgbox SlateportCity_Text_FineBerryPowderTradeSomethingElse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_EventScript_ChooseBerryPowderItem
	msgbox SlateportCity_Text_WhenYouGetMoreBringItToMe, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NoRoomForBerryPowderItem::
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NotEnoughBerryPowder::
	msgbox SlateportCity_Text_DontHaveEnoughBerryPowder, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ScottBattleTentScene::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	opendoor 10, 12
	waitdooranim
	addobject LOCALID_SCOTT
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Movement_PushPlayerDown
	applymovement LOCALID_SCOTT, SlateportCity_Movement_ScottExitBattleTent
	waitmovement 0
	closedoor 10, 12
	waitdooranim
	msgbox SlateportCity_Text_TakingBattleTentChallenge, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, SlateportCity_Movement_ScottExitAfterBattleTent
	waitmovement 0
	removeobject LOCALID_SCOTT
	addvar VAR_SCOTT_STATE, 1
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	releaseall
	end

SlateportCity_Movement_PushPlayerDown:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

SlateportCity_Movement_PlayerWatchScottExit:
	delay_16
	walk_in_place_faster_right
	step_end

SlateportCity_Movement_ScottExitBattleTent:
	delay_8
	walk_down
	step_end

SlateportCity_Movement_ScottExitAfterBattleTent:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_EventScript_BerryCrushRankingsSign::
	lockall
	special ShowBerryCrushRankings
	waitstate
	releaseall
	end

SlateportCity_Text_EnergyGuruSellWhatYouNeed:
	.string "¡Soy el GURÚ DE LA ENERGÍA! ¡Daré\n"
	.string "todo y te venderé lo que necesites!$"

SlateportCity_Text_OhYourPokemon:
	.string "¿Oh?\n"
	.string "Tu {STR_VAR_1}…$"

SlateportCity_Text_PleaseGiveItThisEffortRibbon:
	.string "¡Se esforzó estupendamente!\p"
	.string "Como premio, dale esta\n"
	.string "CINTA ESFUERZO.$"

SlateportCity_Text_ReceivedEffortRibbon:
	.string "{PLAYER} recibió la CINTA ESFUERZO.$"

SlateportCity_Text_PutEffortRibbonOnMon:
	.string "{PLAYER} le puso la CINTA ESFUERZO\n"
	.string "a {STR_VAR_1}.$"

SlateportCity_Text_GoForItLittleHarder:
	.string "Debes esforzarte un poco más.\p"
	.string "Si lo haces, le daré a tu POKéMON\n"
	.string "algo lindo.$"

SlateportCity_Text_EffortRibbonLooksGoodOnIt:
	.string "¡Oh! ¡A tu {STR_VAR_1} le queda\n"
	.string "bien esa CINTA ESFUERZO!$"

SlateportCity_Text_WonderIfLighthouseStartlesPokemon:
	.string "La luz del faro llega a decenas\n"
	.string "de millas de distancia.\p"
	.string "Me pregunto si no asustará a los\n"
	.string "POKéMON del mar.$"

SlateportCity_Text_SeaweedFullOfLife:
	.string "¡Mira esto!\p"
	.string "El alga de esta zona es fresca\n"
	.string "y llena de vida.\p"
	.string "¡Parece que puede hasta levantarse\n"
	.string "y atacar!$"

SlateportCity_Text_HowTownIsBornAndGrows:
	.string "Donde el agua es limpia, abundan\n"
	.string "los frutos de la cosecha.\p"
	.string "Y donde la gente se reúne, nace\n"
	.string "un mercado.\p"
	.string "Así es como un pueblo nace y crece.$"

SlateportCity_Text_SlateportWonderfulPlace:
	.string "Comprar sintiendo el aroma del\n"
	.string "océano...\p"
	.string "¡PORTALUAR es un lugar maravilloso!$"

SlateportCity_Text_BuyBricksSoDecorWontGetDirty:
	.string "Si pongo MUÑECOS o COJINES en el\n"
	.string "suelo, se ensucian.\p"
	.string "Compraré LADRILLOS para que no se\n"
	.string "ensucien al dejarlos fuera.\l"
	.string "$"

SlateportCity_Text_GoingToCompeteInBattleTent:
	.string "¡Roaaar! ¡Yo también lucharé en\n"
	.string "la CARPA DE COMBATE!\p"
	.string "¡Pero antes, debo capturar algunos\n"
	.string "POKéMON!$"

SlateportCity_Text_BushedHikingFromMauville:
	.string "Uff... estoy agotado...\p"
	.string "Vine caminando desde CIUDAD MALVA.\n"
	.string "Pero vaya, esta ciudad es enorme.\p"
	.string "Si lo hubiera sabido, habría\n"
	.string "venido en BIKE.$"

SlateportCity_Text_EveryoneCallsHimCaptStern:
	.string "STERN, quien construyó el MUSEO,\n"
	.string "también lidera un equipo de\l"
	.string "exploración submarina.\p"
	.string "Por eso todos lo llaman CAPT. STERN.$"

SlateportCity_Text_WhatsLongLineOverThere:
	.string "¿Qué hay allá?\n"
	.string "Esa fila tan larga...$"

SlateportCity_Text_VisitedMuseumOften:
	.string "De niño, visitaba mucho el\n"
	.string "MUSEO.\p"
	.string "Soñaba con los misterios del mar\n"
	.string "al ver las exhibiciones.$"

SlateportCity_Text_QuitPushing:
	.string "¡Oye! ¡Deja de empujar!\n"
	.string "Esta es la fila, ¿no lo ves?$"

SlateportCity_Text_AquaHasPolicy:
	.string "El TEAM AQUA se reúne y se\n"
	.string "dispersa en el lugar de la\l"
	.string "operación.$"

SlateportCity_Text_BossIsBrilliant:
	.string "Nuestro JEFE es brillante.\p"
	.string "¿Qué querría hacer ahora con\n"
	.string "un MUSEO?$"

SlateportCity_Text_WhatsNewSchemeIWonder:
	.string "¿Cuál será el nuevo plan?\p"
	.string "El JEFE da miedo cuando se enoja,\n"
	.string "mejor no arruinarlo...$"

SlateportCity_Text_ShouldTakeItAll:
	.string "¡Si hay algo que necesitemos en\n"
	.string "el MUSEO, tomémoslo todo!$"

SlateportCity_Text_DontButtIn:
	.string "¡Oye, tú!\n"
	.string "¡No te metas!$"

SlateportCity_Text_RemindsMeOfLongLineForGames:
	.string "Una fila larga, ¿eh?\p"
	.string "Me recuerda cuando hacía fila para\n"
	.string "comprar juegos exitosos...$"

SlateportCity_Text_WhyAreWeLiningUp:
	.string "¿Para qué hacemos fila y pagamos?\n"
	.string "¡Deberíamos entrar así nada más!$"

SlateportCity_Text_WhatDoYouWant:
	.string "¿Qué?\n"
	.string "¿Qué quieres?$"

SlateportCity_Text_IllReadSignForYou:
	.string "¿Quieres leer este cartel?\n"
	.string "¡Yo lo leeré por ti!$"

SlateportCity_Text_SaysSomethingLikeSeaIsEndless:
	.string "Veamos...\p"
	.string "Eh... Creo que dice algo como\n"
	.string "la vida en el mar es infinita.\p"
	.string "Sí, estoy seguro de que eso es\n"
	.string "lo que dice.$"

SlateportCity_Text_ShouldveBroughtMyGameBoy:
	.string "Grrr...\p"
	.string "Debí traer mi Game Boy Advance\n"
	.string "para no aburrirme en la fila...\p"
	.string "Grrr...$"

SlateportCity_Text_HotSpringsAfterOperation:
	.string "Cuando termine la operación, ¡me\n"
	.string "llevará a un spa termal!\p"
	.string "Eso dijo nuestro líder.\n"
	.string "¡No puedo esperar!$"

SlateportCity_Text_SeaIsSoWet:
	.string "El mar es tan vasto...\p"
	.string "¿Será que el mar se formó con las\n"
	.string "lágrimas de los POKéMON?$"

SlateportCity_Text_SinkOldBoats:
	.string "¿Sabes qué hacen con los barcos\n"
	.string "viejos que ya no pueden navegar?\p"
	.string "Los hunden para que sean el\n"
	.string "hábitat de los POKéMON.$"

SlateportCity_Text_BuyTooMuch:
	.string "Cada vez que vengo aquí, me emociono\n"
	.string "y compro demasiadas cosas.$"

SlateportCity_Text_GetNameRaterToHelpYou:
	.string "Si quieres cambiar el apodo de tu\n"
	.string "POKéMON, ve con el EVALUADOR\l"
	.string "de nombres.$"

SlateportCity_Text_CantChangeTradeMonName:
	.string "Si recibes un POKéMON por cambio,\n"
	.string "no podrás cambiar su apodo.\p"
	.string "El amor del ENTRENADOR original\n"
	.string "está en ese apodo.$"

SlateportCity_Text_BattleTentBuiltRecently:
	.string "Hace poco pusieron una CARPA DE\n"
	.string "LUCHA en FOGONAL.\p"
	.string "Los GIMNASIOS son geniales, pero la\n"
	.string "CARPA DE LUCHA es increíble.\p"
	.string "¡Busca POKéMON fuertes para la\n"
	.string "CARPA DE LUCHA!$"

SlateportCity_Text_CaptSternBeingInterviewed:
	.string "Esperaba que fuera una estrella\n"
	.string "para pedirle un autógrafo.\p"
	.string "¿Pero quién es el entrevistado?\n"
	.string "¿No es el CAPT. STERN?$"

SlateportCity_Text_InterviewerSoCool:
	.string "La entrevistadora es genial\n"
	.string "y muy linda.\p"
	.string "¡Cuando crezca, seré una\n"
	.string "periodista internacional!$"

SlateportCity_Text_SternSaysDiscoveredSomething:
	.string "El CAPT. STERN dice que hallaron\n"
	.string "algo en el fondo del mar.\p"
	.string "Me pregunto qué será.\n"
	.string "¿Qué podrá ser?$"

SlateportCity_Text_CaptainComeBackWithBigFish:
	.string "¿Qué pasa aquí?\p"
	.string "¿El buen CAPITÁN volvió con\n"
	.string "un pez gigante del fondo del mar?$"

SlateportCity_Text_AmIOnTV:
	.string "¡Oye! ¿Estás viendo?\n"
	.string "¿Salgo en la TV?$"

SlateportCity_Text_CaptainsACelebrity:
	.string "¡Una entrevista! ¡Aquí!\n"
	.string "¡El CAPITÁN es famoso!$"

SlateportCity_Text_BigSmileForCamera:
	.string "TY: Bien, CAPT. STERN, ¡una gran\n"
	.string "sonrisa para la cámara!$"

SlateportCity_Text_MostInvaluableExperience:
	.string "GABBY: Ya veo. Ha tenido una\n"
	.string "experiencia invaluable…$"

SlateportCity_Text_SternMoveAheadWithExploration:
	.string "CAPT. STERN: Sí, así es. Planeamos\n"
	.string "seguir con nuestra exploración.$"

SlateportCity_Text_GabbyWonderfulThanksForInterview:
	.string "GABBY: ¡Es genial, CAPT. STERN!\n"
	.string "Gracias por sacar tiempo de su\l"
	.string "agenda para hablar con nosotros.\p"
	.string "¡Esperamos entrevistarlo de nuevo\n"
	.string "con más noticias de descubrimientos!$"

SlateportCity_Text_SternWhewFirstInterview:
	.string "CAPT. STERN: Uff…\p"
	.string "Fue mi primera vez en la TV.\n"
	.string "Estaba muy nervioso.$"

SlateportCity_Text_OhPlayerWeMadeDiscovery:
	.string "¡Oh! {PLAYER}{KUN}!\n"
	.string "¡Te ves muy bien!\p"
	.string "Hicimos un gran hallazgo en nuestra\n"
	.string "última exploración marina.\p"
	.string "Hallamos una caverna submarina en\n"
	.string "la RUTA 128.\p"
	.string "Creemos que es el hábitat de un\n"
	.string "POKéMON que se creía extinto.$"

SlateportCity_Text_AquaWillAssumeControlOfSubmarine:
	.string "Fufufu…\n"
	.string "CAPITÁN STERN, supongo.\p"
	.string "¡Nosotros, el TEAM AQUA, tomaremos\n"
	.string "el control de su submarino!\p"
	.string "¡Sus objeciones no importan!\n"
	.string "¡Esperamos su total cooperación!\p"
	.string "Fufufu…\n"
	.string "¡Mire y aprenda lo que el TEAM\l"
	.string "AQUA ha planeado!$"

SlateportCity_Text_SternWhatWasAllThat:
	.string "CAPITÁN STERN: ¿Qué fue eso?\p"
	.string "Sonó como alguien usando\n"
	.string "un megáfono…\p"
	.string "¿De dónde vino?$"

SlateportCity_Text_FromHarborTryingToTakeSub:
	.string "¡Viene del PUERTO!\p"
	.string "¡El submarino!\n"
	.string "¡Intentan robárselo!$"

SlateportCity_Text_PleaseComeWithMe:
	.string "{PLAYER}{KUN}!\n"
	.string "¡Por favor, ven conmigo!$"

SlateportCity_Text_BattleTentSign:
	.string "TIENDA BATALLA DE FONDA PORTAL\n"
	.string "“¡Búscalo! ¡El POKéMON definitivo!”$"

SlateportCity_Text_SternsShipyardWantedSign:
	.string "ASTILLERO DE STERN\p"
	.string "“Se busca: Marinero capaz de navegar\n"
	.string "en cualquier corriente.”$"

SlateportCity_Text_SternsShipyardNearsCompletion:
	.string "ASTILLERO DE STERN\p"
	.string "“El ferry S.S. TIDAL casi está\n"
	.string "listo para servir a los puertos de\l"
	.string "FONDA PORTAL y CIUDAD VERANO.”$"

SlateportCity_Text_SternsShipyardFerryComplete:
	.string "ASTILLERO DE STERN\p"
	.string "“El embarque al ferry S.S. TIDAL\n"
	.string "hacia LILYCOVE se hace en el\l"
	.string "PUERTO.”$"

SlateportCity_Text_PokemonFanClubSign:
	.string "CLUB DE FANS POKéMON\n"
	.string "“¡Llamamos a todos los fans!”$"

SlateportCity_Text_OceanicMuseumSign:
	.string "“El mar infinito sostiene\n"
	.string "toda la vida.”\p"
	.string "MUSEO OCEÁNICO$"

SlateportCity_Text_CitySign:
	.string "CIUDAD PORTALON\p"
	.string "“El puerto donde personas y\n"
	.string "POKéMON se encuentran.”$"

SlateportCity_Text_MarketSign:
	.string "MERCADO DE PORTALON\n"
	.string "“¡Objetos únicos y exclusivos!”$"

SlateportCity_Text_HarborFerryUnderConstruction:
	.string "PUERTO DE PORTALON\p"
	.string "“El ferry S.S. TIDAL se construye\n"
	.string "en el ASTILLERO.\p"
	.string "“El servicio comenzará\n"
	.string "muy pronto.”$"

SlateportCity_Text_HarborSign:
	.string "PUERTO DE PORTALON\p"
	.string "“Disfruta de un gran crucero en\n"
	.string "el ferry S.S. TIDAL.”$"

SlateportCity_Text_NameRatersHouseSign:
	.string "CASA DEL EVALUADOR\n"
	.string "“Evaluamos apodos de POKéMON.”$"

SlateportCity_Text_ExplainBerries:
	.string "Si un POKéMON salvaje se hiere,\n"
	.string "se cura comiendo BAYAS.\p"
	.string "¿Lo sabías?\p"
	.string "Alguien vio eso y tuvo la idea\n"
	.string "de hacer medicinas con BAYAS.\p"
	.string "¿Lo sabías?\p"
	.string "Para hacer medicinas con BAYAS,\n"
	.string "deben triturarse en polvo.\p"
	.string "¿Lo sabías?\p"
	.string "¡Parece que te interesan\n"
	.string "las BAYAS!\p"
	.string "Tengo algo bueno para alguien\n"
	.string "como tú.$"

SlateportCity_Text_ExplainBerryPowder:
	.string "Puse máquinas en los\n"
	.string "CENTROS POKéMON para triturar BAYAS.\p"
	.string "Están en el RINCÓN DIRECTO\n"
	.string "del piso de arriba.\p"
	.string "¿Lo sabías?\p"
	.string "¿Podrías hacerme POLVO BAYA\n"
	.string "usando esas máquinas?\p"
	.string "Haré medicinas si me traes\n"
	.string "mucho POLVO BAYA.$"

SlateportCity_Text_BroughtMeSomeBerryPowder:
	.string "¿Me trajiste algo de\n"
	.string "POLVO BAYA?$"

SlateportCity_Text_ExchangeWhatWithIt:
	.string "¿Por qué te gustaría\n"
	.string "cambiarlo?$"

SlateportCity_Text_ExchangeBerryPowderForItem:
	.string "Bien, ¿quieres cambiar tu\n"
	.string "POLVO BAYA por un {STR_VAR_1}?$"

SlateportCity_Text_DontHaveEnoughBerryPowder:
	.string "Vaya. No tienes suficiente\n"
	.string "POLVO BAYA.$"

SlateportCity_Text_FineBerryPowderTradeSomethingElse:
	.string "Este POLVO BAYA es bueno.\n"
	.string "Servirá para medicinas excelentes.\p"
	.string "¿Quieres cambiar más\n"
	.string "POLVO BAYA por otra cosa?$"

SlateportCity_Text_WhenYouGetMoreBringItToMe:
	.string "¡Bien! Cuando tengas más\n"
	.string "POLVO BAYA, ¡tráemelo, por favor!$"

SlateportCity_Text_ComeBackToTradeBerryPowder:
	.string "Vuelve si quieres cambiar tu\n"
	.string "POLVO BAYA por medicinas.\p"
	.string "Siempre tengo un bazar aquí.\p"
	.string "¿Lo sabías?$"

SlateportCity_Text_YouDroveTeamAquaAway:
	.string "SCOTT: ¿Eh?\n"
	.string "Seguro que te vi en algún lado.\p"
	.string "¿Me he presentado ya?\n"
	.string "Si no, me llamo SCOTT.\p"
	.string "Vi al TEAM AQUA huir de aquí\n"
	.string "como si los hubieran picado.\p"
	.string "Déjame adivinar... ¿los echaste?$"

SlateportCity_Text_MaybeThisTrainer:
	.string "SCOTT: Hmm…\n"
	.string "Tal vez, solo tal vez, este ENTRENADOR…$"

SlateportCity_Text_LetsRegisterEachOther:
	.string "SCOTT: ¡Bien! Creo que seremos\n"
	.string "buenos amigos.\p"
	.string "Registrémonos mutuamente en el\n"
	.string "POKéNAV.\p"
	.string "... ... ... ... ... ...$"

SlateportCity_Text_RegisteredScott:
	.string "Registraste a SCOTT\n"
	.string "en el POKéNAV.$"

SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou:
	.string "SCOTT: Me gustaría acompañarte,\n"
	.string "pero quiero ver el talento de\l"
	.string "otras personas también.\p"
	.string "Así que iré a recorrer otros\n"
	.string "pueblos un poco más.\p"
	.string "¡Nos vemos, {PLAYER}{KUN}!$"

SlateportCity_Text_TakingBattleTentChallenge:
	.string "SCOTT: ¡Oh, hola!\n"
	.string "¡Si es {PLAYER}{KUN}!\p"
	.string "{PLAYER}{KUN}, deja que adivine... ¿vas\n"
	.string "al reto de la BATTLE TENT?\p"
	.string "¡Sí! ¡Es una buena idea!\n"
	.string "¡Es una idea genial!\p"
	.string "Un TRAINER fuerte es ideal\n"
	.string "para la BATTLE TENT.\p"
	.string "¡Da lo mejor de ti!$"
