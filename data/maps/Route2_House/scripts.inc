Route2_House_MapScripts::
	.byte 0

Route2_House_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_GOT_ROUTE2_NUGGET, Route2_House_EventScript_ManAfter
	msgbox Route2_House_Text_Fisher, MSGBOX_DEFAULT 
	giveitem ITEM_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox Route2_House_Text_Fisher_GotNugget, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_GOT_ROUTE2_NUGGET
	release
	end

Route2_House_EventScript_ManAfter::
	msgbox Route2_House_Text_Fisher_GotNugget, MSGBOX_DEFAULT
	closemessage
	release
	end

Route2_House_Text_Fisher:
	.string "¡Hola! Qué alegría verte.\p"
	.string "Eres la primera visita que tengo en\n"
	.string "mucho tiempo.\p"
	.string "¡Estoy feliz! Déjame darte un\n"
	.string "pequeño regalo.$"

Route2_House_Text_Fisher_GotNugget:
	.string "¡Es una PEPITA!\p"
	.string "No tengo pepitas de sabiduría,\n"
	.string "¡así que esto servirá!$"
