.set LOCALID_ELM, 2
.set LOCALID_AIDE1, 1
.set LOCALID_AIDE2, 3
.set LOCALID_COP, 7
.set PLAYER_STARTER_SPECIES,  VAR_TEMP_2

NewBarkTown_Lab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_Lab_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_Lab_OnFrame
	.byte 0

NewBarkTown_Lab_OnTransition::
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmAtComputer
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, NewBarkTown_Lab_EventScript_ElmAtComputer
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, NewBarkTown_Lab_EventScript_ElmAtComputer
	end
	
NewBarkTown_Lab_OnFrame::
	map_script_2 VAR_NEWBARKTOWN_LABSTATE, 4, NewBarkTown_Lab_EventScript_PoliceEpisode
	.2byte 0

NewBarkTown_Lab_EventScript_ElmAtComputer::
	setobjectxyperm LOCALID_ELM, 3, 2
	setobjectmovementtype LOCALID_ELM, MOVEMENT_TYPE_FACE_UP
	end

NewBarkTown_Lab_EventScript_TriggerStartLabLeft::	
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkRight
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
	end

NewBarkTown_Lab_EventScript_TriggerStartLabRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkLeft
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
	end

NewBarkTown_Lab_EventScript_TriggerStartLab::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_LabMovement_WalkToElm
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_ElmIntro
	end

NewBarkTown_EventScript_Aide1::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_AideAlwaysBusy, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Aide2::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_EventScript_Aide2Testimony
	msgbox NewBarkTown_Lab_Text_AideSave, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Aide2Testimony::
	msgbox NewBarkTown_Lab_Text_AideTheftTestimony, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_Elm::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_NEWBARKTOWN_LAB_AIDE, NewBarkTown_Lab_EventScript_ElmAideIsWaiting
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 7, NewBarkTown_Lab_EventScript_ElmMasterBall
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 8, NewBarkTown_Lab_EventScript_ElmKimono
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 9, NewBarkTown_Lab_EventScript_ElmLeague
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 10, NewBarkTown_Lab_EventScript_ElmSSTicket

	goto_if_set FLAG_SHOWN_ELM_TOGEPI, NewBarkTown_Lab_EventScript_Elm_CallMe
	call_if_unset FLAG_SHOWN_ELM_TOGEPI, NewBarkTown_Lab_EventScript_Elm_Check_Togepi
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 1, NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_Lab_EventScript_ElmState5

	goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmState5
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, CopNewBarkTown_Lab_EventScript_ElmState2
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, CopNewBarkTown_Lab_EventScript_ElmState2
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_MrPokemon
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ElmChoosePokemon
	end

NewBarkTown_Lab_EventScript_ElmAideIsWaiting::
	msgbox NewBarkTown_Lab_Text_ElmAideIsWaiting, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_Text_ElmAideIsWaiting:
	.string "¡{PLAYER}!\p"
	.string "¿Qué haces aquí?\p"
	.string "Mi ayudante te sigue esperando\n"
	.string "¡en CIUDAD MALVA!$"

NewBarkTown_Lab_EventScript_ElmIntro::
	msgbox NewBarkTown_Lab_Text_ElmIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
	end

NewBarkTown_Lab_EventScript_ElmRefused::
	msgbox NewBarkTown_Lab_Text_ElmRefused, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
	end

NewBarkTown_Lab_EventScript_ElmAccepted::
	msgbox NewBarkTown_Lab_Text_ElmAccepted, MSGBOX_DEFAULT
	msgbox NewBarkTown_Lab_Text_ElmResearchAmbitions, MSGBOX_DEFAULT
	delay 30
	playse SE_PC_LOGIN
	waitse
	playse SE_PIN
	applymovement LOCALID_ELM, Common_Movement_QuestionMark
	delay 60
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmail
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Left
	waitmovement 0
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmGotAnEmail, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ReturnFromEmail
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
	waitmovement 0
	delay 30
	msgbox NewBarkTown_Lab_Text_ElmMissionFromMrPokemon, MSGBOX_DEFAULT
	goto NewBarkTown_Lab_EventScript_ElmChoosePokemon
	end

