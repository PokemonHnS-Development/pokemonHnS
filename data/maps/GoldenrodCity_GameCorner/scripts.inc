GoldenrodCity_GameCorner_MapScripts::
	.byte 0

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PrizeClerkMons::
	lock
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NeedCoinCase
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeMon::
	callnative DisableStaticRandomizer
	showcoinsbox 1, 1
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	multichoice 20, 0, MULTI_PRIZE_MONS, FALSE
	switch VAR_RESULT
	case 0, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Abra
	case 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Clefairy
	case 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Munchlax
	case 3, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Dratini
	case 4, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Porygon
	case 5, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	case 127, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange::
	hidecoinsbox 0, 0
	callnative EnableStaticRandomizer
	closemessage
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Abra::
	setvar VAR_TEMP_1, SPECIES_ABRA
	setvar VAR_TEMP_2, 120
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Clefairy::
	setvar VAR_TEMP_1, SPECIES_CLEFAIRY
	setvar VAR_TEMP_2, 500
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Munchlax::
	setvar VAR_TEMP_1, SPECIES_MUNCHLAX
	setvar VAR_TEMP_2, 2800
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Dratini::
	setvar VAR_TEMP_1, SPECIES_DRATINI
	setvar VAR_TEMP_2, 5500
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Porygon::
	setvar VAR_TEMP_1, SPECIES_PORYGON
	setvar VAR_TEMP_2, 6500
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon::
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	msgbox GoldenrodCity_GameCorner_PrizeRoom_Text_YouWantPrize, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	checkcoins VAR_RESULT
	goto_if_lt VAR_RESULT, VAR_TEMP_2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins
	switch VAR_TEMP_1
	updatecoinsbox 1, 1
	playse SE_SHOP
	case SPECIES_ABRA,     GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveAbra
	case SPECIES_CLEFAIRY, GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveClefairy
	case SPECIES_DRATINI,  GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveDratini
	case SPECIES_MUNCHLAX,  GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveMunchlax
	case SPECIES_PORYGON,  GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePorygon
	case SPECIES_PINSIR,   GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePinsir
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveAbra::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveClefairy::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveDratini::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveMunchlax::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePorygon::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePinsir::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon::
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonPC
	goto_if_eq VAR_RESULT, 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyFull
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyFull::
	msgbox Route119_WeatherInstitute_2F_Text_NoRoomForPokemon
	hidecoinsbox 0, 0
	callnative EnableStaticRandomizer
	closemessage
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NicknamePartyMon::
	getpartysize
	subvar VAR_RESULT, 1
	copyvar VAR_0x8004, VAR_RESULT
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty_Nickname_Nuzlocke::
	message GoldenrodGamecorner_Text_GiveNicknameToThisMon
	getpartysize
	subvar VAR_RESULT, 1
	copyvar VAR_0x8004, VAR_RESULT
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorNoCoinCase
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorNeedMoreCoins
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty::
	removecoins VAR_TEMP_2
	playse SE_SHOP
	updatecoinsbox 1, 1
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon
	waitmessage
	waitfanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty_Nickname_Nuzlocke
	msgbox GoldenrodGamecorner_Text_GiveNicknameToThisMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NicknamePartyMon
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonPC::
	removecoins VAR_TEMP_2
	playse SE_SHOP
	updatecoinsbox 1, 1
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon
	waitmessage
	waitfanfare
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_TransferredToPC
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TransferredToPC::
	call Common_EventScript_TransferredToPC
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyMon::
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	end
	
GoldenrodCity_GameCorner_PrizeRoom_EventScript_PcMon::
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_GameCorner_EventScript_SendMon
	call Common_EventScript_NameReceivedBoxMon
	goto GoldenrodCity_GameCorner_EventScript_SendMon
	closemessage
	hidecoinsbox 0, 0
	callnative EnableStaticRandomizer
	release
	end

GoldenrodCity_GameCorner_EventScript_SendMon::
	call Common_EventScript_TransferredToPC
	closemessage
	hidecoinsbox 0, 0
	callnative EnableStaticRandomizer
	release
	end

GoldenrodCity_GameCorner_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_PokefanM1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_Hiker::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_MoveTutorInside, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

GoldenrodCity_GameCorner_EventScript_Gentleman::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

GoldenrodCity_GameCorner_EventScript_PokefanM2::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_PokefanM2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_CooltrainerM::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

GoldenrodCity_GameCorner_EventScript_Pharmacist::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_Pharmacist, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

@ ========================================
@ VOLTORB FLIP GAME IMPLEMENTATION
@ ========================================

@ Entry point — shows a welcome message then goes to the menu.
GoldenrodCity_GameCorner_EventScript_VoltorbFlip::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase
	message GoldenrodCity_GameCorner_Text_VF
	waitmessage
	playbgm MUS_RG_OAK, FALSE
	setvar VAR_FLIP_LEVEL, 0

