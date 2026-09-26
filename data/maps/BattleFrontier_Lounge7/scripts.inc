BattleFrontier_Lounge7_MapScripts::
	.byte 0

BattleFrontier_Lounge7_EventScript_LeftMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_1
	goto_if_set FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor
	msgbox BattleFrontier_Lounge7_Text_LeftTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor::
	msgbox BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_Softboiled::
	setvar VAR_0x8008, 16
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SeismicToss::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_DreamEater::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaPunch::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaKick::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_BodySlam::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RockSlide::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Counter::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderWave::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SwordsDance::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RightMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_2
	goto_if_set FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor
	msgbox BattleFrontier_Lounge7_Text_RightTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor::
	msgbox BattleFrontier_Lounge7_Text_RightTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_DefenseCurl::
	setvar VAR_0x8008, 16
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Snore::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MudSlap::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Swift::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcyWind::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Endure::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_PsychUp::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcePunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderPunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_FirePunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ElementalMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_3
	goto_if_set FLAG_MET_FRONTIER_ELEMENTAL_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetElementalTutor
	msgbox BattleFrontier_Lounge7_Text_ElementalTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_ELEMENTAL_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseElementalTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetElementalTutor::
	msgbox BattleFrontier_Lounge7_Text_ElementalTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseElementalTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseElementalTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMoveElemental
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 2
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_3
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_FrenzyPlant
	case 1, BattleFrontier_Lounge7_EventScript_BlastBurn
	case 2, BattleFrontier_Lounge7_EventScript_HydroCannon
	case 3, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewElementalTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMoveElemental
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 2
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_3
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_FrenzyPlant
	case 1, BattleFrontier_Lounge7_EventScript_BlastBurn
	case 2, BattleFrontier_Lounge7_EventScript_HydroCannon
	case 3, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_FrenzyPlant::
	setvar VAR_0x8008, 64
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_BlastBurn::
	setvar VAR_0x8008, 64
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_HydroCannon::
	setvar VAR_0x8008, 64
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect::
	special CloseBattleFrontierTutorWindow
	special CloseBattlePointsWindow
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge7_EventScript_CancelChooseMon::
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8008 is the price
@ VAR_TEMP_C is the scroll multichoice ID
@ VAR_TEMP_FRONTIER_TUTOR_SELECTION is the move selection
@ VAR_TEMP_FRONTIER_TUTOR_ID is which move tutor was spoken to
BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection::
	copyvar VAR_0x8004, VAR_TEMP_FRONTIER_TUTOR_SELECTION
	copyvar VAR_0x8005, VAR_TEMP_FRONTIER_TUTOR_ID
	special BufferBattleFrontierTutorMoveName
	buffernumberstring STR_VAR_2, VAR_0x8008
	copyvar VAR_0x8004, VAR_TEMP_C
	msgbox BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge7_EventScript_ChooseNewMove
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge7_EventScript_TeachTutorMove
	msgbox BattleFrontier_Lounge7_Text_HaventGotEnoughPoints, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseNewMove
	end

BattleFrontier_Lounge7_EventScript_TeachTutorMove::
	msgbox BattleFrontier_Lounge7_Text_TeachMoveToWhichMon, MSGBOX_DEFAULT
	special GetBattleFrontierTutorMoveIndex
	fadescreen FADE_TO_BLACK
	special CloseBattlePointsWindow
	special CloseBattleFrontierTutorWindow
	special ChooseMonForMoveTutor
	waitstate
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_Lounge7_EventScript_CancelChooseMon
	msgbox BattleFrontier_Lounge7_Text_IllTakeBattlePoints, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	release
	end

BattleFrontier_Lounge7_EventScript_ChooseNewMove::
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 0, BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 2, BattleFrontier_Lounge7_EventScript_ChooseNewElementalTutorMove
	goto BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_Sailor::
	msgbox BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong, MSGBOX_NPC
	end

BattleFrontier_Lounge7_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful, MSGBOX_NPC
	end

