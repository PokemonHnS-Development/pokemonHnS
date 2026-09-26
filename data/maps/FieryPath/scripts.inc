FieryPath_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FieryPath_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

FieryPath_OnTransition:
	call_if_unset FLAG_LANDMARK_FIERY_PATH, FieryPath_EventScript_MoveScottToFallarbor
	setflag FLAG_LANDMARK_FIERY_PATH
	callnative SetTimeBasedEncounters
	end

FieryPath_EventScript_MoveScottToFallarbor::
	setflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	return

