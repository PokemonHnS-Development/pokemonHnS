Route10_PowerPlantBackRoom_MapScripts::
	.byte 0


Route10_PowerPlantBackRoom_EventScript_Manager::
	lock
	faceplayer
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 0, Route10_PowerPlantBackRoom_EventScript_ManagerInitial
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 1, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 2, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 3, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 4, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 5, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 6, Route10_PowerPlantBackRoom_EventScript_ManagerCheckPart
	goto_if_ge VAR_KANTO_ROCKET_STORY_STATE, 7, Route10_PowerPlantBackRoom_EventScript_ManagerDone
	msgbox Route10_PowerPlantBackRoom_Text_ManagerMyBelovedGenerator, MSGBOX_DEFAULT
	closemessage
	release
	end

Route10_PowerPlantBackRoom_EventScript_ManagerInitial::
	msgbox Route10_PowerPlantBackRoom_Text_ManagerWhoWouldRuinMyGenerator, MSGBOX_DEFAULT
	closemessage
	setvar VAR_KANTO_ROCKET_STORY_STATE, 1
	release
	end

Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket::
	msgbox Route10_PowerPlantBackRoom_Text_ManagerIWontForgiveCulprit, MSGBOX_DEFAULT
	closemessage
	release
	end

Route10_PowerPlantBackRoom_EventScript_ManagerCheckPart::
	checkitem ITEM_MACHINE_PART
	goto_if_eq VAR_RESULT, FALSE, Route10_PowerPlantBackRoom_EventScript_ManagerDuringRocket
	removeitem ITEM_MACHINE_PART
	msgbox Route10_PowerPlantBackRoom_Text_ManagerThatsThePart, MSGBOX_DEFAULT
	msgbox Route10_PowerPlantBackRoom_Text_ManagerTakeThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDER
	msgbox Route10_PowerPlantBackRoom_Text_ManagerTM07IsZapCannon, MSGBOX_DEFAULT
	closemessage
	setvar VAR_KANTO_ROCKET_STORY_STATE, 7
	clearflag FLAG_HIDE_ROUTE25_MISTY
	setvar VAR_CERULEAN_CITY_STATE, 2
	setflag FLAG_HIDE_POWER_PLANT_ENGINEER
	setflag FLAG_RETURNED_MACHINE_PART
	release
	end

Route10_PowerPlantBackRoom_EventScript_ManagerDone::
	msgbox Route10_PowerPlantBackRoom_Text_ManagerMyBelovedGenerator, MSGBOX_DEFAULT
	closemessage
	release
	end

Route10_PowerPlantBackRoom_EventScript_Engineer::
	msgbox Route10_PowerPlantBackRoom_Text_Engineer, MSGBOX_NPC
	end

Route10_PowerPlantBackRoom_Text_ManagerWhoWouldRuinMyGenerator:
	.string "GERENTE: ¡Yo, yo, estoy listo para\n"
	.string "fulminar a alguien!\p"
	.string "¿Quién se atrevió a arruinar mi\n"
	.string "generador?\p"
	.string "¡Le dediqué mucho tiempo!\p"
	.string "¡Si lo atrapo, probará mi\n"
	.string "CAÑÓN ELÉCTRICO!$"

Route10_PowerPlantBackRoom_Text_ManagerIWontForgiveCulprit:
	.string "GERENTE: ¡No lo perdonaré!\p"
	.string "El culpable puede llorar y\n"
	.string "pedir perdón,\p"
	.string "¡pero aun así lo aplastaré!\p"
	.string "¡Gajajajaja!$"

Route10_PowerPlantBackRoom_Text_ManagerThatsThePart:
	.string "GERENTE: ¡Ah! ¡Sí!\p"
	.string "¡Es la PIEZA que faltaba de mi\n"
	.string "querido generador! ¿La hallaste?$"

Route10_PowerPlantBackRoom_Text_ManagerTakeThisTM:
	.string "¡Jajaja! ¡Gracias!\p"
	.string "¡Toma esta MT como recompensa!$"

Route10_PowerPlantBackRoom_Text_ManagerTM07IsZapCannon:
	.string "GERENTE: Esa MT es RAYO.\p"
	.string "¡Es una técnica poderosa!\p"
	.string "No es lo que alguien diría que\n"
	.string "es preciso, ¡pero pega\l"
	.string "muy fuerte!$"

Route10_PowerPlantBackRoom_Text_ManagerMyBelovedGenerator:
	.string "GERENTE: ¡Mi querido generador!\p"
	.string "¡Sigue bombeando electricidad!$"

Route10_PowerPlantBackRoom_Text_Engineer:
	.string "La puerta es insegura sin energía.$"

