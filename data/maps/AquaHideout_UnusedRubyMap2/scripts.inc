AquaHideout_UnusedRubyMap2_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, AquaHideout_UnusedRubyMap2_OnResume
	map_script MAP_SCRIPT_ON_LOAD, AquaHideout_UnusedRubyMap2_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, AquaHideout_UnusedRubyMap2_OnTransition
	.byte 0

AquaHideout_UnusedRubyMap2_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, AquaHideout_UnusedRubyMap2_EventScript_TryRemoveRegieleki
	end

AquaHideout_UnusedRubyMap2_EventScript_TryRemoveRegieleki::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

AquaHideout_UnusedRubyMap2_OnLoad:
	call_if_unset FLAG_SYS_BRAILLE_REGIELEKI_COMPLETED, AquaHideout_UnusedRubyMap2_EventScript_HideRegiEntrance
	end

AquaHideout_UnusedRubyMap2_EventScript_HideRegiEntrance::
	setmetatile 7, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 8, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 9, 19, METATILE_Cave_EntranceCover, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 9, 20, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	return

AquaHideout_UnusedRubyMap2_OnTransition:
	setflag FLAG_LANDMARK_CAVE_OF_SHOCK
	call_if_unset FLAG_DEFEATED_REGIELEKI, AquaHideout_UnusedRubyMap2_EventScript_ShowRegieleki
	end

AquaHideout_UnusedRubyMap2_EventScript_ShowRegieleki::
	clearflag FLAG_HIDE_REGIELEKI
	return

AquaHideout_UnusedRubyMap2_EventScript_OpenRegiEntrance::
	msgbox AquaHideout_UnusedRubyMap2_EventScript_CloseBrailleMsgText2, MSGBOX_AUTOCLOSE
	setmetatile 7, 19, METATILE_Cave_SealedChamberEntrance_TopLeft, TRUE
	setmetatile 8, 19, METATILE_Cave_SealedChamberEntrance_TopMid, TRUE
	setmetatile 9, 19, METATILE_Cave_SealedChamberEntrance_TopRight, TRUE
	setmetatile 7, 20, METATILE_Cave_SealedChamberEntrance_BottomLeft, TRUE
	setmetatile 8, 20, METATILE_Cave_SealedChamberEntrance_BottomMid, FALSE
	setmetatile 9, 20, METATILE_Cave_SealedChamberEntrance_BottomRight, TRUE
	special DrawWholeMapView
	playse SE_BANG
	removeitem ITEM_SAPPHIRE
	setflag FLAG_SYS_BRAILLE_REGIELEKI_COMPLETED
	end

AquaHideout_UnusedRubyMap2_EventScript_CaveEntranceMiddle::
	lockall
	goto_if_set FLAG_SYS_BRAILLE_REGIELEKI_COMPLETED, AquaHideout_UnusedRubyMap2_EventScript_BigHoleInWall
	braillemessage Regieleki_Braille_Sapphire
	goto_if_unset FLAG_SYS_BRAILLE_REGIELEKI_COMPLETED, AquaHideout_UnusedRubyMap2_EventScript_CloseBrailleMsg
	waitbuttonpress
	closebraillemessage
	releaseall
	end

AquaHideout_UnusedRubyMap2_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

AquaHideout_UnusedRubyMap2_EventScript_CaveEntranceSide::
	lockall
	goto_if_set FLAG_SYS_BRAILLE_REGIELEKI_COMPLETED, AquaHideout_UnusedRubyMap2_EventScript_BigHoleInWall
	braillemessage Regieleki_Braille_Sapphire
	waitbuttonpress
	closebraillemessage
	releaseall
	end

AquaHideout_UnusedRubyMap2_EventScript_CloseBrailleMsg::
	waitbuttonpress
	closebraillemessage
	releaseall
	msgbox AquaHideout_UnusedRubyMap2_EventScript_CloseBrailleMsgText, MSGBOX_DEFAULT
	waitbuttonpress
	chooseitem KEYITEMS_POCKET
	goto_if_eq VAR_ITEM_ID, ITEM_SAPPHIRE, AquaHideout_UnusedRubyMap2_EventScript_OpenRegiEntrance
	msgbox AquaHideout_UnusedRubyMap2_EventScript_CloseBrailleMsgText3, MSGBOX_AUTOCLOSE
	end

AquaHideout_UnusedRubyMap2_EventScript_CloseBrailleMsgText::
	.string "Hay un hueco.\p"
	.string "Tal vez pueda poner algo\n"
	.string "dentro.$"

AquaHideout_UnusedRubyMap2_EventScript_CloseBrailleMsgText2::
	.string "¡El ZAFIRO encaja perfecto\n"
	.string "en el hueco!$"

AquaHideout_UnusedRubyMap2_EventScript_CloseBrailleMsgText3::
	.string "Hmmm...\p"
	.string "No, eso no es.$"

AquaHideout_UnusedRubyMap2_EventScript_Regieleki::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIELEKI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_REGIELEKI, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	call_if_set FLAG_DIFFICULTY_HARD, AquaHideout_UnusedRubyMap2_EventScript_Regieleki_Stats
	special StartRegiBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	calculatemonstats
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, AquaHideout_UnusedRubyMap2_EventScript_DefeatedRegieleki
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, AquaHideout_UnusedRubyMap2_EventScript_RanFromRegieleki
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, AquaHideout_UnusedRubyMap2_EventScript_RanFromRegieleki
	setflag FLAG_DEFEATED_REGIELEKI
	release
	end

AquaHideout_UnusedRubyMap2_EventScript_Regieleki_Stats::
	setvar VAR_0x8000, 500 @HP
	setvar VAR_0x8003, 999 @SPD
	special SetHpStat
	special SetSpdStat
	return

AquaHideout_UnusedRubyMap2_EventScript_DefeatedRegieleki::
	setflag FLAG_DEFEATED_REGIELEKI
	goto Common_EventScript_RemoveStaticPokemon
	end

AquaHideout_UnusedRubyMap2_EventScript_RanFromRegieleki::
	setvar VAR_0x8004, SPECIES_REGIELEKI
	goto Common_EventScript_LegendaryFlewAway
	end
