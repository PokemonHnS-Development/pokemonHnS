.set LOCALID_ARCHIE, 1
.set LOCALID_MAXIE, 2
.set LOCALID_TABITHA, 3
.set LOCALID_MAGMA_GRUNT_2, 22
.set LOCALID_MAGMA_GRUNT_1, 29


MtChimney_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume:
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie::
	lock
	faceplayer
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	closemessage
	applymovement LOCALID_ARCHIE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end

MtChimney_EventScript_ArchieGoStopTeamMagma::
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting::
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT
	applymovement LOCALID_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAXIE, Common_Movement_Delay48
	waitmovement 0
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat
	msgbox MtChimney_Text_MaxieYouHaventSeenLastOfMagma, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_TABITHA
	removeobject LOCALID_MAGMA_GRUNT_2
	setflag FLAG_GARBAGEFLAG
	fadescreenswapbuffers FADE_FROM_BLACK
	setobjectxyperm LOCALID_ARCHIE, 10, 12
	addobject LOCALID_ARCHIE
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieApproachPlayerEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieApproachPlayerNorth
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieExitEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieExitNorth
	removeobject LOCALID_ARCHIE
	setflag FLAG_GARBAGEFLAG
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_GARBAGEFLAG
	setflag FLAG_GARBAGEFLAG
	clearflag FLAG_GARBAGEFLAG
	releaseall
	end

MtChimney_EventScript_ArchieApproachPlayerEast::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE
	call_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RemoveMoney
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_RemoveMoney::
	removemoney 200
	updatemoneybox
	return

MtChimney_EventScript_DeclineLavaCookie::
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney::
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8:
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

MtChimney_Movement_Unused9:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10:
	walk_down
	step_end

MtChimney_Movement_Unused11:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12:
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15:
	walk_left
	walk_in_place_faster_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1::
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2::
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3::
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2::
	trainerbattle_single TRAINER_THEO, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_BusyMagmaGrunt1::
	msgbox MtChimney_Text_TeamAquaAlwaysMessingWithPlans, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt2::
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3::
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4::
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5::
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6::
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena::
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena::
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine::
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone::
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff::
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn::
	msgbox MtChimney_Text_MetoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign::
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby::
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby::
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa::
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila::
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1::
	trainerbattle_single TRAINER_TERU, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer::
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch::
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano:
	.string "El poder del METEORITO…\p"
	.string "Al ampliar su poder con esta\n"
	.string "máquina, la actividad volcánica del\l"
	.string "MT. CHIMNEY se intensificará…\p"
	.string "Su energía crecerá en el fondo\n"
	.string "del cráter y…\l"
	.string "Fufufu…$"

MtChimney_Text_MaxieIntro:
	.string "MAXIE: ¿Hm?\n"
	.string "¿Quién eres?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Oí a ARCHIE quejarse de un niño\n"
	.string "que se mete en los asuntos del\l"
	.string "TEAM AQUA.\p"
	.string "Debes ser tú quien decía.\p"
	.string "¡Humph! ¿Piensas interferir con\n"
	.string "nosotros, el TEAM MAGMA?\p"
	.string "Ahora escucha.\n"
	.string "Hace mucho, los seres vivos usaban\l"
	.string "la tierra para vivir y crecer.\p"
	.string "¡Por eso la tierra es lo más vital!\n"
	.string "¡Es la cuna de todo!\p"
	.string "Por eso el TEAM MAGMA se dedica\n"
	.string "a expandir la masa terrestre.\p"
	.string "¡Es para el avance de la humanidad\n"
	.string "y de los POKéMON!\p"
	.string "Y para eso, necesitamos el poder de\n"
	.string "lo que duerme en esta montaña…\p"
	.string "¡Oh! No hacía falta que supieras\n"
	.string "tanto.\p"
	.string "¡Pero no importa!\n"
	.string "¡Te enseñaré las consecuencias de\l"
	.string "estorbar nuestro gran plan!$"

MtChimney_Text_MaxieDefeat:
	.string "¡¿Qué?!\p"
	.string "¡¿Yo, MAXIE, fui sorprendido?!$"

MtChimney_Text_MaxieYouHaventSeenLastOfMagma:
	.string "MAXIE: Pero basta.\n"
	.string "Me retiraré por esta vez.\p"
	.string "Pero no creas que es la última vez\n"
	.string "que verás al TEAM MAGMA.\p"
	.string "Fufufu…\p"
	.string "Aun sin el METEORITO, si obtenemos\n"
	.string "ese ORBE… Fufufu…$"

MtChimney_Text_TabithaIntro:
	.string "¡Hehehe!\p"
	.string "¡Así que viniste hasta aquí!\p"
	.string "¡Pero llegas tarde!\n"
	.string "¡Ya entregué el METEORITO de\l"
	.string "METEOR FALLS al JEFE!$"

MtChimney_Text_TabithaDefeat:
	.string "Hehehe…\p"
	.string "Aunque haya perdido, si nuestro\n"
	.string "líder despierta a esa cosa…$"

