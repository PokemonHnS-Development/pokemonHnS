MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan::
	special Script_GetCurrentMauvilleMan
	switch VAR_RESULT
	case MAUVILLE_MAN_BARD, MauvilleCity_PokemonCenter_1F_EventScript_Bard
	case MAUVILLE_MAN_HIPSTER, MauvilleCity_PokemonCenter_1F_EventScript_Hipster
	case MAUVILLE_MAN_TRADER, MauvilleCity_PokemonCenter_1F_EventScript_Trader
	case MAUVILLE_MAN_STORYTELLER, MauvilleCity_PokemonCenter_1F_EventScript_Storyteller
	case MAUVILLE_MAN_GIDDY, MauvilleCity_PokemonCenter_1F_EventScript_Giddy
	end

@ Bard
MauvilleCity_PokemonCenter_1F_EventScript_Bard::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_PlaySong
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong
	end

MauvilleCity_PokemonCenter_1F_EventScript_PlaySong::
	setvar VAR_0x8004, 0
	special PlayBardSong
	delay 60
	special HasBardSongBeenChanged
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	end

MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics::
	setvar VAR_0x8004, EASY_CHAT_TYPE_BARD_SONG
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 1
	special PlayBardSong
	delay 60
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	special SaveBardSongLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2, MSGBOX_DEFAULT
	release
	end

@ Hipster
MauvilleCity_PokemonCenter_1F_EventScript_Hipster::
	lock
	faceplayer
	setflag FLAG_UNLOCKED_TRENDY_SAYINGS
	msgbox MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening, MSGBOX_DEFAULT
	special HasHipsterTaughtWord
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord::
	special HipsterTryTeachWord
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_TeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TeachWord::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord, MSGBOX_DEFAULT
	special SetHipsterTaughtWord
	release
	end

@ Trader
MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor:
	.string "Hola, soy el COMERCIANTE.\n"
	.string "¿Quieres cambiar adornos conmigo?$"

MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues:
	.string "Oh...\n"
	.string "Me has dejado muy triste...$"

MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded:
	.string "Pero ya hemos intercambiado adornos,\n"
	.string "tú y yo.$"

MauvilleCity_PokemonCenter_1F_Text_PickADecorItem:
	.string "Si ves algún adorno mío que quieras,\n"
	.string "dímelo.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything:
	.string "¿No quieres nada?\n"
	.string "Me siento rechazado...$"

MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt:
	.string "Ese adorno perteneció alguna vez a\n"
	.string "{STR_VAR_1}.\p"
	.string "¿Lo quieres?$"

MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor:
	.string "Eh... Espera. ¡No tienes ni un solo\n"
	.string "adorno contigo!$"

MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade:
	.string "Bien, elige el adorno que me vas a\n"
	.string "dar en el intercambio.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade:
	.string "¿No quieres cambiar conmigo?\n"
	.string "Me siento rechazado…$"

MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis:
	.string "Tienes todos los {STR_VAR_2} que\n"
	.string "caben. No tienes espacio.$"

MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor:
	.string "Bien, ¿cambiamos mi {STR_VAR_3}\n"
	.string "por tu {STR_VAR_2}?$"

MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse:
	.string "Ese adorno está en uso.\n"
	.string "No puedes cambiarlo.$"

MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC:
	.string "¡Entonces cambiemos!\n"
	.string "Enviaré mi adorno a tu PC.$"

MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne:
	.string "¡Ups! ¡Perdón! Es un adorno\n"
	.string "muy raro.\l"
	.string "¡No puedo darlo!\p"
	.string "¿Te interesa otra cosa?$"

