LilycoveCity_House3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_House3_OnTransition
	.byte 0

LilycoveCity_House3_OnTransition:
	random 4
	copyvar VAR_TEMP_1, VAR_RESULT
	end

LilycoveCity_House3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_House3_EventScript_DeclinePokeblockLearn
	msgbox LilycoveCity_House3_Text_ExplainPokeblocks, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_DeclinePokeblockLearn::
	msgbox LilycoveCity_House3_Text_OhAreYouSure, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_Man::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_HappyToHaveQuadruplets, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_GameBoyKid1::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid2::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid3::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid4::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_WereDoingMultiBattle::
	msgbox LilycoveCity_House3_Text_GoingToWinMultiBattles, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereMixingRecords::
	msgbox LilycoveCity_House3_Text_LikeMixingAtRecordCorner, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereBlendingBerries::
	msgbox LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereDoingContest::
	msgbox LilycoveCity_House3_Text_GoingToEnterContest, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks:
	.string "¡Vaya, vaya! ¿Viajas solo?\n"
	.string "¡Eres muy joven! ¡Qué bien!\p"
	.string "¡Seguro que mis hijos podrían aprender\n"
	.string "algo de ti!\p"
	.string "¿Yo? Soy maestra de {POKEBLOCK}S.\p"
	.string "Si me pongo seria, puedo crear\n"
	.string "grandes {POKEBLOCK}S.\p"
	.string "¿Quieres aprender de mí,\n"
	.string "una maestra de {POKEBLOCK}S?$"

LilycoveCity_House3_Text_OhAreYouSure:
	.string "¿Oh? ¿Estás seguro?\p"
	.string "¡No intentes hacer siempre todo\n"
	.string "tú solo, cielo!$"

LilycoveCity_House3_Text_ExplainPokeblocks:
	.string "¡Bien! ¡Eres muy inteligente!\n"
	.string "Esto es largo, ¡así que escucha!\p"
	.string "¿Estás listo?\p"
	.string "Si miras los {POKEBLOCK}S, verás\n"
	.string "que tienen una calificación de sabor.\p"
	.string "Cuanto menor sea la calificación,\n"
	.string "mejor es. ¡No lo olvides!\p"
	.string "Un buen {POKEBLOCK} tiene sabor bajo\n"
	.string "y un nivel alto.\p"
	.string "Un POKéMON puede comer más\n"
	.string "{POKEBLOCK}S buenos que los comunes.\p"
	.string "Y esto es importante.\p"
	.string "Para hacer {POKEBLOCK}S suaves,\n"
	.string "usa distintos tipos de BAYAS.\p"
	.string "No seas tacaño; las BAYAS afectan\n"
	.string "la suavidad de los {POKEBLOCK}S.\p"
	.string "Y otra cosa.\p"
	.string "Cuanta más gente mezcle BAYAS,\n"
	.string "más suaves serán los {POKEBLOCK}S.\p"
	.string "Por eso debes hablar con otros\n"
	.string "y hacer {POKEBLOCK}S juntos.\p"
	.string "Eso es todo lo que necesitas saber\n"
	.string "para hacer buenos {POKEBLOCK}S.\p"
	.string "Si todos tuvieran POKéMON amados,\n"
	.string "suaves {POKEBLOCK}S y una familia,\l"
	.string "el mundo sería más feliz.\p"
	.string "¡No te rindas, cielo!$"

LilycoveCity_House3_Text_HappyToHaveQuadruplets:
	.string "Cuando mi mujer tuvo cuatrillizos,\n"
	.string "estaba muy sorprendido.\p"
	.string "Pero ahora, al verlos jugar juntos,\n"
	.string "me hace feliz.$"

LilycoveCity_House3_Text_GoingToWinMultiBattles:
	.string "Haremos COMBATES DOBLES, pero sé\n"
	.string "que voy a ganar.$"

LilycoveCity_House3_Text_LikeMixingAtRecordCorner:
	.string "Nos gusta mezclar cosas en el\n"
	.string "RINCÓN DISCOS.\p"
	.string "¿Pero qué es lo que se mezcla?$"

LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender:
	.string "¡Haremos súper {POKEBLOCK}S\n"
	.string "con una MEZCLADORA DE BAYAS!$"

LilycoveCity_House3_Text_GoingToEnterContest:
	.string "Quiero presumir de lo fuerte que es\n"
	.string "mi POKéMON, así que entraremos\l"
	.string "juntos en un CONCURSO.$"

