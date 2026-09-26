BattleFrontier_Lounge6_MapScripts::
	.byte 0

BattleFrontier_Lounge6_EventScript_Trader::
	msgbox BattleFrontier_Lounge6_Text_WouldYouLikeToTrade, MSGBOX_DEFAULT
	closemessage
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade:
	.string "Mi POKéMON es un SKITTY.\n"
	.string "¿Lo conoces?\l"
	.string "Es lindo y muy agradable.\p"
	.string "¡A este pequeño no podría darlo\n"
	.string "en intercambio!$"

@	
@	lock
@	faceplayer
@	goto_if_set FLAG_BATTLE_FRONTIER_TRADE_DONE, BattleFrontier_Lounge6_EventScript_TradeCompleted
@	setvar VAR_0x8008, INGAME_TRADE_MEOWTH
@	copyvar VAR_0x8004, VAR_0x8008
@	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
@	copyvar VAR_0x8009, VAR_RESULT
@	msgbox BattleFrontier_Lounge6_Text_WouldYouLikeToTrade, MSGBOX_YESNO
@	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge6_EventScript_DeclineTrade
@	special ChoosePartyMon
@	waitstate
@	copyvar VAR_0x800A, VAR_0x8004
@	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge6_EventScript_DeclineTrade
@	copyvar VAR_0x8005, VAR_0x800A
@	specialvar VAR_RESULT, GetTradeSpecies
@	copyvar VAR_0x800B, VAR_RESULT
@	goto_if_ne VAR_RESULT, VAR_0x8009, BattleFrontier_Lounge6_EventScript_NotRequestedMon
@	copyvar VAR_0x8004, VAR_0x8008
@	copyvar VAR_0x8005, VAR_0x800A
@	special CreateInGameTradePokemon
@	special DoInGameTradeScene
@	waitstate
@	msgbox BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt, MSGBOX_DEFAULT
@	setflag FLAG_BATTLE_FRONTIER_TRADE_DONE
@	release
@	end
@
@BattleFrontier_Lounge6_EventScript_DeclineTrade::
@	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo, MSGBOX_DEFAULT
@	release
@	end
@
@BattleFrontier_Lounge6_EventScript_NotRequestedMon::
@	bufferspeciesname STR_VAR_1, VAR_0x8009
@	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
@	release
@	end
@
@BattleFrontier_Lounge6_EventScript_TradeCompleted::
@	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined, MSGBOX_DEFAULT
@	release
@	end

@BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt:
@	.string "¡Oh, es adorable!\n"
@	.string "¡Gracias!\l"
@	.string "¡Prometo cuidarlo bien!\p"
@	.string "¡Oh! Espero que seas bueno con\n"
@	.string "mi {STR_VAR_2}.$"
@
@BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon:
@	.string "¡Oh, lo siento!\n"
@	.string "No pienso cambiarlo por nada\l"
@	.string "salvo un {STR_VAR_1}.$"
@
@BattleFrontier_Lounge6_Text_WellThatsFineToo:
@	.string "¿Oh, no quieres?\n"
@	.string "Bueno, tampoco pasa nada.\l"
@	.string "Por favor, visítanos de nuevo.$"
@
@BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined:
@	.string "Giggle!\n"
@	.string "Un SKITTY es mucho más lindo de lo que\l"
@	.string "imagined. I'm delighted!$"
