ViridianCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_EventScript_CityEnter
	.byte 0

ViridianCity_EventScript_CityEnter::
	setflag FLAG_VISITED_VIRIDIAN_CITY
	end

ViridianCity_EventScript_Gramps::
	lock
	faceplayer
	msgbox ViridianCity_Text_CoffeeGramps_Question, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, ViridianCity_EventScript_GrampsDoubted
	msgbox ViridianCity_Text_CoffeeGramps_Believed, MSGBOX_DEFAULT
	closemessage
	release
	end

ViridianCity_EventScript_GrampsDoubted::
	msgbox ViridianCity_Text_CoffeeGramps_Doubted, MSGBOX_DEFAULT
	closemessage
	release
	end

VirianCity_EventScript_GymGramps::
	goto_if_set FLAG_HIDE_CINNABAR_BLUE, VirianCity_EventScript_GymGrampsBlue
	msgbox ViridianCity_Text_GrampsNearGym, MSGBOX_NPC
	end

VirianCity_EventScript_GymGrampsBlue::
	msgbox ViridianCity_Text_GrampsNearGym_BlueReturned, MSGBOX_NPC
	end

ViridianCity_EventScript_Fisher::
	goto_if_set FLAG_GOT_VIRIDIAN_TM_SLUDGE_BOMB, ViridianCity_EventScript_FisherAfter
	msgbox ViridianCity_Text_DreamEaterFisherNew, MSGBOX_NPC
	giveitem ITEM_TM_SLUDGE_BOMB
	setflag FLAG_GOT_VIRIDIAN_TM_SLUDGE_BOMB
	end

ViridianCity_EventScript_FisherAfter::
	msgbox ViridianCity_Text_DreamEaterFisher_GotTM, MSGBOX_NPC
	end

ViridianCity_EventScript_Youngster::
	msgbox ViridianCity_Text_Youngster, MSGBOX_NPC
	end

ViridianCity_EventScript_CitySign::
	msgbox ViridianCity_Text_WelcomeSign, MSGBOX_SIGN
	end

ViridianCity_EventScript_CitySign2::
	msgbox ViridianCity_Text_Sign, MSGBOX_SIGN
	end

ViridianCity_EventScript_GymSign::
	msgbox ViridianCity_Text_GymSign, MSGBOX_SIGN
	end

ViridianCity_Text_CoffeeGramps_Question:
	.string "¡Oye, chico! Me tomé un espresso\n"
	.string "doble ¡y estoy eléctrico!\p"
	.string "Necesito hablar con alguien, ¡así que\n"
	.string "tú servirás!\p"
	.string "Quizá no lo parezca, pero yo era un\n"
	.string "experto capturando POKéMON.\p"
	.string "¿Me crees?$"

ViridianCity_Text_CoffeeGramps_Believed:
	.string "Bien, bien. ¡Sí, yo era alguien\n"
	.string "fuera de lo común, deja que te\l"
	.string "cuente!$"

ViridianCity_Text_CoffeeGramps_Doubted:
	.string "¿Qué? ¡Mocoso!\p"
	.string "Si fuera un poco más joven, te\n"
	.string "enseñaría un par de cosas. ¡Humph!$"

ViridianCity_Text_GrampsNearGym:
	.string "Este GIMNASIO no tuvo LÍDER\n"
	.string "hasta hace poco.\p"
	.string "Un joven de PALLET se volvió el\n"
	.string "LÍDER, pero suele estar fuera.$"

ViridianCity_Text_GrampsNearGym_BlueReturned:
	.string "¿Vas a luchar contra el\n"
	.string "LÍDER?\p"
	.string "Buena suerte. La necesitarás.$"

ViridianCity_Text_DreamEaterFisherNew:
	.string "…Zzzzz…\p" 
	.string "¡Bostezo!\p"
	.string "Debí quedarme dormido al sol.\p"
	.string "¿Qué? ¿Te recuerdo a alguien?\p"
	.string "No sé, ten, toma esto.$"


ViridianCity_Text_DreamEaterFisher_GotTM::
	.string "…Zzzzz…$"

ViridianCity_Text_DreamEaterFisher:
	.string "¡Bostezo!\p"
	.string "Debí quedarme dormido al sol.\p"
	.string "…Soñé que un DROWZEE se comía\n"
	.string "mi sueño. Raro, ¿no?\p"
	.string "¿Eh? ¿Qué es esto?\p"
	.string "¿De dónde salió esta MT?\p"
	.string "¡Qué miedo! Ten, puedes quedarte\n"
	.string "con esta MT.$"

ViridianCity_Text_DreamEaterFisher_GotDreamEater:
	.string "La MT42 tiene COMESUEÑOS…\p"
	.string "…Zzzzz…$"

ViridianCity_Text_Youngster:
	.string "Oí que hay muchos objetos\n"
	.string "en el BOSQUE VERDE.$"

ViridianCity_Text_Sign:
	.string "CIUDAD VERDE\p"
	.string "El Paraíso Eternamente Verde$"

ViridianCity_Text_GymSign:
	.string "GIMNASIO POKéMON CIUDAD VERDE\n"
	.string "LÍDER: …\p"
	.string "El resto es ilegible…$"

ViridianCity_Text_WelcomeSign:
	.string "BIENVENIDO A CIUDAD VERDE,\p"
	.string "LA PUERTA A LA MESETA AÑIL$"

ViridianCity_Text_TrainerHouseSign:
	.string "CASA DEL ENTRENADOR\p"
	.string "Club de Batallas de Élite$"
