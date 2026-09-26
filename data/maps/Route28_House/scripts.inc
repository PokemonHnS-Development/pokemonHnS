Route28_House_MapScripts::
	.byte 0

Route28House_EventScript_Celebrity::
	lock
	goto_if_set FLAG_GOT_TM_STEEL_WING Route28House_EventScript_CelebrityAfter
	msgbox Route28House_Text_Celebrity1, MSGBOX_NPC
	giveitem ITEM_TM_STEEL_WING
	setflag FLAG_GOT_TM_STEEL_WING
Route28House_EventScript_CelebrityAfter::
	msgbox Route28House_Text_Celebrity2, MSGBOX_NPC
	release
	end

Route28House_Text_Celebrity1:
	.string "Vaya. Me has encontrado.\p"
	.string "Por favor, no digas nada de mí.\p"
	.string "Toma esto por guardar mi\n"
	.string "secreto. ¿Sí?$"

Route28House_Text_Celebrity2:
	.string "Es duro ser una celebridad.\p"
	.string "A donde voy, la gente me persigue.\p"
	.string "Solo quiero que me dejen en paz…$"

Route28House_Text_Fearow:
	.string "FEAROW: ¡Feero!$"

