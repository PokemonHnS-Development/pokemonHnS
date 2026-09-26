.set LOCALID_ATTENDANT_SINGLES, 1
.set LOCALID_ATTENDANT_DOUBLES, 7
.set LOCALID_ATTENDANT_MULTIS, 8
.set LOCALID_ATTENDANT_LINK_MULTIS, 9

@ Note: LOCALID_BATTLE_TOWER_LOBBY_REPORTER is a local id for this map used elsewhere. It's defined in event_objects.h

BattleFrontier_BattleTowerLobby_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerLobby_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerLobby_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerLobby_OnWarp
	.byte 0

BattleFrontier_BattleTowerLobby_OnResume:
	special TryHideBattleTowerReporter
	end

BattleFrontier_BattleTowerLobby_OnTransition:
	call BattleFrontier_BattleTowerLobby_EventScript_ShowOrHideReporter
	apprentice_shouldcheckgone
	goto_if_eq VAR_0x8004, FALSE, BattleFrontier_BattleTowerLobby_EventScript_ShowApprentice  @ VAR_0x8004 always TRUE here
	goto_if_set FLAG_DAILY_APPRENTICE_LEAVES, BattleFrontier_BattleTowerLobby_EventScript_HideApprentice
BattleFrontier_BattleTowerLobby_EventScript_ShowApprentice::
	clearflag FLAG_HIDE_APPRENTICE
	apprentice_setgfx
BattleFrontier_BattleTowerLobby_EventScript_EndShowOrHideApprentice::
	end

BattleFrontier_BattleTowerLobby_EventScript_HideApprentice::
	setflag FLAG_HIDE_APPRENTICE
	goto BattleFrontier_BattleTowerLobby_EventScript_EndShowOrHideApprentice

BattleFrontier_BattleTowerLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerLobby_EventScript_PlayerFaceNorth
	.2byte 0

BattleFrontier_BattleTowerLobby_EventScript_PlayerFaceNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleTowerLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleTowerLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleTowerLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleTowerLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleTowerLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleTowerLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleTowerLobby_EventScript_QuitWithoutSaving::
	lock
	faceplayer
	msgbox BattleFrontier_BattleTowerLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	tower_set TOWER_DATA_WIN_STREAK, 0
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_WonChallenge::
	lock
	faceplayer
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleTowerLobby_EventScript_DefeatedMaiden
	message BattleFrontier_BattleTowerLobby_Text_CongratsBeatenSeven
	waitmessage
	goto BattleFrontier_BattleTowerLobby_EventScript_GiveRibbons

BattleFrontier_BattleTowerLobby_EventScript_DefeatedMaiden::
	msgbox BattleFrontier_BattleTowerLobby_Text_CongratsDefeatedMaiden, MSGBOX_DEFAULT
BattleFrontier_BattleTowerLobby_EventScript_GiveRibbons::
	tower_giveribbons
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_BattleTowerLobby_EventScript_GiveBattlePoints
	message BattleFrontier_BattleTowerLobby_Text_HereAreSomeRibbons
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox BattleFrontier_BattleTowerLobby_Text_PutRibbonOnMons, MSGBOX_DEFAULT
BattleFrontier_BattleTowerLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleTowerLobby_Text_AwardYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	call BattleFrontier_BattleTowerLobby_EventScript_AskSaveBattle
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ne VAR_RESULT, 49, BattleFrontier_BattleTowerLobby_EventScript_LookForwardToChallenge
	msgbox BattleFrontier_BattleTowerLobby_Text_AboutToFace50thTrainer, MSGBOX_DEFAULT
BattleFrontier_BattleTowerLobby_EventScript_LookForwardToChallenge::
	msgbox BattleFrontier_BattleTowerLobby_Text_LookForwardToAnotherChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	callnative UpdateFollowingPokemon
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_LostChallenge::
	goto_if_ne VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_CancelWinStreak
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerLobby_EventScript_CancelWinStreak
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ne VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LostThanksForPlaying
BattleFrontier_BattleTowerLobby_EventScript_CancelWinStreak::
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, FALSE
BattleFrontier_BattleTowerLobby_EventScript_LostThanksForPlaying::
	lock
	faceplayer
	message BattleFrontier_BattleTowerLobby_Text_ThankYouForPlaying
	waitmessage
	call BattleFrontier_BattleTowerLobby_EventScript_AskSaveBattle
	msgbox BattleFrontier_BattleTowerLobby_Text_LookForwardToAnotherChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	callnative UpdateFollowingPokemon
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_AskSaveBattle::
	message BattleFrontier_BattleTowerLobby_Text_RecordWillBeSaved
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	tower_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleTowerLobby_EventScript_EndSaveBattle
	message BattleFrontier_BattleTowerLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerLobby_EventScript_EndSaveBattle
	case 0, BattleFrontier_EventScript_SaveBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_EndSaveBattle

BattleFrontier_EventScript_SaveBattle::
	frontier_savebattle
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_EventScript_BattleSaveFailed
	playse SE_SAVE
	msgbox BattleFrontier_BattleTowerLobby_Text_BattleRecordedOnPass, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_EndSaveBattle

BattleFrontier_EventScript_BattleSaveFailed::
	msgbox BattleFrontier_BattleTowerBattleRoom_Text_RecordCouldntBeSaved, MSGBOX_DEFAULT
BattleFrontier_BattleTowerLobby_EventScript_EndSaveBattle::
	return

BattleFrontier_EventScript_GetCantRecordBattle::
	frontier_get FRONTIER_DATA_RECORD_DISABLED
	return

BattleFrontier_BattleTowerLobby_EventScript_ResumeChallenge::
	lock
	faceplayer
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_SetBravoTrainerOn
	message BattleFrontier_BattleTowerLobby_Text_WeveBeenWaitingForYou
	waitmessage
	message BattleFrontier_BattleTowerLobby_Text_ProgressWillBeSaved
	waitmessage
	tower_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerLobby_EventScript_SetBravoTrainerOn::
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, TRUE
	return

