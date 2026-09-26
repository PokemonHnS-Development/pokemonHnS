GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "Oye, tú.\n"
	.string "Se pone muy oscuro más adelante.\l"
	.string "Será difícil explorar.\p"
	.string "Aquel chico que pasó hace poco...\n"
	.string "STEVEN, creo que se llamaba.\p"
	.string "Él sabía usar FLASH, así que\n"
	.string "estará bien, pero...\p"
	.string "Bueno, para nosotros los HIKERS,\n"
	.string "ayudar es nuestro lema.\p"
	.string "Toma, te daré esto.$"

GraniteCave_1F_Text_ExplainFlash:
	.string "Usa FLASH si tienes la MO en la\n"
	.string "mochila y un POKéMON que la aprenda.\l"
	.string "No hace falta enseñársela.\p"
	.string "Pero para usarla, necesitas la MEDALLA\n"
	.string "del GIMNASIO de DEWFORD.\p"
	.string "Ilumina hasta la oscuridad más\n"
	.string "profunda de las cuevas.$"
