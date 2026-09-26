.set LOCALID_HIDEOUT_GUARD, 5

JaggedPass_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, JaggedPass_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, JaggedPass_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JaggedPass_OnLoad
	.byte 0

JaggedPass_OnResume:
	callnative SetTimeBasedEncounters
	setstepcallback STEP_CB_ASH
	call_if_eq VAR_JAGGED_PASS_STATE, 0, JaggedPass_EventScript_CheckHasMagmaEmblem
	end

JaggedPass_EventScript_CheckHasMagmaEmblem::
	checkitem ITEM_MAGMA_EMBLEM
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_SetReadyToOpenHideout
	return

JaggedPass_EventScript_SetReadyToOpenHideout::
	setvar VAR_JAGGED_PASS_STATE, 1
	return

JaggedPass_OnTransition:
	call_if_eq VAR_JAGGED_PASS_ASH_WEATHER, 1, JaggedPass_EventScript_SetWeatherAsh
	callnative SetTimeBasedEncounters
	end

JaggedPass_EventScript_SetWeatherAsh::
	setweather WEATHER_VOLCANIC_ASH
	doweather
	return

JaggedPass_OnLoad:
	goto_if_le VAR_JAGGED_PASS_STATE, 1, JaggedPass_EventScript_ConcealHideoutEntrance
	end

JaggedPass_EventScript_ConcealHideoutEntrance::
	setmetatile 16, 17, METATILE_Lavaridge_RockWall, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_RockWall, TRUE
	end

JaggedPass_EventScript_OpenMagmaHideout::
	lockall
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	msgbox JaggedPass_Text_BoulderShakingInResponseToEmblem, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 16  @ num shakes
	setvar VAR_0x8007, 3   @ shake delay
	special ShakeCamera
	waitstate
	playse SE_EFFECTIVE
	setmetatile 16, 17, METATILE_Lavaridge_CaveEntrance_Top, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_CaveEntrance_Bottom, FALSE
	special DrawWholeMapView
	delay 30
	setvar VAR_JAGGED_PASS_STATE, 2
	waitse
	releaseall
	end

JaggedPass_EventScript_MagmaHideoutGuard::
	lockall
	goto_if_set FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS, JaggedPass_EventScript_GuardDefeated
	waitse
	playse SE_PIN
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GruntIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_TERRELL, JaggedPass_Text_GruntDefeat
	setflag FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_GuardDefeated::
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GoWhereverYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_Eric::
	trainerbattle_single TRAINER_ERIC, JaggedPass_Text_EricIntro, JaggedPass_Text_EricDefeat
	msgbox JaggedPass_Text_EricPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Diana::
	trainerbattle_single TRAINER_KAZU, JaggedPass_Text_DianaIntro, JaggedPass_Text_DianaDefeat, JaggedPass_EventScript_RegisterDiana
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_DianaRematch
	msgbox JaggedPass_Text_DianaPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterDiana::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_DianaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KAZU
	release
	end

JaggedPass_EventScript_DianaRematch::
	trainerbattle_rematch TRAINER_KAZU, JaggedPass_Text_DianaRematchIntro, JaggedPass_Text_DianaRematchDefeat
	msgbox JaggedPass_Text_DianaPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Ethan::
	trainerbattle_single TRAINER_NAOKO, JaggedPass_Text_EthanIntro, JaggedPass_Text_EthanDefeat, JaggedPass_EventScript_RegisterEthan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_EthanRematch
	msgbox JaggedPass_Text_EthanPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterEthan::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_EthanRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_NAOKO
	release
	end

JaggedPass_EventScript_EthanRematch::
	trainerbattle_rematch TRAINER_NAOKO, JaggedPass_Text_EthanRematchIntro, JaggedPass_Text_EthanRematchDefeat
	msgbox JaggedPass_Text_EthanPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Julio::
	trainerbattle_single TRAINER_JULIO, JaggedPass_Text_JulioIntro, JaggedPass_Text_JulioDefeat
	msgbox JaggedPass_Text_JulioPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Autumn::
	trainerbattle_single TRAINER_COLETTE, JaggedPass_Text_AutumnIntro, JaggedPass_Text_AutumnDefeat
	msgbox JaggedPass_Text_AutumnPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_Text_EricIntro:
	.string "PASO ESCARPADO DEL MT. CHIMNEY…\p"
	.string "Esto es lo que siempre quise\n"
	.string "en una montaña.\p"
	.string "Esta rugosidad escarpada…\n"
	.string "¡Me llega al alma!$"