BattleFrontier_BattleTowerLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
	special SavePlayerParty
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomSingleBattle, MSGBOX_DEFAULT
BattleFrontier_BattleTowerLobby_EventScript_AskEnterSinglesChallenge::
	message BattleFrontier_BattleTowerLobby_Text_TakeSinglesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterSinglesChallenge
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainSinglesChallenge
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge

BattleFrontier_BattleTowerLobby_EventScript_TryEnterSinglesChallenge::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleTowerLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeSinglesChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge

BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeSinglesChallenge::
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	tower_init
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, TRUE
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerLobby_EventScript_ExplainSinglesChallenge::
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterSinglesChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_DoublesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
	special SavePlayerParty
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomeDoubleBattle, MSGBOX_DEFAULT
BattleFrontier_BattleTowerLobby_EventScript_AskEnterDoublesChallenge::
	message BattleFrontier_BattleTowerLobby_Text_TakeDoublesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainDoublesChallenge
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge

BattleFrontier_BattleTowerLobby_EventScript_TryEnterDoublesChallenge::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectFourMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_DOUBLES_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeDoublesChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge

BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeDoublesChallenge::
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	tower_init
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterDoublesChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_MultisAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
	clearflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	special SavePlayerParty
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomeMultiBattle, MSGBOX_DEFAULT
BattleFrontier_BattleTowerLobby_EventScript_AskEnterMultisChallenge::
	message BattleFrontier_BattleTowerLobby_Text_TakeMultisChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainMultisChallenge
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge

BattleFrontier_BattleTowerLobby_EventScript_TryEnterMultisChallenge::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeMultisChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge

BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeMultisChallenge::
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	tower_init
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerLobby_EventScript_ExplainMultisChallenge::
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainMultisChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterMultisChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_LinkMultisAttendantNotAvailable::
	msgbox BattleFrontier_BattleTowerLobby_Text_NotAvailable, MSGBOX_DEFAULT
	closemessage
	end

BattleFrontier_BattleTowerLobby_Text_NotAvailable::
	.string "Lo siento, las SALAS DE BATALLA\n"
	.string "MULTIJUGADOR no están disponibles.$"

BattleFrontier_BattleTowerLobby_EventScript_LinkMultisAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
	special SavePlayerParty
	msgbox BattleFrontier_BattleTowerLobby_Text_WelcomeLinkMultiBattle, MSGBOX_DEFAULT
BattleFrontier_BattleTowerLobby_EventScript_AskEnterLinkMultisChallenge::
	message BattleFrontier_BattleTowerLobby_Text_TakeLinkMultisChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge
	case 1, BattleFrontier_BattleTowerLobby_EventScript_ExplainLinkMultisChallenge
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge

BattleFrontier_BattleTowerLobby_EventScript_TryEnterLinkMultisChallenge::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS
	message BattleFrontier_BattleTowerLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons2, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
	msgbox BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge
	case YES, BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeLinkMultisChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge

BattleFrontier_BattleTowerLobby_EventScript_SaveBeforeLinkMultisChallenge::
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	tower_init
	tower_set TOWER_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
@ The command tower_save ultimately calls TrySavingData(SAVE_LINK), which writes data in SaveBlock1 and SaveBlock2
@ to the flash, but not data in PokemonStorage. The SaveGame script that follows asks the player to do a full save,
@ which they can opt out of. As a result the player can save their party and quit without having saved the PC.
@ This allows players to clone pokemon and their held items by withdrawing them (or erase them by despositing).
#ifndef BUGFIX
	tower_save 0
#endif
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed
@ GAME_STAT_ENTERED_BATTLE_TOWER should not be incremented here, for two reasons:
@ 1. It is incremented again in BattleFrontier_BattleTowerLobby_EventScript_CableLinkSuccessful or BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful
@ 2. If the player tries to connect, but fails, the counter will still be incremented even if the player never enters the tower.
#ifndef BUGFIX
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
#endif
	specialvar VAR_RESULT, IsWirelessAdapterConnected
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleTowerLobby_EventScript_TryWirelessLink
	goto BattleFrontier_BattleTowerLobby_EventScript_TryCableLink
	end

BattleFrontier_BattleTowerLobby_EventScript_FeelingsMan::
	lock
	faceplayer
	message BattleFrontier_BattleTowerLobby_Text_DescribeFeelingsAboutBattleTower
	waitmessage
	multichoice 16, 4, MULTI_BATTLE_TOWER_FEELINGS, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerLobby_EventScript_FeelingsBattleNow
	case 1, BattleFrontier_BattleTowerLobby_EventScript_FeelingsIWon
	case 2, BattleFrontier_BattleTowerLobby_EventScript_FeelingsILost
	case 3, BattleFrontier_BattleTowerLobby_EventScript_FeelingsWontTell
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_FeelingsWontTell
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_FeelingsBattleNow::
	msgbox BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouBegin, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_BATTLE_START
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings
	end

BattleFrontier_BattleTowerLobby_EventScript_FeelingsIWon::
	msgbox BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveWon, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_BATTLE_WON
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings
	end

BattleFrontier_BattleTowerLobby_EventScript_FeelingsILost::
	msgbox BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveLost, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_BATTLE_LOST
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings
	end

BattleFrontier_BattleTowerLobby_EventScript_FeelingsWontTell::
	msgbox BattleFrontier_BattleTowerLobby_Text_DontThinkMuchAboutIt, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_CheckFeelings::
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_CanceledEasyChat
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattleTowerLobby_EventScript_SubmittedFeelings
	end

BattleFrontier_BattleTowerLobby_EventScript_CanceledEasyChat::
	msgbox BattleFrontier_BattleTowerLobby_Text_ChangedYourMind, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_SubmittedFeelings::
	msgbox BattleFrontier_BattleTowerLobby_Text_ThatsHowYouFeel, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleTowerLobby_Text_WinsInRowRecorded, MSGBOX_NPC
	end

