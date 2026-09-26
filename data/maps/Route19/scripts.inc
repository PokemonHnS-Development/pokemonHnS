Route19_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route19_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route19_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route19_EventScript_Harold::
	trainerbattle_single TRAINER_HAROLD Route19_Text_SwimmermHaroldSeen, Route19_Text_SwimmermHaroldBeaten
	msgbox Route19_Text_SwimmermHaroldAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Tucker::
	trainerbattle_single TRAINER_TUCKER Route19_Text_SwimmermTuckerSeen, Route19_Text_SwimmermTuckerBeaten
	msgbox Route19_Text_SwimmermTuckerAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Dawn::
	trainerbattle_single TRAINER_DAWN Route19_Text_SwimmerfDawnSeen, Route19_Text_SwimmerfDawnBeaten
	msgbox Route19_Text_SwimmerfDawnAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Jerome::
	trainerbattle_single TRAINER_JEROME Route19_Text_SwimmermJeromeSeen, Route19_Text_SwimmermJeromeBeaten
	msgbox Route19_Text_SwimmermJeromeAfterBattle, MSGBOX_AUTOCLOSE
	end

Route19_EventScript_Fatman::
	goto_if_unset FLAG_DEFEATED_CINNABAR_ISLAND_GYM, Route19_EventScript_FatmanBefore
	msgbox Route19_Text_Fisher1_RocksCleared, MSGBOX_NPC
	end

Route19_EventScript_FatmanBefore::
	msgbox Route19_Text_Fisher2, MSGBOX_NPC
	end

Route19_EventScript_Sign::
	msgbox Route19_Text_Sign, MSGBOX_SIGN
	end

Route19_EventScript_SwimSign::
	msgbox Route19_Text_CarefulSwimmingSign, MSGBOX_SIGN
	end

CherryGroveCity_EventScript_Kingler::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KINGLER, CRY_MODE_NORMAL
	msgbox Route19_Text_Kingler, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route19_EventScript_Fisher::
	goto_if_unset FLAG_DEFEATED_CINNABAR_ISLAND_GYM, Route19_EventScript_FisherBefore
	msgbox Route19_Text_Fisher2_RocksCleared, MSGBOX_NPC
	end

Route19_EventScript_FisherBefore::
	msgbox Route19_Text_FisherBefore, MSGBOX_NPC
	end

Route19_Text_SwimmermHaroldSeen:
	.string "¿Alguna vez nadaste en el mar\n"
	.string "por la noche?$"

Route19_Text_SwimmermHaroldBeaten:
	.string "Glub…$"

Route19_Text_SwimmermHaroldAfterBattle:
	.string "De noche, el mar se vuelve negro.\n"
	.string "Sientes que te tragará.$"

Route19_Text_SwimmermTuckerSeen:
	.string "Jadeo… Solo… un poco…\p"
	.string "más… hasta… FUCHSIA…$"

Route19_Text_SwimmermTuckerBeaten:
	.string "¡Me ahogo!$"

Route19_Text_SwimmermTuckerAfterBattle:
	.string "Le... pedí a mi novia que nadara\n"
	.string "hasta FUCHSIA... ¡Gasp!$"

Route19_Text_SwimmerfDawnSeen:
	.string "¡Me dan asco los cobardes!$"

Route19_Text_SwimmerfDawnBeaten:
	.string "Podría ganarte nadando…$"

Route19_Text_SwimmerfDawnAfterBattle:
	.string "Es un nado rápido entre FUCHSIA\n"
	.string "y LAS ISLAS ESPUMA...\p"
	.string "¡Cielos, mi novio es un gran hombre\n"
	.string "de papel! ¡Qué miedoso!$"

Route19_Text_SwimmermJeromeSeen:
	.string "¿Nadar? Soy malísimo en eso.\p"
	.string "Solo chapoteo en estas aguas\n"
	.string "poco profundas.$"

Route19_Text_SwimmermJeromeBeaten:
	.string "Pensé que podría ganar.$"

Route19_Text_SwimmermJeromeAfterBattle:
	.string "Quizá sea malo nadando, pero\n"
	.string "amo el mar.$"

Route19_Text_Fisher1:
	.string "Lo siento. El camino está cerrado\n"
	.string "por obras.\p"
	.string "Si quieres ir a CINNABAR,\n"
	.string "mejor ve al sur desde PUEBLO\n"
	.string "PALETA.$"

Route19_Text_Kingler:
	.string "KINGLER: ¡KEEEEEEEEEEEE!$"

Route19_Text_Fisher1_RocksCleared:
	.string "Estoy sudado. ¡Hora de nadar!$"

Route19_Text_Fisher2:
	.string "Rayos, ¡un KINGLER bloquea la\n"
	.string "playa!$"

Route19_Text_FisherBefore:
	.string "No pesques hasta que esos KINGLER\n"
	.string "se vayan.$"

Route19_Text_Fisher2_RocksCleared:
	.string "¡Esos KINGLER al fin se fueron!\p"
	.string "Ya puedo volver a pescar.$"

Route19_Text_Sign:
	.string "RUTA 19\p"
	.string "CIUDAD FUCHSIA - ISLAS SEAFOAM$"

Route19_Text_CarefulSwimmingSign:
	.string "Ten cuidado si nadas hacia las\n"
	.string "ISLAS ESPUMA.\p"
	.string "POLICÍA DE FUCHSIA$"

