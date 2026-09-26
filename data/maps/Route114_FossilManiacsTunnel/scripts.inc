.set LOCALID_FOSSIL_MANIAC, 1

Route114_FossilManiacsTunnel_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsTunnel_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route114_FossilManiacsTunnel_OnLoad
	.byte 0

Route114_FossilManiacsTunnel_OnTransition:
	call_if_set FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac
	end

Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac::
	setobjectxyperm LOCALID_FOSSIL_MANIAC, 6, 5
	setobjectmovementtype LOCALID_FOSSIL_MANIAC, MOVEMENT_TYPE_FACE_DOWN
	return

Route114_FossilManiacsTunnel_OnLoad:
	call_if_unset FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass
	end

Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass::
	setmetatile 6, 1, METATILE_Fallarbor_RedRockWall, TRUE
	setmetatile 6, 2, METATILE_Fallarbor_RedRockWall, TRUE
	return

Route114_FossilManiacsTunnel_EventScript_ManiacMentionCaveIn::
	lockall
	applymovement LOCALID_FOSSIL_MANIAC, Common_Movement_WalkInPlaceFasterUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Route114_FossilManiacsTunnel_Text_NotSafeThatWay, MSGBOX_DEFAULT
	setvar VAR_FOSSIL_MANIAC_STATE, 2
	releaseall
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REVIVED_FOSSIL_MON, Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	msgbox Route114_FossilManiacsTunnel_Text_LookInDesertForFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil::
	msgbox Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil::
	msgbox Route114_FossilManiacsTunnel_Text_FossilsAreWonderful, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_Text_LookInDesertForFossils:
	.string "Soy el MANÍACO FÓSIL…\n"
	.string "Amo los FÓSILES… soy buen tipo…\p"
	.string "¿Quieres un FÓSIL?\p"
	.string "Pero los FÓSILES de por aquí\n"
	.string "son todos míos… Nada para ti…\p"
	.string "Si no puedes vivir sin un\n"
	.string "FÓSIL, busca en un desierto con\l"
	.string "rocas y arena que puedan ocultar\l"
	.string "FÓSILES…$"

Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils:
	.string "Hallaste un FÓSIL, ¿verdad?\n"
	.string "Qué lindo… Es un sueño…\p"
	.string "¿Qué harás con ese\n"
	.string "FÓSIL?\p"
	.string "He oído que DEVON investiga\n"
	.string "cómo revivir POKéMON desde\l"
	.string "FÓSILES…\p"
	.string "Amo mis FÓSILES, jamás\n"
	.string "haría algo así…$"

Route114_FossilManiacsTunnel_Text_FossilsAreWonderful:
	.string "Los FÓSILES son… Maravillosos…\n"
	.string "Es un sueño…$"

Route114_FossilManiacsTunnel_Text_NotSafeThatWay:
	.string "Oh…\n"
	.string "No es seguro ir por ahí…\p"
	.string "Estaba excavando, ¿sabes…\n"
	.string "cuando toda la pared cayó…\p"
	.string "Creo que ahora hay una caverna\n"
	.string "gigante debajo…\p"
	.string "La dejé así porque no creo que\n"
	.string "haya FÓSILES allí…$"

