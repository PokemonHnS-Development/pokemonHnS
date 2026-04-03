.set LOCALID_AZALEA_TOWN_KURT_BEFORE, 1
.set LOCALID_AZALEA_TOWN_KURT, 3

AzaleaTown_KurtsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AzaleaTown_KurtsHouse_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_KurtsHouse_OnTransition
	.byte 0

AzaleaTown_KurtsHouse_OnTransition::
	goto_if_eq VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup
	end

AzaleaTown_KurtsHouse_OnFrame::
	map_script_2 VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWell
	.2byte 0

AzaleaTown_KurtsHouse_EventScript_KurtBefore::
	lock
	faceplayer
	msgbox KurtsHouse_Text_KurtMakingBallsMustWait, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, AzaleaTown_KurtsHouse_EventScript_PlayerMove
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
	setflag FLAG_HIDE_KURT_1
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	setvar VAR_AZALEA_TOWN_STATE, 2
	release
	end

AzaleaTown_KurtsHouse_EventScript_PlayerMove::
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_KurtsHouse_Movement_Player
	waitmovement 0
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
	setflag FLAG_HIDE_KURT_1
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_KURT_2, AzaleaTown_KurtsHouse_EventScript_Girl2
	goto_if_set FLAG_HIDE_KURT_1, AzaleaTown_KurtsHouse_EventScript_Girl3
	msgbox KurtsHouse_Text_GranddaughterSlowpokeGone, MSGBOX_DEFAULT
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl2::
	goto_if_eq VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 4, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 6, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_Girl5
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_Girl5

	msgbox KurtsHouse_Text_GranddaughterDad, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl3::
	msgbox KurtsHouse_Text_GranddaughterLonely, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl4::
	msgbox KurtsHouse_Text_GranddaughterSlowpokeBack, MSGBOX_DEFAULT
	closemessage
	release
	end	

AzaleaTown_KurtsHouse_EventScript_Girl5::
	msgbox KurtsHouse_Text_GranddaughterSound, MSGBOX_DEFAULT
	closemessage
	release
	end	

AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup::
	setobjectmovementtype LOCALID_AZALEA_TOWN_KURT, MOVEMENT_TYPE_FACE_DOWN
	end

AzaleaTown_KurtsHouse_EventScript_ReturnFromWell::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox KurtsHouse_Text_KurtHonoredToMakeBalls, MSGBOX_DEFAULT
	giveitem ITEM_FAST_BALL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtBallsFromApricorns, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	setvar VAR_AZALEA_TOWN_STATE, 4
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall::
	checkitem ITEM_GS_BALL
	goto_if_eq VAR_RESULT, TRUE, AzaleaTown_KurtsHouse_EventScript_KurtGsBall
	return

AzaleaTown_KurtsHouse_EventScript_Kurt::
	lock
	faceplayer
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_KurtGsBall2
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_KurtGsBall3
	msgbox KurtsHouse_Text_KurtAskYouHaveAnApricorn, MSGBOX_DEFAULT
	closemessage
	call_if_unset FLAG_CAUGHT_CELEBI, AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall
AzaleaTown_KurtsHouse_EventScript_Kurt2::
	kurtshop AzaleaTown_KurtsHouse_KurtBallList
	@ Check if purchase was made (VAR_RESULT set by shop)
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_KurtCancel
	@ Shop handled transaction (berries removed, item stored in VAR_0x8004, quantity in VAR_0x8005)
	
	
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_SOUTH
	@ Check quantity to determine singular or plural text
	goto_if_eq VAR_0x8005, 1, AzaleaTown_KurtsHouse_EventScript_SingularBall
	@ Plural case (1+ balls)
	bufferitemname 0, VAR_0x8004
	msgbox KurtsHouse_Text_KurtJustFinishedYourBallPlural, MSGBOX_DEFAULT
	waitmessage
	bufferitemname 0, VAR_0x8004
	buffernumberstring 1, VAR_0x8005
	playfanfare MUS_OBTAIN_ITEM
	msgbox KurtsHouse_Text_ObtainedPlural, MSGBOX_DEFAULT
	waitfanfare
	additem VAR_0x8004, VAR_0x8005
	msgbox KurtsHouse_Text_KurtTurnedOutGreatPlural, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_SingularBall::
	@ Singular case (1 ball)
	bufferitemname 0, VAR_0x8004
	msgbox KurtsHouse_Text_KurtJustFinishedYourBallSingular, MSGBOX_DEFAULT
	waitmessage
	bufferitemname 0, VAR_0x8004
	playfanfare MUS_OBTAIN_ITEM
	msgbox KurtsHouse_Text_ObtainedSingular, MSGBOX_DEFAULT
	waitfanfare
	additem VAR_0x8004, VAR_0x8005
	msgbox KurtsHouse_Text_KurtTurnedOutGreatSingular, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

	.align 2
