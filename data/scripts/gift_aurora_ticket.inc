MysteryGiftScript_AuroraTicket::
	setvaddress MysteryGiftScript_AuroraTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_AURORA_TICKET, AuroraTicket_Obtained
	vgoto_if_set FLAG_BATTLED_DEOXYS, AuroraTicket_Obtained
	checkitem ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, TRUE, AuroraTicket_Obtained
	vmessage sText_AuroraTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, AuroraTicket_NoBagSpace
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	setflag FLAG_RECEIVED_AURORA_TICKET
	vmessage sText_AuroraTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_NoBagSpace:
	vmessage sText_AuroraTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_Obtained:
	vmessage sText_AuroraTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_AuroraTicketForYou:
	.string "Gracias por usar el sistema de\n"
	.string "REGALO MISTERIOSO.\p"
	.string "Tú debes ser {PLAYER}.\n"
	.string "Tengo un ticket para ti.$"

sText_AuroraTicketUseAtPort:
	.string "Parece ser para usarlo en el\n"
	.string "puerto de CIUDAD VERALTO.\p"
	.string "¿Por qué no lo pruebas para ver\n"
	.string "de qué se trata?$"

sText_AuroraTicketThankYou:
	.string "Gracias por usar el sistema de\n"
	.string "REGALO MISTERIOSO.$"

sText_AuroraTicketBagFull:
	.string "Lo siento, {PLAYER}.\n"
	.string "El BOLSILLO OBJETOS CLAVE está lleno.\p"
	.string "Guarda algo en tu PC,\n"
	.string "y luego vuelve por esto.$"
