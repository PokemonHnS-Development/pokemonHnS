BattleFrontier_ExchangeServiceCorner_MapScripts::
	.byte 0

BattleFrontier_ExchangeServiceCorner_EventScript_DecorClerk1::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPDecorShop1
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_DecorClerk2::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPDecorShop2
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_VitaminClerk::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPVitaminShop
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_HoldItemClerk::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPHoldItemShop
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_PokeBallClerk::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPPokeBallShop
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Man::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_GoGetYourOwnDoll, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Sailor::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ItemsWillGetMonTougher, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_PokefanF::
	lock
	msgbox BattleFrontier_ExchangeServiceCorner_Text_GetYouAnythingYouWant, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_RichBoy::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WishIHadAllDolls, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Girl::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_MoreBattlePointsForRecord, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_OldWTMan::
	msgbox BattleFrontier_ExchangeServiceCorner_EventScript_OldWTMan_Text, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_OldWTMan_Text:
	.string "Hi! If you are looking for the\n"
	.string "WONDERTRADE, they're now located in\l"
	.string "every POKéMON CENTER. Have fun!$"

BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize:
	.string "Hello, this is the EXCHANGE SERVICE\n"
	.string "CORNER.\p"
	.string "We exchange the Battle Points you\n"
	.string "have collected for lovely prizes.\p"
	.string "Please choose a prize from this list.$"

BattleFrontier_ExchangeServiceCorner_Text_WishIHadAllDolls:
	.string "Oh, they're so nice!\n"
	.string "I wish I had them!\l"
	.string "Cute cushions!\l"
	.string "Big plush DOLLS!\l"
	.string "Little plush DOLLS!\l"
	.string "I wish I had them all!$"

BattleFrontier_ExchangeServiceCorner_Text_GetYouAnythingYouWant:
	.string "Leave it to your mommy!\p"
	.string "If it's anything you want, I'll go\n"
	.string "through anything to get it, honey!$"

BattleFrontier_ExchangeServiceCorner_Text_ItemsWillGetMonTougher:
	.string "If I can get hold of the items here,\n"
	.string "my POKéMON will get tougher.\p"
	.string "You bet they will!\n"
	.string "No question about it!$"

BattleFrontier_ExchangeServiceCorner_Text_GoGetYourOwnDoll:
	.string "Hah?\n"
	.string "What are you gawking at?\p"
	.string "I don't like you staring at my plush\n"
	.string "doll like that.\p"
	.string "If you want it, go get one yourself!\n"
	.string "Isn't that right, SMOOCHUM?$"

BattleFrontier_ExchangeServiceCorner_Text_MoreBattlePointsForRecord:
	.string "Did you know?\p"
	.string "If you stretch your record at any of\n"
	.string "the BATTLE facilities, they start\l"
	.string "giving you more and more Battle Points.$"

EventScript_DoWonderTrade::
	goto_if_set FLAG_UNLIMITIED_WONDERTRADE, EventScript_DoWonderTradeStartNoLimit
	goto_if_unset FLAG_WONDERTRADE_FIRSTIME, EventScript_FirstTimeWonderRandomizer
	special CheckIfRandomizerIsActive
	goto_if_unset FLAG_WT_ENABLED_RANDOMIZER, EventScript_DoWonderTradeStart
	special CheckIfChallengesAreActive
	goto_if_set FLAG_WONDERTRADE3, EventScript_NoMoreForToday
	goto_if_set FLAG_NO_WT_BECAUSE_CHALLENGE, EventScript_WTChallenges
	goto_if_unset FLAG_WONDERTRADE1, EventScript_DoWonderTradeFirstTrade	
	goto_if_unset FLAG_WONDERTRADE2, EventScript_DoWonderTradeSecondTrade
	goto_if_unset FLAG_WONDERTRADE3, EventScript_DoWonderTradeThirdTrade
	end

EventScript_DoWonderTradeStart:
	goto_if_unset FLAG_BADGE05_GET, EventScript_WTNotActiveYet
	msgbox EventScript_DoWonderTrade_Text_Welcome, MSGBOX_DEFAULT
	closemessage
	special CheckIfChallengesAreActive
	goto_if_set FLAG_WONDERTRADE3, EventScript_NoMoreForToday
	goto_if_set FLAG_NO_WT_BECAUSE_CHALLENGE, EventScript_WTChallenges
	goto_if_unset FLAG_WONDERTRADE1, EventScript_DoWonderTradeFirstTrade	
	goto_if_unset FLAG_WONDERTRADE2, EventScript_DoWonderTradeSecondTrade
	goto_if_unset FLAG_WONDERTRADE3, EventScript_DoWonderTradeThirdTrade
	end

EventScript_WTChallenges::
	goto_if_unset FLAG_SYS_GAME_CLEAR, EventScript_WTChallengesCancel
	goto_if_unset FLAG_WONDERTRADE1, EventScript_DoWonderTradeFirstTrade	
	goto_if_unset FLAG_WONDERTRADE2, EventScript_DoWonderTradeSecondTrade
	goto_if_unset FLAG_WONDERTRADE3, EventScript_DoWonderTradeThirdTrade
	end

EventScript_WTChallengesCancel::
	msgbox EventScript_DoWonderTrade_Text_Challenges, MSGBOX_DEFAULT
	closemessage
	end

EventScript_WTNotActiveYet::
	msgbox EventScript_DoWonderTrade_Text_FiveBadges, MSGBOX_DEFAULT
	closemessage
	end

EventScript_DoWonderTradeFirstTrade::
	setflag FLAG_WONDERTRADE1
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, EventScript_DoWonderTradeCancelSaveFirstTrade
	special ChoosePartyMon
	waitstate
	goto EventScript_DoWonderTradeTrade

