LakeOfRage_House2_MapScripts::
	.byte 0

LakeOfRage_House2_EventScript_Fisher::
	lock
	faceplayer
	goto_if_ge VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_House2_EventScript_FisherAfterRockets
	goto_if_eq VAR_LAKE_OF_RAGE_FISHERMAN, 0, LakeOfRage_House2_EventScript_FisherFirstMeeting
	msgbox LakeOfRage_House2_Text_MenInBlack, MSGBOX_DEFAULT
	closemessage
	release
	end	

LakeOfRage_House2_EventScript_FisherFirstMeeting::
	msgbox LakeOfRage_House2_Text_LakeHistory, MSGBOX_DEFAULT
	msgbox LakeOfRage_House2_Text_MenInBlack, MSGBOX_DEFAULT
	setvar VAR_LAKE_OF_RAGE_FISHERMAN, 1
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherAfterRockets::
	goto_if_eq VAR_LAKE_OF_RAGE_FISHERMAN, 2, LakeOfRage_House2_EventScript_FisherAnotherMagikarp
	msgbox LakeOfRage_House2_Text_WorldsLargest, MSGBOX_DEFAULT
	msgbox LakeOfRage_House2_Text_ForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNo
	getpartysize
	goto_if_eq VAR_RESULT, 1, LakeOfRage_House2_EventScript_LastMon
	special ChoosePartyMon
	waitstate
	lock
	showmoneybox 0, 0
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, LakeOfRage_House2_EventScript_FisherNoMoneyBox
	removegenericmon SPECIES_MAGIKARP
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNotMagikarp
	goto_if_eq VAR_RESULT, MON_SATISFACTORY, LakeOfRage_House2_EventScript_FisherSatisfied
	goto_if_eq VAR_RESULT, MON_UNSATISFACTORY, LakeOfRage_House2_EventScript_FisherSmallMagikarp

LakeOfRage_House2_EventScript_FisherNo::
	msgbox LakeOfRage_House2_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherNoMoneyBox::
	msgbox LakeOfRage_House2_Text_Refused, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherNotMagikarp::
	msgbox LakeOfRage_House2_Text_NotMagikarp, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherSmallMagikarp::
	setvar VAR_LAKE_OF_RAGE_FISHERMAN, 2
	msgbox LakeOfRage_House2_Text_TooShort, MSGBOX_DEFAULT
	addmoney 2000
	updatemoneybox
	playse SE_SHOP
	waitse
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherAnotherMagikarp::
	msgbox LakeOfRage_House2_Text_ForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNo
	getpartysize
	goto_if_eq VAR_RESULT, 1, LakeOfRage_House2_EventScript_LastMon
	special ChoosePartyMon
	waitstate
	lock
	showmoneybox 0, 0
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, LakeOfRage_House2_EventScript_FisherNoMoneyBox
	removegenericmon SPECIES_MAGIKARP
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNotMagikarp
	goto_if_eq VAR_RESULT, MON_SATISFACTORY, LakeOfRage_House2_EventScript_FisherSatisfied
	goto_if_eq VAR_RESULT, MON_UNSATISFACTORY, LakeOfRage_House2_EventScript_FisherSmallMagikarp

LakeOfRage_House2_EventScript_LastMon::
	msgbox LakeOfRage_House2_Text_LastMon, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherSatisfied::
	setvar VAR_LAKE_OF_RAGE_FISHERMAN, 2
	msgbox LakeOfRage_House2_Text_BigPayout, MSGBOX_DEFAULT
	addmoney 100000
	updatemoneybox
	playse SE_SHOP
	waitse
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_Text_LakeHistory:
    .string "EL LAGO DE LA FURIA es un cráter\n"
    .string "hecho por GYARADOS furiosos.\p"
    .string "El cráter se llenó de lluvia\n"
    .string "y así se formó el LAGO.\p"
    .string "Es la historia que contaba el\n"
    .string "tatarabuelo de mi abuelo.\p"
    .string "Antes podías capturar MAGIKARP\n"
    .string "activos ahí, pero...\p"
    .string "No entiendo qué está pasando.$"

LakeOfRage_House2_Text_MenInBlack:
    .string "El LAGO no es normal desde que\n"
    .string "llegaron esos hombres de negro.$"

LakeOfRage_House2_Text_LastMon:
    .string "¡Bueno, no dejaré que me quites\n"
    .string "tu último POKéMON!$"

LakeOfRage_House2_Text_WorldsLargest:
    .string "LAGO DE LA FURIA volvió a la normal.\p"
    .string "Los MAGIKARP han regresado.\p"
    .string "Aún podré cumplir mi sueño de\n"
    .string "tener el MAGIKARP más grande.\p"
    .string "Te pagaré ¥2000 por cada\n"
	.string "MAGIKARP, y ¥100,000 por\l"
	.string "¡un MAGIKARP GIGANTE!$"

LakeOfRage_House2_Text_ForMe:
	.string "Entonces... ¿tienes un MAGIKARP\n"
	.string "para mí?$"

LakeOfRage_House2_Text_HaveMagikarp:
    .string "¡Ah, tienes un MAGIKARP! Veamos\n"
    .string "qué tan grande es ese pequeñín.$"

LakeOfRage_House2_Text_BigPayout:
    .string "¡Guau! ¡Este es increíble!\p"
    .string "¡Me quito el sombrero!\p"
    .string "Toma esto por tu\n"
	.string "esfuerzo.$"

LakeOfRage_House2_Text_Bonus:
    .string "El récord es lo más importante.\p"
    .string "¡Toma esto como un bono!$"

LakeOfRage_House2_Text_TooShort:
    .string "¡Guau! ¡Este es increíble!\p"
    .string "...Desearía decir eso, pero he\n"
    .string "visto uno más grande antes.\p"
    .string "Supongo que vale algo.$"

LakeOfRage_House2_Text_NotMagikarp:
    .string "¡¿Qué?! ¡Eso no es un MAGIKARP!$"

LakeOfRage_House2_Text_Refused:
    .string "Oh... ¿No conseguiste uno lo\n"
    .string "suficiente bueno? Quizá la próxima.$"
