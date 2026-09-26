PalletTown_RedsHouse_1F_MapScripts::
	.byte 0

PalletTown_RedsHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_ge VAR_TEMP_0, 1, PalletTown_RedsHouse_1F_EventScript_MomAfter
	msgbox RedsHouse_Text_Mom1, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 1
	release
	end

PalletTown_RedsHouse_1F_EventScript_MomAfter::
	msgbox RedsHouse_Text_Mom2, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_RedsHouse_1F_EventScript_TV::
	msgbox RedsHouse_Text_TV, MSGBOX_SIGN
	end

RedsHouse_Text_Mom1:
	.string "¡Hola!\p"
	.string "RED se fue hace mucho tiempo.\p"
	.string "Tampoco ha llamado, así que no\n"
	.string "sé dónde está ni qué ha\l"
	.string "estado haciendo.\p"
	.string "Dicen que el silencio es prueba de\n"
	.string "que está bien, pero me\l"
	.string "preocupo por él.$"

RedsHouse_Text_Mom2:
	.string "Temo que RED se lastime o se\n"
	.string "enferme, pero es un chico.\p"
	.string "Me enorgullece que haga lo que\n"
	.string "él quiere hacer.$"

RedsHouse_Text_TV:
	.string "Tienen programas que no se\n"
	.string "transmiten en JOHTO…$"
