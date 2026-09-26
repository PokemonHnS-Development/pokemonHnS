MtPyre_4F_MapScripts::
	.byte 0

@ Seems like the scripts for the 4F and 5F were swapped

MtPyre_5F_EventScript_Atsushi::
	trainerbattle_single TRAINER_CINDY, MtPyre_5F_Text_AtsushiIntro, MtPyre_5F_Text_AtsushiDefeat
	msgbox MtPyre_5F_Text_AtsushiPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_5F_Text_AtsushiIntro:
	.string "Maestro...\n"
	.string "¡Vigila mi progreso, por favor!$"

MtPyre_5F_Text_AtsushiDefeat:
	.string "Maestro...\n"
	.string "¡Por favor, perdóname!$"

MtPyre_5F_Text_AtsushiPostBattle:
	.string "Hasta que mejore, mi maestro, que\n"
	.string "descansa aquí, no tendrá paz...$"

