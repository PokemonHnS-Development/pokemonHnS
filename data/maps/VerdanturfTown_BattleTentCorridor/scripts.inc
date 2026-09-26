.set LOCALID_ATTENDANT, 1

VerdanturfTown_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VerdanturfTown_BattleTentCorridor_OnFrame
	.byte 0

VerdanturfTown_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	@opendoor 2, 1
	@waitdooranim
	applymovement LOCALID_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	@closedoor 2, 1
	@waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_VERDANTURF_TOWN_BATTLE_TENT_BATTLE_ROOM, 6, 5
	waitstate
	releaseall
	end

VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor:
	walk_up
VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end


@ Leftover text from when this was a Contest Hall in R/S
@ Unused
VerdanturfTown_ContestHall_Text_WhichContestYouEntering:
	.string "¿A qué CONTEST entrarás?\n"
	.string "¿Quieres un consejo?\p"
	.string "En cualquier CONTEST, como el CUTE\n"
	.string "CONTEST, no creo que juzguen solo\l"
	.string "la ternura en la primera ronda.\p"
	.string "Busca formas de entrenar mejor a tus\n"
	.string "POKéMON.$"

@ Unused
VerdanturfTown_ContestHall_Text_RaisedMonToBeCute:
	.string "Crié a mi POKéMON para ser lindo.\p"
	.string "¡Vi que puedes inscribir POKéMON en\n"
	.string "un CONTEST de ternura!\p"
	.string "Me alegra haber criado a mi POKéMON\n"
	.string "con tanto cariño…$"

@ Unused
VerdanturfTown_ContestHall_Text_MyMonRules:
	.string "¡Mi POKéMON es el mejor!\p"
	.string "Es genial, fuerte, lindo, bello\n"
	.string "y listo. ¡Es perfecto!\p"
	.string "Podría ganar en cada uno de los\n"
	.string "CONTEST.$"

@ Unused
VerdanturfTown_ContestHall_Text_NormalRankStage:
	.string "POKéMON CONTESTS\n"
	.string "¡RANGO NORMAL!$"

