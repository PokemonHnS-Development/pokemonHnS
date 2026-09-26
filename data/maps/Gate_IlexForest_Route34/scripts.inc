Gate_IlexForest_Route34_MapScripts::
	.byte 0

Route34IlexForestGate_EventScript_Lass::
	lock
	faceplayer
	msgbox Route34IlexForestGate_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34IlexForestGate_EventScript_Butterfree::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_BUTTERFREE, CRY_MODE_NORMAL
	msgbox Route34IlexForestGate_Text_Butterfree, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route34IlexForestGate_Text_Lass:
	.string "¿Viste el santuario al\n"
	.string "protector?\p"
	.string "Vigila el BOSQUE desde\n"
	.string "más allá del tiempo.\p"
	.string "Creo que debe ser un\n"
	.string "POKéMON tipo PLANTA.$"

Route34IlexForestGate_Text_Butterfree:
	.string "BUTTERFREE: ¡Freeh!$"
