PalletTown_Lab_MapScripts::
	.byte 0

PalletTown_Lab_EventScript_Oak::
	lock
	faceplayer
	call_if_unset FLAG_SYS_NATIONAL_DEX, PalletTown_Lab_EventScript_OakGiveNatDex_ForPlaytesters
	goto_if_eq VAR_PALLETTOWN_LABSTATE, 1, PalletTown_Lab_EventScript_OakBadgeCheck
	goto_if_eq VAR_PALLETTOWN_LABSTATE, 2, PalletTown_Lab_EventScript_OakDex
	msgbox PalletTown_Lab_Text_OakWelcomeKanto, MSGBOX_DEFAULT
	msgbox PalletTown_Lab_Text_OakLabGoodbye, MSGBOX_DEFAULT
	setvar VAR_PALLETTOWN_LABSTATE, 1
	closemessage
	release
	end

PalletTown_Lab_EventScript_OakGiveNatDex_ForPlaytesters::
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	return

PalletTown_Lab_EventScript_OakBadgeCheck::
	goto_if_ge VAR_NUM_BADGES, 16, PalletTown_Lab_EventScript_Oak16Badges
	goto_if_ge VAR_NUM_BADGES, 9, PalletTown_Lab_EventScript_Oak9Badges
	msgbox PalletTown_Lab_Text_OakNoKantoBadges, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_Oak16Badges::
	msgbox PalletTown_Lab_Text_OakOpenMtSilver, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
	setvar VAR_PALLETTOWN_LABSTATE, 2
	release
	end

PalletTown_Lab_EventScript_Oak9Badges::
	msgbox PalletTown_Lab_Text_OakYesKantoBadges, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_OakDex::
	msgbox PalletTown_Lab_Text_OakLabDexCheck, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_Assistant1::
	msgbox PalletTown_Lab_Text_OaksAssistant1, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_Assistant2::
	msgbox PalletTown_Lab_Text_OaksAssistant2, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_Assistant3::
	msgbox PalletTown_Lab_Text_OaksAssistant3, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_PC::
	msgbox PalletTown_Lab_Text_OaksLabPC, MSGBOX_SIGN
	end

PalletTown_Lab_Text_OakLabDexCheck:
	.string "¿Cómo va tu POKéDEX?$"

PalletTown_Lab_Text_OakWelcomeKanto:
	.string "OAK: ¡Ah, {PLAYER}!\n"
	.string "Es bueno que hayas venido hasta\l"
	.string "KANTO.\p"
	.string "¿Qué te parecen los entrenadores\n"
	.string "de aquí? Son fuertes, ¿eh?$"

PalletTown_Lab_Text_OakLabGoodbye:
	.string "Si estás por la zona, espero que\n"
	.string "vuelvas a visitarme.$"

PalletTown_Lab_Text_OakOpenMtSilver:
	.string "OAK: ¡Vaya! ¡Eso es excelente!\p"
	.string "Obtuviste las MEDALLAS de los\n"
	.string "GIMNASIOS de KANTO. ¡Bien hecho!\p"
	.string "Mi evaluación sobre ti\n"
	.string "fue correcta.\p"
	.string "Mira, {PLAYER}. Haré los\n"
	.string "arreglos para que puedas ir\l"
	.string "al MT.SILVER.\p"
	.string "MT.SILVER es una gran montaña\n"
	.string "con muchos POKéMON salvajes.\p"
	.string "Es muy peligroso para un\n"
	.string "entrenador común, así que está\l"
	.string "prohibido. Pero haremos una\l"
	.string "excepción contigo, {PLAYER}.\p"
	.string "Ve a la MESETA AÑIL. Desde\n"
	.string "allí podrás llegar al MT.SILVER.$"

PalletTown_Lab_Text_OakNoKantoBadges:
	.string "OAK: ¿Hmm? ¿No estás buscando\n"
	.string "las MEDALLAS de KANTO?\p"
	.string "Los LÍDERES de KANTO son tan\n"
	.string "fuertes como los de JOHTO.\p"
	.string "Te recomiendo desafiarlos.$"

PalletTown_Lab_Text_OakYesKantoBadges:
	.string "OAK: Ah, estás buscando las\n"
	.string "MEDALLAS de KANTO.\p"
	.string "Imagino que es difícil, pero la\n"
	.string "experiencia seguro te ayudará.\p"
	.string "Ven a verme cuando las tengas todas.\p"
	.string "Tengo un regalo para ti.\p"
	.string "¡Sigue esforzándote, {PLAYER}!$"

PalletTown_Lab_Text_OaksAssistant1:
	.string "El programa de radio POKéMON TALK\n"
	.string "del PROF. no se transmite en KANTO.\p"
	.string "Es una pena, me gustaría oírlo.$"

PalletTown_Lab_Text_OaksAssistant2:
	.string "Gracias a tu trabajo con la POKéDEX,\n"
	.string "la investigación del PROF. va\l"
	.string "muy bien.$"

PalletTown_Lab_Text_OaksAssistant3:
	.string "No se lo digas a nadie, pero el\n"
	.string "POKéMON TALK no es en vivo.$"

PalletTown_Lab_Text_OaksLabPC:
	.string "Hay un correo en la PC.\p"
	.string "…\p"
	.string "PROF.OAK, ¿cómo va su\n"
	.string "investigación?\p"
	.string "Sigo trabajando en ello.\p"
	.string "Oí que {PLAYER} se está\n"
	.string "haciendo famoso.\p"
	.string "Me alegra mucho saberlo.\p"
	.string "ELM en PUEBLO PRIMAVERA 8-)$"
