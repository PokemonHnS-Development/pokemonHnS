VermilionCity_Mart_MapScripts::
	.byte 0

VermilionCity_Mart_EventScript_BirdMan::
	msgbox VermilionMart_Text_SuperNerd, MSGBOX_NPC
	end

VermilionCity_Mart_EventScript_Woman::
	msgbox VermilionMart_Text_Beauty, MSGBOX_NPC
	end

VermilionMart_Text_SuperNerd:
	.string "El TEAM ROCKET ya no está en\n"
	.string "KANTO.\p"
	.string "Solo eso me hace feliz.$"

VermilionMart_Text_Beauty:
	.string "Pienso ir de compras\n"
	.string "a CIUDAD AZAFRÁN.$"
