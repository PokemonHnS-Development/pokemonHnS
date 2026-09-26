.set LOCALID_DAYCARE_LADY, 1

Route34_DayCare_MapScripts::
	.byte 0

Route34_DayCare_Bookshelf1::
	msgbox Route34_DayCare_Text_Bookshelf1, MSGBOX_SIGN
	end

Route34_DayCare_Bookshelf2::
	msgbox Route34_DayCare_Text_Bookshelf2, MSGBOX_SIGN
	end

Route34_DayCare_Bookshelf3::
	msgbox Route34_DayCare_Text_Bookshelf3, MSGBOX_SIGN
	end

Route34_DayCare_Bookshelf4::
	msgbox Route34_DayCare_Text_Bookshelf4, MSGBOX_SIGN
	end

Route34_DayCare_Text_Bookshelf1:
	.string "¡Un diccionario!\p"
	.string "{PLAYER} abrió el diccionario en\n"
	.string "una página al azar.\p"
	.string "BEBÉ\n"
	.string "Sustantivo, significa infante.\p"
	.string "{PLAYER} guardó el diccionario.$"

Route34_DayCare_Text_Bookshelf2:
	.string "¡Un libro de POKéMON!\p"
	.string "{PLAYER} hojeó el\n"
	.string "libro.\p"
	.string "Debe tener la palabra\n"
	.string "POKéMON en cada página.\p"
	.string "{PLAYER} guardó el libro.$"

Route34_DayCare_Text_Bookshelf3:
	.string "¡Un libro de asociaciones!\p"
	.string "{PLAYER} hojeó el\n"
	.string "libro.\p"
	.string "PICHU -> LINDO\l"
	.string "CLEFFA -> LINDO\l"
	.string "IGGLYBUFF -> CANTO\l"
	.string "TYROGUE -> LUCHA\l"
	.string "SMOOCHUM -> HIELO\l"
	.string "ELEKID -> ELÉCTRICO\l"
	.string "MAGBY -> FUEGO\p"
	.string "{PLAYER} guardó el libro.$"

Route34_DayCare_Text_Bookshelf4:
	.string "¡Un libro de habilidades!\p"
	.string "{PLAYER} hojeó el\n"
	.string "libro.\p"
	.string "PICHU -> ESTÁTICA\l"
	.string "CLEFFA -> ATRACTIVO\l"
	.string "IGGLYBUFF -> ATRACTIVO\l"
	.string "TYROGUE -> AGALLA\l"
	.string "SMOOCHUM -> DESPISTADO\l"
	.string "ELEKID -> ESTÁTICA\l"
	.string "MAGBY -> CUERPO LLAMA\p"
	.string "{PLAYER} guardó el libro.$"

Route34_DayCare_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_ODD_EGG, Route34_DayCare_EventScript_ClerkAfter
	msgbox Route34_DayCare_Text_ClerkBefore, MSGBOX_DEFAULT
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route34_DayCare_EventScript_ClerkPartyFull
	msgbox Route34_DayCare_Text_ClerkQuestion, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_INTERVIEW
	setvar VAR_0x8005, 0
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	switch VAR_RESULT
	case 0, Route34_DayCare_EventScript_ClerkRejection
	case 1, Route34_DayCare_EventScript_GivePichu
	case 2, Route34_DayCare_EventScript_GiveCleffa
	case 3, Route34_DayCare_EventScript_GiveIgglybuff
	case 4, Route34_DayCare_EventScript_GiveTyrogue
	case 5, Route34_DayCare_EventScript_GiveSmoochum
	case 6, Route34_DayCare_EventScript_GiveElekid
	case 7, Route34_DayCare_EventScript_GiveMagby
	closemessage
	release
	end

Route34_DayCare_EventScript_GivePichu::
	giveoddegg 1
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveCleffa::
	giveoddegg 2
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveIgglybuff::
	giveoddegg 3
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveTyrogue::
	giveoddegg 4
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveSmoochum::
	giveoddegg 5
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveElekid::
	giveoddegg 6
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_GiveMagby::
	giveoddegg 7
	goto Route34_DayCare_EventScript_Clerk_GaveEgg

