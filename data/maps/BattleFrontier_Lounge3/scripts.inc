BattleFrontier_Lounge3_MapScripts::
	.byte 0

	.set BET_AMOUNT_5,  5
	.set BET_AMOUNT_10, 10
	.set BET_AMOUNT_15, 15

BattleFrontier_Lounge3_EventScript_Gambler::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_GAMBLER, BattleFrontier_Lounge3_EventScript_AlreadyMetGambler
	call BattleFrontier_Lounge3_EventScript_CountSilverSymbols
	goto_if_le VAR_0x8004, 2, BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols
	setflag FLAG_MET_BATTLE_FRONTIER_GAMBLER
	msgbox BattleFrontier_Lounge3_Text_YouLookToughExplainGambling, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_AskToEnterChallenge::
	special ShowFrontierGamblerLookingMessage
	waitmessage
	waitbuttonpress
	msgbox BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	msgbox BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_ChooseBetAmount::
	multichoice 20, 4, MULTI_FRONTIER_GAMBLER_BET, FALSE
	copyvar VAR_FRONTIER_GAMBLER_AMOUNT_BET, VAR_RESULT
	switch VAR_RESULT
	case FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_Bet5
	case FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_Bet10
	case FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_Bet15
	case FRONTIER_GAMBLER_BET_CANCEL, BattleFrontier_Lounge3_EventScript_CancelBet
	case MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_CancelBet
	end

BattleFrontier_Lounge3_EventScript_Bet5::
	setvar VAR_0x8008, BET_AMOUNT_5
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet10::
	setvar VAR_0x8008, BET_AMOUNT_10
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet15::
	setvar VAR_0x8008, BET_AMOUNT_15
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_TryPlaceBet::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge3_EventScript_PlaceBet
	msgbox BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints, MSGBOX_DEFAULT
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_PlaceBet::
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_ThanksOffYouGo, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FinishBet
	end

BattleFrontier_Lounge3_EventScript_FinishBet::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_Lounge3_EventScript_CountSilverSymbols::
	setvar VAR_0x8004, 0
	call_if_set FLAG_SYS_TOWER_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_DOME_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PALACE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_ARENA_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_FACTORY_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PIKE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PYRAMID_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	return

BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount::
	addvar VAR_0x8004, 1
	return

BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols::
	msgbox BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_AlreadyMetGambler::
	msgbox BattleFrontier_Lounge3_Text_Oh, MSGBOX_DEFAULT
	goto_if_ge VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_CheckBetResults
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_CheckBetResults::
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WON, BattleFrontier_Lounge3_EventScript_WonChallenge
	goto BattleFrontier_Lounge3_EventScript_LostChallenge
	end

BattleFrontier_Lounge3_EventScript_WonChallenge::
	msgbox BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints, MSGBOX_DEFAULT
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_RewardBet5
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_RewardBet10
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_RewardBet15
	msgbox BattleFrontier_Lounge3_Text_ObtainedBattlePoints, MSGBOX_GETPOINTS
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_LostChallenge::
	msgbox BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_RewardBet5::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_5 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_5 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet10::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_10 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_10 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet15::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_15 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_15 * 2)
	return

BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge3_EventScript_DeclineChallenge::
	msgbox BattleFrontier_Lounge3_Text_NotInterested, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_CancelBet::
	special CloseBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_DeclineChallenge
	end

BattleFrontier_Lounge3_EventScript_Man::
	msgbox BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges, MSGBOX_NPC
	end

BattleFrontier_Lounge3_EventScript_Woman::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_BackedWrongTrainer, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FatMan::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_TrainerGoodButRattled, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere::
	.string "...¿Qué quieres?\p"
	.string "¿No ves que estamos ocupados?\n"
	.string "¿No puede esperar tu asunto?$"

