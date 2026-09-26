Route13_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route13_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route13_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route13_EventScript_Alex::
	trainerbattle_single TRAINER_ALEX Route13_Text_PokefanmAlexSeen, Route13_Text_PokefanmAlexBeaten
	msgbox Route13_Text_PokefanmAlexAfterBattle, MSGBOX_AUTOCLOSE
	end

Route13_EventScript_Joshua::
	trainerbattle_single TRAINER_JOSHUA Route13_Text_PokefanmJoshuaSeen, Route13_Text_PokefanmJoshuaBeaten
	msgbox Route13_Text_PokefanmJoshuaAfterBattle, MSGBOX_AUTOCLOSE
	end

Route13_EventScript_Perry::
	trainerbattle_single TRAINER_PERRY Route13_Text_BirdKeeperPerrySeen, Route13_Text_BirdKeeperPerryBeaten
	msgbox Route13_Text_BirdKeeperPerryAfterBattle, MSGBOX_AUTOCLOSE
	end

Route13_EventScript_Bret::
	trainerbattle_single TRAINER_BRET Route13_Text_BirdKeeperBretSeen, Route13_Text_BirdKeeperBretBeaten
	msgbox Route13_Text_BirdKeeperBretAfterBattle, MSGBOX_AUTOCLOSE
	end

Route13_EventScript_Kenny::
	trainerbattle_single TRAINER_KENNY Route13_Text_HikerKennySeen, Route13_Text_HikerKennyBeaten
	msgbox Route13_Text_HikerKennyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route13_EventScript_TrainerTips::
	msgbox Route13_Text_TrainerTips, MSGBOX_SIGN
	end

Route13_EventScript_RouteSign::
	msgbox Route13_Text_Sign, MSGBOX_SIGN
	end

Route13_EventScript_DirectionsSign::
	msgbox Route13_Text_DirectionsSign, MSGBOX_SIGN
	end

Route13_Text_PokefanmAlexSeen:
	.string "¡Inclínate ante mis POKéMON reales!$"

Route13_Text_PokefanmAlexBeaten:
	.string "¡Cómo... cómo te atreves a burlarte!$"

Route13_Text_PokefanmAlexAfterBattle:
	.string "¿Acaso no todos desean ser\n"
	.string "reyes algún día?$"

Route13_Text_PokefanmJoshuaSeen:
	.string "¡Nihihi! ¿Quieres luchar contra\n"
	.string "mi banda de PIKACHU?$"

Route13_Text_PokefanmJoshuaBeaten:
	.string "¡PI-PIKACHU!$"

Route13_Text_PokefanmJoshuaAfterBattle:
	.string "Parece que tienes muchos\n"
	.string "POKéMON, pero PIKACHU\l"
	.string "sigue siendo el mejor.$"

Route13_Text_BirdKeeperPerrySeen:
	.string "La agilidad es la clave de los\n"
	.string "POKéMON ave.$"

Route13_Text_BirdKeeperPerryBeaten:
	.string "Me venciste con tu velocidad...$"

Route13_Text_BirdKeeperPerryAfterBattle:
	.string "Tus POKéMON están muy bien-\n"
	.string "entrenados.$"

Route13_Text_BirdKeeperBretSeen:
	.string "Mira mis POKéMON. Mira sus\n"
	.string "colores y su\l"
	.string "plumaje.$"

Route13_Text_BirdKeeperBretBeaten:
	.string "¡Rayos! ¡No es suficiente!$"

Route13_Text_BirdKeeperBretAfterBattle:
	.string "Si los aseas, los POKéMON se\n"
	.string "ponen felices.$"

Route13_Text_HikerKennySeen:
	.string "Debo ir al TÚNEL ROCK para\n"
	.string "atrapar un ONIX.$"

Route13_Text_HikerKennyBeaten:
	.string "Perdí...$"

Route13_Text_HikerKennyAfterBattle:
	.string "Parece que el relieve no\n"
	.string "cambia.\p"
	.string "Pero en realidad cambia, poco\n"
	.string "a poco.$"

Route13_Text_TrainerTips:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "¡Mira! Ahí mismo, al lado\n"
	.string "izquierdo del poste.$"

Route13_Text_Sign:
	.string "RUTA 13\p"
	.string "NORTE AL PUENTE SILENCIO$"

Route13_Text_DirectionsSign:
	.string "NORTE A PUEBLO LAVANDA\p"
	.string "OESTE A CIUDAD FUCHSIA$"

