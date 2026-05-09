.set LOCALID_ENTEI_1, 4
.set LOCALID_ENTEI_2, 3
.set LOCALID_ENTEI_3, 2

MagmaHideout_3F_1R_Entei_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_3F_1R_Entei_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

MagmaHideout_3F_1R_Entei_OnTransition::
	callnative SetTimeBasedEncounters
	end

MagmaHideout_3F_1R_DroughtTrigger::
	setweather WEATHER_DROUGHT
	doweather
	setvar VAR_TEMP_0, 1
	end

MagmaHideout_3F_1R_NormalWeatherTrigger::
	setweather WEATHER_SUNNY
	doweather
	setvar VAR_TEMP_0, 0
	end

@@Trigger at the start

MagmaHideout_3F_1R_EntranceTrigger::
	lock
	playmoncry SPECIES_ENTEI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_ENTEI_EVENT, 1
	applymovement OBJ_EVENT_ID_PLAYER, MagmaHideout_3F_1R_EntranceTriggerMovement
	waitmovement 0
	msgbox MagmaHideout_3F_1R_EntranceTrigger_Text, MSGBOX_DEFAULT
	waitmessage
	release
	end

MagmaHideout_3F_1R_EntranceTrigger_Text:
	.string "A big roar echoes around MAGMA\n"
	.string "HIDEOUT.\p"
	.string "It seems that the echoing roars\n"
	.string "come from a menacing POKéMON.\p"
	.string "However… It looks distressed.\n"
	.string "Is it scared?\p"
	.string "Catching it may be impossible without\n"
	.string "weakening it.$"

MagmaHideout_3F_1R_EntranceTriggerMovement:
	face_right
	delay_16
	emote_question_mark
	step_end

@@First encounter with Entei. Level 40, has 300HP.

MagmaHideout_3F_1R_Entei_EnteiBattle1::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_ENTEI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_ENTEI, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_RG_VS_WILD
	call_if_set FLAG_DIFFICULTY_HARD, MagmaHideout_3F_1R_Entei_EnteiBattle1_Stats
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MagmaHideout_3F_1R_EnteiBattle1_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MagmaHideout_3F_1R_Entei_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MagmaHideout_3F_1R_Entei_Ran
	releaseall
	end

MagmaHideout_3F_1R_Entei_EnteiBattle1_Stats::
	setvar VAR_0x8000, 300 @HP
	special SetHpStat
	return

MagmaHideout_3F_1R_EnteiBattle1_Won::
	applymovement LOCALID_ENTEI_1, MagmaHideout_3F_1R_EnteiBattle1_Movement
	waitmovement 0
	msgbox MagmaHideout_3F_1R_EnteiBattle1_Text, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_ENTEI_BATTLE_1
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

MagmaHideout_3F_1R_EnteiBattle1_Movement:
	face_right
	delay_16
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

MagmaHideout_3F_1R_EnteiBattle1_Text:
	.string "The POKéMON ran away!$"

@@Second encounter with Entei. Has 750HP and is now level 50. Atk and Sp.Atk are getting stronger.

MagmaHideout_3F_1R_Entei_EnteiBattle2::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_ENTEI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_ENTEI, 50
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_RG_VS_LEGEND
	call_if_set FLAG_DIFFICULTY_HARD, MagmaHideout_3F_1R_Entei_EnteiBattle2_Stats
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MagmaHideout_3F_1R_EnteiBattle2_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MagmaHideout_3F_1R_EnteiBattle2_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MagmaHideout_3F_1R_Entei_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MagmaHideout_3F_1R_Entei_Ran
	releaseall
	end

MagmaHideout_3F_1R_Entei_EnteiBattle2_Stats::
	setvar VAR_0x8000, 750 @HP
	setvar VAR_0x8001, 200 @Atk
	setvar VAR_0x8005, 200 @Sp. Atk
	special SetHpStat
	special SetAtkStat
	special SetSpAtkStat
	return

MagmaHideout_3F_1R_EnteiBattle2_Won::
	applymovement LOCALID_ENTEI_2, MagmaHideout_3F_1R_EnteiBattle2_Movement
	waitmovement 0
	msgbox MagmaHideout_3F_1R_EnteiBattle2_Text, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_ENTEI_BATTLE_2
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

