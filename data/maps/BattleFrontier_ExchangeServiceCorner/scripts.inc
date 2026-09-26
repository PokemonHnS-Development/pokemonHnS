BattleFrontier_ExchangeServiceCorner_MapScripts::
	.byte 0

BattleFrontier_ExchangeServiceCorner_EventScript_ClerkWelcome::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special ShowBattlePointsWindow
	return

BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ThankYouVisitWithPoints, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_ExchangeServiceCorner_EventScript_TryGivePrize
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveEnoughPoints, MSGBOX_DEFAULT
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR2_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_VITAMIN_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TryGivePrize::
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveDecor
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR2_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveDecor
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveDecor::
	checkdecorspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ExchangeServiceCorner_EventScript_NoRoomForDecor
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	adddecoration VAR_0x8009
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WellSendItToPC, MSGBOX_DEFAULT
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	end

BattleFrontier_ExchangeServiceCorner_EventScript_NoRoomForDecor::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_PCIsFull, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveItem::
	checkitemspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ExchangeServiceCorner_EventScript_BagFull
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	additem VAR_0x8009
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_ExchangeServiceCorner_Text_HereIsYourPrize, MSGBOX_DEFAULT
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_VITAMIN_CLERK, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_BagFull::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_DontHaveSpaceToHoldIt, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_DecorClerk1::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK
	call BattleFrontier_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_DECOR_VENDOR_1
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, BattleFrontier_ExchangeServiceCorner_EventScript_TreeckoDoll
	case 1, BattleFrontier_ExchangeServiceCorner_EventScript_TorchicDoll
	case 2, BattleFrontier_ExchangeServiceCorner_EventScript_MudkipDoll
	case 3, BattleFrontier_ExchangeServiceCorner_EventScript_TogepiDoll
	case 4, BattleFrontier_ExchangeServiceCorner_EventScript_MeowthDoll
	case 5, BattleFrontier_ExchangeServiceCorner_EventScript_ClefairyDoll
	case 6, BattleFrontier_ExchangeServiceCorner_EventScript_DittoDoll
	case 7, BattleFrontier_ExchangeServiceCorner_EventScript_CyndaquilDoll
	case 8, BattleFrontier_ExchangeServiceCorner_EventScript_ChikoritaDoll
	case 9, BattleFrontier_ExchangeServiceCorner_EventScript_TotodileDoll
	case 10, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TreeckoDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmTreeckoDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_TREECKO_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TorchicDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmTorchicDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_TORCHIC_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_MudkipDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmMudkipDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_MUDKIP_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TogepiDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmTogepiDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_TOGEPI_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_MeowthDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmMeowthDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_MEOWTH_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ClefairyDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmClefairyDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_CLEFAIRY_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_DittoDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmDittoDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_DITTO_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_CyndaquilDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmCyndaquilDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 80
	setvar VAR_0x8009, DECOR_CYNDAQUIL_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChikoritaDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmChikoritaDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 80
	setvar VAR_0x8009, DECOR_CHIKORITA_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_TotodileDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmTotodileDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 80
	setvar VAR_0x8009, DECOR_TOTODILE_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_DecorClerk2::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_DECOR2_CLERK
	call BattleFrontier_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_DECOR_VENDOR_2
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, BattleFrontier_ExchangeServiceCorner_EventScript_LaprasDoll
	case 1, BattleFrontier_ExchangeServiceCorner_EventScript_SnorlaxDoll
	case 2, BattleFrontier_ExchangeServiceCorner_EventScript_VenusaurDoll
	case 3, BattleFrontier_ExchangeServiceCorner_EventScript_CharizardDoll
	case 4, BattleFrontier_ExchangeServiceCorner_EventScript_BlastoiseDoll
	case 5, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_LaprasDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmLaprasDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 128
	setvar VAR_0x8009, DECOR_LAPRAS_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_SnorlaxDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmSnorlaxDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 128
	setvar VAR_0x8009, DECOR_SNORLAX_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_VenusaurDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmVenusaurDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 256
	setvar VAR_0x8009, DECOR_VENUSAUR_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_CharizardDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmCharizardDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 256
	setvar VAR_0x8009, DECOR_CHARIZARD_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_BlastoiseDoll::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmBlastoiseDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 256
	setvar VAR_0x8009, DECOR_BLASTOISE_DOLL
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_VitaminClerk::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_VITAMIN_CLERK
	call BattleFrontier_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_VITAMIN_VENDOR
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, BattleFrontier_ExchangeServiceCorner_EventScript_EonTicket
	case 1, BattleFrontier_ExchangeServiceCorner_EventScript_MysticTicket
	case 2, BattleFrontier_ExchangeServiceCorner_EventScript_AuroraTicket
	case 3, BattleFrontier_ExchangeServiceCorner_EventScript_OldMap
	case 4, BattleFrontier_ExchangeServiceCorner_EventScript_Brace
	case 5, BattleFrontier_ExchangeServiceCorner_EventScript_Upgrade
	case 6, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_YouAlreadyHaveThis::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_YouAlreadyHaveThis, MSGBOX_DEFAULT
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_EonTicket::
	checkitem ITEM_EON_TICKET, 1
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_YouAlreadyHaveThis
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmEonTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_EON_TICKET
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_MysticTicket::
	checkitem ITEM_MYSTIC_TICKET, 1
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_YouAlreadyHaveThis
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmMysticTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 96
	setvar VAR_0x8009, ITEM_MYSTIC_TICKET
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_AuroraTicket::
	checkitem ITEM_AURORA_TICKET, 1
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_YouAlreadyHaveThis
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmAuroraTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 96
	setvar VAR_0x8009, ITEM_AURORA_TICKET
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_OldMap::
	checkitem ITEM_OLD_SEA_MAP, 1
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_ExchangeServiceCorner_EventScript_YouAlreadyHaveThis
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmOldMap, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 96
	setvar VAR_0x8009, ITEM_OLD_SEA_MAP
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Brace::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmBrace, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 4
	setvar VAR_0x8009, ITEM_MACHO_BRACE
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Upgrade::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmUpgrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 16
	setvar VAR_0x8009, ITEM_UP_GRADE
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_HoldItemClerk::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_HOLD_ITEM_CLERK
	call BattleFrontier_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_HOLD_ITEM_VENDOR
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, BattleFrontier_ExchangeServiceCorner_EventScript_Leftovers
	case 1, BattleFrontier_ExchangeServiceCorner_EventScript_WhiteHerb
	case 2, BattleFrontier_ExchangeServiceCorner_EventScript_QuickClaw
	case 3, BattleFrontier_ExchangeServiceCorner_EventScript_MentalHerb
	case 4, BattleFrontier_ExchangeServiceCorner_EventScript_Brightpowder
	case 5, BattleFrontier_ExchangeServiceCorner_EventScript_ChoiceBand
	case 6, BattleFrontier_ExchangeServiceCorner_EventScript_KingsRock
	case 7, BattleFrontier_ExchangeServiceCorner_EventScript_FocusBand
	case 8, BattleFrontier_ExchangeServiceCorner_EventScript_ScopeLens
	case 9, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, BattleFrontier_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Leftovers::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmLeftovers, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_LEFTOVERS
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_WhiteHerb::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmWhiteHerb, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_WHITE_HERB
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_QuickClaw::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmQuickClaw, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_QUICK_CLAW
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_MentalHerb::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmMentalHerb, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_MENTAL_HERB
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Brightpowder::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmBrightpowder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_BRIGHT_POWDER
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ChoiceBand::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmChoiceBand, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_CHOICE_BAND
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_KingsRock::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmKingsRock, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_KINGS_ROCK
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_FocusBand::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmFocusBand, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_FOCUS_BAND
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

