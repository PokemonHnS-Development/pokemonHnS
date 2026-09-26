.set LOCALID_EXPERT_M, 4
.set LOCALID_TWIN, 5
.set LOCALID_SCHOOL_KID_M, 7
.set LOCALID_PSYCHIC_M, 8

DewfordTown_Hall_MapScripts::
	.byte 0

DewfordTown_Hall_EventScript_Girl::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special IsTrendyPhraseBoring
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Hall_EventScript_GirlBoredOfTrend
	msgbox DewfordTown_Hall_Text_CantImagineLifeWithoutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_GirlBoredOfTrend::
	msgbox DewfordTown_Hall_Text_GettingBoredOfTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Woman::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TeachingMonAboutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Man::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special BufferDeepLinkPhrase
	msgbox DewfordTown_Hall_Text_DeepLinkBetweenXAndY, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_Hall_EventScript_ConfirmTrendLink
	goto_if_eq VAR_RESULT, NO, DewfordTown_Hall_EventScript_RejectTrendLink
	end

DewfordTown_Hall_EventScript_ConfirmTrendLink::
	msgbox DewfordTown_Hall_Text_MyHunchWasRight, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_RejectTrendLink::
	msgbox DewfordTown_Hall_Text_NotEasyToKeepUp, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_ExpertM::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TVShowAboutTrend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_EXPERT_M, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_Twin::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TWIN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_LittleBoy::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_CollectTrendMerchandise, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Bookshelf::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_BooksAboutTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_Painting::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_ScreamTitle
	case 4, DewfordTown_Hall_EventScript_ScreamTitle
	case 1, DewfordTown_Hall_EventScript_SmileTitle
	case 5, DewfordTown_Hall_EventScript_ScreamTitle
	case 2, DewfordTown_Hall_EventScript_LastTitle
	case 6, DewfordTown_Hall_EventScript_LastTitle
	case 3, DewfordTown_Hall_EventScript_BirthTitle
	case 7, DewfordTown_Hall_EventScript_LastTitle
	end

DewfordTown_Hall_EventScript_ScreamTitle::
	msgbox DewfordTown_Hall_Text_TrendsScream, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SmileTitle::
	msgbox DewfordTown_Hall_Text_TrendsSmile, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_LastTitle::
	msgbox DewfordTown_Hall_Text_LastTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_BirthTitle::
	msgbox DewfordTown_Hall_Text_BirthOfTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SchoolKidM::
	lockall
	setvar VAR_0x8008, 0
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_PsychicM::
	lockall
	setvar VAR_0x8008, 1
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_DoTrendDebate::
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_TrendDebate1
	case 1, DewfordTown_Hall_EventScript_TrendDebate1
	case 2, DewfordTown_Hall_EventScript_TrendDebate2
	case 3, DewfordTown_Hall_EventScript_TrendDebate2
	case 4, DewfordTown_Hall_EventScript_TrendDebate3
	case 5, DewfordTown_Hall_EventScript_TrendDebate3
	case 6, DewfordTown_Hall_EventScript_TrendDebate4
	case 7, DewfordTown_Hall_EventScript_TrendDebate5
	end

DewfordTown_Hall_EventScript_TrendDebate1::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_SawTrendCoolestThing, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_AllegedTrendNotAuthentic, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate2::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_ComposedTrendThemeSong, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WorkOnYourSinging, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate3::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_OrganizeTrendParty, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_BrilliantIndeed, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate4::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_TrendHasBecomePartOfLife, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate5::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WellBeTrendDuo, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_DontMovePlayer1::
	return

DewfordTown_Hall_EventScript_DebateReact1::
	applymovement LOCALID_PSYCHIC_M, DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactWest
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_DontMovePlayer2
	end

DewfordTown_Hall_EventScript_PlayerReactWest::
	goto_if_eq VAR_FACING, DIR_EAST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

DewfordTown_Hall_EventScript_DontMovePlayer2::
	return

DewfordTown_Hall_EventScript_DebateReact2::
	applymovement LOCALID_SCHOOL_KID_M, DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactNorthSouth
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_PlayerReactEast
	end

DewfordTown_Hall_EventScript_PlayerReactNorthSouth::
	call_if_eq VAR_FACING, DIR_NORTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp
	call_if_eq VAR_FACING, DIR_SOUTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerReactEast::
	goto_if_eq VAR_FACING, DIR_WEST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft:
	walk_in_place_left
	step_end

DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight:
	walk_in_place_right
	step_end

DewfordTown_Hall_EventScript_SludgeBombMan::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	goto_if_set FLAG_RECEIVED_TM_SLUDGE_BOMB, DewfordTown_Hall_EventScript_ReceivedSludgeBomb
	msgbox DewfordTown_Hall_Text_GiveYouSludgeBomb, MSGBOX_DEFAULT
	giveitem ITEM_TM_SLUDGE_BOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SLUDGE_BOMB
	release
	end

DewfordTown_Hall_EventScript_ReceivedSludgeBomb::
	msgbox DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_Text_CantImagineLifeWithoutTrend:
	.string "¿Qué está de moda? ¡Tiene que ser\n"
	.string "{STR_VAR_1}!\p"
	.string "¡No imagino la vida\n"
	.string "sin {STR_VAR_1}!$"

DewfordTown_Hall_Text_GettingBoredOfTrend:
	.string "¿Qué está de moda? ¡Tiene que ser\n"
	.string "{STR_VAR_1}!\p"
	.string "Pero ya me estoy aburriendo.\p"
	.string "Buscaré la siguiente tendencia.$"

DewfordTown_Hall_Text_TeachingMonAboutTrend:
	.string "Le enseño a mi POKéMON sobre\n"
	.string "{STR_VAR_1},\l"
	.string "pero no va muy bien.\p"
	.string "Creo que es demasiado.$"

DewfordTown_Hall_Text_DeepLinkBetweenXAndY:
	.string "Estudio lo más moderno y trendy:\n"
	.string "{STR_VAR_1}.\p"
	.string "¿Es cierto que hay un vínculo\n"
	.string "entre {STR_VAR_1}\l"
	.string "y {STR_VAR_2}?$"

DewfordTown_Hall_Text_MyHunchWasRight:
	.string "¡Oh!\n"
	.string "¡Mi presentimiento era correcto!\p"
	.string "¡Estoy más cerca de estar a la moda,\n"
	.string "guau!$"

DewfordTown_Hall_Text_NotEasyToKeepUp:
	.string "¡¿Qué?!\n"
	.string "¡¿Es así?!\p"
	.string "¡No es fácil para alguien mayor\n"
	.string "seguir las tendencias!$"

DewfordTown_Hall_Text_TVShowAboutTrend:
	.string "Todo este asunto sobre\n"
	.string "{STR_VAR_1}...\l"
	.string "¿No hay un programa de TV sobre eso?$"

DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea:
	.string "Al otro lado del mar...\p"
	.string "¿Será {STR_VAR_1}\n"
	.string "aún más popular?$"

DewfordTown_Hall_Text_CollectTrendMerchandise:
	.string "Colecciono cosas\n"
	.string "oficiales de “{STR_VAR_1}”\l"
	.string "con licencia.\p"
	.string "Tengo MUÑECOS\n"
	.string "oficiales de “{STR_VAR_1}”…\p"
	.string "Ropa oficial “{STR_VAR_1}”\n"
	.string "de la marca…\p"
	.string "Y libros ilustrados\n"
	.string "de “{STR_VAR_1}”\l"
	.string "con licencia oficial.\p"
	.string "¡Jeje, son míos!\n"
	.string "¡No comparto nada contigo!$"

DewfordTown_Hall_Text_BooksAboutTrend:
	.string "IDENTIFICANDO BUENO\n"
	.string "“{STR_VAR_1}” &\l"
	.string "MALO “{STR_VAR_1}”…\p"
	.string "EL VÍNCULO ENTRE\n"
	.string "“{STR_VAR_1}” Y\l"
	.string "POKéMON…\p"
	.string "ÚTIL\n"
	.string "“{STR_VAR_1}”…\p"
	.string "Está lleno de libros sobre\n"
	.string "“{STR_VAR_1}.”$"

DewfordTown_Hall_Text_TrendsScream:
	.string "{STR_VAR_1}\n"
	.string "GRITA es el título.$"

DewfordTown_Hall_Text_TrendsSmile:
	.string "{STR_VAR_1}\n"
	.string "SONRÍE es el título.$"

DewfordTown_Hall_Text_LastTrend:
	.string "Se titula “EL ÚLTIMO\n"
	.string "{STR_VAR_1}”.$"

