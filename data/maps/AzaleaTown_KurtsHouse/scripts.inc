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
	multichoice 20, 0, MULTI_KURT_BALLS, FALSE
	switch VAR_RESULT
	case 0, AzaleaTown_KurtsHouse_EventScript_Kurt_Love
	case 1, AzaleaTown_KurtsHouse_EventScript_Kurt_Lure
	case 2, AzaleaTown_KurtsHouse_EventScript_Kurt_Friend
	case 3, AzaleaTown_KurtsHouse_EventScript_Kurt_Heavy
	case 4, AzaleaTown_KurtsHouse_EventScript_Kurt_Moon
	case 5, AzaleaTown_KurtsHouse_EventScript_Kurt_Fast
	case 6, AzaleaTown_KurtsHouse_EventScript_Kurt_Level
	case 7, AzaleaTown_KurtsHouse_EventScript_KurtCancel
	case MULTI_B_PRESSED, AzaleaTown_KurtsHouse_EventScript_KurtCancel
	closemessage

AzaleaTown_KurtsHouse_EventScript_Kurt_Love::
	closemessage
	bufferitemname STR_VAR_1, ITEM_PECHA_BERRY
	checkitem ITEM_PECHA_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
	closemessage
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_LOVE_BALL, 5
	removeitem ITEM_PECHA_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end
AzaleaTown_KurtsHouse_EventScript_Kurt_Lure::
	closemessage
	bufferitemname STR_VAR_1, ITEM_RAWST_BERRY
	checkitem ITEM_RAWST_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
	closemessage
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_LURE_BALL, 5
	removeitem ITEM_RAWST_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end
AzaleaTown_KurtsHouse_EventScript_Kurt_Friend::
	closemessage
	bufferitemname STR_VAR_1, ITEM_CHERI_BERRY
	checkitem ITEM_CHERI_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
	closemessage
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_FRIEND_BALL, 5
	removeitem ITEM_CHERI_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end
AzaleaTown_KurtsHouse_EventScript_Kurt_Heavy::
	closemessage
	bufferitemname STR_VAR_1, ITEM_ORAN_BERRY
	checkitem ITEM_ORAN_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
	closemessage
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_HEAVY_BALL, 5
	removeitem ITEM_ORAN_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end
AzaleaTown_KurtsHouse_EventScript_Kurt_Moon::
	closemessage
	bufferitemname STR_VAR_1, ITEM_CHESTO_BERRY
	checkitem ITEM_CHESTO_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
	closemessage
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_MOON_BALL, 5
	removeitem ITEM_CHESTO_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end
AzaleaTown_KurtsHouse_EventScript_Kurt_Fast::
	closemessage
	bufferitemname STR_VAR_1, ITEM_ASPEAR_BERRY
	checkitem ITEM_ASPEAR_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
	closemessage
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_FAST_BALL, 5
	removeitem ITEM_ASPEAR_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end
AzaleaTown_KurtsHouse_EventScript_Kurt_Level::
	closemessage
	bufferitemname STR_VAR_1, ITEM_PERSIM_BERRY
	checkitem ITEM_PERSIM_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_DontHaveBerry
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
	closemessage
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_LEVEL_BALL, 5
	removeitem ITEM_PERSIM_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
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
	.string "En fin, ¿te hago algunas BALLS?$"

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
	.string "KURT: ¡Empezaré ahora mismo!$"

KurtsHouse_Text_KurtMakingBallsMustWait:
	.string "¿Mmm? ¿Quién eres?\p"
	.string "{PLAYER}, ¿eh? ¿Quieres que haga\n"
	.string "unas BALLS?\p"
	.string "Lo siento, eso tendrá que esperar.\p"
	.string "¿Conoces al TEAM ROCKET?\n"
	.string "Ah, no te preocupes.\p"
	.string "Te lo contaré de todos modos.\p"
	.string "TEAM ROCKET es una banda malvada\n"
	.string "que usa POKéMON para sus fechorías.\p"
	.string "Se supone que se disolvieron\n"
	.string "hace tres años.\p"
	.string "En fin, ¡están en el POZO\n"
	.string "cortando COLAS DE SLOWPOKE!\p"
	.string "¡Así que iré a darles una\n"
	.string "lección de dolor!\p"
	.string "¡Aguanta, SLOWPOKE! ¡El viejo KURT\n"
	.string "ya va en camino!$"

