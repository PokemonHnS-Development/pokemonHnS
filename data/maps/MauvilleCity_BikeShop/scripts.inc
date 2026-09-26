MauvilleCity_BikeShop_MapScripts::
	.byte 0

MauvilleCity_BikeShop_EventScript_Rydel::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, MauvilleCity_BikeShop_EventScript_AskSwitchBikes
	goto_if_set FLAG_DECLINED_BIKE, MauvilleCity_BikeShop_EventScript_SkipGreeting
	msgbox MauvilleCity_BikeShop_Text_RydelGreeting, MSGBOX_DEFAULT
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_SkipGreeting::
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_ChooseBike::
	msgbox MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_GetAcroBike
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_GetMachBike
	@waitmessage
	@multichoice 21, 8, MULTI_BIKE, TRUE
	@switch VAR_RESULT
	@case 0, MauvilleCity_BikeShop_EventScript_GetMachBike
	@case 1, MauvilleCity_BikeShop_EventScript_GetMachBike
	end

MauvilleCity_BikeShop_EventScript_NotFar::
	setflag FLAG_DECLINED_BIKE
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_YesFar::
	goto MauvilleCity_BikeShop_EventScript_ChooseBike
	end

MauvilleCity_BikeShop_EventScript_GetMachBike::
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike2, MSGBOX_DEFAULT
	@giveitem ITEM_MACH_BIKE
	@goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	release
	end

MauvilleCity_BikeShop_EventScript_GetAcroBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseAcroBike, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	setflag FLAG_RECEIVED_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_AskSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_WantToSwitchBikes, MSGBOX_NPC
	@goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_SwitchBikes
	@goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_KeepBike
	end

@ If the player does not have a bike on them Rydel assumes its stored in the PC
MauvilleCity_BikeShop_EventScript_SwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_IllSwitchBikes, MSGBOX_DEFAULT
	checkitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchAcroForMach
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchMachForAcro
	msgbox MauvilleCity_BikeShop_Text_OhYourBikeIsInPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_KeepBike::
	msgbox MauvilleCity_BikeShop_Text_HappyYouLikeIt, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_SwitchAcroForMach::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedAcroForMach, MSGBOX_DEFAULT
	removeitem ITEM_ACRO_BIKE
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_SwitchMachForAcro::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedMachForAcro, MSGBOX_DEFAULT
	removeitem ITEM_MACH_BIKE
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_Assistant::
	msgbox MauvilleCity_BikeShop_Text_HandbooksAreInBack, MSGBOX_NPC
	end

MauvilleCity_BikeShop_EventScript_MachBikeHandbook::
	message MauvilleCity_BikeShop_Text_MachHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage::
	multichoice 0, 0, MULTI_MACH_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_HowToRide
	case 1, MauvilleCity_BikeShop_EventScript_HowToTurn
	case 2, MauvilleCity_BikeShop_EventScript_SandySlopes
	case 3, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	end

MauvilleCity_BikeShop_EventScript_HowToRide::
	message MauvilleCity_BikeShop_Text_HowToRideMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_HowToTurn::
	message MauvilleCity_BikeShop_Text_HowToTurnMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_SandySlopes::
	message MauvilleCity_BikeShop_Text_SandySlopes
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitMachHandbook::
	release
	end

MauvilleCity_BikeShop_EventScript_AcroBikeHandbook::
	message MauvilleCity_BikeShop_Text_AcroHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage::
	multichoice 0, 0, MULTI_ACRO_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_Wheelies
	case 1, MauvilleCity_BikeShop_EventScript_BunnyHops
	case 2, MauvilleCity_BikeShop_EventScript_Jumps
	case 3, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	end

MauvilleCity_BikeShop_EventScript_Wheelies::
	message MauvilleCity_BikeShop_Text_Wheelies
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_BunnyHops::
	message MauvilleCity_BikeShop_Text_BunnyHops
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_Jumps::
	message MauvilleCity_BikeShop_Text_Jumps
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitAcroHandbook::
	release
	end

MauvilleCity_BikeShop_Text_RydelGreeting:
	.string "Vaya, vaya, ¿qué tenemos aquí?\n"
	.string "¡Un cliente muy energético!\p"
	.string "¿Yo? Puedes llamarme RYDEL.\n"
	.string "Soy el dueño de esta tienda de bicis.$"

MauvilleCity_BikeShop_Text_DidYouComeFromFarAway:
	.string "RYDEL: Tus ZAPATOS DE CORRER…\n"
	.string "Están terriblemente sucios.\p"
	.string "¿Vienes de muy lejos?$"

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike:
	.string "RYDEL: ¿Ah, sí?\p"
	.string "Entonces, supongo que no necesitas\n"
	.string "ninguna de mis BIKES.$"

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike2:
	.string "RYDEL: ¿Ah, sí?\p"
	.string "Está bien, tú decides.$"

MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne:
	.string "RYDEL: Hm, hm… … … … …\p"
	.string "¿Dices que viniste desde\n"
	.string "PUEBLO RAÍZ?\p"
	.string "¡Cielos!\n"
	.string "¡Eso está ridículamente lejos!\p"
	.string "¡Con una de mis BICICLETAS podrías\n"
	.string "ir a donde sea sintiendo la\l"
	.string "brisa en tu rostro!\p"
	.string "¡Tengo una idea!\n"
	.string "¡Te daré una BICICLETA!\p"
	.string "¡Ah, espera un segundo!\p"
	.string "¡Olvidé decirte que hay\n"
	.string "dos tipos de BICICLETAS!\p"
	.string "¡Están la MACH BIKE y\n"
	.string "la ACRO BIKE!\p"
	.string "¡La MACH BIKE es para quienes\n"
	.string "quieren sentir la velocidad!\p"
	.string "¡Y la ACRO BIKE es para quienes\n"
	.string "prefieren los trucos técnicos!\p"
	.string "¿Y sabes qué es lo mejor?\p"
	.string "¡Ambas son una sola\n"
	.string "BICICLETA! ¡Todo en uno!\p"
	.string "Entonces, ¿quieres una BICICLETA?$"

MauvilleCity_BikeShop_Text_ChoseMachBike:
	.string "{PLAYER} eligió la MACH BIKE.$"

MauvilleCity_BikeShop_Text_ChoseAcroBike:
	.string "{PLAYER} recibió una BIKE.$"

MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes:
	.string "RYDEL: ¡Disfruta tu nueva BIKE!\p"
	.string "RYDEL: Recuerda pulsar el botón R\n"
	.string "para cambiar el modo de la BIKE.$"

MauvilleCity_BikeShop_Text_WantToSwitchBikes:
	.string "RYDEL: ¿Estás disfrutando\n"
	.string "tu BICICLETA?\p"
	.string "RYDEL: Recuerda pulsar el botón R\n"
	.string "para cambiar el modo de BICICLETA.$"

MauvilleCity_BikeShop_Text_IllSwitchBikes:
	.string "RYDEL: ¡Vale, no hay problema!\n"
	.string "¡Te cambiaré la BIKE!$"

MauvilleCity_BikeShop_Text_ExchangedMachForAcro:
	.string "{PLAYER} cambió la MACH BIKE\n"
	.string "por una ACRO BIKE.$"

MauvilleCity_BikeShop_Text_ExchangedAcroForMach:
	.string "{PLAYER} cambió la ACRO BIKE\n"
	.string "por una MACH BIKE.$"

MauvilleCity_BikeShop_Text_HappyYouLikeIt:
	.string "RYDEL: ¡Bien, bien!\n"
	.string "¡Me alegra que te guste!$"

MauvilleCity_BikeShop_Text_OhYourBikeIsInPC:
	.string "¿Eh? ¿Qué pasó con la BIKE\n"
	.string "que te di?\p"
	.string "Ya veo, la guardaste en el PC.\p"
	.string "Sácala del PC y con gusto\n"
	.string "la cambiaré!\p"
	.string "¡Que el viento te acompañe en\n"
	.string "tu aventura!$"

MauvilleCity_BikeShop_Text_HandbooksAreInBack:
	.string "Aprendo sobre BIKES mientras\n"
	.string "trabajo aquí.\p"
	.string "Si necesitas consejos para usar la\n"
	.string "BIKE, hay manuales en la parte\l"
	.string "trasera.$"

MauvilleCity_BikeShop_Text_MachHandbookWhichPage:
	.string "Es un manual de la MACH BIKE.\p"
	.string "¿Qué página quieres leer?$"

MauvilleCity_BikeShop_Text_HowToRideMachBike:
	.string "La BIKE avanza hacia donde se\n"
	.string "presiona la cruceta.\p"
	.string "Aumentará su velocidad al rodar.\p"
	.string "Para frenar, suelta la cruceta.\n"
	.string "La BIKE irá frenando hasta parar.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_HowToTurnMachBike:
	.string "La MACH BIKE es veloz, pero no\n"
	.string "frena muy rápido.\p"
	.string "Es algo difícil tomar las\n"
	.string "curvas.\p"
	.string "Suelta la cruceta un poco antes\n"
	.string "de la curva para reducir velocidad.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_SandySlopes:
	.string "Hay pequeñas pendientes de arena\n"
	.string "en toda la región de HOENN.\p"
	.string "La arena suelta impide que se\n"
	.string "pueda subir normalmente.\p"
	.string "Pero con una MACH BIKE, puedes\n"
	.string "subir rápido por la arena.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_AcroHandbookWhichPage:
	.string "Es un manual sobre la ACRO BIKE.\p"
	.string "¿Qué página quieres leer?$"

MauvilleCity_BikeShop_Text_Wheelies:
	.string "Pulsa B mientras conduces y la\n"
	.string "rueda delantera se elevará.\p"
	.string "Puedes girar con la rueda arriba\n"
	.string "usando la cruceta.\p"
	.string "Esta técnica se llama wheelie.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_BunnyHops:
	.string "Mantén pulsado B y tu BIKE\n"
	.string "podrá saltar en el sitio.\p"
	.string "Esta técnica se llama bunny hop.\p"
	.string "También puedes saltar mientras vas.\p"
	.string "¿Quieres leer otra página?$"

MauvilleCity_BikeShop_Text_Jumps:
	.string "Pulsa B y la cruceta a la vez\n"
	.string "para saltar.\p"
	.string "Pulsa la cruceta a un lado para\n"
	.string "saltar lateralmente.\p"
	.string "Pulsa atrás para que la BIKE\n"
	.string "cambie de rumbo al saltar.\p"
	.string "¿Quieres leer otra página?$"

