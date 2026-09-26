CeladonCity_DepartmentStore_3F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDept3_EventScript_Youngster::
	msgbox CeladonDeptStore3F_Text_Youngster, MSGBOX_NPC
	end
CeladonDept3_EventScript_Gbakid1::
	msgbox CeladonDeptStore3F_Text_GameboyKid1, MSGBOX_NPC
	end
CeladonDept3_EventScript_Gbakid2::
	msgbox CeladonDeptStore3F_Text_GameboyKid2, MSGBOX_NPC
	end
CeladonDept3_EventScript_SuperNerd::
	msgbox CeladonDeptStore3F_Text_SuperNerd, MSGBOX_NPC
	end
CeladonDept3_EventScript_Directory::
	msgbox CeladonDeptStore3F_Text_Directory, MSGBOX_SIGN
	end

CeladonDeptStore3F_Text_Youngster:
	.string "No sé en qué POKéMON debería\n"
	.string "usar esta MT…$"

CeladonDeptStore3F_Text_GameboyKid1:
	.string "¡Oh, no! Intercambié mi POKéMON\n"
	.string "sin quitarle la MEJORA.$"

CeladonDeptStore3F_Text_GameboyKid2:
	.string "¡Sí! ¡Al fin tendré un\n"
	.string "PORYGON!\p"
	.string "Soy malo en las máquinas, así que\n"
	.string "nunca juntaba monedas...\p"
	.string "...¿Eh?\p"
	.string "¡El PORYGON cambió a un\n"
	.string "POKéMON diferente!$"

CeladonDeptStore3F_Text_SuperNerd:
	.string "La TIENDA MT vende movimientos raros.$"

CeladonDeptStore3F_Text_Directory:
	.string "3F: TIENDA MT\p"
	.string "¡Haz más fuertes a tus POKéMON!$"

