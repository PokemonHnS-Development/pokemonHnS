.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_OnResume:
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition:
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2
	tower_loadpartners
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MR_FUJI
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_MR_FUJI
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_MR_FUJI
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_MR_FUJI
	setvar VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_MR_FUJI
	setvar VAR_OBJ_GFX_ID_5, OBJ_EVENT_GFX_MR_FUJI
	setvar VAR_OBJ_GFX_ID_6, OBJ_EVENT_GFX_MR_FUJI
	setvar VAR_OBJ_GFX_ID_7, OBJ_EVENT_GFX_MR_FUJI
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_3, 1
	setobjectxyperm LOCALID_ATTENDANT, 10, 2
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp:
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom::
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom
	waitmovement 0
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit
	waitmovement 0
	copyobjectxytoperm LOCALID_ATTENDANT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom:
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit:
	walk_left
	walk_in_place_faster_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant::
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator::
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
	waitstate
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorEast:
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorWest:
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator:
	walk_up
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast:
	walk_right
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest:
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1::
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner::
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_INTRO
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON1
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON2_ASK
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	call_if_ne VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner::
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2::
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3::
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4::
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5::
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6::
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7::
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8::
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner:
	.string "Busca un compañero entre los\n"
	.string "ENTRENADORES reunidos aquí.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner:
	.string "{PLAYER}, no has hallado un compañero\n"
	.string "para tu equipo doble.\p"
	.string "¿Quieres dejar de buscar y volver\n"
	.string "al mostrador de recepción?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2:
	.string "Entonces, busca un compañero entre\n"
	.string "los ENTRENADORES reunidos aquí.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner::
	.string "Gracias por elegir compañero.\p"
	.string "Ahora te llevaré a tu\n"
	.string "SALA DE BATALLA DOBLE.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro::
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.\n"
	.string "¡Puedes llamarme {STR_VAR_3}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1::
	.string "Por consejo de {STR_VAR_1}, traje\n"
	.string "un {STR_VAR_3} con {STR_VAR_2} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Por favor, ¡seamos un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept::
	.string "¡Gracias!\n"
	.string "Iré a registrarme ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject::
	.string "De verdad quería formar un equipo\n"
	.string "contigo, {PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro::
	.string "Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}.\n"
	.string "Mi nombre es {STR_VAR_3}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1::
	.string "Seguí el consejo de {STR_VAR_1} y\n"
	.string "elegí un {STR_VAR_3} con {STR_VAR_2} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¡Por favor, seamos equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept::
	.string "¡Muchas gracias!\n"
	.string "¡Terminaré el registro rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject::
	.string "{PLAYER}, esperaba que pudiera\n"
	.string "ser tu compañero…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro::
	.string "Eh, soy {STR_VAR_3}, el aprendiz\n"
	.string "nro. {STR_VAR_2} de {STR_VAR_1}.\p"
	.string "Snif…\p"
	.string "¡Lo siento!\n"
	.string "¡Los nervios me hacen llorar!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1::
	.string "{STR_VAR_3} me aconsejó, así que tengo\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Snif...\n"
	.string "¡Por favor, haz equipo conmigo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept::
	.string "¿Ah, sí? ¿Lo harás?\n"
	.string "¡Genial! ¡Súper! ¡Awoooh!\p"
	.string "Oh... lo siento...\n"
	.string "Estoy tan feliz que lloro...\p"
	.string "Iré a registrarme ahora mismo.\n"
	.string "¡Por favor, no te vayas!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject::
	.string "Oh, p-pero...\n"
	.string "¡Buaaa... waaaaah!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro::
	.string "¡Hola! ¡Soy {STR_VAR_3}!\n"
	.string "¡Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1::
	.string "{STR_VAR_3} recomendó mi equipo.\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1},\n"
	.string "¡eso es lo que tengo! ¿Genial, no?\p"
	.string "¡Así que vamos!\n"
	.string "¡Hagamos un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept::
	.string "¡Siií! ¡Genial!\n"
	.string "Bien, iré a registrarme, ¿sí?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject::
	.string "Ay, ¿por qué?\n"
	.string "¡Quería hacer equipo, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro::
	.string "Soy {STR_VAR_3}, el aprendiz no. {STR_VAR_2}\n"
	.string "¡del famoso {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1::
	.string "Le pedí consejo a {STR_VAR_3}.\n"
	.string "Un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1},\n"
	.string "ese es mi par.\p"
	.string "¿Te unirías a mí en\n"
	.string "un combate doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept::
	.string "¡Gracias!\n"
	.string "¡Me registraré ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject::
	.string "{PLAYER}, esperaba que nos uniéramos\n"
	.string "en un combate doble…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro::
	.string "Eh… me alegra mucho que te\n"
	.string "tomes el tiempo de hablarme.\p"
	.string "Soy {STR_VAR_3}.\n"
	.string "Soy el aprendiz n. {STR_VAR_2} de {STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1::
	.string "{STR_VAR_3} me dio un consejo.\n"
	.string "Estoy muy agradecido.\p"
	.string "Tengo un equipo de un {STR_VAR_2}\n"
	.string "con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n"
	.string "Sé que pido mucho…\p"
	.string "No creo que quieras, pero\n"
	.string "¿puedo ser tu compañero?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept::
	.string "¿En serio? ¡No lo puedo creer!\n"
	.string "¡No creo que me dejes acompañarte!\l"
	.string "Yo... ¡no te fallaré!\p"
	.string "Eh... si está bien, ¡iré a registrarme\n"
	.string "ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject::
	.string "Oh...\n"
	.string "No creí que fuera lo bastante bueno...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro::
	.string "Hola, soy {STR_VAR_3}.\n"
	.string "¡Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1::
	.string "{STR_VAR_3} me dijo que sería\n"
	.string "bueno armar este equipo:\l"
	.string "un {STR_VAR_2} que use {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask::
	.string "y un {STR_VAR_2} que sepa\n"
	.string "usar {STR_VAR_1}.\p"
	.string "Nada mal, ¿eh?\n"
	.string "¿Quieres que me una a ti?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept::
	.string "¡Bien, feliz de acompañarte!\n"
	.string "¡Espero que no me metas en líos!\l"
	.string "Iré a registrarme ahora.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject::
	.string "¿Eh? ¿Por qué me rechazaste?\n"
	.string "¡No sabes juzgar a la gente!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro::
	.string "Soy {STR_VAR_3} y soy TRIATLETA.\n"
	.string "Entre correr, entrenar y rapear,\l"
	.string "no paro nunca.\p"
	.string "Además soy aprendiz de {STR_VAR_1}\n"
	.string "n.º {STR_VAR_2}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1::
	.string "Esto es lo que {STR_VAR_3} sugirió.\n"
	.string "Un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask::
	.string "y un {STR_VAR_1}\n"
	.string "{STR_VAR_2}.\p"
	.string "Me esforcé mucho en criarlos\n"
	.string "aunque estoy muy ocupado.\p"
	.string "¡Hagamos un equipo doble\n"
	.string "y probemos suerte!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept::
	.string "¡Gracias, ese es el espíritu!\n"
	.string "Espera mientras me registro, ¿sí?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject::
	.string "¡Saqué tiempo de mi agenda\n"
	.string "para estar aquí! ¡Ten piedad!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro::
	.string "¡Hola!\n"
	.string "¿Cómo te va?\p"
	.string "Soy {STR_VAR_3}, el aprendiz de {STR_VAR_1}\n"
	.string "n.º {STR_VAR_2}. ¡Mucho gusto!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1::
	.string "¡Oye, escucha! Debes saber de los\n"
	.string "POKéMON que {STR_VAR_3} sugirió.\l"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n"
	.string "¡Claro que los crié súper bien!\p"
	.string "¿Quieres hacer equipo?\n"
	.string "¡Será una gran combinación!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept::
	.string "¡Súper, creo que será divertido!\n"
	.string "¡Iré a registrarme!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject::
	.string "¡Oh, qué malo eres!\n"
	.string "Vengo recomendado, ¿sabes?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro::
	.string "Permíteme presentarme.\n"
	.string "Soy {STR_VAR_3}.\p"
	.string "Sirvo como aprendiz de {STR_VAR_1}\n"
	.string "n.º {STR_VAR_2}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1::
	.string "Busqué el consejo de\n"
	.string "{STR_VAR_3} y entrené a mi equipo\l"
	.string "de un {STR_VAR_2} con {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¡Acepta luchar en pareja conmigo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept::
	.string "¡Oh... estoy encantado!\n"
	.string "¡Prometo dar lo mejor de mí!\p"
	.string "¡Claro que nos registraré!\n"
	.string "¡Espera un momento!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject::
	.string "Esperaba poder unirme a ti,\n"
	.string "{PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro::
	.string "¡Ay! ¡Me hablaste!\n"
	.string "Yo... ¡estoy contentísimo!\p"
	.string "¡Soy {STR_VAR_3}! Soy el aprendiz de {STR_VAR_1}\n"
	.string "n.º {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1::
	.string "Por consejo de {STR_VAR_3}, entrené\n"
	.string "un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask::
	.string "y un {STR_VAR_1}-usuario\n"
	.string "{STR_VAR_2}.\p"
	.string "¿Puedes concederme mi deseo?\n"
	.string "¡Quiero ser tu compañero de equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept::
	.string "¡Ay! ¡Me siento mareada!\n"
	.string "¡Muchas gracias!\l"
	.string "¡Iré a registrarnos ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject::
	.string "¡Waaah! ¿No tienes piedad?\n"
	.string "Pero eso te hace más genial...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro::
	.string "¡Yupi! Soy el aprendiz de {STR_VAR_1}\n"
	.string "n.º {STR_VAR_2}!\p"
	.string "¡Me llamo {STR_VAR_3}, hola, hola!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1::
	.string "Mi mentor {STR_VAR_3} recomendó\n"
	.string "al maestro {STR_VAR_2} de {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask::
	.string "y al maestro de {STR_VAR_1}\n"
	.string "{STR_VAR_2}.\p"
	.string "Es genial, ¿verdad?\n"
	.string "Serás mi pareja, ¿cierto?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept::
	.string "¡Bien, excelente!\n"
	.string "¡Haré el registro rápidamente!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject::
	.string "¡Gwaaah!\n"
	.string "¡Eres muy calculador, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro::
	.string "¡Oye! ¡Hay problemas! ¡Es el último\n"
	.string "día de la BATTLE TOWER!\p"
	.string "… … … … … …\n"
	.string "¡Es broma!\p"
	.string "¡Me llaman {STR_VAR_3} y yo también!\n"
	.string "¡Soy el aprendiz 1000 de {STR_VAR_1}!\l"
	.string "¡En realidad, soy el n. {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1::
	.string "{STR_VAR_3} me dio un consejo.\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask::
	.string "{STR_VAR_2} con {STR_VAR_1}.\n"
	.string "¡Tengo diez de cada tipo!\l"
	.string "¡Bueno, solo uno de cada uno!\p"
	.string "¿Qué te parece?\n"
	.string "¿Quieres batallas dobles conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept::
	.string "¡Yupi!\n"
	.string "¡Te daré un POKéMON en agradecimiento!\p"
	.string "¡Broma! Pero iré a hacer\n"
	.string "el registro, ¿está bien?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject::
	.string "¡Qué frío! ¡Por eso tendré que\n"
	.string "destruir la BATTLE TOWER!\p"
	.string "¡Claro que no lo haré!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro::
	.string "¡Hola! ¡Llego con todo el ritmo!\n"
	.string "¡A los POKéMON yo los domino!\p"
	.string "Soy {STR_VAR_3}, el MARINERO rapero.\n"
	.string "¡No me confundas con un ballenero!\p"
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.\n"
	.string "¡No me subestimes tan rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1::
	.string "Seguí el consejo de {STR_VAR_3}\n"
	.string "y armé mi equipo con orgullo!\l"
	.string "Un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask::
	.string "y un {STR_VAR_1}-usuario\n"
	.string "{STR_VAR_2}!\p"
	.string "Debemos conmemorar nuestro encuentro\n"
	.string "¡con una victoria en pareja!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept::
	.string "¡Oye, me gusta tu estilo!\n"
	.string "¡Iré a hacer el registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject::
	.string "¡Oh, {PLAYER}, eso fue frío!\n"
	.string "¡Si me permites ser sincero!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro::
	.string "¡Yippee-yahoo!\n"
	.string "¡No huyas! ¡Solo me divertía!\p"
	.string "¡Hola! ¡Soy {STR_VAR_3}!\n"
	.string "¡Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1::
	.string "{STR_VAR_3} me dijo qué hacer.\n"
	.string "Así que un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask::
	.string "y un {STR_VAR_1}-usuario\n"
	.string "{STR_VAR_2}, yo elegí.\p"
	.string "Entonces, ¿qué dices?\n"
	.string "¡Vamos, dame el gusto!\p"
	.string "¡Por favor, te lo ruego!\n"
	.string "¡Déjame ir, no me ignores!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept::
	.string "¡Siií! ¡La suerte está conmigo!\n"
	.string "¡Eso me hace muy feliz!\p"
	.string "Antes de ir a la batalla,\n"
	.string "¡iré a registrarme ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject::
	.string "¿Me estás rechazando?\n"
	.string "{PLAYER}, ¡me pones triste!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro::
	.string "¡Cof!\p"
	.string "Ay, perdón, estoy resfriado.\n"
	.string "Pero mis POKéMON están bien.\p"
	.string "Me llamo {STR_VAR_3}, el aprendiz de {STR_VAR_1}\n"
	.string "n.º {STR_VAR_2}. ¡Cof!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1::
	.string "Seguí el consejo de {STR_VAR_3}\n"
	.string "y armé mi equipo con\l"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Los entrené cada día,\n"
	.string "bajo el viento y la lluvia.\p"
	.string "Por eso tengo este resfriado,\n"
	.string "creo yo.\p"
	.string "Eso es lo que soy.\n"
	.string "¿Quieres ser mi pareja?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept::
	.string "¡Gracias, te lo agradezco!\n"
	.string "¡Cof, cof!\l"
	.string "Espera mientras me registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject::
	.string "¿Ah, no quieres?\n"
	.string "{PLAYER}, creo que haríamos buen par.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro::
	.string "¡Oh, hola!\n"
	.string "Esto pone nervioso.\p"
	.string "Soy {STR_VAR_3}.\n"
	.string "Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1::
	.string "{STR_VAR_3} dijo que este equipo es bueno--\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Me da algo de pena,\n"
	.string "¿pero me dejarías unirme a ti?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept::
	.string "¡Vaya, muchas gracias!\n"
	.string "¡Me da timidez, pero daré lo mejor!\p"
	.string "Iré a hacer el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject::
	.string "¡Oh, por favor, no digas que no!\n"
	.string "Ya me siento bastante nerviosa…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro::
	.string "Soy {STR_VAR_3}, y no miento.\n"
	.string "Soy la aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1::
	.string "{STR_VAR_3} recomendó mi equipo.\p"
	.string "Como el consejo parecía sincero,\n"
	.string "decidí traer conmigo\l"
	.string "mi {STR_VAR_2} de {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask::
	.string "mi {STR_VAR_2} de {STR_VAR_1}.\p"
	.string "Si es posible, me gustaría que me\n"
	.string "aceptaras como tu pareja de combate.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept::
	.string "¿De verdad me aceptarás?\n"
	.string "De lo contrario sería terrible.\p"
	.string "Ya que aceptaste, todo está bien.\n"
	.string "Iré a registrarnos a los dos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject::
	.string "¿Hm? ¿Por qué me rechazarías?\n"
	.string "¿Crees que esto es una broma?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro::
	.string "¡Soy {STR_VAR_1} y soy una CHICA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1::
	.string "Tengo un {STR_VAR_2}\n"
	.string "que usa {STR_VAR_1} y otro$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask::
	.string "{STR_VAR_2} que usa {STR_VAR_1}.\n"
	.string "Eso es lo que traigo conmigo.\p"
	.string "¿Quieres ser mi pareja?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept::
	.string "¡Gracias!\n"
	.string "¡Iré a hacer el registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject::
	.string "¿No quieres ser mi pareja?\n"
	.string "¡Te arrepentirás después!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro::
	.string "¡Hola!\p"
	.string "¡Soy el JOVEN {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1::
	.string "¿Quieres saber qué tengo?\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Serás mi pareja de equipo,\n"
	.string "¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept::
	.string "¡Súper!\n"
	.string "Iré a registrarme, ¿está bien?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject::
	.string "¡Ay! ¡Si formaras un equipo con\n"
	.string "mis POKéMON, seríamos invencibles!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro::
	.string "¡Yahoo!\n"
	.string "¡Soy el EXCURSIONISTA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1::
	.string "¿Sabes qué traigo conmigo?\n"
	.string "Mi {STR_VAR_2} de {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask::
	.string "¡mi {STR_VAR_2} de {STR_VAR_1}!\p"
	.string "Suena bien, ¿no?\n"
	.string "¿Hacemos un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept::
	.string "¡Yahoo!\n"
	.string "Iré a hacer el registro entonces.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject::
	.string "Me hubiera gustado luchar\n"
	.string "contigo a mi lado.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1}, y soy una BEAUTY!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1::
	.string "¿Sabes qué he estado criando?\n"
	.string "Un {STR_VAR_2} de {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask::
	.string "¡un {STR_VAR_2} de {STR_VAR_1}!\p"
	.string "¿Qué te parece?\n"
	.string "¿Hacemos un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept::
	.string "¡Maravilloso!\n"
	.string "¡Haré el registro ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject::
	.string "¡Qué decepción!\p"
	.string "Juntos habríamos sido\n"
	.string "¡los mejores!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro::
	.string "¡Hola!\p"
	.string "¿Sabes quién soy?\n"
	.string "¡Soy {STR_VAR_1}, el PESCADOR!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1::
	.string "Tengo un equipo de un\n"
	.string "{STR_VAR_2} de tipo {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask::
	.string "un {STR_VAR_2} de tipo {STR_VAR_1}.\p"
	.string "¿Y bien?\n"
	.string "¿Lucharás a mi lado?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept::
	.string "¡Bien, bien!\n"
	.string "¡Déjamelo a mí!\p"
	.string "Iré a registrarnos ahora.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject::
	.string "Encajábamos perfectamente...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro::
	.string "Gusto en conocerte.\n"
	.string "Soy {STR_VAR_1}, una DAMA.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1::
	.string "Me acompaña un equipo de\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Espero que me aceptes.\n"
	.string "Quiero que seas mi compañero.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept::
	.string "Te lo agradezco sinceramente.\n"
	.string "Yo me encargo del registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject::
	.string "Seguro que te arrepentirás de no\n"
	.string "tenerme como tu compañero.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro::
	.string "¡Soy el TRIATLETA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1::
	.string "Lo que tengo...\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\n"
	.string "¡Esa es mi pareja!\p"
	.string "¿Por favor?\n"
	.string "¿Haces equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept::
	.string "¡Vaya, gracias!\n"
	.string "Iré a registrarme al mostrador.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject::
	.string "¡Juntos habríamos sido\n"
	.string "muy fuertes, seguro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro::
	.string "¡Hola!\n"
	.string "¡Soy el CAZABICHOS {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1::
	.string "¡Mira lo que tengo!\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¡Oye, escucha!\n"
	.string "¿Quieres hacer equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept::
	.string "¡Genial!\p"
	.string "Iré a hacer el registro\n"
	.string "en el mostrador.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject::
	.string "Mis POKéMON son increíbles.\n"
	.string "¡Espero que no te arrepientas!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro::
	.string "¡Buen día!\n"
	.string "¡Soy el ESTUDIANTE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1::
	.string "He estado criando un\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask::
	.string "y un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "No está mal, ¿no crees?\n"
	.string "¿Quieres formar un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept::
	.string "¡Muchas gracias!\n"
	.string "Terminaré con el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject::
	.string "Qué mal...\p"
	.string "Esperaba aprender de ti\n"
	.string "siendo tu compañero...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro::
	.string "¡Hola! ¡Déjame decirte quién soy!\n"
	.string "¡Soy el RICO {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1::
	.string "¡Adivina qué tengo!\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Te doy la oportunidad de estar\n"
	.string "en un equipo doble conmigo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept::
	.string "¡Buena decisión!\p"
	.string "¡Terminaré el proceso de registro\n"
	.string "rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject::
	.string "¿Me rechazas a mí?\n"
	.string "¡Seguro lamentarás tu decisión!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro::
	.string "¡Hiyah!\n"
	.string "Soy el CINTURÓN NEGRO {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1::
	.string "Como mis compañeros, tengo\n"
	.string "un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask::
	.string "y un {STR_VAR_2} usando\n"
	.string "{STR_VAR_1}.\p"
	.string "¡Por favor, cumple mi deseo!\n"
	.string "¡Deja que sea tu compañero!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept::
	.string "¡Hiyah!\n"
	.string "¡Iré a registrarme ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject::
	.string "Ya veo... Espero tener una\n"
	.string "oportunidad la próxima vez...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1} y soy un TUBER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1::
	.string "Te diré lo que tengo.\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\n"
	.string "¿Puedo estar en tu equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept::
	.string "¡Gracias!\n"
	.string "¡Iré a registrarnos ahora!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject::
	.string "¡Si hubiéramos sido compañeros,\n"
	.string "seríamos muy fuertes!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro::
	.string "Saludos...\n"
	.string "Soy la HEX MANIAC {STR_VAR_1}...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1::
	.string "Llevo conmigo un {STR_VAR_1}\n"
	.string "{STR_VAR_2} junto con uno$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask::
	.string "{STR_VAR_2} que usa {STR_VAR_1}...\p"
	.string "Te lo ruego...\n"
	.string "¡Sé mi pareja de combate!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept::
	.string "Te lo agradezco...\n"
	.string "Nos registraré...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject::
	.string "Tanto deseaba unirme a ti...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro::
	.string "¿Cómo estás? Soy {STR_VAR_1},\n"
	.string "¡y soy CRIADORA POKéMON!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1::
	.string "¡Crío un par de muy buenos!\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Qué dices?\n"
	.string "¿Quieres ser mi pareja de equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept::
	.string "¡Muchas gracias!\p"
	.string "Iré a encargarme del registro\n"
	.string "ahora, ¡espera aquí mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject::
	.string "Tenía muchas ganas de ser\n"
	.string "tu compañero…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro::
	.string "¡Hola, qué tal!\n"
	.string "¡Soy el TRIATLETA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1::
	.string "¿Quieres ver con qué corro?\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Y bien?\n"
	.string "¿Quieres ser mi pareja de equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept::
	.string "¡Genial!\p"
	.string "¡Iré rápido a dejar el registro\n"
	.string "listo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject::
	.string "Tú y yo habríamos sido los mejores.\n"
	.string "Es una lástima…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro::
	.string "¡Hola! ¡Mi nombre es {STR_VAR_1}!\n"
	.string "¡Soy TRIATLETA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1::
	.string "Corro con mi equipo resistente--\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Nada mal, ¿eh?\n"
	.string "¡Deberíamos ser un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept::
	.string "¡Muy bien!\n"
	.string "¡Iré a registrarme enseguida!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject::
	.string "De verdad quería luchar como tu\n"
	.string "compañero de equipo doble…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro::
	.string "¡Soy la CHICA BATALLA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1::
	.string "He estado entrenando a un\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask::
	.string "¡un {STR_VAR_2} que usa {STR_VAR_1}!\p"
	.string "¿Te gusta ese combo?\n"
	.string "¿Y si nos unimos nosotros?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept::
	.string "¡Vaya, gracias!\p"
	.string "¡Haré el registro\n"
	.string "ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject::
	.string "Pensé que contigo podríamos formar\n"
	.string "el mejor equipo doble…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro::
	.string "¡Soy el TRIATLETA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1::
	.string "Corro con un {STR_VAR_2}\n"
	.string "que sabe usar {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask::
	.string "¡y un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Podríamos ser un equipo doble.\n"
	.string "¿No sería genial?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept::
	.string "¡Gracias!\p"
	.string "¡Iré a registrarnos\n"
	.string "ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject::
	.string "Qué mal. ¡Habríamos sido el equipo\n"
	.string "doble más fuerte de todos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro::
	.string "¿Yo?\n"
	.string "¡Soy TUBER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1::
	.string "¿Qué traigo conmigo?\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Oye?\n"
	.string "Te unirás a mi equipo, ¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept::
	.string "¡Bien!\p"
	.string "¡Iré a registrarme!\n"
	.string "¡Seamos excelentes juntos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject::
	.string "Mis POKéMON son fuertes...\n"
	.string "Lástima que no quieras unirte.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro::
	.string "¡Siii!\n"
	.string "¡Llámame GUITARISTA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1::
	.string "¡Mira mi séquito!\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¡Yei-hey! Muy salvaje, ¿no?\n"
	.string "¡Haremos un dúo en equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept::
	.string "¡Siii! ¡Exacto!\n"
	.string "¡Haré el registro ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject::
	.string "¡Mis POKéMON son fuertes!\n"
	.string "¡Te arrepentirás, ya verás!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro::
	.string "Mucho gusto.\n"
	.string "Soy {STR_VAR_1}, un CABALLERO.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1::
	.string "Me acompaña mi fiel\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask::
	.string "otro {STR_VAR_2} que usa {STR_VAR_1}.\p"
	.string "¿Te gustaría ser mi pareja en un\n"
	.string "combate doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept::
	.string "Ah, gracias por tu confianza.\n"
	.string "Terminaré con el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject::
	.string "Eso es muy lamentable...\p"
	.string "Esperaré con ansias la próxima\n"
	.string "oportunidad...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro::
	.string "Hola, soy {STR_VAR_1},\n"
	.string "¡y soy un POKéFAN!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1::
	.string "Tengo conmigo un {STR_VAR_2}\n"
	.string "que sabe {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te gusta lo que ves?\n"
	.string "¿Quieres ser mi pareja?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept::
	.string "¡Gracias!\n"
	.string "¡Yo me encargo del registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject::
	.string "Mis POKéMON son de primer nivel…\n"
	.string "Lástima que no lo aprecies.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro::
	.string "¡Hm!\n"
	.string "¡Soy {STR_VAR_1} y soy un EXPERTO!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1::
	.string "Los POKéMON que he entrenado son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Hacemos equipo juntos?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept::
	.string "¡Hm!\n"
	.string "¡Nos registraré ahora mismo!\l"
	.string "¡Demos lo mejor de nosotros!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject::
	.string "Espero que tu elección sea\n"
	.string "realmente la correcta…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro::
	.string "Hola, hola.\n"
	.string "Soy {STR_VAR_1}, ¡soy un EXPERTO!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1::
	.string "He criado bien a mis POKéMON.\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}--\n"
	.string "eso es lo que tengo.\p"
	.string "¿Quieres formar equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept::
	.string "Bien, bien.\n"
	.string "Haré el registro ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject::
	.string "Tal vez podamos formar equipo la\n"
	.string "próxima vez que nos veamos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro::
	.string "¡Soy el DOMADOR DRAGÓN {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1::
	.string "El equipo que he fortalecido es\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Qué te parece?\n"
	.string "¿Quieres ser mi pareja?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept::
	.string "¡Está bien, daré lo mejor de mí!\n"
	.string "Iré a registrarme ahora, ¿sí?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject::
	.string "¡No hallarás muchos compañeros\n"
	.string "más fuertes que yo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro::
	.string "¡Soy el CRIADOR {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1::
	.string "¿Qué POKéMON tengo?\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿No crees que seríamos un buen\n"
	.string "equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept::
	.string "¡Genial, gracias!\n"
	.string "¡Yo me encargo del registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject::
	.string "Mis POKéMON y yo somos fuertes.\n"
	.string "Qué decepción.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro::
	.string "¡Soy NINJA BOY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1::
	.string "Mi equipo POKéMON tiene un\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¡Hagamos un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept::
	.string "¡Súper!\n"
	.string "¡Iré a registrarme!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject::
	.string "¡Te arrepentirás de no tener a mis\n"
	.string "fuertes POKéMON de tu lado!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro::
	.string "¡Hola!\n"
	.string "¡Soy la SEÑORA SOMBRILLA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1::
	.string "Me acompañan mis {STR_VAR_2}\n"
	.string "que usan {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask::
	.string "un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "¿No son lindos?\n"
	.string "¿Quieres unirte a nuestro equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept::
	.string "¡Muchas gracias!\p"
	.string "Iré a registrarme al mostrador.\n"
	.string "¡No nos decepcionemos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject::
	.string "Mis POKéMON son muy fuertes.\n"
	.string "Qué decepción...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro::
	.string "Hola.\n"
	.string "¡Soy {STR_VAR_1}, un FANÁTICO DE LOS BICHO!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1::
	.string "Hallé mis POKéMON, sí.\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}--\n"
	.string "eso fue lo que hallé.\p"
	.string "¿Te interesa formar\n"
	.string "un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept::
	.string "¡Está bien!\n"
	.string "¡Entendido!\p"
	.string "¡No tardaré en registrarme!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject::
	.string "Con los POKéMON que hallé, no\n"
	.string "habríamos perdido...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro::
	.string "¡Ahoy, ahí!\n"
	.string "¡Soy el MARINERO {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1::
	.string "¡Mira mi mayor orgullo!\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Claro que no me rechazarás.\n"
	.string "Haremos equipo, ¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept::
	.string "¡No esperaba menos!\n"
	.string "Iré a registrarme ahora.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject::
	.string "¡Habríamos arrasado con\n"
	.string "todos! ¡Qué lástima!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro::
	.string "Hola, soy {STR_VAR_1}.\n"
	.string "Soy COLECCIONISTA.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1::
	.string "Las joyas de mi colección son\n"
	.string "mi {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Genial, ¿no?\n"
	.string "Deberíamos hacer equipo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept::
	.string "¡Eso es!\p"
	.string "No perdamos más tiempo.\n"
	.string "Registraré a los dos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject::
	.string "Vaya, eso es molesto.\n"
	.string "No aprecias mis POKéMON.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro::
	.string "Hola, soy {STR_VAR_1}.\n"
	.string "¡Soy un POKéMON RANGER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1::
	.string "Me acompañan un\n"
	.string "{STR_VAR_1} que usa {STR_VAR_2} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿No crees que seríamos un equipo\n"
	.string "impresionante?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept::
	.string "¡Eso es genial!\n"
	.string "Haré el registro ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject::
	.string "La próxima vez, elige mis POKéMON,\n"
	.string "¿está bien?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro::
	.string "Mi nombre es {STR_VAR_1}.\n"
	.string "¡Soy un POKéMON RANGER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1::
	.string "Te hablaré de mi equipo. Tengo\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Quieres formar un equipo doble\n"
	.string "con mi pequeño grupo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept::
	.string "¡Estaremos en nuestra mejor forma!\n"
	.string "¡Haré el registro rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject::
	.string "Espero que elijas a mi POKéMON\n"
	.string "la próxima vez.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro::
	.string "Gusto en conocerte. Soy {STR_VAR_1}.\n"
	.string "Me considero una AROMA LADY.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1::
	.string "Viajo con un {STR_VAR_2}\n"
	.string "que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask::
	.string "un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "Espero que te gusten.\n"
	.string "¿Quieres ser mi pareja?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept::
	.string "Me honra que aceptes.\n"
	.string "Iré a registrarme ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject::
	.string "Sería maravilloso formar un equipo\n"
	.string "doble la próxima vez que nos veamos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro::
	.string "¿Quieres saber quién soy?\n"
	.string "¡Soy {STR_VAR_1}, el MANÍACO RUINAS!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1::
	.string "Los POKéMON que traigo conmigo son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Intrigante, ¿eh?\n"
	.string "¿Qué tal si somos pareja?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept::
	.string "¡Es una decisión acertada!\n"
	.string "Iré a hacer el papeleo del registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject::
	.string "Hmm...\n"
	.string "Creo que mis POKéMON son fuertes...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro::
	.string "¡Soy el COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1::
	.string "Los POKéMON que tengo ahora son un\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n"
	.string "Genial, ¿no?\p"
	.string "¿No crees que sería genial\n"
	.string "si formáramos un equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept::
	.string "¡Genial!\n"
	.string "¡Me registraré en un abrir y cerrar!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject::
	.string "Pensé que formaríamos el mejor\n"
	.string "equipo de todos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro::
	.string "¡Soy COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1::
	.string "Mi equipo tiene un\n"
	.string "{STR_VAR_2} con {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te parece bien?\n"
	.string "¿Quieres ser mi pareja de combate?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept::
	.string "¡Me parece perfecto!\n"
	.string "Mejor voy a registrarme.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject::
	.string "Pensaba que seríamos un equipo\n"
	.string "muy fuerte…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1}, el POKéMANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1::
	.string "¿Qué tiene alguien como yo?\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1},\n"
	.string "¡eso es todo!\p"
	.string "¡Hagámoslo!\n"
	.string "¡Lucharemos como equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept::
	.string "¡Buena idea!\n"
	.string "¡Nos registraré a los dos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject::
	.string "¡Mis POKéMON son brutales!\n"
	.string "¡No es mi culpa si te arrepientes!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro::
	.string "¡Hola, tú!\n"
	.string "¡Soy KINDLER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1::
	.string "¿Sabes qué logré entrenar?\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Bueno, ¿qué dices?\n"
	.string "¿Quieres formar un equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept::
	.string "¡Muy bien!\n"
	.string "Procederé con el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject::
	.string "Promete que seremos pareja\n"
	.string "la próxima vez que nos veamos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro::
	.string "¡Soy {STR_VAR_1} y soy CAMPISTA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1::
	.string "He criado un {STR_VAR_1}\n"
	.string "usando {STR_VAR_2} y uno$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask::
	.string "{STR_VAR_1} con {STR_VAR_2}.\p"
	.string "¿Crees que sería divertido unirnos?\n"
	.string "¡Seguro que sí!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept::
	.string "¡Sí!\n"
	.string "¡Me voy a registrar!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject::
	.string "¿La próxima vez, ok?\n"
	.string "Quiero estar en tu equipo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1} y soy EXCURSIONISTA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1::
	.string "Los POKéMON que he traído son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te interesa unirte a mí\n"
	.string "en un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept::
	.string "¡Vaya, gracias!\n"
	.string "Haré el registro ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject::
	.string "Sería lindo unirme a ti\n"
	.string "en alguna otra ocasión.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro::
	.string "¡Soy el PSÍQUICO {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1::
	.string "Los dos que he criado son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Quieres formar un equipo doble\n"
	.string "conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept::
	.string "¡Claro que sí!\n"
	.string "¡Yo me encargo del registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject::
	.string "Si nos volvemos a ver, ahí me\n"
	.string "gustaría formar equipo contigo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro::
	.string "Soy {STR_VAR_1}.\n"
	.string "Soy un PSÍQUICO.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1::
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}--\n"
	.string "son mis discípulos.\p"
	.string "¿Te intriga la idea de formar\n"
	.string "una pareja de combate?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept::
	.string "Gracias.\n"
	.string "Iré a encargarme del registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject::
	.string "Espero que haya otra oportunidad\n"
	.string "de formar una alianza.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro::
	.string "¡Soy el ESTUDIANTE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1::
	.string "Un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask::
	.string "y uno que usa {STR_VAR_1}\n"
	.string "{STR_VAR_2} son mi pareja.\p"
	.string "¿Puedo ser tu compañero en\n"
	.string "un combate doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept::
	.string "¡Oh, gracias!\n"
	.string "¡Me registraré en el mostrador ya!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject::
	.string "¿Por favor?\n"
	.string "¿Puedo ir contigo la próxima vez?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro::
	.string "¡Hola! ¡Me llamo {STR_VAR_1}!\n"
	.string "¡Soy CRIADOR de POKéMON!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1::
	.string "Los POKéMON que crié son uno\n"
	.string "{STR_VAR_1} que usa {STR_VAR_2} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask::
	.string "uno {STR_VAR_1} que usa {STR_VAR_2}.\p"
	.string "¿Te interesa?\n"
	.string "¿Hacemos un equipo entonces?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept::
	.string "¡Muy bien!\n"
	.string "¡Deja el registro en mis manos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject::
	.string "Tienes que hacer equipo conmigo la\n"
	.string "próxima vez, ¿está bien?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro::
	.string "Soy {STR_VAR_1}, y me enorgullece\n"
	.string "decir que soy un POKéFAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1::
	.string "Los POKéMON que he criado son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿No son los más lindos?\n"
	.string "¡Hagamos un equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept::
	.string "¡Gracias, cielo!\n"
	.string "¡Iré ahora mismo a registrarme!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject::
	.string "Mis POKéMON son los mejores,\n"
	.string "te lo aseguro. ¡Qué molesto!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro::
	.string "Hola, soy el NADADOR {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1::
	.string "Un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask::
	.string "y un {STR_VAR_1}-usuario\n"
	.string "{STR_VAR_2} es lo que entrené.\p"
	.string "Hagamos un equipo doble.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept::
	.string "¡Genial!\n"
	.string "Nos registraré a los dos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject::
	.string "Si nos volvemos a ver, ¡me debes\n"
	.string "un combate doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro::
	.string "¿Qué pasa?\n"
	.string "Soy {STR_VAR_1}, ¡soy TRIATLETA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1::
	.string "Tengo un par de POKéMON decentes.\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Sería genial hacer un equipo doble\n"
	.string "juntos, ¿qué te parece?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept::
	.string "¡Genial!\n"
	.string "Espera mientras me registro, ¿sí?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject::
	.string "Espero que me dejes unirme a ti\n"
	.string "la próxima vez, ¿te parece?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro::
	.string "¡Soy el TRIATLETA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1::
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask::
	.string "otro {STR_VAR_2} que sepa usar\n"
	.string "{STR_VAR_1}. Esa es mi pareja.\p"
	.string "¿Qué te parece?\n"
	.string "Seríamos un buen equipo, diría.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept::
	.string "¡Me gusta esa respuesta!\n"
	.string "¡Haré el registro rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject::
	.string "Me darás otra oportunidad de formar\n"
	.string "una pareja, ¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro::
	.string "¡Hola! ¡Hola!\n"
	.string "¡Soy {STR_VAR_1} y soy NADADOR!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1::
	.string "¡Mira lo que he estado criando!\n"
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Genial, ¿no?\n"
	.string "¡Sería genial formar un equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept::
	.string "¡Muy agradecido!\n"
	.string "¡Terminaré pronto el registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject::
	.string "Si nos vemos, debes hacer equipo\n"
	.string "conmigo. Lo harás, ¿verdad?$"

