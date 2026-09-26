AzaleaTown_Mart_MapScripts::
	.byte 0

AzaleaTown_Mart_EventScriptCooltrainerM::
	lock
	faceplayer
	msgbox AzaleaMart_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Mart_EventScriptBugCatcher::
	lock
	faceplayer
	msgbox AzaleaMart_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaMart_Text_CooltrainerM:
	.string "¿Puedes comprar GREAT BALL?\n"
	.string "Solo puedo comprar POKé BALLS.\p"
	.string "¡He oído que hay más objetos\n"
	.string "disponibles al ganar\l"
	.string "MEDALLAS de GIMNASIO!\p"
	.string "Ojalá KURT me hiciera algunas\n"
	.string "de sus BALLS personalizadas.$"

AzaleaMart_Text_BugCatcher:
	.string "La GREAT BALL es mejor para capturar\n"
	.string "POKéMON que la POKé BALL.\p"
	.string "Pero las de KURT podrían ser mejores\n"
	.string "en ocasiones.$"

