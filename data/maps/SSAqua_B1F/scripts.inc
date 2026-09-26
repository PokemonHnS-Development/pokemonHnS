.set LOCALID_SSAQUA_B1F_SAILORLOOKING, 10

SSAqua_B1F_MapScripts::
	.byte 0

SSAqua_B1F_EventScript_Trigger::
	lock
	turnobject LOCALID_SSAQUA_B1F_SAILORLOOKING, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox SSAqua_B1F_Text_FastShipOnDutySailor, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0 
	turnobject LOCALID_SSAQUA_B1F_SAILORLOOKING, DIR_SOUTH
	release
	end

SSAqua_B1F_EventScript_SailorLookingForBuddy::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SSAQUA_SAILOR, SSAqua_B1F_EventScript_SailorLookingFoundBuddy
	msgbox SSAqua_B1F_Text_FastShipOnDutySailor, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_B1F_EventScript_SailorLookingFoundBuddy::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorThanks, MSGBOX_DEFAULT
	goto_if_lt VAR_SSAQUA_STATE, 5, SSAqua_B1F_EventScript_SailorGirl
	closemessage
	release
	end
SSAqua_B1F_EventScript_SailorGirl::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorSawGirl, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_B1F_EventScript_SleepySailor::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorDirections, MSGBOX_NPC
	end

SSAqua_B1F_EventScript_Barfcan::
	msgbox SSAqua_B1F_Text_BarfCan, MSGBOX_SIGN
	end

SSAqua_B1F_Text_BarfCan:
    .string "¡Qué asco!\n"
    .string "¡No debí mirar!$"

SSAqua_B1F_Text_FastShipOnDutySailor:
	.string "Hola, chico. ¿Podrías\n"
	.string "buscar a mi compañero?\p"
	.string "Está perdiendo el tiempo,\n"
	.string "¡ese vago!\p"
	.string "Quiero ir por él, pero ahora\n"
	.string "estoy de servicio.$"

SSAqua_B1F_Text_FastShipOnDutySailorRefused:
	.string "Vaya...\p"
	.string "El CAPITÁN estará furioso...$"

SSAqua_B1F_Text_FastShipOnDutySailorThanks:
	.string "¡Gracias! Le regañé bien\n"
	.string "para que deje de holgazanear!$"

SSAqua_B1F_Text_FastShipOnDutySailorSawGirl:
	.string "¿Una niña?\p"
	.string "Creo que la vi pasar por aquí.$"

SSAqua_B1F_Text_FastShipOnDutySailorDirections:
	.string "El comedor está más adelante.\p"
	.string "Las escaleras del final van a\n"
	.string "la cabina del CAPITÁN.$"

SSAqua_B1F_EventScript_Jeff::
	trainerbattle_single TRAINER_JEFF SSAqua_B1F_Text_SailorJeffSeen, SSAqua_B1F_Text_SailorJeffBeaten
	msgbox SSAqua_B1F_Text_SailorJeffAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorJeffSeen:
	.string "Nada supera una batalla\n"
	.string "en mi tiempo de descanso.$"

SSAqua_B1F_Text_SailorJeffBeaten:
	.string "¡Gane o pierda, acabó mi descanso!$"

SSAqua_B1F_Text_SailorJeffAfter:
	.string "Supongo que no ganaré si no me\n"
	.string "tomo esto en serio.$"

SSAqua_B1F_EventScript_Debra::
	trainerbattle_single TRAINER_DEBRA SSAqua_B1F_Text_PicnickerDebraSeen, SSAqua_B1F_Text_PicnickerDebraBeaten
	msgbox SSAqua_B1F_Text_PicnickerDebraAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_PicnickerDebraSeen:
	.string "Estoy aburrido. ¿Quieres luchar?$"

SSAqua_B1F_Text_PicnickerDebraBeaten:
	.string "¡Ay! ¡Eres demasiado fuerte!$"

SSAqua_B1F_Text_PicnickerDebraAfter:
	.string "SAFFRON, CELADON... Oigo que hay\n"
	.string "muchas ciudades grandes en KANTO.$"

SSAqua_B1F_EventScript_Fritz::
	trainerbattle_single TRAINER_FRITZ SSAqua_B1F_Text_JugglerFritzSeen, SSAqua_B1F_Text_JugglerFritzBeaten
	msgbox SSAqua_B1F_Text_JugglerFritzAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_JugglerFritzSeen:
	.string "Uff... ¡Tengo mareos!$"

SSAqua_B1F_Text_JugglerFritzBeaten:
	.string "Ya no puedo moverme...$"

SSAqua_B1F_Text_JugglerFritzAfter:
	.string "No más barcos para mí.\n"
	.string "La próxima,\p"
	.string "iré en el MAGNET TRAIN.$"

