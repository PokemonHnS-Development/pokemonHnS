.set LOCALID_ROUTE25_MISTY, 10
.set LOCALID_ROUTE25_MAN, 11
.set LOCALID_ROUTE25_SUICUNE, 16
.set LOCALID_ROUTE25_EUSINE, 15
.set LOCALID_CAPE_MISTY, 20

Route25_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route25_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route25_MapScript_OnTransition::
	callnative SetTimeBasedEncounters
	goto_if_eq VAR_SUICUNE_ENCOUNTERS, 7, Route25_EventScript_SetSuicuneSceneMid
	end

Route25_EventScript_SetSuicuneSceneMid::
	setobjectxyperm LOCALID_ROUTE25_EUSINE, 65, 9
	end

Route25_EventScript_MistyRematch::
    lock
    faceplayer
    msgbox Route25_Text_Misty, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_CAPE_MISTY
    removeobject LOCALID_CAPE_MISTY
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_MISTY
    release
    end

Route25_Text_Misty:
    .string "MISTY: ¡Amo el ocaso de aquí!\n"
	.string "Me da valor para seguir adelante,\l"
	.string "¿sabes?\p"
	.string "¡Cierto!\p"
	.string "Si quieres un chapuzón real,\n"
	.string "¡ve al DOJO DE LUCHA!$"

Route25_EventScript_Dudley::
	trainerbattle_single TRAINER_DUDLEY Route25_Text_SchoolboyDudleySeen, Route25_Text_SchoolboyDudleyBeaten
	msgbox Route25_Text_SchoolboyDudleyAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Ellen::
	trainerbattle_single TRAINER_ELLEN Route25_Text_LassEllenSeen, Route25_Text_LassEllenBeaten
	msgbox Route25_Text_LassEllenAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Joe::
	trainerbattle_single TRAINER_JOE Route25_Text_SchoolboyJoeSeen, Route25_Text_SchoolboyJoeBeaten
	msgbox Route25_Text_SchoolboyJoeAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Laura::
	trainerbattle_single TRAINER_LAURA Route25_Text_LassLauraSeen, Route25_Text_LassLauraBeaten
	msgbox Route25_Text_LassLauraAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Lloyd::
	trainerbattle_single TRAINER_LLOYD Route25_Text_CamperLloydSeen, Route25_Text_CamperLloydBeaten
	msgbox Route25_Text_CamperLloydAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Shannon::
	trainerbattle_single TRAINER_SHANNON Route25_Text_LassShannonSeen, Route25_Text_LassShannonBeaten
	msgbox Route25_Text_LassShannonAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Pat::
	trainerbattle_single TRAINER_PAT Route25_Text_SupernerdPatSeen, Route25_Text_SupernerdPatBeaten
	msgbox Route25_Text_SupernerdPatAfter, MSGBOX_AUTOCLOSE
	end

Route25_EventScript_Kevin::
	lock
	faceplayer
	goto_if_set FLAG_ROUTE25_GOT_NUGGET, Route25_EventScript_KevinAfter
	msgbox Route25_Text_CooltrainerKevinNugget, MSGBOX_DEFAULT
	giveitem ITEM_BIG_NUGGET
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_ROUTE25_GOT_NUGGET
	msgbox Route25_Text_CooltrainerKevinSeen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_KEVIN, Route25_Text_CooltrainerKevinBeaten
	msgbox Route25_Text_CooltrainerKevinAfter, MSGBOX_DEFAULT
	closemessage
	release
	end
Route25_EventScript_KevinAfter::
	msgbox Route25_Text_CooltrainerKevinAfter, MSGBOX_NPC
	end

Route25_EventScript_BillsHouseSign::
	msgbox Route25_Text_BillsHouseSign, MSGBOX_SIGN
	end

Route25_Trigger_MistyRight::
	lock
	turnobject LOCALID_ROUTE25_MISTY, DIR_SOUTH
	delay 40
	turnobject LOCALID_ROUTE25_MAN, DIR_SOUTH
	playse SE_PIN
	applymovement2 LOCALID_ROUTE25_MAN, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_ROUTE25_MAN, Route25_Movement_ManLeaveRight
	waitmovement 0
	applymovement2 LOCALID_ROUTE25_MISTY, Route25_Movement_MistyWalkToPlayerRight
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	goto Route25_EventScript_Misty
Route25_Trigger_MistyLeft::
	lock
	turnobject LOCALID_ROUTE25_MISTY, DIR_SOUTH
	delay 40
	turnobject LOCALID_ROUTE25_MAN, DIR_SOUTH
	playse SE_PIN
	applymovement2 LOCALID_ROUTE25_MAN, Common_Movement_ExclamationMark
	delay 60
	applymovement2 LOCALID_ROUTE25_MAN, Route25_Movement_ManLeaveLeft
	waitmovement 0
	applymovement2 LOCALID_ROUTE25_MISTY, Route25_Movement_MistyWalkToPlayerLeft
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	goto Route25_EventScript_Misty
Route25_EventScript_Misty::
	msgbox Route25_Text_MistyDate, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_ROUTE25_MISTY, Route25_Movement_MistyLeave
	waitmovement 0
	removeobject LOCALID_ROUTE25_MISTY
	removeobject LOCALID_ROUTE25_MAN
	setflag FLAG_HIDE_ROUTE25_MISTY
	clearflag FLAG_HIDE_CERULEAN_GYM_TRAINERS
	setflag FLAG_HIDE_CERULEAN_GYM_POKEMON
	setvar VAR_CERULEAN_CITY_STATE, 3
	release
	end

