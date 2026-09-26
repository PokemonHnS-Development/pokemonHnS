CianwoodHouse3_MapScripts::
	.byte 0

CianwoodCity_EventScript_Kirk::
	lock
	faceplayer
	goto_if_eq VAR_SHUCKIE, 1, CianwoodCity_EventScript_KirkGivenShuckie
	goto_if_eq VAR_SHUCKIE, 3, CianwoodCity_EventScript_KirkReturnedShuckie
	msgbox CianwoodCity_Text_ManiacAskShuckle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_KirkDeclined

	@HnS named gift pokemon setup
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SHUCKLE
	bufferspeciesname STR_VAR_1, SPECIES_SHUCKLE
	givenamedmon 2
	call Common_EventScript_GiftMonNamed

	setvar VAR_SHUCKIE, 1
	release
	end

CianwoodCity_EventScript_KirkDeclined::
	msgbox CianwoodCity_Text_ManiacIfHeComesBack, MSGBOX_DEFAULT
	closemessage
	end

CianwoodCity_EventScript_KirkGivenShuckie::
	goto_if_set FLAG_BADGE01_GET, CianwoodCity_EventScript_KirkReturnShuckie
	msgbox CianwoodCity_Text_ManiacHowsdoing, MSGBOX_DEFAULT
	closemessage
	end

CianwoodCity_EventScript_KirkReturnShuckie::
	msgbox CianwoodCity_Text_ManiacAskReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_KirkDeclineReturnShuckie
	removenamedmon 2
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, CianwoodCity_EventScript_KirkNotRight
	goto_if_eq VAR_RESULT, 3, CianwoodCity_EventScript_KirkKeepShuckie
	playse MUS_OBTAIN_ITEM
	callnative UpdateFollowingPokemon
	msgbox CianwoodCity_Text_ManiacReturnedMon, MSGBOX_DEFAULT
	waitse
	msgbox CianwoodCity_Text_ManiacThankYou, MSGBOX_DEFAULT
	setvar VAR_SHUCKIE, 3
	release
	end

CianwoodCity_EventScript_KirkDeclineReturnShuckie::
	msgbox CianwoodCity_Text_ManiacRobbed2, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_KirkNotRight::
	msgbox CianwoodCity_Text_ManiacRobbed, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_KirkKeepShuckie::
	msgbox CianwoodCity_Text_ManiacShuckleLikesYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SHUCKIE, 3
	release
	end

CianwoodCity_EventScript_KirkReturnedShuckie::
	msgbox CianwoodCity_Text_ManiacHappinessSpeech, MSGBOX_DEFAULT
	closemessage
	end

CianwoodCity_Text_ManiacAskShuckle:
	.string "¡Estoy en shock!\p"
	.string "Un chico de tu edad, de ojos\n"
	.string "penetrantes y pelo largo, entró.\p"
	.string "¡Me asustó para que le diera\n"
	.string "mi POKéMON favorito!\p"
	.string "Me queda uno, ¿pero y si\n"
	.string "regresa?\p"
	.string "Te ves fuerte. ¿Cuidarías de mi\n"
	.string "POKéMON un tiempo?$"

CianwoodCity_Text_ManiacTakeCareShuckle:
	.string "¡Oh, gracias!\p"
	.string "¡Cuídalo mucho, por favor!$"

CianwoodCity_Text_ManiacGotShuckle:
	.string "{PLAYER} recibió un POKéMON.$"

CianwoodCity_Text_ManiacPartyFull:
	.string "Tu equipo POKéMON está lleno.$"

CianwoodCity_Text_ManiacIfHeComesBack:
	.string "Oh, no... ¿Qué haré si él\n"
	.string "regresa?$"

CianwoodCity_Text_ManiacHowsdoing:
	.string "¡Hola! ¿Cómo está mi POKéMON?$"

CianwoodCity_Text_ManiacAskReturn:
	.string "¡Hola! ¿Cómo está mi POKéMON?\p"
	.string "Creo que ya estoy a salvo, ¿me lo\n"
	.string "devuelves?$"

CianwoodCity_Text_ManiacThankYou:
	.string "¡Gracias!$"

CianwoodCity_Text_ManiacShuckleNotThere:
	.string "Oye, no tienes mi POKéMON\n"
	.string "contigo.$"

CianwoodCity_Text_ManiacShuckleLikesYou:
	.string "Mi POKéMON te ha tomado cariño.\p"
	.string "Está bien, quédatelo.\p"
	.string "¡Pero prométeme cuidarlo bien!$"

CianwoodCity_Text_ManiacRobbed:
	.string "Eh, algo no está bien.$"

CianwoodCity_Text_ManiacRobbed2:
	.string "Oh, no, no... Eso es lo mismo\n"
	.string "que ser robado.$"

CianwoodCity_Text_ManiacHappinessSpeech:
	.string "Para un POKéMON, la felicidad es\n"
	.string "estar con alguien que lo trate bien.$"

CianwoodCity_Text_ManiacLastMon:
	.string "Si recupero mi POKéMON,\n"
	.string "¿qué vas a usar\n"
	.string "en la batalla?$"


CianwoodCity_Text_ManiacReturnedMon:
	.string "{PLAYER} devolvió a SHUCKIE.$"
