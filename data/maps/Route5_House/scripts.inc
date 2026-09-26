Route5_House_MapScripts::
	.byte 0

Route5_House_EventScript_Granny::
	goto_if_set FLAG_GOT_CLEANSE_TAG, Route5_House_EventScript_GrannyAfter
	msgbox Route5_House_Text_Granny1, MSGBOX_NPC
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setflag FLAG_GOT_CLEANSE_TAG
	release
	end

Route5_House_EventScript_GrannyAfter::
	msgbox Route5_House_Text_Granny2, MSGBOX_NPC
	end

Route5_House_EventScript_Woman::
	msgbox Route5_House_Text_Woman, MSGBOX_NPC
	end

Route5_House_Text_Granny1:
	.string "¡Eeyaaaah!\p"
	.string "Siento una sombra siniestra\n"
	.string "sobre ti.\l"
	.string "¡Toma esto para ahuyentarla!$"

Route5_House_Text_Granny2:
	.string "Estabas en peligro mortal, pero\n"
	.string "ahora estás protegido.$"

Route5_House_Text_Woman:
	.string "Mi abuela ahuyenta lo que ella\n"
	.string "cree que son espíritus malignos.\p"
	.string "Siento que te haya asustado.$"