BattleFrontier_ExchangeServiceCorner_EventScript_ScopeLens::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ConfirmScopeLens, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_SCOPE_LENS
	goto BattleFrontier_ExchangeServiceCorner_EventScript_TryPurchasePrize
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

BattleFrontier_ExchangeServiceCorner_Text_YouAlreadyHaveThis:
	.string "Ya tienes este objeto.$"

BattleFrontier_ExchangeServiceCorner_EventScript_OldWTMan_Text:
	.string "¡Hola! Si buscas el WONDERTRADE,\n"
	.string "está ahora en cada POKéMON CENTER.\l"
	.string "¡Diviértete!$"

BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize:
	.string "Hola, este es el RINCÓN DEL\n"
	.string "SERVICIO DE INTERCAMBIO.\p"
	.string "Cambiamos tus Puntos de Batalla por\n"
	.string "lindos premios.\p"
	.string "Elige un premio de la lista.$"

@ Unused
BattleFrontier_ExchangeServiceCorner_Text_PleaseChoosePrize:
	.string "Elige un premio de la lista.$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmTreeckoDoll:
	.string "Elegiste el PÓSTER DE BESOS.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmTorchicDoll:
	.string "Elegiste el COJÍN DE BESOS.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmMudkipDoll:
	.string "Elegiste el MUÑECO SMOOCHUM.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmTogepiDoll:
	.string "Elegiste el MUÑECO TOGEPI.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmMeowthDoll:
	.string "Elegiste el MUÑECO DE MEOWTH.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmClefairyDoll:
	.string "Elegiste el MUÑECO DE CLEFAIRY.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmDittoDoll:
	.string "Elegiste el MUÑECO DE DITTO.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmCyndaquilDoll:
	.string "Elegiste el MUÑECO DE CYNDAQUIL.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmChikoritaDoll:
	.string "Elegiste el MUÑECO DE CHIKORITA.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmTotodileDoll:
	.string "Elegiste el MUÑECO DE TOTODILE.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmLaprasDoll:
	.string "Elegiste el MUÑECO DE LAPRAS.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmSnorlaxDoll:
	.string "Elegiste el MUÑECO DE SNORLAX.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmVenusaurDoll:
	.string "Elegiste el MUÑECO DE VENUSAUR.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmCharizardDoll:
	.string "Elegiste el MUÑECO DE CHARIZARD.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmBlastoiseDoll:
	.string "Elegiste el MUÑECO DE BLASTOISE.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmEonTicket:
	.string "Elegiste el TICKET EON.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmMysticTicket:
	.string "Elegiste el TICKET MÍSTICO.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmAuroraTicket:
	.string "Elegiste el TICKET AURORA.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmOldMap:
	.string "Elegiste el MAPA ANTIGUO.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmBrace:
	.string "Elegiste la PRENDA FUERTE.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmUpgrade:
	.string "Elegiste el UP GRADE.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmBrightpowder:
	.string "Elegiste el BRIGHTPOWDER.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmWhiteHerb:
	.string "Elegiste la WHITE HERB.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmQuickClaw:
	.string "Elegiste la QUICK CLAW.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmMentalHerb:
	.string "Elegiste la MENTAL HERB.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmChoiceBand:
	.string "Elegiste la CHOICE BAND.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmKingsRock:
	.string "Elegiste la ROCA DEL REY.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmFocusBand:
	.string "Elegiste la FOCUS BAND.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmScopeLens:
	.string "Elegiste LENTE MIRADA.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_ConfirmLeftovers:
	.string "Elegiste RESTOS.\n"
	.string "¿Es correcto?$"

