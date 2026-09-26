TrainerHill_Courtyard_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, TrainerHill_Courtyard_OnTransition
	.byte 0

TrainerHill_Courtyard_OnTransition::
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	end

TrainerHill_Courtyard_EventScript_BattleTowerSign::
	lock
	msgbox BattleTowerOutsideSignText, MSGBOX_SIGN	
	closemessage	
	release
	end

TrainerHill_Courtyard_EventScript_Tent_Factory::
	lock
	msgbox BattleTower_Battle_Tent_Text_Factory, MSGBOX_SIGN	
	closemessage	
	release
	end

TrainerHill_Courtyard_EventScript_Tent_Palace::
	lock
	msgbox BattleTower_Battle_Tent_Text_Palace, MSGBOX_SIGN	
	closemessage	
	release
	end

TrainerHill_Courtyard_EventScript_Tent_Arena::
	lock
	msgbox BattleTower_Battle_Tent_Text_Arena, MSGBOX_SIGN	
	closemessage	
	release
	end
	
TrainerHill_Courtyard_EventScript_Engineer::
	lock
	faceplayer
	msgbox BattleTowerOutsideText_Closed, MSGBOX_DEFAULT
	closemessage
	release
	end

TrainerHill_Courtyard_EventScript_Youngster::
	lock
	faceplayer
	msgbox BattleTowerOutsideYoungsterText, MSGBOX_DEFAULT
	closemessage
	release
	end

TrainerHill_Courtyard_EventScript_Beauty::
	lock
	faceplayer
	msgbox BattleTowerOutsideBeautyText, MSGBOX_DEFAULT
	closemessage
	release
	end

TrainerHill_Courtyard_EventScript_Sailor::
	lock
	faceplayer
	msgbox BattleTowerOutsideSailorText, MSGBOX_DEFAULT
	closemessage
	release
	end

BattleTowerOutsideYoungsterText:
	.string "¡Vaya, la COLINA ENTRENADOR es\p"
	.string "enorme! ¡Debe haber muchos tipos\n"
	.string "de POKéMON allí!$"

BattleTowerOutsideBeautyText:
	.string "En las CARPAS DE BATALLA solo\n"
	.string "puedes usar tres POKéMON.\p"
	.string "Es difícil decidir cuáles tres\n"
	.string "irán a la batalla…$"

BattleTowerOutsideSailorText:
	.string "Jeje, me escapé del trabajo.\p"
	.string "¡No volveré hasta que gane!\p"
	.string "Debo ganarlo todo. ¡Tengo que hacerlo!$"

BattleTowerOutsideSignText:
	.string "{UP_ARROW} ENTRADA COLINA ENTRENADOR\p"
	.string "“¡Escalen la cima, ENTRENADORES\n"
	.string "apasionados!”\p"
	.string "{RIGHT_ARROW} CARPAS DE BATALLA.$"

BattleTower_Battle_Tent_Text_Factory:
	.string "CARPA DE BATALLA: FÁBRICA\n"
	.string "“¡Búscalo! ¡El POKéMON definitivo!”$"

BattleTower_Battle_Tent_Text_Palace:
	.string "CARPA DE BATALLA: PALACIO\n"
	.string "“¡Disfruten de las batallas!”$"

BattleTower_Battle_Tent_Text_Arena:
	.string "CARPA DE BATALLA: ARENA\n"
	.string "“¡Que se reúnan los mejores equipos!”$"

BattleTowerOutsideText_Closed:
	.string "La COLINA ENTRENADOR está\n"
	.string "cerrada por reparaciones.$"


TrainerHill_Courtyard_EventScript_LeftMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_1
	goto_if_set FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR, TrainerHill_Courtyard_EventScript_AlreadyMetLeftTutor
	msgbox TrainerHill_Courtyard_Text_LeftTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR
	goto TrainerHill_Courtyard_EventScript_ChooseLeftTutorMove
	end

TrainerHill_Courtyard_EventScript_AlreadyMetLeftTutor::
	msgbox TrainerHill_Courtyard_Text_LeftTutorWelcomeBack, MSGBOX_DEFAULT
	goto TrainerHill_Courtyard_EventScript_ChooseLeftTutorMove
	end

