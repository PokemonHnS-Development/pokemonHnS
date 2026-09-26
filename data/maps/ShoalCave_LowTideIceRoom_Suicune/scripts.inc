
.set LOCALID_SUICUNE_1, 7
.set LOCALID_SUICUNE_2, 8

ShoalCave_LowTideIceRoom_Suicune_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ShoalCave_LowTideIceRoom_Suicune_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

ShoalCave_LowTideIceRoom_Suicune_OnTransition::
	callnative SetTimeBasedEncounters
	end

@@Trigger at the start

ShoalCave_LowTideIceRoom_Suicune_EntranceTrigger::
	lock
	playmoncry SPECIES_SUICUNE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_SUICUNE_EVENT, 1
	applymovement OBJ_EVENT_ID_PLAYER, ShoalCave_LowTideIceRoom_Suicune_EntranceTriggerMovement
	waitmovement 0
	msgbox ShoalCave_LowTideIceRoom_Suicune_EntranceTrigger_Text, MSGBOX_DEFAULT
	waitmessage
	release
	end

ShoalCave_LowTideIceRoom_Suicune_EntranceTrigger_Text:
	.string "Un rugido gélido resuena en la\n"
	.string "CUEVA DE LOS ARRECIFES.\p"
	.string "Hay algo o alguien aquí.$"

ShoalCave_LowTideIceRoom_Suicune_EntranceTriggerMovement:
	face_right
	delay_16
	emote_question_mark
	step_end

@@First encounter with Suicune. Level 90, high defenses

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle1::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_SUICUNE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_SUICUNE, 90
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_RG_VS_LEGEND
	call_if_set FLAG_DIFFICULTY_HARD, ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle1_Stats
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle1_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ShoalCave_LowTideIceRoom_Suicune_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ShoalCave_LowTideIceRoom_Suicune_Ran
	releaseall
	end

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle1_Stats::
	setvar VAR_0x8002, 450 @DEF
	setvar VAR_0x8006, 450 @SP. DEF
	special SetDefStat
	special SetSpDefStat
	return

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle1_Won::
	applymovement LOCALID_SUICUNE_1, ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle1_Movement
	waitmovement 0
	msgbox ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle1_Text, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SUICUNE_BATTLE_1
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle1_Movement:
	face_down
	delay_16
	walk_fast_down
	walk_fast_down
	jump_2_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	step_end

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle1_Text:
	.string "¡El POKéMON huyó rápidamente!$"

@@Second encounter with Suicune. Level 80. High defenses

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle2::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_SUICUNE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_SUICUNE, 80
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_C_VS_LEGEND_BEAST
	call_if_set FLAG_DIFFICULTY_HARD, ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle2_Stats
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle2_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ShoalCave_LowTideIceRoom_Suicune_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ShoalCave_LowTideIceRoom_Suicune_Ran
	releaseall
	end

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle2_Stats::
	setvar VAR_0x8002, 550 @DEF
	setvar VAR_0x8006, 550 @SP. DEF
	special SetDefStat
	special SetSpDefStat
	return

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle2_Won::
	applymovement LOCALID_SUICUNE_2, ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle2_Movement
	waitmovement 0
	msgbox ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle2_Text, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SUICUNE_BATTLE_2
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle2_Movement:
	face_up
	delay_16
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle2_Text:
	.string "¡Huyó rápidamente otra vez!$"

@@Final battle with Suicune, now you can catch it. Level 70, holds Mystic water, and has high defenses

ShoalCave_LowTideIceRoom_Suicune_SuicuneFinalBattle::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_SUICUNE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox ShoalCave_LowTideIceRoom_Suicune_SuicuneFinalBattle_Text, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_SUICUNE, 70, ITEM_MYSTIC_WATER
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	call_if_set FLAG_DIFFICULTY_HARD, ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle3_Stats
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ShoalCave_LowTideIceRoom_Suicune_SuicuneFinalBattle_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, ShoalCave_LowTideIceRoom_Suicune_SuicuneFinalBattle_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, ShoalCave_LowTideIceRoom_Suicune_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, ShoalCave_LowTideIceRoom_Suicune_Ran
	releaseall
	end

ShoalCave_LowTideIceRoom_Suicune_SuicuneBattle3_Stats::
	setvar VAR_0x8002, 700 @DEF
	setvar VAR_0x8006, 700 @SP. DEF
	special SetDefStat
	special SetSpDefStat
	return

ShoalCave_LowTideIceRoom_Suicune_SuicuneFinalBattle_Text:
	.string "SUICUNE ya no tiene ningún\n"
	.string "otro lugar donde esconderse.\p"
	.string "¿Podré capturarlo ahora?$"

ShoalCave_LowTideIceRoom_Suicune_SuicuneFinalBattle_Won::
	setflag FLAG_DEFEATED_SUICUNE
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

ShoalCave_LowTideIceRoom_Suicune_Ran::
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	releaseall
	end
