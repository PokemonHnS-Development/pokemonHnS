.set LOCALID_SS_TIDAL, 2
.set LOCALID_FERRY_ATTENDANT, 3
.set LOCALID_MANIAC_1, 9
.set LOCALID_MANIAC_2, 10
.set LOCALID_GIRL, 12
.set LOCALID_CAMPER, 14
.set LOCALID_FISHERMAN_2, 18
.set LOCALID_MAN_4, 23

BattleFrontier_OutsideWest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

BattleFrontier_OutsideWest_OnTransition:
	callnative SetTimeBasedEncounters
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	end

BattleFrontier_OutsideWest_EventScript_Sailor::
	lock
	faceplayer
	msgbox BattleFrontierOutsideWest_Text_SailorReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_AsYouLike
	msgbox EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FERRY_ATTENDANT, MAP_BATTLE_FRONTIER_OUTSIDE_WEST
	setvar VAR_0x8004, LOCALID_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	warpsilent MAP_VERMILION_CITY_PORT_INSIDE, 8, 9
	waitstate
	release
	end

BattleFrontier_OutsideWest_AsYouLike::
	msgbox EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

BattleFrontierOutsideWest_Text_SailorReturn:
	.string "¿Quieres volver a VERMILION?$"

BattleFrontier_OutsideWest_EventScript_FerryAttendant::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideWest_EventScript_NoSSTicket
	message BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination::
	multichoicedefault 18, 6, MULTI_SSTIDAL_BATTLE_FRONTIER, 2, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_OutsideWest_EventScript_FerryToSlateport
	case 1, BattleFrontier_OutsideWest_EventScript_FerryToLilycove
	case 2, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	case MULTI_B_PRESSED, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	end

BattleFrontier_OutsideWest_EventScript_NoSSTicket::
	msgbox BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToSlateport::
	msgbox BattleFrontier_OutsideWest_Text_SlateportItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToLilycove::
	msgbox BattleFrontier_OutsideWest_Text_LilycoveItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination::
	message BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_BoardFerry::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FERRY_ATTENDANT, MAP_BATTLE_FRONTIER_OUTSIDE_WEST
	setvar VAR_0x8004, LOCALID_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	return

BattleFrontier_OutsideWest_EventScript_CancelFerrySelect::
	msgbox BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign::
	msgbox BattleFrontier_OutsideWest_Text_BattleFactorySign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattlePikeSign, MSGBOX_SIGN
	end

@ Unused. Of note, Battle Tower is in the East section in the final release
BattleFrontier_OutsideWest_EventScript_UnusedNPC1::
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC2::
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1::
	msgbox BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Engineer::
	msgbox BattleFrontier_OutsideWest_Text_Reparations, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Engineer2::
	msgbox BattleFrontier_OutsideWest_Text_Reparations2, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Engineer3::
	msgbox BattleFrontier_OutsideWest_Text_Reparations3, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Engineer4::
	msgbox BattleFrontier_OutsideWest_Text_Reparations4, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere
	waitmessage
	applymovement LOCALID_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1::
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Maniac1::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_Maniac2::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk::
	applymovement LOCALID_MANIAC_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons, MSGBOX_DEFAULT
	applymovement LOCALID_MANIAC_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_MANIAC_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_MANIAC_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper::
	lock
	faceplayer
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_CamperFaceFactory::
	applymovement LOCALID_CAMPER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory::
	return

BattleFrontier_OutsideWest_EventScript_Girl::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper
	waitmessage
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_GirlShudderNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_GirlShudderSouth
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_GirlShudderWest
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_GirlShudderEast
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_GirlShudderNorth::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderSouth::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderWest::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderEast::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth:
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth:
	walk_in_place_faster_up
	walk_in_place_faster_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest:
	walk_in_place_faster_right
	walk_in_place_faster_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast:
	walk_in_place_faster_left
	walk_in_place_faster_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors, MSGBOX_DEFAULT
	random 2
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1::
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman_Milotic::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MILOTIC, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideWest_Text_Milotic, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC3::
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass::
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM::
	msgbox BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man2::
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman1::
	msgbox BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan1::
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2::
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2::
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan::
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF::
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign:
	.string "¡Es el BATTLE DOME!\n"
	.string "¡Tu camino a ser una superestrella!$"

BattleFrontier_OutsideWest_Text_BattleFactorySign:
	.string "¡Es la BATTLE FACTORY!\n"
	.string "¡Busca a los POKéMON más fuertes!$"

BattleFrontier_OutsideWest_Text_BattlePikeSign:
	.string "¡Es la BATTLE PIKE!\n"
	.string "¡Elige uno de los tres caminos!$"