MtChimney_Text_TabithaPostBattle:
	.string "¡JEFE, rápido!\n"
	.string "¡Dale la energía del METEORITO!\p"
	.string "Hehehe…$"

MtChimney_Text_Grunt2Intro:
	.string "En el TEAM MAGMA trabajamos duro\n"
	.string "por el bien de todos.\p"
	.string "Si el poder de esa cosa crea más\n"
	.string "tierra, habrá más sitios donde vivir.\p"
	.string "¡Todos serían felices!$"

MtChimney_Text_Grunt2Defeat:
	.string "¿Eh?\n"
	.string "¿Cómo que perdí?$"

MtChimney_Text_Grunt2PostBattle:
	.string "Nuestro JEFE dice: “Todos serán\n"
	.string "felices”.\p"
	.string "¿Pero por qué todos se interponen\n"
	.string "en nuestro camino?$"

MtChimney_Text_Grunt1Intro:
	.string "¡Si hubiera más tierra, tendría\n"
	.string "mi propia casa grande!\p"
	.string "¡La construiré sobre lava sólida!$"

MtChimney_Text_Grunt1Defeat:
	.string "Mi sueño de una casa grande…$"

MtChimney_Text_Grunt1PostBattle:
	.string "¡Un chico como tú debería estar\n"
	.string "jugando entre las olas!$"

MtChimney_Text_TeamAquaAlwaysMessingWithPlans:
	.string "El molesto TEAM AQUA…\n"
	.string "¡Siempre arruinan nuestros planes!$"

MtChimney_Text_MeteoritesPackAmazingPower:
	.string "¡Los METEORITOS tienen gran poder!$"

MtChimney_Text_YouBetterNotMessWithUs:
	.string "¡Mejor no te metas con nosotros!\p"
	.string "¡Despertaremos a esa cosa por el\n"
	.string "bien de todos!$"

MtChimney_Text_AquasNameSimilar:
	.string "¡Somos el TEAM MAGMA!\p"
	.string "¡Ellos son el TEAM AQUA!\p"
	.string "¡Me molesta que usen un nombre\n"
	.string "parecido al nuestro!$"

MtChimney_Text_DouseThemInFire:
	.string "¡Sí!\n"
	.string "¡Quémalos a todos!$"

MtChimney_Text_KeepMakingMoreLand:
	.string "¡Seguiremos creando más tierra!$"

MtChimney_Text_Bufoh:
	.string "¡Bufoh!$"

MtChimney_Text_ArchieGoStopTeamMagma:
	.string "ARCHIE: ¡Grr, {PLAYER}!\n"
	.string "¡Sabía que aparecerías!\p"
	.string "¡Mira lo que planean los fanáticos\n"
	.string "del TEAM MAGMA!\p"
	.string "¡Quieren inyectar el poder del\n"
	.string "METEORITO robado al volcán!\p"
	.string "¡Eso provocará la erupción\n"
	.string "del volcán!$"

MtChimney_Text_ArchieIHaveMyHandsFull:
	.string "ARCHIE: Grrr…\p"
	.string "¡Quiero detener a MAXIE,\n"
	.string "pero no puedo!\p"
	.string "¡No mientras lucho contra tres\n"
	.string "oponentes a la vez!$"

MtChimney_Text_ArchieThankYou:
	.string "ARCHIE: {PLAYER}!\n"
	.string "¡Gracias!\p"
	.string "¡Con tu ayuda frenamos el plan\n"
	.string "destructivo del TEAM MAGMA!\p"
	.string "Pero… tú…\n"
	.string "¿De qué lado estás?\p"
	.string "Ah, no importa.\p"
	.string "Seguiremos vigilantes y\n"
	.string "perseguiremos al TEAM MAGMA.\p"
	.string "{PLAYER}, ¡nos volveremos a ver!$"

MtChimney_Text_MagmaOutnumbersUs:
	.string "Rayos… ¡el TEAM MAGMA nos supera!\n"
	.string "¡No podemos contra ellos!$"

MtChimney_Text_LessHabitatForWaterPokemon:
	.string "Si expanden la tierra, ¡habrá\n"
	.string "menos hábitats para POKéMON AGUA!$"

MtChimney_Text_MagmasNameSimilar:
	.string "¡Somos el TEAM AQUA!\p"
	.string "¡Ellos son el TEAM MAGMA!\p"
	.string "¡Me enfurece que usen un nombre\n"
	.string "tan confuso!$"

MtChimney_Text_Bushaa:
	.string "¡Bushaa!$"

MtChimney_Text_LavaCookiesJust200:
	.string "Las GALLETAS DE LAVA son la especial\n"
	.string "local del MT. CHIMNEY.\p"
	.string "Prueba una. Solo cuestan ¥200.$"

MtChimney_Text_ThankYouDear:
	.string "¡Gracias, cielo!$"

MtChimney_Text_YouveNotGotTheMoney:
	.string "Vaya. No puedes comprar nada si\n"
	.string "no tienes el dinero.$"

MtChimney_Text_OhFineThen:
	.string "Está bien entonces.$"