MagmaHideout_3F_1R_EnteiBattle2_Movement:
	face_right
	delay_16
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MagmaHideout_3F_1R_EnteiBattle2_Text:
	.string "The POKéMON ran away, but not\n"
	.string "as fast as before.$"

@@Third and last encounter with Entei before catching it. Has 800HP and is now level 60, and it's sunny. More atk and sp.atk.

MagmaHideout_3F_1R_Entei_EnteiBattle3::
	lockall
	faceplayer
	waitse
	playmoncry SPECIES_ENTEI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_ENTEI, 60
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_SET_BATTLE_BGM
	setvar VAR_TEMP_F, MUS_C_VS_LEGEND_BEAST
	call_if_set FLAG_DIFFICULTY_HARD, MagmaHideout_3F_1R_Entei_EnteiBattle3_Stats
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MagmaHideout_3F_1R_EnteiBattle3_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MagmaHideout_3F_1R_EnteiBattle3_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MagmaHideout_3F_1R_Entei_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MagmaHideout_3F_1R_Entei_Ran
	releaseall
	end

MagmaHideout_3F_1R_Entei_EnteiBattle3_Stats::
	setvar VAR_0x8000, 750 @HP
	setvar VAR_0x8001, 250 @Atk
	setvar VAR_0x8005, 200 @Sp. Atk
	special SetHpStat
	special SetAtkStat
	special SetSpAtkStat
	return

MagmaHideout_3F_1R_EnteiBattle3_Won::
	applymovement LOCALID_ENTEI_3, MagmaHideout_3F_1R_EnteiBattle3_Movement
	waitmovement 0
	msgbox MagmaHideout_3F_1R_EnteiBattle3_Text, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_ENTEI_BATTLE_3
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

MagmaHideout_3F_1R_EnteiBattle3_Movement:
	face_right
	delay_16
	walk_right
	walk_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

MagmaHideout_3F_1R_EnteiBattle3_Text:
	.string "The POKéMON ran away. However it's\n"
	.string "way slower than before.\l"
	.string "Is it getting tired?$"

@@Final battle with Entei, now you can catch it. Has 900HP, holds charcoal and it's sunny. Way stronger as well.

MagmaHideout_3F_1R_Entei_EnteiFinalBattle::
	lockall
	faceplayer
	delay 20
	playse SE_THUNDERSTORM_STOP
	setvar VAR_0x8004, 0  @ vertical pan
	setvar VAR_0x8005, 3  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 2  @ shake delay
	special ShakeCamera
	delay 30
	playse SE_THUNDERSTORM_STOP
	setvar VAR_0x8004, 0  @ vertical pan
	setvar VAR_0x8005, 3  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 2  @ shake delay
	special ShakeCamera
	delay 30
	delay 50
	waitse
	playmoncry SPECIES_ENTEI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox MagmaHideout_3F_1R_EnteiBattleFinal_Text, MSGBOX_DEFAULT
	closemessage
	setwildbattle SPECIES_ENTEI, 70, ITEM_CHARCOAL
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	call_if_set FLAG_DIFFICULTY_HARD, MagmaHideout_3F_1R_Entei_EnteiBattle4_Stats
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, MagmaHideout_3F_1R_EnteiFinalBattle_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MagmaHideout_3F_1R_EnteiFinalBattle_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, MagmaHideout_3F_1R_Entei_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, MagmaHideout_3F_1R_Entei_Ran
	releaseall
	end

MagmaHideout_3F_1R_Entei_EnteiBattle4_Stats::
	setvar VAR_0x8000, 900 @HP
	setvar VAR_0x8001, 300 @Atk
	setvar VAR_0x8005, 200 @Sp. Atk
	special SetHpStat
	special SetAtkStat
	special SetSpAtkStat
	return

MagmaHideout_3F_1R_EnteiBattleFinal_Text:
	.string "ENTEI looks exhausted.\n"
	.string "Can it be captured now?$"

MagmaHideout_3F_1R_EnteiFinalBattle_Won::
	setflag FLAG_DEFEATED_ENTEI
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	callnative UpdateFollowingPokemon
	goto Common_EventScript_RemoveStaticPokemon
	end

MagmaHideout_3F_1R_Entei_Ran::
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_SYS_NO_CATCHING
	releaseall
	end