BattleFrontier_OutsideWest_Text_ThisIsBattleTower:
	.string "Es la BATTLE TOWER.\p"
	.string "Los ENTRENADORES traen sus mejores\n"
	.string "POKéMON para luchar por eliminación.$"

BattleFrontier_OutsideWest_Text_MayISeeYourTicket:
	.string "Hola, ¿vienes por el ferry?\n"
	.string "¿Puedo ver tu TICKET?$"

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard:
	.string "{PLAYER} no tiene el TICKET…\p"
	.string "Lo siento muchísimo.\p"
	.string "Necesitas un TICKET para subir\n"
	.string "al ferry.$"

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo:
	.string "{PLAYER} mostró el TICKET.\p"
	.string "¡Perfecto! ¡Eso es todo!\p"
	.string "¿A dónde te gustaría ir?$"

BattleFrontier_OutsideWest_Text_SlateportItIs:
	.string "¡Entonces será CIUDAD PORTAL!$"

BattleFrontier_OutsideWest_Text_LilycoveItIs:
	.string "¡Entonces será CIUDAD VERA!$"

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime:
	.string "¡Viaja con nosotros otra vez!$"

BattleFrontier_OutsideWest_Text_PleaseBoardFerry:
	.string "Sube al ferry y espera la\n"
	.string "salida.$"

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo:
	.string "¿Entonces, a dónde quieres ir?$"

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends:
	.string "Soy el mejor de mis amigos.\n"
	.string "Pero aquí...\l"
	.string "¡no he servido para nada!$"

BattleFrontier_OutsideWest_Text_CantFindBattleTower:
	.string "Quiero ir a la BATTLE TOWER,\n"
	.string "pero no la hallo aunque tenga el\l"
	.string "mapa de BATTLE FRONTIER.\p"
	.string "¡Este lugar es muy grande!$"

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere:
	.string "Quería un reto apenas llegara\n"
	.string "aquí.\p"
	.string "Pero en el camino, me mareé...\n"
	.string "Urrrrp...$"

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere:
	.string "No es como si cualquiera pudiera\n"
	.string "venir aquí, ¿sabes?\p"
	.string "Solo traen a los ENTRENADORES que\n"
	.string "son reconocidos como fuertes.\p"
	.string "Por eso muchos ni saben que existe\n"
	.string "el BATTLE FRONTIER.$"

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons:
	.string "Oye, hermano...\p"
	.string "¿Seguro que podemos hacer retos\n"
	.string "aunque no tengamos POKéMON?$"

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons:
	.string "Eh...\n"
	.string "Seguro que todo saldrá bien.\p"
	.string "Creo...\p"
	.string "¿Recuerdas al tipo ese aterrador?\n"
	.string "Dijo: ¡Te prestaré POKéMON!$"

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons:
	.string "Esa es la BATTLE FACTORY.\n"
	.string "Ahí puedes rentar POKéMON fuertes.\p"
	.string "Pero me pregunto...\n"
	.string "¿Quién cría esos POKéMON de renta?$"

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper:
	.string "Me da miedo ir al BATTLE PIKE\n"
	.string "por culpa de SEVIPER...\p"
	.string "P-pero vine hasta aquí, ¡así que\n"
	.string "intentaré conquistarlo todo!\l"
	.string "...Tiemblo...$"

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors:
	.string "¡Juguemos piedra, papel o tijera!\n"
	.string "¡Uno, dos, tres!\p"
	.string "... ... ... ... ... ...$"

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge:
	.string "¡Sii! ¡Gané!\n"
	.string "¡Aceptaré el reto del BATTLE PIKE!$"

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge:
	.string "Oh, no...\n"
	.string "Perdí.\p"
	.string "Creo que hoy no tengo suerte.\n"
	.string "Dejaré el reto del BATTLE PIKE\l"
	.string "para mañana.$"

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling:
	.string "Creo que soy el único aquí que,\n"
	.string "por alguna razón, prefiere la\l"
	.string "pesca que luchar.\p"
	.string "¿Eh? ¿No atrapas nada aquí?\n"
	.string "Qué decepcionante…$"

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol:
	.string "Hoy seguiré luchando, pase lo\n"
	.string "que pase, ¡hasta ganar un Símbolo!$"

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome:
	.string "¿Oh? ¿Vas a desafiar el\n"
	.string "BATTLE DOME?\p"
	.string "Te deseo mucha suerte.\n"
	.string "¡Ganemos ambos para vernos en\l"
	.string "los desafíos!$"

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa:
	.string "¡Abuelo, por aquí!\n"
	.string "¡El BATTLE DOME está aquí!\l"
	.string "¡Ve por ellos, abuelo!$"

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe:
	.string "Ah, ¿así que esto es el BATTLE DOME?\n"
	.string "¡No dejaré que los GENTLEMEN ganen!\p"
	.string "¿Pero dónde está la entrada?$"

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo:
	.string "Hace no mucho tiempo no había\n"
	.string "nada aquí.\p"
	.string "¡Pero mira este lugar! ¡Increíble!\n"
	.string "Traeré a mi madre a verlo.$"

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier:
	.string "¡Al fin llegué al BATTLE\n"
	.string "FRONTIER!\p"
	.string "¡Llamaré la atención con mi\n"
	.string "aspecto y habilidad!$"

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople:
	.string "Munch, munch…\p"
	.string "Parece que esta plaza está llena\n"
	.string "de gente fuerte.\p"
	.string "Munch, munch…$"

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike:
	.string "Crunch, munch…\p"
	.string "Hace tiempo conocí a una chica\n"
	.string "en el BATTLE PIKE.\p"
	.string "Tenía unos ojos que daban miedo\n"
	.string "de una forma muy malhumorada.\p"
	.string "Crunch, munch…\p"
	.string "Se puso furiosa: “¡Deja de\n"
	.string "comer!” Y luego me golpeó.\p"
	.string "Fue una experiencia aterradora\n"
	.string "y espeluznante, la verdad.\p"
	.string "Crunch, munch…$"

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet:
	.string " ¿Eh? ¿Te escuchas a ti misma?\n"
	.string "¡Eso no es nada!\p"
	.string "¡La última vez que lo animé,\n"
	.string "nuestras miradas se cruzaron!$"

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering:
	.string "¡¿Quéééé?!\n"
	.string "¡Pfft!\p"
	.string "¡Eso pasó solo porque\n"
	.string "estaba sentado junto a ti!\p"
	.string "¡El DOME ACE nos miró porque\n"
	.string "yo gritaba muy fuerte!$"