MtChimney_Text_MetoriteFittedOnMachine:
	.string "Un METEORITO está puesto en una\n"
	.string "máquina misteriosa...\p"
	.string "La máquina parece guardar energía\n"
	.string "en el METEORITO.$"

MtChimney_Text_RemoveTheMeteorite:
	.string "Un METEORITO está en una máquina\n"
	.string "misteriosa…\p"
	.string "¿Quieres quitar el METEORITO?$"

MtChimney_Text_PlayerRemovedMeteorite:
	.string "{PLAYER} quitó el METEORITO de la\n"
	.string "máquina misteriosa.$"

MtChimney_Text_PlayerLeftMeteorite:
	.string "{PLAYER} dejó el METEORITO donde\n"
	.string "estaba.$"

MtChimney_Text_MachineMakesNoResponse:
	.string "Esta máquina misteriosa…\n"
	.string "No da respuesta alguna.$"

MtChimney_Text_RouteSign:
	.string "{DOWN_ARROW} CAMINO ROCOSO\n"
	.string "PUEBLO LAVARIDGE ADELANTE$"

MtChimney_Text_ShelbyIntro:
	.string "Fui a las aguas termales y\n"
	.string "descansé mis huesos.\l"
	.string "¡Ahora me siento fuerte!$"

MtChimney_Text_ShelbyDefeat:
	.string "Cielos.\n"
	.string "¡Vaya sorpresa me das!$"

MtChimney_Text_ShelbyPostBattle:
	.string "Vaya, he perdido. Ya no puedo\n"
	.string "llamarme EXPERTO, ¿verdad?$"

MtChimney_Text_ShelbyRegister:
	.string "Gracias, niño. Fue divertido, como\n"
	.string "si luchara con mi propio nieto.\p"
	.string "Por favor, vuelve a visitarme para\n"
	.string "una revancha.$"

MtChimney_Text_ShelbyRematchIntro:
	.string "Si unes tu corazón con el de tus\n"
	.string "POKéMON, podrás lograr\l"
	.string "grandes cosas.$"

MtChimney_Text_ShelbyRematchDefeat:
	.string "¡Cielos!\n"
	.string "¡Vaya que eres sorprendente!$"

MtChimney_Text_ShelbyPostRematch:
	.string "Tal vez tu corazón se ha vuelto uno\n"
	.string "con el de tus POKéMON.$"

MtChimney_Text_MelissaIntro:
	.string "Tengo el fuego interno, nene.\n"
	.string "¡No aguanto más! ¡Tengo que luchar!$"

MtChimney_Text_MelissaDefeat:
	.string "¡Uff, fue un combate ardiente!$"

MtChimney_Text_MelissaPostBattle:
	.string "¡El calor del MT. CHIMNEY me\n"
	.string "da energía, nene!$"

MtChimney_Text_SheilaIntro:
	.string "Al fin llegué al MT. CHIMNEY.\n"
	.string "¡Quiero que mis POKéMON luchen!$"

MtChimney_Text_SheilaDefeat:
	.string "Tu forma de luchar...\n"
	.string "¡Es como una erupción del MT. CHIMNEY!$"

MtChimney_Text_SheilaPostBattle:
	.string "Como dije, al fin llegué al\n"
	.string "MT. CHIMNEY. Sería una pena si\l"
	.string "solo vengo a pasear...\p"
	.string "Quiero luchar y comprar algunas\n"
	.string "GALLETAS de recuerdo.$"

MtChimney_Text_ShirleyIntro:
	.string "Desde que me bañé en las aguas\n"
	.string "termales, ¡me siento genial!\l"
	.string "¡Seguro que voy a ganar!$"

MtChimney_Text_ShirleyDefeat:
	.string "¡Ay!\n"
	.string "El agua me está dando escalofríos.$"

MtChimney_Text_ShirleyPostBattle:
	.string "Tendré que bañarme otra vez en las\n"
	.string "aguas termales. ¿Vienes?\p"
	.string "¡Es broma!$"

MtChimney_Text_SawyerIntro:
	.string "¡Qué montaña tan linda! ¡Hay mucha\n"
	.string "gente ardiente para acompañarme!$"

MtChimney_Text_SawyerDefeat:
	.string "¡Oh, tú también eres muy fogoso!$"

MtChimney_Text_SawyerPostBattle:
	.string "¡Creo que necesito un baño en las\n"
	.string "AGUAS DE LAVARIDGE con los locales!$"

MtChimney_Text_SawyerRegister:
	.string "Me gustan las bolitas de fuego.\n"
	.string "¡Te registraré en mi POKéNAV!$"

MtChimney_Text_SawyerRematchIntro:
	.string "Estoy rodeado de gente ardiente\n"
	.string "por aquí. ¡No perderé!$"

MtChimney_Text_SawyerRematchDefeat:
	.string "¡Cielos, sigues siendo el mismo\n"
	.string "ardiente de siempre!$"

MtChimney_Text_SawyerPostRematch:
	.string "En serio, hace calor aquí.\n"
	.string "Llevo demasiada ropa para esto.$"