AzaleaTown_KurtsHouse_KurtBallList:
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_HEAVY_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_NONE
	release
	end

AzaleaTown_KurtsHouse_EventScript_DontHaveBerry::
	msgbox KurtsHouse_Text_KurtThatsALetdown, MSGBOX_DEFAULT
	closemessage
	goto AzaleaTown_KurtsHouse_EventScript_Kurt2
	release
	end
	
AzaleaTown_KurtsHouse_EventScript_KurtCancel::
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtGsBall::
	msgbox KurtsHouse_Text_KurtWhatIsThat, MSGBOX_DEFAULT
	closemessage
	removeitem ITEM_GS_BALL
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtThisBallStartedToShake, MSGBOX_DEFAULT
	closemessage
	playse SE_M_PETAL_DANCE
	waitse
	playse SE_PIN
	applymovement LOCALID_AZALEA_TOWN_KURT, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	delay 60
	waitse
	playse SE_M_PETAL_DANCE
	waitse
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Look_Around
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTownKurt_Movement_Look_Around
	waitmovement 0
	waitmovement 0
AzaleaTown_KurtsHouse_EventScript_KurtGsBall2::
	msgbox KurtsHouse_Text_Kurt_Whatwasthat, MSGBOX_DEFAULT
	setvar VAR_AZALEA_TOWN_STATE, 8
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtGsBall3::
	msgbox KurtsHouse_Text_Forest, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox KurtsHouse_Text_BallAnyway, MSGBOX_DEFAULT
	closemessage
	goto AzaleaTown_KurtsHouse_EventScript_Kurt2
	release
	end
KurtsHouse_Text_BallAnyway:
	.string "Anyway, can I make you some BALLS?$"

AzaleaTown_KurtsHouse_EventScript_OakPhoto::
	msgbox KurtsHouse_Text_OakPhoto, MSGBOX_SIGN
	closemessage
	end

AzaleaTown_KurtsHouse_EventScript_CelebiStatue::
	msgbox KurtsHouse_Text_CelebiStatue, MSGBOX_SIGN
	closemessage
	end

AzaleaTownKurt_Movement_Look_Around:
	face_left
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_down
	delay_8
	face_left
	step_end

AzaleaTownKurt_Movement_Making_Ball:
	face_up
	walk_in_place_fast_up
	delay_8
	walk_in_place_fast_up
	delay_8
	walk_in_place_fast_up
	step_end

AzaleaTown_KurtsHouse_Movement_Player:
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

AzaleaTown_KurtsHouse_Movement_KurtWalkDown:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

KurtsHouse_Text_KurtGetStarted:
	.string "KURT: I'll get started right now!$"

KurtsHouse_Text_KurtMakingBallsMustWait:
	.string "Hm? Who are you?\p"
	.string "{PLAYER}, eh? You want me to make\n"
	.string "some BALLS?\p"
	.string "Sorry, but that'll have to wait.\p"
	.string "Do you know TEAM ROCKET?\n"
	.string "Ah, don't worry.\p"
	.string "I'll tell you anyhow.\p"
	.string "TEAM ROCKET's an evil gang that\n"
	.string "uses POKéMON for their dirty work.\p"
	.string "They're supposed to have disbanded\n"
	.string "three years ago.\p"
	.string "Anyway, they're at the WELL,\n"
	.string "cutting off SLOWPOKETAILS to sell!\p"
	.string "So I'm going to go give them a\n"
	.string "lesson in pain!\p"
	.string "Hang on, SLOWPOKE! Old KURT\n"
	.string "is on his way!$"