EventScript_DoWonderTradeCancelSaveFirstTrade::
	clearflag FLAG_WONDERTRADE1
	msgbox EventScript_DoWonderTrade_Text_Done, MSGBOX_DEFAULT
	closemessage
	end

EventScript_DoWonderTradeSecondTrade::
	setflag FLAG_WONDERTRADE2
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, EventScript_DoWonderTradeCancelSaveSecondTrade
	special ChoosePartyMon
	waitstate
	goto EventScript_DoWonderTradeTrade

EventScript_DoWonderTradeCancelSaveSecondTrade::
	clearflag FLAG_WONDERTRADE2
	msgbox EventScript_DoWonderTrade_Text_Done, MSGBOX_DEFAULT
	closemessage
	end

EventScript_DoWonderTradeThirdTrade::
	setflag FLAG_WONDERTRADE3
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, EventScript_DoWonderTradeCancelSaveThirdTrade
	special ChoosePartyMon
	waitstate
	goto EventScript_DoWonderTradeTrade

EventScript_DoWonderTradeCancelSaveThirdTrade::
	clearflag FLAG_WONDERTRADE3
	msgbox EventScript_DoWonderTrade_Text_Done, MSGBOX_DEFAULT
	closemessage
	end

EventScript_DoWonderTradeStartNoLimit::
	goto_if_unset FLAG_WONDERTRADE_FIRSTIME, EventScript_FirstTimeWonderUnlimited
	goto_if_unset FLAG_BADGE05_GET, EventScript_WTNotActiveYet
	special CheckIfChallengesAreActive
	goto_if_set FLAG_NO_WT_BECAUSE_CHALLENGE, EventScript_WTChallengesUnlimited
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, 0, EventScript_DoWonderTradeCancelSaveThirdTrade
	special ChoosePartyMon
	waitstate
	goto EventScript_DoWonderTradeTrade

EventScript_WTChallengesUnlimited::
	goto_if_unset FLAG_SYS_GAME_CLEAR, EventScript_WTChallengesCancel
	return

EventScript_DoWonderTradeTrade::
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge EventScript_End
	copyvar VAR_0x8005, VAR_0x8004
	special CreateWonderTradePokemon
	special DoInGameTradeScene
	waitstate
	special ForceSaveGame
	waitstate
	msgbox EventScript_DoWonderTrade_Text_Done, MSGBOX_DEFAULT
	closemessage
	end

EventScript_NoMoreForToday::
	msgbox EventScript_NoMoreForToday_Text, MSGBOX_DEFAULT
	closemessage
	end

EventScript_FirstTimeWonderRandomizer::
	msgbox EventScript_FirstTimeWonder_Text, MSGBOX_DEFAULT
	setflag FLAG_WONDERTRADE_FIRSTIME
	closemessage
	end

EventScript_FirstTimeWonderUnlimited::
	msgbox EventScript_FirstTimeWonder_Text_Unlimited, MSGBOX_DEFAULT
	setflag FLAG_WONDERTRADE_FIRSTIME
	closemessage
	end

EventScript_End::
	end

EventScript_DoWonderTrade_Text_Welcome:
	.string "Welcome to the WONDERTRADE\n"
	.string "STATION of the POKéCENTER!\p"
	.string "Please select the POKéMON that\n"
	.string "is going to get WONDERTRADED.$"

EventScript_NoMoreForToday_Text:
	.string "Oh! Seems that you have\n"
	.string "used all 3 DAILY TRADES.\p"
	.string "Come back tomorrow!$"

EventScript_FirstTimeWonder_Text:
	.string "Hello trainer!\p"
	.string "Oh, is this your first time\n"
	.string "using the WONDERTRADE SYSTEM?\p"
	.string "WONDERTRADE is a techonology developed\n"
	.string "by DEVON CORP. to TRADE anonimously.\p"
	.string "You basically send a selected\n"
	.string "POKéMON to someone, and they send\p"
	.string "you another one in exchange.\n"
	.string "Neither you nor the other trainer\p"
	.string "know which POKéMON is going to\n"
	.string "show up. And that is the fun of\p"
	.string "WONDERTRADE! Oh, also, to not\n"
	.string "overload the server, there is a\p"
	.string "maximum of 3 DAILY WONDERTRADES.\p"
	.string "We hope you have a great\n"
	.string "WONDERTRADE experience!$"

EventScript_FirstTimeWonder_Text_Unlimited:
	.string "Hello trainer!\p"
	.string "Oh, is this your first time\n"
	.string "using the WONDERTRADE SYSTEM?\p"
	.string "WONDERTRADE is a techonology developed\n"
	.string "by DEVON CORP. to TRADE anonimously.\p"
	.string "You basically send a selected\n"
	.string "POKéMON to someone, and they send\p"
	.string "you another one in exchange.\n"
	.string "Neither you nor the other trainer\p"
	.string "know which POKéMON is going to\n"
	.string "show up. And that is the fun of\l"
	.string "WONDERTRADE!\p"
	.string "We hope you have a great\n"
	.string "WONDERTRADE experience!$"

EventScript_DoWonderTrade_Text_Done:
	.string "We hope you had a good\n"
	.string "WONDERTRADE!$"

EventScript_DoWonderTrade_Text_Challenges:
	.string "Looks like you have challenges\n"
	.string "activated. Please come back\l"
	.string "again after the POKéMON LEAGUE.$"

EventScript_DoWonderTrade_Text_FiveBadges:
	.string "Sadly, the WONDERTRADE SYSTEM is\n"
	.string "not active yet. Please do come\l"
	.string "back later.$"