BattleFrontier_ExchangeServiceCorner_Text_WellSendItToPC:
	.string "¡Gracias!\n"
	.string "Lo enviaremos a tu PC en casa.$"

BattleFrontier_ExchangeServiceCorner_Text_HereIsYourPrize:
	.string "¡Aquí tienes tu premio!$"

BattleFrontier_ExchangeServiceCorner_Text_DontHaveEnoughPoints:
	.string "Lo siento mucho…\n"
	.string "No te alcanzan los Puntos de Combate…$"

BattleFrontier_ExchangeServiceCorner_Text_PCIsFull:
	.string "Lo siento mucho...\n"
	.string "Tu PC parece estar llena...$"

BattleFrontier_ExchangeServiceCorner_Text_DontHaveSpaceToHoldIt:
	.string "Lo siento mucho...\n"
	.string "No tienes espacio para llevarlo...$"

BattleFrontier_ExchangeServiceCorner_Text_ThankYouVisitWithPoints:
	.string "Muchas gracias.\p"
	.string "Vuelve cuando hayas ahorrado\n"
	.string "más Puntos de Batalla.$"

BattleFrontier_ExchangeServiceCorner_Text_WishIHadAllDolls:
	.string "¡Oh, son tan lindos!\n"
	.string "¡Desearía tenerlos!\l"
	.string "¡Cojines lindos!\l"
	.string "¡MUÑECOS grandes!\l"
	.string "¡MUÑECOS pequeños!\l"
	.string "¡Quisiera tenerlos todos!$"

