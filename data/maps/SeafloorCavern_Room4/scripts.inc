SeafloorCavern_Room4_MapScripts::
	.byte 0

SeafloorCavern_Room4_EventScript_Grunt3::
	trainerbattle_single TRAINER_TYLER, SeafloorCavern_Room4_Text_Grunt3Intro, SeafloorCavern_Room4_Text_Grunt3Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_EventScript_Grunt4::
	trainerbattle_single TRAINER_VALERIE, SeafloorCavern_Room4_Text_Grunt4Intro, SeafloorCavern_Room4_Text_Grunt4Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_Text_Grunt3Intro:
	.string "¿Quién eres?\n"
	.string "¿Por dónde entraste?$"

SeafloorCavern_Room4_Text_Grunt3Defeat:
	.string "Lo perdí...$"

SeafloorCavern_Room4_Text_Grunt3PostBattle:
	.string "¡No hallo la salida!\p"
	.string "¡No tengo miedo, no me malentiendas!$"

SeafloorCavern_Room4_Text_Grunt4Intro:
	.string "¿Quién eres?\n"
	.string "¿A dónde crees que vas?$"

SeafloorCavern_Room4_Text_Grunt4Defeat:
	.string "¡No pude ganar!$"

SeafloorCavern_Room4_Text_Grunt4PostBattle:
	.string "¡Mi socio olvidó el mapa en aquel\n"
	.string "submarino!\p"
	.string "¿No es un inútil?$"

