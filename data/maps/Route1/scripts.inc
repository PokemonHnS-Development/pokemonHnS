Route1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route1_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route1_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route1_EventScript_SchoolboyDanny::
	trainerbattle_single TRAINER_DANNY, Route1_Text_SchoolboyDanny_Seen, Route1_Text_SchoolboyDanny_Beaten
	msgbox Route1_Text_SchoolboyDanny_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route1_EventScript_Quinn::
	trainerbattle_single TRAINER_QUINN, Route1_Text_CooltrainerFQuinn_Seen, Route1_Text_CooltrainerFQuinn_Beaten
	msgbox Route1_Text_CooltrainerFQuinn_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route1_EventScript_Sign::
	msgbox Route1_Text_Sign, MSGBOX_SIGN
	end

Route1_Text_SchoolboyDanny_Seen:
	.string "Si los entrenadores se encuentran,\n"
	.string "lo primero es luchar.$"

Route1_Text_SchoolboyDanny_Beaten:
	.string "Aww... tengo un récord perdedor...$"

Route1_Text_SchoolboyDanny_AfterBattle:
	.string "Para los entrenadores, es obvio\n"
	.string "que lucharemos al vernos.$"

Route1_Text_CooltrainerFQuinn_Seen:
	.string "¡Tú! ¿Quieres luchar?$"

Route1_Text_CooltrainerFQuinn_Beaten:
	.string "Estoy acabado...$"

Route1_Text_CooltrainerFQuinn_AfterBattle:
	.string "Eres fuerte.\p"
	.string "Se nota que has entrenado\n"
	.string "duro.$"

Route1_Text_Sign:
	.string "RUTA 1\p"
	.string "PLATA EA - CIUDAD VERIDIAN$"
