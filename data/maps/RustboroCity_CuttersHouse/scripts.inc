RustboroCity_CuttersHouse_MapScripts::
	.byte 0

RustboroCity_CuttersHouse_EventScript_Cutter::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_CUT, RustboroCity_CuttersHouse_EventScript_ExplainCut
	msgbox RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	setflag FLAG_RECEIVED_HM_CUT
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_ExplainCut::
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_Lass::
	msgbox RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse:
	.string "Esa expresión decidida...\n"
	.string "Esa forma de moverte...\l"
	.string "Y tus POKéMON entrenados...\p"
	.string "¡Eres un TRAINER experto!\p"
	.string "No, espera, no digas nada.\n"
	.string "Lo noto solo con mirarte.\p"
	.string "Seguro que sabrás usar bien\n"
	.string "esta MOVIENOCULTA.\p"
	.string "No seas modesto ni tímido.\n"
	.string "¡Anda, tómala!$"

RustboroCity_CuttersHouse_Text_ExplainCut:
	.string "Esa MOVIENOCULTA, o MN\n"
	.string "para abreviar, es CORTE.\p"
	.string "Las MN se usan con los POKéMON\n"
	.string "fuera de las batallas.\p"
	.string "Cualquier POKéMON que sepa CORTE\n"
	.string "podrá talar árboles si el TRAINER\l"
	.string "tiene la INSIGNIA ROCA.\p"
	.string "Y lo mejor es que no hace falta\n"
	.string "enseñarle el movimiento. Funciona.$"

RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees:
	.string "Cuando ampliaban la ciudad de\n"
	.string "PORTO SALADO, mi papá ayudó.\p"
	.string "Hizo que sus POKéMON usaran CORTE\n"
	.string "para limpiar los árboles del lugar.$"