@ Coin cap check — runs on fresh entry and after any coins are awarded.
@ If the player is at 9999 coins they cannot earn more, so end the session.
GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap::
	checkcoins VAR_RESULT
	goto_if_lt VAR_RESULT, MAX_COINS, GoldenrodCity_GameCorner_EventScript_VF_ShowMenu
	msgbox GoldenrodCity_GameCorner_Text_VF_CoinCap, MSGBOX_DEFAULT
	setvar VAR_FLIP_LEVEL, 0
	setvar VAR_FLIP_STREAK, 0
	hidecoinsbox 0, 5
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

@ ─────────────────────────────────────────────────────────────────────────────
@ Main menu — shown on entry and after every round (win/loss/mid-game quit).
@ Displays current level and gives the player three choices.
@ ─────────────────────────────────────────────────────────────────────────────
GoldenrodCity_GameCorner_EventScript_VF_ShowMenu::
	showcoinsbox 1, 1
	copyvar VAR_TEMP_A, VAR_FLIP_LEVEL
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	message GoldenrodCity_GameCorner_Text_VF_PlayLevel
	waitmessage
	multichoice 19, 6, MULTI_VF_MAIN_MENU, FALSE
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_EventScript_VF_Play
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_EventScript_VF_GameInfo
	@ Case 2 or 127 (B-press) — player chooses to quit the session entirely.
	setvar VAR_FLIP_LEVEL, 0
	setvar VAR_FLIP_STREAK, 0
	closemessage
	hidecoinsbox 0, 5
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

@ ─────────────────────────────────────────────────────────────────────────────
@ Game Info sub-menu — How to Play / Hint / About Notes / Return
@ ─────────────────────────────────────────────────────────────────────────────
GoldenrodCity_GameCorner_EventScript_VF_GameInfo::
	message GoldenrodCity_GameCorner_Text_VF_WhichInfo
	waitmessage
	multichoice 19, 4, MULTI_VF_GAME_INFO, FALSE
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_EventScript_VF_HowToPlay
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_EventScript_VF_Hint
	goto_if_eq VAR_RESULT, 2, GoldenrodCity_GameCorner_EventScript_VF_AboutNotes
	@ Case 3 or 127 — Return to main menu.
	goto GoldenrodCity_GameCorner_EventScript_VF_ShowMenu

GoldenrodCity_GameCorner_EventScript_VF_HowToPlay::
	msgbox GoldenrodCity_GameCorner_Text_VF_HowToPlay, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_GameInfo

GoldenrodCity_GameCorner_EventScript_VF_Hint::
	msgbox GoldenrodCity_GameCorner_Text_VF_HintText, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_GameInfo

GoldenrodCity_GameCorner_EventScript_VF_AboutNotes::
	msgbox GoldenrodCity_GameCorner_Text_VF_AboutNotes, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_GameInfo

@ ─────────────────────────────────────────────────────────────────────────────
@ Play — snapshot the level, clear winnings, then run the mini-game.
@ VAR_RESULT on return: 0 = loss, 1 = win (all ×2/×3 found), 2 = mid-game quit.
@ ─────────────────────────────────────────────────────────────────────────────
GoldenrodCity_GameCorner_EventScript_VF_Play::
	closemessage
	copyvar VAR_FLIP_PREV_LEVEL, VAR_FLIP_LEVEL
	setvar VAR_FLIP_WINNINGS, 0
	hidecoinsbox 0, 5
	special Special_ViewVoltorbFlip
	waitstate
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_EventScript_VF_HandleLoss
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_EventScript_VF_HandleWin
	goto GoldenrodCity_GameCorner_EventScript_VF_HandleQuit
	end

@ ─────────────────────────────────────────────────────────────────────────────
@ Win — award coins, show results, advance-level message if applicable.
@ ─────────────────────────────────────────────────────────────────────────────
GoldenrodCity_GameCorner_EventScript_VF_HandleWin::
	msgbox GoldenrodCity_GameCorner_Text_VF_GameClear, MSGBOX_DEFAULT
	copyvar VAR_TEMP_1, VAR_FLIP_WINNINGS
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_1
	msgbox GoldenrodCity_GameCorner_Text_VF_ReceivedCoins, MSGBOX_DEFAULT
	addcoins VAR_FLIP_WINNINGS
	setvar VAR_FLIP_WINNINGS, 0
	updatecoinsbox 1, 1
	@ If level did not increase, check cap then go to menu.
	goto_if_le VAR_FLIP_LEVEL, VAR_FLIP_PREV_LEVEL, GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap
	@ Level went up — show advancement message.
	copyvar VAR_TEMP_A, VAR_FLIP_LEVEL
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	msgbox GoldenrodCity_GameCorner_Text_VF_Advanced, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap

