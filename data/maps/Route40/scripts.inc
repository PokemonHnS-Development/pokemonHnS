Route40_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route40_MapScript_OnTransition
	.byte 0

Route40_MapScript_OnTransition::
	callnative SetTimeBasedEncounters
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, Route40_MapScript_ClearWeather
	end

Route40_MapScript_ClearWeather::
	setweather WEATHER_NONE
	end

Route40_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON, Route40_Text_SwimmermSimonSeen, Route40_Text_SwimmermSimonBeaten
	msgbox Route40_Text_SwimmermSimonAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmermSimonSeen:
	.string "Debes calentar antes de\n"
	.string "entrar al agua.\p"
	.string "Es básico.$"

Route40_Text_SwimmermSimonBeaten:
	.string "¡Está bien! ¡Tío! ¡Me rindo!$"

Route40_Text_SwimmermSimonAfter:
	.string "CIUDAD ORQUIDEA queda a una\n"
	.string "buena distancia de aquí.$"

Route40_EventScript_Randall::
	trainerbattle_single TRAINER_RANDALL, Route40_Text_SwimmermRandallSeen, Route40_Text_SwimmermRandallBeaten
	msgbox Route40_Text_SwimmermRandallAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmermRandallSeen:
	.string "¡Oye, eres joven y fuerte!\p"
	.string "¡No uses tu POKéMON!\n"
	.string "¡Nada!$"

Route40_Text_SwimmermRandallBeaten:
	.string "Oh, no. Perdí...$"

Route40_Text_SwimmermRandallAfter:
	.string "Nadar ejercita todo el\n"
	.string "cuerpo. Es saludable.$"

Route40_EventScript_Elaine::
	trainerbattle_single TRAINER_ELAINE, Route40_Text_SwimmerfElaineSeen, Route40_Text_SwimmerfElaineBeaten
	msgbox Route40_Text_SwimmerfElaineAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmerfElaineSeen:
	.string "¿Vas a CIUDAD ORQUIDEA?\p"
	.string "¿Qué tal una batalla rápida\n"
	.string "antes?$"

Route40_Text_SwimmerfElaineBeaten:
	.string "¡Perdí esa batalla!$"

Route40_Text_SwimmerfElaineAfter:
	.string "Diría que nado mejor\n"
	.string "que tú. ¡Sí!$"

Route40_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA, Route40_Text_SwimmerfPaulaSeen, Route40_Text_SwimmerfPaulaBeaten
	msgbox Route40_Text_SwimmerfPaulaAfter, MSGBOX_AUTOCLOSE
	end

Route40_Text_SwimmerfPaulaSeen:
	.string "No necesito flotador.\p"
	.string "¡Me agarro a un POKéMON\n"
	.string "marino!$"

Route40_Text_SwimmerfPaulaBeaten:
	.string "¡Uf, me siento mareado!$"

Route40_Text_SwimmerfPaulaAfter:
	.string "Mientras floto así,\n"
	.string "las olas me llevan.$"

Route40_EventScript_Woman1::
	lock
	faceplayer
	msgbox Route40_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_Lass1:
	.string "Aunque no se ve desde aquí,\n"
	.string "CIUDAD ORQUIDEA está al otro lado.$"

Route40_EventScript_Woman2::
	lock
	faceplayer
	msgbox Route40_Text_Lass2, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_Lass2:
	.string "Vine a CIUDAD OLIVO en barco para\n"
	.string "ver los paisajes y sentir la\l"
	.string "atmósfera.\p"
	.string "Al ser un puerto, se siente muy\n"
	.string "distinto a una gran ciudad.$"

Route40_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route40_Text_StandingYoungster, MSGBOX_DEFAULT
	closemessage
	release
	end

Route40_Text_StandingYoungster:
	.string "¿Has ido a la COLINA DEL\n"
	.string "ENTRENADOR?\p"
	.string "Creo que ya se reunieron muchos\n"
	.string "entrenadores fuertes allí.\p"
	.string "Pero con tantas MEDALLAS,\n"
	.string "no deberías tener problemas.$"

Route40_Text_Monica:
	.string "MONICA: Gusto en conocerte.\n"
	.string "Soy MONICA de la FAMILIA SEMANAL.\p"
	.string "¡Apuesto a que no adivinas mi día\n"
	.string "favorito de la semana!$"

Route40_Text_MonicaGivesGift:
	.string "¡Exacto!\p"
	.string "Como muestra de nuestra amistad,\n"
	.string "¡tengo un regalo para ti!$"

Route40_Text_MonicaGaveGift:
	.string "MONICA: Es un objeto que sube\n"
	.string "el poder de los ataques VOLADOR.\p"
	.string "Equípalo en un POKéMON\n"
	.string "que sea un ave.$"

Route40_Text_MonicaMonday:
	.string "MONICA: Mis hermanos y\n"
	.string "hermanas están por todas partes.\p"
	.string "¡Mira si puedes\n"
	.string "encontrarlos a todos!$"

Route40_Text_MonicaNotMonday:
	.string "MONICA: No creo que hoy\n"
	.string "sea lunes. Qué triste…$"

Route40_Text_MonicaNope:
	.string "Ese no es.$"

Rotue40_EventScript_Monica::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SHARP_BEAK, Rotue40_EventScript_MonicaCompleted
	msgbox Route40_Text_Monica, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Rotue40_EventScript_MonicaNope
	case 1, Rotue40_EventScript_MonicaYes
	case 2, Rotue40_EventScript_MonicaNope
	case 3, Rotue40_EventScript_MonicaNope
	case 4, Rotue40_EventScript_MonicaNope
	case 5, Rotue40_EventScript_MonicaNope
	case 6, Rotue40_EventScript_MonicaNope
	case 7 Rotue40_EventScript_MonicaCancel
	case MULTI_B_PRESSED, Rotue40_EventScript_MonicaCancel
	closemessage
	release
	end
Rotue40_EventScript_MonicaYes::
	msgbox Route40_Text_MonicaGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_SHARP_BEAK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_SHARP_BEAK
	msgbox Route40_Text_MonicaGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Rotue40_EventScript_MonicaNope::
	msgbox Route40_Text_MonicaNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Rotue40_EventScript_MonicaCancel::
	closemessage
	release
	end
Rotue40_EventScript_MonicaCompleted::
	msgbox Route40_Text_MonicaMonday, MSGBOX_DEFAULT
	closemessage
	release
	end