TrainerHill_Courtyard_EventScript_ChooseLeftTutorMove::
	message TrainerHill_Courtyard_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, TrainerHill_Courtyard_EventScript_Softboiled
	case 1, TrainerHill_Courtyard_EventScript_SeismicToss
	case 2, TrainerHill_Courtyard_EventScript_DreamEater
	case 3, TrainerHill_Courtyard_EventScript_MegaPunch
	case 4, TrainerHill_Courtyard_EventScript_MegaKick
	case 5, TrainerHill_Courtyard_EventScript_BodySlam
	case 6, TrainerHill_Courtyard_EventScript_RockSlide
	case 7, TrainerHill_Courtyard_EventScript_Counter
	case 8, TrainerHill_Courtyard_EventScript_ThunderWave
	case 9, TrainerHill_Courtyard_EventScript_SwordsDance
	case 10, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	end

TrainerHill_Courtyard_EventScript_ChooseNewLeftTutorMove::
	message TrainerHill_Courtyard_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, TrainerHill_Courtyard_EventScript_Softboiled
	case 1, TrainerHill_Courtyard_EventScript_SeismicToss
	case 2, TrainerHill_Courtyard_EventScript_DreamEater
	case 3, TrainerHill_Courtyard_EventScript_MegaPunch
	case 4, TrainerHill_Courtyard_EventScript_MegaKick
	case 5, TrainerHill_Courtyard_EventScript_BodySlam
	case 6, TrainerHill_Courtyard_EventScript_RockSlide
	case 7, TrainerHill_Courtyard_EventScript_Counter
	case 8, TrainerHill_Courtyard_EventScript_ThunderWave
	case 9, TrainerHill_Courtyard_EventScript_SwordsDance
	case 10, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	end

TrainerHill_Courtyard_EventScript_Softboiled::
	setvar VAR_0x8008, 16
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_SeismicToss::
	setvar VAR_0x8008, 24
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_DreamEater::
	setvar VAR_0x8008, 24
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_MegaPunch::
	setvar VAR_0x8008, 24
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_MegaKick::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_BodySlam::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_RockSlide::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_Counter::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_ThunderWave::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_SwordsDance::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_RightMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_2
	goto_if_set FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR, TrainerHill_Courtyard_EventScript_AlreadyMetRightTutor
	msgbox TrainerHill_Courtyard_Text_RightTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR
	goto TrainerHill_Courtyard_EventScript_ChooseRightTutorMove
	end

TrainerHill_Courtyard_EventScript_AlreadyMetRightTutor::
	msgbox TrainerHill_Courtyard_Text_RightTutorWelcomeBack, MSGBOX_DEFAULT
	goto TrainerHill_Courtyard_EventScript_ChooseRightTutorMove
	end

TrainerHill_Courtyard_EventScript_ChooseRightTutorMove::
	message TrainerHill_Courtyard_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, TrainerHill_Courtyard_EventScript_DefenseCurl
	case 1, TrainerHill_Courtyard_EventScript_Snore
	case 2, TrainerHill_Courtyard_EventScript_MudSlap
	case 3, TrainerHill_Courtyard_EventScript_Swift
	case 4, TrainerHill_Courtyard_EventScript_IcyWind
	case 5, TrainerHill_Courtyard_EventScript_Endure
	case 6, TrainerHill_Courtyard_EventScript_PsychUp
	case 7, TrainerHill_Courtyard_EventScript_IcePunch
	case 8, TrainerHill_Courtyard_EventScript_ThunderPunch
	case 9, TrainerHill_Courtyard_EventScript_FirePunch
	case 10, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	end

TrainerHill_Courtyard_EventScript_ChooseNewRightTutorMove::
	message TrainerHill_Courtyard_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, TrainerHill_Courtyard_EventScript_DefenseCurl
	case 1, TrainerHill_Courtyard_EventScript_Snore
	case 2, TrainerHill_Courtyard_EventScript_MudSlap
	case 3, TrainerHill_Courtyard_EventScript_Swift
	case 4, TrainerHill_Courtyard_EventScript_IcyWind
	case 5, TrainerHill_Courtyard_EventScript_Endure
	case 6, TrainerHill_Courtyard_EventScript_PsychUp
	case 7, TrainerHill_Courtyard_EventScript_IcePunch
	case 8, TrainerHill_Courtyard_EventScript_ThunderPunch
	case 9, TrainerHill_Courtyard_EventScript_FirePunch
	case 10, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	end

