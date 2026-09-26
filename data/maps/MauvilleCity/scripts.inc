.set LOCALID_WALLY, 6
.set LOCALID_WALLYS_UNCLE, 7
.set LOCALID_SCOTT, 11

MauvilleCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	.byte 0

MauvilleCity_OnTransition:
	setflag FLAG_VISITED_BLACKTHORN_CITY
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_GARBAGEFLAG
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_GARBAGEVAR, 0
	call_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	end

MauvilleCity_EventScript_MoveWattsonBackToGym::
	clearflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_MagnezoneEvo::
	msgbox MauvilleCity_EventScript_MagnezoneEvo_Text, MSGBOX_NPC
	end

MauvilleCity_EventScript_MagnezoneEvo_Text:
	.string "¿Sabes que MAGNETON evoluciona?\n"
	.string "¿Sabes cómo?\p"
	.string "Es que... me gustaría saberlo.\p"
	.string "Sé que era algo relacionado con una\n"
	.string "PIEDRA. ¡PIEDRA TRUENO, exacto!\p"
	.string "Pero no era usándola.\n"
	.string "¿Luchando? ¿SOSTENIÉNDOLA?\l"
	.string "En serio, no lo sé...$"

MauvilleCity_EventScript_Boy::
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac::
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman::
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy::
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign::
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign::
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign::
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign::
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM::
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained::
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally::
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally::
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt::
	call_if_eq VAR_RESULT, YES, MauvilleCity_EventScript_BattleWally
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_DeclineWallyBattle
	closemessage
	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth1
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth1
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerFaceUncleNorth
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerNorth
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth2
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth2
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast1
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast1
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerEast
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast2
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast2
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally::
	removeobject LOCALID_WALLY
	removeobject LOCALID_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_GARBAGEFLAG
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottApproachPlayerNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth::
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast::
	setobjectxyperm LOCALID_SCOTT, 12, 13
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally::
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT
	return

MauvilleCity_EventScript_DeclineWallyBattle::
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain::
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_Movement_WallyExitNorth1:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1:
	delay_16
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast1:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast:
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2:
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

MauvilleCity_Movement_ScottApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_EventScript_Wattson::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_EventScript_CompletedNewMauville
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville::
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt::
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall::
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy:
	.string "TÍO: Supongo que es por los POKéMON\n"
	.string "que el chico tiene más energía...\l"
	.string "Pero se ha vuelto demasiado activo...$"

MauvilleCity_Text_WallyWantToChallengeGym:
	.string "WALLY: ¡Ay, TÍO, por favor!\p"
	.string "Quiero retar al GIMNASIO y ver\n"
	.string "cuánto he mejorado.\p"
	.string "¿Por favor? ¿Puedo, por favor?$"

MauvilleCity_Text_UncleYourePushingIt:
	.string "TÍO: Espera un momento, WALLY.\p"
	.string "Desde que vives con POKéMON,\n"
	.string "te has vuelto mucho más fuerte.\p"
	.string "¿No crees que es precipitado\n"
	.string "retar a un GIMNASIO de repente?$"

MauvilleCity_Text_WallyWeCanBeatAnyone:
	.string "WALLY: No forzaré las cosas.\p"
	.string "¡Si me uno a RALTS,\n"
	.string "podremos vencer a cualquiera!$"

MauvilleCity_Text_WallyWillYouBattleMe:
	.string "WALLY: ¡Oh! ¡Hola, {PLAYER}!\p"
	.string "Me he vuelto más fuerte desde\n"
	.string "que nos conocimos.\p"
	.string "{PLAYER}, quiero que tú y mi TÍO\n"
	.string "lo entiendan.\p"
	.string "{PLAYER}, por favor, ¿tendrías\n"
	.string "una batalla conmigo?$"

MauvilleCity_Text_WallyMyUncleWontKnowImStrong:
	.string "WALLY: Oh... Si no luchas conmigo,\n"
	.string "{PLAYER}, mi TÍO no sabrá que me\l"
	.string "he vuelto muy fuerte.$"

