MtPyre_1F_MapScripts::
	.byte 0

MtPyre_1F_DusknoirMisdreavusEvo::
	msgbox MtPyre_1F_DusknoirMisdreavusEvo_Text, MSGBOX_NPC
	end

MtPyre_1F_DusknoirMisdreavusEvo_Text:
	.string "DUSKULL salvajes llevan SPELL TAG.\n"
	.string "¿Por qué será? ¿Para qué sirve?\l"
	.string "¿Tal vez para evolucionar?\p"
	.string "Lo que sí sé es que MISDREAVUS\n"
	.string "evoluciona con ello durante la noche.$"

MtPyre_1F_EventScript_CleanseTagWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag::
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_PokefanF::
	msgbox MtPyre_1F_Text_ComeToPayRespects, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Man::
	msgbox MtPyre_1F_Text_RestingPlaceOfZigzagoon, MSGBOX_NPC
	end

MtPyre_1F_Text_TakeThisForYourOwnGood:
	.string "Todo tipo de seres vagan por las\n"
	.string "laderas del MT. PYRE…\p"
	.string "No se sabe qué puede pasar.\n"
	.string "Toma esto. Es por tu bien.$"

MtPyre_1F_Text_ExplainCleanseTag:
	.string "Haz que un POKéMON lleve ese\n"
	.string "CLEANSE TAG.\p"
	.string "Ayudará a ahuyentar POKéMON salvajes.$"

MtPyre_1F_Text_ComeToPayRespects:
	.string "¿Vienes a rendir respeto a los\n"
	.string "espíritus de POKéMON fallecidos?\p"
	.string "Debes querer mucho a tus POKéMON.$"

MtPyre_1F_Text_RestingPlaceOfZigzagoon:
	.string "Este es el lugar de descanso de mi\n"
	.string "ZIGZAGOON. Lo quería mucho…$"

