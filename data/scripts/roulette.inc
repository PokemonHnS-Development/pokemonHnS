Roulette_EventScript_Table1::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Table2::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Play::
	special PlayRoulette
	waitstate
	end

Roulette_Text_PlayMinimumWagerIsX::
	.string "La apuesta mínima en esta mesa\n"
	.string "es {STR_VAR_1}. ¿Quieres jugar?$"

Roulette_Text_NotEnoughCoins::
	.string "No tienes suficientes MONEDAS.$"

Roulette_Text_SpecialRateTable::
	.string "¡Ahora hay una tarifa especial!$"

Roulette_Text_ControlsInstruction::
	.string "Apuesta con el botón + del\n"
	.string "Control, luego presiona A.$"

Roulette_Text_ItsAHit::
	.string "¡Es un acierto!$"

Roulette_Text_Jackpot::
	.string "¡Jackpot!$"

Roulette_Text_NothingDoing::
	.string "¡No has ganado nada!$"

Roulette_Text_YouveWonXCoins::
	.string "¡Ganaste {STR_VAR_1} MONEDAS!$"

Roulette_Text_NoCoinsLeft::
	.string "No quedan COINS…$"

Roulette_Text_KeepPlaying::
	.string "¿Quieres seguir jugando?$"

Roulette_Text_BoardWillBeCleared::
	.string "Se borrará el tablero de ROULETTE.$"

@ Unused
Roulette_Text_YouDontHaveACoinCase::
	.string "No tienes un COIN CASE.$"

Roulette_Text_CoinCaseIsFull::
	.string "¡Tu COIN CASE está lleno!\n"
	.string "Cambia COINS por premios.$"
