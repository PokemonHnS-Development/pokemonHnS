.set LOCALID_GREETER, 1
.set LOCALID_GUIDE, 2
.set LOCALID_SCOTT, 4

BattleFrontier_ReceptionGate_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition
	.byte 0

BattleFrontier_ReceptionGate_OnTransition:
	setflag FLAG_VISITED_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame:
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering
	.2byte 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering::
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_GREETER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene::
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_GUIDE, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott
	applymovement LOCALID_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott
	applymovement LOCALID_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter:
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

@ Unused
BattleFrontier_ReceptionGate_Movement_WalkDown:
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FacilityGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFacilities, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower::
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome::
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena::
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory::
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall::
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner::
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_RulesGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToRules, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode::
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_Level50::
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel::
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry::
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems::
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	end

BattleFrontier_ReceptionGate_EventScript_Symbols::
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle::
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay:
	.string "¿Es tu primera vez aquí?\n"
	.string "¡Por aquí, por favor!$"

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier:
	.string "¡La vanguardia del combate POKéMON!\n"
	.string "¡Bienvenido al FRENTE DE BATALLA!$"

BattleFrontier_ReceptionGate_Text_IssueFrontierPass:
	.string "A los nuevos visitantes les damos\n"
	.string "el FRONTIER PASS.\p"
	.string "Sirve para todas las instalaciones\n"
	.string "del BATTLE FRONTIER.\p"
	.string "¡Aquí tienes!$"

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass:
	.string "{PLAYER} obtuvo el\n"
	.string "FRONTIER PASS.$"

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass:
	.string "{PLAYER} puso su TARJETA DE ENTRENADOR\n"
	.string "en el FRONTIER PASS.$"

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier:
	.string "¡Esperamos que disfrutes todo lo que\n"
	.string "el BATTLE FRONTIER ofrece!$"

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame:
	.string "???: Vaya, ¿quién tenemos aquí?\n"
	.string "¿Un entrenador nuevo, eh?$"

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay:
	.string "GUÍA: ¡Oh! ¡Sr. SCOTT!\n"
	.string "¡Buen día tenga usted, señor!$"

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere:
	.string "Me llamo SCOTT. Siempre busco a\n"
	.string "entrenadores con talento.\p"
	.string "¡Y tú pareces tenerlo!\n"
	.string "¿Me dices tu nombre?\p"
	.string "¡Ah, así que eres {PLAYER}{KUN}!\p"
	.string "¿Viniste desde JOHTO?\n"
	.string "¡Vaya viaje has hecho!\p"
	.string "Es genial verte por aquí,\n"
	.string "¡de verdad!\p"
	.string "Espero que te tomes tu tiempo y\n"
	.string "explores todo el lugar.\p"
	.string "Y que sientas la esencia pura\n"
	.string "de las batallas.\p"
	.string "Tengo mi cuarto aquí, así que\n"
	.string "visítame si tienes tiempo.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities:
	.string "Seré tu guía por las instalaciones\n"
	.string "del BATTLE FRONTIER.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2:
	.string "¿De cuál quieres saber más?$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo:
	.string "Es la torre gigante que es el\n"
	.string "símbolo del BATTLE FRONTIER.\p"
	.string "Hay cuatro tipos de SALAS DE BATALLA\n"
	.string "para COMBATES INDIVIDUALES, DOBLES,\l"
	.string "MÚLTIPLES y LINK MÚLTIPLES.$"

BattleFrontier_ReceptionGate_Text_BattleDomeInfo:
	.string "El BATTLE DOME es el edificio\n"
	.string "con forma de huevo gigante.\p"
	.string "Aquí se celebran eventos llamados\n"
	.string "Torneos de Batalla.\p"
	.string "Hay dos modalidades: para COMBATES\n"
	.string "INDIVIDUALES y DOBLES.\l"
	.string "$"

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo:
	.string "El BATTLE PALACE es el edificio rojo\n"
	.string "a la derecha del BATTLE FRONTIER.\p"
	.string "Hay dos tipos de SALAS DE BATALLA\n"
	.string "para COMBATES INDIVIDUALES y DOBLES.$"

BattleFrontier_ReceptionGate_Text_BattleArenaInfo:
	.string "El BATTLE ARENA es el edificio tipo\n"
	.string "dojo al centro-derecha del\l"
	.string "BATTLE FRONTIER.\p"
	.string "Allí se celebra un evento llamado\n"
	.string "Torneo de KO Fijo.$"

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo:
	.string "La BATTLE FACTORY es el edificio\n"
	.string "grande que está más cerca.\p"
	.string "Allí se lleva a cabo un evento\n"
	.string "llamado Battle Swap.\p"
	.string "El Battle Swap ofrece dos cursos\n"
	.string "para COMBATES INDIVIDUALES y\l"
	.string "DOBLES.$"

