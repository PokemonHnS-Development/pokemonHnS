.set LOCALID_CERULEAN_WOMAN, 2
.set LOCALID_CERULEAN_SLOWBRO, 3

CeruleanCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCity_EventScript_CityEnter
	.byte 0

CeruleanCity_EventScript_CityEnter::
	setflag FLAG_VISITED_CERULEAN_CITY
	end

CeruleanCity_EventScript_CooltrainerM1::
	goto_if_set FLAG_RETURNED_MACHINE_PART, CeruleanCity_EventScript_CooltrainerMReturnedPart
	msgbox CeruleanCity_Text_CooltrainerM1, MSGBOX_NPC
	end

CeruleanCity_EventScript_CooltrainerMReturnedPart::
	msgbox CeruleanCity_Text_CooltrainerM2, MSGBOX_NPC
	end

CeruleanCity_EventScript_Boy::
	msgbox CeruleanCity_Text_SuperNerd, MSGBOX_NPC
	end

CeruleanCity_EventScript_Guard::
	msgbox CeruleanCity_Text_ThisIsCeruleanCave, MSGBOX_NPC
	end

CeruleanCity_Text_ThisIsCeruleanCave::
    .string "Esta es la CAVERNA AZUL.\p"
    .string "Viven POKéMON muy fuertes\n"
    .string "allí dentro.\p"
    .string "Se requiere un TRAINER muy especial\n"
    .string "para poder entrar.\p"
    .string "Para empezar, debes ser lo bastante\n"
    .string "fuerte para ser el CAMPEÓN de la\l"
    .string "LIGA POKéMON de KANTO.\p"
    .string "Y tendrías que haber logrado\n"
    .string "un gran hazaña.$"

CeruleanCity_Text_CooltrainerM1:
	.string "¿La CENTRAL ELÉCTRICA de KANTO?\p"
	.string "Está al final de la RUTA 9, el\n"
	.string "camino que va al este desde aquí.\p"
	.string "Creo que hubo un accidente de\n"
	.string "algún tipo allí.$"

CeruleanCity_Text_CooltrainerM2:
	.string "¿Coleccionas cada especie\n"
	.string "de POKéMON?\p"
	.string "Debe ser un gran desafío,\n"
	.string "¡pero suena divertido!$"

CeruleanCity_Text_SuperNerd:
	.string "El CABO al norte es un buen\n"
	.string "lugar para citas.\p"
	.string "¡A las chicas les gusta!$"

CeruleanCity_EventScript_Slowbro::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SLOWBRO, CRY_MODE_NORMAL
	msgbox CeruleanCity_Text_Slowbro, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CeruleanCity_Text_Slowbro:
	.string "SLOWBRO: ¿Yarah?$"

CeruleanCity_EventScript_SlowbroWoman::
	msgbox CeruleanCity_Text_CooltrainerF1, MSGBOX_NPC
	turnobject LOCALID_CERULEAN_WOMAN, DIR_EAST
	msgbox CeruleanCity_Text_CooltrainerF2, MSGBOX_DEFAULT
	delay 20
	playmoncry SPECIES_SLOWBRO, CRY_MODE_NORMAL
	applymovement2 LOCALID_CERULEAN_SLOWBRO, Common_Movement_QuestionMark
	turnobject LOCALID_CERULEAN_SLOWBRO DIR_WEST
	delay 30
	turnobject LOCALID_CERULEAN_SLOWBRO, DIR_EAST
	delay 30
	turnobject LOCALID_CERULEAN_SLOWBRO, DIR_SOUTH
	delay 70
	msgbox CeruleanCity_Text_CooltrainerF3, MSGBOX_NPC
	end

CeruleanCity_Text_CooltrainerF1:
	.string "¡Mi SLOWBRO y yo somos un\n"
	.string "equipo increíble!$"

CeruleanCity_Text_CooltrainerF2:
	.string "¡SLOWBRO, usa CONFUSIÓN!$"

CeruleanCity_Text_CooltrainerF3:
	.string "…$"

CeruleanCity_EventScript_Fisher::
	goto_if_eq VAR_CERULEAN_CITY_STATE, 2, CeruleanCity_EventScript_FisherDuringRocket
	msgbox CeruleanCity_Text_Fisher, MSGBOX_NPC
	end

CeruleanCity_EventScript_FisherDuringRocket::
	msgbox CeruleanCity_Text_Fisher_RocketTip, MSGBOX_NPC
	end

CeruleanCity_Text_Fisher:
	.string "Soy muy fan de MISTY, del\n"
	.string "GIMNASIO CERULEAN.$"

CeruleanCity_Text_Fisher_RocketTip:
	.string "Vi a un tipo sospechoso ir hacia\n"
	.string "CABO AZUL.$"

CeruleanCity_EventScript_Youngster::
	msgbox CeruleanCity_Text_Youngster1, MSGBOX_NPC
	end

CeruleanCity_Text_Youngster1:
	.string "La cueva al norte del pueblo tiene\n"
	.string "POKéMON muy poderosos.$"

CeruleanCity_Text_Youngster2:
	.string "¿Eh?\p"
	.string "Mi ITEMFINDER está reaccionando…$"

CeruleanCity_EventScript_Sign::
	msgbox CeruleanCity_Text_Sign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_GymSign::
	msgbox CeruleanCity_Text_GymSign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_BikeShopSign::
	msgbox CeruleanCity_Text_BikeShopSign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_PoliceSign::
	msgbox CeruleanCity_Text_PoliceSign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_CapeSign::
	msgbox CeruleanCity_Text_CapeSign, MSGBOX_SIGN
	end

CeruleanCity_Text_Sign:
	.string "CIUDAD AZUL\p"
	.string "Un aura azul misteriosa la rodea$"

CeruleanCity_Text_GymSign:
	.string "CIUDAD AZUL\n"
	.string "GIMNASIO POKéMON\n"
	.string "LÍDER: MISTY\p"
	.string "La sirena marimacho$"

CeruleanCity_Text_BikeShopSign:
	.string "Hay un aviso aquí…\p"
	.string "La TIENDA DE BICIS se mudó a\n"
	.string "CIUDAD TRIGAL en JOHTO…$"

CeruleanCity_Text_PoliceSign:
	.string "Hay un aviso aquí…\p"
	.string "¡Acaben con los robos y hagan de la\n"
	.string "ciudad un lugar más alegre y\l"
	.string "amistoso!\p"
	.string "POLICÍA DE CIUDAD AZUL$"

CeruleanCity_Text_CapeSign:
	.string "CABO AZUL\n"
	.string "ADELANTE$"

CeruleanCity_Text_LockedDoor:
	.string "Está cerrada...$"

