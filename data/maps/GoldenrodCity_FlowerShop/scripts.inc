.set LOCALID_MINT_CLERK, 3

GoldenrodCity_FlowerShop_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodCity_FlowerShop_OnTransition
	.byte 0

GoldenrodCity_FlowerShop_OnTransition::
	call_if_unset FLAG_MINTS_ENABLED, GoldenrodCity_FlowerShop_HideMintClerk
	call_if_set FLAG_MINTS_ENABLED, GoldenrodCity_FlowerShop_ShowMintClerk
	end

GoldenrodCity_FlowerShop_HideMintClerk::
	goto_if_set FLAG_SYS_GAME_CLEAR, GoldenrodCity_FlowerShop_ShowMintClerkPostgame
	setflag FLAG_MINTS_CLERK
	removeobject LOCALID_MINT_CLERK
	return

GoldenrodCity_FlowerShop_ShowMintClerkPostgame::
	clearflag FLAG_MINTS_CLERK
	addobject LOCALID_MINT_CLERK
	end

GoldenrodCity_FlowerShop_ShowMintClerk::
	clearflag FLAG_MINTS_CLERK
	addobject LOCALID_MINT_CLERK
	return

GoldenrodCity_FlowerShop_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Normal
	goto_if_set FLAG_RECEIVED_SQUIRTBOTTLE, GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle
	msgbox GoldenrodCity_FlowerShop_Text_Owner1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner2, MSGBOX_DEFAULT
	giveitem ITEM_SQUIRT_BOTTLE
	setflag FLAG_RECEIVED_SQUIRTBOTTLE
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner3, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Normal::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner4, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria1::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Floria3
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_Floria2
	msgbox GoldenrodCity_FlowerShop_Text_Floria, MSGBOX_DEFAULT
	closemessage
	release
	end
	
GoldenrodCity_FlowerShop_EventScript_Floria2::
	msgbox GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria3::
	msgbox GoldenrodCity_FlowerShop_Text_FloriaItWasAMon, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_Text_Floria:
	.string "Le conté a mi hermana el árbol\n"
	.string "que baila y dijo que es peligroso.\p"
	.string "Si venzo a WHITNEY, quizá me\n"
	.string "preste su botella de agua…$"

GoldenrodCity_FlowerShop_Text_Owner1:
.string "Parece que hay un árbol extraño\n"
.string "en la RUTA 36.\p"
.string "Dicen que baila si lo riegas...\n"
.string "it...\p"
.string "¡Ah, claro que no!\p"
.string "Esta es una floristería, así que\n"
.string "tenemos regaderas...\p"
.string "¡Pero no puedo darte una!\n"
.string "¡Es muy peligroso!\p"
.string "Bueno, si logras derrotar a la\n"
.string "líder WHITNEY, tal vez\l"
.string "esté bien.$"

GoldenrodCity_FlowerShop_Text_Owner2:
.string "Parece que hay un árbol extraño\n"
.string "en la RUTA 36.\p"
.string "Dicen que baila si lo riegas...\n"
.string "it...\p"
.string "¡Es una PLAINBADGE del\n"
.string "GIMNASIO de CIUDAD TRIGAL!\p"
.string "¡¿Derrotaste a WHITNEY?!\p"
.string "Bueno, entonces no hay nada\n"
.string "de qué preocuparse, ¿verdad?\p"
.string "Te prestaré esta SQUIRTBOTTLE\n"
.string "por un tiempo.\l"
.string "...\p"
.string "Olvídalo. ¡Quédatela!$"

GoldenrodCity_FlowerShop_Text_Owner3:
.string "El árbol extraño está en la\n"
.string "RUTA 36. ¡Ten cuidado!$"

GoldenrodCity_FlowerShop_Text_Owner4:
    .string "Lalala lalalala. ¡Bebe mucha\n"
    .string "agua, mi cielo!$"

GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney:
    .string "¡Vaya, venciste a WHITNEY! ¡Genial!$"

GoldenrodCity_FlowerShop_Text_FloriaItWasAMon:
    .string "¡Así que sí era un POKéMON!$"
