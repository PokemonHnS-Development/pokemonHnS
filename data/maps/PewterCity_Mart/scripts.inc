PewterCity_Mart_MapScripts::
	.byte 0

PewterCity_Mart_EventScript_Youngster::
	msgbox PewterCity_Mart_Text_Youngster, MSGBOX_NPC
	end

PewterCity_Mart_EventScript_Nerd::
	msgbox PewterCity_Mart_Text_SuperNerd, MSGBOX_NPC
	end

PewterCity_Mart_Text_Youngster:
	.string "¡Hola! ¡Mira mi GYARADOS!\p"
	.string "Lo crié desde MAGIKARP. No puedo\n"
	.string "creer lo fuerte que se volvió.$"

PewterCity_Mart_Text_SuperNerd:
	.string "Había un viejo raro que vendía\n"
	.string "MAGIKARP.\p"
	.string "Decía que los MAGIKARP del\n"
	.string "LAGO DE la FURIA eran excelentes.$"

