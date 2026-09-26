AquaHideout_UnusedRubyMap1_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, AquaHideout_UnusedRubyMap1_OnResume
	map_script MAP_SCRIPT_ON_LOAD, AquaHideout_UnusedRubyMap1_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, AquaHideout_UnusedRubyMap1_OnTransition
	.byte 0

AquaHideout_UnusedRubyMap1_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, AquaHideout_UnusedRubyMap1_EventScript_TryRemoveRegidrago
	end

AquaHideout_UnusedRubyMap1_EventScript_TryRemoveRegidrago::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

AquaHideout_UnusedRubyMap1_OnLoad:
	call_if_unset FLAG_SYS_BRAILLE_REGIDRAGO_COMPLETED, AquaHideout_UnusedRubyMap1_EventScript_HideRegiEntrance
	end

AquaHideout_UnusedRubyMap1_EventScript_HideRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 8, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 9, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	return

AquaHideout_UnusedRubyMap1_OnTransition:
	setflag FLAG_LANDMARK_DRACO_CHAMBER
	call_if_unset FLAG_DEFEATED_REGIDRAGO, AquaHideout_UnusedRubyMap1_EventScript_ShowRegidrago
	end

AquaHideout_UnusedRubyMap1_EventScript_ShowRegidrago::
	clearflag FLAG_HIDE_REGIDRAGO
	return

AquaHideout_UnusedRubyMap1_EventScript_OpenRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_SealedChamberEntrance_TopLeft, TRUE
	setmetatile 8, 19, METATILE_Cave_SealedChamberEntrance_TopMid, TRUE
	setmetatile 9, 19, METATILE_Cave_SealedChamberEntrance_TopRight, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberEntrance_BottomLeft, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberEntrance_BottomMid, FALSE
	setmetatile 9, 20, METATILE_Cave_SealedChamberEntrance_BottomRight, TRUE
	special DrawWholeMapView
	playse SE_BANG
	setflag FLAG_SYS_BRAILLE_REGIDRAGO_COMPLETED
	end

AquaHideout_UnusedRubyMap1_EventScript_CaveEntranceMiddle::
	lockall
	goto_if_set FLAG_SYS_BRAILLE_REGIDRAGO_COMPLETED, AquaHideout_UnusedRubyMap1_EventScript_BigHoleInWall
	braillemessage Regidrago_Braille_Text
	goto_if_unset FLAG_SYS_BRAILLE_REGIDRAGO_COMPLETED, AquaHideout_UnusedRubyMap1_EventScript_CloseBrailleMsg
	waitbuttonpress
	closebraillemessage
	releaseall
	end

AquaHideout_UnusedRubyMap1_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

AquaHideout_UnusedRubyMap1_EventScript_CaveEntranceSide::
	lockall
	goto_if_set FLAG_SYS_BRAILLE_REGIDRAGO_COMPLETED, AquaHideout_UnusedRubyMap1_EventScript_BigHoleInWall
	braillemessage Regidrago_Braille_Text
	waitbuttonpress
	closebraillemessage
	releaseall
	end

AquaHideout_UnusedRubyMap1_EventScript_CloseBrailleMsg::
	waitbuttonpress
	closebraillemessage
	releaseall
	end

AquaHideout_UnusedRubyMap1_EventScript_Regidrago::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIDRAGO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIDRAGO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	call_if_set FLAG_DIFFICULTY_HARD, AquaHideout_UnusedRubyMap1_EventScript_Regidrago_Stats
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, AquaHideout_UnusedRubyMap1_EventScript_DefeatedRegidrago
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, AquaHideout_UnusedRubyMap1_EventScript_RanFromRegidrago
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, AquaHideout_UnusedRubyMap1_EventScript_RanFromRegidrago
	setflag FLAG_DEFEATED_REGIDRAGO
	release
	end

AquaHideout_UnusedRubyMap1_EventScript_Regidrago_Stats::
	setvar VAR_0x8000, 999 @HP
	special SetHpStat
	return

AquaHideout_UnusedRubyMap1_EventScript_DefeatedRegidrago::
	setflag FLAG_DEFEATED_REGIDRAGO
	goto Common_EventScript_RemoveStaticPokemon
	end

AquaHideout_UnusedRubyMap1_EventScript_RanFromRegidrago::
	setvar VAR_0x8004, SPECIES_REGIDRAGO
	goto Common_EventScript_LegendaryFlewAway
	end

AquaHideout_UnusedRubyMap1_EventScript_DusknoirButton::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, AquaHideout_UnusedRubyMap1_Movement
	waitmovement 0
	goto_if_set FLAG_DEFEATED_DUSKNOIR, AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonFinished
	msgbox AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonText, MSGBOX_YESNO
	waitmessage
	switch VAR_RESULT
	case NO, AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonNo
	case YES, AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonYes
	case MULTI_B_PRESSED, AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonNo
	end

AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonFinished::
	msgbox AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonText3, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonYes::
	waitse
	playmoncry SPECIES_DUSKNOIR, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonText2, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_DUSKNOIR, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	goto AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonBattle
	
AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonBattle::
	faceplayer
	setwildbattle SPECIES_DUSKNOIR, 65
	setflag FLAG_SYS_NO_CATCHING
	setflag FLAG_SYS_NO_BAG_USE
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonBattle_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonBattle_Won
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonBattle_Ran
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonBattle_Ran
	releaseall
	end

AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonBattle_Won::
	setflag FLAG_DEFEATED_DUSKNOIR
	clearflag FLAG_SYS_NO_CATCHING
	clearflag FLAG_SYS_NO_BAG_USE
	callnative UpdateFollowingPokemon
	goto AquaHideout_UnusedRubyMap1_EventScript_OpenRegiEntrance
	end

AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonBattle_Ran::
	clearflag FLAG_SYS_NO_CATCHING
	clearflag FLAG_SYS_NO_BAG_USE
	callnative UpdateFollowingPokemon
	end

AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonNo::
	releaseall
	callnative UpdateFollowingPokemon
	end

AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonText:
	.string "Debe haber un botón\n"
	.string "por aquí…\p"
	.string "…\l"
	.string "…\p"
	.string "¡Oh!\n"
	.string "¡Aquí está!\p"
	.string "¿Debería presionarlo?$"

AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonText2:
	.string "Intentaste presionar\n"
	.string "el botón…\p"
	.string "¡Pero una mano fría empezó\n"
	.string "a tocarte!\p"
	.string "¡Su agarre es muy fuerte!$"

AquaHideout_UnusedRubyMap1_EventScript_DusknoirButtonText3::
	.string "El botón ha sido presionado.$"

AquaHideout_UnusedRubyMap1_Movement:
	step_end