TrainerHill_Courtyard_EventScript_DefenseCurl::
	setvar VAR_0x8008, 16
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_Snore::
	setvar VAR_0x8008, 24
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_MudSlap::
	setvar VAR_0x8008, 24
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_Swift::
	setvar VAR_0x8008, 24
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_IcyWind::
	setvar VAR_0x8008, 24
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_Endure::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_PsychUp::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_IcePunch::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_ThunderPunch::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_FirePunch::
	setvar VAR_0x8008, 48
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_ElementalMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_3
	goto_if_set FLAG_MET_FRONTIER_ELEMENTAL_MOVE_TUTOR, TrainerHill_Courtyard_EventScript_AlreadyMetElementalTutor
	msgbox TrainerHill_Courtyard_Text_ElementalTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_ELEMENTAL_MOVE_TUTOR
	goto TrainerHill_Courtyard_EventScript_ChooseElementalTutorMove
	end

TrainerHill_Courtyard_EventScript_AlreadyMetElementalTutor::
	msgbox TrainerHill_Courtyard_Text_ElementalTutorWelcomeBack, MSGBOX_DEFAULT
	goto TrainerHill_Courtyard_EventScript_ChooseElementalTutorMove
	end

TrainerHill_Courtyard_EventScript_ChooseElementalTutorMove::
	message TrainerHill_Courtyard_Text_TeachWhichMoveElemental
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 2
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_3
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, TrainerHill_Courtyard_EventScript_FrenzyPlant
	case 1, TrainerHill_Courtyard_EventScript_BlastBurn
	case 2, TrainerHill_Courtyard_EventScript_HydroCannon
	case 3, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	end

TrainerHill_Courtyard_EventScript_ChooseNewElementalTutorMove::
	message TrainerHill_Courtyard_Text_TeachWhichMoveElemental
	waitmessage
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 2
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_3
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, TrainerHill_Courtyard_EventScript_FrenzyPlant
	case 1, TrainerHill_Courtyard_EventScript_BlastBurn
	case 2, TrainerHill_Courtyard_EventScript_HydroCannon
	case 3, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect
	end

TrainerHill_Courtyard_EventScript_FrenzyPlant::
	setvar VAR_0x8008, 64
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_BlastBurn::
	setvar VAR_0x8008, 64
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_HydroCannon::
	setvar VAR_0x8008, 64
	goto TrainerHill_Courtyard_EventScript_ConfirmMoveSelection
	end

TrainerHill_Courtyard_EventScript_ExitTutorMoveSelect::
	special CloseBattleFrontierTutorWindow
	special CloseBattlePointsWindow
	msgbox TrainerHill_Courtyard_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

TrainerHill_Courtyard_EventScript_CancelChooseMon::
	msgbox TrainerHill_Courtyard_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8008 is the price
@ VAR_TEMP_C is the scroll multichoice ID
@ VAR_TEMP_FRONTIER_TUTOR_SELECTION is the move selection
@ VAR_TEMP_FRONTIER_TUTOR_ID is which move tutor was spoken to
TrainerHill_Courtyard_EventScript_ConfirmMoveSelection::
	copyvar VAR_0x8004, VAR_TEMP_FRONTIER_TUTOR_SELECTION
	copyvar VAR_0x8005, VAR_TEMP_FRONTIER_TUTOR_ID
	special BufferBattleFrontierTutorMoveName
	buffernumberstring STR_VAR_2, VAR_0x8008
	copyvar VAR_0x8004, VAR_TEMP_C
	msgbox TrainerHill_Courtyard_Text_MoveWillBeXBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_EventScript_ChooseNewMove
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, TrainerHill_Courtyard_EventScript_TeachTutorMove
	msgbox TrainerHill_Courtyard_Text_HaventGotEnoughPoints, MSGBOX_DEFAULT
	goto TrainerHill_Courtyard_EventScript_ChooseNewMove
	end

TrainerHill_Courtyard_EventScript_TeachTutorMove::
	msgbox TrainerHill_Courtyard_Text_TeachMoveToWhichMon, MSGBOX_DEFAULT
	special GetBattleFrontierTutorMoveIndex
	fadescreen FADE_TO_BLACK
	special CloseBattlePointsWindow
	special CloseBattleFrontierTutorWindow
	special ChooseMonForMoveTutor
	waitstate
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Courtyard_EventScript_CancelChooseMon
	msgbox TrainerHill_Courtyard_Text_IllTakeBattlePoints, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	release
	end

TrainerHill_Courtyard_EventScript_ChooseNewMove::
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 0, TrainerHill_Courtyard_EventScript_ChooseNewLeftTutorMove
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 2, TrainerHill_Courtyard_EventScript_ChooseNewElementalTutorMove
	goto TrainerHill_Courtyard_EventScript_ChooseNewRightTutorMove
	end

