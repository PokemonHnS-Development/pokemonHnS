Route26_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route26_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route26_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route26_EventScript_Jake::
	trainerbattle_single TRAINER_JAKE Route26_Text_CooltrainermJakeSeen, Route26_Text_CooltrainermJakeBeaten
	msgbox Route26_Text_CooltrainermJakeAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Gaven::
	trainerbattle_single TRAINER_GAVEN Route26_Text_CooltrainermGavenSeen, Route26_Text_CooltrainermGavenBeaten
	msgbox Route26_Text_CooltrainermGavenAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Joyce::
	trainerbattle_single TRAINER_JOYCE Route26_Text_CooltrainerfJoyceSeen, Route26_Text_CooltrainerfJoyceBeaten
	msgbox Route26_Text_CooltrainerfJoyceAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Beth::
	trainerbattle_single TRAINER_BETH Route26_Text_CooltrainerfBethSeen, Route26_Text_CooltrainerfBethBeaten
	msgbox Route26_Text_CooltrainerfBethAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Richard::
	trainerbattle_single TRAINER_RICHARD Route26_Text_PsychicRichardSeen, Route26_Text_PsychicRichardBeaten
	msgbox Route26_Text_PsychicRichardAfter, MSGBOX_AUTOCLOSE
	end

Route26_Text_CooltrainermJakeSeen:
    .string "Hago mis preparativos finales\n"
    .string "para la LIGA POKéMON.$"

Route26_Text_CooltrainermJakeBeaten:
    .string "¡Lo arruiné!$"

Route26_Text_CooltrainermJakeAfter:
    .string "Será difícil ganar en la\n"
    .string "LIGA.\p"
    .string "Debo entrenar más.\p"
    .string "Dicen que el ALTO MANDO de la\n"
    .string "LIGA es más fuerte que los LÍDERES.$"

Route26_Text_CooltrainermGavenSeen:
    .string "Viviendo batallas difíciles,\n"
    .string "ganas poder.$"

Route26_Text_CooltrainermGavenBeaten:
    .string "¡Gaah! ¡La vida es más difícil!$"

Route26_Text_CooltrainermGavenAfter:
    .string "Para ir a la LIGA POKéMON, debes\n"
    .string "pasar por la CALLE VICTORIA.\p"
    .string "Pero es un camino muy duro.\p"
    .string "¡Casi nadie va por ahí!$"

Route26_Text_CooltrainerfJoyceSeen:
    .string "Ya que llegaste hasta aquí,\n"
    .string "debes ser bueno.\p"
    .string "¡Daré todo de mí en esta\n"
    .string "batalla!$"

Route26_Text_CooltrainerfJoyceBeaten:
    .string "¡No! ¡No puedo creerlo!$"

Route26_Text_CooltrainerfJoyceAfter:
    .string "Vencí a ocho LÍDERES de GIMNASIO,\n"
    .string "así que estaba confiado.\p"
    .string "Debo esforzarme más la próxima vez.$"

Route26_Text_CooltrainerfBethSeen:
    .string "Perdí contra un ENTRENADOR llamado {RIVAL}.\p"
    .string "Era muy fuerte, pero...\p"
    .string "Parecía que tenía que ganar\n"
    .string "a cualquier costo.\p"
    .string "Sentí pena por sus POKéMON.$"

Route26_Text_CooltrainerfBethBeaten:
    .string "Los POKéMON no son armas de guerra.$"

Route26_Text_CooltrainerfBethAfter:
    .string "Los POKéMON son compañeros\n"
    .string "invaluables para toda la vida.$"

Route26_Text_PsychicRichardSeen:
    .string "¡Vaya, mira todas esas MEDALLAS!\n"
    .string "Estoy impresionado.\p"
    .string "Pero no te basta con solo\n"
    .string "coleccionarlas, ¿verdad?$"

Route26_Text_PsychicRichardBeaten:
    .string "¡Buena batalla!$"

Route26_Text_PsychicRichardAfter:
    .string "Gente y POKéMON crecen con sus\n"
    .string "experiencias.\p"
    .string "No te vuelvas flojo ni confiado.$"

Route26_Text_Sign:
    .string "RUTA 26\p"
    .string "PUERTA DE ACCESO DE LA\n"
    .string "LIGA POKéMON$"