BattleFrontier_BattleTowerLobby_EventScript_Boy::
	msgbox BattleFrontier_BattleTowerLobby_Text_CanLeaveUntilLossOrSevenWins, MSGBOX_NPC
	end

BattleFrontier_BattleTowerLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleTowerLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleTowerLobby_EventScript_ShowMultisResults::
	lockall
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_MULTIS
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleTowerLobby_EventScript_ShowLinkMultisResults::
	lockall
	frontier_results FRONTIER_FACILITY_TOWER, FRONTIER_MODE_LINK_MULTIS
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50::
	switch VAR_FRONTIER_BATTLE_MODE
	case FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Singles
	case FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Doubles
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Multis, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Singles::
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Singles, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLv50Doubles::
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Doubles, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpen::
	switch VAR_FRONTIER_BATTLE_MODE
	case FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenSingles
	case FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenDoubles
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenMultis, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenSingles::
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenSingles, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_NotEnoughValidMonsLvOpenDoubles::
	msgbox BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenDoubles, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS  @ No status provided, so it relies on VAR_0x8006 being 0 already
	goto BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_LoadPartyCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge::
	special CloseLink
	msgbox BattleFrontier_BattleTowerLobby_Text_LookForwardToAnotherChallenge, MSGBOX_DEFAULT
BattleFrontier_BattleTowerLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_EnterElevator::
	special SavePlayerParty
	setvar VAR_0x8004, FRONTIER_UTIL_FUNC_SET_PARTY_ORDER
	call BattleFrontier_BattleTowerLobby_EventScript_GetPartySize
	special CallFrontierUtilFunc
	setvar VAR_RESULT, 0
BattleFrontier_BattleTowerLobby_EventScript_WaitForLinkOpponentLoad::
	tower_loadlinkopponents
	delay 1
	goto_if_ne VAR_RESULT, 6, BattleFrontier_BattleTowerLobby_EventScript_WaitForLinkOpponentLoad
	call BattleFrontier_BattleTowerLobby_EventScript_ShowYouToBattleRoom
	clearflag FLAG_CANCEL_BATTLE_ROOM_CHALLENGE
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleTowerLobby_EventScript_ShowYouToBattleRoom::
	call BattleFrontier_BattleTowerLobby_EventScript_BufferModeText
	goto_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_ShowYouToLinkMultiBattleRoom
	msgbox BattleFrontier_BattleTowerLobby_Text_ShowYouToBattleRoom, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_WalkToElevator

BattleFrontier_BattleTowerLobby_EventScript_ShowYouToLinkMultiBattleRoom::
	messageautoscroll BattleFrontier_BattleTowerLobby_Text_ShowYouToBattleRoom
	waitmessage
	delay 48
BattleFrontier_BattleTowerLobby_EventScript_WalkToElevator::
	closemessage
	call BattleFrontier_BattleTowerLobby_EventScript_SetAttendantTalkedTo
	call BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoord
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerLobby_Movement_WalkToElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerLobby_Movement_WalkToElevator
	waitmovement 0
	opendoor VAR_0x8004, 1
	waitdooranim
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerLobby_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerLobby_Movement_PlayerEnterElevator
	waitmovement 0
	closedoor VAR_0x8004, 1
	waitdooranim
	return

BattleFrontier_BattleTowerLobby_Movement_WalkToElevator:
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleTowerLobby_Movement_AttendantEnterElevator:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerLobby_Movement_PlayerEnterElevator:
	walk_up
	walk_up
	set_invisible
	step_end

@ Unused
BattleFrontier_BattleTowerLobby_Movement_UnusedEnterElevator:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	set_invisible
	step_end

BattleFrontier_BattleTowerLobby_EventScript_BufferModeText::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_BufferTextSingle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_BufferTextDouble
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_BufferTextMulti
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_BufferTextLinkMulti
	return

BattleFrontier_BattleTowerLobby_EventScript_BufferTextSingle::
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
	return

BattleFrontier_BattleTowerLobby_EventScript_BufferTextDouble::
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
	return

BattleFrontier_BattleTowerLobby_EventScript_BufferTextMulti::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
	return

BattleFrontier_BattleTowerLobby_EventScript_BufferTextLinkMulti::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
	return

BattleFrontier_BattleTowerLobby_EventScript_SetAttendantTalkedTo::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_TalkedToSinglesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_TalkedToDoublesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_TalkedToMultisAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_TalkedToLinkMultisAttendant
	return

BattleFrontier_BattleTowerLobby_EventScript_TalkedToSinglesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_SINGLES
	return

BattleFrontier_BattleTowerLobby_EventScript_TalkedToDoublesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_DOUBLES
	return

BattleFrontier_BattleTowerLobby_EventScript_TalkedToMultisAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_MULTIS
	return

BattleFrontier_BattleTowerLobby_EventScript_TalkedToLinkMultisAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_LINK_MULTIS
	return

BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoord::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordSingles
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordDoubles
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordMultis
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordLinkMultis
	return

BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordSingles::
	setvar VAR_0x8004, 6
	return

BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordDoubles::
	setvar VAR_0x8004, 10
	return

BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordMultis::
	setvar VAR_0x8004, 14
	return

BattleFrontier_BattleTowerLobby_EventScript_GetDoorXCoordLinkMultis::
	setvar VAR_0x8004, 18
	return

BattleFrontier_BattleTowerLobby_EventScript_GetPartySize::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleTowerLobby_EventScript_GetSinglesPartySize
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleTowerLobby_EventScript_GetDoublesPartySize
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetMultisPartySize
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_LINK_MULTIS, BattleFrontier_BattleTowerLobby_EventScript_GetLinkMultisPartySize
	return

BattleFrontier_BattleTowerLobby_EventScript_GetSinglesPartySize::
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	return

