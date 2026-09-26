CeladonCity_Apartments_1F_MapScripts::
	.byte 0

CeladonCity_Apartments_1F_EventScript_Manager::
	msgbox CeladonMansion_Text_Manager, MSGBOX_NPC
	end

CeladonCity_Apartments_1F_EventScript_Sign::
	msgbox CeladonMansion_Text_ManagersSuiteSign, MSGBOX_SIGN
	end

CeladonMansion_Text_Manager:
	.string "Mis POKéMON me hacen compañía,\n"
	.string "así nunca me siento solo.\p"
	.string "MEOWTH hasta trae dinero a casa.$"

CeladonMansion_Text_ManagersSuiteSign:
	.string "SUITE DEL GERENTE DE LA MANSIÓN$"