Route34_DayCare_EventScript_Clerk_GaveEgg::
	msgbox Route34_DayCare_Text_TakeCare, MSGBOX_DEFAULT
	closemessage
	delay 30
	setflag FLAG_RECEIVED_ODD_EGG
	playfanfare MUS_OBTAIN_ITEM
	message Route34_DayCare_Text_ReceivedOddEgg
	waitfanfare
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkPartyFull::
	msgbox Route34_DayCare_Text_ClerkNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkRejection::
	msgbox Route34_DayCare_Text_Rejection, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_EventScript_ClerkAfter::
	msgbox Route34_DayCare_Text_ClerkAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

Route34_DayCare_Text_ClerkBefore:
	.string "Soy el hijo de la GUARDERÍA.\p"
	.string "Hallaron un HUEVO EXTRAÑO con un\n"
	.string "POKéMON, pero no lo quisieron...\p"
	.string "Te lo daría...\n"
	.string "¿Pero cómo sé que lo cuidarás\l"
	.string "bien?$"

Route34_DayCare_Text_ClerkNoRoom:
	.string "Parece que no puedes llevar\n"
	.string "otro POKéMON de todos modos.$"

Route34_DayCare_Text_ClerkQuestion:
	.string "Responde esta pregunta.\n"
	.string "¿Qué piensas de este HUEVO EXTRAÑO?$"

Route34_DayCare_Text_Rejection:
	.string "Hmm, creo que este HUEVO no es tuyo.\p"
	.string "Sería irresponsable de mi parte\n"
	.string "dar un HUEVO tan precioso\l"
	.string "a alguien que no sabe tanto\l"
	.string "sobre la crianza Pokémon!$"

Route34_DayCare_Text_ReceivedOddEgg:
	.string "{PLAYER} recibió el HUEVO EXTRAÑO.$"

Route34_DayCare_Text_TakeCare:
	.string "Sabía que eras el ENTRENADOR\n"
	.string "ideal. ¡Cuídalo mucho!$"

Route34_DayCare_Text_ClerkAfter:
	.string "Vemos muchos de esos huevos por\n"
	.string "aquí.\p"
	.string "Pero aquel era diferente a los\n"
	.string "demás.$"

Route34_DayCare_EventScript_Ditto::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DITTO, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_Ditto, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route34_DayCare_Text_Ditto:
	.string "DITTO: ¡Tto!$"

Route34_EventScript_DaycareMan::
	lock
	faceplayer
	special GetDaycareMonNicknames
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_EventScript_DaycareEggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_EventScript_CheckOnOneMon
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route34_EventScript_CheckOnTwoMons
	msgbox Route34_Text_SeeWifeIfYoudLikeMeToRaiseMon, MSGBOX_DEFAULT
	release
	end

Route34_EventScript_DaycareEggWaiting::
	msgbox Route34_Text_DoYouWantEgg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_EventScript_DaycareAcceptEgg
	msgbox Route34_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_EventScript_DaycareAcceptEgg
	msgbox Route34_Text_IllKeepIt, MSGBOX_DEFAULT
	clearflag FLAG_PENDING_DAYCARE_EGG
	special RejectEggFromDayCare
	release
	end

Route34_EventScript_DaycareAcceptEgg::
	specialvar VAR_0x8004, GetMaxPartySize @ tx_randomizer_and_challenges
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_ne VAR_RESULT, VAR_0x8004, Route34_EventScript_DaycareReceiveEgg
	msgbox Route34_Text_YouHaveNoRoomForIt, MSGBOX_DEFAULT
	release
	end

Route34_EventScript_DaycareReceiveEgg::
	message Route34_Text_ReceivedEgg
	playfanfare MUS_LEVEL_UP
	waitfanfare
	waitbuttonpress
	msgbox Route34_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	special GiveEggFromDaycare
	clearflag FLAG_PENDING_DAYCARE_EGG
	release
	end