BattleFrontier_Lounge7_Text_LeftTutorIntro:
	.string "¡Buhahaha!\p"
	.string "No lo notarías ahora,\n"
	.string "pero yo era una ENTRENADORA dura.\p"
	.string "¡Tenía fama de ser la BEAUTY más\n"
	.string "fuerte de todas, te lo digo!\p"
	.string "… … … … … …\p"
	.string "¿Qué pasa?\n"
	.string "No me crees.\p"
	.string "No soy como esa fanfarrona de\n"
	.string "allá. ¡Tengo talento real!\p"
	.string "Déjame demostrártelo.\n"
	.string "Puedo enseñar a tu POKéMON movimientos\l"
	.string "especiales y lindos.\p"
	.string "Pero mis lecciones no son gratis.\n"
	.string "¿Qué tal si pagas los movimientos\l"
	.string "con unos pocos Puntos de Batalla?$"

BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack:
	.string "¡Buhahaha!\p"
	.string "¿Vuelves para aprender movimientos\n"
	.string "especiales y lindos para tu POKéMON?$"

BattleFrontier_Lounge7_Text_TeachWhichMove:
	.string "¡Bien, bien, mira aquí!\n"
	.string "¿Qué movimiento debo enseñar?$"

BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints:
	.string "¿El movimiento {STR_VAR_1}, eh?\n"
	.string "Serán {STR_VAR_2} Puntos de Batalla, ¿está bien?$"

BattleFrontier_Lounge7_Text_TeachMoveToWhichMon:
	.string "Bien, bien, ahora elige al POKéMON\n"
	.string "al que le enseñaré el movimiento.$"

BattleFrontier_Lounge7_Text_HaventGotEnoughPoints:
	.string "Pero qué…\n"
	.string "¡No tienes suficientes Puntos de Batalla!$"

BattleFrontier_Lounge7_Text_IllTakeBattlePoints:
	.string "¿Ves ahora lo hábil que soy?\n"
	.string "¡Me llevo tus Puntos de Batalla, gracias!$"

BattleFrontier_Lounge7_Text_YouDontWantTo:
	.string "¿Qué dices?\n"
	.string "¿No quieres…\p"
	.string "Si quieres ver lo hábil que soy,\n"
	.string "¡ven a verme cuando quieras!$"

BattleFrontier_Lounge7_Text_RightTutorIntro:
	.string "¡Ihihihi!\p"
	.string "Sé que es difícil verlo ahora, pero\n"
	.string "fui un ENTRENADOR fantástico.\p"
	.string "¡Tenía fama de ser el NADADOR más\n"
	.string "invencible de todos, te lo digo!\p"
	.string "… … … … … …\p"
	.string "¿Qué pasa?\n"
	.string "No me crees.\p"
	.string "No soy como esa mujer bufona de\n"
	.string "allí. ¡Tengo experiencia!\p"
	.string "Puedo probártelo.\n"
	.string "Puedo enseñar a tus POKéMON pasos\l"
	.string "fuertes y hermosos.\p"
	.string "Pero mis clases no son gratis.\n"
	.string "¿Qué tal pagar los movimientos con\l"
	.string "unos pocos Puntos de Batalla?$"

BattleFrontier_Lounge7_Text_RightTutorWelcomeBack:
	.string "¡Ihihihi!\p"
	.string "¿Vienes a aprender pasos de\n"
	.string "POKéMON fuertes y hermosos?$"

BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong:
	.string "Esas damas se critican tanto que\n"
	.string "probablemente pienses que\l"
	.string "no se llevan bien.\p"
	.string "Pero si fuera cierto, no estarían\n"
	.string "aquí juntas, ¿verdad?$"

BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful:
	.string "Cuando era un pequeño YOUNGSTER,\n"
	.string "esas damas eran fuertes y bellas.\p"
	.string "Eran ídolos entre los ENTRENADORES.\p"
	.string "Aún ahora, la edad no ha mermado\n"
	.string "sus habilidades.\p"
	.string "De hecho, sus movimientos de\n"
	.string "POKéMON son más pulidos.\p"
	.string "Pero... por alguna razón, no puedo\n"
	.string "evitar sentir esto...\p"
	.string "El tiempo es tan cruel...$"

BattleFrontier_Lounge7_Text_SoftboiledDesc::
	.string "Recupera hasta\n"
	.string "la mitad de los\n"
	.string "PS máximos del usuario.$"

BattleFrontier_Lounge7_Text_SeismicTossDesc::
	.string "Inflige un daño\n"
	.string "igual al nivel\n"
	.string "del usuario.$"

BattleFrontier_Lounge7_Text_DreamEaterDesc::
	.string "Recupera la mitad\n"
	.string "del daño causado a\n"
	.string "un rival dormido.$"

