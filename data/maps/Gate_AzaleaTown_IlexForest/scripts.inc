Gate_AzaleaTown_IlexForest_MapScripts::
	.byte 0

Gate_AzaleaTown_IlexForest_EventScript_Officer::
	lock
	faceplayer
	msgbox Gate_AzaleaTown_IlexForest_Text_Officer, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_AzaleaTown_IlexForest_EventScript_Granny::
	lock
	faceplayer
	msgbox Gate_AzaleaTown_IlexForest_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_AzaleaTown_IlexForest_Text_Officer:
	.string "EL BOSQUE VERDE es grande.\n"
	.string "¡Ten cuidado!\n"
	.string "No te pierdas.$"

Gate_AzaleaTown_IlexForest_Text_Granny:
	.string "El BOSQUE VERDE es vigilado\n"
	.string "por su protector.\p"
	.string "¡No hagas travesuras!$"
