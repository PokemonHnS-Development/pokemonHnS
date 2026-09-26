MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_GARBAGEFLAG
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "¡Yuju!\p"
	.string "Dicen que soy el TIPO ROCA ROMPER\n"
	.string "pero me parece degradante.\p"
	.string "Creo que merezco más respeto,\n"
	.string "como el TIPO GUAY ROCA ROMPER.\p"
	.string "¡Yuju!\p"
	.string "En fin, tus POKéMON se ven muy\n"
	.string "fuertes.\p"
	.string "¡Me gusta eso!\n"
	.string "¡Toma esta MO QUITA!$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "Esa MO contiene ROCA ROMPER.\p"
	.string "Si encuentras rocas grandes\n"
	.string "que bloqueen tu camino...\p"
	.string "¡Usa ese movimiento de MO y\n"
	.string "destrúyelas para pasar!\p"
	.string "¡Eso es! ¡Rompe rocas, digo yo!\n"
	.string "¡Yuju!$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Ah, sí, si rompes una roca, un POKéMON\n"
	.string "podría salir volando de su escondite.\p"
	.string "¡Yuju!$"

