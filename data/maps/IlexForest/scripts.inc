.set LOCALID_ILEX_FOREST_FARFETCHD_1, 3
.set LOCALID_ILEX_FOREST_FARFETCHD_2, 31
.set LOCALID_ILEX_FOREST_FARFETCHD_3, 33
.set LOCALID_ILEX_FOREST_FARFETCHD_4, 32
.set LOCALID_ILEX_FOREST_CELEBI, 7
.set LOCALID_ILEX_FOREST_KURT, 34
.set LOCALID_ILEX_FOREST_KIMONO, 36
.set LOCALID_ILEX_FOREST_BUTTERFREE, 37
.set LOCALID_ILEX_FOREST_SECOND_CELEBI, 38

IlexForest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IlexForest_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

IlexForest_OnTransition: 
	call_if_eq VAR_ILEX_FOREST_FARFETCHD, 1, IlexForest_EventScript_ReenterWhenFarfetchdLeaving
	call_if_eq VAR_ILEX_FOREST_FARFETCHD, 2, IlexForest_EventScript_ReenterDuringCutScene
	callnative SetTimeBasedEncounters
	end	

IlexForest_EventScript_ReenterWhenFarfetchdLeaving::
	setobjectxyperm LOCALID_ILEX_FOREST_FARFETCHD_1, 33, 51
	return

IlexForest_EventScript_ReenterDuringCutScene::
	clearflag FLAG_HIDE_ILEX_FOREST_MASTER
	clearflag FLAG_HIDE_ILEX_FOREST_APPRENTICE
	setobjectxyperm LOCALID_ILEX_FOREST_FARFETCHD_1, 28, 42
	return

IlexForest_EventScript_Apprentice::
	lock
	faceplayer
	goto_if_eq VAR_ILEX_FOREST_FARFETCHD, 2, IlexForest_EventScript_Apprentice2
	goto_if_eq VAR_ILEX_FOREST_FARFETCHD, 3, IlexForest_EventScript_Apprentice2
	msgbox IlexForest_Text_ApprenticeIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_EventScript_Apprentice2::
	msgbox IlexForest_Text_ApprenticeAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_EventScript_Boss::
	lock
	faceplayer
	msgbox IlexForest_Text_CharcoalMasterTalkAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_EventScript_Farfetchd_1A::
	lock
	faceplayer
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq VAR_ILEX_FOREST_FARFETCHD, 3, IlexForest_EventScript_Farfetchd_Done
	goto_if_eq VAR_ILEX_FOREST_FARFETCHD, 2, IlexForest_EventScript_Farfetchd_Done
	goto_if_eq VAR_ILEX_FOREST_FARFETCHD, 1, IlexForest_EventScript_Farfetchd_Leave
	goto_if_eq VAR_FACING, DIR_SOUTH, IlexForest_EventScript_Farfetchd_1B
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_1, IlexForest_Movement_Farfetchd_1A
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_1
	@add clockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_2
	addobject LOCALID_ILEX_FOREST_FARFETCHD_2
	release
	end
IlexForest_EventScript_Farfetchd_1B::
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_1, IlexForest_Movement_Farfetchd_1B
	waitmovement 0
	setvar VAR_ILEX_FOREST_FARFETCHD, 1
	setobjectxyperm LOCALID_ILEX_FOREST_FARFETCHD_1, 33, 51
	release
	end

IlexForest_EventScript_Farfetchd_2A::
	lock
	faceplayer
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq VAR_FACING, DIR_SOUTH, IlexForest_EventScript_Farfetchd_2B
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_2, IlexForest_Movement_Farfetchd_2A
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_2
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_2
	@add clockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_3
	addobject LOCALID_ILEX_FOREST_FARFETCHD_3
	release
	end
IlexForest_EventScript_Farfetchd_2B::
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_2, IlexForest_Movement_Farfetchd_2B
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_2
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_2
	@add counterclockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
	addobject LOCALID_ILEX_FOREST_FARFETCHD_1
	release
	end

IlexForest_EventScript_Farfetchd_3A::
	lock
	faceplayer
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq VAR_FACING, DIR_SOUTH, IlexForest_EventScript_Farfetchd_3B
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_3, IlexForest_Movement_Farfetchd_3A
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_3
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_3
	@add clockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_2
	addobject LOCALID_ILEX_FOREST_FARFETCHD_2
	release
	end
IlexForest_EventScript_Farfetchd_3B::
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_3, IlexForest_Movement_Farfetchd_3B
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_3
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_3
	@add counterclockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_4
	addobject LOCALID_ILEX_FOREST_FARFETCHD_4
	release
	end