NewBarkTown_Lab_EventScript_ElmChoosePokemon::
	msgbox NewBarkTown_Lab_Text_ElmChooseAPokemon, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEWBARKTOWN_LABSTATE, 1
	release
	end

NewBarkTown_Lab_EventScript_TriggerReturnPlayer::
	lock
	msgbox NewBarkTown_Lab_Text_ElmWhereGoing, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_ReturnPlayer
	waitmovement 0
	release
	end

NewBarkTown_Lab_EventScript_ShouldntTouch::
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	closemessage
	end


NewBarkTown_Lab_EventScript_ChikoritaBall::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ChikoritaBall_Choice
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	release
	closemessage
	end

NewBarkTown_Lab_EventScript_ChikoritaBall_Choice::
	callnative DisableStaticRandomizer
	setvar VAR_STARTER_MON, 0
	setvar PLAYER_STARTER_SPECIES, SPECIES_CHIKORITA
	showmonpic PLAYER_STARTER_SPECIES, 10, 3
	playmoncry PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
	bufferspeciesname STR_VAR_1, PLAYER_STARTER_SPECIES
	buffermoncategory STR_VAR_2, PLAYER_STARTER_SPECIES
	msgbox NewBarkTown_Lab_Text_ChooseChikorita, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ChoseStarter
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_DeclinedStarter
	end

NewBarkTown_Lab_EventScript_CyndaquilBall::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_CyndaquilBall_Choice
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_CyndaquilBall_Choice::
	callnative DisableStaticRandomizer
	setvar VAR_STARTER_MON, 1
	setvar PLAYER_STARTER_SPECIES, SPECIES_CYNDAQUIL
	showmonpic PLAYER_STARTER_SPECIES, 10, 3
	playmoncry PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
	bufferspeciesname STR_VAR_1, PLAYER_STARTER_SPECIES
	buffermoncategory STR_VAR_2, PLAYER_STARTER_SPECIES
	msgbox NewBarkTown_Lab_Text_ChooseCyndaquil, MSGBOX_YESNO	
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ChoseStarter
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_DeclinedStarter
	end

NewBarkTown_Lab_EventScript_TotodileBall::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_TotodileBall_Choice
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	release
	closemessage
	end

NewBarkTown_Lab_EventScript_TotodileBall_Choice::
	callnative DisableStaticRandomizer
	setvar VAR_STARTER_MON, 2
	setvar PLAYER_STARTER_SPECIES, SPECIES_TOTODILE
	showmonpic PLAYER_STARTER_SPECIES, 10, 3
	playmoncry PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
	bufferspeciesname STR_VAR_1, PLAYER_STARTER_SPECIES
	buffermoncategory STR_VAR_2, PLAYER_STARTER_SPECIES
	msgbox NewBarkTown_Lab_Text_ChooseTotodile, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ChoseStarter
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_DeclinedStarter
	end

NewBarkTown_Lab_EventScript_DeclinedStarter::
	hidemonpic
	msgbox NewBarkTown_Lab_Text_DidntChooseStarter, MSGBOX_DEFAULT
	closemessage
	callnative EnableStaticRandomizer
	release
	end

NewBarkTown_Lab_EventScript_ChoseStarter::
	callnative EnableStaticRandomizer
	hidemonpic
	removeobject VAR_LAST_TALKED
	msgbox NewBarkTown_Lab_Text_ChoseStarter, MSGBOX_DEFAULT
	givemon PLAYER_STARTER_SPECIES, 5
	setflag FLAG_SYS_POKEMON_GET
	playfanfare MUS_OBTAIN_ITEM
	bufferspeciesname STR_VAR_1, PLAYER_STARTER_SPECIES
	message NewBarkTown_Lab_Text_ReceivedStarter
	waitfanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_ChoseStarter_NicknameStarter_Nuzlocke
	msgbox NewBarkTown_Lab_Text_Nickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_NicknameStarter
	callnative UpdateFollowingPokemon
	release
	end