Route34_EventScript_CheckMonReceivedMail::
	specialvar VAR_RESULT, CheckDaycareMonReceivedMail
	call_if_eq VAR_RESULT, 1, Route34_EventScript_MonReceivedMail
	return

Route34_EventScript_MonReceivedMail::
	msgbox Route34_Text_FriendlyWithOtherTrainersMon, MSGBOX_DEFAULT
	return

Route34_EventScript_CheckOnOneMon::
	special GetDaycareMonNicknames
	msgbox Route34_Text_YourMonIsDoingFine, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_EventScript_CheckMonReceivedMail
	release
	end

Route34_EventScript_CheckOnTwoMons::
	special GetDaycareMonNicknames
	msgbox Route34_Text_YourMonsAreDoingFine, MSGBOX_DEFAULT
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 0
	call Route34_EventScript_CheckMonReceivedMail
	setvar VAR_0x8004, 1
	call Route34_EventScript_CheckMonReceivedMail
	release
	end

Route34_DayCare_EventScript_DaycareWoman::
	lock
	faceplayer
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_DayCare_EventScript_EggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_OneMonInDaycare
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route34_DayCare_EventScript_TwoMonsInDaycare
	msgbox Route34_DayCare_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	msgbox Route34_DayCare_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_GiveMonToRaise::
	specialvar VAR_RESULT, CountPartyNonEggMons
	goto_if_eq VAR_RESULT, 1, Route34_DayCare_EventScript_OnlyOneMon
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_eq VAR_RESULT, 2, Route34_DayCare_EventScript_OnlyTwoAliveMons
	msgbox Route34_DayCare_Text_WhichMonShouldWeRaise, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseSendDaycareMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route34_DayCare_EventScript_ComeAgain
	specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	goto_if_eq VAR_RESULT, 0, Route34_DayCare_EventScript_OnlyOneAliveMon
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	waitse
	playmoncry VAR_0x8005, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_WellRaiseYourMon, MSGBOX_DEFAULT
	waitmoncry
	special StoreSelectedPokemonInDaycare
	callnative UpdateFollowingPokemon
	incrementgamestat GAME_STAT_USED_DAYCARE
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_CanRaiseOneMore
	release
	end

Route34_DayCare_EventScript_ComeAgain::
	msgbox Route34_DayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_CanRaiseOneMore::
	msgbox Route34_DayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_OnlyOneMon::
	msgbox Route34_DayCare_Text_YouHaveJustOneMon, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_OnlyOneAliveMon::
	msgbox Route34_DayCare_Text_WhatWillYouBattleWith, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_OnlyTwoAliveMons::
	msgbox Route34_DayCare_Text_YoullBeLeftWithJustOne, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_EggWaiting::
	msgbox Route34_DayCare_Text_HusbandWasLookingForYou, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_YourMonHasGrownXLevels::
	msgbox Route34_DayCare_Text_YourMonHasGrownXLevels, MSGBOX_DEFAULT
	return

Route34_DayCare_EventScript_DisplayLevelsGained::
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	call_if_ne VAR_RESULT, 0, Route34_DayCare_EventScript_YourMonHasGrownXLevels
	return

Route34_DayCare_EventScript_OneMonInDaycare::
	msgbox Route34_DayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_DayCare_EventScript_DisplayLevelsGained
	msgbox Route34_DayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_GiveMonToRaise
	msgbox Route34_DayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_TryRetrieveMon::
	specialvar VAR_0x8004, GetMaxPartySize @ tx_randomizer_and_challenges
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_eq VAR_RESULT, VAR_0x8004, Route34_DayCare_EventScript_NoRoom
	specialvar VAR_RESULT, GetDaycareState
	setvar VAR_0x8004, 0
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar VAR_0x8004, VAR_RESULT
	goto_if_eq VAR_RESULT, DAYCARE_EXITED_LEVEL_MENU, Route34_DayCare_EventScript_ComeAgain
	goto Route34_DayCare_EventScript_CostPrompt
	end

