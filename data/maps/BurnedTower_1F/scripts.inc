.set LOCALID_BURNED_TOWER_SILVER, 3
.set LOCALID_BURNED_TOWER_EUSINE, 1

BurnedTower_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BurnedTower_1F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BurnedTower_1F_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BurnedTower_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

BurnedTower_1F_OnTransition: 
	callnative SetTimeBasedEncounters
	end

BurnedTower_1F_OnLoad::
	goto_if_ge VAR_ECRUTEAK_CITY_STATE, 4, BurnedTower_1F_MapScript_CreateHole
	end

BurnedTower_1F_MapScript_CreateHole::
	setmetatile 16, 12, 0x37E, FALSE
	end

BurnedTower_1F_OnFrame::
	map_script_2 VAR_ECRUTEAK_CITY_STATE, 1, BurnedTower_1F_EventScript_MeetEusine
	.2byte 0

BurnedTower_1F_EventScript_MeetEusine::
	lock
	playse SE_PIN
	applymovement LOCALID_BURNED_TOWER_EUSINE, Common_Movement_ExclamationMark
	delay 60
	applymovement LOCALID_BURNED_TOWER_EUSINE, BurnedTower_Movement_Eusine1
	waitmovement 0
	msgbox BurnedTower_1FEusineIntroText, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BURNED_TOWER_EUSINE, BurnedTower_Movement_Eusine2
	waitmovement 0
	setvar VAR_ECRUTEAK_CITY_STATE, 2
	release
	end

BurnedTower_Movement_Eusine1:
	walk_down
	walk_down
	step_end

BurnedTower_Movement_Eusine2:
	walk_up
	walk_up
	step_end


BurnedTower_1FEusineIntroText:
	.string "EUSINE: Me llamo EUSINE.\p"
	.string "Sigo el rastro de un POKéMON\n"
	.string "llamado SUICUNE.\p"
	.string "¿Y tú eres...?\p"
	.string "¿{PLAYER}? ¡Mucho gusto!\p"
	.string "Oí que SUICUNE podría estar en\n"
	.string "la TORRE QUEMADA, así que vine\l"
	.string "a investigar.\p"
	.string "Pero, ¿dónde podría estar?$"

BurnedTower_1F_EventScript_Item_HpUp::
	finditem ITEM_HP_UP
	end

BurnedTower_1F_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end

BurnedTower_1F_EventScript_Eusine::
	lock
	faceplayer
	msgbox BurnedTower_1FEusineText, MSGBOX_DEFAULT
	closemessage
	release
	end

BurnedTower_1F_EventScript_Morty::
	lock
	faceplayer
	msgbox BurnedTower_1FMortyText, MSGBOX_DEFAULT
	closemessage
	release
	end

BurnedTower_1FEusineText:
	.string "EUSINE: Oí que SUICUNE podría\n"
	.string "estar en la TORRE QUEMADA, así\l"
	.string "que vine a investigar.\p"
	.string "Pero, ¿dónde podría estar?$"

BurnedTower_1FMortyText:
	.string "MORTY: El LÍDER del GIMNASIO de\n"
	.string "CIUDAD IRIS debe estudiar a los\l"
	.string "legendarios POKéMON--\l"
	.string "SUICUNE, ENTEI y RAIKOU.\p"
	.string "EUSINE está aquí, así que\n"
	.string "decidí investigar la\l"
	.string "TORRE con él.$"