IlexForest_EventScript_Farfetchd_4A::
	lock
	faceplayer
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox IlexForest_Text_Kwaaaa, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	goto_if_eq VAR_FACING, DIR_SOUTH, IlexForest_EventScript_Farfetchd_4B
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_4, IlexForest_Movement_Farfetchd_4A
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_4
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_4
	@add clockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_3
	addobject LOCALID_ILEX_FOREST_FARFETCHD_3
	release
	end
IlexForest_EventScript_Farfetchd_4B::
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_4, IlexForest_Movement_Farfetchd_4B
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_4
	removeobject LOCALID_ILEX_FOREST_FARFETCHD_4
	@add counterclockwise farfetchd
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
	addobject LOCALID_ILEX_FOREST_FARFETCHD_1
	release
	end


IlexForest_EventScript_Farfetchd_Leave::
	goto_if_eq VAR_FACING, DIR_EAST, IlexForest_EventScript_Farfetchd_Return
	goto_if_eq VAR_FACING, DIR_SOUTH, IlexForest_EventScript_Farfetchd_Return
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_1, IlexForest_Movement_Farfetchd_Leave
	waitmovement 0
	setobjectxyperm LOCALID_ILEX_FOREST_FARFETCHD_1, 28, 42
	setvar VAR_ILEX_FOREST_FARFETCHD, 2
	clearflag FLAG_HIDE_ILEX_FOREST_KIMONO
	clearflag FLAG_HIDE_ILEX_FOREST_MASTER
	setflag FLAG_HIDE_AZALEA_TOWN_CUT_MASTER
	addobject 1
	release
	end
IlexForest_EventScript_Farfetchd_Return::
	setvar VAR_ILEX_FOREST_FARFETCHD, 0
	applymovement LOCALID_ILEX_FOREST_FARFETCHD_1, IlexForest_Movement_Farfetchd_Return
	waitmovement 0
	setobjectxyperm LOCALID_ILEX_FOREST_FARFETCHD_1, 42, 47
	release
	end
IlexForest_EventScript_Farfetchd_Done::
	release
	end

IlexForest_EventScript_TriggerBot::
	lock
	applymovement OBJ_EVENT_ID_PLAYER Common_Movement_WalkUp
	waitmovement 0
IlexForest_EventScript_Trigger::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox IlexForest_Text_CharcoalMasterIntro, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_HM_CUT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox IlexForest_Text_CharcoalMasterOutro, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_HM_CUT
	setflag FLAG_HIDE_ILEX_FOREST_MASTER
	setflag FLAG_HIDE_ILEX_FOREST_APPRENTICE
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
	setvar VAR_ILEX_FOREST_FARFETCHD, 3
	setvar VAR_AZALEA_TOWN_STATE, 7
	clearflag FLAG_HIDE_AZALEA_TOWN_FARFETCHD
	clearflag FLAG_HIDE_AZALEA_TOWN_CUT_MASTER
	closemessage
	release
	end

IlexForest_EventScript_Picnicker::
	lock
	faceplayer
	msgbox IlexForest_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_EventScript_BugcatcherWayne::
	trainerbattle_single TRAINER_WAYNE IlexForest_Text_BugCatcherWayneSeen, IlexForest_Text_BugCatcherWayneBeaten
	msgbox IlexForest_Text_BugCatcherWayneAfter, MSGBOX_AUTOCLOSE
	end

IlexForest_EventScript_HeadbuttMoveTutor::
	lock
	faceplayer
	goto_if_set FLAG_FINITE_TMS, IlexForest_EventScript_HeadbuttTutorFinite
	clearflag FLAG_MOVE_TUTOR_TAUGHT_HEADBUTT
	msgbox MoveTutor_Text_HeadbuttTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_HeadbuttDeclined
	msgbox MoveTutor_Text_HeadbuttWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, TUTOR_MOVE_HEADBUTT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_HeadbuttDeclined
	goto MoveTutor_EventScript_HeadbuttTaught
	end

IlexForest_EventScript_HeadbuttTutorFinite::
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_HEADBUTT, MoveTutor_EventScript_HeadbuttTaught
	msgbox MoveTutor_Text_HeadbuttTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_HeadbuttDeclined
	call MoveTutor_EventScript_CanOnlyBeLearnedOnceFinite
	goto_if_eq VAR_RESULT, NO, MoveTutor_EventScript_HeadbuttDeclined
	msgbox MoveTutor_Text_HeadbuttWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, TUTOR_MOVE_HEADBUTT
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_HeadbuttDeclined
	setflag FLAG_MOVE_TUTOR_TAUGHT_HEADBUTT
	goto MoveTutor_EventScript_HeadbuttTaught
	end