BattleFrontier_BattleTowerLobby_EventScript_GetDoublesPartySize::
	setvar VAR_0x8005, FRONTIER_DOUBLES_PARTY_SIZE
	return

BattleFrontier_BattleTowerLobby_EventScript_GetMultisPartySize::
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
	return

BattleFrontier_BattleTowerLobby_EventScript_GetLinkMultisPartySize::
	setvar VAR_0x8005, FRONTIER_MULTI_PARTY_SIZE
	return

BattleFrontier_EventScript_GetLvlMode::
	frontier_get FRONTIER_DATA_LVL_MODE
	return

BattleFrontier_BattleTowerLobby_EventScript_TryCableLink::
	setvar VAR_0x8004, USING_BATTLE_TOWER
	message gText_PleaseWaitForLink
	waitmessage
	setvar VAR_0x8005, 0
	special TryBattleLinkup
	waitstate
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, BattleFrontier_BattleTowerLobby_EventScript_CableLinkSuccessful
	goto_if_eq VAR_RESULT, LINKUP_SOMEONE_NOT_READY, CableClub_EventScript_AbortLinkSomeoneNotReady
	goto_if_eq VAR_RESULT, LINKUP_DIFF_SELECTIONS, BattleFrontier_BattleTowerLobby_EventScript_AbortLinkDifferentSelections
	goto_if_eq VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS, BattleFrontier_BattleTowerLobby_EventScript_AbortLinkIncorrectNumberOfPlayers
	goto_if_eq VAR_RESULT, LINKUP_FAILED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	goto_if_eq VAR_RESULT, LINKUP_CONNECTION_ERROR, CableClub_EventScript_AbortLinkConnectionError
	goto_if_eq VAR_RESULT, LINKUP_FAILED_BATTLE_TOWER, BattleFrontier_BattleTowerLobby_EventScript_AbortLink
	end

BattleFrontier_BattleTowerLobby_EventScript_AbortLinkDifferentSelections::
	special CloseLink
	goto_if_eq VAR_0x8005, 3, BattleFrontier_BattleTowerLobby_EventScript_FriendDifferentSelection
	msgbox Text_PlayersMadeDifferentSelections, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_FriendDifferentSelection::
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlMode, MSGBOX_DEFAULT
	msgbox BattleFrontier_BattleTowerLobby_Text_ChooseDifferentMonsMatchLvlMode, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_AbortLinkIncorrectNumberOfPlayers::
	msgbox BattleFrontier_BattleTowerLobby_Text_LinkMultiOnlyForTwoPlayers, MSGBOX_DEFAULT
	special CloseLink
	msgbox CableClub_Text_IncorrectNumberOfParticipants, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_AbortLink::
	special CloseLink
	call_if_eq VAR_0x8005, 0, BattleFrontier_BattleTowerLobby_EventScript_FriendChoseDifferentLvlMode
	call_if_eq VAR_0x8005, 1, BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMon
	call_if_eq VAR_0x8005, 2, BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMons
	msgbox BattleFrontier_BattleTowerLobby_Text_ChooseDifferentMonsMatchLvlMode, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_FriendChoseDifferentLvlMode::
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlMode, MSGBOX_DEFAULT
	return

BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMon::
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMon, MSGBOX_DEFAULT
	return

BattleFrontier_BattleTowerLobby_EventScript_FriendAlsoSelectedMons::
	msgbox BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMons, MSGBOX_DEFAULT
	return

BattleFrontier_BattleTowerLobby_EventScript_CableLinkSuccessful::
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
	message BattleFrontier_BattleTowerLobby_Text_SaveGameBeforeShowingIn
	waitmessage
	tower_save CHALLENGE_STATUS_SAVING
	special SaveForBattleTowerLink
	waitstate
	playse SE_SAVE
	waitse
	special TrySetBattleTowerLinkType
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerLobby_EventScript_ExplainLinkMultisChallenge::
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainLinkMultisChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_AskEnterLinkMultisChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_TryWirelessLink::
	setvar VAR_0x8004, LINK_GROUP_BATTLE_TOWER
	goto BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader
	end

BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader::
	message CableClub_Text_ChooseGroupLeaderOfTwo
	waitmessage
	multichoice 16, 6, MULTI_LINK_LEADER, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerLobby_EventScript_TryJoinGroup
	case 1, BattleFrontier_BattleTowerLobby_EventScript_TryBecomeLeader
	case 2, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_CancelChallenge
	end

BattleFrontier_BattleTowerLobby_EventScript_TryBecomeLeader::
	call CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful
	goto_if_eq VAR_RESULT, LINKUP_FAILED, BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, BattleFrontier_BattleTowerLobby_EventScript_TryBecomeLeader
	goto_if_eq VAR_RESULT, LINKUP_FAILED_BATTLE_TOWER, BattleFrontier_BattleTowerLobby_EventScript_AbortLink
	release
	return

BattleFrontier_BattleTowerLobby_EventScript_TryJoinGroup::
	call CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful
	goto_if_eq VAR_RESULT, LINKUP_FAILED, BattleFrontier_BattleTowerLobby_EventScript_ChooseLeader
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, BattleFrontier_BattleTowerLobby_EventScript_TryJoinGroup
	goto_if_eq VAR_RESULT, LINKUP_FAILED_BATTLE_TOWER, BattleFrontier_BattleTowerLobby_EventScript_AbortLink
	release
	return