BattleFrontier_Lounge3_Text_YouLookToughExplainGambling::
	.string "...¿Eh?\n"
	.string "Pareces un ENTRENADOR fuerte.\p"
	.string "Jeje...\n"
	.string "Escucha, tengo una propuesta.\p"
	.string "Tenemos un grupito por aquí,\n"
	.string "y jugamos a algo sobre lo que\l"
	.string "pasa en la BATTLE FRONTIER.\p"
	.string "Las reglas son muy simples.\p"
	.string "Primero, elegimos una instalación\n"
	.string "de la BATTLE FRONTIER.\p"
	.string "Luego, cada uno elige un ENTRENADOR\n"
	.string "que acepte ese desafío,\l"
	.string "y apostamos Puntos de Batalla.\p"
	.string "Quien apueste por el ENTRENADOR con\n"
	.string "mejor récord se lleva todos los\l"
	.string "Puntos de Batalla del pozo.\p"
	.string "Suena simple, ¿no?\n"
	.string "Así que, bueno...$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerSingle::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "retar las SALAS DE BATALLA INDIVIDUAL\l"
	.string "de la BATTLE TOWER.\p"
	.string "Pero no he visto a ningún ENTRENADOR\n"
	.string "con esa chispa ganadora.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerDouble::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "retar las SALAS DE BATALLA DOBLE\l"
	.string "de la BATTLE TOWER.\p"
	.string "Pero no he visto a ningún ENTRENADOR\n"
	.string "con esa chispa ganadora.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerMulti::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "retar las SALAS DE BATALLA MULTI\l"
	.string "de la BATTLE TOWER.\p"
	.string "Pero no he visto a ningún ENTRENADOR\n"
	.string "con esa chispa ganadora.$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeSingle::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "entrar al Torneo Individual\l"
	.string "del BATTLE DOME.\p"
	.string "Pero no he visto a ningún ENTRENADOR\n"
	.string "con esa chispa ganadora.$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeDouble::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "entrar al Torneo Doble\l"
	.string "del BATTLE DOME.\p"
	.string "Pero no he visto a ningún ENTRENADOR\n"
	.string "con esa chispa ganadora.$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactorySingle::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "entrar al Battle Swap Single\l"
	.string "Tourney de la BATTLE FACTORY.\p"
	.string "Pero aún no veo a un ENTRENADOR\n"
	.string "con esa calidad ganadora.$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactoryDouble::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "entrar al Torneo Doble de Intercambio\l"
	.string "de la BATTLE FACTORY.\p"
	.string "Pero aún no he visto a un ENTRENADOR\n"
	.string "con esa chispa ganadora.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceSingle::
	.string "Busco a un ENTRENADOR que\n"
	.string "desafíe las SALAS DE BATALLA\l"
	.string "INDIVIDUAL del PALACIO.\p"
	.string "Pero aún no he visto a un ENTRENADOR\n"
	.string "con esa calidad de ganador.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceDouble::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "desafiar las SALAS DE COMBATE DOBLE\l"
	.string "del BATTLE PALACE.\p"
	.string "Pero aún no he visto a un ENTRENADOR\n"
	.string "con esa chispa ganadora.$"

BattleFrontier_Lounge3_Text_ChallengeBattleArena::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "entrar al Torneo KO Fijo de la\l"
	.string "BATTLE ARENA.\p"
	.string "Pero aún no he visto a un ENTRENADOR\n"
	.string "con esa chispa ganadora.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePike::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "entrar a la Elección de Combate del\l"
	.string "BATTLE PIKE.\p"
	.string "Pero aún no he visto a un ENTRENADOR\n"
	.string "con esa chispa ganadora.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePyramid::
	.string "Busco un ENTRENADOR que vaya a\n"
	.string "entrar a la Búsqueda de Combate de la\l"
	.string "BATTLE PYRAMID.\p"
	.string "Pero aún no he visto a un ENTRENADOR\n"
	.string "con esa chispa ganadora.$"

BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe::
	.string "Haré que tú también te beneficies.\n"
	.string "¿Qué te parece?\l"
	.string "¿Entrarías en ese evento por mí?$"

BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints::
	.string "Muy bien, es perfecto.\n"
	.string "Entonces... ¿Podrías darme algunos\l"
	.string "de tus Puntos de Batalla?\p"
	.string "Confía en mí, te mostraré mi gratitud\n"
	.string "después.$"