NewBarkTown_Lab_EventScript_NicknameStarter::
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	end

NewBarkTown_Lab_EventScript_ChoseStarter_NicknameStarter_Nuzlocke::
	message NewBarkTown_Lab_Text_Nickname
	waitmessage
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	release
	end

NewBarkTown_Lab_EventScript_MrPokemon::
	setvar VAR_NEWBARKTOWN_LABSTATE, 2
	setvar VAR_NEWBARK_TOWN_STATE, 3
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_EAST, NewBarkTown_Lab_EventScript_MrPokemonMovementSafe
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmailSlow
	waitmovement 0
	clearflag FLAG_RECEIVED_FIRST_BALLS
	clearflag FLAG_RECEIVED_FIRST_POTION
	setvar VAR_NEWBARK_TOWN_STATE, 3
	release
	end

NewBarkTown_Lab_EventScript_MrPokemonMovementSafe::
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_GotoComputerSafe
	waitmovement 0
	clearflag FLAG_RECEIVED_FIRST_BALLS
	clearflag FLAG_RECEIVED_FIRST_POTION
	setvar VAR_NEWBARK_TOWN_STATE, 3
	release
	end

CopNewBarkTown_Lab_EventScript_ElmState2::
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
	applymovement LOCALID_ELM, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_HealingMachine1::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_HealingMachine2
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_HealingMachine2::
	call Common_EventScript_OutOfCenterPartyHeal
	release
	end



NewBarkTown_Lab_EventScript_TriggerAideGivePotion::
	lock
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Lab_Text_AideGivePotion, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FIRST_POTION
	setvar VAR_NEWBARKTOWN_LABSTATE, 3
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	release
	end

NewBarkTown_Lab_EventScript_HideCyndaquil::
	setflag FLAG_HIDE_CYNDAQUILBALL
	return
NewBarkTown_Lab_EventScript_HideTotodile::
	setflag FLAG_HIDE_TOTODILEBALL
	return
NewBarkTown_Lab_EventScript_HideChikorita::
	setflag FLAG_HIDE_CHIKORITABALL
	return

NewBarkTown_Lab_EventScript_PoliceEpisode::
	lock
	setmetatile 7, 1, METATILE_R26_21_Broken_Window, TRUE
	call_if_eq VAR_STARTER_MON, 0 NewBarkTown_Lab_EventScript_HideCyndaquil
	call_if_eq VAR_STARTER_MON, 1 NewBarkTown_Lab_EventScript_HideTotodile
	call_if_eq VAR_STARTER_MON, 2 NewBarkTown_Lab_EventScript_HideChikorita
	applymovement OBJ_EVENT_ID_PLAYER, NeBarkTownLab_Movement_PlayerWalkToCop
	waitmovement 0
	setflag FLAG_HIDE_LAB_POLICEMAN
	turnobject LOCALID_COP DIR_WEST
	msgbox NewBarkTown_Lab_Text_Officer1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
	end

NewBarkTown_Lab_EventScript_PoliceNo::
	msgbox NewBarkTown_Lab_Text_OfficerNo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
	end

NewBarkTown_Lab_EventScript_PoliceYes::
	closemessage
	special NameRival
	waitstate
	msgbox NewBarkTown_Lab_Text_Officer2_1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_Lab_EventScript_PoliceYes
	msgbox NewBarkTown_Lab_Text_Officer2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
	waitmovement 0
	removeobject LOCALID_COP

	@ setobjectxyperm LOCALID_COP, 25, 4
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
	delay 20
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
	setvar VAR_NEWBARK_TOWN_STATE, 4
	setflag FLAG_HIDE_MOMS_FRIEND
	clearflag FLAG_HIDE_MOMS_FRIEND2
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_EXP_SHARE
	removeitem ITEM_MYSTERY_EGG
	end

NewBarkTown_Lab_EventScript_ElmState5::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_ElmStudyingEgg, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELM Common_Movement_FaceOriginalDirection
	release
	end
	
