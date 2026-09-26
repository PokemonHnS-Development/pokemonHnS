CeladonCity_DepartmentStore_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDept1_EventScript_Receptionsit::
    msgbox CeladonDeptStore_Text_1FReceptionist, MSGBOX_NPC
    end

CeladonDept1_EventScript_Gent::
    msgbox CeladonDeptStore_Text_1FGentleman, MSGBOX_NPC
    end

CeladonDept1_EventScript_Teacher::
    msgbox CeladonDeptStore_Text_1FTeacher, MSGBOX_NPC
    end

CeladonDept1_EventScript_Directory::
    msgbox CeladonDeptStore_Text_1FDirectory, MSGBOX_SIGN
    end

CeladonDeptStore_Text_1FReceptionist:
    .string "¡Hola! Bienvenido a los ALMACENES\n"
    .string "CELADON.\p"
    .string "El directorio está en la pared.$"

CeladonDeptStore_Text_1FGentleman:
    .string "Estos ALMACENES son de la misma\n"
    .string "cadena que los de CIUDAD TRIGAL.\p"
    .string "Ambos fueron renovados al mismo\n"
    .string "tiempo.$"

CeladonDeptStore_Text_1FTeacher:
    .string "Es mi primera vez aquí.\p"
    .string "Es tan grande...\p"
    .string "Tengo miedo de perderme.$"

CeladonDeptStore_Text_1FDirectory:
    .string "1F: MOSTRADOR DE SERVICIO\p"
    .string "2F: MERCADO DE ENTRENADORES\p"
    .string "3F: TIENDA DE MT\p"
    .string "4F: REGALOS DE SABIOS\p"
    .string "5F: FARMACIA\p"
    .string "6F: PLAZA DE LA AZOTEA$"
