EcruteakCity_Mart_MapScripts::
	.byte 0

EcruteakCity_Mart_EventScript_Nerd::
	lock
	faceplayer
	msgbox EcruteakMart_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Mart_EventScript_Granny::
	lock
	faceplayer
	msgbox EcruteakMart_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakMart_Text_SuperNerd:
	.string "Mi EEVEE evolucionó a ESPEON.\p"
	.string "Pero el EEVEE de mi amigo fue un\n"
	.string "UMBREON.\p"
	.string "¿Por qué? Criamos a nuestros\n"
	.string "EEVEE de la misma forma...$"

EcruteakMart_Text_Granny:
	.string "Si usas REVIVE, un POKéMON que\n"
	.string "esté debilitado despertará.$"