BattleFrontier_ExchangeServiceCorner_Text_GetYouAnythingYouWant:
	.string "¡Déjaselo a tu mami!\p"
	.string "Si es algo que quieras, ¡haré lo\n"
	.string "que sea para conseguirlo, cielo!$"

BattleFrontier_ExchangeServiceCorner_Text_ItemsWillGetMonTougher:
	.string "Si consigo los objetos de aquí,\n"
	.string "mis POKéMON serán más fuertes.\p"
	.string "¡Seguro que lo serán!\n"
	.string "¡No hay duda de ello!$"

BattleFrontier_ExchangeServiceCorner_Text_GoGetYourOwnDoll:
	.string "¿Eh?\n"
	.string "¿Qué estás mirando?\p"
	.string "No me gusta que mires mi muñeco\n"
	.string "de esa forma.\p"
	.string "¡Si lo quieres, ve por uno tú!\n"
	.string "¿Verdad, SMOOCHUM?$"

BattleFrontier_ExchangeServiceCorner_Text_MoreBattlePointsForRecord:
	.string "¿Lo sabías?\p"
	.string "Si superas tu récord en cualquier\n"
	.string "lugar de BATALLA, te darán\l"
	.string "más y más Puntos de Batalla.$"

BattleFrontier_ExchangeServiceCorner_Text_TreeckoDollDesc::
	.string "UN MUÑECO DE TREECKO.\n"
	.string "Ponlo sobre un tapete o un escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_TorchicDollDesc::
	.string "UN MUÑECO DE TORCHIC.\n"
	.string "Ponlo sobre un tapete o un escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_MudkipDollDesc::
	.string "UN MUÑECO DE MUDKIP.\n"
	.string "Ponlo sobre un tapete o un escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_TogepiDollDesc::
	.string "MUÑECO DE TOGEPI.\n"
	.string "Ponlo en un tapete o escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_MeowthDollDesc::
	.string "MUÑECO DE MEOWTH.\n"
	.string "Ponlo en un tapete o escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_ClefairyDollDesc::
	.string "MUÑECO DE CLEFAIRY.\n"
	.string "Ponlo en un tapete o escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_DittoDollDesc::
	.string "MUÑECO DE DITTO.\n"
	.string "Ponlo en un tapete o escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_CyndaquilDollDesc::
	.string "MUÑECO DE CYNDAQUIL.\n"
	.string "Ponlo en un tapete o escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_ChikoritaDollDesc::
	.string "MUÑECO DE CHIKORITA.\n"
	.string "Ponlo en un tapete o escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_TotodileDollDesc::
	.string "MUÑECO DE TOTODILE.\n"
	.string "Ponlo en un tapete o escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_LargeDollDesc::
	.string "UN MUÑECO grande.\n"
	.string "Ponlo en un tapete o escritorio.$"

BattleFrontier_ExchangeServiceCorner_Text_ProteinDesc::
	.string "Sube el ATK de un\n"
	.string "POKéMON.$"

BattleFrontier_ExchangeServiceCorner_Text_CalciumDesc::
	.string "Sube el ATK ESP. de un\n"
	.string "POKéMON.$"

BattleFrontier_ExchangeServiceCorner_Text_IronDesc::
	.string "Sube la DEF de un\n"
	.string "POKéMON.$"

BattleFrontier_ExchangeServiceCorner_Text_ZincDesc::
	.string "Sube la DEF ESP. de un\n"
	.string "POKéMON.$"

BattleFrontier_ExchangeServiceCorner_Text_CarbosDesc::
	.string "Sube la VEL de un\n"
	.string "POKéMON.$"

BattleFrontier_ExchangeServiceCorner_Text_HPUpDesc::
	.string "Sube los PS de un POKéMON.$"

BattleFrontier_ExchangeServiceCorner_Text_LeftoversDesc::
	.string "Objeto que recupera los PS\n"
	.string "poco a poco en combate.$"

