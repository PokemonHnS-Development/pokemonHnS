Route18_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route18_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route18_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route18_EventScript_Boris::
	trainerbattle_single TRAINER_BORIS Route18_Text_BirdKeeperBorisSeen, Route18_Text_BirdKeeperBorisBeaten
	msgbox Route18_Text_BirdKeeperBorisAfterBattle, MSGBOX_AUTOCLOSE
	end

Route18_EventScript_Bob::
	trainerbattle_single TRAINER_BOB Route18_Text_BirdKeeperBobSeen, Route18_Text_BirdKeeperBobBeaten
	msgbox Route18_Text_BirdKeeperBobAfterBattle, MSGBOX_AUTOCLOSE
	end

Route18_EventScript_Sign::
	msgbox Route18_Text_Sign, MSGBOX_SIGN
	end

Route18_Text_BirdKeeperBorisSeen:
	.string "Si buscas POKéMON,\n"
	.string "busca en la hierba alta.$"

Route18_Text_BirdKeeperBorisBeaten:
	.string "¡Ayieee!$"

Route18_Text_BirdKeeperBorisAfterBattle:
	.string "Como eres tan fuerte, debe ser\n"
	.string "divertido luchar.$"

Route18_Text_BirdKeeperBobSeen:
	.string "La CICLOVÍA es un camino corto\n"
	.string "hacia CIUDAD CELADON.$"

Route18_Text_BirdKeeperBobBeaten:
	.string "…¡Uff!$"

Route18_Text_BirdKeeperBobAfterBattle:
	.string "Si no tienes una BICYCLE,\n"
	.string "no puedes usar el\l"
	.string "atajo.$"

Route18_Text_Sign:
	.string "RUTA 18\p"
	.string "CIUDAD CELADON - CIUDAD FUCHSIA$"
