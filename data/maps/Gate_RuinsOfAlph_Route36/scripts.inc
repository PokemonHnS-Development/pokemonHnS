Gate_RuinsOfAlph_Route36_MapScripts::
	.byte 0

Gate_RuinsOfAlph_Route36_EventScript_Officer::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route36_Text_Officer, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route36_EventScript_PokefanM::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route36_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route36_EventScript_Youngster::
	lock
	faceplayer
	msgbox Gate_RuinsOfAlph_Route36_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_RuinsOfAlph_Route36_Text_Officer:
	.string "RUINAS ALFA\p"
	.string "Sitio Turístico de Tocar y Ver\p"
	.string "¡Prueba los paneles de piedra!$"

Gate_RuinsOfAlph_Route36_Text_PokefanM:
	.string "¿Estudias las RUINAS?\p"
	.string "Veo que eres un futuro científico.$"

Gate_RuinsOfAlph_Route36_Text_Youngster:
	.string "Hay dibujos en paneles\n"
	.string "de piedra.\p"
	.string "Intenté moverlos.\n"
	.string "Me pregunto qué serán.$"