TrainerHill_Courtyard_Text_LeftTutorIntro:
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
	.string "Enseño a tu POKéMON movimientos\l"
	.string "especiales y lindos.\p"
	.string "Pero mis clases no son gratis.\n"
	.string "¿Qué tal pagar los movimientos\l"
	.string "con unos pocos Puntos de Batalla?$"

TrainerHill_Courtyard_Text_LeftTutorWelcomeBack:
	.string "¡Buhahaha!\p"
	.string "¿Vuelves para aprender movimientos\n"
	.string "especiales y lindos para tu POKéMON?$"

TrainerHill_Courtyard_Text_TeachWhichMove:
	.string "¡Bien, bien, mira aquí!\n"
	.string "¿Qué movimiento debo enseñar?$"

TrainerHill_Courtyard_Text_MoveWillBeXBattlePoints:
	.string "El movimiento {STR_VAR_1}, ¿sí?\n"
	.string "Serán {STR_VAR_2} Puntos de Batalla, ¿está bien?$"

TrainerHill_Courtyard_Text_TeachMoveToWhichMon:
	.string "Bien, bien, ahora elige al POKéMON\n"
	.string "al que le enseñaré el movimiento.$"

TrainerHill_Courtyard_Text_HaventGotEnoughPoints:
	.string "Pero qué…\n"
	.string "¡No tienes suficientes Puntos de Batalla!$"

TrainerHill_Courtyard_Text_IllTakeBattlePoints:
	.string "¿Ves ahora lo hábil que soy?\n"
	.string "¡Me llevo tus Puntos de Batalla, gracias!$"

TrainerHill_Courtyard_Text_YouDontWantTo:
	.string "¿Qué dices?\n"
	.string "¿No quieres…\p"
	.string "Si quieres ver lo hábil que soy,\n"
	.string "¡ven a verme cuando quieras!$"

TrainerHill_Courtyard_Text_RightTutorIntro:
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
	.string "Pero mis lecciones no son gratis.\n"
	.string "¿Qué tal si pagas los movimientos\l"
	.string "con unos pocos Puntos de Batalla?$"

TrainerHill_Courtyard_Text_RightTutorWelcomeBack:
	.string "¡Ihihihi!\p"
	.string "¿Vienes a aprender movimientos\n"
	.string "fuertes y bellos para tus POKéMON?$"

TrainerHill_Courtyard_Text_ThinkLadiesDontGetAlong:
	.string "Esas damas, por cómo se critican\n"
	.string "entre sí, pensarás que\l"
	.string "no se llevan bien.\p"
	.string "Pero si fuera cierto, no estarían\n"
	.string "aquí juntas, ¿verdad?$"

TrainerHill_Courtyard_Text_LadiesWereStrongAndBeautiful:
	.string "Cuando era un pequeño YOUNGSTER,\n"
	.string "esas damas eran fuertes y bellas.\p"
	.string "Eran ídolos entre los ENTRENADORES.\p"
	.string "Aún ahora, la edad no ha mermado\n"
	.string "sus habilidades.\p"
	.string "De hecho, sus movimientos POKéMON\n"
	.string "están más pulidos.\p"
	.string "Pero... por alguna razón, no puedo\n"
	.string "evitar sentir esto...\p"
	.string "El tiempo es tan cruel...$"

TrainerHill_Courtyard_Text_SoftboiledDesc::
	.string "Recupera hasta\n"
	.string "la mitad de los\n"
	.string "PS máximos del usuario.$"

TrainerHill_Courtyard_Text_SeismicTossDesc::
	.string "Inflige un daño\n"
	.string "idéntico al\n"
	.string "nivel del usuario.$"

TrainerHill_Courtyard_Text_DreamEaterDesc::
	.string "Recupera la mitad\n"
	.string "del daño infligido\n"
	.string "a un rival dormido.$"

TrainerHill_Courtyard_Text_MegaPunchDesc::
	.string "Un golpe fuerte\n"
	.string "lanzado con un\n"
	.string "poder increíble.$"

TrainerHill_Courtyard_Text_MegaKickDesc::
	.string "Una patada muy\n"
	.string "poderosa y con\n"
	.string "fuerza intensa.$"

TrainerHill_Courtyard_Text_BodySlamDesc::
	.string "Un placaje total\n"
	.string "que puede causar\n"
	.string "parálisis.$"

TrainerHill_Courtyard_Text_RockSlideDesc::
	.string "Lanza rocas\n"
	.string "grandes. Puede\n"
	.string "causar retroceso.$"

TrainerHill_Courtyard_Text_CounterDesc::
	.string "Devuelve un golpe\n"
	.string "físico con el\n"
	.string "doble de poder.$"

