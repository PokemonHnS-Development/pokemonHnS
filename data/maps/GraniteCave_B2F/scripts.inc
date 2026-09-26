GraniteCave_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GraniteCave_B2F_OnLoad
	.byte 0

GraniteCave_B2F_OnLoad:
	call_if_unset FLAG_SYS_BRAILLE_REGIGIGAS_COMPLETED, GraniteCave_B2F_EventScript_HideRegiEntrance
	end

GraniteCave_B2F_EventScript_HideRegiEntrance::
	setmetatile 20, 9, METATILE_Cave_EntranceCover, TRUE
	setmetatile 21, 9, METATILE_Cave_EntranceCover, TRUE
	setmetatile 22, 9, METATILE_Cave_EntranceCover, TRUE
	setmetatile 20, 10, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 21, 10, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	setmetatile 22, 10, METATILE_Cave_SealedChamberBraille_Mid, TRUE
	return

GraniteCave_B2F_RegigigasStart::
	goto_if_set FLAG_SYS_BRAILLE_REGIGIGAS_COMPLETED, GraniteCave_B2F_EventScript_BigHoleInWall
	braillemessage Regigigas_Braille_Text
	waitbuttonpress
	closebraillemessage
	goto_if_set FLAG_SYS_GAME_CLEAR, GraniteCave_B2F_RegigigasCheck0
	end

GraniteCave_B2F_EventScript_BigHoleInWall::
	msgbox gText_BigHoleInTheWall, MSGBOX_DEFAULT
	releaseall
	end

GraniteCave_B2F_RegigigasCheck0::
	goto_if_set FLAG_DEFEATED_REGIELEKI, GraniteCave_B2F_RegigigasCheck1
	end 

GraniteCave_B2F_RegigigasCheck1::
	goto_if_set FLAG_DEFEATED_REGIDRAGO, GraniteCave_B2F_RegigigasCheck2
	end

GraniteCave_B2F_RegigigasCheck2::
	goto_if_set FLAG_DEFEATED_REGICE, GraniteCave_B2F_RegigigasCheck3
	end

GraniteCave_B2F_RegigigasCheck3::
	goto_if_set FLAG_DEFEATED_REGISTEEL, GraniteCave_B2F_RegigigasCheck4
	end

GraniteCave_B2F_RegigigasCheck4::
	goto_if_set FLAG_DEFEATED_REGIROCK, GraniteCave_B2F_RegigigasDoor
	end

GraniteCave_B2F_RegigigasDoor:
	delay 60
	setmetatile 20, 9, METATILE_Cave_SealedChamberEntrance_TopLeft, TRUE
	setmetatile 21, 9, METATILE_Cave_SealedChamberEntrance_TopMid, TRUE
	setmetatile 22, 9, METATILE_Cave_SealedChamberEntrance_TopRight, TRUE
	setmetatile 20, 10, METATILE_Cave_SealedChamberEntrance_BottomLeft, TRUE
	setmetatile 21, 10, METATILE_Cave_SealedChamberEntrance_BottomMid, FALSE
	setmetatile 22, 10, METATILE_Cave_SealedChamberEntrance_BottomRight, TRUE
	special DrawWholeMapView
	playse SE_BANG
	setflag FLAG_SYS_BRAILLE_REGIGIGAS_COMPLETED
	end
