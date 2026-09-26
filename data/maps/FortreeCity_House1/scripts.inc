FortreeCity_House1_MapScripts::
	.byte 0

FortreeCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_FORTREE_NPC_TRADE_COMPLETED, FortreeCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_ONIX
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox FortreeCity_House1_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FortreeCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FortreeCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, FortreeCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_MonYouTakeCare, MSGBOX_DEFAULT
	setflag FLAG_FORTREE_NPC_TRADE_COMPLETED
	release
	end

FortreeCity_House1_EventScript_DeclineTrade::
	msgbox FortreeCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_TradeCompleted::
	msgbox FortreeCity_House1_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_ExpertF::
	msgbox FortreeCity_House1_Text_TradingMemoriesWithOthers, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House1_Text_YouWillTradeWontYou:
	.string "¡Wrooooaaar! ¡Lo quiero!\n"
	.string "¡Tengo que conseguir un {STR_VAR_1}!\l"
	.string "¡Haré lo que sea por él!\p"
	.string "...Eh... ¿Escuchaste eso?\n"
	.string "¿Mi grito desde el fondo del alma?\p"
	.string "Habiendo oído eso, cambiarás\n"
	.string "tu {STR_VAR_1} por mi {STR_VAR_2},\p"
	.string "¿verdad? ¡Es un POKéMON muy raro\n"
	.string "de otra región!$"

FortreeCity_House1_Text_MonYouTakeCare:
	.string "¡Oh, sí, genial!\p"
	.string "{STR_VAR_1}, ¡bienvenido!\n"
	.string "{STR_VAR_2}, ¡cuídate mucho!$"

FortreeCity_House1_Text_ThisIsntAMon:
	.string "Eh, no, no lo creo.\n"
	.string "Eso no es un {STR_VAR_1}.$"

FortreeCity_House1_Text_YouWontTradeMe:
	.string "¿No? ¿No cambiarás conmigo?\n"
	.string "¿Ni después de abrirte mi corazón?$"

FortreeCity_House1_Text_GoingToMakeVolbeatStrong:
	.string "¡Haré que VOLBEAT sea súper\n"
	.string "fuerte desde este momento!\p"
	.string "¡Espero que hagas lo mismo con PLUSLE!$"

FortreeCity_House1_Text_TradingMemoriesWithOthers:
	.string "Intercambiar POKéMON con otros...\p"
	.string "Es como si cambiaras tus propios\n"
	.string "recuerdos con otras personas.$"

FortreeCity_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: ¿Gumomoh?$"

