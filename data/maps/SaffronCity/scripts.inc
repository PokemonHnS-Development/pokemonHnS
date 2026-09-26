SaffronCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_EventScript_CityEnter
	.byte 0

SaffronCity_OnFrame::
	map_script_2 VAR_SAFFRON_CITY_STATE, 0,  SaffronCity_EventScript_BaobaCall
	.2byte 0

SaffronCity_EventScript_CityEnter::
	setflag FLAG_VISITED_SAFFRON_CITY
	end

SaffronCity_EventScript_BaobaCall::
	pokenavcall SaffronCity_Text_Baoba
	waitmessage
	delay 30
	setflag FLAG_SAFARI_ZONE_EAST_EXPANSION
	setvar VAR_SAFFRON_CITY_STATE, 1
	end

SaffronCity_Text_Baoba:
	.string "GUARDIA BAOBA: {PLAYER}!\p"
	.string "Soy el GUARDIA BAOBA.\p"
	.string "¡Llamo para decirte que la\n"
	.string "ZONA SAFARI se expandió otra vez!\p"
	.string "¡Al fin mi ZONA SAFARI está\n"
	.string "completamente terminada!\p"
	.string "Recuerdas dónde está, ¿verdad?\p"
	.string "¡Al oeste de CIUDAD ORQUIDEA!\n"
	.string "¡Nos vemos pronto!$"

SaffronCity_EventScript_Lass1A::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_EventScript_Lass1B
	msgbox SaffronCity_Text_Lass1, MSGBOX_NPC
	end

SaffronCity_EventScript_Lass1B::
	msgbox SaffronCity_Text_Lass1_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_EventScript_Lass2::
	msgbox SaffronCity_Text_Lass2, MSGBOX_NPC
	end

SaffronCity_EventScript_PokefanM::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_EventScript_PokefanM2
	msgbox SaffronCity_Text_PokefanM, MSGBOX_NPC
	end

SaffronCity_EventScript_PokefanM2::
	msgbox SaffronCity_Text_PokefanM_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_EventScript_CooltrainerM::
	msgbox SaffronCity_Text_CooltrainerM, MSGBOX_NPC
	end

SaffronCity_EventScript_CooltrainerF::
	msgbox SaffronCity_Text_CooltrainerF, MSGBOX_NPC
	end

SaffronCity_EventScript_Fisher::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_EventScript_Fisher2
	msgbox SaffronCity_Text_Fisher, MSGBOX_NPC
	end

SaffronCity_EventScript_Fisher2::
	msgbox SaffronCity_Text_Fisher_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_EventScript_Youngster1::
	msgbox SaffronCity_Text_Youngster1, MSGBOX_NPC
	end

SaffronCity_EventScript_Youngster2::
	msgbox SaffronCity_Text_Youngster2, MSGBOX_NPC
	end
SaffronCity_EventScript_CitySign::
	msgbox SaffronCity_Text_Sign, MSGBOX_SIGN
	end

SaffronCity_EventScript_GymSign::
	msgbox SaffronCity_Text_GymSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_DojoSign::
	msgbox SaffronCity_Text_FightingDojoSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_SilphCoSign::
	msgbox SaffronCity_Text_SilphCoSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_MrPsychicSign::
	msgbox SaffronCity_Text_MrPsychicHouseSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_MagnetTrainSign::
	msgbox SaffronCity_Text_MagnetTrainStationSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_Elli::
	msgbox SaffronCity_Text_Elli, MSGBOX_NPC
	end

SaffronCity_Text_Elli:
	.string "¡Amo a VULPIX! :D$"

SaffronCity_Text_Lass1:
	.string "Aquí vive una niña experta en\n"
	.string "imitar a las personas.\p"
	.string "Imita hasta a quien habla con\n"
	.string "ella. Es confuso.$"

SaffronCity_Text_Lass1_ReturnedPart:
	.string "La niña COPYCAT se veía triste.\p"
	.string "Dijo que perdió su MUÑECA POKé\n"
	.string "favorita: CLEFAIRY.$"

SaffronCity_Text_PokefanM:
	.string "¿Vienes de JOHTO?\p"
	.string "Puedes volver rápido a casa si el\n"
	.string "MAGNET TRAIN funciona.$"

SaffronCity_Text_PokefanM_ReturnedPart:
	.string "¿Vienes de JOHTO?\p"
	.string "Puedes volver rápido a casa\n"
	.string "usando el MAGNET TRAIN.$"

SaffronCity_Text_CooltrainerM:
	.string "Fui al GIMNASIO, ansioso por\n"
	.string "luchar contra entrenadores...\p"
	.string "Resulta que entré al GIMNASIO\n"
	.string "vacío de al lado.\p"
	.string "Vaya, qué vergüenza pasé.$"

SaffronCity_Text_CooltrainerF:
	.string "Esta es SILPH CO., famosa por sus\n"
	.string "productos POKéMON.\p"
	.string "Por eso el TEAM ROCKET quiso\n"
	.string "apoderarse de la empresa.$"

SaffronCity_Text_Fisher:
	.string "Masticar... Masticar...\p"
	.string "Oigo que hay graves problemas\n"
	.string "en la CENTRAL ELÉCTRICA.\p"
	.string "Masticar... Masticar...$"

SaffronCity_Text_Fisher_ReturnedPart:
	.string "Masticar... Masticar...\p"
	.string "Oigo que hubo graves problemas en la\n"
	.string "CENTRAL ELÉCTRICA.\p"
	.string "Masticar... ¡Ah, estoy lleno!$"

SaffronCity_Text_Youngster1:
	.string "Entrar en un callejón por primera\n"
	.string "vez me pone algo ansioso.$"

SaffronCity_Text_Youngster2:
	.string "Hay un lugar llamado CASA DEL\n"
	.string "ENTRENADOR en VIRIDIAN donde se\l"
	.string "reúnen entrenadores de todo lado.$"

SaffronCity_Text_Lass2:
	.string "Nuestra ciudad salió en un programa\n"
	.string "de radio.\p"
	.string "Es lindo oír elogios, pero también\n"
	.string "da un poco de vergüenza.\l"
	.string "$"

SaffronCity_Text_Sign:
	.string "CIUDAD AZURIA\p"
	.string "Tierra Dorada y Brillante del Comercio$"

SaffronCity_Text_GymSign:
	.string "CIUDAD AZURIA\n"
	.string "GIMNASIO POKéMON\l"
	.string "LÍDER: SABRINA\p"
	.string "¡La Maestra de los POKéMON Psíquicos!$"

SaffronCity_Text_FightingDojoSign:
	.string "¡Bienvenidos todos!\n"
	.string "DOJO DE LUCHA$"

SaffronCity_Text_SilphCoSign:
	.string "SILPH CO.\n"
	.string "EDIFICIO DE OFICINAS$"

SaffronCity_Text_MrPsychicHouseSign:
	.string "CASA DEL\n"
	.string "SR. PSÍQUICO$"

SaffronCity_Text_MagnetTrainStationSign:
	.string "CIUDAD AZAFRÁN\n"
	.string "ESTACIÓN DEL TREN MAGNÉTICO$"
