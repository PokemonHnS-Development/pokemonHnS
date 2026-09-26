OlivineCity_House2_MapScripts::
	.byte 0

OlivineCity_EventScript_Punisher::
	lock
	faceplayer
	msgbox OlivineCity_Text_PunishmentBro, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_PunisherBoy::
	lock
	faceplayer
	msgbox OlivineCity_Text_PunishmentBoy, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_PunishmentBro:
	.string "Rumbo a CIUDAD ORQUIDEA,\n"
	.string "hay cuatro islas desiertas.\p"
	.string "¡Llevan a los niños malos allí\n"
	.string "como castigo!$"

OlivineCity_Text_PunishmentBoy:
	.string "Cuando me meto en problemas,\n"
	.string "mi hermano siempre me asusta.$"
