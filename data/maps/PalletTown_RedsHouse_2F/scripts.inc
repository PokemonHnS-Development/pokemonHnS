PalletTown_RedsHouse_2F_MapScripts::
	.byte 0

PalletTown_RedsHouse_2F_EventScript_NES::
	msgbox RedsHouse_Text_NES, MSGBOX_SIGN
	end

PalletTown_RedsHouse_2F_EventScript_PC::
	msgbox RedsHouse_Text_PC, MSGBOX_SIGN
	end

RedsHouse_Text_NES:
	.string "{PLAYER} usó la NES.\p"
	.string "¡Me voy, no hay tiempo que perder!$"

RedsHouse_Text_PC:
	.string "Parece que no se ha usado\n"
	.string "en mucho tiempo...$"
