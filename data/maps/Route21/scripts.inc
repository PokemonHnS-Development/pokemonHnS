Route21_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route21_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route21_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route21_EventScript_Seth::
	trainerbattle_single TRAINER_SETH Route21_Text_SwimmermSethSeen, Route21_Text_SwimmermSethBeaten
	msgbox Route21_Text_SwimmermSethAfterBattle, MSGBOX_AUTOCLOSE
	end

Route21_EventScript_Nikki::
	trainerbattle_single TRAINER_NIKKI Route21_Text_SwimmerfNikkiSeen, Route21_Text_SwimmerfNikkiBeaten
	msgbox Route21_Text_SwimmerfNikkiAfterBattle, MSGBOX_AUTOCLOSE
	end

Route21_EventScript_Arnold::
	trainerbattle_single TRAINER_ARNOLD Route21_Text_FisherArnoldSeen, Route21_Text_FisherArnoldBeaten
	msgbox Route21_Text_FisherArnoldAfterBattle, MSGBOX_AUTOCLOSE
	end

Route21_Text_SwimmermSethSeen:
	.string "¡Tierra a la vista! ¡Hay que seguir!$"

Route21_Text_SwimmermSethBeaten:
	.string "Glug…$"

Route21_Text_SwimmermSethAfterBattle:
	.string "Este arrogante estuvo en el\n"
	.string "volcán de CINNABAR.$"

Route21_Text_SwimmerfNikkiSeen:
	.string "¡Si gano, me ayudas con mi\n"
	.string "loción bronceadora!$"

Route21_Text_SwimmerfNikkiBeaten:
	.string "Me preocupa quemarme con el sol…$"

Route21_Text_SwimmerfNikkiAfterBattle:
	.string "Debo cuidar las manchas\n"
	.string "causadas por el sol.$"

Route21_Text_FisherArnoldSeen:
	.string "Me aburre pescar. ¡Luchemos!$"

Route21_Text_FisherArnoldBeaten:
	.string "Un fracaso total…$"

Route21_Text_FisherArnoldAfterBattle:
	.string "Volveré a pescar...$"