BattleFrontier_ReceptionGate_Text_BattlePikeInfo:
	.string "El BATTLE PIKE es el edificio con\n"
	.string "forma de POKéMON al centro-izq. de\l"
	.string "la BATTLE FRONTIER.\p"
	.string "Allí se realiza el evento llamado\n"
	.string "Battle Choice.$"

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo:
	.string "La BATTLE PYRAMID es la enorme\n"
	.string "pirámide.\p"
	.string "Allí se realiza el evento llamado\n"
	.string "Battle Quest.$"

BattleFrontier_ReceptionGate_Text_RankingHallInfo:
	.string "El RANKING HALL está cerca de la\n"
	.string "BATTLE TOWER.\p"
	.string "Allí verás los récords más increíbles\n"
	.string "de los TRAINERS que aceptaron los\l"
	.string "retos de la BATTLE FRONTIER.\l"
	.string "$"

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo:
	.string "El EXCHANGE SERVICE CORNER está\n"
	.string "cerca de la BATTLE TOWER.\p"
	.string "Los Puntos de Batalla ganados en la\n"
	.string "BATTLE FRONTIER se canjean por\l"
	.string "premios fabulosos allí.$"

BattleFrontier_ReceptionGate_Text_YourGuideToRules:
	.string "Soy tu guía de las reglas básicas\n"
	.string "comunes a todos los desafíos\l"
	.string "de las instalaciones de la\l"
	.string "BATTLE FRONTIER.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhat:
	.string "¿Sobre qué quieres aprender?$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo:
	.string "Los retos de la BATTLE FRONTIER\n"
	.string "tienen dos niveles:\l"
	.string "NORMAL y DIFÍCIL.$"

BattleFrontier_ReceptionGate_Text_Level50Info:
	.string "¡El curso NORMAL ya está abierto!\n"
	.string "Los POKéMON serán nivel 50.\p"
	.string "Es el nivel de entrada para las\n"
	.string "luchas de la BATTLE FRONTIER.\p"
	.string "Para empezar, esperamos que\n"
	.string "superes este curso.$"

BattleFrontier_ReceptionGate_Text_OpenLevelInfo:
	.string "¡El curso DIFÍCIL ya abrió!\n"
	.string "Todo POKéMON será Lv. 50.\p"
	.string "Este curso es un reto mayor\n"
	.string "para ENTRENADORES expertos.\p"
	.string "¡Entra en este curso si buscas\n"
	.string "un verdadero desafío!$"

BattleFrontier_ReceptionGate_Text_MonEntryInfo:
	.string "Casi cualquier POKéMON puede ir a\n"
	.string "los retos de las instalaciones.\p"
	.string "HUEVOS y ciertos POKéMON,\n"
	.string "sin embargo, no están permitidos.\p"
	.string "El número de POKéMON requeridos\n"
	.string "dependerá de la instalación.\p"
	.string "No se permiten dos o más POKéMON\n"
	.string "de la misma especie en ningún\l"
	.string "lugar.$"

BattleFrontier_ReceptionGate_Text_HoldItemsInfo:
	.string "En los retos de la BATTLE FRONTIER,\n"
	.string "los POKéMON no pueden llevar\l"
	.string "el mismo objeto.\p"
	.string "Asegúrate de que todo POKéMON\n"
	.string "que participe lleve un objeto\l"
	.string "diferente.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass:
	.string "Soy tu guía del FRONTIER PASS.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1:
	.string "¿Sobre qué quieres aprender?$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo:
	.string "Hay siete instalaciones en la\n"
	.string "BATTLE FRONTIER.\p"
	.string "Los ENTRENADORES reconocidos\n"
	.string "por su habilidad ganarán símbolos\l"
	.string "de cada instalación.\p"
	.string "Para ganar uno, debes vencer a\n"
	.string "varios ENTRENADORES seguidos\l"
	.string "o ganar eventos repetidamente.\p"
	.string "No es fácil ganar los símbolos.\n"
	.string "¡Te deseo mucha suerte!$"

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo:
	.string "Puedes grabar una batalla\n"
	.string "en tu FRONTIER PASS.\p"
	.string "Puedes grabar una batalla contra\n"
	.string "un amigo o amigos.\p"
	.string "O puedes grabar una batalla de la\n"
	.string "BATTLE FRONTIER, excepto\l"
	.string "las de la BATTLE PIKE o la\l"
	.string "BATTLE PYRAMID.\p"
	.string "Elige grabar tu combate\n"
	.string "al finalizar la batalla.$"

BattleFrontier_ReceptionGate_Text_BattlePointsInfo:
	.string "Los Puntos de Batalla son premios para\n"
	.string "ENTRENADORES destacados en la\l"
	.string "BATTLE FRONTIER.\p"
	.string "Puedes canjear tus Puntos de Batalla\n"
	.string "por premios en el EXCHANGE\l"
	.string "SERVICE CORNER.$"

