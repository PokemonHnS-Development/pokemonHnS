SootopolisCity_LotadAndSeedotHouse_MapScripts::
	.byte 0

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotBrother::
	special GetSeedotSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot
	special CompareSeedotSize
	bufferunitsystemtext UNIT_TEXT_LENGTH_SMALL_PLURAL, 1
	goto_if_eq VAR_RESULT, 1, SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot
	goto_if_eq VAR_RESULT, 2, SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot
	goto_if_eq VAR_RESULT, 3, SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadBrother::
	special GetLotadSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad
	special CompareLotadSize
	bufferunitsystemtext UNIT_TEXT_LENGTH_SMALL_PLURAL, 1
	goto_if_eq VAR_RESULT, 1, SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad
	goto_if_eq VAR_RESULT, 2, SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad
	goto_if_eq VAR_RESULT, 3, SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotSizeRecord::
	special GetSeedotSizeRecordInfo
	lockall
	bufferunitsystemtext UNIT_TEXT_LENGTH_SMALL_SINGLE, 1
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadSizeRecord::
	special GetLotadSizeRecordInfo
	lockall
	bufferunitsystemtext UNIT_TEXT_LENGTH_SMALL_SINGLE, 1
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot:
	.string "¿Conoces al POKéMON SEEDOT?\n"
	.string "Casi no se ven en CALORÍA.\p"
	.string "Amo a los SEEDOT grandes.\n"
	.string "Cuanto más grandes, mejor.\p"
	.string "Pero mi hermano dice que\n"
	.string "LOTAD es más grande.\p"
	.string "Qué tontería.\n"
	.string "¡SEEDOT debe ser más grande!\p"
	.string "¿Tienes un SEEDOT contigo?\n"
	.string "¡P-p-por favor, muéstramelo!$"

SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad:
	.string "{STR_VAR_2} {STR_VAR_1}!\n"
	.string "¡Cielos, este es enorme!\p"
	.string "¡Podría vencer al LOTAD grande\n"
	.string "que vio mi hermano!\p"
	.string "Gracias por mostrármelo.\n"
	.string "¡Toma esto como agradecimiento!$"

@ Unused
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion1:
	.string "{PLAYER} recibió una POCIÓN.$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1:
	.string "¿Eh?\n"
	.string "Tu MOCHILA está llena.$"

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot:
	.string "{STR_VAR_2} {STR_VAR_1}, ¿eh?\p"
	.string "Hmm... He visto un SEEDOT más\n"
	.string "grande que este.$"

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot:
	.string "Vaya, esto es impresionante...\n"
	.string "¡Pero no es un SEEDOT!$"

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot:
	.string "¿No tienes un SEEDOT grande?\n"
	.string "Qué mal...\p"
	.string "Si consigues uno grande, por favor\n"
	.string "ven a mostrármelo.$"

SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory:
	.string "¡El SEEDOT más grande de la historia!\n"
	.string "¡El {STR_VAR_3}-{STR_VAR_1} {STR_VAR_2} gigante!\p"
	.string "¡Un SEEDOT más grande que un LOTAD,\n"
	.string "como siempre quise!$"

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad:
	.string "¿Conoces al POKéMON LOTAD?\n"
	.string "Rara vez se ve en SOOTOPOLIS.\p"
	.string "¡Amo, amo a los LOTAD grandes!\p"
	.string "Mi hermano dice que SEEDOT es\n"
	.string "más grande.\p"
	.string "¡Pero se equivoca! Todos saben que\n"
	.string "LOTAD es mucho más grande.\p"
	.string "¿Eh? ¿Tienes un LOTAD?\n"
	.string "¡P-p-por favor, muéstramelo!$"

SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot:
	.string "{STR_VAR_2} {STR_VAR_1}!\n"
	.string "¡Vaya, es enorme!\p"
	.string "Podría ser más grande que el SEEDOT\n"
	.string "gigante que vio mi hermano.\p"
	.string "¡Gracias por mostrármelo!\n"
	.string "¡Toma esto como agradecimiento!$"

@ Unused
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion2:
	.string "{PLAYER} recibió una POCIÓN.$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2:
	.string "¿Eh?\n"
	.string "Tu MOCHILA está llena.$"

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad:
	.string "¿{STR_VAR_2} {STR_VAR_1}?\p"
	.string "Hmm... He visto un LOTAD más\n"
	.string "grande que este.$"

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad:
	.string "¡Vaya, mira esto!\n"
	.string "¡Pero no es un LOTAD!$"

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad:
	.string "¿No tienes un LOTAD grande?\n"
	.string "Qué decepción...\p"
	.string "Si consigues un LOTAD grande,\n"
	.string "¡ven a mostrármelo!$"

SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory:
	.string "¡El LOTAD más grande de la historia!\n"
	.string "¡El coloso {STR_VAR_3}-{STR_VAR_1} de {STR_VAR_2}!\p"
	.string "¡El LOTAD más grande que un SEEDOT\n"
	.string "siempre quiso!$"
