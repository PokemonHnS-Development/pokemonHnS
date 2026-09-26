FuchsiaCity_House2_MapScripts::
	.byte 0

FuchsiaCity_House2_EventScript_Granddaughter::	
	goto_if_set FLAG_TEMP_1, FuchsiaCity_House2_EventScript_Granddaughter2
	msgbox FuchsiaCity_House2_Text_WardensGranddaughter1, MSGBOX_NPC
	setflag FLAG_TEMP_1
	end

FuchsiaCity_House2_EventScript_Granddaughter2::
	msgbox FuchsiaCity_House2_Text_WardensGranddaughter2, MSGBOX_NPC
	end

FuchsiaCity_House2_EventScript_Photo::
	msgbox FuchsiaCity_House2_Text_WardenPhoto, MSGBOX_NPC
	end

FuchsiaCity_House2_Text_WardensGranddaughter1:
	.string "Mi abuelo es el GUARDABOSQUES\n"
	.string "de la SAFARI ZONE.\p"
	.string "Bueno, lo era...\p"
	.string "Se fue de vacaciones al extranjero\n"
	.string "él solo.\p"
	.string "Dejó la SAFARI ZONE así\n"
	.string "de repente.$"

FuchsiaCity_House2_Text_WardensGranddaughter2:
	.string "Muchos se decepcionaron porque la\n"
	.string "SAFARI ZONE cerró, pero mi abuelo\l"
	.string "es muy terco...$"

FuchsiaCity_House2_Text_WardenPhoto:
	.string "Es la foto de un anciano sonriente\n"
	.string "rodeado de POKéMON.$"

FuchsiaCity_House2_Text_SafariZonePhoto:
	.string "Es la foto de una gran llanura\n"
	.string "con POKéMON raros jugando.$"