@ ─────────────────────────────────────────────────────────────────────────────
@ Loss — show zero-coin message, level-drop message if applicable.
@ ─────────────────────────────────────────────────────────────────────────────
GoldenrodCity_GameCorner_EventScript_VF_HandleLoss::
	msgbox GoldenrodCity_GameCorner_Text_VF_OhNo, MSGBOX_DEFAULT
	@ If level did not drop, go straight back to the menu.
	goto_if_ge VAR_FLIP_LEVEL, VAR_FLIP_PREV_LEVEL, GoldenrodCity_GameCorner_EventScript_VF_ShowMenu
	@ Level dropped — show demotion message.
	copyvar VAR_TEMP_A, VAR_FLIP_LEVEL
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	msgbox GoldenrodCity_GameCorner_Text_VF_Dropped, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_ShowMenu

@ ─────────────────────────────────────────────────────────────────────────────
@ Mid-game quit — keep whatever coins were earned so far.
@ ─────────────────────────────────────────────────────────────────────────────
GoldenrodCity_GameCorner_EventScript_VF_HandleQuit::
	goto_if_eq VAR_FLIP_WINNINGS, 0, GoldenrodCity_GameCorner_EventScript_VF_QuitNoCoins
	copyvar VAR_TEMP_1, VAR_FLIP_WINNINGS
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_1
	msgbox GoldenrodCity_GameCorner_Text_VF_ReceivedCoins, MSGBOX_DEFAULT
	addcoins VAR_FLIP_WINNINGS
	setvar VAR_FLIP_WINNINGS, 0
	updatecoinsbox 1, 1

GoldenrodCity_GameCorner_EventScript_VF_QuitNoCoins::
	@ Level never changes for mid-game quit, but check anyway for future-proofing.
	goto_if_ge VAR_FLIP_LEVEL, VAR_FLIP_PREV_LEVEL, GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap
	copyvar VAR_TEMP_A, VAR_FLIP_LEVEL
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	msgbox GoldenrodCity_GameCorner_Text_VF_Dropped, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap

GoldenrodCity_GameCorner_EventScript_VFAttendant1::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_VFAttendant1, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceDown
	waitmovement 0
	release
	end

GoldenrodCity_GameCorner_EventScript_VFAttendant2::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_VFAttendant2, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceDown
	waitmovement 0
	release
	end

@ ========================================
@ TEXT STRINGS
@ ========================================

GoldenrodCity_GameCorner_PrizeRoom_Text_YouWantPrize:
	.string "{STR_VAR_1} is what you want?$"

GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon:
	.string "{PLAYER} got {STR_VAR_1}!$"

GoldenrodGamecorner_Text_GiveNicknameToThisMon:
	.string "Nickname {STR_VAR_1}?$"

GoldenrodCity_GameCorner_Text_PrizeVendorIntro:
    .string "Welcome!\p"
    .string "We exchange your game coins for\n"
    .string "fabulous prizes!$"

GoldenrodCity_GameCorner_Text_PrizeVendorWhichPrize:
    .string "Which prize would you like?$"

GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo:
    .string "Here you go!$"

GoldenrodCity_GameCorner_Text_PrizeVendorNeedMoreCoins:
    .string "Sorry! You need more coins.$"

GoldenrodCity_GameCorner_Text_PrizeVendorNoMoreRoom:
    .string "Sorry. You can't carry any more.$"

GoldenrodCity_GameCorner_Text_PrizeVendorQuit:
    .string "OK. Please save your coins and come\n"
    .string "again!$"

GoldenrodCity_GameCorner_Text_PrizeVendorNoCoinCase:
    .string "Oh? You don't have a COIN CASE.$"

GoldenrodCity_GameCorner_Text_Pharmacist:
    .string "I always play this slot machine.\n"
    .string "It pays out more than others,\l"
    .string "I think.$"

GoldenrodCity_GameCorner_Text_PokefanM1:
    .string "I just love this new slot machine.\p"
    .string "It's more of a challenge than the\n"
    .string "ones in CELADON.$"

GoldenrodCity_GameCorner_Text_CooltrainerM:
    .string "Life is a gamble. I'm going to pull\n"
    .string "till I drop!$"

GoldenrodCity_GameCorner_Text_CooltrainerF:
    .string "I won't quit until I win!$"

GoldenrodCity_GameCorner_Text_Gentleman:
    .string "I taught ICE BEAM to my POKéMON.\p"
    .string "It was hard to get enough coins for\n"
    .string "it, but it was worth it.$"

GoldenrodCity_GameCorner_Text_PokefanM2:
    .string "I couldn't win at the slots, and I'm\n"
    .string "no good at VOLTORB FLIP.\p"
    .string "I got so furious, I tossed out my\n"
    .string "COIN CASE in the UNDERGROUND.$"

