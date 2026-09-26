CeruleanCave3_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CeruleanCave3_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCave3_OnTransition
	.byte 0

CeruleanCave3_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, CeruleanCave3_EventScript_TryRemoveMewtwo
	end

CeruleanCave3_EventScript_TryRemoveMewtwo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

CeruleanCave3_OnTransition:
	call_if_unset FLAG_UNLOCK_MEWTWO, CeruleanCave3_EventScript_HideMewtwo
	call_if_unset FLAG_DEFEATED_MEWTWO, CeruleanCave3_EventScript_ShowMewtwo
	end

CeruleanCave3_EventScript_ShowMewtwo::
	clearflag FLAG_HIDE_MEWTWO
	end

CeruleanCave3_EventScript_HideMewtwo::
	setflag FLAG_HIDE_MEWTWO
	removeobject LOCALID_MEWTWO
	end

CeruleanCave3_EventScript_Mewtwo::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEWTWO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_MEWTWO, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	call_if_set FLAG_DIFFICULTY_HARD, CeruleanCave3_EventScript_Mewtwo_Hard_Stats
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, CeruleanCave3_EventScript_DefeatedMewtwo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, CeruleanCave3_EventScript_RanFromMewtwo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, CeruleanCave3_EventScript_RanFromMewtwo
	setflag FLAG_DEFEATED_MEWTWO
	release
	end

CeruleanCave3_EventScript_Mewtwo_Hard_Stats::
	setvar VAR_0x8000, 500 @HP
	setvar VAR_0x8003, 500 @SPD
	special SetHpStat
	special SetSpdStat
	return

CeruleanCave3_EventScript_DefeatedMewtwo::
	setflag FLAG_DEFEATED_MEWTWO
	goto Common_EventScript_RemoveStaticPokemon
	end

CeruleanCave3_EventScript_RanFromMewtwo::
	setvar VAR_0x8004, SPECIES_MEWTWO
	goto Common_EventScript_LegendaryFlewAway
	end
