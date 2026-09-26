GoldenrodCity_DepartmentStore_3F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore3_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore3_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore3_EventScript_Rocker::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FRocker, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_3FSuperNerd:
    .string "¡Soy, soy muy impaciente!\p"
    .string "Uso X SPEED en batalla para dar\n"
    .string "velocidad a mis POKéMON.$"

GoldenrodDeptStore_Text_3FRocker:
    .string "¡Oye! Al luchar, ¿usas X\n"
    .string "SPECIAL?\p"
    .string "Es genial. ¡Sube mucho el\n"
    .string "ATAQUE ESPECIAL!$"

GoldenrodDeptStore_Text_3FDirectory:
    .string "Para buscadores de victoria\p"
    .string "COLECCIÓN BATALLA 3F$"
