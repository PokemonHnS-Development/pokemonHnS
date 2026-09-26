BlackthornCity_Mart_MapScripts::
	.byte 0

BlackthornMart_EventScript_CoolTrainerM::
	msgbox BlackthornMart_Text_CooltrainerM, MSGBOX_NPC
	end

BlackthornMart_EventScript_BlackBelt::
	msgbox BlackthornMart_Text_BlackBelt, MSGBOX_NPC
	end

BlackthornMart_Text_CooltrainerM:
	.string "No puedes comprar MAX REVIVE, pero\n"
	.string "cura totalmente a un POKéMON.\p"
	.string "Cuidado: no restaura los PP, los\n"
	.string "PUNTOS DE PODER de los movimientos.$"

BlackthornMart_Text_BlackBelt:
	.string "MAX REPEL aleja a los POKéMON\n"
	.string "débiles de ti.\p"
	.string "Es el spray REPEL que dura\n"
	.string "más tiempo.$"
