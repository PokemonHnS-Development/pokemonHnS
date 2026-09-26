.set LOCALID_RAIKOU_1, 3
.set LOCALID_RAIKOU_2, 2

NewMauville_Inside_Raikou_MapScripts::
	.byte 0

@@Trigger at the start

NewMauville_Inside_Raikou_EntranceTrigger::
	lock
	playmoncry SPECIES_RAIKOU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_RAIKOU_EVENT, 1
	applymovement OBJ_EVENT_ID_PLAYER, NewMauville_Inside_Raikou_EntranceTrigger_Movement
	waitmovement 0
	msgbox NewMauville_Inside_Raikou_EntranceTrigger_Text, MSGBOX_DEFAULT
	waitmessage
	release
	end

NewMauville_Inside_Raikou_EntranceTrigger_Text:
	.string "Un gran rugido resuena en\n"
	.string "VILLA TENIA.\p"
	.string "¿Hay algo oculto en\n"
	.string "este lugar?$"

NewMauville_Inside_Raikou_EntranceTrigger_Movement:
	delay_16
	emote_question_mark
	step_end

@@First encounter with Raikou. Level 70, 400 speed, 250hp

NewMauville_Inside_Raikou_RaikouBattle_1::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_RAIKOU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RAIKOU, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_RG_VS_LEGEND
	call_if_set FLAG_DIFFICULTY_HARD, NewMauville_Inside_Raikou_RaikouBattle_1_Stats
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_Raikou_RaikouBattle_1_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewMauville_Inside_Raikou_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewMauville_Inside_Raikou_Ran
	releaseall
	end

NewMauville_Inside_Raikou_RaikouBattle_1_Stats::
	setvar VAR_0x8000, 250 @hp
	setvar VAR_0x8003, 400 @Speed
	special SetHpStat
	special SetSpdStat
	return

NewMauville_Inside_Raikou_RaikouBattle_1_Won::
	applymovement LOCALID_RAIKOU_1, NewMauville_Inside_Raikou_RaikouBattle_1_Movement
	waitmovement 0
	msgbox NewMauville_Inside_Raikou_RaikouBattle_1_Text, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RAIKOU_BATTLE_1
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_Raikou_RaikouBattle_1_Movement:
	face_down
	delay_16
	walk_fast_down
	step_end

NewMauville_Inside_Raikou_RaikouBattle_1_Text:
	.string "¡Huyó más rápido que la luz!$"

@@Second encounter with Raikou. Level 70, 400 speed, 300hp

NewMauville_Inside_Raikou_RaikouBattle_2::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_RAIKOU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RAIKOU, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_C_VS_LEGEND_BEAST
	call_if_set FLAG_DIFFICULTY_HARD, NewMauville_Inside_Raikou_RaikouBattle_2_Stats
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_Raikou_RaikouBattle_2_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewMauville_Inside_Raikou_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewMauville_Inside_Raikou_Ran
	releaseall
	end

NewMauville_Inside_Raikou_RaikouBattle_2_Stats::
	setvar VAR_0x8000, 400 @hp
	setvar VAR_0x8003, 400 @Speed
	special SetHpStat
	special SetSpdStat
	return

NewMauville_Inside_Raikou_RaikouBattle_2_Won::
	applymovement LOCALID_RAIKOU_2, NewMauville_Inside_Raikou_RaikouBattle_2_Movement
	waitmovement 0
	msgbox NewMauville_Inside_Raikou_RaikouBattle_2_Text, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RAIKOU_BATTLE_2
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_Raikou_RaikouBattle_2_Movement:
	face_right
	delay_16
	step_end

NewMauville_Inside_Raikou_RaikouBattle_2_Text:
	.string "¡Huyó aún más rápido que antes!$"

@@ Final battle with Raikou, has 600hp and 400 speed, with magnet
NewMauville_Inside_Raikou_RaikouBattle::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_RAIKOU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox NewMauville_Inside_Raikou_RaikouBattle_Text, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_RAIKOU, 70, ITEM_MAGNET
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	call_if_set FLAG_DIFFICULTY_HARD, NewMauville_Inside_Raikou_RaikouBattle_3_Stats
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewMauville_Inside_Raikou_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, NewMauville_Inside_Raikou_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewMauville_Inside_Raikou_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewMauville_Inside_Raikou_Ran
	release
	end

NewMauville_Inside_Raikou_RaikouBattle_3_Stats::
	setvar VAR_0x8000, 600 @hp
	setvar VAR_0x8003, 400 @Speed
	special SetHpStat
	special SetSpdStat
	return

NewMauville_Inside_Raikou_RaikouBattle_Text::
	.string "RAIKOU dejó de huir.\n"
	.string "¿Se podrá capturar ahora?$"

NewMauville_Inside_Raikou_Won::
	setflag FLAG_DEFEATED_RAIKOU
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

NewMauville_Inside_Raikou_Ran::
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	releaseall
	end