MoveTutor_EventScript_HeadbuttDeclined::
	msgbox MoveTutor_Text_HeadbuttDeclined, MSGBOX_DEFAULT
	release
	end

MoveTutor_EventScript_HeadbuttTaught::
	setflag FLAG_GET_HEADBUTT
	msgbox MoveTutor_Text_HeadbuttTaught, MSGBOX_DEFAULT
	release
	end


IlexForest_EventScript_Shrine::
	lock
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, IlexForest_EventScript_Celebi_Event
	msgbox IlexForest_Text_Shrine, MSGBOX_DEFAULT
	closemessage
	release
	end

IlexForest_EventScript_Celebi_Event::
	msgbox IlexForest_Text_ShrineCelebiEvent, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, IlexForest_EventScript_Shrine_Cancel
	msgbox IlexForest_Text_InsertGSBall, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_CELEBI
	addobject LOCALID_ILEX_FOREST_CELEBI
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_ILEX_FOREST_CELEBI, IlexForest_Movement_Celebi1
	waitmovement 0
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_ILEX_FOREST_CELEBI, IlexForest_Movement_Celebi2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	waitmovement 0
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_ILEX_FOREST_CELEBI, IlexForest_Movement_Celebi3
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playmoncry SPECIES_CELEBI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	seteventmon SPECIES_CELEBI, 40
	special BattleSetup_StartLegendaryBattle
waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, IlexForest_EventScript_Shrine_Caught
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ILEX_FOREST_CELEBI
	setflag FLAG_HIDE_CELEBI
	fadescreenswapbuffers FADE_FROM_BLACK
IlexForest_EventScript_Kurt::
	clearflag FLAG_HIDE_ILEX_FOREST_KURT
	addobject LOCALID_ILEX_FOREST_KURT
	applymovement LOCALID_ILEX_FOREST_KURT, IlexForest_Movement_Kurt1
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	msgbox IlexForest_Text_KurtCaughtCelebi, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ILEX_FOREST_KURT, IlexForest_Movement_Kurt2
	waitmovement 0
	setflag FLAG_HIDE_ILEX_FOREST_KURT
	removeobject LOCALID_ILEX_FOREST_KURT
	setvar VAR_AZALEA_TOWN_STATE, 10
	release
	end

IlexForest_EventScript_Shrine_Caught::
	setflag FLAG_CAUGHT_CELEBI
	return

IlexForest_EventScript_Shrine_Cancel::
	closemessage
	release
	end


IlexForest_EventScript_SecondCelebi::
	lock
	faceplayer
	playmoncry SPECIES_CELEBI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	seteventmon SPECIES_CELEBI, 40
	special BattleSetup_StartLegendaryBattle
waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, IlexForest_EventScript_SecondCelebiRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ILEX_FOREST_SECOND_CELEBI
	setflag FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

IlexForest_EventScript_SecondCelebiRan::
	release
	end


IlexForest_EventScript_Sign::
	lock
	msgbox IlexForest_Text_Signpost MSGBOX_SIGN
	closemessage
	release
	end