MauvilleCity_PokemonCenter_1F_EventScript_Trader::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade
	special GetTraderTradedFlag
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade::
	msgbox MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive::
	special TraderMenuGetDecoration
	waitstate
	goto_if_eq VAR_0x8004, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor
	goto_if_eq VAR_0x8004, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor
	special DoesPlayerHaveNoDecorations
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor::
	message MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor::
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive::
	msgbox MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade, MSGBOX_DEFAULT
	special TraderShowDecorationMenu
	waitstate
	goto_if_eq VAR_0x8006, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor
	goto_if_eq VAR_0x8006, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse
	special IsDecorationCategoryFull
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	special TraderDoDecorationTrade
	msgbox MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis, MSGBOX_DEFAULT
	release
	end

@ Storyteller
MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale:
	.string "Soy el NARRADOR.\n"
	.string "Te contaré historias de\l"
	.string "ENTRENADORES legendarios.\p"
	.string "¿Quieres oír mi historia?$"

MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues:
	.string "Oh…\n"
	.string "Me has dejado muy triste…$"

MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell:
	.string "Conozco esas leyendas.\n"
	.string "¿Qué historia quieres que cuente?$"

MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales:
	.string "Pero no conozco ENTRENADORES\n"
	.string "legendarios.\p"
	.string "¿Dónde se halla un ENTRENADOR\n"
	.string "digno de una leyenda?$"

MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes:
	.string "¿Qué es eso?\n"
	.string "Tú... Tú...\p"
	.string "{STR_VAR_2}\n"
	.string "¿{STR_VAR_1} vez(es)?!\p"
	.string "¡Eso es magnífico!\n"
	.string "¡Nace una nueva leyenda!$"

MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends:
	.string "Me hace pensar, ¿podría haber\n"
	.string "otros ENTRENADORES con leyendas\l"
	.string "más increíbles por descubrir?$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales:
	.string "¿Eres un ENTRENADOR?\p"
	.string "Dime, ¿tienes alguna historia que\n"
	.string "sea remotamente legendaria?$"

@ Unused
MauvilleCity_PokemonCenter_1F_Text_HearAnotherLegendaryTale:
	.string "Por cierto... ¿Quieres escuchar\n"
	.string "otra historia legendaria?$"

MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend:
	.string "Hmm…\n"
	.string "No estoy satisfecho…\p"
	.string "Quisiera que me traigas noticias\n"
	.string "dignas de ser una leyenda.$"

MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested:
	.string "Desearía que más gente se interesara\n"
	.string "en oír mis épicas historias de\l"
	.string "ENTRENADORES legendarios.$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameTitle::
	.string "El ENTRENADOR precavido$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameAction::
	.string "Guardó la partida$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR guardó la partida\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡Jamás hallarás a alguien tan\n"
	.string "cauteloso como {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedTitle::
	.string "El ENTRENADOR vanguardista$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedAction::
	.string "Creó tendencias$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR creó tendencias\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} marca la moda en toda\n"
	.string "la región de HOENN!$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedTitle::
	.string "El ENTRENADOR cultivador$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedAction::
	.string "Plantó BAYAS$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR plantó BAYAS\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un amante legendario\n"
	.string "de las BAYAS!$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesTitle::
	.string "El ENTRENADOR amante de la BICI$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesAction::
	.string "Intercambió BICICLETAS$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR cambió BICIS\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe amar las BICIS\n"
	.string "con mucha pasión!$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsTitle::
	.string "El ENTRENADOR entrevistado$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsAction::
	.string "Fue entrevistado$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR fue entrevistado\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un ENTRENADOR\n"
	.string "que atrae mucha atención!$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesTitle::
	.string "El ENTRENADOR feliz de luchar$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesAction::
	.string "Combatió$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesStory::
	.string "Esta es la historia de un TRAINER\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este TRAINER luchó {STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un TRAINER que\n"
	.string "¡jamás rechaza una batalla!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtTitle::
	.string "El ENTRENADOR capturador$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtAction::
	.string "POKéMON capturados$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtStory::
	.string "Esta es la historia de un\n"
	.string "ENTRENADOR llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR capturó\n"
	.string "{STR_VAR_1} POKéMON!\p"
	.string "{STR_VAR_3} es un capturador\n"
	.string "legendario de POKéMON salvajes!$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtTitle::
	.string "El ENTRENADOR pescador$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtAction::
	.string "POKéMON capturados con CAÑA$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtStory::
	.string "Esta es la historia de un\n"
	.string "ENTRENADOR llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR capturó\n"
	.string "{STR_VAR_1} POKéMON pescando!\p"
	.string "{STR_VAR_3} es un experto\n"
	.string "legendario en la pesca!$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedTitle::
	.string "El ENTRENADOR que cuida HUEVOS$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedAction::
	.string "HUEVOS eclosionados$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR eclosionó {STR_VAR_1}\n"
	.string "POKéMON de HUEVOS!\p"
	.string "{STR_VAR_3} es un experto legendario\n"
	.string "en cuidar HUEVOS!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedTitle::
	.string "El ENTRENADOR Evolucionador$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedAction::
	.string "POKéMON evolucionados$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedStory::
	.string "Esta es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR hizo {STR_VAR_1}\n"
	.string "POKéMON evolucionar!\p"
	.string "{STR_VAR_3} es el gran evolucionador\n"
	.string "de POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterTitle::
	.string "El ENTRENADOR fan del CENTRO POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterAction::
	.string "CENTROS POKéMON usados$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterStory::
	.string "Es la historia de un TRAINER\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este TRAINER curó POKéMON\n"
	.string "{STR_VAR_1} veces en CENTROS POKéMON!\p"
	.string "¡Nadie ama más los CENTROS POKéMON\n"
	.string "que {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeTitle::
	.string "El ENTRENADOR hogareño$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeAction::
	.string "Descansó POKéMON en casa$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeStory::
	.string "Es la historia de un TRAINER\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este TRAINER curó POKéMON\n"
	.string "{STR_VAR_1} veces en casa!\p"
	.string "¡Nadie es más hogareño\n"
	.string "que {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesTitle::
	.string "El ENTRENADOR fan del SAFARI$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesAction::
	.string "Entró en la ZONA SAFARI$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesStory::
	.string "Es la historia de un TRAINER\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este TRAINER entró a la SAFARI ZONE\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡El lado salvaje de {STR_VAR_3}\n"
	.string "sale en la SAFARI ZONE!$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutTitle::
	.string "El ENTRENADOR fan de CUT$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutAction::
	.string "Usó CORTE$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR usó CORTE\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un ENTRENADOR que\n"
	.string "¡ama usar CORTE!$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashTitle::
	.string "El ENTRENADOR ROMPEROCAS$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashAction::
	.string "Rompió rocas$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR usó ROMPEROCAS\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un ENTRENADOR que\n"
	.string "¡no deja piedra sin romper!$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesTitle::
	.string "El ENTRENADOR AMANTE DE MOVER$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesAction::
	.string "Movió la BASE SECRETA$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Movió la BASE SECRETA\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un ENTRENADOR que\n"
	.string "¡ama mudarse a menudo!$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashTitle::
	.string "El ENTRENADOR feliz de SALPICAR$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashAction::
	.string "Usó SALPICAR$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR usó SALPICAR\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un ENTRENADOR que\n"
	.string "¡ama andar salpicando!$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleTitle::
	.string "El ENTRENADOR tenaz$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleAction::
	.string "Tuvo que usar ESFUERZO$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR tuvo que usar\n"
	.string "ESFUERZO {STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un ENTRENADOR tenaz\n"
	.string "¡que jamás se rinde!$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsTitle::
	.string "El campeón de las TRAGAPERRAS$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsAction::
	.string "Ganó el premio en las TRAGAPERRAS$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR ganó el premio\n"
	.string "en SLOTS {STR_VAR_1} veces.\p"
	.string "{STR_VAR_3} es un ENTRENADOR que\n"
	.string "tuvo suerte en los SLOTS!$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsTitle::
	.string "El Campeón de la RULETA$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsAction::
	.string "Tuvo victorias seguidas en RULETA de$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR ganó en RULETA\n"
	.string "{STR_VAR_1} veces seguidas.\p"
	.string "{STR_VAR_3} tuvo suerte con la bola\n"
	.string "en la RULETA!$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesTitle::
	.string "El Retador de la BATTLE TOWER$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesAction::
	.string "Aceptó el reto de la BATTLE TOWER$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR retó a la BATTLE\n"
	.string "TOWER {STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un ENTRENADOR que\n"
	.string "busca la excelencia en BATTLE TOWER!$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksTitle::
	.string "El ENTRENADOR que ama las mezclas$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksAction::
	.string "Hizo {POKEBLOCK}S$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR hizo {POKEBLOCK}S\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡Nadie usa mejor la LICUADORA\n"
	.string "de BAYAS que {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsTitle::
	.string "ENTRENADOR amante de CONCURSOS$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsAction::
	.string "Participó en CONCURSOS$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR participó en\n"
	.string "CONCURSOS {STR_VAR_1} veces!\p"
	.string "¡A {STR_VAR_3} le debe encantar lucir\n"
	.string "sus POKéMON ante todos!$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsTitle::
	.string "El Maestro de CONCURSOS$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsAction::
	.string "Ganó CONCURSOS$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR ganó CONCURSOS\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe ser un maestro\n"
	.string "increíble de CONCURSOS!$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedTitle::
	.string "El Comprador Feliz$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedAction::
	.string "Compró$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR compró objetos\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser de esas\n"
	.string "personas que nacieron para comprar.$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderTitle::
	.string "El ENTRENADOR Buscador$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderAction::
	.string "Usó un ITEMFINDER$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR usó un ITEMFINDER\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe amar buscar\n"
	.string "objetos ocultos en el suelo!$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedTitle::
	.string "El ENTRENADOR Empapado$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedAction::
	.string "Se mojó con la lluvia$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR se mojó con la\n"
	.string "lluvia {STR_VAR_1} veces!\p"
	.string "¡El carisma de {STR_VAR_3} hasta\n"
	.string "atrae la lluvia!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexTitle::
	.string "El ávido lector de POKéDEX$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexAction::
	.string "Consultó una POKéDEX$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR consultó la\n"
	.string "POKéDEX {STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe amar ver sus\n"
	.string "POKéMON en la POKéDEX!$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsTitle::
	.string "El coleccionista de CINTAS$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsAction::
	.string "Recibió CINTAS$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR recibió CINTAS\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe ser un ENTRENADOR\n"
	.string "que ama coleccionar CINTAS!$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedTitle::
	.string "El ENTRENADOR saltarrocas$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedAction::
	.string "Saltó desde salientes$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR saltó desde\n"
	.string "salientes {STR_VAR_1} veces!\p"
	.string "Si hay un saliente para saltar,\n"
	.string "¡{STR_VAR_3} no puede ignorarlo!$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedTitle::
	.string "El Legendario Espectador de TV$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedAction::
	.string "Vio la televisión$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR vio la TV\n"
	.string "{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} debe amar ver la TV!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockTitle::
	.string "El ENTRENADOR Puntual$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockAction::
	.string "Revisó la hora$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR revisó la hora\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un ENTRENADOR\n"
	.string "muy consciente del tiempo.$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryTitle::
	.string "El Mago de la LOTERÍA POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryAction::
	.string "LOTERÍAS POKéMON ganadas$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR ganó la LOTERÍA\n"
	.string "POKéMON {STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe tener muchos amigos\n"
	.string "para intercambiar POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareTitle::
	.string "El Entrenador del DAY CARE$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareAction::
	.string "POKéMON dejados en el DAY CARE$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Dejó POKéMON en el DAY CARE\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser alguien muy\n"
	.string "activo al criar POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarTitle::
	.string "El ENTRENADOR fan del TELEFÉRICO$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarAction::
	.string "Viajes en TELEFÉRICO$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR usó el TELEFÉRICO\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un ENTRENADOR\n"
	.string "muy activo y ocupado!$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsTitle::
	.string "ENTRENADOR amante de las termas$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsAction::
	.string "Bañado en aguas termales$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR fue a las termas\n"
	.string "{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe tener una piel\n"
	.string "suave como la de un bebé!$"


