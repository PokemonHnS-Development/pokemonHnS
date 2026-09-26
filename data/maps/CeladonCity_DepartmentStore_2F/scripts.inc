CeladonCity_DepartmentStore_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDept2_EventScript_Pokefan::
	msgbox CeladonDeptStore2F_Text_PokefanM, MSGBOX_NPC
	end

CeladonDept2_EventScript_Youngster::
	msgbox CeladonDeptStore2F_Text_Youngster, MSGBOX_NPC
	end

CeladonDept2_EventScript_Directory::
	msgbox CeladonDeptStore2F_Text_Directory, MSGBOX_SIGN
	end

CeladonDeptStore2F_Text_PokefanM:
	.string "Hace poco soy entrenador.\p"
	.string "Mi hijo me animó a hacerlo.\p"
	.string "Me impresiona la variedad de\n"
	.string "objetos útiles.$"

CeladonDeptStore2F_Text_Youngster:
	.string "A mi papá le cuesta aprender\n"
	.string "los nombres de los objetos y\l"
	.string "cómo se deben usar…$"

CeladonDeptStore2F_Text_Directory:
	.string "¡Objetos top para entrenadores!\p"
	.string "2F: MERCADO ENTRENADOR$"

