.set LOCALID_ZAPDOS, 14

ScorchedSlab_Zapdos_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, ScorchedSlab_Zapdos_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, ScorchedSlab_Zapdos_OnTransition
	.byte 0

ScorchedSlab_Zapdos_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, ScorchedSlab_Zapdos_EventScript_TryRemoveZapdos
	end

ScorchedSlab_Zapdos_EventScript_TryRemoveZapdos::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

ScorchedSlab_Zapdos_OnTransition:
	call_if_unset FLAG_UNLOCK_BIRDS, ScorchedSlab_Zapdos_EventScript_HideZapdos
	call_if_unset FLAG_DEFEATED_ZAPDOS, ScorchedSlab_Zapdos_EventScript_ShowZapdos
	end

ScorchedSlab_Zapdos_EventScript_ShowZapdos::
	clearflag FLAG_HIDE_ZAPDOS
	end

ScorchedSlab_Zapdos_EventScript_HideZapdos::
	setflag FLAG_HIDE_ZAPDOS
	removeobject LOCALID_ZAPDOS
	end

ScorchedSlab_Zapdos_EventScript_Zapdos::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZAPDOS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_ZAPDOS, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	call_if_set FLAG_DIFFICULTY_HARD, ScorchedSlab_Zapdos_EventScript_Zapdos_Stats
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ScorchedSlab_Zapdos_EventScript_DefeatedZapdos
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ScorchedSlab_Zapdos_EventScript_RanFromZapdos
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ScorchedSlab_Zapdos_EventScript_RanFromZapdos
	setflag FLAG_DEFEATED_ZAPDOS
	release
	end

ScorchedSlab_Zapdos_EventScript_Zapdos_Stats::
	setvar VAR_0x8000, 450 @HP
	setvar VAR_0x8003, 500 @SPD
	special SetHpStat
	special SetSpdStat
	return

ScorchedSlab_Zapdos_EventScript_DefeatedZapdos::
	setflag FLAG_DEFEATED_ZAPDOS
	goto Common_EventScript_RemoveStaticPokemon
	end

ScorchedSlab_Zapdos_EventScript_RanFromZapdos::
	setvar VAR_0x8004, SPECIES_ZAPDOS
	goto Common_EventScript_LegendaryFlewAway
	end