MauvilleCity_PokemonCenter_1F_EventScript_Storyteller::
	lock
	faceplayer
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, 0
	setvar VAR_0x800A, 0
	setvar VAR_0x800B, 0
	msgbox MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, StorytellerGetFreeStorySlot
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales
	message MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell
	waitmessage
	special StorytellerStoryListMenu
	waitstate
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection
	setvar VAR_0x8008, 1
	special Script_StorytellerDisplayStory
	waitmessage
	waitbuttonpress
	specialvar VAR_RESULT, StorytellerUpdateStat
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales
	goto MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale

MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection::
	goto MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	end

MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasStorytellerAlreadyRecorded
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd
	goto MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales

MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales, MSGBOX_DEFAULT
MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, Script_StorytellerInitializeRandomStat
	goto_if_eq VAR_RESULT, 1, MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale
	msgbox MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller::
	msgbox MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

@ Unused
MauvilleCity_PokemonCenter_1F_EventScript_WaitingForRecordMix::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd::
	release
	end

@ Giddy
MauvilleCity_PokemonCenter_1F_Text_HearMyStory:
	.string "¡Estoy EMOCIONADA!\n"
	.string "¡Tengo una historia genial para ti!\p"
	.string "¿Quieres escucharla?$"

MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues:
	.string "Oh...\n"
	.string "Me has dejado muy triste...$"

MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking:
	.string "Además, estaba pensando...$"

MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain:
	.string "Eso es todo, creo...\p"
	.string "¡Hablemos de nuevo!\n"
	.string "¡Adiós!$"

MauvilleCity_PokemonCenter_1F_EventScript_Giddy::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_HearMyStory, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	end

@ Giddy will continue to tell stories regardless of whether yes or no is selected below.
@ Each story there is a 10% chance it will be his last. Otherwise he will stop at 10 stories.
MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale::
	special GenerateGiddyLine
	special ShowFieldMessageStringVar4
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy::
	msgbox MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong:
	.string "Hola, soy el TROVADOR.\n"
	.string "¿Quieres oír mi canción?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1:
	.string "Oh...\n"
	.string "Me has dejado muy triste...$"

MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers:
	.string "Qué canción tan emotiva...\n"
	.string "Quisiera tocarla para otros...$"

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics:
	.string "¿Y bien?\n"
	.string "¿Te gusta mi canción?\p"
	.string "Pero no estoy muy feliz con\n"
	.string "la letra.\p"
	.string "¿Te gustaría escribir una\n"
	.string "letra nueva para mí?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2:
	.string "Oh...\n"
	.string "Me has dejado muy triste...$"

MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou:
	.string "¡Muchas gracias!\n"
	.string "Déjame cantarla para ti.$"

MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo:
	.string "¿Así es como querías que\n"
	.string "fuera tu canción?$"

MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile:
	.string "¡Bien! Eso es todo.\n"
	.string "Cantaré esta canción un tiempo.$"

MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening:
	.string "¡Hola! Me llaman el HIPSTER.\n"
	.string "Te enseñaré lo que está de moda.$"

MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou:
	.string "Pero ya te enseñé lo que está de\n"
	.string "moda.\p"
	.string "Quiero llevar esta buena noticia a\n"
	.string "otras personas.$"

MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach:
	.string "Pero ya sabes mucho sobre lo que\n"
	.string "está de moda.\p"
	.string "¡No tengo nada nuevo que enseñarte!$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord:
	.string "Oye, ¿has oído hablar de\n"
	.string "“{STR_VAR_1}”?\p"
	.string "¿Qué significa? Bueno...\n"
	.string "Pregúntale a tu papá o mamá, ¿sí?$"