KurtsHouse_Text_KurtHonoredToMakeBalls:
	.string "KURT: Hi, {PLAYER}!\p"
	.string "You handled yourself like a\n"
	.string "real hero at the WELL.\p"
	.string "I like your style!\p"
	.string "I would be honored to make\n"
	.string "POKé BALLS for a TRAINER like you.\p"
	.string "This is all I have now, \n"
	.string "but take it.$"

KurtsHouse_Text_KurtBallsFromApricorns:
	.string "KURT: I make POKé BALLS from BERRIES.\p"
	.string "Collect them from trees and bring\n"
	.string "'em to me.\p"
	.string "I'll make POKé BALLS out of them.$"

KurtsHouse_Text_KurtAskYouHaveAnApricorn:
	.string "KURT: You have BERRIES for me?\p"
	.string "Fine! I'll turn them into POKé BALLS.$"

KurtsHouse_Text_KurtThatsALetdown:
	.string "KURT: I don't see any {STR_VAR_1}s!$"

KurtsHouse_Text_KurtJustFinishedYourBallPlural:
	.string "KURT: {PLAYER}!\n"
	.string "Your {STR_VAR_1}S are done. Here!$"

KurtsHouse_Text_KurtJustFinishedYourBallSingular:
	.string "KURT: {PLAYER}!\n"
	.string "Your {STR_VAR_1} is done. Here!$"

KurtsHouse_Text_KurtTurnedOutGreatPlural:
	.string "They turned out great.\n"
	.string "Try catching some POKéMON with 'em!$"

KurtsHouse_Text_KurtTurnedOutGreatSingular:
	.string "It turned out great.\n"
	.string "Try catching a POKéMON with it!$"

KurtsHouse_Text_ObtainedPlural:
	.string "{PLAYER} obtained\n"
	.string "{STR_VAR_2} {STR_VAR_1}S!$"

KurtsHouse_Text_ObtainedSingular:
	.string "{PLAYER} obtained\n"
	.string "the {STR_VAR_1}!$"

KurtsHouse_Text_KurtWhatIsThat:
	.string "Wh-what is that?\p"
	.string "I've never seen one before.\p"
	.string "It looks a like a POKé BALL, but\n"
	.string "it appears to be something else.\p"
	.string "Let me check it for you.$"

KurtsHouse_Text_KurtImCheckingItNow:
	.string "I'm checking it now.$"

KurtsHouse_Text_KurtAhHaISee:
	.string "Ah-ha! I see! So…$"

KurtsHouse_Text_KurtThisBallStartedToShake:
	.string "{PLAYER}!\p"
	.string "This BALL started to shake\n"
	.string "while I was checking it.\p"
	.string "There must be something to this!$"

KurtsHouse_Text_Kurt_Whatwasthat:
	.string "What was that sound?!\p"
	.string "Let's go outside to investigate!$"

KurtsHouse_Text_GranddaughterSlowpokeGone:
	.string "The SLOWPOKE are gone… \n"
	.string "Were they taken away by bad people?$"

KurtsHouse_Text_GranddaughterLonely:
	.string "Grandpa's gone… I'm so lonely…$"

KurtsHouse_Text_GranddaughterSlowpokeBack:
	.string "The SLOWPOKE my dad gave me came back!\p"
	.string "Its TAIL is growing back too!$"

KurtsHouse_Text_GranddaughterDad:
	.string "Dad works at SILPH where\n"
	.string "he studies POKé BALLS.\p"
	.string "I have to stay home\n"
	.string "with Grandpa and SLOWPOKE.$"

KurtsHouse_Text_GranddaughterHelp:
	.string "I get to help Grandpa now!\p"
	.string "We'll make good BALLS\n"
	.string "for you, so please wait!$"

KurtsHouse_Text_GranddaughterFun:
	.string "It's fun to make BALLS!$"

KurtsHouse_Text_GranddaughterSound:
	.string "Did that sound come from\n"
	.string "ILEX FOREST????$"

KurtsHouse_Text_Forest:
	.string "Did you check ILEX FOREST yet?\n"
	.string "It sounds very restless.$"

KurtsHouse_Text_Slowpoke:
	.string "SLOWPOKE: … Yawn?$"

KurtsHouse_Text_OakPhoto:
	.string "…A young PROF. OAK?$"

KurtsHouse_Text_CelebiStatue:
	.string "It's a statue of the forest's\n"
	.string "protector.$"
