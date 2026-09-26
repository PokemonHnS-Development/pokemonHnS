.set LOCALID_WINGULL, 3

FortreeCity_House4_MapScripts::
	.byte 0

FortreeCity_House4_EventScript_Woman::
	msgbox FortreeCity_House4_Text_BringsWorldCloserTogether, MSGBOX_NPC
	end

FortreeCity_House4_EventScript_Boy::
	lockall
	goto_if_set FLAG_RECEIVED_MENTAL_HERB, FortreeCity_House4_EventScript_ReceivedMentalHerb
	goto_if_set FLAG_WINGULL_DELIVERED_MAIL, FortreeCity_House4_EventScript_WingullReturned
	goto_if_set FLAG_WINGULL_SENT_ON_ERRAND, FortreeCity_House4_EventScript_WingullOnErrand
	msgbox FortreeCity_House4_Text_GoBirdPokemon, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_WINGULL_SENT_ON_ERRAND
	clearflag FLAG_GARBAGEFLAG
	applymovement LOCALID_WINGULL, FortreeCity_House4_Movement_WingullExit
	waitmovement 0
	removeobject LOCALID_WINGULL
	releaseall
	end

FortreeCity_House4_EventScript_WingullOnErrand::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_AskedWingullToRunErrand, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_House4_EventScript_WingullReturned::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_WelcomeWingullTakeMentalHerb, MSGBOX_DEFAULT
	giveitem ITEM_MENTAL_HERB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MENTAL_HERB
	releaseall
	end

FortreeCity_House4_EventScript_ReceivedMentalHerb::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_FriendsFarAwayThanksToWingull, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_House4_Movement_WingullExit:
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_in_place_faster_down
	delay_8
	step_end

FortreeCity_House4_EventScript_Wingull::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
	msgbox FortreeCity_House4_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House4_Text_BringsWorldCloserTogether:
	.string "Al estar con los POKéMON,\n"
	.string "la gente hace más y más amigos.\p"
	.string "Eso une más al mundo.\n"
	.string "¡Creo que es maravilloso!$"

FortreeCity_House4_Text_GoBirdPokemon:
	.string "¡Listo!\n"
	.string "¡Ve, POKéMON PÁJARO!$"

FortreeCity_House4_Text_AskedWingullToRunErrand:
	.string "Jeje, le pedí a mi WINGULL que\n"
	.string "hiciera un recado por mí.$"

FortreeCity_House4_Text_WelcomeWingullTakeMentalHerb:
	.string "¡Bien!\n"
	.string "¡Bienvenido, WINGULL!\p"
	.string "¿Eh? ¿Qué es esto?\n"
	.string "¿Qué trae ahí?\p"
	.string "¿Una HIERBA MENTAL?\n"
	.string "La habrá recogido en algún lado.\p"
	.string "No soy ENTRENADOR, así que\n"
	.string "quédatela tú.$"

FortreeCity_House4_Text_FriendsFarAwayThanksToWingull:
	.string "Gracias a mi WINGULL, tengo amigos\n"
	.string "que viven muy lejos.$"

FortreeCity_House4_Text_Wingull:
	.string "WINGULL: ¡Pihyoh!$"

