FortreeCity_Mart_MapScripts::
	.byte 0

FortreeCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

FortreeCity_Mart_EventScript_Clerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FortreeCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_Mart_Pokemart:
	.2byte ITEM_WOOD_MAIL
	.2byte ITEM_NONE
	release
	end

FortreeCity_Mart_EventScript_Woman::
	msgbox FortreeCity_Mart_Text_SuperRepelBetter, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Girl::
	msgbox FortreeCity_Mart_Text_StockUpOnItems, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Boy::
	msgbox FortreeCity_Mart_Text_RareCandyMakesMonGrow, MSGBOX_NPC
	end

FortreeCity_Mart_Text_SuperRepelBetter:
	.string "SUPER REPEL dura mucho tiempo,\n"
	.string "y es muy eficaz.\p"
	.string "Es mucho mejor que un\n"
	.string "REPEL común.$"

FortreeCity_Mart_Text_StockUpOnItems:
	.string "Siempre llevo más objetos de los\n"
	.string "que creo necesitar.\p"
	.string "Nunca se sabe qué pasará.\n"
	.string "¡Más vale prevenir!$"

FortreeCity_Mart_Text_RareCandyMakesMonGrow:
	.string "Un RARE CANDY hace que un POKéMON\n"
	.string "suba un nivel al instante.$"