BattleFrontier_BattleTowerLobby_EventScript_WirelessLinkSuccessful::
	incrementgamestat GAME_STAT_ENTERED_BATTLE_TOWER
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, FALSE
	message BattleFrontier_BattleTowerLobby_Text_SaveGameBeforeShowingIn
	waitmessage
	tower_save CHALLENGE_STATUS_SAVING
	special SaveForBattleTowerLink
	waitstate
	playse SE_SAVE
	waitse
	goto BattleFrontier_BattleTowerLobby_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleTowerLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleTowerLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 2, MULTI_BATTLE_TOWER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerLobby_EventScript_RulesTower
	case 1, BattleFrontier_BattleTowerLobby_EventScript_RulesMons
	case 2, BattleFrontier_BattleTowerLobby_EventScript_RulesSalon
	case 3, BattleFrontier_BattleTowerLobby_EventScript_RulesMultiLink
	case 4, BattleFrontier_BattleTowerLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_ExitRules
	end

BattleFrontier_BattleTowerLobby_EventScript_RulesTower::
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainTowerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleTowerLobby_EventScript_RulesMons::
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleTowerLobby_EventScript_RulesSalon::
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainSalonRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleTowerLobby_EventScript_RulesMultiLink::
	msgbox BattleFrontier_BattleTowerLobby_Text_ExplainMultiLinkRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleTowerLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleTowerLobby_EventScript_ExitRules::
	releaseall
	end

@ Unused
BattleFrontier_BattleTowerLobby_Text_DirectYouToBattleRoom:
	.string "Te guiaré a tu SALA DE BATALLA ahora.$"

BattleFrontier_BattleTowerLobby_Text_DidntSaveBeforeQuitting:
	.string "¡Disculpa!\p"
	.string "No guardaste antes de salir de tu\n"
	.string "desafío la última vez.\p"
	.string "Por eso, tu progreso hasta ahora\n"
	.string "ha sido descalificado. ¡Lo siento!$"

BattleFrontier_BattleTowerLobby_Text_CongratsBeatenSeven:
	.string "¡Felicidades!\n"
	.string "¡Venciste a los siete ENTRENADORES!\p"
	.string "$"

@ Unused
BattleFrontier_BattleTowerLobby_Text_EarnedFabulousPrize:
	.string "¡Por vencer a siete ENTRENADORES\n"
	.string "seguidos, ganaste este gran premio!\p"
	.string "$"

BattleFrontier_BattleTowerLobby_Text_ReceivedPrize:
	.string "{PLAYER} recibió el premio\n"
	.string "{STR_VAR_1}.$"

@ Unused
BattleFrontier_BattleTowerLobby_Text_BagFullMakeRoom:
	.string "Oh, parece que tu MOCHILA está llena.\p"
	.string "Haz espacio en tu MOCHILA y luego\n"
	.string "vuelve a verme.$"

BattleFrontier_BattleTowerLobby_Text_ThankYouForPlaying:
	.string "¡Gracias por jugar!\p"
	.string "$"

BattleFrontier_BattleTowerLobby_Text_RecordWillBeSaved:
	.string "Tu récord se guardará.\n"
	.string "Espera, por favor.$"

BattleFrontier_BattleTowerLobby_Text_WeveBeenWaitingForYou:
	.string "¡Te estábamos esperando!\p"
	.string "$"

BattleFrontier_BattleTowerLobby_Text_ProgressWillBeSaved:
	.string "Antes de entrar a una BATTLE ROOM,\n"
	.string "se guardará tu progreso. Espera.$"

BattleFrontier_BattleTowerLobby_Text_AboutToFace50thTrainer:
	.string "Finalmente vas a enfrentar al\n"
	.string "ENTRENADOR 50.\p"
	.string "De ahora en adelante, cada vez que\n"
	.string "venzas a 7 ENTRENADORES, tu POKéMON\l"
	.string "recibirá una CINTA conmemorativa.\p"
	.string "¡Buena suerte!$"

BattleFrontier_BattleTowerLobby_Text_HereAreSomeRibbons:
	.string "Aquí tienes CINTAS por vencer a\n"
	.string "siete ENTRENADORES fuertes seguidos.\p"
	.string "¡{PLAYER} recibió algunas CINTAS!$"

BattleFrontier_BattleTowerLobby_Text_PutRibbonOnMons:
	.string "{PLAYER} puso las CINTAS en\n"
	.string "los POKéMON desafiantes.$"

BattleFrontier_BattleTowerLobby_Text_DescribeFeelingsAboutBattleTower:
	.string "Disculpa, ¿tienes un momento?\p"
	.string "¿Puedes describir qué sientes al\n"
	.string "empezar un combate en BATTLE TOWER\l"
	.string "o cuando has ganado o\l"
	.string "perdido un combate?$"

BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouBegin:
	.string "Bien, ¿qué sientes cuando\n"
	.string "estás por empezar un combate?$"

BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveWon:
	.string "¿Qué sientes cuando ganas\n"
	.string "un combate?$"

BattleFrontier_BattleTowerLobby_Text_FeelWhatWhenYouveLost:
	.string "¿Me cuentas cómo te sientes cuando\n"
	.string "¿pierdes un combate?$"

BattleFrontier_BattleTowerLobby_Text_DontThinkMuchAboutIt:
	.string "Oh, ¿así que no piensas en eso?\n"
	.string "Eres alguien muy tranquilo.$"

BattleFrontier_BattleTowerLobby_Text_ChangedYourMind:
	.string "¿Eh? ¿Cambiaste de opinión?\n"
	.string "Parece que eres indeciso.$"

BattleFrontier_BattleTowerLobby_Text_ThatsHowYouFeel:
	.string "Vale, ¿así que así te sientes?\n"
	.string "Eso es bastante original.\p"
	.string "¡Gracias!$"

BattleFrontier_BattleTowerLobby_Text_WinsInRowRecorded:
	.string "Tus victorias consecutivas\n"
	.string "quedan registradas.\p"
	.string "¡No debo perder de una forma\n"
	.string "tan vergonzosa!$"

BattleFrontier_BattleTowerLobby_Text_CanLeaveUntilLossOrSevenWins:
	.string "Al entrar en la BATTLE TOWER,\n"
	.string "no podrás salir hasta que pierdas\l"
	.string "o venzas a siete ENTRENADORES seguidos.\p"
	.string "Asegúrate de estar listo para\n"
	.string "el desafío.$"

