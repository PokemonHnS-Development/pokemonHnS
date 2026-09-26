VictoryRoad_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, VictoryRoad_B2F_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_B2F_OnTransition
	.byte 0

VictoryRoad_B2F_OnResume:
	callnative SetTimeBasedEncounters
	end

VictoryRoad_B2F_OnTransition:
	callnative SetTimeBasedEncounters
	goto_if_set FLAG_UNLOCK_BIRDS, VictoryRoad_B2F_SwitchToModern
	end

VictoryRoad_B2F_SwitchToModern::
	setmaplayoutindex LAYOUT_VICTORY_ROAD_B2F_MODERN
	end

VictoryRoad_B2F_EventScript_Vito::
	trainerbattle_single TRAINER_VITO, VictoryRoad_B2F_Text_VitoIntro, VictoryRoad_B2F_Text_VitoDefeat
	msgbox VictoryRoad_B2F_Text_VitoPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN, VictoryRoad_B2F_Text_OwenIntro, VictoryRoad_B2F_Text_OwenDefeat
	msgbox VictoryRoad_B2F_Text_OwenPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Caroline::
	trainerbattle_single TRAINER_CAROLINE, VictoryRoad_B2F_Text_CarolineIntro, VictoryRoad_B2F_Text_CarolineDefeat
	msgbox VictoryRoad_B2F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Julie::
	trainerbattle_single TRAINER_JULIE, VictoryRoad_B2F_Text_JulieIntro, VictoryRoad_B2F_Text_JulieDefeat
	msgbox VictoryRoad_B2F_Text_JuliePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Felix::
	trainerbattle_single TRAINER_NORMAN, VictoryRoad_B2F_Text_FelixIntro, VictoryRoad_B2F_Text_FelixDefeat
	msgbox VictoryRoad_B2F_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Dianne::
	trainerbattle_single TRAINER_KENJI, VictoryRoad_B2F_Text_DianneIntro, VictoryRoad_B2F_Text_DianneDefeat
	msgbox VictoryRoad_B2F_Text_DiannePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_Text_VitoIntro:
	.string "Entrené con toda mi familia,\n"
	.string "¡cada uno de nosotros!\l"
	.string "¡No perderé con nadie!$"

VictoryRoad_B2F_Text_VitoDefeat:
	.string "¡¿Mejor que mi familia?!\n"
	.string "¡¿Es eso posible?!$"

VictoryRoad_B2F_Text_VitoPostBattle:
	.string "Era mejor que todos en mi\n"
	.string "familia. Jamás perdí...\p"
	.string "Perdí mi confianza...\n"
	.string "Tal vez vuelva a casa...$"

VictoryRoad_B2F_Text_OwenIntro:
	.string "Oí que había un niño fuerte\n"
	.string "por aquí. ¿Se referían a ti?$"

VictoryRoad_B2F_Text_OwenDefeat:
	.string "¡El pequeño es fuerte!$"

VictoryRoad_B2F_Text_OwenPostBattle:
	.string "Según los rumores, ese niño\n"
	.string "fuerte es de CIUDAD PETALBURG.$"

VictoryRoad_B2F_Text_CarolineIntro:
	.string "Debes estar cansándote un poco.$"

VictoryRoad_B2F_Text_CarolineDefeat:
	.string "¡No se ve cansado para nada!$"

VictoryRoad_B2F_Text_CarolinePostBattle:
	.string "LA RUTA VICTORIA y la LIGA POKéMON\n"
	.string "son retos largos y agotadores.\l"
	.string "¡Cuidado con el cansancio!$"

VictoryRoad_B2F_Text_JulieIntro:
	.string "No te confíes solo porque tengas\n"
	.string "muchas MEDALLAS de GIMNASIO.\p"
	.string "¡Siempre habrá alguien mejor\n"
	.string "que tú!$"

VictoryRoad_B2F_Text_JulieDefeat:
	.string "¡Eres mejor que yo!$"

VictoryRoad_B2F_Text_JuliePostBattle:
	.string "Mira tus MEDALLAS y recuerda a los\n"
	.string "ENTRENADORES que has enfrentado.$"

VictoryRoad_B2F_Text_FelixIntro:
	.string "Llegué hasta aquí, pero los nervios\n"
	.string "me dan un dolor de estómago...$"

VictoryRoad_B2F_Text_FelixDefeat:
	.string "Ooh...\n"
	.string "Me duele...$"

VictoryRoad_B2F_Text_FelixPostBattle:
	.string "Me pongo tenso al saber que ya\n"
	.string "estoy cerca de la LIGA POKéMON.\p"
	.string "Hago lo posible por fingir calma.$"

VictoryRoad_B2F_Text_DianneIntro:
	.string "La élite de la élite se reúne en\n"
	.string "esta cueva.\p"
	.string "¿Qué te parece el lugar?$"

VictoryRoad_B2F_Text_DianneDefeat:
	.string "¡No me he inmutado ni un poco!$"

VictoryRoad_B2F_Text_DiannePostBattle:
	.string "¡Tienes agallas! ¡Me gusta!\n"
	.string "¡Sigue así!$"

