MtPyre_5F_MapScripts::
	.byte 0

@ Seems like the scripts for the 4F and 5F were swapped

MtPyre_4F_EventScript_Tasha::
	trainerbattle_single TRAINER_TASHA, MtPyre_4F_Text_TashaIntro, MtPyre_4F_Text_TashaDefeat
	msgbox MtPyre_4F_Text_TashaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_4F_Text_TashaIntro:
	.string "Amo todo lo horroroso...\n"
	.string "Es como una enfermedad...\p"
	.string "Cuando estoy aquí...\n"
	.string "Tiemblo de miedo...$"

MtPyre_4F_Text_TashaDefeat:
	.string "Perder, no me gusta...$"

MtPyre_4F_Text_TashaPostBattle:
	.string "Quiero ver cosas terribles...\n"
	.string "No puedo irme...\p"
	.string "Quédate...\n"
	.string "¿No te quedarás conmigo?$"