@ Unused
BattleFrontier_BattleTowerLobby_Text_DoubleBattleRoomConstruction:
	.string "¡Bienvenido al ÁREA DE BATALLAS\n"
	.string "DOBLES de la BATTLE TOWER!\p"
	.string "Lamentablemente, las BATTLE ROOMS\n"
	.string "están aún en construcción.\p"
	.string "Vuelve cuando el trabajo haya\n"
	.string "terminado.$"

@ Unused
BattleFrontier_BattleTowerLobby_Text_MultiBattleRoomConstruction:
	.string "¡Bienvenido al RINCÓN DE BATALLAS\n"
	.string "MÚLTIPLES de la TORRE BATALLA!\p"
	.string "Lamentablemente, las SALAS DE BATALLA\n"
	.string "están aún en construcción.\p"
	.string "Vuelve cuando el trabajo\n"
	.string "esté terminado.$"

BattleFrontier_BattleTowerLobby_Text_LookForwardToAnotherChallenge:
	.string "¡Esperamos verte en\n"
	.string "otro desafío!$"

BattleFrontier_BattleTowerLobby_Text_WhichLevelMode:
	.string "La SALA DE BATALLA tiene dos niveles\n"
	.string "de desafío: NORMAL y DIFÍCIL.\l"
	.string "¿Cuál eliges?$"

@ Unused
BattleFrontier_BattleTowerLobby_Text_PleaseSelectMons:
	.string "Selecciona los POKéMON que deseas\n"
	.string "que participen.$"

BattleFrontier_BattleTowerLobby_Text_OkayToSaveBeforeEntering:
	.string "Antes de entrar a la SALA DE BATALLA,\n"
	.string "debes guardar tu partida. ¿Está bien?$"

BattleFrontier_BattleTowerLobby_Text_ShowYouToBattleRoom:
	.string "Ahora te llevaré a la\n"
	.string "SALA DE BATALLA {STR_VAR_1}.$"

BattleFrontier_BattleTowerLobby_Text_RecordLastMatch:
	.string "¿Registro tu último combate de la\n"
	.string "TORRE BATALLA en tu FRONTIER PASS?$"

@ Unused
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50:
	.string "¡Disculpa!\p"
	.string "No tienes {STR_VAR_2} POKéMON aptos.\p"
	.string "Deben ser {STR_VAR_2} POKéMON distintos.\p"
	.string "También deben llevar objetos\n"
	.string "diferentes.\p"
	.string "Los HUEVOS{STR_VAR_1} no cuentan.\p"
	.string "Vuelve cuando estés listo.$"

@ Unused
BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpen:
	.string "¡Disculpa!\p"
	.string "No tienes {STR_VAR_2} POKéMON aptos.\p"
	.string "Debes tener {STR_VAR_2} POKéMON distintos\n"
	.string "para entrar.\p"
	.string "Deben llevar objetos de tipos\n"
	.string "diferentes.\p"
	.string "Los HUEVOS{STR_VAR_1} no valen.\p"
	.string "Vuelve cuando estés listo.$"

BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Singles:
	.string "¡Disculpa!\p"
	.string "No tienes tres POKéMON aptos.\p"
	.string "Debes tener tres POKéMON distintos.\n"
	.string "Deben llevar objetos de tipos\n"
	.string "diferentes.\p"
	.string "Los HUEVOS{STR_VAR_1} no valen.\p"
	.string "Vuelve cuando estés listo.$"

BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenSingles:
	.string "¡Disculpa!\p"
	.string "No tienes tres POKéMON aptos.\p"
	.string "Debes tener tres POKéMON distintos\n"
	.string "para entrar.\p"
	.string "Deben llevar objetos de tipos\n"
	.string "diferentes.\p"
	.string "Los HUEVOS{STR_VAR_1} no valen.\p"
	.string "Vuelve cuando estés listo.$"

BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Doubles:
	.string "¡Disculpa!\p"
	.string "No tienes cuatro POKéMON aptos.\p"
	.string "Debes tener cuatro POKéMON distintos.\n"
	.string "Deben llevar objetos de tipos\n"
	.string "diferentes.\p"
	.string "Los HUEVOS{STR_VAR_1} no valen.\p"
	.string "Vuelve cuando estés listo.$"

BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenDoubles:
	.string "¡Disculpa!\p"
	.string "No tienes cuatro POKéMON aptos.\p"
	.string "Debes tener cuatro POKéMON distintos\n"
	.string "para entrar.\p"
	.string "Deben llevar objetos de tipos\n"
	.string "diferentes.\p"
	.string "Los HUEVOS{STR_VAR_1} no valen.\p"
	.string "Vuelve cuando estés listo.$"

BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLv50Multis:
	.string "¡Disculpa!\p"
	.string "No tienes dos POKéMON aptos.\p"
	.string "Debes tener dos POKéMON distintos.\n"
	.string "Deben llevar objetos de tipos\n"
	.string "diferentes.\p"
	.string "Los HUEVOS{STR_VAR_1} no valen.\p"
	.string "Vuelve cuando estés listo.$"

BattleFrontier_BattleTowerLobby_Text_NotEnoughValidMonsLvOpenMultis:
	.string "¡Disculpa!\p"
	.string "No tienes dos POKéMON aptos.\p"
	.string "Debes tener dos POKéMON distintos\n"
	.string "para entrar.\p"
	.string "Deben llevar objetos de tipos\n"
	.string "diferentes.\p"
	.string "Los HUEVOS{STR_VAR_1} no valen.\p"
	.string "Vuelve cuando estés listo.$"

BattleFrontier_BattleTowerLobby_Text_WelcomSingleBattle:
	.string "¡Donde el talento de los\n"
	.string "ENTRENADORES se pone a prueba!\p"
	.string "¡Bienvenido a la BATTLE TOWER!\p"
	.string "Soy tu guía para las SALAS DE\n"
	.string "BATALLA INDIVIDUAL.$"

