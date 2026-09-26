LakeOfRage_House1_MapScripts::
	.byte 0

LakeOfRage_House1_EventScript_HiddenPowerGuy::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HIDDEN_POWER, LakeOfRage_House1_EventScript_HiddenPowerGuyAfter
	msgbox HiddenPowerGuy_Text_Intro, MSGBOX_DEFAULT
	giveitem ITEM_TM_HIDDEN_POWER
	msgbox HiddenPowerGuy_Text_Explanation, MSGBOX_DEFAULT
	setflag FLAG_GOT_HIDDEN_POWER
	closemessage
	release
	end

LakeOfRage_House1_EventScript_HiddenPowerGuyAfter::
	msgbox HiddenPowerGuy_Text_Meditating, MSGBOX_DEFAULT
	closemessage
	release
	end

HiddenPowerGuy_Text_Intro:
    .string "...Te has alejado mucho...\p"
    .string "Aquí he meditado. En mi interior,\n"
    .string "un nuevo poder ha despertado.\p"
    .string "Compartiré mi poder con tus\n"
    .string "POKéMON. Toma esto, niño.$"

HiddenPowerGuy_Text_Explanation:
    .string "¿Lo ves? ¡Es PODER OCULTO!\p"
    .string "Saca el poder de los POKéMON\n"
    .string "para atacar.\p"
    .string "Recuerda: su tipo y poder\n"
    .string "dependen del POKéMON que lo use.$"

HiddenPowerGuy_Text_Meditating:
    .string "Estoy meditando...$"
