CaveOfOrigin_UnusedRubySapphireMap2_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CaveOfOrigin_UnusedRubySapphireMap2_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, CaveOfOrigin_UnusedRubySapphireMap2_OnTransition
	.byte 0

CaveOfOrigin_UnusedRubySapphireMap2_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, CaveOfOrigin_UnusedRubySapphireMap2_EventScript_TryRemoveRegigigas
	end

CaveOfOrigin_UnusedRubySapphireMap2_EventScript_TryRemoveRegigigas::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

CaveOfOrigin_UnusedRubySapphireMap2_OnTransition:
	call_if_unset FLAG_DEFEATED_REGIGIGAS, CaveOfOrigin_UnusedRubySapphireMap2_EventScript_ShowRegigigas
	end

CaveOfOrigin_UnusedRubySapphireMap2_EventScript_ShowRegigigas::
	clearflag FLAG_HIDE_REGIGIGAS
	return

CaveOfOrigin_UnusedRubySapphireMap2_EventScript_Regigigas::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIGIGAS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIGIGAS, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	call_if_set FLAG_DIFFICULTY_HARD, CaveOfOrigin_UnusedRubySapphireMap2_EventScript_Regigigas_Stats
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, CaveOfOrigin_UnusedRubySapphireMap2_EventScript_DefeatedRegigigas
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, CaveOfOrigin_UnusedRubySapphireMap2_EventScript_RanFromRegigigas
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, CaveOfOrigin_UnusedRubySapphireMap2_EventScript_RanFromRegigigas
	setflag FLAG_DEFEATED_REGIGIGAS
	release
	end

CaveOfOrigin_UnusedRubySapphireMap2_EventScript_Regigigas_Stats::
	setvar VAR_0x8000, 600 @HP
	setvar VAR_0x8001, 464 @ATK
	special SetHpStat
	special SetAtkStat
	return

CaveOfOrigin_UnusedRubySapphireMap2_EventScript_DefeatedRegigigas::
	setflag FLAG_DEFEATED_REGIGIGAS
	goto Common_EventScript_RemoveStaticPokemon
	end

CaveOfOrigin_UnusedRubySapphireMap2_EventScript_RanFromRegigigas::
	setvar VAR_0x8004, SPECIES_REGIGIGAS
	goto Common_EventScript_LegendaryFlewAway
	end