MauvilleCity_Text_UncleCanYouBattleWally:
	.string "TÍO: {PLAYER}{KUN}, ¿verdad?\n"
	.string "Por WALLY, ¿podrías luchar con él\l"
	.string "solo por esta vez?\p"
	.string "No creo que escuche razones\n"
	.string "estando así ahora mismo.$"

MauvilleCity_Text_WallyPleaseBattleMe:
	.string "WALLY: {PLAYER}, ¡por favor!\n"
	.string "¡Lucha conmigo, por favor!$"

MauvilleCity_Text_WallyHereICome:
	.string "WALLY: {PLAYER}, gracias.\p"
	.string "Bien... ¡Aquí voy!$"

MauvilleCity_Text_WallyDefeat:
	.string "WALLY: … … … … … … …\p"
	.string "… … … … … … … …\p"
	.string "Perdí…$"

MauvilleCity_Text_WallyIllGoBackToVerdanturf:
	.string "WALLY: TÍO...\n"
	.string "Volveré a PUEBLO VERDANTE...$"

MauvilleCity_Text_ThankYouNotEnoughToBattle:
	.string "{PLAYER}, gracias.\n"
	.string "Ser ENTRENADOR es duro, ¿no?\p"
	.string "No basta con tener POKéMON\n"
	.string "y hacer que luchen. No se trata de\l"
	.string "eso ser un verdadero ENTRENADOR.$"

MauvilleCity_Text_UncleNoNeedToBeDown:
	.string "TÍO: WALLY, no hace falta que seas\n"
	.string "tan duro contigo mismo.\p"
	.string "¿Qué te impide volverte cada vez\n"
	.string "más y más fuerte?\p"
	.string "Vamos, volvamos a casa.\n"
	.string "Todos te están esperando.$"

MauvilleCity_Text_UncleVisitUsSometime:
	.string "TÍO: {PLAYER}{KUN}, acabo de notar\n"
	.string "que debes ser el ENTRENADOR que\l"
	.string "cuidó de WALLY cuando atrapó\l"
	.string "sus POKéMON.\p"
	.string "¿Por qué no nos visitas en PUEBLO\n"
	.string "VERDANTE algún día?\l"
	.string "Seguro que a WALLY le gustaría.$"


MauvilleCity_Text_WallyPokenavCall:
	.string "... ... ... ... ...\n"
	.string "... ... ... ... ... ¡Bip!\p"
	.string "WALLY: ¡Hola, {PLAYER}!\p"
	.string "¡Quería decirte que mi tío me\n"
	.string "compró un POKéNAV!\p"
	.string "¡Ahora puedo contactarte cuando\n"
	.string "quiera, {PLAYER}!\p"
	.string "... ... ... ... ...\n"
	.string "... ... ... ... ... ¡Click!$"

MauvilleCity_Text_RegisteredWally:
	.string "Registré a WALLY\n"
	.string "en el POKéNAV.$"

MauvilleCity_Text_ScottYouDidntHoldBack:
	.string "SCOTT: Jeje...\n"
	.string "¡Vi ese combate!\p"
	.string "Eres amigo de ese chico WALLY,\n"
	.string "¿verdad?\p"
	.string "Pero no te contuviste y lo\n"
	.string "venciste impresionantemente.\p"
	.string "¡Sí! ¡De eso se trata una real\n"
	.string "batalla POKéMON!\p"
	.string "¡Idolatro a TRAINERS así!\p"
	.string "... ... ... ... ... ...\n"
	.string "¡Estaré apoyándote!$"

