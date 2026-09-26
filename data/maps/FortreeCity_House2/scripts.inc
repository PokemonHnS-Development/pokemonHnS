FortreeCity_House2_MapScripts::
	.byte 0

FortreeCity_House2_EventScript_HiddenPowerGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_HIDDEN_POWER, FortreeCity_House2_EventScript_ExplainHiddenPower
	call_if_unset FLAG_MET_HIDDEN_POWER_GIVER, FortreeCity_House2_EventScript_Greeting
	msgbox FortreeCity_House2_Text_CoinInWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand2, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 0, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_YourHiddenPowerHasAwoken, MSGBOX_DEFAULT
	giveitem ITEM_TM_HIDDEN_POWER
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_HIDDEN_POWER
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_Greeting::
	msgbox FortreeCity_House2_Text_HiddenPowersArousedByNature, MSGBOX_DEFAULT
	setflag FLAG_MET_HIDDEN_POWER_GIVER
	return

FortreeCity_House2_EventScript_ExplainHiddenPower::
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_WrongGuess::
	msgbox FortreeCity_House2_Text_YouGuessedWrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_Text_HiddenPowersArousedByNature:
	.string "Gente... POKéMON...\p"
	.string "Sus poderes ocultos despiertan al\n"
	.string "vivir en entornos naturales...$"

FortreeCity_House2_Text_CoinInWhichHand:
	.string "Deja que esta anciana vea si tu\n"
	.string "poder oculto despertó...\p"
	.string "Tengo una moneda en mi mano.\p"
	.string "Dime, ¿la tengo en la mano\n"
	.string "derecha? ¿O en la izquierda?$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand:
	.string "¡Oh! ¡Sí, correcto!\p"
	.string "Intentémoslo de nuevo.\p"
	.string "¿En qué mano tengo la moneda?\n"
	.string "¿Derecha o izquierda?$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand2:
	.string "¡Oh! ¡Sí, correcto!\p"
	.string "Intentémoslo de nuevo.\p"
	.string "¿En qué mano tengo la moneda?\n"
	.string "¿Derecha o izquierda?$"

FortreeCity_House2_Text_YourHiddenPowerHasAwoken:
	.string "¡Oh! ¡Espléndido!\n"
	.string "¡Tu poder oculto ha despertado!\p"
	.string "Toma esto y despierta el poder\n"
	.string "oculto de tu POKéMON.$"

FortreeCity_House2_Text_ExplainHiddenPower:
	.string "PODER OCULTO es un movimiento que\n"
	.string "cambia según el POKéMON.$"

FortreeCity_House2_Text_YouGuessedWrong:
	.string "No, qué mal.\n"
	.string "Adivinaste mal.$"