BattleFrontier_BattleTowerLobby_Text_TakeSinglesChallenge:
	.string "¿Quieres aceptar el desafío de la\n"
	.string "SINGLE BATTLE ROOM?$"

BattleFrontier_BattleTowerLobby_Text_ExplainSinglesChallenge:
	.string "Las SINGLE BATTLE ROOMS de la\n"
	.string "BATTLE TOWER son para hacer\l"
	.string "BATALLAS individuales con 3 POKéMON.\p"
	.string "Hay muchas SINGLE BATTLE ROOMS\n"
	.string "en la BATTLE TOWER para equipos.\p"
	.string "En cada SINGLE BATTLE ROOM,\n"
	.string "siete ENTRENADORES esperan tu reto.\p"
	.string "Si logras vencer a los siete,\n"
	.string "ganarás Puntos de Batalla.\p"
	.string "Si quieres interrumpir el reto,\n"
	.string "por favor, guarda la partida.\p"
	.string "Si no guardas antes de salir,\n"
	.string "quedarás descalificado.$"

BattleFrontier_BattleTowerLobby_Text_SelectThreeMons:
	.string "Ahora elige los tres POKéMON\n"
	.string "que entrarán al combate.$"

BattleFrontier_BattleTowerLobby_Text_WelcomeDoubleBattle:
	.string "¡Donde el talento de los TRAINERS\n"
	.string "se pone a prueba!\p"
	.string "¡Bienvenido a la BATTLE TOWER!\p"
	.string "Soy tu guía para las DOUBLE\n"
	.string "BATTLE ROOMS.$"

BattleFrontier_BattleTowerLobby_Text_TakeDoublesChallenge:
	.string "¿Quieres aceptar el desafío de la\n"
	.string "DOUBLE BATTLE ROOM?$"

BattleFrontier_BattleTowerLobby_Text_ExplainDoublesChallenge:
	.string "Las DOUBLE BATTLE ROOMS de la\n"
	.string "BATTLE TOWER son para hacer\l"
	.string "BATALLAS dobles con cuatro POKéMON.\p"
	.string "Hay muchas DOUBLE BATTLE ROOMS\n"
	.string "en la BATTLE TOWER para equipos.\p"
	.string "En cada DOUBLE BATTLE ROOM,\n"
	.string "siete ENTRENADORES esperan tu reto.\p"
	.string "Si logras vencer a los siete,\n"
	.string "ganarás Puntos de Batalla.\p"
	.string "Si quieres interrumpir el reto,\n"
	.string "por favor, guarda la partida.\p"
	.string "Si no guardas antes de salir,\n"
	.string "quedarás descalificado.$"

BattleFrontier_BattleTowerLobby_Text_PleaseSelectFourMons:
	.string "Ahora elige los cuatro POKéMON\n"
	.string "que entrarán en combate.$"

BattleFrontier_BattleTowerLobby_Text_WelcomeMultiBattle:
	.string "¡Donde el talento de los\n"
	.string "ENTRENADORES se pone a prueba!\p"
	.string "¡Bienvenido a la BATTLE TOWER!\p"
	.string "Soy tu guía para las SALAS de\n"
	.string "COMBATES MÚLTIPLES.$"

BattleFrontier_BattleTowerLobby_Text_TakeMultisChallenge:
	.string "¿Quieres aceptar el reto de la SALA\n"
	.string "de COMBATES MÚLTIPLES?$"

BattleFrontier_BattleTowerLobby_Text_ExplainMultisChallenge:
	.string "Las SALAS de COMBATES MÚLTIPLES de\n"
	.string "la BATTLE TOWER son para hacer\l"
	.string "COMBATES MÚLTIPLES.\p"
	.string "Para estos, debes aliarte con un\n"
	.string "ENTRENADOR de la TORRE y entrar\l"
	.string "con dos POKéMON cada uno.\p"
	.string "En la TORRE hay un lugar llamado\n"
	.string "BATTLE SALON donde verás a\l"
	.string "otros ENTRENADORES.\p"
	.string "Allí debes buscar un ENTRENADOR\n"
	.string "que sea tu pareja de combate.\p"
	.string "Cuando tengas pareja, te llevarán\n"
	.string "a una SALA de COMBATES MÚLTIPLES.\p"
	.string "En la SALA, siete parejas de\n"
	.string "combate esperan tu desafío.\p"
	.string "Si logras vencer a los siete\n"
	.string "equipos, ganarás Puntos de Batalla.\p"
	.string "Si quieres interrumpir el reto,\n"
	.string "por favor, guarda la partida.\p"
	.string "Si no guardas antes de salir,\n"
	.string "quedarás descalificado.$"

BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons:
	.string "Ahora elige los dos POKéMON\n"
	.string "que entrarán en combate.$"

BattleFrontier_BattleTowerLobby_Text_WelcomeLinkMultiBattle:
	.string "¡Donde el talento de los\n"
	.string "ENTRENADORES se pone a prueba!\p"
	.string "¡Bienvenido a la BATTLE TOWER!\p"
	.string "Soy tu guía para las SALAS de\n"
	.string "COMBATES MÚLTIPLES por LINK.$"

BattleFrontier_BattleTowerLobby_Text_TakeLinkMultisChallenge:
	.string "¿Quieres aceptar el reto de la SALA\n"
	.string "de COMBATES MÚLTIPLES por LINK?$"

