AbandonedShip_CaptainsOffice_MapScripts::
	.byte 0

AbandonedShip_CaptainsOffice_EventScript_CaptSternAide::
	lock
	faceplayer
	goto_if_set FLAG_EXCHANGED_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	checkitem ITEM_SCANNER
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner
	goto_if_set FLAG_ITEM_GARBAGEFLAG, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	msgbox AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner::
	msgbox AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus::
	msgbox AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner:
	.string "Investigo este barco por encargo\n"
	.string "del CAPT. STERN.\p"
	.string "Me pidió buscar un SCANNER,\n"
	.string "pero no he tenido éxito…$"

AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner:
	.string "¡Oh! ¡Eso es un SCANNER!\p"
	.string "Oye, ¿podrías entregárselo\n"
	.string "al CAPT. STERN?\p"
	.string "Quiero investigar este barco un\n"
	.string "poco más.$"

AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus:
	.string "Este barco se llama S.S. CACTUS.\n"
	.string "Parece ser de una era antigua.$"