BattleFrontier_Lounge7_Text_MegaPunchDesc::
	.string "Un golpe fuerte\n"
	.string "lanzado con un\n"
	.string "poder increíble.$"

BattleFrontier_Lounge7_Text_MegaKickDesc::
	.string "Una patada muy\n"
	.string "poderosa con una\n"
	.string "fuerza intensa.$"

BattleFrontier_Lounge7_Text_BodySlamDesc::
	.string "Un placaje total\n"
	.string "que puede causar\n"
	.string "parálisis.$"

BattleFrontier_Lounge7_Text_RockSlideDesc::
	.string "Lanza rocas grandes.\n"
	.string "Puede causar\n"
	.string "retroceso.$"

BattleFrontier_Lounge7_Text_CounterDesc::
	.string "Devuelve un golpe\n"
	.string "físico con el doble\n"
	.string "de potencia.$"

BattleFrontier_Lounge7_Text_ThunderWaveDesc::
	.string "Una descarga débil\n"
	.string "que paraliza al\n"
	.string "adversario.$"

BattleFrontier_Lounge7_Text_SwordsDanceDesc::
	.string "Una danza de lucha\n"
	.string "que sube mucho el\n"
	.string "ATAQUE.$"

BattleFrontier_Lounge7_Text_DefenseCurlDesc::
	.string "Se encoge para\n"
	.string "ocultar puntos débiles\n"
	.string "y subir DEFENSA.$"

BattleFrontier_Lounge7_Text_SnoreDesc::
	.string "Un ataque fuerte\n"
	.string "que solo se usa\n"
	.string "estando dormido.$"

BattleFrontier_Lounge7_Text_MudSlapDesc::
	.string "Lanza lodo a la cara\n"
	.string "del rival para\n"
	.string "bajar su precisión.$"

BattleFrontier_Lounge7_Text_SwiftDesc::
	.string "Lanza rayos en\n"
	.string "forma de estrella\n"
	.string "que nunca fallan.$"

BattleFrontier_Lounge7_Text_IcyWindDesc::
	.string "Ataque gélido que\n"
	.string "reduce la VELOCIDAD\n"
	.string "del rival.$"

BattleFrontier_Lounge7_Text_EndureDesc::
	.string "Resiste cualquier\n"
	.string "ataque un turno\n"
	.string "y deja 1 PS.$"

BattleFrontier_Lounge7_Text_PsychUpDesc::
	.string "Copia los efectos\n"
	.string "del rival y los\n"
	.string "da al usuario.$"

BattleFrontier_Lounge7_Text_IcePunchDesc::
	.string "Un puño de hielo\n"
	.string "que puede conge-\n"
	.string "lar al rival.$"

BattleFrontier_Lounge7_Text_ThunderPunchDesc::
	.string "Un puño eléctrico\n"
	.string "que puede paralizar\n"
	.string "al rival.$"

BattleFrontier_Lounge7_Text_FirePunchDesc::
	.string "Un puño de fuego\n"
	.string "que puede quemar\n"
	.string "al rival.$"

BattleFrontier_Lounge7_Text_ElementalTutorIntro::
	.string "Zzzzzz…\p"
	.string "¿Qué? ¿Cómo? ¿Qué?\p"
	.string "Perdón, estaba dormitando.\p"
	.string "Soy el TUTOR ELEMENTAL.\p"
	.string "Enseño los movimientos más\n"
	.string "fuertes a POKéMON de tipo PLANTA,\l"
	.string "FUEGO y AGUA.\p"
	.string "¿Vienes a aprender un poder\n"
	.string "así de fuerte?$"

BattleFrontier_Lounge7_Text_ElementalTutorWelcomeBack:
	.string "Zzzzzz…\p"
	.string "¿Qué? ¿Cómo? ¿Qué? ¿Quién?\p"
	.string "¿Vienes a aprender el poder\n"
	.string "de mis mejores movimientos?$"

BattleFrontier_Lounge7_Text_TeachWhichMoveElemental::
	.string "¿Qué movimiento crees que es el\n"
	.string "ideal para tu POKéMON?$"

BattleFrontier_Lounge7_Text_StrongElementalMoveDesc::
	.string "Es poderoso, pero\n"
	.string "deja al usuario\n"
	.string "sin moverse un turno.$"