BattleFrontier_Lounge3_Text_HowMuchCanYouSpot::
	.string "¡Genial, genial!\n"
	.string "¿Entonces, cuánto me prestarás?$"

BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints::
	.string "¡Oh, no, no, no!\n"
	.string "¡No tienes suficientes BP!\p"
	.string "¡No juegues conmigo ni\n"
	.string "pierdas el tiempo de todos!$"

BattleFrontier_Lounge3_Text_ThanksOffYouGo::
	.string "¡Jeje! ¡Muchas gracias!\n"
	.string "¡Ahora, vete ya!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerSingle::
	.string "¡Ve a las SALAS DE BATALLA INDIVIDUAL\n"
	.string "de la BATTLE TOWER pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerDouble::
	.string "¡Ve a las SALAS DE BATALLA DOBLE\n"
	.string "de la BATTLE TOWER pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerMulti::
	.string "¡Ve a las SALAS DE BATALLA MULTI\n"
	.string "de la BATTLE TOWER pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleDomeSingle::
	.string "¡Ve al TORNEO INDIVIDUAL\n"
	.string "del BATTLE DOME pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleDomeDouble::
	.string "¡Ve al TORNEO DOBLE\n"
	.string "del BATTLE DOME pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleFactorySingle::
	.string "¡Ve al Torneo Individual de la\n"
	.string "BATTLE FACTORY pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleFactoryDouble::
	.string "¡Ve al Torneo Doble de la\n"
	.string "BATTLE FACTORY pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceSingle::
	.string "¡Ve a las Salas Individuales del\n"
	.string "BATTLE PALACE pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceDouble::
	.string "¡Ve a las Salas Dobles del\n"
	.string "BATTLE PALACE pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleArena::
	.string "¡Ve al Torneo Set KO de la\n"
	.string "BATTLE ARENA pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattlePike::
	.string "¡Ve a la Battle Choice del\n"
	.string "BATTLE PIKE pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_GetToBattlePyramid::
	.string "¡Ve a la Battle Quest de la\n"
	.string "BATTLE PYRAMID pronto!\p"
	.string "¡Tienes que ganar sí o sí!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestro futuro depende de ti!$"

BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints::
	.string "Ah, eres tú...\n"
	.string "Buen intento...\p"
	.string "Siento decirte que no puedo\n"
	.string "devolverte tus Puntos de Batalla...\p"
	.string "¡Que esto nos motive a esforzarnos\n"
	.string "más la próxima vez!$"

BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints::
	.string "¡Oh, sí!\n"
	.string "¡Hola, campeón!\p"
	.string "¡Sabía que podías!\n"
	.string "¡Sabía que lo harías!\l"
	.string "¡Ambos somos ganadores!\p"
	.string "Te daré tus Puntos de Batalla y,\n"
	.string "¡claro, un extra de mi parte!$"

BattleFrontier_Lounge3_Text_ObtainedBattlePoints::
	.string "{PLAYER} obtuvo\n"
	.string "{STR_VAR_1} Puntos de Batalla.$"

BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge::
	.string "Si quieres otro desafío,\n"
	.string "¡por favor, piensa en mí!$"

BattleFrontier_Lounge3_Text_NotInterested::
	.string "¡¿No te interesa?! ¡No deberías\n"
	.string "tener miedo de arriesgarte!$"

BattleFrontier_Lounge3_Text_Oh::
	.string "Oh…$"

BattleFrontier_Lounge3_Text_BackedWrongTrainer::
	.string "¡Aposté al ENTRENADOR equivocado!\p"
	.string "Tal vez debería luchar normal\n"
	.string "como todos los demás…$"

BattleFrontier_Lounge3_Text_TrainerGoodButRattled::
	.string "Ese ENTRENADOR…\p"
	.string "Es bueno, pero se pone nervioso\n"
	.string "para sobrevivir al BATTLE DOME…$"

BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne::
	.string "¡Jeje!\n"
	.string "¡Reconozco a un ganador al verlo!$"

BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges::
	.string "Esos ENTRENADORES...\n"
	.string "¿Qué están haciendo?\l"
	.string "Deberían aceptar retos.$"
