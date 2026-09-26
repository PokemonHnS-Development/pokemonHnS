DarkCave_NorthSide_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DarkCave_NorthSide_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

DarkCave_NorthSide_OnTransition: 
	callnative SetTimeBasedEncounters
	end

DarkCave2_EventScript_Item_BlackFlute::
	finditem ITEM_BLACK_FLUTE
	end

DarkCave2_EventScript_Item_StarPiece::
	finditem ITEM_STAR_PIECE
	end

DarkCave2_EventScript_BlackGlasses::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BLACK_GLASSES, DarkCave2_EventScript_BlackGlassesGot
	msgbox DarkCave2_Text_Nerd, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_GLASSES
	setflag FLAG_GOT_BLACK_GLASSES
	closemessage
	release
	end

DarkCave2_EventScript_BlackGlassesGot::
	msgbox DarkCave2_Text_Nerd2, MSGBOX_DEFAULT
	closemessage
	release
	end

DarkCave2_Text_Nerd:
    .string "¡Vaya! ¡Me has asustado!\p"
    .string "Llevaba mis BLACK-GLASSES,\n"
    .string "así que no te vi venir.\p"
    .string "¿Qué hago yo aquí?\p"
    .string "Oye, no te preocupes por eso.\p"
    .string "Te daré unos BLACK-GLASSES,\n"
    .string "así que olvida que me viste,\n"
    .string "¿vale?$"

DarkCave2_Text_Nerd2:
    .string "BLACK-GLASSES sube el poder de\n"
    .string "los movimientos tipo SINONIMO.$"