NewBarkTown_Lab_EventScript_ElmMasterBall::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall1, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall2, MSGBOX_DEFAULT
	closemessage
	delay 20
	playse SE_PIN
	applymovement LOCALID_ELM, Common_Movement_ExclamationMark
	delay 60
	msgbox NewBarkTown_Lab_Text_KimonoGirls, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEWBARKTOWN_LABSTATE, 8
	setvar VAR_ECRUTEAK_CITY_THEATER, 4
	setflag FLAG_HIDE_ECRUTEAK_SILVER
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	release
	end

NewBarkTown_Lab_EventScript_ElmKimono::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_KimonoWaiting, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_ElmLeague::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_League, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_ElmSSTicket::
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket1, MSGBOX_DEFAULT
	giveitem ITEM_SS_TICKET
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket2, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_SSAQUA_1F_GRANDPA
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
	clearflag FLAG_HIDE_OLIVINE_PORT_OAK
	release
	end

NewBarkTown_Lab_EventScript_TriggerAideGiveBalls::
	lock
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Lab_Text_AideGiveBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POKE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FIRST_BALLS
	setvar VAR_NEWBARKTOWN_LABSTATE, 6
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	release
	end

NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg::
	msgbox NewBarkTown_Lab_Text_ElmWaitingEggHatch, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_Elm_Check_Togepi::
	specialvar VAR_RESULT, CheckTogepi
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_Elm_Togepi_Seen
	return

NewBarkTown_Lab_EventScript_Elm_Togepi_Seen::
	msgbox NewBarkTown_Lab_Text_ShowTogepi1, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ShowTogepi2, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ShowTogepi3, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ElmGiveEverstone1, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_EVERSTONE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox NewBarkTown_Lab_Text_ElmGiveEverstone2, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SHOWN_ELM_TOGEPI
	release
	end

NewBarkTown_Lab_EventScript_Elm_CallMe::
	msgbox NewBarkTown_Lab_Text_Elm_CallMe, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_Movement_WalkRight:
	walk_right
	step_end

NewBarkTown_Lab_Movement_WalkLeft:
	walk_left
	step_end

NewBarkTown_LabMovement_WalkToElm:
	walk_up
	walk_up
	walk_up
	step_end

NewBarkTown_Lab_Movement_ReturnPlayer:
	walk_up
	step_end

NewBarkTown_Lab_Movement_CheckEmail:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	step_end

NewBarkTown_Lab_Movement_CheckEmailSlow:
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

NewBarkTown_Lab_Movement_GotoComputerSafe:
	walk_up
	walk_left
	walk_left
	walk_left
	face_up
	step_end

NewBarkTown_Lab_Movement_ReturnFromEmail:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_down
	step_end

NewBarkTown_Lab_Movement_Look_Left:
	face_left
	step_end

NewBarkTown_Lab_Movement_Look_Up:
	face_up
	step_end


NewBarkTown_Lab_Movement_Aide1WalkToPlayer:
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

NewBarkTown_Lab_Movement_Aide1LeavePlayer:
	walk_left
	walk_left
	walk_up
	walk_up
	face_down
	step_end

NeBarkTownLab_Movement_PlayerWalkToCop:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_up
	face_right
	step_end

NewBarkTown_Lab_Movement_CopLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

NewBarkTown_Lab_Movement_PlayerStepsToElm:
	walk_right
	face_up
	step_end

NewBarkTown_Lab_Movement_ElmStepBack:
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	step_end

NewBarkTown_Lab_Movement_ElmStepForward:
	walk_fast_down
	step_end

NewBarkTown_Lab_Text_ShouldntTouch:
	.string "Mejor no tocarlo.$"

