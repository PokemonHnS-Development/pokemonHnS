.set LOCALID_ARTICUNO, 1

MeteorFalls_Articuno_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MeteorFalls_Articuno_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MeteorFalls_Articuno_OnTransition
	.byte 0

MeteorFalls_Articuno_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, MeteorFalls_Articuno_EventScript_TryRemoveArticuno
	end

MeteorFalls_Articuno_EventScript_TryRemoveArticuno::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

MeteorFalls_Articuno_OnTransition:
	call_if_unset FLAG_UNLOCK_BIRDS, MeteorFalls_Articuno_EventScript_HideArticuno
	call_if_unset FLAG_DEFEATED_ARTICUNO, MeteorFalls_Articuno_EventScript_ShowArticuno
	end

MeteorFalls_Articuno_EventScript_ShowArticuno::
	clearflag FLAG_HIDE_ARTICUNO
	end

MeteorFalls_Articuno_EventScript_HideArticuno::
	setflag FLAG_HIDE_ARTICUNO
	removeobject LOCALID_ARTICUNO
	end

MeteorFalls_Articuno_EventScript_Articuno::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ARTICUNO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_ARTICUNO, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	call_if_set FLAG_DIFFICULTY_HARD, MeteorFalls_Articuno_EventScript_Articuno_Stats
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MeteorFalls_Articuno_EventScript_DefeatedArticuno
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MeteorFalls_Articuno_EventScript_RanFromArticuno
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MeteorFalls_Articuno_EventScript_RanFromArticuno
	setflag FLAG_DEFEATED_ARTICUNO
	release
	end

MeteorFalls_Articuno_EventScript_Articuno_Stats::
	setvar VAR_0x8000, 450 @HP
	setvar VAR_0x8006, 400 @SP. DEF
	special SetHpStat
	special SetSpDefStat
	return

MeteorFalls_Articuno_EventScript_DefeatedArticuno::
	setflag FLAG_DEFEATED_ARTICUNO
	goto Common_EventScript_RemoveStaticPokemon
	end

MeteorFalls_Articuno_EventScript_RanFromArticuno::
	setvar VAR_0x8004, SPECIES_ARTICUNO
	goto Common_EventScript_LegendaryFlewAway
	end
