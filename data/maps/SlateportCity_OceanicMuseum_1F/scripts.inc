.set LOCALID_FAMILIAR_GRUNT, 13

SlateportCity_OceanicMuseum_1F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_1F_EventScript_EntranceAttendant::
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeRight::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee::
	showmoneybox 0, 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee
	closemessage
	hidemoneybox
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee::
	checkmoney 50
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 50
	updatemoneybox
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney::
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway
	msgbox SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt5::
	msgbox SlateportCity_OceanicMuseum_1F_Text_RustboroBungled, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt6::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_WhirlpoolExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_WaterfallExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanSoilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_BeachSandDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_FossilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_FossilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_DepthMeasuringMachine::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGrunt::
	lock
	faceplayer
	delay 8
	playse SE_PIN
	applymovement LOCALID_FAMILIAR_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FAMILIAR_GRUNT, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_THIEF
	goto_if_eq VAR_RESULT, 0, SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief
	setflag FLAG_RECEIVED_TM_THIEF
	msgbox SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth
	goto_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth
	goto_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	goto_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth
	applymovement LOCALID_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth::
	applymovement LOCALID_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast
	applymovement LOCALID_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited::
	setflag FLAG_ITEM_GARBAGEFLAG
	playse SE_EXIT
	removeobject LOCALID_FAMILIAR_GRUNT
	release
	end

SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief::
	msgbox SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis, MSGBOX_DEFAULT
	release
	end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast:
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit:
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter:
	.string "Bienvenido al MUSEO OCEÁNICO.\p"
	.string "La entrada cuesta ¥50.\n"
	.string "¿Quieres entrar?$"

SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself:
	.string "Por favor, disfruta tu visita.$"

SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney:
	.string "¿Oh? Lo siento, pero parece que no\n"
	.string "tienes suficiente dinero.$"

SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup:
	.string "¿Oh? ¿Vienes con el grupo que\n"
	.string "entró hace un momento?\p"
	.string "Eres el único que llega tarde.\n"
	.string "¡Ve rápido a alcanzarlos!$"

SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll:
	.string "¡Nosotros, el TEAM AQUA, existimos\n"
	.string "por el bien de todos!$"

SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere:
	.string "Nos dijeron que nos reuniéramos\n"
	.string "aquí, y lo hicimos, pero...\p"
	.string "Nuestro JEFE, la pieza clave, no está.$"

SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich:
	.string "Si robara las cosas de aquí,\n"
	.string "¿me haría rico?$"

SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds:
	.string "Lo que aprenda aquí, podré usarlo\n"
	.string "en actos nefarios...$"

SlateportCity_OceanicMuseum_1F_Text_RustboroBungled:
	.string "¡Si mis secuaces no hubieran fallado\n"
	.string "en FUNDAQUA, no estaríamos aquí!$"

SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney:
	.string "No tenía ¥50, así que tardé mucho\n"
	.string "en pasar la recepción.$"

SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling:
	.string "Quiero aprender sobre el mar y usar\n"
	.string "ese saber para combatir.$"

SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel:
	.string "¡Me emociono mucho cuando\n"
	.string "veo el mar!\p"
	.string "¡Para mí, CAPT. STERN es el mejor\n"
	.string "ejemplo a seguir!$"

SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow:
	.string "El mar es vasto y sin final, y\n"
	.string "está infinitamente profundo...\p"
	.string "Debe haber muchos POKéMON que\n"
	.string "no conocemos.$"

SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon:
	.string "Quiero un POKéMON marino.\p"
	.string "Creo que se sentiría genial y rico\n"
	.string "al abrazarlo.$"

SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis:
	.string "¡Aiyeeeh!\n"
	.string "¿Qué haces aquí?\p"
	.string "¿Yo? Soy el miembro del TEAM AQUA\n"
	.string "que venciste antes, ¿recuerdas?\l"
	.string "¿En el TÚNEL RUSTURF?\p"
	.string "¡Toma esto!\n"
	.string "¡Tienes que perdonarme!$"

SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain:
	.string "Esa MT te queda mejor a ti\n"
	.string "que a mí.\p"
	.string "¡Espero no verte nunca más!\n"
	.string "¡Jajajaja!$"

SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis:
	.string "¡Ay, vamos!\n"
	.string "¡Toma esto y déjame ir!$"

SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment:
	.string "Un fluido azul gira dentro de\n"
	.string "un recipiente de vidrio.\p"
	.string "“Es un experimento para crear un\n"
	.string "REMOLINO artificial con viento.”$"

SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment:
	.string "Una bola roja flota arriba y abajo\n"
	.string "en un recipiente de vidrio.\p"
	.string "“Es un experimento que simula una\n"
	.string "CASCADA usando la flotabilidad.”$"

SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay:
	.string "Es una muestra de suelo del fondo\n"
	.string "del océano.\p"
	.string "“Por años, restos de seres vivos\n"
	.string "caen al fondo del mar, creando\l"
	.string "capas sedimentarias.\p"
	.string "“Al analizar estas capas, se\n"
	.string "revela el pasado antiguo.”$"

SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay:
	.string "Es una muestra de arena de playa.\p"
	.string "“Piedras de montañas bajan por\n"
	.string "ríos, donde se rompen y se\l"
	.string "desgastan.\p"
	.string "“Se reducen a granos y terminan\n"
	.string "siendo arena en las playas.”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1:
	.string "“DATO MARINO 1\n"
	.string "¿Por qué el mar es azul?\p"
	.string "”La luz tiene muchos colores.\p"
	.string "“Cuando la luz pasa por el agua,\n"
	.string "la mayoría pierde su color.\p"
	.string "”Pero la luz azul mantiene el suyo,\n"
	.string "haciendo que el mar se vea azul.“$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2:
	.string "“DATO MARINO 2\n"
	.string "¿Por qué el mar es salado?\p"
	.string "”El agua tiene sal disuelta en forma\n"
	.string "de iones de sodio y cloro.\p"
	.string "“Estos iones salen de las rocas\n"
	.string "y la lluvia los lleva al mar.\p"
	.string "”Esa concentración de sal disuelta\n"
	.string "hace que el mar sea salado.“$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3:
	.string "“DATO MARINO 3\n"
	.string "¿Qué es más grande? ¿Mar o tierra?\p"
	.string "”El mar cubre el 70% del planeta,\n"
	.string "y el resto es tierra.\p"
	.string "“Por eso, el mar es más del doble\n"
	.string "del tamaño de la tierra.”$"

SlateportCity_OceanicMuseum_1F_Text_FossilDisplay:
	.string "Es un fósil con crestas onduladas.\p"
	.string "“El suelo marino es erosionado\n"
	.string "por la marea.\p"
	.string "“El agua marca el suelo con pequeñas\n"
	.string "crestas y valles.\p"
	.string "“Si este suelo se fosiliza, se\n"
	.string "llama marca de rizo.”$"

SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine:
	.string "Una máquina gira bajo una cúpula\n"
	.string "de cristal.\p"
	.string "Tal vez sirve para medir la\n"
	.string "profundidad de algo…$"