Route34_DayCare_EventScript_CostPrompt::
	special GetDaycareCost
	msgbox Route34_DayCare_Text_ItWillCostX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_CheckEnoughMoney
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_CheckEnoughMoney::
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	goto_if_eq VAR_RESULT, 1, Route34_DayCare_EventScript_RetrieveMon
	msgbox Route34_DayCare_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_EventScript_RetrieveMon::
	@applymovement LOCALID_DAYCARE_LADY, Route34_DayCare_Movement_RetrieveDaycareMon
	@waitmovement 0
	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_SHOP
	msgbox Route34_DayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	waitse
	playmoncry VAR_RESULT, CRY_MODE_NORMAL
	msgbox Route34_DayCare_Text_TookBackMon, MSGBOX_DEFAULT
	waitmoncry
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route34_DayCare_EventScript_AskRetrieveOtherMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_AskRetrieveOtherMon::
	msgbox Route34_DayCare_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	goto Route34_DayCare_EventScript_ComeAgain
	end

Route34_DayCare_EventScript_NoRoom::
	msgbox Route34_DayCare_Text_YourTeamIsFull, MSGBOX_DEFAULT
	release
	end

Route34_DayCare_Movement_RetrieveDaycareMon:
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	face_right
	delay_16
	delay_16
	face_up
	walk_slow_up
	set_invisible
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	set_visible
	walk_slow_down
	step_end

@ Unused. Possibly a commented script, or a typo end added to the above Movement script
Route34_DayCare_EventScript_UnusedEnd::
	end

Route34_DayCare_EventScript_TwoMonsInDaycare::
	msgbox Route34_DayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route34_DayCare_EventScript_DisplayLevelsGained
	setvar VAR_0x8004, 1
	call Route34_DayCare_EventScript_DisplayLevelsGained
	msgbox Route34_DayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route34_DayCare_EventScript_TryRetrieveMon
	msgbox Route34_DayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route34_Text_SeeWifeIfYoudLikeMeToRaiseMon:
	.string "Soy el GUARDERÍA.\p"
	.string "Cuido los valiosos POKéMON\n"
	.string "de los ENTRENADORES.\p"
	.string "Si quieres que críe tu POKéMON,\n"
	.string "habla con mi esposa.$"

Route34_Text_DoYouWantEgg:
	.string "¡Ah, eres tú!\p"
	.string "Criábamos tu POKéMON y,\n"
	.string "¡vaya que nos sorprendió!\p"
	.string "¡Tu POKéMON tuvo un HUEVO!\p"
	.string "No sabemos cómo pasó,\n"
	.string "pero tu POKéMON lo tenía.\p"
	.string "Lo quieres, ¿verdad?$"

Route34_Text_YourMonIsDoingFine:
	.string "¡Ah, eres tú! Qué gusto verte.\n"
	.string "Tu {STR_VAR_1} está muy bien.$"

Route34_Text_IllKeepIt:
	.string "Bueno, entonces me lo quedo.\n"
	.string "¡Gracias!$"

Route34_Text_YouHaveNoRoomForIt:
	.string "No tienes espacio para ello...\n"
	.string "Vuelve cuando tengas espacio.$"

Route34_Text_ReceivedEgg:
	.string "{PLAYER} recibió el HUEVO del\n"
	.string "ENCARGADO DE LA GUARDERÍA.$"

Route34_Text_TakeGoodCareOfIt:
	.string "Cuídalo muy bien.$"

Route34_Text_FriendlyWithOtherTrainersMon:
	.string "Por cierto, sobre tu {STR_VAR_1},\n"
	.string "parecía llevarse bien con el\l"
	.string "{STR_VAR_3} de {STR_VAR_2}.\p"
	.string "Creo que hasta vi que recibía\n"
	.string "una CARTA.$"

@ Unused
Route34_Text_SeeWifeIfYouWantToPickUpMon:
	.string "Si quieres recuperar tu POKéMON,\n"
	.string "habla con mi esposa.$"

