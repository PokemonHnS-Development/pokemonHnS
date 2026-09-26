GoldenrodCity_DepartmentStore_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore2_EventScript_Youngster::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FYoungster, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_CooltrainerF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FCooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_Gent::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FGentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore2_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_2FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_2FYoungster:
    .string "El POKéGEAR guarda hasta 25\n"
    .string "números de teléfono.\p"
    .string "Es difícil decidir qué números\n"
    .string "conservar.$"

GoldenrodDeptStore_Text_2FCooltrainerF:
    .string "Conseguí mi ABRA en el GAME CORNER.\p"
    .string "Ahora es mi mejor compañero.$"

GoldenrodDeptStore_Text_2FGentleman:
    .string "Este DEPT.STORE me hace ver que\n"
    .string "CIUDAD TRIGAL es una gran ciudad.\p"
    .string "La selección aquí no tiene\n"
    .string "comparación.$"

GoldenrodDeptStore_Text_2FDirectory:
    .string "Tu Compañero de Viaje\p"
    .string "2F MERCADO DE ENTRENADORES$"
