VioletCity_House2_MapScripts::
	.byte 0

VioletCity_House2_EventScript_Lass::
	lock
	faceplayer
	msgbox VioletCity_NicknameHouse_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_House2_EventScript_Teacher::
	lock
	faceplayer
	msgbox VioletCity_NicknameHouse_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_House2_EventScript_Pidgey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	msgbox VioletCity_NicknameHouse_Text_Bird, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VioletCity_NicknameHouse_Text_Teacher:
	.string "Usa nombres de sus cosas\n"
	.string "favoritas para comer.\p"
	.string "Me refiero a los apodos que\n"
	.string "les pone a sus POKéMON.$"

VioletCity_NicknameHouse_Text_Lass:
	.string "¡Llamo a mi PIDGEY FRESA!$"

VioletCity_NicknameHouse_Text_Bird:
	.string "FRESA: ¡Pijji!$"