BattleFrontier_ExchangeServiceCorner_Text_WhiteHerbDesc::
	.string "Objeto que restaura cualquier\n"
	.string "estadística bajada.$"

BattleFrontier_ExchangeServiceCorner_Text_QuickClawDesc::
	.string "Objeto que a veces permite\n"
	.string "atacar primero.$"

BattleFrontier_ExchangeServiceCorner_Text_MentalHerbDesc::
	.string "Objeto que cura el enamoramiento\n"
	.string "del POKéMON.$"

BattleFrontier_ExchangeServiceCorner_Text_BrightpowderDesc::
	.string "Objeto que lanza una mirada para\n"
	.string "bajar la precisión.$"

BattleFrontier_ExchangeServiceCorner_Text_ChoiceBandDesc::
	.string "Sube el poder de un movimiento,\n"
	.string "pero solo permite usar ese.$"

BattleFrontier_ExchangeServiceCorner_Text_KingsRockDesc::
	.string "Objeto que puede causar retroceso\n"
	.string "al golpear al rival.$"

BattleFrontier_ExchangeServiceCorner_Text_FocusBandDesc::
	.string "Objeto que a veces evita que el\n"
	.string "POKéMON se debilite.$"

BattleFrontier_ExchangeServiceCorner_Text_ScopeLensDesc::
	.string "Objeto que aumenta la tasa de\n"
	.string "golpes críticos.$"

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
	.string "¡Bienvenido a la ESTACIÓN de\n"
	.string "INTERCAMBIO SORPRESA!\p"
	.string "Elige el POKéMON que quieres\n"
	.string "intercambiar.$"

EventScript_NoMoreForToday_Text:
	.string "¡Oh! Parece que ya usaste\n"
	.string "los 3 INTERCAMBIOS DIARIOS.\p"
	.string "¡Vuelve mañana!$"

EventScript_FirstTimeWonder_Text:
	.string "¡Hola, entrenador!\p"
	.string "¿Es tu primera vez usando el\n"
	.string "SISTEMA WONDERTRADE?\p"
	.string "WONDERTRADE es tecnología de\n"
	.string "DEVON CORP. para INTERCAMBIOS\p"
	.string "anónimos. Envías un POKéMON\n"
	.string "elegido a alguien y esa persona\p"
	.string "te envía otro a cambio.\n"
	.string "Ni tú ni el otro entrenador\p"
	.string "saben qué POKéMON aparecerá.\n"
	.string "¡Esa es la gracia de\p"
	.string "WONDERTRADE! Para no saturar el\n"
	.string "servidor, hay un máximo de 3\p"
	.string "WONDERTRADES DIARIOS.\p"
	.string "¡Esperamos que tengas una gran\n"
	.string "experiencia con WONDERTRADE!$"

EventScript_FirstTimeWonder_Text_Unlimited:
	.string "¡Hola, entrenador!\p"
	.string "¿Es tu primera vez usando el\n"
	.string "SISTEMA WONDERTRADE?\p"
	.string "WONDERTRADE es tecnología de\n"
	.string "DEVON CORP. para INTERCAMBIOS\p"
	.string "anónimos. Envías un POKéMON\n"
	.string "elegido a alguien y esa persona\p"
	.string "te envía otro a cambio.\n"
	.string "Ni tú ni el otro entrenador\p"
	.string "saben qué POKéMON aparecerá.\n"
	.string "¡Esa es la gracia de\l"
	.string "WONDERTRADE!\p"
	.string "¡Esperamos que tengas una gran\n"
	.string "experiencia con WONDERTRADE!$"

EventScript_DoWonderTrade_Text_Done:
	.string "¡Esperamos que hayas tenido un\n"
	.string "buen WONDERTRADE!$"

EventScript_DoWonderTrade_Text_Challenges:
	.string "Parece que tienes desafíos\n"
	.string "activos. Vuelve después de la\l"
	.string "LIGA POKéMON.$"

EventScript_DoWonderTrade_Text_FiveBadges:
	.string "Lamentablemente, el SISTEMA\n"
	.string "WONDERTRADE no está activo.\l"
	.string "Vuelve más tarde.$"