NewBarkTown_Lab_Text_ElmIntro:
	.string "ELM: ¡{PLAYER}! ¡Ahí estás!\p"
	.string "Necesito pedirte un favor.\p"
	.string "Estoy investigando un nuevo\n"
	.string "POKéMON. Me preguntaba\l"
	.string "si podrías ayudarme\l"
	.string "con eso, {PLAYER}.\p"
	.string "Verás…\p"
	.string "Escribo un trabajo que quiero\n"
	.string "presentar en una conferencia.\p"
	.string "Pero hay cosas que aún no\n"
	.string "entiendo del todo.\p"
	.string "¡Bien!\p"
	.string "Quiero que críes a un\n"
	.string "POKéMON que atrapé hace poco.$"

NewBarkTown_Lab_Text_ElmAccepted:
	.string "¡Gracias, {PLAYER}!\n"
	.string "¡Eres de gran ayuda!$"

NewBarkTown_Lab_Text_ElmRefused:
	.string "Pero… ¡Por favor, necesito\n"
	.string "tu ayuda!$"

NewBarkTown_Lab_Text_ElmResearchAmbitions:
	.string "Cuando publique mis hallazgos,\n"
	.string "seguro profundizaremos\p"
	.string "en los muchos misterios de\n"
	.string "los POKéMON.\p"
	.string "¡Cuenta con ello!$"

NewBarkTown_Lab_Text_ElmGotAnEmail:
	.string "¡Ah, hola! ¡Me llegó un correo!\p"
	.string "… … … … … … … …\n"
	.string "Mmm… Ajá…\p"
	.string "Bien…$"

NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
	.string "Escucha.\p"
	.string "Tengo un conocido llamado\n"
	.string "SR. POKéMON.\p"
	.string "Siempre encuentra cosas raras y\n"
	.string "delira con sus descubrimientos.\p"
	.string "En fin, acabo de recibir correo\n"
	.string "de él diciendo que esta vez\l"
	.string "es de verdad.\p"
	.string "Es intrigante, pero estamos\n"
	.string "ocupados con la investigación...\p"
	.string "¡Un momento!\n"
	.string "¡Ya sé!\p"
	.string "{PLAYER}, ¿puedes ir tú\n"
	.string "en nuestro lugar?$"

NewBarkTown_Lab_Text_ElmChooseAPokemon:
	.string "Quiero que críes a uno de\n"
	.string "los POKéMON que están en estas BALLS.\p"
	.string "Serás el primer compañero\n"
	.string "de ese POKéMON, {PLAYER}!\p"
	.string "Vamos. ¡Elige uno!$"

NewBarkTown_Lab_Text_ElmWhereGoing:
	.string "ELM: ¡Espera! ¿Adónde\n"
	.string "vas?$"

NewBarkTown_Lab_Text_ChooseCyndaquil:
	.string "ELM: ¿Te llevas a {STR_VAR_1},\n"
	.string "el POKéMON {STR_VAR_2}?$"

NewBarkTown_Lab_Text_ChooseTotodile:
	.string "ELM: ¿Quieres a {STR_VAR_1},\n"
	.string "el POKéMON {STR_VAR_2}?$"

NewBarkTown_Lab_Text_ChooseChikorita:
	.string "ELM: ¿Así que te gusta {STR_VAR_1},\n"
	.string "el POKéMON {STR_VAR_2}?$"

NewBarkTown_Lab_Text_DidntChooseStarter:
	.string "ELM: Piénsalo con calma.\p"
	.string "Tu compañero es importante.$"

NewBarkTown_Lab_Text_ChoseStarter:
	.string "ELM: ¡Creo que ese POKéMON\n"
	.string "también es genial!$"

NewBarkTown_Lab_Text_ReceivedStarter:
	.string "¡{PLAYER} recibió a {STR_VAR_1}!$"

NewBarkTown_Lab_Text_Nickname:
	.string "¿Quieres darle un apodo\n"
	.string "a {STR_VAR_1}?$"

NewBarkTown_Lab_Text_ElmDirections1:
	.string "El SR. POKéMON vive un poco\n"
	.string "más allá de CIUDAD CEREZO,\l"
	.string "la ciudad siguiente.\p"
	.string "Es casi un camino directo\n"
	.string "hasta allá, no tiene pérdida.\p"
	.string "Pero por si acaso, tienes mi\n"
	.string "número. ¡Llámame si pasa\l"
	.string "algo!$"