TrainerHill_Courtyard_Text_ThunderWaveDesc::
	.string "Una descarga\n"
	.string "eléctrica débil\n"
	.string "que paraliza.$"

TrainerHill_Courtyard_Text_SwordsDanceDesc::
	.string "Una danza de\n"
	.string "lucha que sube\n"
	.string "mucho el ATAQUE.$"

TrainerHill_Courtyard_Text_DefenseCurlDesc::
	.string "Se encoge para\n"
	.string "cubrirse y subir\n"
	.string "la DEFENSA.$"

TrainerHill_Courtyard_Text_SnoreDesc::
	.string "Un ataque fuerte\n"
	.string "que solo se usa\n"
	.string "estando dormido.$"

TrainerHill_Courtyard_Text_MudSlapDesc::
	.string "Lanza lodo a la cara\n"
	.string "del rival para\n"
	.string "bajar su precisión.$"

TrainerHill_Courtyard_Text_SwiftDesc::
	.string "Lanza rayos en\n"
	.string "forma de estrella\n"
	.string "que nunca fallan.$"

TrainerHill_Courtyard_Text_IcyWindDesc::
	.string "Ataque gélido que\n"
	.string "reduce la VELOCIDAD\n"
	.string "del rival.$"

TrainerHill_Courtyard_Text_EndureDesc::
	.string "Resiste cualquier\n"
	.string "ataque un turno y\n"
	.string "queda con 1 PS.$"

TrainerHill_Courtyard_Text_PsychUpDesc::
	.string "Copia los efectos\n"
	.string "del rival y se los\n"
	.string "da al usuario.$"

TrainerHill_Courtyard_Text_IcePunchDesc::
	.string "Un puño helado que\n"
	.string "puede congelar al\n"
	.string "rival.$"

TrainerHill_Courtyard_Text_ThunderPunchDesc::
	.string "Un puño eléctrico\n"
	.string "que puede paralizar\n"
	.string "al rival.$"

TrainerHill_Courtyard_Text_FirePunchDesc::
	.string "Un puño ardiente\n"
	.string "que puede quemar\n"
	.string "al rival.$"

TrainerHill_Courtyard_Text_ElementalTutorIntro::
	.string "Zzzzzz…\p"
	.string "¿Qué? ¿Cómo? ¿Qué?\p"
	.string "Oh, perdón, me dormía un poco.\p"
	.string "Soy el TUTOR ELEMENTAL.\p"
	.string "Puedo enseñar los movimientos más\n"
	.string "fuertes a POKéMON de tipo PLANTA,\l"
	.string "FUEGO y AGUA.\p"
	.string "¿Vienes a aprender un poder así\n"
	.string "de fuerte?$"

TrainerHill_Courtyard_Text_ElementalTutorWelcomeBack:
	.string "Zzzzzz…\p"
	.string "¿Qué? ¿Cómo? ¿Qué? ¿Quién?\p"
	.string "Oh, ¿vienes a aprender el\n"
	.string "poder de mis mejores movimientos?$"

TrainerHill_Courtyard_Text_TeachWhichMoveElemental::
	.string "¿Qué movimiento crees que es el\n"
	.string "ideal para tu POKéMON?$"

