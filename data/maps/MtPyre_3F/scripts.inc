MtPyre_3F_MapScripts::
	.byte 0

MtPyre_3F_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM, MtPyre_3F_Text_WilliamIntro, MtPyre_3F_Text_WilliamDefeat
	msgbox MtPyre_3F_Text_WilliamPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Kayla::
	trainerbattle_single TRAINER_KAYLA, MtPyre_3F_Text_KaylaIntro, MtPyre_3F_Text_KaylaDefeat
	msgbox MtPyre_3F_Text_KaylaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Gabrielle::
	trainerbattle_single TRAINER_ROD, MtPyre_3F_Text_GabrielleIntro, MtPyre_3F_Text_GabrielleDefeat, MtPyre_3F_EventScript_RegisterGabrielle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_3F_EventScript_RematchGabrielle
	msgbox MtPyre_3F_Text_GabriellePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_3F_EventScript_RegisterGabrielle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_3F_Text_GabrielleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ROD
	release
	end

MtPyre_3F_EventScript_RematchGabrielle::
	trainerbattle_rematch TRAINER_ROD, MtPyre_3F_Text_GabrielleRematchIntro, MtPyre_3F_Text_GabrielleRematchDefeat
	msgbox MtPyre_3F_Text_GabriellePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_Text_WilliamIntro:
	.string "¡El aire de la montaña\n"
	.string "subió mi poder psíquico!\p"
	.string "Un niño como tú...\n"
	.string "¿Sueñas con ganar?$"

MtPyre_3F_Text_WilliamDefeat:
	.string "Me ahogo en mi propia pena...$"

MtPyre_3F_Text_WilliamPostBattle:
	.string "Mi poder psíquico seguro\n"
	.string "creció mucho, pero...$"

MtPyre_3F_Text_KaylaIntro:
	.string "¡Ahajajaja!\p"
	.string "Este lugar no es para niños,\n"
	.string "¡y menos para ti!$"

MtPyre_3F_Text_KaylaDefeat:
	.string "Perdí limpiamente...$"

MtPyre_3F_Text_KaylaPostBattle:
	.string "Mi entrenamiento aún no\n"
	.string "es suficiente...\p"
	.string "Debo seguir esforzándome\n"
	.string "hasta la cima...\p"
	.string "¡Ánimo!$"

MtPyre_3F_Text_GabrielleIntro:
	.string "¿Por qué viniste aquí?$"

MtPyre_3F_Text_GabrielleDefeat:
	.string "¡Fue increíble!\n"
	.string "Eres un ENTRENADOR muy especial.$"

MtPyre_3F_Text_GabriellePostBattle:
	.string "POKéMON que ya no están aquí.\n"
	.string "POKéMON que están contigo ahora.\p"
	.string "Y los POKéMON que conocerás\n"
	.string "en el futuro…\p"
	.string "A todos debes quererlos igual.\n"
	.string "Por favor, recuerda eso.$"

MtPyre_3F_Text_GabrielleRegister:
	.string "Quisiera ver a tus POKéMON\n"
	.string "cuando crezcan un poco más…\p"
	.string "Por favor, enséñame tu POKéNAV.$"

MtPyre_3F_Text_GabrielleRematchIntro:
	.string "Oh, eres tú…\p"
	.string "¿Vienes a mostrarme a tus\n"
	.string "POKéMON ya crecidos?$"

MtPyre_3F_Text_GabrielleRematchDefeat:
	.string "¡Qué increíble!\n"
	.string "Eres una persona especial.$"

MtPyre_3F_Text_GabriellePostRematch:
	.string "POKéMON que ya no están aquí.\n"
	.string "POKéMON que están contigo ahora.\p"
	.string "Y los POKéMON que conocerás\n"
	.string "en el futuro…\p"
	.string "A todos debes quererlos igual.\n"
	.string "Veo que lo has recordado.$"

