Route31_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route31_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route31_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route31_EventScript_Bugcatcher_Wade::
	trainerbattle_single TRAINER_WADE, Route31_Text_BugCatcherWade1_Seen, Route31_Text_BugCatcherWade1_Beaten
	msgbox Route31_Text_BugCatcherWade1_After, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route31_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan::
	lock
	faceplayer
	goto_if_eq VAR_KENYA, 1, Route31_EventScript_SleepyMan_AskForKenya
	msgbox Route31_Text_SleepyMan, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan_AskForKenya::
	msgbox Route31_Text_SleepyManGotMail MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route31_EventScript_SleepyMan_GiveKenya
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan_GiveKenya::
	removenamedmon 1
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Route31_EventScript_SleepyMan_Fail
	msgbox Route31_Text_HandOverMailMon, MSGBOX_DEFAULT
	delay 55
	callnative UpdateFollowingPokemon
	msgbox Route31_Text_ReadingMail, MSGBOX_DEFAULT
	giveitem ITEM_TM_TORMENT
	msgbox Route31_Text_DescribeNightmare, MSGBOX_DEFAULT
	closemessage
	setvar VAR_KENYA, 2
	release
	end

Route31_EventScript_SleepyMan_Fail::
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
	release
	end


Route31_EventScript_Boy::
	lock
	faceplayer
	msgbox Route31_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_DarkCaveSign::
	lock
	msgbox Route31_Text_DarkCaveSign, MSGBOX_SIGN
	closemessage
	release
	end

Route31_EventScript_Sign::
	lock
	msgbox Route31_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route31_EventScript_ItemPokeBall::
	finditem ITEM_POKE_BALL
	end

Route31_EventScript_ItemAntidote::
	finditem ITEM_ANTIDOTE
	end

Route31_Text_CooltrainerM:
	.string "CUEVA OSCURA…\p"
	.string "Si un POKéMON pudiera iluminarla,\n"
	.string "la exploraría.$"

Route31_Text_BugCatcherWade1_Seen:
	.string "Atrapé muchos POKéMON.\n"
	.string "¡Lucha conmigo!$"

Route31_Text_BugCatcherWade1_Beaten:
	.string "Awwwww…$"

Route31_Text_BugCatcherWade1_After:
	.string "Puedes atrapar POKéMON aunque\n"
	.string "tengas seis contigo.\p"
	.string "Si atrapas uno, irá a tu BOX\n"
	.string "automáticamente.$"

Route31_Text_SleepyMan:
	.string "… Hnuurg… ¿Eh?\p"
	.string "Caminé mucho hoy buscando\n"
	.string "POKéMON.\p"
	.string "Me duelen los pies y tengo sueño…\p"
	.string "Si fuera un POKéMON salvaje,\n"
	.string "sería fácil de atrapar…\p"
	.string "…Zzzz…$"

Route31_Text_SleepyManGotMail:
	.string "…Zzzz… ¿Eh?\p"
	.string "¿Qué es eso? ¿Tienes CORREO\n"
	.string "para mí?$"

Route31_Text_SleepyManFail:
	.string "…Zzzz…$"

Route31_Text_HandOverMailMon:
	.string "{PLAYER} entregó al\n"
	.string "POKéMON que traía el CORREO.$"

Route31_Text_ReadingMail:
	.string "Veamos...\p"
	.string "Gracias por traerme\n"
	.string "esto.\p"
	.string "Mi amigo es buen tipo, y\n"
	.string "¡tú también eres genial!\p"
	.string "¡Yo también quiero hacer\n"
	.string "algo bueno a cambio!\p"
	.string "¡Ya sé! ¡Quiero que tengas\n"
	.string "esto!$"

Route31_Text_DescribeNightmare:
	.string "Esa MT contiene TORMENTA.\p"
	.string "Es un movimiento malvado que\n"
	.string "pone nervioso al rival y\l"
	.string "evita que use el mismo\p"
	.string "movimiento varias veces.$"

Route31_Text_WrongMail:
	.string "Este CORREO no es para mí.$"

Route31_Text_MissingMail:
	.string "¿Por qué este POKéMON es especial?\p"
	.string "No tiene ningún CORREO.$"

Route31_Text_DeclinedToHandOverMail:
	.string "¿Qué? ¿No quieres\n"
	.string "nada?$"

Route31_Text_CantTakeLastMon:
	.string "Si te quito ese POKéMON,\n"
	.string "entonces,\p"
	.string "¿qué usarás en la\n"
	.string "batalla?$"

Route31_Text_Youngster:
	.string "Hallé un buen POKéMON en la\n"
	.string "CUEVA OSCURA.\p"
	.string "Lo entrenaré para enfrentar a\n"
	.string "FALKNER.\p"
	.string "Es el líder del GIMNASIO de\n"
	.string "CIUDAD MALVA.$"

Route31_Text_Sign:
	.string "RUTA 31\p"
	.string "CIUDAD MALVA - CIUDAD CEREZO$"

Route31_Text_DarkCaveSign:
	.string "CUEVA OSCURA$"