TrainerHill_Courtyard_Text_StrongElementalMoveDesc::
	.string "Es poderoso, pero\n"
	.string "deja al usuario\n"
	.string "sin moverse un turno.$"

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkWelcome::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special ShowBattlePointsWindow
	return

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkGoodbye::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ThankYouVisitWithPoints, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryGivePrize
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_DontHaveEnoughPoints, MSGBOX_DEFAULT
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR2_CLERK, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor2
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_VITAMIN_CLERK, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryGivePrize::
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryGiveDecor
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR2_CLERK, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryGiveDecor
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryGiveItem
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryGiveDecor::
	checkdecorspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_NoRoomForDecor
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	adddecoration VAR_0x8009
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_WellSendItToPC, MSGBOX_DEFAULT
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor2
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_NoRoomForDecor::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_PCIsFull, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryGiveItem::
	checkitemspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_BagFull
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	additem VAR_0x8009
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_HereIsYourPrize, MSGBOX_DEFAULT
	goto_if_eq VAR_TEMP_2, EXCHANGE_CORNER_VITAMIN_CLERK, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_BagFull::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_DontHaveSpaceToHoldIt, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_DecorClerk1::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_DECOR1_CLERK
	call TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_DECOR_VENDOR_1
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_KissPoster
	case 1, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_KissCushion
	case 2, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_SmoochumDoll
	case 3, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TogepiDoll
	case 4, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_MeowthDoll
	case 5, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClefairyDoll
	case 6, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_DittoDoll
	case 7, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_CyndaquilDoll
	case 8, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChikoritaDoll
	case 9, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TotodileDoll
	case 10, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_KissPoster::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmKissPoster, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 16
	setvar VAR_0x8009, DECOR_KISS_POSTER
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_KissCushion::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmKissCushion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 32
	setvar VAR_0x8009, DECOR_KISS_CUSHION
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_SmoochumDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmSmoochumDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 32
	setvar VAR_0x8009, DECOR_SMOOCHUM_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TogepiDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmTogepiDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_TOGEPI_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_MeowthDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmMeowthDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_MEOWTH_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClefairyDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmClefairyDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_CLEFAIRY_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_DittoDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmDittoDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, DECOR_DITTO_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_CyndaquilDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmCyndaquilDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 80
	setvar VAR_0x8009, DECOR_CYNDAQUIL_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChikoritaDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmChikoritaDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 80
	setvar VAR_0x8009, DECOR_CHIKORITA_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TotodileDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmTotodileDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor1
	setvar VAR_0x8008, 80
	setvar VAR_0x8009, DECOR_TOTODILE_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_DecorClerk2::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_DECOR2_CLERK
	call TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor2
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor2::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_DECOR_VENDOR_2
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_LaprasDoll
	case 1, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_SnorlaxDoll
	case 2, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_VenusaurDoll
	case 3, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_CharizardDoll
	case 4, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_BlastoiseDoll
	case 5, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_LaprasDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmLaprasDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 128
	setvar VAR_0x8009, DECOR_LAPRAS_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_SnorlaxDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmSnorlaxDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 128
	setvar VAR_0x8009, DECOR_SNORLAX_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_VenusaurDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmVenusaurDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 256
	setvar VAR_0x8009, DECOR_VENUSAUR_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_CharizardDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmCharizardDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 256
	setvar VAR_0x8009, DECOR_CHARIZARD_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_BlastoiseDoll::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmBlastoiseDoll, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseDecor2
	setvar VAR_0x8008, 256
	setvar VAR_0x8009, DECOR_BLASTOISE_DOLL
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_VitaminClerk::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_VITAMIN_CLERK
	call TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_VITAMIN_VENDOR
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Protein
	case 1, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Calcium
	case 2, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Iron
	case 3, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Zinc
	case 4, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Carbos
	case 5, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_HpUp
	case 6, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_YouAlreadyHaveThis::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_YouAlreadyHaveThis, MSGBOX_DEFAULT
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Protein::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmProtein, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_PROTEIN
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Calcium::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmCalcium, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_CALCIUM
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Iron::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmIron, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_IRON
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Zinc::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmZinc, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_ZINC
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Carbos::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmCarbos, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_CARBOS
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_HpUp::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmHpUp, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseVitamin
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, ITEM_HP_UP
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_HoldItemClerk::
	lock
	faceplayer
	setvar VAR_TEMP_2, EXCHANGE_CORNER_HOLD_ITEM_CLERK
	call TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkWelcome
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem::
	setvar VAR_0x8004, SCROLL_MULTI_BF_EXCHANGE_CORNER_HOLD_ITEM_VENDOR
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Leftovers
	case 1, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_WhiteHerb
	case 2, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_QuickClaw
	case 3, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_MentalHerb
	case 4, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Brightpowder
	case 5, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChoiceBand
	case 6, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_KingsRock
	case 7, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_FocusBand
	case 8, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ScopeLens
	case 9, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ClerkGoodbye
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Leftovers::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmLeftovers, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_LEFTOVERS
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_WhiteHerb::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmWhiteHerb, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_WHITE_HERB
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_QuickClaw::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmQuickClaw, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_QUICK_CLAW
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_MentalHerb::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmMentalHerb, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 48
	setvar VAR_0x8009, ITEM_MENTAL_HERB
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Brightpowder::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmBrightpowder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_BRIGHT_POWDER
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChoiceBand::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmChoiceBand, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_CHOICE_BAND
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_KingsRock::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmKingsRock, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_KINGS_ROCK
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_FocusBand::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmFocusBand, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_FOCUS_BAND
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ScopeLens::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmScopeLens, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_ChooseHoldItem
	setvar VAR_0x8008, 64
	setvar VAR_0x8009, ITEM_SCOPE_LENS
	goto TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_TryPurchasePrize
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Man::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_GoGetYourOwnDoll, MSGBOX_NPC
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Sailor::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ItemsWillGetMonTougher, MSGBOX_NPC
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_PokefanF::
	lock
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_GetYouAnythingYouWant, MSGBOX_DEFAULT
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_RichBoy::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_WishIHadAllDolls, MSGBOX_NPC
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Girl::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_MoreBattlePointsForRecord, MSGBOX_NPC
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_OldWTMan::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_OldWTMan_Text, MSGBOX_NPC
	end

