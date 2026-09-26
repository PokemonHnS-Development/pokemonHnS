DewfordTown_House2_MapScripts::
	.byte 0

DewfordTown_House2_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SILK_SCARF, DewfordTown_House2_EventScript_ExplainSilkScarf
	msgbox DewfordTown_House2_Text_WantYouToHaveSilkScarf, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_House2_EventScript_NoRoomForScarf
	setflag FLAG_RECEIVED_SILK_SCARF
	release
	end

DewfordTown_House2_EventScript_NoRoomForScarf::
	msgbox DewfordTown_House2_Text_NoRoom, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_ExplainSilkScarf::
	msgbox DewfordTown_House2_Text_ExplainSilkScarf, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_Boy::
	msgbox DewfordTown_House2_Text_BrawlySoCool, MSGBOX_NPC
	end

DewfordTown_House2_Text_WantYouToHaveSilkScarf:
	.string "¡Mira esto con atención!\p"
	.string "Es un PAÑUELO SEDA. ¡Está a la\n"
	.string "última moda, sí!\p"
	.string "¡Veo que tus ojos brillan!\n"
	.string "¡Aprecias mi estilo deslumbrante!\p"
	.string "¡Eres un encanto!\n"
	.string "Toma. ¡Quiero que lo tengas!$"

DewfordTown_House2_Text_NoRoom:
	.string "¿Oh, no tienes espacio?\p"
	.string "Escucha bien, ¡este PAÑUELO es\n"
	.string "imprescindible! ¡Vendería todo\l"
	.string "lo que tengo por él!$"

DewfordTown_House2_Text_ExplainSilkScarf:
	.string "El PAÑUELO SEDA sube el poder de\n"
	.string "los movimientos tipo NORMAL.\p"
	.string "¡Es un pañuelo maravilloso que\n"
	.string "va con casi todo POKéMON!$"

DewfordTown_House2_Text_BrawlySoCool:
	.string "Vaya, ¿cruzaste el mar para\n"
	.string "visitar DEWFORD?\p"
	.string "¿Acaso viniste porque oíste\n"
	.string "hablar de BRAWLY?\p"
	.string "Es tan genial...\n"
	.string "Todos lo idolatran.$"

