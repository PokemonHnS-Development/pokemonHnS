MossdeepCity_Mart_MapScripts::
	.byte 0

MossdeepCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Mart_EventScript_Clerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart:
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_NONE
	release
	end

MossdeepCity_Mart_EventScript_Woman::
	msgbox MossdeepCity_Mart_Text_ReviveIsFantastic, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Boy::
	msgbox MossdeepCity_Mart_Text_MaxRepelLastsLongest, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Sailor::
	msgbox MossdeepCity_Mart_Text_NetAndDiveBallsRare, MSGBOX_NPC
	end

MossdeepCity_Mart_Text_ReviveIsFantastic:
	.string "¡REVIVE es fantástico!\p"
	.string "Dáselo a un POKéMON debilitado,\n"
	.string "y el POKéMON despertará.\p"
	.string "Pero ojo, REVIVE no restaura\n"
	.string "los PP usados de los movimientos.$"

MossdeepCity_Mart_Text_MaxRepelLastsLongest:
	.string "MAX REPEL aleja a POKéMON débiles.\p"
	.string "De todos los sprays REPEL, es el\n"
	.string "que más dura.$"

MossdeepCity_Mart_Text_NetAndDiveBallsRare:
	.string "NET y DIVE BALL son POKé BALL raras\n"
	.string "que solo se hacen en MOSSDEEP.\p"
	.string "NET BALL es eficaz contra POKéMON\n"
	.string "tipo BICHOS y tipo AGUA.\p"
	.string "DIVE BALL funciona mejor con POKéMON\n"
	.string "en el fondo del mar.$"

