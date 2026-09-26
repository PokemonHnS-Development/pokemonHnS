OlivineCity_Mart_MapScripts::
	.byte 0

OlivineCity_EventScript_Trainer1::
	lock
	faceplayer
	msgbox OlivineCity_Text_MartCooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Lass::
	lock
	faceplayer
	msgbox OlivineCity_Text_MartLass, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_MartCooltrainerF:
	.string "¿Tus POKéMON ya saben\n"
	.string "el movimiento para llevar gente\l"
	.string "sobre el agua?$"

OlivineCity_Text_MartLass:
	.string "Mi BUTTERFREE vino de mi\n"
	.string "novio del extranjero.\p"
	.string "Trajo una CARTA de su parte.\p"
	.string "¿Quieres saber qué dice?\p"
	.string "Veamos... ¡No! ¡Es un\n"
	.string "secreto!$"