Route34_Text_YourMonsAreDoingFine:
	.string "¡Ah, eres tú! Tu {STR_VAR_1} y\n"
	.string "{STR_VAR_2} están muy bien.$"

Route34_Text_IWillKeepDoYouWantIt:
	.string "De verdad me lo quedaré.\n"
	.string "¿Seguro que quieres esto?$"

Route34_DayCare_Text_WouldYouLikeUsToRaiseAMon:
	.string "Soy la SEÑORA DE LA GUARDERÍA.\p"
	.string "Criamos POKéMON por ti.\p"
	.string "¿Quieres que criemos uno?$"

Route34_DayCare_Text_WhichMonShouldWeRaise:
	.string "¿Qué POKéMON quieres que criemos\n"
	.string "por ti?$"

Route34_DayCare_Text_WellRaiseYourMon:
	.string "Bien, criaremos a tu {STR_VAR_1}\n"
	.string "un tiempo.\p"
	.string "Vuelve más tarde por él.$"

Route34_DayCare_Text_WeCanRaiseOneMore:
	.string "Podemos criar dos POKéMON.\n"
	.string "¿Quieres que criemos uno más?$"

Route34_DayCare_Text_HusbandWasLookingForYou:
	.string "Mi esposo te estaba buscando.$"

Route34_DayCare_Text_FineThenComeAgain:
	.string "Oh, está bien entonces.\n"
	.string "Vuelve pronto.$"

Route34_DayCare_Text_NotEnoughMoney:
	.string "No tienes suficiente dinero…$"

Route34_DayCare_Text_TakeOtherOneBackToo:
	.string "¿Te llevarás también al otro\n"
	.string "POKéMON?$"

Route34_DayCare_Text_ComeAgain:
	.string "Bien.\n"
	.string "Vuelve pronto.$"

Route34_DayCare_Text_GoodToSeeYou:
	.string "¡Ah, eres tú! Qué gusto verte.\n"
	.string "¡Tus POKéMON deben estar genial!$"

Route34_DayCare_Text_YourMonHasGrownXLevels:
	.string "En nivel, tu {STR_VAR_1} ha\n"
	.string "subido {STR_VAR_2}.$"

Route34_DayCare_Text_YourTeamIsFull:
	.string "Tu equipo POKéMON está lleno.\n"
	.string "Haz espacio y vuelve a verme.$"

@ Unused
Route34_DayCare_Text_TakeBackWhichMon:
	.string "¿Qué POKéMON quieres llevarte?$"

Route34_DayCare_Text_ItWillCostX:
	.string "Si quieres recuperar a {STR_VAR_1},\n"
	.string "costará ¥{STR_VAR_2}.$"

Route34_DayCare_Text_HeresYourMon:
	.string "¡Perfecto!\n"
	.string "Aquí tienes a tu POKéMON.$"

Route34_DayCare_Text_TookBackMon:
	.string "{PLAYER} recuperó a {STR_VAR_1} de\n"
	.string "la SEÑORA DE LA GUARDERÍA.$"

Route34_DayCare_Text_YouHaveJustOneMon:
	.string "¿Oh? Pero solo tienes un\n"
	.string "POKéMON.\p"
	.string "Vuelve en otro momento.$"

Route34_DayCare_Text_TakeYourMonBack:
	.string "¿Te llevarás a tu POKéMON?$"

Route34_DayCare_Text_WhatWillYouBattleWith:
	.string "Si me dejas a ese POKéMON,\n"
	.string "¿con qué vas a luchar?\p"
	.string "Vuelve en otro momento.$"

Route34_DayCare_Text_YoullBeLeftWithJustOne:
	.string "¿Eh?\n"
	.string "Tranquilo.\p"
	.string "Si me dejas a ese POKéMON,\n"
	.string "solo te quedará uno.\p"
	.string "Sería mejor que atraparas\n"
	.string "algunos más, creo yo.$"