MauvilleCity_Text_WattsonNeedFavorTakeKey:
	.string "WATTSON: ¡Oh, {PLAYER}{KUN}!\n"
	.string "¡Te ves con mucha energía!\l"
	.string "¡Eso es bueno, wahahahaha!\p"
	.string "¡Bien! ¡Ya decidí!\n"
	.string "¡Necesito un favor, {PLAYER}{KUN}!\p"
	.string "CIUDAD MALTA tiene un sector\n"
	.string "subterráneo llamado NUEVA MALTA.\p"
	.string "{PLAYER}{KUN}, ve allí y apaga el\n"
	.string "GENERADOR.\p"
	.string "El GENERADOR está fallando un poco.\n"
	.string "Se está volviendo peligroso.\p"
	.string "Toma, es la LLAVE para entrar a\n"
	.string "NUEVA MALTA.$"

MauvilleCity_Text_WattsonWontBeChallenge:
	.string "WATTSON: No te preocupes por eso.\n"
	.string "No será un reto para ti.\p"
	.string "La entrada a NUEVA MALTA está a\n"
	.string "poco SURF de la RUTA 110.\p"
	.string "¡Eso es todo, confío en ti!\n"
	.string "¡Wahahahaha!$"

MauvilleCity_Text_WattsonThanksTakeTM:
	.string "WATTSON: ¡Wahahahaha!\p"
	.string "¡Lo sabía, {PLAYER}{KUN}! ¡Sabía que\n"
	.string "elegí bien al pedirte ayuda!\p"
	.string "Toma mi agradecimiento: ¡una MT\n"
	.string "con RAYO!\p"
	.string "¡Tómala, te la ganaste!$"

MauvilleCity_Text_WattsonYoungTakeCharge:
	.string "WATTSON: ¡Wahahahaha!\p"
	.string "¡Me alegra mucho ver que los\n"
	.string "jóvenes tomen la iniciativa!$"

MauvilleCity_Text_NurseHurtMonBackToHealth:
	.string "Sabes, es genial tener batallas\n"
	.string "POKéMON y esas cosas...\p"
	.string "Pero si tu POKéMON se lastima,\n"
	.string "debes curarlo hasta que sane.$"

MauvilleCity_Text_AllSortsOfPeopleComeThrough:
	.string "Los caminos de este pueblo van al\n"
	.string "norte y sur, y al este y oeste.\p"
	.string "Por eso, llega todo tipo de\n"
	.string "gente por aquí.$"

MauvilleCity_Text_RydelVeryGenerous:
	.string "¿Fuiste a RYDEL'S CYCLES ya?\p"
	.string "RYDEL, el dueño, es un hombre\n"
	.string "muy generoso.$"

MauvilleCity_Text_PokemonCanJumpYouOnBike:
	.string "Aunque vayas en BIKE,\n"
	.string "los POKéMON salvajes pueden atacarte.$"

MauvilleCity_Text_CitySign:
	.string "CIUDAD MALVEILLE\n"
	.string "¡La brillante ciudad de la diversión!$"

MauvilleCity_Text_GymSign:
	.string "GIMNASIO de CIUDAD MALVEILLE\n"
	.string "LÍDER: WATTSON\l"
	.string "¡El hombre electrizante y alegre!$"

MauvilleCity_Text_BikeShopSign:
	.string "¡Rueda en la grava y sacude tu\n"
	.string "alma!\l"
	.string "CICLOS RYDEL$"

MauvilleCity_Text_GameCornerSign:
	.string "¡El lugar de juego para todos!\n"
	.string "GAME CORNER de CIUDAD MALVEILLE$"

MauvilleCity_Text_ExplainTV:
	.string "Hola, ¿ves la TV?\p"
	.string "Han puesto programas nuevos y geniales\n"
	.string "recientemente.\p"
	.string "La TV es genial. He visto a mis amigos\n"
	.string "en la TV de la nada.\p"
	.string "A veces, hasta te ponen en la TV\n"
	.string "sin avisarte.\p"
	.string "Desearía salir en la TV algún día.\p"
	.string "Por eso creo que deberías ver la TV\n"
	.string "siempre que puedas.$"

MauvilleCity_Text_BeenCheckingOutTV:
	.string "Hola, ¿has estado viendo la TV?$"
