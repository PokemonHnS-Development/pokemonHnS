Route17_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route17_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route17_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route17_EventScript_Riley::
	trainerbattle_single TRAINER_RILEY Route17_Text_BikerRileySeen, Route17_Text_BikerRileyBeaten
	msgbox Route17_Text_BikerRileyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route17_EventScript_Joel::
	trainerbattle_single TRAINER_JOEL Route17_Text_BikerJoelSeen, Route17_Text_BikerJoelBeaten
	msgbox Route17_Text_BikerJoelAfterBattle, MSGBOX_AUTOCLOSE
	end

Route17_EventScript_Glenn::
	trainerbattle_single TRAINER_GLENN Route17_Text_BikerGlennSeen, Route17_Text_BikerGlennBeaten
	msgbox Route17_Text_BikerGlennAfterBattle, MSGBOX_AUTOCLOSE
	end

Route17_EventScript_Charles::
	trainerbattle_single TRAINER_CHARLES Route17_Text_BikerCharlesSeen, Route17_Text_BikerCharlesBeaten
	msgbox Route17_Text_BikerCharlesAfterBattle, MSGBOX_AUTOCLOSE
	end

Route17_Text_BikerRileySeen:
	.string "¡Oye, tú! Eres de JOHTO, ¿no?$"

Route17_Text_BikerRileyBeaten:
	.string "¡Vaya, eres fuerte!$"

Route17_Text_BikerRileyAfterBattle:
	.string "¡No te creas mucho, novato de JOHTO!$"

Route17_Text_BikerJoelSeen:
	.string "¡Guau! ¡Qué BICYCLE tan genial!$"

Route17_Text_BikerJoelBeaten:
	.string "Pero no solo te ves genial…$"

Route17_Text_BikerJoelAfterBattle:
	.string "Me veo genial, pero soy débil, así\n"
	.string "que no lo soy tanto.\p"
	.string "Debo entrenar más…$"

Route17_Text_BikerGlennSeen:
	.string "¡Hola! ¿Quieres una batalla veloz?$"

Route17_Text_BikerGlennBeaten:
	.string "¡Cielos! ¡Tienes un torque increíble!$"

Route17_Text_BikerGlennAfterBattle:
	.string "Andar sin manos se considera\n"
	.string "genial en la RUTA CICLISTA.$"

Route17_Text_BikerCharlesSeen:
	.string "¡Somos estrellas de la ruta!$"

Route17_Text_BikerCharlesBeaten:
	.string "¡Agh! ¡Choqué y caí!$"

Route17_Text_BikerCharlesAfterBattle:
	.string "¡Manejar así causa accidentes!\n"
	.string "¡Ve con calma!$"

