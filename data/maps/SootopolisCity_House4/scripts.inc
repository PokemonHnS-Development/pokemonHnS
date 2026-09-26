SootopolisCity_House4_MapScripts::
	.byte 0

SootopolisCity_House4_EventScript_Man::
	msgbox SootopolisCity_House4_Text_AncientTreasuresWaitingInSea, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Woman::
	msgbox SootopolisCity_House4_Text_StrollUnderwaterWithPokemon, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SootopolisCity_House4_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SootopolisCity_House4_Text_AncientTreasuresWaitingInSea:
	.string "Escucha, te diré algo\n"
	.string "bueno.\p"
	.string "Se dice que hay una ruina antigua\n"
	.string "en el mar por aquí.\p"
	.string "Podría haber tesoros esperando\n"
	.string "ser descubiertos allá abajo.$"

SootopolisCity_House4_Text_StrollUnderwaterWithPokemon:
	.string "Tesoros antiguos...\p"
	.string "Sería genial que existieran, pero\n"
	.string "aunque no, sería hermoso dar un\l"
	.string "paseo submarino con mis\l"
	.string "POKéMON.$"

SootopolisCity_House4_Text_Azumarill:
	.string "AZUMARILL: Marurii.$"