NewBarkTown_Lab_Text_ElmLetYourMonBattle:
	.string "Si aparece un POKéMON salvaje,\n"
	.string "¡deja que el tuyo lo enfrente!$"

NewBarkTown_Lab_Text_ElmDirections2:
	.string "Si aparece un POKéMON salvaje,\n"
	.string "¡deja que el tuyo luche!\p"
	.string "Si tu POKéMON está herido,\n"
	.string "cúralo con la máquina que tengo\l"
	.string "a la derecha o en el CENTRO POKéMON.\p"
	.string "¡Cuento contigo!$"

NewBarkTown_Lab_Text_GotElmsNumber:
	.string "{PLAYER} obtuvo el número\n"
	.string "de teléfono de ELM.$"

NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
	.string "El SR. POKéMON va a todos lados\n"
	.string "y encuentra rarezas.\p"
	.string "Lástima que sean solo raras\n"
	.string "y no muy útiles…$"

NewBarkTown_Lab_Text_ElmPokeBall:
	.string "Contiene un POKéMON atrapado\n"
	.string "por el PROF.ELM.$"

@THEFT================================================================================

NewBarkTown_Lab_Text_ElmAfterTheft1:
	.string "ELM: {PLAYER}, esto es terrible…\p"
	.string "Ah, sí, ¿cuál fue el gran\n"
	.string "descubrimiento del SR. POKéMON?$"

NewBarkTown_Lab_Text_ElmAfterTheft2:
	.string "{PLAYER} le entregó el HUEVO\n"
	.string "MISTERIOSO al PROF.ELM.$"

NewBarkTown_Lab_Text_ElmAfterTheft3:
	.string "ELM: ¿Esto?$"

NewBarkTown_Lab_Text_ElmAfterTheft4:
	.string "Pero… ¿Es un HUEVO POKéMON?\p"
	.string "Si lo es, ¡es un gran\n"
	.string "descubrimiento!\p"
	.string "ELM: ¿¡Qué!?\p"
	.string "¿El PROF.OAK te dio una POKéDEX?\p"
	.string "{PLAYER}, ¿es cierto?\n"
	.string "¡E-increíble!\p"
	.string "Él ve el potencial de la gente\n"
	.string "como entrenadores.\p"
	.string "Vaya, {PLAYER}. Puede que tengas\n"
	.string "lo que hace falta para ser CAMPEÓN.\p"
	.string "También pareces llevarte\n"
	.string "genial con los POKéMON.\p"
	.string "Deberías aceptar el reto\n"
	.string "de los GIMNASIOS POKéMON.\p"
	.string "El GIMNASIO más cercano\n"
	.string "está en CIUDAD MALVA.\p"
	.string "…{PLAYER}. El camino al\n"
	.string "campeonato será muy largo.\p"
	.string "Antes de irte, asegúrate\n"
	.string "de hablar con tu mamá.$"

NewBarkTown_Lab_Text_ElmStudyingEgg:
	.string "ELM: ¡No te rindas!\n"
	.string "Te llamo si averiguo algo\l"
	.string "sobre ese HUEVO!$"

NewBarkTown_Lab_Text_ElmAideHasEgg:
	.string "ELM: ¿{PLAYER}? ¿No te encontraste\n"
	.string "con mi ayudante?\p"
	.string "Debía recibirte con el\n"
	.string "HUEVO en el CENTRO POKéMON\p"
	.string "de CIUDAD MALVA.\p"
	.string "Habrás pasado de largo.\n"
	.string "Intenta alcanzarlo allá.$"

NewBarkTown_Lab_Text_ElmWaitingEggHatch:
	.string "ELM: Oye, ¿el HUEVO ha\n"
	.string "cambiado algo?$"

NewBarkTown_Lab_Text_ElmThoughtEggHatched:
	.string "¿{PLAYER}? Pensé que el\n"
	.string "HUEVO había eclosionado.\p"
	.string "¿Dónde está el POKéMON?$"