GoldenrodCity_GameCorner_Text_MoveTutorInside:
    .string "Wahahah! The coins keep rolling in!$"

GoldenrodCity_GameCorner_Text_LeftTheirDrink:
    .string "Someone left their drink.\p"
    .string "It smells sweet.$"

@ Voltorb Flip Text Strings
GoldenrodCity_GameCorner_Text_VF:
	.string "Welcome to VOLTORB FLIP!\p$"

@ "Play VOLTORB Flip Lv. X?" — level display dialogue used on the main menu and after every round.
GoldenrodCity_GameCorner_Text_VF_PlayLevel:
	.string "Play VOLTORB Flip Lv. {STR_VAR_1}?$"

@ Win / receive-coins messages
GoldenrodCity_GameCorner_Text_VF_GameClear:
	.string "Game clear!\p"
	.string "You've found all the hidden\n"
	.string "x2 and x3 cards!$"

GoldenrodCity_GameCorner_Text_VF_ReceivedCoins:
	.string "You have received\n"
	.string "{STR_VAR_1} Coin(s)!$"

GoldenrodCity_GameCorner_Text_VF_Advanced:
	.string "Advanced to Game Lv. {STR_VAR_1}!$"

@ Loss message
GoldenrodCity_GameCorner_Text_VF_OhNo:
	.string "Oh no! You get 0 Coins!$"

@ Level-drop message (loss or poor mid-game quit)
GoldenrodCity_GameCorner_Text_VF_Dropped:
	.string "Dropped to Game Lv. {STR_VAR_1}.$"

@ Coin cap message
GoldenrodCity_GameCorner_Text_VF_CoinCap:
	.string "You've gathered 9,999 COINS.\n"
	.string "You cannot gather any more.$"

@ Game Info sub-menu header
GoldenrodCity_GameCorner_Text_VF_WhichInfo:
	.string "Which set of info?$"

@ How to Play tutorial
GoldenrodCity_GameCorner_Text_VF_HowToPlay:
	.string "VOLTORB Flip is a game in which you flip\n"
	.string "over cards to find numbers hidden\l"
	.string "beneath them.\p"
	.string "The cards are hiding the numbers\n"
	.string "1 through 3...and VOLTORB as well.\p"
	.string "The first number you flip over will give\n"
	.string "you that many Coins.\p"
	.string "From then on, the next number you\n"
	.string "find will multiply the total amount of\l"
	.string "Coins you've collected by that number.\p"
	.string "If it's a 2, your total will be multiplied\n"
	.string "by 'x2.'\p"
	.string "If it's a 3, your total will be multiplied\n"
	.string "by 'x3.'\p"
	.string "But if you flip over a VOLTORB, it's\n"
	.string "game over.\p"
	.string "When that happens, you'll lose all the\n"
	.string "Coins you've collected in the\l"
	.string "current game.\p"
	.string "Press {B_BUTTON} to 'Quit' and you'll\n"
	.string "withdraw from the game.\p"
	.string "If you get to a difficult spot, you might\n"
	.string "want to end the game early.\p"
	.string "Once you've found all the hidden\n"
	.string "2 and 3 cards, you've cleared\l"
	.string "the game.\p"
	.string "Once you've flipped over all these\n"
	.string "cards, then you'll advance to the\l"
	.string "next level.\p"
	.string "As you move up in levels, you will be\n"
	.string "able to receive more Coins.\l"
	.string "Do your best!$"

	

@ Hint text
GoldenrodCity_GameCorner_Text_VF_HintText:
	.string "The numbers at the side of the board\n"
	.string "give you a clue about the numbers\l"
	.string "hidden under the cards.\p"
	.string "The larger the number, the more likely\n"
	.string "it is that there are many large numbers\l"
	.string "hidden in that row or column.\p"
	.string "In the same way, you can tell how many\n"
	.string "VOLTORB are hidden in the row\l"
	.string "or column.\p"
	.string "Consider the hidden number totals and\n"
	.string "the VOLTORB totals carefully as you\l"
	.string "flip over panels!$"

@ About Notes text
GoldenrodCity_GameCorner_Text_VF_AboutNotes:
	.string "Use the Notes mode ({L_BUTTON} & {R_BUTTON}) to mark\n"
	.string "cards with numbers 1-3 or a VOLTORB.\p"
	.string "Mark a card you think you know,\n"
	.string "then flip it when you're sure.\l"
	.string "Apply a note again to remove it.$"

@ Voltorb Flip Attendant Texts
GoldenrodCity_GameCorner_Text_VFAttendant1:
	.string "You want to play VOLTORB FLIP?\p"
	.string "You need to be on the other\n"
	.string "side of the table.$"

GoldenrodCity_GameCorner_Text_VFAttendant2:
	.string "Try the other side of\n"
	.string "the table, pal.$"