BattleFrontier_OutsideWest_Text_DomeAceIsMine:
	.string "¡Oh, cállate!\n"
	.string "¡Deja de hacer ruido!\p"
	.string "¡Fans así deberían animar a\n"
	.string "algún LÍDER de GIMNASIO!\p"
	.string "¡El DOME ACE es mío!\n"
	.string "¡Es mi único ídolo!$"

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers:
	.string "Esa gente discutiendo allá…\p"
	.string "Cuesta creerlo, pero antes\n"
	.string "eran TRAINERS, y muy buenos.\p"
	.string "Eran increíblemente fuertes\n"
	.string "y también eran famosos.\p"
	.string "Pero un cierto TRAINER los\n"
	.string "aplastó en un torneo.\p"
	.string "Les dieron tal paliza que\n"
	.string "se enamoraron del TRAINER.\p"
	.string "Ahora solo son sus fans.\n"
	.string "Van a animar a su ídolo al\l"
	.string "BATTLE DOME todos los días.$"

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier:
	.string "¡Hace unas semanas había\n"
	.string "una cueva en el BATTLE FRONTIER!\p"
	.string "¡Había POKéMON extraños\n"
	.string "con colas inusualmente largas!\p"
	.string "Pero hace poco la cueva\n"
	.string "colapsó sin razón alguna…\p"
	.string "Me pregunto qué habrá sido\n"
	.string "de esas pobres criaturas…$"

BattleFrontier_OutsideWest_Text_Reparations:
    .string "¡Cuidado ahí!\p"
    .string "La cueva bajo el BATTLE FRONTIER\n"
    .string "colapsó hace poco.\p"
    .string "Reforzamos la estructura para que\n"
    .string "no vuelva a pasar.\p"
    .string "Hasta que terminen las obras,\n"
    .string "usa los puentes de madera.$"

BattleFrontier_OutsideWest_Text_Reparations2:
    .string "¡Mira por dónde pisas!\p"
    .string "Aún reparamos los daños del\n"
    .string "colapso de la cueva.\p"
    .string "Estos puentes de madera son\n"
    .string "temporales, ¡ten cuidado!$"

BattleFrontier_OutsideWest_Text_Reparations3:
    .string "Ugh... Otro día de reparaciones.\n"
    .string "El derrumbe dejó todo hecho un caos.\p"
    .string "Espero que los soportes aguanten\n"
    .string "hasta que terminemos el trabajo.$"

BattleFrontier_OutsideWest_Text_Reparations4:
    .string "¡Estos MACHOKE y MACHAMP ayudan\n"
    .string "mucho con las reparaciones!\p"
    .string "¡Sin ellos, reconstruir tras el\n"
    .string "derrumbe tardaría una eternidad!$"

BattleFrontier_OutsideWest_Text_Milotic:
	.string "MILOTIC: ¡Milooo!$"
