Route114_FossilManiacsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsHouse_OnTransition
	.byte 0

Route114_FossilManiacsHouse_OnTransition:
	setflag FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE
	end

Route114_FossilManiacsHouse_EventScript_FossilManiacsBrother::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_DIG, Route114_FossilManiacsHouse_EventScript_ReceivedDig
	msgbox Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother, MSGBOX_DEFAULT
	giveitem ITEM_TM_DIG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_DIG
	release
	end

Route114_FossilManiacsHouse_EventScript_ReceivedDig::
	msgbox Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsHouse_EventScript_RockDisplay::
	msgbox Route114_FossilManiacsHouse_Text_RocksFillDisplayCase, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_EventScript_Bookshelf::
	msgbox Route114_FossilManiacsHouse_Text_CrammedWithBooks, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother:
	.string "Mi hermano es el MANÍACO FÓSIL…\n"
	.string "Es un buen tipo que ama los FÓSILES…\p"
	.string "También ama cavar hoyos…\n"
	.string "Él cavó este hoyo solo…\p"
	.string "Toma esto para que puedas CAVAR\n"
	.string "hoyos como mi hermano…$"

Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance:
	.string "Si un POKéMON usa CAVAR en una\n"
	.string "cueva, volverás a la entrada…$"

Route114_FossilManiacsHouse_Text_RocksFillDisplayCase:
	.string "Rocas de formas peculiares llenan\n"
	.string "la vitrina…$"

Route114_FossilManiacsHouse_Text_CrammedWithBooks:
	.string "LA COMPOSICIÓN DE LOS ESTRATOS…\n"
	.string "CÓMO LA LLUVIA MOLDEA LA TIERRA…\l"
	.string "PIEDRAS, SUELO Y ROCA…\p"
	.string "Está lleno de libros.$"