Route25_Trigger_SuicuneLeft::
	lock
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	delay 60
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_ROUTE25_SUICUNE, Route25_Movement_Suicune1
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Route25_Movement_WalkToSuicune
	waitmovement 0
	goto Route25_EventScript_SuicuneMerge
Route25_Trigger_SuicuneRight::
	lock
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	delay 60
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_ROUTE25_SUICUNE, Route25_Movement_Suicune1
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Route25_Movement_WalkToSuicune
	waitmovement 0
	goto Route25_EventScript_SuicuneMerge
Route25_EventScript_SuicuneMerge::
	clearflag FLAG_HIDE_ROUTE25_EUSINE
	addobject LOCALID_ROUTE25_EUSINE
	applymovement LOCALID_ROUTE25_EUSINE, Route25_Movement_EusineEnter
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	msgbox Route25_Text_Eusine1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE25_EUSINE, Route25_Movement_EusineSide
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox Route25_Text_Eusine2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SUICUNE_ENCOUNTERS, 7
	release
	end
	
Route25_Text_Eusine1:
	.string "EUSINE: Puff, puff...\n"
	.string "No soy... rival para ti.\p"
	.string "...Como predije.\n"
	.string "..........................\l"
	.string "... Adelante.\p"
	.string "Desde que te vi en la TORRE QUEMADA\n"
	.string "de CIUDAD IRIS, ya sabía\l"
	.string "que SUICUNE te elegiría\l"
	.string "a ti.$"

Route25_Text_Eusine2:
	.string "¡Mira allí!\p"
	.string "¡SUICUNE te está esperando!\n"
	.string "Esperaba una batalla con un\l"
	.string "entrenador digno al que pueda\l"
	.string "confiarle su destino.$"

Route25_Text_Eusine3:
	.string "{PLAYER}...\n"
	.string "Ustedes dos son increíbles...\p"
	.string "¡Nunca vi una batalla tan\n"
	.string "intensa!\l"
	.string "No me arrepiento de nada...\p"
	.string "¡Adiós, SUICUNE!\n"
	.string "¡Adiós... {PLAYER}!$"

Route25_EventScript_Eusine::
	msgbox Route25_Text_Eusine2, MSGBOX_NPC
	end

Route25_EventScript_Suicune::
	lock
	faceplayer
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_ROUTE25_SUICUNE, Route25_Movement_Suicune1
	playse SE_LEDGE
	waitse
	waitmovement 0
	playmoncry SPECIES_SUICUNE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	seteventmon SPECIES_SUICUNE, 50
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route25_EventScript_SuicuneRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE25_SUICUNE
	setflag FLAG_HIDE_ROUTE25_SUICUNE
	fadescreenswapbuffers FADE_FROM_BLACK
	goto_if_ge VAR_SUICUNE_ENCOUNTERS, 8, Route25_EventScript_SuicunePostGame
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 66, Route25_AdjustPlayer
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	turnobject LOCALID_ROUTE25_EUSINE, DIR_NORTH
	msgbox Route25_Text_Eusine3, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_ROUTE25_EUSINE, Route25_Movement_EusineLeave
	waitmovement 0
	removeobject LOCALID_ROUTE25_EUSINE
	setflag FLAG_HIDE_ROUTE25_EUSINE
	clearflag FLAG_HIDE_CELADON_EUSINE
	setvar VAR_SUICUNE_ENCOUNTERS, 8
	release
	end

Route25_EventScript_SuicuneRan::
	release
	end

Route25_AdjustPlayer::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	return

Route25_EventScript_SuicunePostGame::
	release
	end

Route25_Movement_EusineLeave:
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

Route25_Movement_EusineSide:
	walk_slow_left
	walk_slow_up
	step_end

Route25_Movement_EusineEnter:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_up
	walk_slow_up
	step_end

Route25_Movement_Suicune1:
	jump_in_place_down
	step_end

Route25_Movement_WalkToSuicune:
	walk_up
	walk_up
	step_end

Route25_Movement_MistyLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route25_Movement_ManLeaveRight:
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
Route25_Movement_ManLeaveLeft:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route25_Movement_MistyWalkToPlayerRight:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	face_right
	step_end