TrainerHill_Courtyard_ExchangeServiceCorner_Text_YouAlreadyHaveThis:
	.string "Ya tienes este objeto.$"

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_OldWTMan_Text:
	.string "¡Hola! Si buscas el WONDERTRADE,\n"
	.string "está ahora en cada POKéMON\l"
	.string "CENTER. ¡Diviértete!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize:
	.string "Hola, este es el RINCÓN DEL\n"
	.string "SERVICIO DE INTERCAMBIO.\p"
	.string "Cambiamos tus Puntos de Batalla\n"
	.string "por premios geniales.\p"
	.string "Elige un premio de esta lista.$"

@ Unused
TrainerHill_Courtyard_ExchangeServiceCorner_Text_PleaseChoosePrize:
	.string "Elige un premio de esta lista.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmKissPoster:
	.string "Elegiste el PÓSTER DE BESOS.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmKissCushion:
	.string "Elegiste el COJÍN DE BESOS.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmSmoochumDoll:
	.string "Elegiste el MUÑECO SMOOCHUM.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmTogepiDoll:
	.string "Elegiste el MUÑECO TOGEPI.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmMeowthDoll:
	.string "Elegiste el MUÑECO MEOWTH.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmClefairyDoll:
	.string "Elegiste el MUÑECO CLEFAIRY.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmDittoDoll:
	.string "Elegiste el MUÑECO DITTO.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmCyndaquilDoll:
	.string "Elegiste el MUÑECO CYNDAQUIL.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmChikoritaDoll:
	.string "Elegiste el MUÑECO DE CHIKORITA.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmTotodileDoll:
	.string "Elegiste el MUÑECO DE TOTODILE.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmLaprasDoll:
	.string "Elegiste el MUÑECO DE LAPRAS.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmSnorlaxDoll:
	.string "Elegiste el MUÑECO DE SNORLAX.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmVenusaurDoll:
	.string "Elegiste el MUÑECO DE VENUSAUR.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmCharizardDoll:
	.string "Elegiste el MUÑECO DE CHARIZARD.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmBlastoiseDoll:
	.string "Elegiste el MUÑECO DE BLASTOISE.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmProtein:
	.string "Elegiste la PROTEÍNA.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmCalcium:
	.string "Elegiste el CALCIO.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmIron:
	.string "Elegiste el HIERRO.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmZinc:
	.string "Elegiste el ZINC.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmCarbos:
	.string "Elegiste el CARBÓN.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmHpUp:
	.string "Elegiste el VITAMINA HP.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmBrightpowder:
	.string "Elegiste el POLVO LUZ.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmWhiteHerb:
	.string "Elegiste la HIERBA BLANCA.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmQuickClaw:
	.string "Elegiste la GARRA RÁPIDA.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmMentalHerb:
	.string "Elegiste la HIERBA MENTAL.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmChoiceBand:
	.string "Elegiste la PRENDA ELECCIÓN.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmKingsRock:
	.string "Elegiste la ROCA REAL.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmFocusBand:
	.string "Elegiste la PRENDA ENFOQUE.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmScopeLens:
	.string "Elegiste la LENTE MIRADA.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ConfirmLeftovers:
	.string "Elegiste las SOBRAS.\n"
	.string "¿Es correcto?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_WellSendItToPC:
	.string "¡Gracias!\n"
	.string "Lo enviaremos a tu PC en casa.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_HereIsYourPrize:
	.string "¡Aquí tienes tu premio!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_DontHaveEnoughPoints:
	.string "Lo siento mucho…\n"
	.string "No tienes bastantes Puntos de Batalla…$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_PCIsFull:
	.string "Lo siento mucho...\n"
	.string "Tu PC parece estar llena...$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_DontHaveSpaceToHoldIt:
	.string "Lo siento mucho...\n"
	.string "No tienes espacio para guardarlo...$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ThankYouVisitWithPoints:
	.string "Muchas gracias.\p"
	.string "Vuelve cuando hayas ahorrado\n"
	.string "Puntos de Batalla.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_WishIHadAllDolls:
	.string "¡Oh, son tan lindos!\n"
	.string "¡Desearía tenerlos!\l"
	.string "¡Cojines lindos!\l"
	.string "¡Muñecos grandes!\l"
	.string "¡Muñecos pequeños!\l"
	.string "¡Quisiera tenerlos todos!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_GetYouAnythingYouWant:
	.string "¡Déjaselo a mamá!\p"
	.string "Si es algo que quieres, ¡haré lo\n"
	.string "que sea para conseguirlo, cielo!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ItemsWillGetMonTougher:
	.string "Si consigo los objetos de aquí,\n"
	.string "mis POKéMON serán más fuertes.\p"
	.string "¡Seguro que sí!\n"
	.string "¡No hay duda de ello!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_GoGetYourOwnDoll:
	.string "¿Eh?\n"
	.string "¿Qué estás mirando?\p"
	.string "No me gusta que mires mi muñeco\n"
	.string "de esa forma.\p"
	.string "¡Si lo quieres, ve por uno tú!\n"
	.string "¿Verdad, SMOOCHUM?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_MoreBattlePointsForRecord:
	.string "¿Lo sabías?\p"
	.string "Si superas tu récord en las\n"
	.string "instalaciones de BATALLA, te darán\l"
	.string "más y más Puntos de Batalla.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_KissPosterDesc::
	.string "Un póster grande de SMOOCHUM.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_KissCushionDesc::
	.string "Un cojín de SMOOCHUM.\n"
	.string "Ponlo en un tapete o escritorio.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_SmoochumDollDesc::
	.string "Un MUÑECO de SMOOCHUM.\n"
	.string "Ponlo en un tapete o escritorio.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_TogepiDollDesc::
	.string "Un MUÑECO de TOGEPI.\n"
	.string "Ponlo en un tapete o escritorio.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_MeowthDollDesc::
	.string "Un MUÑECO de MEOWTH.\n"
	.string "Ponlo en un tapete o escritorio.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ClefairyDollDesc::
	.string "Un MUÑECO de CLEFAIRY.\n"
	.string "Ponlo en un tapete o escritorio.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_DittoDollDesc::
	.string "Un MUÑECO de DITTO.\n"
	.string "Ponlo en un tapete o escritorio.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_CyndaquilDollDesc::
	.string "MUÑECO DE CYNDAQUIL.\n"
	.string "Ponlo en un tapete o escritorio.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ChikoritaDollDesc::
	.string "MUÑECO DE CHIKORITA.\n"
	.string "Ponlo en un tapete o escritorio.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_TotodileDollDesc::
	.string "MUÑECO DE TOTODILE.\n"
	.string "Ponlo en un tapete o escritorio.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_LargeDollDesc::
	.string "UN MUÑECO grande.\n"
	.string "Ponlo en un tapete o escritorio.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ProteinDesc::
	.string "Un ticket extraño que te llevará\n"
	.string "a una isla abandonada.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_CalciumDesc::
	.string "Un ticket extraño que te llevará\n"
	.string "a una isla abandonada.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_IronDesc::
	.string "Un ticket extraño que te llevará\n"
	.string "a una isla abandonada.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ZincDesc::
	.string "¿Un... mapa viejo? Tal vez\n"
	.string "te lleve a algún lugar.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_CarbosDesc::
	.string "x10 EV, pero reduce la velocidad.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_HPUpDesc::
	.string "Una caja peculiar fabricada\n"
	.string "por SILPH CO.$"  

TrainerHill_Courtyard_ExchangeServiceCorner_Text_LeftoversDesc::
	.string "Objeto que recupera PS poco a\n"
	.string "poco en combate.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_WhiteHerbDesc::
	.string "Objeto que restaura cualquier\n"
	.string "estadística bajada.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_QuickClawDesc::
	.string "Objeto que a veces permite\n"
	.string "atacar primero.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_MentalHerbDesc::
	.string "Objeto que cura el enamoramiento\n"
	.string "del POKéMON.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_BrightpowderDesc::
	.string "Objeto que lanza una mirada para\n"
	.string "bajar la precisión.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ChoiceBandDesc::
	.string "Sube el poder de un movimiento,\n"
	.string "pero solo permite usar ese.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_KingsRockDesc::
	.string "Objeto que puede causar retroceso\n"
	.string "al golpear al rival.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_FocusBandDesc::
	.string "Objeto que ocasionalmente\n"
	.string "evita el desmayo.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ScopeLensDesc::
	.string "Objeto que aumenta la tasa de\n"
	.string "golpes críticos.$"