KurtsHouse_Text_KurtHonoredToMakeBalls:
	.string "KURT: ¡Hola, {PLAYER}!\p"
	.string "Te portaste como un verdadero\n"
	.string "héroe en el POZO.\p"
	.string "¡Me gusta tu estilo!\p"
	.string "Sería un honor hacer BALLS\n"
	.string "para un ENTRENADOR como tú.\p"
	.string "Esto es todo lo que tengo,\n"
	.string "¡pero tómalo!$"

KurtsHouse_Text_KurtBallsFromApricorns:
	.string "KURT: Hago BALLS con BAYAS.\p"
	.string "Búscalas en los árboles y tráeme\n"
	.string "grupos de 5.\p"
	.string "Las convertiré en BALLS.$"

KurtsHouse_Text_KurtAskYouHaveAnApricorn:
	.string "KURT: ¿Tienes 5 BAYAS para mí?\p"
	.string "¡Bien! Las convertiré en BALLS.$"

KurtsHouse_Text_KurtThatsALetdown:
	.string "KURT: ¡No veo 5 {STR_VAR_1}!$"

KurtsHouse_Text_KurtJustFinishedYourBall:
	.string "KURT: ¡Ah, {PLAYER}!\p"
	.string "Acabo de terminar tu BALL. ¡Toma!$"

KurtsHouse_Text_KurtTurnedOutGreat:
	.string "KURT: Quedó genial.\p"
	.string "Intenta capturar POKéMON con ella.$"

KurtsHouse_Text_KurtWhatIsThat:
	.string "¿Qu-qué es esto?\p"
	.string "Nunca había visto una así.\p"
	.string "Parece una POKé BALL, pero\n"
	.string "parece ser algo distinto.\p"
	.string "Déjame revisarla.$"

KurtsHouse_Text_KurtImCheckingItNow:
	.string "La estoy revisando ahora.$"

KurtsHouse_Text_KurtAhHaISee:
	.string "¡Ajá! ¡Ya veo! Así que...$"

KurtsHouse_Text_KurtThisBallStartedToShake:
	.string "{PLAYER}!\p"
	.string "Esta BALL empezó a vibrar\n"
	.string "mientras la revisaba.\p"
	.string "¡Debe haber algo aquí!$"

KurtsHouse_Text_Kurt_Whatwasthat:
	.string "¡¿Qué fue ese sonido?!\p"
	.string "¡Vamos fuera a investigar!$"

KurtsHouse_Text_GranddaughterSlowpokeGone:
	.string "Los SLOWPOKE se fueron...\n"
	.string "¿Se los llevó gente mala?$"

KurtsHouse_Text_GranddaughterLonely:
	.string "El abuelo se fue... Me siento solo...$"

KurtsHouse_Text_GranddaughterSlowpokeBack:
	.string "¡Volvió el SLOWPOKE que me dio\p"
	.string "mi papá! ¡Su COLA también crece!$"

KurtsHouse_Text_GranddaughterDad:
	.string "Papá trabaja en SILPH donde\n"
	.string "estudia las POKé BALLS.\p"
	.string "Me quedo en casa con el\n"
	.string "abuelo y SLOWPOKE.$"

KurtsHouse_Text_GranddaughterHelp:
	.string "¡Ahora ayudo al abuelo!\p"
	.string "Haremos buenas BALLS\n"
	.string "para ti, ¡así que espera!$"

KurtsHouse_Text_GranddaughterFun:
	.string "¡Es divertido hacer BALLS!$"

KurtsHouse_Text_GranddaughterSound:
	.string "¿Ese sonido vino del\n"
	.string "BOSQUE VERDE????$"

KurtsHouse_Text_Forest:
	.string "¿Ya revisaste el BOSQUE VERDE?\n"
	.string "Se escucha muy inquieto.$"

KurtsHouse_Text_Slowpoke:
	.string "SLOWPOKE: … ¿Bostezo?$"

KurtsHouse_Text_OakPhoto:
	.string "… ¿Un PROF. OAK joven?$"

KurtsHouse_Text_CelebiStatue:
	.string "Es una estatua del protector\n"
	.string "del bosque.$"
