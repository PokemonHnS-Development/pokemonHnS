.set LOCALID_MART_EMPLOYEE, 2
.set LOCALID_FOOTPRINTS_MAN, 3
.set LOCALID_RIVAL, 4

OldaleTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_OnTransition
	.byte 0

OldaleTown_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	setflag FLAG_VISITED_VIOLET_CITY
	call_if_unset FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_BlockWestEntrance
	call_if_unset FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MoveMartEmployee
	call_if_set FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_SetOldaleState
	end

@ This script seems pointless because nothing uses VAR_GARBAGEVAR
OldaleTown_EventScript_SetOldaleState::
	setvar VAR_GARBAGEVAR, 1
	return

OldaleTown_EventScript_BlockWestEntrance::
	setobjectxyperm LOCALID_FOOTPRINTS_MAN, 1, 11
	setobjectmovementtype LOCALID_FOOTPRINTS_MAN, MOVEMENT_TYPE_FACE_LEFT
	return

OldaleTown_EventScript_MoveMartEmployee::
	setobjectxyperm LOCALID_MART_EMPLOYEE, 13, 14
	setobjectmovementtype LOCALID_MART_EMPLOYEE, MOVEMENT_TYPE_FACE_DOWN
	return

OldaleTown_EventScript_TownSign::
	msgbox OldaleTown_Text_TownSign, MSGBOX_SIGN
	end

OldaleTown_EventScript_Girl::
	msgbox OldaleTown_Text_SavingMyProgress, MSGBOX_NPC
	end

OldaleTown_EventScript_InfiniteItems1::
	faceplayer
	goto_if_set FLAG_INFINITE_STUFF, OldaleTown_EventScript_InfiniteItems5
	playbgm MUS_RG_FOLLOW_ME, FALSE
	msgbox OldaleTown_Text_InfiniteItems1, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, OldaleTown_EventScript_InfiniteItems2
	call_if_eq VAR_RESULT, NO, OldaleTown_EventScript_InfiniteItemsNo
	end

OldaleTown_EventScript_InfiniteItems2::
	msgbox OldaleTown_Text_InfiniteItems2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, OldaleTown_EventScript_InfiniteItems3
	call_if_eq VAR_RESULT, NO, OldaleTown_EventScript_InfiniteItemsNo
	end

OldaleTown_EventScript_InfiniteItems3::
	msgbox OldaleTown_Text_InfiniteItems3, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, OldaleTown_EventScript_InfiniteItems4
	call_if_eq VAR_RESULT, NO, OldaleTown_EventScript_InfiniteItemsNo
	end

OldaleTown_EventScript_InfiniteItems4::
	giveitem ITEM_INFINITE_REPEL
	giveitem ITEM_INFINITE_RARE_CANDIES
	msgbox OldaleTown_Text_InfiniteItems4, MSGBOX_NPC
	setflag FLAG_INFINITE_STUFF
	fadedefaultbgm
	end

OldaleTown_EventScript_InfiniteItems5::
	msgbox OldaleTown_Text_InfiniteItems4, MSGBOX_NPC
	end

OldaleTown_EventScript_InfiniteItemsNo::
	msgbox OldaleTown_Text_InfiniteItemsNo, MSGBOX_NPC
	fadedefaultbgm
	end

OldaleTown_EventScript_MartEmployee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_ExplainPotion
	goto_if_set FLAG_TEMP_1, OldaleTown_EventScript_ExplainPotion
	setflag FLAG_TEMP_1
	playbgm MUS_FOLLOW_ME, FALSE
	msgbox OldaleTown_Text_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, OldaleTown_EventScript_GoToMartSouth
	case DIR_NORTH, OldaleTown_EventScript_GoToMartNorth
	case DIR_EAST, OldaleTown_EventScript_GoToMartEast
	end

OldaleTown_EventScript_GoToMartSouth::
	applymovement LOCALID_MART_EMPLOYEE, OldaleTown_Movement_EmployeeSouth
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerSouth
	waitmovement 0
	goto OldaleTown_EventScript_ExplainPokemonMart
	end

OldaleTown_EventScript_GoToMartNorth::
	applymovement LOCALID_MART_EMPLOYEE, OldaleTown_Movement_EmployeeNorth
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerNorth
	waitmovement 0
	goto OldaleTown_EventScript_ExplainPokemonMart
	end

OldaleTown_EventScript_GoToMartEast::
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerEast
	applymovement LOCALID_MART_EMPLOYEE, OldaleTown_Movement_EmployeeEast
	waitmovement 0
	goto OldaleTown_EventScript_ExplainPokemonMart
	end

OldaleTown_EventScript_ExplainPokemonMart::
	msgbox OldaleTown_Text_ThisIsAPokemonMart, MSGBOX_DEFAULT
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, OldaleTown_EventScript_BagIsFull
	msgbox OldaleTown_Text_PotionExplanation, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_POTION_OLDALE
	fadedefaultbgm
	release
	end

OldaleTown_EventScript_ExplainPotion::
	msgbox OldaleTown_Text_PotionExplanation, MSGBOX_DEFAULT
	release
	end

OldaleTown_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	fadedefaultbgm
	release
	end

OldaleTown_Movement_EmployeeEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_EmployeeSouth:
	walk_left
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_EmployeeNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_Unknown1:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_PlayerEast:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_Movement_PlayerSouth:
	delay_16
	delay_16
	delay_16
	delay_16
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_Movement_PlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_Movement_Unknown2:
	walk_left
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_EventScript_FootprintsMan::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_NotBlockingPath
	msgbox OldaleTown_Text_DiscoveredFootprints, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