SSAqua_B1F_EventScript_Garrett::
	trainerbattle_single TRAINER_GARRETT SSAqua_B1F_Text_SailorGarrettSeen, SSAqua_B1F_Text_SailorGarrettBeaten
	msgbox SSAqua_B1F_Text_SailorGarrettAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorGarrettSeen:
	.string "¡Aquí es donde trabajamos nosotros!$"

SSAqua_B1F_Text_SailorGarrettBeaten:
	.string "Perdí en mi propio campo...$"

SSAqua_B1F_Text_SailorGarrettAfter:
	.string "Llevamos pasajeros distintos\n"
	.string "de CIUDAD VERMILIAN a\p"
	.string "CIUDAD OLIVO.$"

SSAqua_B1F_EventScript_Jonah::
	trainerbattle_single TRAINER_JONAH SSAqua_B1F_Text_FisherJonahSeen, SSAqua_B1F_Text_FisherJonahBeaten
	msgbox SSAqua_B1F_Text_FisherJonahAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_FisherJonahSeen:
	.string "¡Aunque estamos en el mar,\n"
	.string "no puedo pescar!\p"
	.string "¡Qué aburrido! ¡Luchemos!$"

SSAqua_B1F_Text_FisherJonahBeaten:
	.string "Ya... ya no estoy aburrido...$"

SSAqua_B1F_Text_FisherJonahAfter:
	.string "Pienso pescar desde el\n"
	.string "muelle de VERMILIAN.$"

SSAqua_B1F_EventScript_Wai::
	trainerbattle_single TRAINER_WAI SSAqua_B1F_Text_BlackbeltWaiSeen, SSAqua_B1F_Text_BlackbeltWaiBeaten
	msgbox SSAqua_B1F_Text_BlackbeltWaiAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_BlackbeltWaiSeen:
	.string "¡Fortalezco mis piernas al\n"
	.string "resistir\p"
	.string "el balanceo del barco!$"

SSAqua_B1F_Text_BlackbeltWaiBeaten:
	.string "¡Me han dejado tambaleando!$"

SSAqua_B1F_Text_BlackbeltWaiAfter:
	.string "No hallé al KARATE KING\n"
	.string "en JOHTO.\p"
	.string "Debería estar entrenando en\n"
	.string "alguna cueva.$"

SSAqua_B1F_EventScript_Kenneth::
	trainerbattle_single TRAINER_KENNETH SSAqua_B1F_Text_SailorKennethSeen, SSAqua_B1F_Text_SailorKennethBeaten
	msgbox SSAqua_B1F_Text_SailorKennethAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorKennethSeen:
	.string "¡Soy un marinero!\p"
	.string "Pero entreno POKéMON para\n"
	.string "¡ser el CAMPEÓN!$"

SSAqua_B1F_Text_SailorKennethBeaten:
	.string "Es obvio que me falta entreno…$"

SSAqua_B1F_Text_SailorKennethAfter:
	.string "¡Ocho MEDALLAS! Eso prueba\n"
	.string "que venciste a los\p"
	.string "LÍDERES de GIMNASIO.\p"
	.string "¡Por eso eres tan bueno!$"

SSAqua_B1F_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY SSAqua_B1F_Text_TeacherShirleySeen, SSAqua_B1F_Text_TeacherShirleyBeaten
	msgbox SSAqua_B1F_Text_TeacherShirleyAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_TeacherShirleySeen:
	.string "¡No pongas un dedo sobre\n"
	.string "mis alumnos!$"

SSAqua_B1F_Text_TeacherShirleyBeaten:
	.string "¡Aaack!$"

SSAqua_B1F_Text_TeacherShirleyAfter:
	.string "Estamos de excursión en las\n"
	.string "RUINAS fuera de CIUDAD MALVA.$"

SSAqua_B1F_EventScript_Nate::
	trainerbattle_single TRAINER_NATE SSAqua_B1F_Text_SchoolboyNateSeen, SSAqua_B1F_Text_SchoolboyNateBeaten
	msgbox SSAqua_B1F_Text_SchoolboyNateAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SchoolboyNateSeen:
	.string "¿Conoces las RUINAS ALFA?$"

SSAqua_B1F_Text_SchoolboyNateBeaten:
	.string "¡Yaargh!$"

SSAqua_B1F_Text_SchoolboyNateAfter:
	.string "Las radios captan señales raras\n"
	.string "en las RUINAS.$"

SSAqua_B1F_EventScript_Ricky::
	trainerbattle_single TRAINER_RICKY SSAqua_B1F_Text_SchoolboyRickySeen, SSAqua_B1F_Text_SchoolboyRickyBeaten
	msgbox SSAqua_B1F_Text_SchoolboyRickyAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SchoolboyRickySeen:
	.string "Hay unos paneles de piedra raros\n"
	.string "en las RUINAS ALFA.$"

SSAqua_B1F_Text_SchoolboyRickyBeaten:
	.string "¡Me derrotaron!$"

SSAqua_B1F_Text_SchoolboyRickyAfter:
	.string "Leí que hay cuatro de esos\n"
	.string "paneles de piedra.$"