JaggedPass_Text_EricDefeat:
	.string "¡Perder me dejó amargado!$"

JaggedPass_Text_EricPostBattle:
	.string "Sí, perdí en POKéMON…\p"
	.string "Pero en el amor por las\n"
	.string "montañas, ¡te supero!$"

JaggedPass_Text_DianaIntro:
	.string "Esto no es un paseo cualquiera.\n"
	.string "No es lugar para un picnic.$"

JaggedPass_Text_DianaDefeat:
	.string "¡Ohhh, no!\n"
	.string "El suelo es muy irregular…$"

JaggedPass_Text_DianaPostBattle:
	.string "¿Sabías?\p"
	.string "Algunos usan sus bicicletas\n"
	.string "en este paso tan irregular.$"

JaggedPass_Text_DianaRegister:
	.string "¿Volverás por esta zona?\n"
	.string "Si regresas, quiero una revancha.$"

JaggedPass_Text_DianaRematchIntro:
	.string "Los picnics son divertidos.\n"
	.string "¡Igual que los POKéMON!$"

JaggedPass_Text_DianaRematchDefeat:
	.string "¡Perdí solo porque el suelo es\n"
	.string "muy irregular!$"

JaggedPass_Text_DianaPostRematch:
	.string "Olvidaré la derrota y solo\n"
	.string "disfrutaré este camino irregular.$"

JaggedPass_Text_EthanIntro:
	.string "PASO ESCARPADO es difícil de andar.\n"
	.string "Es un buen lugar para entrenar.$"

JaggedPass_Text_EthanDefeat:
	.string "Todo terminó mientras aún\n"
	.string "buscábamos dónde apoyarnos…$"

JaggedPass_Text_EthanPostBattle:
	.string "Si tuviera una ACRO BIKE, podría\n"
	.string "saltar los bordes.$"

JaggedPass_Text_EthanRegister:
	.string "Cuando me acostumbre a este suelo,\n"
	.string "¡seguro que ganaré!\p"
	.string "¿Me registras en tu POKéNAV?$"

JaggedPass_Text_EthanRematchIntro:
	.string "Ya me acostumbré a este suelo.\n"
	.string "Ahora canto mientras subo.$"

JaggedPass_Text_EthanRematchDefeat:
	.string "Sigue siendo difícil luchar en este\n"
	.string "suelo tan irregular…$"

JaggedPass_Text_EthanPostRematch:
	.string "Debo conseguir una ACRO BIKE de RYDEL\n"
	.string "en CIUDAD MALVA…$"

JaggedPass_Text_GruntIntro:
	.string "¡Wah!\n"
	.string "¿Qué haces aquí?\p"
	.string "¿Qué hago yo en un lugar así?\p"
	.string "¿A ti qué te importa?$"

JaggedPass_Text_GruntDefeat:
	.string "Urrrgh…\p"
	.string "Debí entrar al ESCONDITE\n"
	.string "de inmediato…$"

JaggedPass_Text_GoWhereverYouWant:
	.string "¡Está bien, está bien!\n"
	.string "¡Admito que eres fuerte!\p"
	.string "No te preocupes por mí.\n"
	.string "¡Ve a donde quieras!$"

JaggedPass_Text_BoulderShakingInResponseToEmblem:
	.string "¡Oh! ¡La roca vibra por el efecto\n"
	.string "del EMBLEMA MAGMA!$"

JaggedPass_Text_JulioIntro:
	.string "¡Aiyeeh! ¡Da miedo bajar la\n"
	.string "montaña de un solo golpe!$"

JaggedPass_Text_JulioDefeat:
	.string "Siento que me desarmo…$"

JaggedPass_Text_JulioPostBattle:
	.string "Mi bici saltó tanto que\n"
	.string "me duele el trasero…$"

JaggedPass_Text_AutumnIntro:
	.string "Subo esta colina cada día.\n"
	.string "¡Confío en mi fuerza!$"

JaggedPass_Text_AutumnDefeat:
	.string "Hmm...\n"
	.string "¿Qué salió mal?$"

JaggedPass_Text_AutumnPostBattle:
	.string "¿Qué es esa roca tan extraña\n"
	.string "más arriba de la colina?$"

