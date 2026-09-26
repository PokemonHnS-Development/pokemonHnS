SSTidalLowerDeck_MapScripts::
	.byte 0

SSTidalLowerDeck_EventScript_Phillip::
	trainerbattle_single TRAINER_PHILLIP, SSTidalLowerDeck_Text_PhillipIntro, SSTidalLowerDeck_Text_PhillipDefeat
	msgbox SSTidalLowerDeck_Text_PhillipPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_EventScript_Leonard::
	trainerbattle_single TRAINER_LEONARD, SSTidalLowerDeck_Text_LeonardIntro, SSTidalLowerDeck_Text_LeonardDefeat
	msgbox SSTidalLowerDeck_Text_LeonardPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_Text_PhillipIntro:
	.string "¡Argh! ¡Estoy harto y agotado de\n"
	.string "limpiar este lugar tan grande!\p"
	.string "¡Tengamos una batalla rápida!$"

SSTidalLowerDeck_Text_PhillipDefeat:
	.string "¡Hermano, perdí!$"

SSTidalLowerDeck_Text_PhillipPostBattle:
	.string "¡Somos los HERMANOS LIMPIEZA!\p"
	.string "¡El mayor echa el detergente,\n"
	.string "y el menor se encarga de fregar!$"

SSTidalLowerDeck_Text_LeonardIntro:
	.string "Este es el fondo del casco del barco.\n"
	.string "Hay mucho espacio.\l"
	.string "Estará bien para una batalla POKéMON.$"

SSTidalLowerDeck_Text_LeonardDefeat:
	.string "¡Hermano, perdí!$"

SSTidalLowerDeck_Text_LeonardPostBattle:
	.string "¡Somos los HERMANOS LIMPIEZA!\p"
	.string "¡El mayor echa el detergente,\n"
	.string "y el menor se encarga de fregar!$"

