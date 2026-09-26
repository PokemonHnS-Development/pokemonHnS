.set LOCALID_MOLTRES, 1

VictoryRoad_Moltres2_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_RESUME, VictoryRoad_Moltres2_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_Moltres2_OnTransition
	.byte 0

VictoryRoad_Moltres2_OnResume:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_VICTORY_ROAD_MOLTRES
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, VictoryRoad_Moltres2_EventScript_TryRemoveMoltres
	end

VictoryRoad_Moltres2_EventScript_TryRemoveMoltres::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

VictoryRoad_Moltres2_OnTransition:
	call CaveHole_FixCrackedGround
	call_if_unset FLAG_UNLOCK_BIRDS, VictoryRoad_Moltres2_EventScript_HideMoltres
	call_if_unset FLAG_DEFEATED_MOLTRES, VictoryRoad_Moltres2_EventScript_ShowMoltres
	end

VictoryRoad_Moltres2_EventScript_ShowMoltres::
	clearflag FLAG_HIDE_MOLTRES
	end

VictoryRoad_Moltres2_EventScript_HideMoltres::
	setflag FLAG_HIDE_MOLTRES
	removeobject LOCALID_MOLTRES
	end

VictoryRoad_Moltres2_EventScript_Moltres::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MOLTRES, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_MOLTRES, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	call_if_set FLAG_DIFFICULTY_HARD, VictoryRoad_Moltres2_EventScript_Moltres_Stats
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VictoryRoad_Moltres2_EventScript_DefeatedMoltres
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, VictoryRoad_Moltres2_EventScript_RanFromMoltres
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, VictoryRoad_Moltres2_EventScript_RanFromMoltres
	setflag FLAG_DEFEATED_MOLTRES
	release
	end

VictoryRoad_Moltres2_EventScript_Moltres_Stats::
	setvar VAR_0x8000, 450 @HP
	setvar VAR_0x8005, 350 @SP. ATK
	special SetHpStat
	special SetSpAtkStat
	return

VictoryRoad_Moltres2_EventScript_DefeatedMoltres::
	setflag FLAG_DEFEATED_MOLTRES
	goto Common_EventScript_RemoveStaticPokemon
	end

VictoryRoad_Moltres2_EventScript_RanFromMoltres::
	setvar VAR_0x8004, SPECIES_MOLTRES
	goto Common_EventScript_LegendaryFlewAway
	end
