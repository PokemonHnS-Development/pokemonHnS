RustboroCity_House1_MapScripts::
	.byte 0

RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_SEEDOT
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox RustboroCity_House1_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, RustboroCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, RustboroCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox RustboroCity_House1_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
	release
	end

RustboroCity_House1_EventScript_DeclineTrade::
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradeCompleted::
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
	end

RustboroCity_House1_Text_IllTradeIfYouWant:
	.string "¿Eh? ¿Mi POKéMON es lindo?\n"
	.string "Claro, ya lo sabía.\p"
	.string "Pero si de verdad quieres, estoy\n"
	.string "dispuesta a cambiártelo.\p"
	.string "Te daré mi {STR_VAR_2} por un\n"
	.string "{STR_VAR_1} si quieres.$"

RustboroCity_House1_Text_PleaseBeGoodToMyPokemon:
	.string "Eheheh…\n"
	.string "Por favor, cuida bien a mi POKéMON.$"

RustboroCity_House1_Text_DoesntLookLikeMonToMe:
	.string "¿Eh? Eso no se parece en nada a\n"
	.string "un {STR_VAR_1} para mí.$"

RustboroCity_House1_Text_YouDontWantToThatsOkay:
	.string "Oh, si no quieres, no pasa nada.\n"
	.string "Pero mi POKéMON es lindo, ¿sabes?$"

RustboroCity_House1_Text_AnyPokemonCanBeCute:
	.string "Cualquier POKéMON puede ser lindo si\n"
	.string "lo crías con cariño y bondad.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "En todo tipo de lugares hay todo\n"
	.string "tipo de POKéMON y personas.\p"
	.string "Eso me fascina, así que voy a todo\n"
	.string "tipo de lugares.$"