IlexForest_EventScript_Kimono::
	lock
	playbgm MUS_HG_KIMONO_GIRL, TRUE
	playse SE_PIN
	turnobject OBJ_EVENT_ID_FOLLOWER, DIR_NORTH
	applymovement2 LOCALID_ILEX_FOREST_KIMONO, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_ILEX_FOREST_KIMONO, IlexForest_Movement_Kimono_Girl1
	waitmovement 0
	msgbox IlexForest_Text_Kimono_Girl1, MSGBOX_DEFAULT
	closemessage
	playse SE_M_PETAL_DANCE
	applymovement2 LOCALID_ILEX_FOREST_KIMONO, IlexForest_Movement_Kimono_Girl_Spin
	waitmovement 0
	turnobject LOCALID_ILEX_FOREST_KIMONO, DIR_SOUTH
	msgbox IlexForest_Text_Kimono_Girl2, MSGBOX_YESNO
	closemessage
	msgbox IlexForest_Text_Kimono_Girl3, MSGBOX_DEFAULT
	closemessage
	playfirstmoncry
	applymovement2 OBJ_EVENT_ID_FOLLOWER, IlexForest_Movement_Follower1
	waitmovement 0
	playfirstmoncry
	turnobject LOCALID_ILEX_FOREST_KIMONO DIR_WEST
	msgbox IlexForest_Text_Kimono_Girl4, MSGBOX_DEFAULT
	closemessage 
	turnobject LOCALID_ILEX_FOREST_KIMONO DIR_SOUTH
	delay 16
	msgbox IlexForest_Text_Kimono_Girl5, MSGBOX_DEFAULT
	closemessage
	delay 16
	playfirstmoncry
	applymovement2 OBJ_EVENT_ID_FOLLOWER, IlexForest_Movement_Follower2
	applymovement2 LOCALID_ILEX_FOREST_KIMONO, IlexForest_Movement_Kimono_Girl2
	waitmovement 0
	waitmovement 0
	fadedefaultbgm
	setvar VAR_ILEX_FOREST_FARFETCHD, 4
	setflag FLAG_HIDE_ILEX_FOREST_KIMONO
	removeobject LOCALID_ILEX_FOREST_KIMONO
	playfirstmoncry
	applymovement OBJ_EVENT_ID_FOLLOWER, IlexForest_Movement_Follower3
	waitmovement 0
	playfirstmoncry
	release
	end

IlexForest_EventScript_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

IlexForest_EventScript_Ether::
	finditem ITEM_ETHER
	end

IlexForest_EventScript_FullHeal::
	finditem ITEM_FULL_HEAL
	end

IlexForest_EventScript_SunnyDay::
	finditem ITEM_TM_SUNNY_DAY
	end

IlexForest_Movement_Kimono_Girl1:
	walk_right
	face_down
	step_end

IlexForest_Movement_Kimono_Girl_Spin:
	face_left
	delay_8
	face_up
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_up
	delay_8
	face_right
	delay_8
	face_down
	step_end

IlexForest_Movement_Follower1:
	walk_left
	jump_2_up
	walk_up
	face_right
	jump_in_place_right
	delay 16
	face_left
	jump_in_place_left
	delay 16
	face_right
	step_end

IlexForest_Movement_Follower2:
	face_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

IlexForest_Movement_Kimono_Girl2:
	face_left
	delay_16
	walk_left
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

IlexForest_Movement_Follower3:
	delay 16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	jump_2_down
	walk_right
	face_up
	step_end


IlexForest_Movement_Farfetchd_1A:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
IlexForest_Movement_Farfetchd_1B:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
IlexForest_Movement_Farfetchd_2A:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end
IlexForest_Movement_Farfetchd_2B:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end
IlexForest_Movement_Farfetchd_3A:
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
IlexForest_Movement_Farfetchd_3B:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end
IlexForest_Movement_Farfetchd_4A:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
IlexForest_Movement_Farfetchd_4B:
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

IlexForest_Movement_Farfetchd_Leave:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_down
	step_end
IlexForest_Movement_Farfetchd_Return:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up	
	step_end

IlexForest_Movement_Celebi1:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

IlexForest_Movement_Celebi2:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	step_end

IlexForest_Movement_Celebi3:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

IlexForest_Movement_Kurt1:
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

IlexForest_Movement_Kurt2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

IlexForest_Text_ApprenticeIntro:
	.string "Cielos... Mi jefe se pondrá\n"
	.string "furioso...\p"
	.string "El FARFETCH'D que CORTA árboles\n"
	.string "para carbón huyó de mí.\p"
	.string "No puedo buscarlo aquí\n"
	.string "en el BOSQUE VERDE.\p"
	.string "Es muy grande, oscuro y\n"
	.string "da miedo...$"

IlexForest_Text_ApprenticeAfter:
	.string "¡Guau! ¡Muchísimas gracias!\p"
	.string "El POKéMON de mi jefe no me obedece\n"
	.string "porque no tengo una MEDALLA.$"

IlexForest_Text_ItsTheMissingPokemon:
	.string "¡Es el POKéMON perdido!$"

IlexForest_Text_Kwaaaa:
	.string "FARFETCH'D: ¡Kwaa!$"

IlexForest_Text_CharcoalMasterIntro:
	.string "¡Ah! ¡Mi FARFETCH'D!\p"
	.string "¿Lo encontraste, niño?\p"
	.string "Sin él, no podríamos\n"
	.string "CORTAR árboles para carbón.\p"
	.string "¡Gracias, niño!\p"
	.string "Ahora, ¿cómo te agradezco...\p"
	.string "¡Ya sé! Toma esto.$"

