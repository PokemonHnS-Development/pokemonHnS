NationalPark_Normal_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NationalPark_Normal_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

NationalPark_Normal_OnTransition: 
	callnative SetTimeBasedEncounters
	end

NationalPark_Normal_EventScript_Lass::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Youngster1::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Youngster2::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Teacher2::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Teacher2, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	release
	end

NationalPark_Normal_EventScript_TeacherQuickclaw::
	lock
	faceplayer
	goto_if_set FLAG_GOT_QUICK_CLAW, NationalPark_Normal_EventScript_TeacherQuickclaw2
	msgbox NationalPark_Normal_Text_Teacher1, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setflag FLAG_GOT_QUICK_CLAW
NationalPark_Normal_EventScript_TeacherQuickclaw2::
	msgbox NationalPark_Normal_Text_Teacher1_QuickClaw, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Persian::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PERSIAN, CRY_MODE_NORMAL
	msgbox NationalPark_Normal_Text_Persian, MSGBOX_DEFAULT
	waitmoncry
	release
	end



NationalPark_Normal_Text_Lass:
	.string "¡Mira! ¡Mira mi bolso!\p"
	.string "Imprimí mis favoritos de la\n"
	.string "POKéDEX y los pegué en mi bolso.$"

NationalPark_Normal_Text_PokefanF:
	.string "Es una CARTA de mi hija.\n"
	.string "Me pone muy feliz.$"

NationalPark_Normal_Text_Teacher1:
	.string "¡Presta atención, por favor!\p"
	.string "...Vaya, debo dejar de pensar\n"
	.string "como profesor todo el tiempo.\p"
	.string "Debes ser un entrenador POKéMON.\p"
	.string "Como te esfuerzas tanto, quiero\n"
	.string "darte esto.$"

NationalPark_Normal_Text_Teacher1_QuickClaw:
	.string "Que un POKéMON lleve esa GARRA RÁPIDA.\p"
	.string "A veces atacará primero\n"
	.string "en la batalla.$"

NationalPark_Normal_Text_Youngster1:
	.string "Juego con calcomanías que imprimí\n"
	.string "de mi POKéDEX.$"

NationalPark_Normal_Text_Youngster2:
	.string "Si gano, me quedo con la calcomanía\n"
	.string "de la POKéDEX del otro.$"

NationalPark_Normal_Text_Teacher2:
	.string "Camino por el PARQUE, pero nunca\n"
	.string "entro en la hierba.\p"
	.string "Los entrenadores siempre pelean...\p"
	.string "Habrás tenido muchas batallas.\n"
	.string "Deja que cure a tus POKéMON.$"

NationalPark_Normal_Text_Persian:
	.string "PERSIAN: ¡Fufushaa!$"

NationalPark_Normal_EventScript_Jack::
	trainerbattle_single TRAINER_JACK NationalPark_Normal_Text_SchoolboyJack1_Seen, NationalPark_Normal_Text_SchoolboyJack1_Beaten
	msgbox NationalPark_Normal_Text_SchoolboyJack_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_Beverly::
	trainerbattle_single TRAINER_BEVERLY NationalPark_Normal_Text_PokefanFBeverly1_Seen, NationalPark_Normal_Text_PokefanFBeverly1_Beaten
	msgbox NationalPark_Normal_Text_PokefanFBeverly_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM NationalPark_Normal_Text_PokefanmWilliam_Seen, NationalPark_Normal_Text_PokefanmWilliam_Beaten
	msgbox NationalPark_Normal_Text_PokefanmWilliam_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_Krise::
	trainerbattle_single TRAINER_KRISE NationalPark_Normal_Text_LassKrise_Seen, NationalPark_Normal_Text_LassKrise_Beaten
	msgbox NationalPark_Normal_Text_LassKrise_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_TM_Dig::
	finditem ITEM_TM_DIG
	end

NationalPark_Normal_EventScript_Item_Soothe_Bell::
	finditem ITEM_SOOTHE_BELL
	end

NationalPark_Normal_Text_SchoolboyJack1_Seen:
	.string "El mundo POKéMON es profundo.\p"
	.string "Aún hay muchas cosas que\n"
	.string "no sabemos.\p"
	.string "¡Pero yo sé más que tú!$"

NationalPark_Normal_Text_SchoolboyJack1_Beaten:
	.string "¿Qu-qu-qué?$"

NationalPark_Normal_Text_SchoolboyJack_After:
	.string "Hay mucho que aprender.\p"
	.string "Por ejemplo...\p"
	.string "Hay 50 tipos de MT.\p"
	.string "Los POKéMON tradeados suben más.$"

NationalPark_Normal_Text_PokefanFBeverly1_Seen:
	.string "Mis POKéMON son adorables.\p"
	.string "Déjame decirte lo orgullosa\n"
	.string "que me hacen sentir.$"

NationalPark_Normal_Text_PokefanFBeverly1_Beaten:
	.string "Puedo ganarte en orgullo, pero...$"

NationalPark_Normal_Text_PokefanFBeverly_After:
	.string "Debo admitir que tus POKéMON\n"
	.string "también son muy lindos.$"

NationalPark_Normal_Text_PokefanmWilliam_Seen:
	.string "Amamos a los POKéMON, aunque\n"
	.string "no nos quieran.\p"
	.string "Eso es ser un FAN.$"

NationalPark_Normal_Text_PokefanmWilliam_Beaten:
	.string "¡M-mis POKéMON!$"

NationalPark_Normal_Text_PokefanmWilliam_After:
	.string "Perdí la batalla, pero mi POKéMON\n"
	.string "ganó el premio a la más linda.$"

NationalPark_Normal_Text_LassKrise_Seen:
	.string "¿Hola? ¿Por qué me miras así?\p"
	.string "¿Ah, una batalla?$"

NationalPark_Normal_Text_LassKrise_Beaten:
	.string "...Hmmm...$"

NationalPark_Normal_Text_LassKrise_After:
	.string "¡Pensé que me mirabas\n"
	.string "porque soy linda!$"

NationalPark_Normal_Text_Sign_RelaxationSquare:
	.string "PLAZA DE RELAJACIÓN\n"
	.string "PARQUE NACIONAL$"

NationalPark_Normal_Text_Sign_BattleNotice:
	.string "¿Qué es este aviso?\p"
	.string "Lucha solo en la hierba.\p"
	.string "OFICINA DEL GUARDAPARQUE$"

NationalPark_Normal_Text_TrainerTips:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Imprime el CORREO abriéndolo y\n"
	.string "luego pulsando START.$"
