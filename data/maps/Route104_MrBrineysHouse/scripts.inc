.set LOCALID_BRINEY, 1
.set LOCALID_PEEKO, 2

Route104_MrBrineysHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_MrBrineysHouse_OnTransition
	.byte 0

Route104_MrBrineysHouse_OnTransition:
	setflag FLAG_LANDMARK_MR_BRINEY_HOUSE
	call_if_eq VAR_GARBAGEVAR, 1, Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos
	call_if_set FLAG_RECEIVED_POKENAV, Route104_MrBrineysHouse_EventScript_HideRustboroRival
	end

Route104_MrBrineysHouse_EventScript_HideRustboroRival::
	setflag FLAG_GARBAGEFLAG
	return

Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos::
	setobjectxyperm LOCALID_BRINEY, 9, 3
	setobjectmovementtype LOCALID_BRINEY, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT
	setobjectxyperm LOCALID_PEEKO, 9, 6
	setobjectmovementtype LOCALID_PEEKO, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN
	return

Route104_MrBrineysHouse_EventScript_Briney::
	lock
	faceplayer
	call_if_unset FLAG_MR_BRINEY_SAILING_INTRO, Route104_MrBrineysHouse_EventScript_SailingIntro
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_MrBrineysHouse_EventScript_SailBothDeliveries
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, Route104_MrBrineysHouse_EventScript_SailDeliverPackage
	goto Route104_MrBrineysHouse_EventScript_WhereAreWeBound
	end

Route104_MrBrineysHouse_EventScript_SailingIntro::
	setflag FLAG_MR_BRINEY_SAILING_INTRO
	msgbox Route104_MrBrineysHouse_Text_WaitUpPeeko, MSGBOX_DEFAULT
	msgbox Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_WhereAreWeBound::
	message Route104_MrBrineysHouse_Text_WhereAreWeBound
	waitmessage
	multichoicedefault 20, 8, MULTI_BRINEY_OFF_DEWFORD, 1, FALSE
	switch VAR_RESULT
	case 0, Route104_MrBrineysHouse_EventScript_SailToDewford
	case 1, Route104_MrBrineysHouse_EventScript_DeclineSailing
	case MULTI_B_PRESSED, Route104_MrBrineysHouse_EventScript_DeclineSailing
	end

Route104_MrBrineysHouse_EventScript_SailBothDeliveries::
	msgbox Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_SailDeliverPackage::
	msgbox Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
	end

Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing::
	msgbox Route104_MrBrineysHouse_Text_DeclineDeliverySail, MSGBOX_DEFAULT
	release
	end

Route104_MrBrineysHouse_EventScript_DeclineSailing::
	msgbox Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail, MSGBOX_DEFAULT
	release
	end

Route104_MrBrineysHouse_EventScript_SailToDewford::
	msgbox Route104_MrBrineysHouse_Text_SetSailForDewford, MSGBOX_DEFAULT
	call EventScript_BackupMrBrineyLocation
	setvar VAR_GARBAGEVAR, 1
	clearflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	setvar VAR_GARBAGEVAR, 8
	setvar VAR_GARBAGEVAR, 2
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_HIDE_ROUTE_104_RIVAL
	warp MAP_ROUTE104, 13, 51
	waitstate
	releaseall
	end

Route104_MrBrineysHouse_EventScript_Peeko::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox Route104_MrBrineysHouse_Text_Peeko, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route104_MrBrineysHouse_Text_WaitUpPeeko:
	.string "SR. BRINEY: ¡Espera, niña!\n"
	.string "¡Espera, PEEKO!$"

Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford:
	.string "Hm? ¡Eres {PLAYER}{KUN}!\n"
	.string "¡Salvaste a mi querido PEEKO!\l"
	.string "¡Te debemos muchísimo!\p"
	.string "¿Qué dices?\n"
	.string "¿Quieres navegar conmigo?\p"
	.string "Hmhm...\p"
	.string "¿Tienes una CARTA para DEWFORD\n"
	.string "y un paquete para SLATEPORT?\p"
	.string "¡Llevas una vida muy agitada!\p"
	.string "Pero claro, lo que pides\n"
	.string "no es problema alguno.\p"
	.string "¡Has venido al hombre indicado!\n"
	.string "Zarparemos hacia DEWFORD.$"

Route104_MrBrineysHouse_Text_SetSailForDewford:
	.string "SR. BRINEY: ¡A ROCA entonces!\p"
	.string "¡Leven anclas!\n"
	.string "¡PEEKO, zarpamos, querida!$"

Route104_MrBrineysHouse_Text_DeclineDeliverySail:
	.string "SR. BRINEY: ¿Ah, sí?\n"
	.string "¿Tus entregas pueden esperar?\p"
	.string "¡Solo dime cuando quieras\n"
	.string "que zarpemos!$"

Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford:
	.string "SR. BRINEY: ¡Ahoy!\n"
	.string "¡Sé exactamente qué quieres decir!\p"
	.string "Debes llevar una CARTA a ROCA\n"
	.string "y un paquete a FONDOPORTUAL.\p"
	.string "Lo que pides no es problema\n"
	.string "ninguno, ¡soy el hombre ideal!\p"
	.string "Primero, zarparemos hacia ROCA.$"

Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford:
	.string "SR. BRINEY: ¡Ahoy!\n"
	.string "¡Sé exactamente qué quieres decir!\p"
	.string "Debes llevar un paquete al\n"
	.string "CAP. STERN en FONDOPORTUAL.\p"
	.string "Lo que pides no es problema\n"
	.string "ninguno, ¡soy el hombre ideal!\p"
	.string "Primero, zarparemos hacia ROCA.$"

Route104_MrBrineysHouse_Text_WhereAreWeBound:
	.string "SR. BRINEY: ¡Ahoy!\n"
	.string "¡Iré al mar por ti cuando quieras!\p"
	.string "Amigo, ¿a dónde nos dirigimos?$"

Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail:
	.string "SR. BRINEY: ¿Ah, sí?\n"
	.string "Bueno, PEEKO te debe la vida.\p"
	.string "¡Solo dime cuando quieras\n"
	.string "que zarpemos!$"

Route104_MrBrineysHouse_Text_Peeko:
	.string "PEEKO: ¡Pii piihyoro!$"

