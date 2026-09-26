Gate_RuinsOfAlph_Route32_MapScripts::
	.byte 0


Gate_RuinsOfAlph_Route32_EventScript_PokefanM::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route32_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route32_EventScript_Youngster::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route32_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route32_Text_PokefanM:
	.string "¿Estudias las RUINAS?\n"
	.string "Veo a un futuro científico.$"

Gate_RuinsOfAlph_Route32_Text_Youngster:
	.string "Hay dibujos en paneles\n"
	.string "de piedra.\p"
	.string "Intenté moverlos.\n"
	.string "Me pregunto qué serán.$"