NewBarkTown_Lab_Text_ShowTogepi1:
	.string "ELM: ¡{PLAYER}, te ves genial!$"

NewBarkTown_Lab_Text_ShowTogepi2:
	.string "¿Qué? ¡¿Ese POKéMON?!$"

NewBarkTown_Lab_Text_ShowTogepi3:
	.string "¡El HUEVO eclosionó! Así que\n"
	.string "los POKéMON nacen de HUEVOS…\p"
	.string "No, quizá no todos los POKéMON\n"
	.string "lo hacen.\p"
	.string "Vaya, aún queda mucha\n"
	.string "investigación por hacer.$"

NewBarkTown_Lab_Text_ElmGiveEverstone1:
	.string "¡Gracias, {PLAYER}! ¡Nos ayudas\n"
	.string "a resolver misterios POKéMON!\p"
	.string "Quiero que tengas esto como\n"
	.string "muestra de nuestro aprecio.$"

NewBarkTown_Lab_Text_ElmGiveEverstone2:
	.string "Eso es una PIEDRA ETERNA.\p"
	.string "Algunas especies de POKéMON\n"
	.string "evolucionan al subir de nivel.\p"
	.string "Un POKéMON que lleve la\n"
	.string "PIEDRA ETERNA no evoluciona.\p"
	.string "Dásela a un POKéMON que no\n"
	.string "quieras evolucionar.$"

NewBarkTown_Lab_Text_ElmCallYou:
	.string "ELM: {PLAYER}, te llamo si\n"
	.string "pasa algo.$"

NewBarkTown_Lab_Text_AideAfterTheft:
	.string "…ay… Ese POKéMON robado.\p"
	.string "Me pregunto cómo estará.\p"
	.string "Dicen que un POKéMON criado\n"
	.string "por alguien malo se vuelve malo.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall1:
	.string "ELM: ¡Hola, {PLAYER}!\p"
	.string "Gracias a ti, mi investigación\n"
	.string "¡va genial!\p"
	.string "Toma esto como muestra\n"
	.string "de mi agradecimiento.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall2:
	.string "¡La MASTER BALL es la mejor!\p"
	.string "¡Es la BALL definitiva! Atrapará\n"
	.string "cualquier POKéMON sin fallar.\p"
	.string "Se entrega solo a investigadores\n"
	.string "POKéMON reconocidos.\p"
	.string "Creo que tú le darás mejor uso\n"
	.string "que yo, ¡{PLAYER}!$"

NewBarkTown_Lab_Text_KimonoGirls:
	.string "Por cierto...\n"
	.string "Un grupo de hermosas CHICAS\l"
	.string "KIMONO te estaba buscando.\p"
	.string "Me dijeron que te esperan\n"
	.string "en el TEATRO DE DANZA\l" 
	.string "DE CIUDAD IRIS.\p"
	.string "Sé que has pasado por muchas\n"
	.string "cosas desde que ese HUEVO te\l"
	.string "metió en todo esto...\p"
	.string "Espero que lo lleves hasta el final.$"

NewBarkTown_Lab_Text_KimonoWaiting:
	.string "PROF.ELM: Las CHICAS KIMONO\n"
	.string "te esperan en el TEATRO\l"
	.string "DE DANZA DE CIUDAD IRIS.$"

NewBarkTown_Lab_Text_League:
	.string "PROF.ELM: Jajaja...\n"
	.string "¡Buen trabajo!\p"
	.string "Ese raro HUEVO te ha traído\n"
	.string "muchos problemas, ¿eh?\p"
	.string "¿Las CHICAS KIMONO dijeron algo\n"
	.string "sobre mí?\p"
	.string "No tengo nada que ver.\p"
	.string "Tú tomaste tu decisión y\n"
	.string "la llevaste a cabo.\p"
	.string "Habiendo hecho tanto, ya\n"
	.string "¡deberías poder enfrentar la LIGA!\p"
	.string "Deberías ir a la MESETA\n"
	.string "AÑIL.\p"
	.string "¿Sabes cómo llegar?\n"
	.string "Sigue la RUTA 27 hasta la RUTA 26.\p"
	.string "¡Al llegar, ve derecho al norte!$"


