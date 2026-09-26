Route39_FarmHouse_MapScripts::
	.byte 0


Route39House_EventScript_FarmerF::
	lock
	faceplayer
	goto_if_eq VAR_ROUTE39_BARN, 5, Route39House_EventScript_FarmerFAfter
	msgbox Route39_Text_FarmerFInTrouble, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39House_EventScript_FarmerFAfter::
	goto_if_set FLAG_GOT_TM_SNATCH, Route39House_EventScript_FarmerFAfterTM
	msgbox Route39_Text_FarmerFHealedMiltank, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNATCH
	msgbox Route39_Text_FarmerFSnatchSpeech, MSGBOX_DEFAULT
	closemessage 
	setflag FLAG_GOT_TM_SNATCH
	release
	end

Route39House_EventScript_FarmerFAfterTM::
	msgbox Route39_Text_FarmerFSnatchSpeech, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM::
	lock
	faceplayer
	goto_if_lt VAR_ROUTE39_BARN, 5, Route39_FarmHouse_EventScript_FarmerM_Sick
	showmoneybox 0, 0
	msgbox Route39_Text_FarmerMBuyMilk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route39_FarmHouse_EventScript_FarmerMBuyMilk
	msgbox Route39_Text_FarmerMNoSale, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	end

Route39_FarmHouse_EventScript_FarmerMBuyMilk::
	checkmoney 500, 0
	goto_if_eq VAR_RESULT, FALSE, Route39_FarmHouse_EventScript_FarmerM_NotEnough
	additem ITEM_MOOMOO_MILK
	goto_if_eq VAR_RESULT, FALSE, Route39_FarmHouse_EventScript_FarmerM_BagFull
	removemoney 500
	updatemoneybox 0
	msgbox Route39FarmHouse_Text_WouldYouLikeAnother, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route39_FarmHouse_EventScript_FarmerMBuyMilk

	
	msgbox Route39_Text_FarmerMGotMilk, MSGBOX_DEFAULT
	closemessage
	playse MUS_OBTAIN_ITEM
	msgbox Route39_Text_GotMilk, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

Route39_FarmHouse_EventScript_FarmerM_Sick::
	msgbox Route39_Text_FarmerMSickCow, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM_BagFull::
	msgbox Route39_Text_FarmerMNoRoom, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM_NotEnough::
	msgbox Route39_Text_FarmerMNoMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

Route39_Text_FarmerMSickCow:
	.string "Mi MILTANK ya no me da\n"
	.string "leche.\p"
	.string "La leche de esta GRANJA es famosa.\p"
	.string "Casi todos quieren beberla.\p"
	.string "Creo que me dará mucha leche si\n"
	.string "le doy muchas BAYAS,\l"
	.string "me imagino.$"

Route39_Text_FarmerMBuyMilk:
	.string "¿Qué te parece mi LECHE MU-MU?\p"
	.string "Es mi orgullo y alegría.\p"
	.string "¡Dásela a POKéMON para curar HP!\p"
	.string "Te la daré por solo\n"
	.string "¥500.$"

Route39_Text_FarmerMGotMilk:
	.string "¡Aquí tienes!\n"
	.string "¡Bebe y disfruta!$"

Route39_Text_FarmerMNoMoney:
	.string "Lo siento.\n"
	.string "¡Sin dinero no hay venta!$"

Route39_Text_FarmerMNoRoom:
	.string "Creo que tu MOCHILA está llena.$"

Route39_Text_FarmerMNoSale:
	.string "¿No la quieres?\n"
	.string "¡Vuelve luego, ¿sí?$"

Route39FarmHouse_Text_WouldYouLikeAnother:
	.string "¿Quieres otra más?$"

Route39_Text_GotMilk:
	.string "{PLAYER} recibió LECHE MU-MU.$"

Route39_Text_FarmerMMilking:
	.string "Mejor voy a ordeñar.$"

Route39_Text_FarmerFInTrouble:
	.string "Nuestra leche llega hasta\n"
	.string "KANTO.\p"
	.string "Si nuestro MILTANK no nos da\n"
	.string "leche, estaremos en problemas.$"

Route39_Text_FarmerFHealedMiltank:
	.string "Curaste a nuestro MILTANK.\n"
	.string "Ya da LECHE MU-MU otra vez.\p"
	.string "Toma esto por tu ayuda.$"

Route39_Text_FarmerFSnatchSpeech:
	.string "Eso es ARREBATO.\p"
	.string "Es un movimiento que deja que\n"
	.string "un POKéMON robe el ataque del\l"
	.string "rival justo antes de usarlo.\p"
	.string "Si varios POKéMON usan\n"
	.string "ARREBATO, solo el más lento\l"
	.string "logrará robar el movimiento.\p"
	.string "Úsalo bien. El tiempo lo es\n"
	.string "todo.$"
