Route30_House_MapScripts::
	.byte 0

Route30_House_EventScript_BaldMan::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BERRY_ROUTE_30_HOUSE, Route30_House_EventScript_BaldMan2
	msgbox Route30_BerryHouse_Text_MonEatBerries, MSGBOX_DEFAULT
	giveitem ITEM_CHERI_BERRY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_GOT_BERRY_ROUTE_30_HOUSE
Route30_House_EventScript_BaldMan2::
	msgbox Route30_BerryHouse_Text_CheckTrees MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_BerryHouse_Text_MonEatBerries:
	.string "Si sigues el camino al norte,\n"
	.string "verás la casa del SR. POKéMON.\p"
	.string "Pero antes, ¡déjame hablarte\n"
	.string "sobre las BAYAS!\p"
	.string "Los POKéMON sanan al comer\n"
	.string "BAYAS.\p"
	.string "Incluso pueden comer BAYAS\n"
	.string "que lleven en combate.\p"
	.string "KURT, en PUEBLO AZALEA, puede\n"
	.string "hacer BALLS con BAYAS.\p"
	.string "Toma. ¡Compartiré una contigo!$"

Route30_BerryHouse_Text_CheckTrees:
	.string "Busca BAYAS en los árboles.\n"
	.string "Vuelven a crecer tras unas horas.$"
