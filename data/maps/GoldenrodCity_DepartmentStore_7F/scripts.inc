.set LOCALID_GOLDENROD_ROOF_NERD, 1

GoldenrodCity_DepartmentStore_7F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodCity_DepartmentStore_7F_OnTransition
	.byte 0

GoldenrodCity_DepartmentStore_7F_OnTransition:
	call_if_set FLAG_DAY_POKEMON, GoldenrodCity_DepartmentStore_7F_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, GoldenrodCity_DepartmentStore_7F_EventScript_SetDay
	end

GoldenrodCity_DepartmentStore_7F_EventScript_SetNight::
	setmaplayoutindex LAYOUT_GOLDENROD_CITY_DEPARTMENT_STORE_7FNIGHT
	return

GoldenrodCity_DepartmentStore_7F_EventScript_SetDay::
	setmaplayoutindex LAYOUT_GOLDENROD_CITY_DEPARTMENT_STORE_7F
	return


GoldenrodDeptStore7_EventScript_PokefanF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofPokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofPokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Twin::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofTwin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Nerd::
	lock
	msgbox GoldenrodDeptStore_Text_RoofSuperNerdOhWow, MSGBOX_DEFAULT
	closemessage
	PLAYSE SE_PIN
	applymovement LOCALID_GOLDENROD_ROOF_NERD, Common_Movement_ExclamationMark
	delay 20
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofSuperNerdQuitBotheringMe, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_ROOF_NERD, DIR_SOUTH
	release
	end

GoldenrodDeptStore7_EventScript_Teacher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Bugcatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofBugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_RoofPokefanF:
    .string "Uff, estoy cansado.\p"
    .string "A veces subo a la azotea\n"
    .string "para descansar de las compras.$"

GoldenrodDeptStore_Text_RoofFisher:
    .string "¿Perdón? ¿Quién dice que un adulto\n"
    .string "no puede hacer esto?\p"
    .string "¡Volveré cada día hasta tener\n"
    .string "todos los muñecos!$"

GoldenrodDeptStore_Text_RoofTwin:
    .string "Aquí hacen ofertas muy buenas\n"
    .string "seguido.$"

GoldenrodDeptStore_Text_RoofSuperNerdOhWow:
    .string "¡Oh, vaya!$"

GoldenrodDeptStore_Text_RoofSuperNerdQuitBotheringMe:
    .string "¿Puedes dejar de molestarme?$"

GoldenrodDeptStore_Text_RoofPokefanM:
    .string "Hay algo que quiero mucho,\n"
    .string "pero no tengo el dinero...\p"
    .string "Tal vez venda las BAYAS que\n"
    .string "he recolectado...$"

GoldenrodDeptStore_Text_RoofTeacher:
    .string "¡Oh, todo es tan barato!\p"
    .string "¡Compré tanto que mi PACK está lleno!$"

GoldenrodDeptStore_Text_RoofBugCatcher:
    .string "Mis POKéMON siempre se paralizan o\n"
    .string "envenenan en el peor momento...\p"
    .string "Vine a comprar FULL HEAL.\p"
    .string "¿Me pregunto si quedará alguno?$"