DewfordTown_Hall_Text_BirthOfTrend:
	.string "Se titula “EL NACIMIENTO\n"
	.string "DE {STR_VAR_1}”.$"

DewfordTown_Hall_Text_SawTrendCoolestThing:
	.string "¡Vi a “{STR_VAR_1}”!\n"
	.string "¿Genial, no?\p"
	.string "¡Es lo más increíble que hay!\p"
	.string "¡Fue asombroso!\n"
	.string "¡Era el verdadero, sí!$"

DewfordTown_Hall_Text_AllegedTrendNotAuthentic:
	.string "Oh, no, no, no.\p"
	.string "Ese supuesto\n"
	.string "“{STR_VAR_1}”\l"
	.string "que dices haber visto no es.\p"
	.string "El auténtico es mucho más…\n"
	.string "¿Cómo decirlo?\l"
	.string "¡Afilado y a la vez suave!\p"
	.string "Bah, no importa. ¡Es increíble!$"

DewfordTown_Hall_Text_ComposedTrendThemeSong:
	.string "Oye, escucha, compuse un tema\n"
	.string "para “{STR_VAR_1}”.\p"
	.string "“{STR_VAR_1}”\n"
	.string "es muy popular ahora.\p"
	.string "¡Bien, escucha!\n"
	.string "… …\p"
	.string "¡Oh!\n"
	.string "{STR_VAR_1}!\p"
	.string "¡Maravilloso\n"
	.string "{STR_VAR_1}!$"

DewfordTown_Hall_Text_WorkOnYourSinging:
	.string "… …\p"
	.string "Digo, amigo, te convendría\n"
	.string "mejorar tu canto antes de\l"
	.string "intentar cantar\l"
	.string "“{STR_VAR_1}.”$"

DewfordTown_Hall_Text_OrganizeTrendParty:
	.string "Como decía hace un momento, we\n"
	.string "deberíamos reunirnos y organizar una\l"
	.string "fiesta de “{STR_VAR_1}”\l"
	.string "en la isla.$"

DewfordTown_Hall_Text_BrilliantIndeed:
	.string "¡Oh, una idea fantástica!\p"
	.string "Se decidirá de una vez por todas\n"
	.string "quién es el mejor en\l"
	.string "{STR_VAR_1}.\l"
	.string "¡Brillante, en verdad!\p"
	.string "Desde hoy, nuestras vidas girarán\n"
	.string "en torno a {STR_VAR_1}!$"

DewfordTown_Hall_Text_TrendHasBecomePartOfLife:
	.string "Pero estaba pensando...\p"
	.string "¿No estarías de acuerdo en que\n"
	.string "“{STR_VAR_1}” ha\l"
	.string "pasado de ser una moda a\l"
	.string "ser parte de nuestra vida diaria?$"

DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind:
	.string "¿Perdón?\n"
	.string "¿Tanto así, qué?\p"
	.string "Aun así, es cierto que\n"
	.string "“{STR_VAR_1}”\l"
	.string "te preocupa mucho, ya sea\l"
	.string "estando despierto o dormido.\p"
	.string "Sin duda, eres el\n"
	.string "“{STR_VAR_1}”\l"
	.string "PROFESSOR, ¡viejo amigo!$"

DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible:
	.string "Si hacemos equipo como un combo,\n"
	.string "seremos invencibles en todo lo\l"
	.string "relacionado con {STR_VAR_1}!$"

DewfordTown_Hall_Text_WellBeTrendDuo:
	.string "¡Exacto, amigo mío!\p"
	.string "¡Seremos el\n"
	.string "DÚO {STR_VAR_1}!\p"
	.string "¿No es una imagen genial?\n"
	.string "¡Jajaja!$"

DewfordTown_Hall_Text_GiveYouSludgeBomb:
	.string "Para mí, SLUDGE BOMB es lo más\n"
	.string "popular. Es el mejor.\p"
	.string "¿Eh? ¿Me dices que no\n"
	.string "conoces SLUDGE BOMB?\p"
	.string "Eso es lamentable.\n"
	.string "Te daré uno.$"

DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo:
	.string "Amo SLUDGE BOMB.\p"
	.string "Pero los POKéMON con el movimiento\n"
	.string "“{STR_VAR_1}”\l"
	.string "también están de moda.$"