NewBarkTown_Lab_Text_ElmGiveTicket1:
	.string "ELM: ¡{PLAYER}! ¡Ahí estás!\p"
	.string "Te llamé porque tengo\n"
	.string "algo para ti.\p"
	.string "¿Ves? Es un BILLETE S.S.\p"
	.string "Ahora podrás atrapar POKéMON\n"
	.string "en KANTO.$"

NewBarkTown_Lab_Text_ElmGiveTicket2:
	.string "El barco sale de CIUDAD\n"
	.string "OLIVO.\p"
	.string "Pero eso ya lo sabías,\n"
	.string "{PLAYER}.\p"
	.string "Después de todo, has viajado\n"
	.string "por todos lados con tu POKéMON.\p"
	.string "¡Dale saludos al PROF.OAK en\n"
	.string "KANTO!$"

NewBarkTown_Lab_Text_LabMonEgg:
	.string "Es el HUEVO POKéMON que\n"
	.string "estudia el PROF.ELM.$"

NewBarkTown_Lab_Text_AideGivePotion:
	.string "{PLAYER}, quiero que tengas\n"
	.string "esto para tu encargo.$"

NewBarkTown_Lab_Text_AideAlwaysBusy:
	.string "Solo somos tres, así que\n"
	.string "siempre estamos ocupados.$"

NewBarkTown_Lab_Text_AideSave:
	.string "¡No olvides guardar tu partida\n"
	.string "con frecuencia!\p"
	.string "¡Pulsa START y luego\n"
	.string "GUARDA la partida!$"

NewBarkTown_Lab_Text_AideTheftTestimony:
	.string "Se oyó un ruido fuerte\n"
	.string "afuera…\p"
	.string "Cuando fuimos a ver,\n"
	.string "alguien robó un POKéMON.\p"
	.string "¡Es increíble que alguien\n"
	.string "hiciera eso!\p"
	.string "…ay… Ese POKéMON robado.\p"
	.string "Me pregunto cómo estará.\p"
	.string "Dicen que un POKéMON criado\n"
	.string "por alguien malo se vuelve malo.$"

NewBarkTown_Lab_Text_AideGiveBalls:
	.string "¡{PLAYER}!\p"
	.string "¡Úsalas en tu búsqueda\n"
	.string "de la POKéDEX!$"

NewBarkTown_Lab_Text_AideExplainBalls:
	.string "Para completar tu POKéDEX,\n"
	.string "tienes que atrapar POKéMON.\p"
	.string "Lanza POKé BALLS a los POKéMON\n"
	.string "salvajes para conseguirlos.$"

NewBarkTown_Lab_Text_Officer1:
	.string "Oí que robaron un POKéMON\n"
	.string "aquí…\p"
	.string "Justo estaba pidiendo\n"
	.string "información al PROF.ELM.\p"
	.string "Al parecer, fue un joven\n"
	.string "de pelo largo y rojo…\p"
	.string "¿Qué?\p"
	.string "¿Luchaste contra un entrenador\n"
	.string "así?\p"
	.string "¿Por casualidad supiste\n"
	.string "su nombre?$"

NewBarkTown_Lab_Text_Officer2_1:
	.string "¡Bien! ¿Así que se llamaba {RIVAL}?$"

NewBarkTown_Lab_Text_Officer2:
	.string "¡Gracias por ayudar en mi\n"
	.string "investigación!$"

NewBarkTown_Lab_Text_OfficerNo:
	.string "¡¿Seguro que no supiste su nombre?!$"

NewBarkTown_Lab_Text_Elm_CallMe:
	.string "¡Ah, {PLAYER}!\p"
	.string "¿Cómo va tu POKéDEX?\n"
	.string "Ahora estoy ocupado, pero llámame\l"
	.string "¡y reviso tu progreso!$"