OldaleTown_EventScript_BlockedPath::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerStepBack
	applymovement LOCALID_FOOTPRINTS_MAN, OldaleTown_Movement_BackUp
	waitmovement 0
	msgbox OldaleTown_Text_WaitDontComeInHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, OldaleTown_Movement_ReturnToOriginalPosition
	waitmovement 0
	releaseall
	end

OldaleTown_EventScript_NotBlockingPath::
	msgbox OldaleTown_Text_FinishedSketchingFootprints, MSGBOX_DEFAULT
	release
	end

OldaleTown_EventScript_Rival::
	lockall
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_0x8009, 0
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger1::
	lockall
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger2::
	lockall
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_RivalTrigger3::
	lockall
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalApproachPlayer3
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto OldaleTown_EventScript_ShowRivalMessage
	end

OldaleTown_EventScript_ShowRivalMessage::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, OldaleTown_EventScript_ShowMayMessage
	goto_if_eq VAR_RESULT, FEMALE, OldaleTown_EventScript_ShowBrendanMessage
	end

OldaleTown_EventScript_ShowMayMessage::
	msgbox OldaleTown_Text_MayLetsGoBack, MSGBOX_DEFAULT
	goto OldaleTown_EventScript_RivalFinish
	end

OldaleTown_EventScript_ShowBrendanMessage::
	msgbox OldaleTown_Text_BrendanLetsGoBack, MSGBOX_DEFAULT
	goto OldaleTown_EventScript_RivalFinish
	end

OldaleTown_EventScript_RivalFinish::
	closemessage
	call_if_eq VAR_0x8009, 0, OldaleTown_EventScript_DoExitMovement1
	call_if_eq VAR_0x8009, 1, OldaleTown_EventScript_DoExitMovement2
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	removeobject LOCALID_RIVAL
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_GARBAGEFLAG
	releaseall
	end

OldaleTown_EventScript_DoExitMovement1::
	goto_if_ne VAR_FACING, DIR_SOUTH, OldaleTown_EventScript_DoExitMovement2
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	return

OldaleTown_EventScript_DoExitMovement2::
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_WatchRivalExit
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	return

OldaleTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	step_end

OldaleTown_Movement_RivalApproachPlayer2:
	walk_left
	step_end

OldaleTown_Movement_RivalApproachPlayer3:
	face_left
	step_end

OldaleTown_Movement_RivalExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OldaleTown_Movement_WatchRivalExit:
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_PlayerStepBack:
	delay_8
	walk_right
	step_end

OldaleTown_Movement_BackUp:
	walk_fast_up
	walk_in_place_faster_left
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

OldaleTown_Movement_ReturnToOriginalPosition:
	walk_down
	walk_left
	step_end

OldaleTown_Text_SavingMyProgress:
	.string "Quiero descansar, así que guardaré\n"
	.string "mi progreso.$"

OldaleTown_Text_IWorkAtPokemonMart:
	.string "¡Hola!\n"
	.string "Trabajo en un POKéMON MART.\p"
	.string "¿Me acompañas?$"

OldaleTown_Text_ThisIsAPokemonMart:
	.string "Este es un POKéMON MART.\n"
	.string "Busca nuestro techo azul.\p"
	.string "Vendemos varias cosas, como\n"
	.string "POKé BALLS para capturar POKéMON.\p"
	.string "Toma esto como un\n"
	.string "artículo promocional.$"

OldaleTown_Text_PotionExplanation:
	.string "Una POCIÓN sirve en cualquier momento,\n"
	.string "es más útil que un POKéMON CENTER\l"
	.string "en ciertas situaciones.$"

OldaleTown_Text_WaitDontComeInHere:
	.string "¡Aaaaah! ¡Espera!\n"
	.string "Por favor, no entres aquí.\p"
	.string "¡Hallé las huellas de un\n"
	.string "POKéMON raro!\p"
	.string "Espera a que termine de dibujarlas,\n"
	.string "¿está bien?$"

OldaleTown_Text_DiscoveredFootprints:
	.string "¡Hallé las huellas de un\n"
	.string "POKéMON raro!\p"
	.string "Espera a que termine de dibujarlas,\n"
	.string "¿está bien?$"

OldaleTown_Text_FinishedSketchingFootprints:
	.string "Terminé de dibujar las huellas de un\n"
	.string "POKéMON raro.\p"
	.string "Pero resultan que eran solo mis\n"
	.string "propias huellas…$"

OldaleTown_Text_MayLetsGoBack:
	.string "MAY: ¡{PLAYER}{KUN}!\n"
	.string "¡Por aquí!\l"
	.string "¡Démonos prisa en volver a casa!$"

OldaleTown_Text_BrendanLetsGoBack:
	.string "BRENDAN: Vuelvo al LAB de mi papá\n"
	.string "ahora.\l"
	.string "{PLAYER}, tú también date prisa.$"

OldaleTown_Text_TownSign:
	.string "PUEBLO PRIMAVERA\n"
	.string "“Donde todo comienza.”$"

OldaleTown_Text_InfiniteItems1:
	.string "¡Hola! Un tipo raro me dio cosas\n"
	.string "geniales. Son...\p"
	.string "¡Un REPELENTE INFINITO y una CAJA de\n"
	.string "CARAMELOS RAROS! ¿Genial, no?\p"
	.string "¿Te interesan?$"

OldaleTown_Text_InfiniteItems2:
	.string "Hmm... Usar estos objetos se\n"
	.string "considera hacer trampa...\p"
	.string "¿Seguro que los quieres?$"

OldaleTown_Text_InfiniteItems3:
	.string "¿De verdad los quieres?\n"
	.string "Solo quiero asegurarme...\p"
	.string "No podrás desecharlos.$"

OldaleTown_Text_InfiniteItems4:
	.string "¡Haz trampa bajo tu riesgo!$"

OldaleTown_Text_InfiniteItemsNo:
	.string "¡Está bien!$"