IlexForest_Text_CharcoalMasterOutro:
	.string "Es la MO CUT.\n"
	.string "Enséñala a un POKéMON para quitar\l"
	.string "árboles pequeños.\p"
	.string "Claro, necesitas la MEDALLA del\n"
	.string "GIMNASIO de AZALEA para usarla.$"

IlexForest_Text_CharcoalMasterTalkAfter:
	.string "¿Quieres ser mi aprendiz\n"
	.string "fabricando carbón?\p"
	.string "¡Serás un experto en diez años!$"

MoveTutor_Text_HeadbuttTeach:
	.string "¿Qué estoy haciendo?\p"
	.string "Sacudo árboles usando CABEZAZO.\p"
	.string "¿Crees que tu POKéMON también\n"
	.string "querrá usar CABEZAZO?\p"
	.string "Puedo enseñarle el movimiento\n"
	.string "si quieres. ¡Es divertido!$"
	
MoveTutor_Text_HeadbuttWhichMon:
	.string "¡Jeje, claro que sí! Sería genial si\n"
	.string "el POKéMON se pareciera a mí.$"

MoveTutor_Text_HeadbuttDeclined:
	.string "No tienes que ser tímido.\n"
	.string "¡Choquemos las cabezas!$"

MoveTutor_Text_HeadbuttTaught:
	.string "Sacude árboles con CABEZAZO.\n"
	.string "A veces caen POKéMON dormidos.$"

IlexForest_Text_Lass:
	.string "¿Pasó algo con el guardián\n"
	.string "del bosque?$"

IlexForest_Text_Signpost:
	.string "El BOSQUE VERDE está tan tupido\n"
	.string "que no se ve el cielo.\p"
	.string "Busca objetos que puedan haber\n"
	.string "caído al suelo.$"

IlexForest_Text_Shrine:
	.string "SANTUARIO DEL BOSQUE VERDE…\p"
	.string "Es en honor al protector\n"
	.string "del bosque…$"

IlexForest_Text_ShrineCelebiEvent:
	.string "SANTUARIO DEL BOSQUE VERDE…\p"
	.string "Es en honor al protector\n"
	.string "del bosque…\p"
	.string "¿Eh? ¿Qué es esto?\p"
	.string "Es un hueco.\n"
	.string "Parece que la GS BALL cabría\l"
	.string "dentro.\p"
	.string "¿Quieres poner la GS BALL aquí?$"

IlexForest_Text_InsertGSBall:
	.string "{PLAYER} puso la GS BALL.$"

IlexForest_Text_KurtCaughtCelebi:
	.string "¡Uff, fue increíble!\p"
	.string "{PLAYER}, estuvo fantástico. ¡Gracias!\p"
	.string "Las leyendas sobre ese ALTAR eran\n"
	.string "reales después de todo.\p"
	.string "Me siento inspirado por lo que vi.\p"
	.string "¡Me motiva a hacer mejores BALLS!\p"
	.string "¡Me voy!$"

IlexForest_Text_BugCatcherWayneSeen:
	.string "¡No me asustes así!\p"
	.string "¡Ahuyentaste a un POKéMON!$"

IlexForest_Text_BugCatcherWayneBeaten:
	.string "No había visto ese POKéMON antes…$"

IlexForest_Text_BugCatcherWayneAfter:
	.string "Un POKéMON que nunca había visto\n"
	.string "cayó del árbol al usar\l"
	.string "CABEZAZO.\p"
	.string "Debería usar CABEZAZO en otros\n"
	.string "lugares también.$"

IlexForest_Text_Kimono_Girl1:
	.string "CHICA KIMONO, CHICA KIMONO, sola\n"
	.string "y perdida. Pobre chica perdida en\l"
	.string "el oscuro BOSQUE VERDE.$"

IlexForest_Text_Kimono_Girl2:
	.string "¿Me recuerdas de CIUDAD MALVA?\n"
	.string "Debes estar imaginando.\p"
	.string "En fin, ¿me enseñas cómo\n"
	.string "salir de este bosque?$"

IlexForest_Text_Kimono_Girl3:
	.string "Cielos... Tú también estás perdido,\n"
	.string "¿verdad?$"

IlexForest_Text_Kimono_Girl4:
	.string "¡Guau! ¿Me vas a enseñar cómo\n"
	.string "salir de aquí?\p"
	.string "¡Eres un POKéMON muy listo!$"

IlexForest_Text_Kimono_Girl5:
	.string "Nos vemos.$"