Route25_Movement_MistyWalkToPlayerLeft:
	walk_down
	walk_down
	walk_down
	walk_down
	face_left
	step_end

Route25_Text_MistyDate:
	.string "MISTY: ¡Aww! ¿Por qué vienes a\n"
	.string "molestarnos justo ahora?\p"
	.string "¿Sabes cómo llaman a la\n"
	.string "gente como tú?\p"
	.string "¡Plagas! ¡Me oíste bien,\n"
	.string "plaga!\p"
	.string "…\p"
	.string "…¿Oh? Esas MEDALLAS…\n"
	.string "¿Son MEDALLAS de JOHTO?\p"
	.string "Si tienes ocho, debes ser\n"
	.string "bueno.\p"
	.string "Bien. Ve al GIMNASIO CERULEAN.\p"
	.string "Estaré feliz de luchar contigo.\p"
	.string "Soy MISTY, la LÍDER del\n"
	.string "GIMNASIO CERULEAN.$"

Route25_Text_SchoolboyDudleySeen:
	.string "¡Vence a los seis entrenadores\n"
	.string "para ganar un gran premio!\p"
	.string "¿Crees que puedes lograrlo?$"

Route25_Text_SchoolboyDudleyBeaten:
	.string "¡Whoo! Muy bien.$"

Route25_Text_SchoolboyDudleyAfter:
	.string "Hice mi mejor esfuerzo.\n"
	.string "No me arrepiento de nada.$"

Route25_Text_LassEllenSeen:
	.string "Soy el segundo.\n"
	.string "¡Ahora va en serio!$"

Route25_Text_LassEllenBeaten:
	.string "¿Cómo pude perder?$"

Route25_Text_LassEllenAfter:
	.string "Hice lo mejor que pude.\n"
	.string "No me arrepiento.$"

Route25_Text_SchoolboyJoeSeen:
	.string "¡Aquí está el No. 3!\n"
	.string "No será fácil.$"

Route25_Text_SchoolboyJoeBeaten:
	.string "¡Ay! ¡Me aplastaron!$"

Route25_Text_SchoolboyJoeAfter:
	.string "Hice lo mejor que pude.\n"
	.string "No me arrepiento.$"

Route25_Text_LassLauraSeen:
	.string "¡Soy el No. 4!\n"
	.string "¿Ya te cansaste?$"

Route25_Text_LassLauraBeaten:
	.string "Yo también perdí...$"

Route25_Text_LassLauraAfter:
	.string "Hice lo mejor que pude.\n"
	.string "No me arrepiento de nada.$"

Route25_Text_CamperLloydSeen:
	.string "¡Bien! Soy el No. 5.\n"
	.string "¡Te voy a aplastar!$"

Route25_Text_CamperLloydBeaten:
	.string "¡Vaya! Fue demasiado.$"

Route25_Text_CamperLloydAfter:
	.string "Hice lo mejor que pude.\n"
	.string "No me arrepiento de nada.$"

Route25_Text_LassShannonSeen:
	.string "Soy el último en la fila, ¡pero\n"
	.string "te digo que soy fuerte!$"

Route25_Text_LassShannonBeaten:
	.string "Tienes que estar bromeando.$"

Route25_Text_LassShannonAfter:
	.string "Hice lo mejor que pude.\n"
	.string "No me arrepiento de nada.$"

Route25_Text_SupernerdPatSeen:
	.string "Mufufufu…\p"
	.string "No tengo nada que ver con los\n"
	.string "entrenadores musculosos.\p"
	.string "Esperé aquí para vencerte cuando\n"
	.string "estuvieras cansado por todas las\l"
	.string "batallas.$"

Route25_Text_SupernerdPatBeaten:
	.string "¿No estás cansado para nada?$"

Route25_Text_SupernerdPatAfter:
	.string "Lo siento... No volveré a hacer\n"
	.string "trampa...$"

Route25_Text_CooltrainerKevinNugget:
	.string "Tuviste una batalla más de la\n"
	.string "esperada, pero ganaste\l"
	.string "al final.\p"
	.string "Como prometí, tienes un premio.$"

Route25_Text_CooltrainerKevinSeen:
	.string "Pero tras ver cómo luchas,\n"
	.string "quiero ver cómo me va a mí.\p"
	.string "¿Qué dices? Déjame\n"
	.string "enfrentarte.$"

Route25_Text_CooltrainerKevinBeaten:
	.string "¡Nunca tuve una batalla tan\n"
	.string "buena!$"

Route25_Text_CooltrainerKevinAfter:
	.string "¡Fue una gran batalla!\p"
	.string "¡Tú y tu POKéMON son realmente\n"
	.string "increíbles!$"

Route25_Text_BillsHouseSign:
	.string "CABAÑA DEL MAR\n"
	.string "CASA DE BILL$"