BurnedTower_1F_EventScript_Silver::
	lock
	playse SE_PIN
	applymovement LOCALID_BURNED_TOWER_SILVER, Common_Movement_ExclamationMark
	delay 60
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	applymovement LOCALID_BURNED_TOWER_SILVER, Common_Movement_WalkLeft1
	waitmovement 0
	waitmovement 0
	msgbox BurnedTowerSilver_BeforeText, MSGBOX_DEFAULT
	call_if_eq VAR_STARTER_MON, 0, BurnedTower_1F_Silver_Battle_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, BurnedTower_1F_Silver_Battle_Totodile
	call_if_eq VAR_STARTER_MON, 2, BurnedTower_1F_Silver_Battle_Chikorita
	playbgm MUS_HG_RIVAL_EXIT, TRUE
	msgbox BurnedTowerSilver_AfterText1, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 20  @ num shakes
	setvar VAR_0x8007, 6  @ shake delay
	special ShakeCamera
	waitstate
	playse SE_CLICK
	setmetatile 16, 12, 0x37E, FALSE
	special DrawWholeMapView
	waitse
	delay 60
	special SpawnCameraObject
	removeobject OBJ_EVENT_ID_PLAYER
	playse SE_FALL
	delay 60
	msgbox BurnedTowerSilver_AfterText2, MSGBOX_AUTOCLOSE
	waitmessage
	warphole MAP_BURNED_TOWER_B1F
	setvar VAR_ECRUTEAK_CITY_STATE, 3
	release
	end

BurnedTower_1F_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_3, BurnedTowerSilver_WinText
	return

BurnedTower_1F_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_3, BurnedTowerSilver_WinText
	return

BurnedTower_1F_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_3, BurnedTowerSilver_WinText
	return

BurnedTowerSilver_BeforeText:
	.string "..............................\p"
	.string "...Ah, eres tú.\p"
	.string "Vine buscando a los POKéMON\n"
	.string "legendarios que dicen que\l"
	.string "viven aquí.\p"
	.string "¡Pero no hay nada!\p"
	.string "¿Nada, tras el esfuerzo de\n"
	.string "venir a este basurero?\l"
	.string "¡No puede ser!\p"
	.string "¡Es todo tu culpa!$"

BurnedTowerSilver_WinText:
	.string "...¡Hmph!\p"
	.string "Perdí solo porque mis\n"
	.string "POKéMON son increíblemente débiles.\p"
	.string "Qué patético.$"

BurnedTowerSilver_AfterText1:
	.string "...Bah, da igual.\p"
	.string "De todos modos, jamás podrías\n"
	.string "atrapar a un POKéMON legendario.$"

BurnedTowerSilver_LossText:
	.string "...¡Hmph!\p"
	.string "Por eso odio luchar contra\n"
	.string "cobardes. Es perder el tiempo.$"

BurnedTowerSilver_AfterText2:
	.string "¡Hmph!\p"
	.string "¿Qué haces cayendo en un hueco?\n"
	.string "¡Qué genio!\p"
	.string "¡Te lo mereces!$"

BurnedTower_1F_EventScript_Nard::
	trainerbattle_single TRAINER_NARD BurnedTower_Text_NardSeen, BurnedTower_Text_NardBeaten
	msgbox BurnedTower_Text_NardAfter, MSGBOX_AUTOCLOSE
	end

BurnedTower_1F_EventScript_Richardo::
	trainerbattle_single TRAINER_RICHARDO BurnedTower_Text_RichardoSeen, BurnedTower_Text_RichardoBeaten
	msgbox BurnedTower_Text_RichardoAfter, MSGBOX_AUTOCLOSE
	end

BurnedTower_Text_NardSeen:
	.string "¡No te preocupes!\p"
	.string "¡Los que lanzamos fuego sabemos\n"
	.string "su poder mejor que nadie!$"
BurnedTower_Text_NardBeaten:
	.string "¡Gracias por una batalla ardiente!$"
BurnedTower_Text_NardAfter:
	.string "Esta torre ardió porque\n"
	.string "le cayó un rayo.\p"
	.string "Mi fuego es insignificante\n"
	.string "en comparación...$"

BurnedTower_Text_RichardoSeen:
	.string "¡Practico el robo en la\n"
	.string "TORRE QUEMADA! ¡No intenten\l"
	.string "esto en casa!$"
BurnedTower_Text_RichardoBeaten:
	.string "Pfffffffffffffff.$"
BurnedTower_Text_RichardoAfter:
	.string "Tal vez la vida criminal\n"
	.string "no es para mí...$"
