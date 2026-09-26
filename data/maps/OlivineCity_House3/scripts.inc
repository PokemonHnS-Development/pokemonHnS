OlivineCity_House3_MapScripts::
	.byte 0

OlivineCityHouse3_EventScriptFishingGuru::
	lock
	faceplayer
	checkitem ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, TRUE, OlivineCityHouse3_EventScriptFishingGuru2
	msgbox OlivineCity_Text_OfferGoodRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, OlivineCityHouse3_EventScriptFishingGuruRefused
	msgbox OlivineCity_Text_GiveGoodRod, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	msgbox OlivineCity_Text_GaveGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCityHouse3_EventScriptFishingGuru2::
	msgbox OlivineCity_Text_HaveGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCityHouse3_EventScriptFishingGuruRefused::
	msgbox OlivineCity_Text_DontWantGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_OfferGoodRod:
	.string "¡CIUDAD OLIVO está en el mar!\p"
	.string "¡Y si está en el mar, tiene\n"
	.string "que haber peces!\p"
	.string "He pescado aquí por 30 años.\p"
	.string "¿Quieres mirar el mar e\n"
	.string "intentar pescar algo?$"

OlivineCity_Text_GiveGoodRod:
	.string "¡Ah, jaja! ¡Tenemos a un\n"
	.string "nuevo pescador en potencia!$"

OlivineCity_Text_GaveGoodRod:
	.string "Los peces no están solo en el\n"
	.string "mar; están donde haya\l"
	.string "agua.\p"
	.string "Tu POKéDEX muestra grupos\n"
	.string "de pesca para POKéMON.\p"
	.string "Varios sitios pueden tener\n"
	.string "peces similares.$"

OlivineCity_Text_DontWantGoodRod:
	.string "¿Qué? ¡¿No te gusta pescar?!\n"
	.string "¡Eso es incomprensible!$"

OlivineCity_Text_HaveGoodRod:
	.string "¿Cómo va todo?\n"
	.string "¿Atrapaste al pez grande?$"