BattleFrontier_BattleTowerLobby_Text_ExplainLinkMultisChallenge:
	.string "Las SALAS de COMBATES MÚLTIPLES de\n"
	.string "la BATTLE TOWER son para luchar\l"
	.string "con un amigo.\p"
	.string "Debes conectarte con tu amigo usando\n"
	.string "Adaptadores Inalámbricos o un cable\l"
	.string "Game Link de Game Boy Advance.\p"
	.string "Alíate con tu amigo y entren con\n"
	.string "dos tipos de POKéMON diferentes.\p"
	.string "Hay muchas SALAS de COMBATES\n"
	.string "MÚLTIPLES en la BATTLE TOWER.\p"
	.string "En una SALA, siete parejas esperan\n"
	.string "que tú y tu amigo acepten\l"
	.string "el desafío en equipo.\p"
	.string "Si logran vencer a los siete\n"
	.string "equipos, ganarán Puntos de Batalla.\p"
	.string "Ten cuidado, pues a diferencia de\n"
	.string "otras SALAS, no puedes parar.\p"
	.string "Una vez que empieces, debes luchar\n"
	.string "siete COMBATES MÚLTIPLES seguidos.$"

BattleFrontier_BattleTowerLobby_Text_PleaseSelectTwoMons2:
	.string "Ahora elige los dos POKéMON\n"
	.string "que quieres ingresar.$"

@ Unused
BattleFrontier_BattleTowerLobby_Text_ChoseSameMonAsFriend:
	.string "Elegiste los mismos POKéMON\n"
	.string "que tu amigo.\p"
	.string "Elige dos POKéMON distintos a los\n"
	.string "de tu amigo, ajusta el nivel\l"
	.string "y regístrate de nuevo.$"

BattleFrontier_BattleTowerLobby_Text_LinkMultiOnlyForTwoPlayers:
	.string "El reto de BATALLA MULTI LINK\n"
	.string "es solo para dos jugadores.$"

BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMon:
	.string "Tu amigo también eligió al\n"
	.string "POKéMON {STR_VAR_1}.$"

BattleFrontier_BattleTowerLobby_Text_FriendAlsoSelectedMons:
	.string "Tu amigo también eligió a los\n"
	.string "POKéMON {STR_VAR_1} y {STR_VAR_2}.$"

BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlMode:
	.string "Tu amigo eligió un nivel de\n"
	.string "batalla diferente.$"

@ Unused
BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlModeSameMon:
	.string "Tu amigo eligió un nivel de\n"
	.string "batalla diferente.\p"
	.string "Tu amigo también eligió al\n"
	.string "POKéMON {STR_VAR_1}.$"

@ Unused
BattleFrontier_BattleTowerLobby_Text_FriendChoseDifferentLvlModeSameMons:
	.string "Tu amigo eligió un nivel de\n"
	.string "batalla diferente.\p"
	.string "Tu amigo también eligió a los\n"
	.string "POKéMON {STR_VAR_1} y {STR_VAR_2}.$"

BattleFrontier_BattleTowerLobby_Text_ChooseDifferentMonsMatchLvlMode:
	.string "Elige dos POKéMON distintos a los\n"
	.string "de tu amigo, el mismo nivel\l"
	.string "y regístrate de nuevo.$"

BattleFrontier_BattleTowerLobby_Text_SaveGameBeforeShowingIn:
	.string "Guardaré la partida antes de\n"
	.string "dejarte entrar. Espera, por favor.$"

BattleFrontier_BattleTowerLobby_Text_CongratsDefeatedMaiden:
	.string "¡Felicidades!\n"
	.string "¡Venciste a la DAMA DEL SALÓN\l"
	.string "y a siete ENTRENADORES!$"

BattleFrontier_BattleTowerLobby_Text_AwardYouTheseBattlePoints:
	.string "Por tu talento infinito,\n"
	.string "te damos estos Puntos de Batalla.$"

BattleFrontier_Text_ObtainedXBattlePoints:
	.string "{PLAYER} obtuvo {STR_VAR_1} Puntos de Batalla.$"

BattleFrontier_BattleTowerLobby_Text_RulesAreListed:
	.string "Reglas de la BATTLE TOWER listadas.$"

BattleFrontier_BattleTowerLobby_Text_ReadWhichHeading:
	.string "¿Qué sección quieres leer?$"

BattleFrontier_BattleTowerLobby_Text_ExplainTowerRules:
	.string "La TORRE DE BATALLA es un lugar con\n"
	.string "cuatro tipos de combates:\l"
	.string "INDIVIDUAL, DOBLE, MULTI\l"
	.string "y MULTI VÍNCULO.\p"
	.string "Para cada tipo, hay\n"
	.string "SALAS DE BATALLA separadas.\p"
	.string "Habla con el guía del tipo de\n"
	.string "combate que quieras jugar.$"

BattleFrontier_BattleTowerLobby_Text_ExplainMonRules:
	.string "Según la SALA DE BATALLA,\n"
	.string "deberás llevar un número\l"
	.string "cierto de POKéMON.\p"
	.string "El modo INDIVIDUAL requiere\n"
	.string "tres POKéMON.\p"
	.string "El modo DOBLE requiere cuatro,\n"
	.string "y los MULTI requieren dos.$"

BattleFrontier_BattleTowerLobby_Text_ExplainSalonRules:
	.string "En el SALÓN DE BATALLA debes\n"
	.string "buscar un compañero para el\l"
	.string "reto de la SALA MULTI.\p"
	.string "Elige al mejor compañero\n"
	.string "viendo los POKéMON y ataques\l"
	.string "de otros ENTRENADORES.\p"
	.string "Puedes cambiar de compañero\n"
	.string "tras ganar siete combates.$"

BattleFrontier_BattleTowerLobby_Text_ExplainMultiLinkRules:
	.string "El modo MULTIBATALLA es para que dos\n"
	.string "amigos se enfrenten juntos.\p"
	.string "Tú y tu amigo deben conectarse con\n"
	.string "Adaptadores Inalámbricos o un cable\l"
	.string "cable Game Link de GBA.\p"
	.string "Debes elegir dos POKéMON en el\n"
	.string "mostrador de registro.\p"
	.string "Estos POKéMON deben ser distintos\n"
	.string "a los de tu amigo.\p"
	.string "No puedes interrumpir el reto a la\n"
	.string "mitad, a diferencia de otros modos.$"
