.set LOCALID_CELADON_FALKNER, 5

CeladonCity_DepartmentStore_5F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDept5_EventScript_Gent::
	msgbox CeladonDeptStore5F_Text_Gentleman, MSGBOX_NPC
	end
CeladonDept5_EventScript_Sailor::
	msgbox CeladonDeptStore5F_Text_Sailor, MSGBOX_NPC
	end
CeladonDept5_EventScript_Teacher::
	msgbox CeladonDeptStore5F_Text_Teacher, MSGBOX_NPC
	end
CeladonDept5_EventScript_Directory::
	msgbox CeladonDeptStore5F_Text_Directory, MSGBOX_SIGN
	end

CeladonDeptStore5_EventScript_Falkner::
	lock
	faceplayer
	msgbox CeladonDeptStore5_Text_Falkner, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_CELADON_FALKNER
	removeobject LOCALID_CELADON_FALKNER
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_FALKNER
	release
	end

CeladonDeptStore5_Text_Falkner:
	.string "{PLAYER}. No esperaba verte\n"
	.string "por aquí.\p"
	.string "Busco equipo para mis\n"
	.string "POKéMON voladores.\p"
	.string "Si quieres luchar, estaré en el\n"
	.string "DOJO de CIUDAD AZAFRÁN.$"

CeladonDeptStore5F_Text_Gentleman:
	.string "Quiero comprar objetos que suban\n"
	.string "las estadísticas, pero no\l"
	.string "tengo suficiente dinero…$"

CeladonDeptStore5F_Text_Sailor:
	.string "Quiero PP UP para subir el\n"
	.string "PP de los ataques. Pero no se vende…$"

CeladonDeptStore5F_Text_Teacher:
	.string "Usar objetos hace felices a los\n"
	.string "POKéMON.\p"
	.string "Aunque odian ciertos objetos…$"

CeladonDeptStore5F_Text_Directory:
	.string "5F: FARMACIA$"
