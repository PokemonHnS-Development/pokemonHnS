Route3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route3_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route3_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route3_EventScript_Otis::
	trainerbattle_single TRAINER_OTIS, Route3_Text_FirebreatherOtis_Seen, Route3_Text_FirebreatherOtis_Beaten
	msgbox Route3_Text_FirebreatherOtis_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Warren::
	trainerbattle_single TRAINER_WARREN, Route3_Text_YoungsterWarren_Seen, Route3_Text_YoungsterWarren_Beaten
	msgbox Route3_Text_YoungsterWarren_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Jimmy::
	trainerbattle_single TRAINER_JIMMY, Route3_Text_YoungsterJimmy_Seen, Route3_Text_YoungsterJimmy_Beaten
	msgbox Route3_Text_YoungsterJimmy_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Burt::
	trainerbattle_single TRAINER_BURT, Route3_Text_FirebreatherBurt_Seen, Route3_Text_FirebreatherBurt_Beaten
	msgbox Route3_Text_FirebreatherBurt_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route3_EventScript_Sign::
	msgbox Route3_Text_MtMoonSquareSign, MSGBOX_SIGN
	end

Route3_Text_FirebreatherOtis_Seen:
	.string "¡Ah! El clima está genial.$"

Route3_Text_FirebreatherOtis_Beaten:
	.string "Hace sol, pero estoy empapado…$"

Route3_Text_FirebreatherOtis_AfterBattle:
	.string "Cuando llueve, es difícil\n"
	.string "encenderse…$"

Route3_Text_YoungsterWarren_Seen:
	.string "Hmmm… No sé qué hacer…$"

Route3_Text_YoungsterWarren_Beaten:
	.string "Sabía que perdería…$"

Route3_Text_YoungsterWarren_AfterBattle:
	.string "Te veías fuerte.\p"
	.string "Me dio miedo enfrentarte…$"

Route3_Text_YoungsterJimmy_Seen:
	.string "¡Corro como el viento!$"

Route3_Text_YoungsterJimmy_Beaten:
	.string "¡Salí volando!$"

Route3_Text_YoungsterJimmy_AfterBattle:
	.string "Uso shorts todo el año.\p"
	.string "Es mi estilo de moda.$"

Route3_Text_FirebreatherBurt_Seen:
	.string "¡Acérquense y echen un vistazo!$"

Route3_Text_FirebreatherBurt_Beaten:
	.string "¡Ay! ¡Eso quema!$"

Route3_Text_FirebreatherBurt_AfterBattle:
	.string "El mejor lanzallamas de KANTO,\n"
	.string "soy yo.\p"
	.string "Pero no el mejor entrenador…$"

Route3_Text_MtMoonSquareSign:
	.string "PLAZA DEL MT.MOON\p"
	.string "Solo sube las escaleras.$"

