SeafloorCavern_Room1_MapScripts::
	.byte 0

SeafloorCavern_Room1_EventScript_Grunt1::
	trainerbattle_single TRAINER_TROY, SeafloorCavern_Room1_Text_Grunt1Intro, SeafloorCavern_Room1_Text_Grunt1Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_EventScript_Grunt2::
	trainerbattle_single TRAINER_TULLY, SeafloorCavern_Room1_Text_Grunt2Intro, SeafloorCavern_Room1_Text_Grunt2Defeat
	msgbox SeafloorCavern_Room1_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room1_Text_Grunt1Intro:
	.string "¡No queremos niños aquí!\n"
	.string "¡Vete ya a casa!$"

SeafloorCavern_Room1_Text_Grunt1Defeat:
	.string "Quiero ir a casa…$"

SeafloorCavern_Room1_Text_Grunt1PostBattle:
	.string "Quiero un ascenso para poder\n"
	.string "mandar a los RECLUTAS…$"

SeafloorCavern_Room1_Text_Grunt2Intro:
	.string "Ese submarino… es diminuto.\n"
	.string "¡Me duele todo el cuerpo!$"

SeafloorCavern_Room1_Text_Grunt2Defeat:
	.string "¡Perder me duele!$"

SeafloorCavern_Room1_Text_Grunt2PostBattle:
	.string "Ese submarino que robamos,\n"
	.string "es un viaje brutal.\l"
	.string "¡Está muy apretado ahí dentro!$"

