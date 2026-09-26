Route8_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route8_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route8_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route8_EventScript_Dwayne::
	trainerbattle_single TRAINER_DWAYNE, Route8_Text_BikerDwayneSeen, Route8_Text_BikerDwayneBeaten
	msgbox Route8_Text_BikerDwayneAfter, MSGBOX_AUTOCLOSE
	end

Route8_EventScript_Harris::
	trainerbattle_single TRAINER_HARRIS, Route8_Text_BikerHarrisSeen, Route8_Text_BikerHarrisBeaten
	msgbox Route8_Text_BikerHarrisAfter, MSGBOX_AUTOCLOSE
	end

Route8_EventScript_Zeke::
	trainerbattle_single TRAINER_ZEKE, Route8_Text_BikerZekeSeen, Route8_Text_BikerZekeBeaten
	msgbox Route8_Text_BikerZekeAfter, MSGBOX_AUTOCLOSE
	end

Route8_EventScript_Sam::
	trainerbattle_single TRAINER_SAM, Route8_Text_SupernerdSamSeen, Route8_Text_SupernerdSamBeaten
	msgbox Route8_Text_SupernerdSamAfter, MSGBOX_AUTOCLOSE
	end

Route8_EventScript_Tom::
	trainerbattle_single TRAINER_TOM, Route8_Text_SupernerdTomSeen, Route8_Text_SupernerdTomBeaten
	msgbox Route8_Text_SupernerdTomAfter, MSGBOX_AUTOCLOSE
	end

Route8_Text_BikerDwayneSeen:
	.string "Somos el grupo de ENTRENADORES de la\n"
	.string "FEDERACIÓN POKéMON de KANTO.\p"
	.string "¡Te pasaremos por encima!$"

Route8_Text_BikerDwayneBeaten:
	.string "¡L-lo siento!$"

Route8_Text_BikerDwayneAfter:
	.string "¡La FEDERACIÓN POKéMON de KANTO\n"
	.string "jamás caerá!$"

Route8_Text_BikerHarrisSeen:
	.string "¡La policía cerró nuestro\n"
	.string "CAMINO SUBTERRÁNEO!\p"
	.string "¡Eso me enfurece!$"

Route8_Text_BikerHarrisBeaten:
	.string "¡P-perdóname!$"

Route8_Text_BikerHarrisAfter:
	.string "Derrotado por un novato de\n"
	.string "JOHTO…$"

Route8_Text_BikerZekeSeen:
	.string "¡Somos la FEDERACIÓN POKéMON de\n"
	.string "KANTO!\n"
	.string "¡Así es!$"

Route8_Text_BikerZekeBeaten:
	.string "¡Ay! ¡Lo siento!$"

Route8_Text_BikerZekeAfter:
	.string "Trataremos de no molestar a nadie\n"
	.string "de ahora en adelante…$"

Route8_Text_SupernerdSamSeen:
	.string "¿Cómo funciona el MAGNET TRAIN?$"

Route8_Text_SupernerdSamBeaten:
	.string "Solo quiero ver el MAGNET\n"
	.string "TRAIN…$"

Route8_Text_SupernerdSamAfter:
	.string "¡El poder de los imanes es genial!$"

Route8_Text_SupernerdTomSeen:
	.string "Hm… Tienes muchas GYM BADGES.$"

Route8_Text_SupernerdTomBeaten:
	.string "Como pensaba… ¡Eres fuerte!$"

Route8_Text_SupernerdTomAfter:
	.string "Las GYM BADGES dan ventajas en\n"
	.string "las batallas.$"

Route8_Text_LockedDoor:
	.string "Está cerrado…$"

Route8_Text_UndergroundPathSign:
	.string "El volante está roto.\p"
	.string "Es imposible leerlo…$"
