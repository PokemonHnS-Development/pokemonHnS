MossdeepCity_House3_MapScripts::
	.byte 0

MossdeepCity_House3_EventScript_SuperRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SUPER_ROD, MossdeepCity_House3_EventScript_ReceivedSuperRod
	msgbox MossdeepCity_House3_Text_YouWantSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_House3_EventScript_DeclineSuperRod
	msgbox MossdeepCity_House3_Text_SuperRodIsSuper, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	setflag FLAG_RECEIVED_SUPER_ROD
	msgbox MossdeepCity_House3_Text_TryDroppingRodInWater, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_ReceivedSuperRod::
	msgbox MossdeepCity_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_DeclineSuperRod::
	msgbox MossdeepCity_House3_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_Text_YouWantSuperRod:
	.string "¡Hola, ENTRENADOR!\n"
	.string "¡La SUPERCAÑA es genial!\p"
	.string "¡Esta joya puede atrapar POKéMON\n"
	.string "desde el fondo del mar!\p"
	.string "¿Qué te parece?\n"
	.string "La quieres, ¿verdad?$"

MossdeepCity_House3_Text_SuperRodIsSuper:
	.string "¡Claro que sí, claro que sí!\n"
	.string "¡Una SUPER ROD es súper genial!$"

MossdeepCity_House3_Text_TryDroppingRodInWater:
	.string "Si hay agua, ¡lanza tu CAÑA y mira\n"
	.string "qué muerde el anzuelo!$"

MossdeepCity_House3_Text_DontYouLikeToFish:
	.string "¿Eh?\n"
	.string "¿No te gusta pescar?$"

MossdeepCity_House3_Text_GoAfterSeafloorPokemon:
	.string "Busca POKéMON en el fondo del mar\n"
	.string "con tu SUPERCAÑA.$"

