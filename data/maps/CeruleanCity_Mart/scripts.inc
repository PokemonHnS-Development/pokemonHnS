CeruleanCity_Mart_MapScripts::
	.byte 0

CeruleanCity_Mart_EventScript_Juggler::
	msgbox CeruleanMart_Text_CooltrainerM, MSGBOX_NPC
	end

CeruleanCity_Mart_EventScript_CooltrainerF::
	msgbox CeruleanMart_Text_CooltrainerF, MSGBOX_NPC
	end

CeruleanMart_Text_CooltrainerM:
	.string "Verás muchos entrenadores en\n"
	.string "el camino al CABO CERULEAN.\p"
	.string "Quieren ver cómo les va frente\n"
	.string "a otros entrenadores.$"

CeruleanMart_Text_CooltrainerF:
	.string "MISTY es casi la única persona en\n"
	.string "el pueblo que puede vencer a los\l"
	.string "entrenadores del CABO CERULEAN.$"
