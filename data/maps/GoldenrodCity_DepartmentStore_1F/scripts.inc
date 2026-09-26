GoldenrodCity_DepartmentStore_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore1_EventScript_Receptionist::
	lock
	faceplayer
	msgbox GoldenrodDeptStor1_Text_Receptionist, MSGBOX_DEFAULT
	closemessage
	release
	end
GoldenrodDeptStore1_EventScript_Gentleman::
	lock
	faceplayer
	msgbox GoldenrodDeptStore1_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end
GoldenrodDeptStore1_EventScript_PokefanF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore1_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end
GoldenrodDeptStore1_EventScript_BugCatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore1_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore1_EventScript_Directory::
	lock
	msgbox GoldenrodDeptStore1_Text_Directory, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodDeptStor1_Text_Receptionist:
    .string "Bienvenido a ALMACENES TRIGAL.$"

GoldenrodDeptStore1_Text_Gentleman:
    .string "El DEPT.STORE tiene una buena\n"
    .string "selección.\p"
    .string "Pero algunos objetos solo están\n"
    .string "en el GAME CORNER.$"

GoldenrodDeptStore1_Text_PokefanF:
    .string "¡Tengo ganas de comprar hoy otra vez!$"

GoldenrodDeptStore1_Text_BugCatcher:
    .string "Mamá es buena buscando ofertas.\p"
    .string "Siempre compra cosas a precios\n"
    .string "más bajos.$"

GoldenrodDeptStore1_Text_Directory:
    .string "1F MOSTRADOR DE SERVICIO\n"
	.string "ESTÁS AQUÍ.\p"
    .string "2F MERCADO ENTRENADOR\p"
    .string "3F COLECCIÓN BATALLA\p"
    .string "4F CAJA DE MEDICINAS\p"
    .string "5F RINCÓN MT\p"
    .string "6F PLAZA TRANQUILA\p"
    .string "MIRADOR DE LA AZOTEA$"
