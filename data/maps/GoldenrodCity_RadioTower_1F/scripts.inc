.set LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, 6
.set LOCALID_GOLDENROD_RADIOTOWER_GRUNT, 3
.set LOCALID_LOTTERY_CLERK, 2

GoldenrodCity_RadioTower_1F_MapScripts::
	.byte 0

RadioTower1F_EventScript_Grunt::
	lock
	faceplayer
	msgbox RadioTower1F_Text_GruntM3Seen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_2,  RadioTower1F_Text_GruntM3Beaten
	msgbox RadioTower1F_Text_GruntM3After, MSGBOX_AUTOCLOSE
	turnobject LOCALID_GOLDENROD_RADIOTOWER_GRUNT, DIR_EAST
	applymovement2 LOCALID_GOLDENROD_RADIOTOWER_GRUNT, RadioTower1F_Movement_Rocket
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_GOLDENROD_RADIOTOWER_GRUNT
	setflag FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	release
	end

RadioTower1F_Movement_Rocket::
	walk_in_place_right
	step_end

RadioTower1F_EventScript_Lass::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_Youngster::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_Whitney::
	lock
	faceplayer
	msgbox RadioTower1F_Text_Whitney1, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, DIR_SOUTH
	release
	end

RadioTower1F_Text_Whitney1::
	.string "WHITNEY: ¡Hola!\p"
	.string "¡Me llamo WHITNEY!\p"
	.string "Supe del QUIZ para ganar una\n"
	.string "RADIO, así que vine por\l"
	.string "una...\p"
	.string "¡Pero este QUIZ es muy difícil!$"

RadioTower1F_Text_Whitney2::
	.string "WHITNEY: ¡Vaya, lo lograste!\p"
	.string "¡Creí que la respuesta a la tercera\n"
	.string "pregunta eran las bayas!\l"
	.string "¡Ups!\p"
	.string "¡Es hora de volver al GIMNASIO!$"

RadioTower1F_EventScript_Reception::
	lock
	faceplayer
	msgbox RadioTower1F_Text_ReceptionistWelcome, MSGBOX_DEFAULT
	goto_if_unset FLAG_ENABLE_RADIO, RadioTower1F_EventScript_ReceptionOfferQuiz
	msgbox RadioTower1F_Text_ReceptionistNoTours, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionOfferQuiz::
	msgbox RadioTower1F_Text_RadioCardWomanOfferQuiz, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz1
	msgbox RadioTower1F_Text_DeclineQuiz, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz1::
	msgbox RadioTower1F_Text_QuizQuestion1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz2
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz2::
	msgbox RadioTower1F_Text_QuizQuestion2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz3
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz3::
	msgbox RadioTower1F_Text_QuizQuestion3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_ReceptionQuiz4
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz4::
	msgbox RadioTower1F_Text_QuizQuestion4, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, RadioTower1F_EventScript_ReceptionQuiz5
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionQuiz5::
	msgbox RadioTower1F_Text_QuizQuestion5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, RadioTower1F_EventScript_ReceptionGiveRadio
	msgbox RadioTower1F_Text_WrongAnswer, MSGBOX_DEFAULT
	closemessage
	release
	end

RadioTower1F_EventScript_ReceptionGiveRadio::
	msgbox RadioTower1F_Text_QuizWin, MSGBOX_DEFAULT
	closemessage
	playfanfare MUS_OBTAIN_ITEM
	giveitem ITEM_RADIO
	waitfanfare
	msgbox RadioTower1F_Text_TuneIn, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, DIR_EAST
	delay 20
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox RadioTower1F_Text_Whitney2, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_GOLDENROD_RADIOTOWER_WHITNEY, GoldenrodCity_RadioTower_4F_Movement_WhitneyLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_GOLDENROD_RADIOTOWER_WHITNEY
	setflag FLAG_ENABLE_RADIO
	setflag FLAG_HIDE_GOLDENROD_BEAUTY
	setvar VAR_GOLDENROD_CITY_STATE, 2
	release
	end

GoldenrodCity_RadioTower_4F_Movement_WhitneyLeave:
	face_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_in_place_down
	step_end

GoldenrodCity_RadioTower_1F_EventScript_Sign::
	lock
	msgbox RadioTower1F_Text_Directory, MSGBOX_SIGN
	closemessage
	release
	end

RadioTower1F_Text_ReceptionistWelcome:
    .string "¡Bienvenido!$"

RadioTower1F_Text_ReceptionistNoTours:
    .string "Hola. Lo siento, pero hoy no\n"
    .string "estamos dando recorridos.$"

RadioTower1F_Text_RadioCardWomanOfferQuiz:
    .string "Tenemos una campaña de QUIZ\n"
    .string "especial ahora mismo.\p"
    .string "Responde cinco preguntas bien para\n"
    .string "ganar una RADIO.\p"
    .string "Tú y tu POKéMON podrán usarla para\n"
    .string "oír música donde sea.\p"
    .string "¿Quieres hacer el QUIZ?$"

RadioTower1F_Text_QuizQuestion1:
    .string "Pregunta 1:\p"
    .string "¿Hay algún POKéMON que aparezca\n"
    .string "solo durante el día?$"

RadioTower1F_Text_QuizQuestion2:
    .string "¡Correcto!\n"
    .string "Pregunta 2:\p"
    .string "¿Es correcta esta frase?\p"
    .string "No puedes comprar BAYAS en un MART.$"

RadioTower1F_Text_QuizQuestion3:
    .string "¡Exacto!\n"
    .string "Pregunta 3:\p"
    .string "¿KURT, el creador de POKéBALL, usa\n"
	.string "bayas como ingredientes?$"

RadioTower1F_Text_QuizQuestion4:
    .string "¡Todo va bien!\n"
    .string "Pregunta 4:\p"
    .string "¿Es FALKNER el LÍDER del GIMNASIO\n"
    .string "de CIUDAD MALVA que usa aves?$"

RadioTower1F_Text_QuizQuestion5:
    .string "¡Wow! ¡Otra vez bien!\n"
    .string "Aquí está la pregunta final:\p"
    .string "¿Las máquinas de GOLDENROD tienen\n"
    .string "a CHARMANDER en sus rodillos?$"

RadioTower1F_Text_QuizWin:
    .string "¡Bingo! ¡Lo lograste!\n"
    .string "¡Felicidades!\p"
    .string "¡Aquí tienes tu premio, una RADIO!$"

RadioTower1F_Text_PokegearRadio:
    .string "¡El POKéGEAR de {PLAYER} ahora\n"
    .string "también sirve como RADIO!$"

RadioTower1F_Text_TuneIn:
    .string "Sintoniza nuestros programas RADIO.$"

RadioTower1F_Text_WrongAnswer:
    .string "Vaya, vaya.\n"
    .string "Lo siento, pero fallaste.\p"
    .string "¡Por favor, intenta de nuevo!$"

RadioTower1F_Text_DeclineQuiz:
    .string "Oh. Ya veo. Búscame si\n"
    .string "cambias de opinión.$"

RadioTower1F_Text_Lass:
    .string "BEN es un DJ fabuloso.\p"
    .string "¡Su dulce voz me derrite!$"

RadioTower1F_Text_Youngster:
    .string "Amo a MARY, de POKéMON TALK.\p"
    .string "Aunque solo conozco su voz.\n"
    .string "$"

RadioTower1F_Text_GruntM3Seen:
    .string "¡Al fin tomamos la\n"
    .string "RADIO TOWER!\p"
    .string "¡Todos sentirán el verdadero terror\n"
    .string "del TEAM ROCKET!\p"
    .string "¡Verán lo aterradores que somos!$"

RadioTower1F_Text_GruntM3Beaten:
    .string "¡Muy fuerte! Lo siento, jefe…$"

RadioTower1F_Text_GruntM3After:
    .string "Eres muy fuerte.\p"
    .string "El plan podría arruinarse. Debo\n"
    .string "avisar a los demás…$"

RadioTower1F_Text_Directory:
    .string "1F RECEPCIÓN\n"
    .string "2F VENTAS\p"
    .string "3F PERSONAL\n"
    .string "4F PRODUCCIÓN\p"
    .string "5F OFICINA DIRECTOR$"


GoldenrodCity_RadioTower_1F_EventScript_LotteryClerk::
	lock
	faceplayer
	dotimebasedevents
	goto_if_ne VAR_POKELOT_PRIZE_ITEM, ITEM_NONE, GoldenrodCity_RadioTower_1F_EventScript_GivePrizeFromEarlier
	goto_if_set FLAG_DAILY_PICKED_LOTO_TICKET, GoldenrodCity_RadioTower_1F_EventScript_ComeBackTomorrow
	msgbox GoldenrodCity_RadioTower_1F_Text_LotteryCornerDrawTicket, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain
	setflag FLAG_DAILY_PICKED_LOTO_TICKET
	message GoldenrodCity_RadioTower_1F_Text_PleasePickTicket
	waitmessage
	special RetrieveLotteryNumber
	copyvar VAR_0x8008, VAR_RESULT
	special BufferLottoTicketNumber
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketNumberIsXPleaseWait, MSGBOX_DEFAULT
	applymovement 4, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	playse SE_PC_ON
	@special DoLotteryCornerComputerEffect
	special PickLotteryCornerTicket
	delay 220
	@special EndLotteryCornerComputerEffect
	delay 10
	applymovement 4, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_eq VAR_0x8004, 0, GoldenrodCity_RadioTower_1F_EventScript_NoMatch
	incrementgamestat GAME_STAT_WON_POKEMON_LOTTERY
	call_if_eq VAR_0x8006, 0, GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPartyMon
	call_if_eq VAR_0x8006, 1, GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPCMon
	bufferitemname STR_VAR_1, VAR_0x8005
	call_if_eq VAR_0x8004, 1, GoldenrodCity_RadioTower_1F_EventScript_TwoDigitMatch
	call_if_eq VAR_0x8004, 2, GoldenrodCity_RadioTower_1F_EventScript_ThreeDigitMatch
	call_if_eq VAR_0x8004, 3, GoldenrodCity_RadioTower_1F_EventScript_FourDigitMatch
	call_if_eq VAR_0x8004, 4, GoldenrodCity_RadioTower_1F_EventScript_FullMatch
	giveitem VAR_0x8005
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_RadioTower_1F_EventScript_RecordPrizeNoRoom
	special TryPutLotteryWinnerReportOnAir
	goto GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2
	end

GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPartyMon::
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketMatchesPartyMon, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_TicketMatchPCMon::
	msgbox GoldenrodCity_RadioTower_1F_Text_TicketMatchesPCMon, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_ComeBackTomorrow::
	msgbox GoldenrodCity_RadioTower_1F_Text_ComeBackTomorrow, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain::
	msgbox GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_NoMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_NoNumbersMatched, MSGBOX_DEFAULT
	goto GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2
	end

GoldenrodCity_RadioTower_1F_EventScript_PleaseVisitAgain2::
	msgbox GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain2, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_TwoDigitMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_TwoDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_ThreeDigitMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_ThreeDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_FourDigitMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_FourDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_FullMatch::
	msgbox GoldenrodCity_RadioTower_1F_Text_AllFiveDigitsMatched, MSGBOX_DEFAULT
	return

GoldenrodCity_RadioTower_1F_EventScript_RecordPrizeNoRoom::
	copyvar VAR_POKELOT_PRIZE_PLACE, VAR_0x8004
	copyvar VAR_POKELOT_PRIZE_ITEM, VAR_0x8005
	goto GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize
	end

GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize::
	msgbox GoldenrodCity_RadioTower_1F_Text_NoRoomForThis, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_RadioTower_1F_EventScript_GivePrizeFromEarlier::
	msgbox GoldenrodCity_RadioTower_1F_Text_PrizeWeveBeenHolding, MSGBOX_DEFAULT
	giveitem VAR_POKELOT_PRIZE_ITEM
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_RadioTower_1F_EventScript_NoRoomForPrize
	copyvar VAR_0x8004, VAR_POKELOT_PRIZE_PLACE
	copyvar VAR_0x8005, VAR_POKELOT_PRIZE_ITEM
	special TryPutLotteryWinnerReportOnAir
	setvar VAR_POKELOT_PRIZE_ITEM, ITEM_NONE
	setvar VAR_POKELOT_PRIZE_PLACE, 0
	release
	end

GoldenrodCity_RadioTower_1F_Text_LotteryCornerDrawTicket:
	.string "Es el RINCÓN DE LOTERÍA POKéMON.\p"
	.string "Si el número del LOTO TICKET coincide\n"
	.string "con el ID de algún POKéMON,\l"
	.string "recibirás un regalo fabuloso.\p"
	.string "¿Quieres sacar un LOTO TICKET\n"
	.string "de POKéMON?$"

GoldenrodCity_RadioTower_1F_Text_ComeBackTomorrow:
	.string "Por favor, vuelve mañana.$"

GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain:
	.string "Por favor, visítanos de nuevo.$"

GoldenrodCity_RadioTower_1F_Text_PleasePickTicket:
	.string "Elige un BOLETO LOTO.\n"
	.string "…{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}…{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}…{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}{PAUSE 0x0F}$"

GoldenrodCity_RadioTower_1F_Text_TicketNumberIsXPleaseWait:
	.string "El número del LOTO TICKET es {STR_VAR_1}.\p"
	.string "Revisaré si este número coincide\n"
	.string "con el ID de alguno de tus\l"
	.string "POKéMON. Por favor, espera.$"

GoldenrodCity_RadioTower_1F_Text_TicketMatchesPartyMon:
	.string "¡Felicidades!\p"
	.string "El ID de tu equipo\n"
	.string "{STR_VAR_1} coincide con el\l"
	.string "número del LOTO TICKET!$"

GoldenrodCity_RadioTower_1F_Text_TicketMatchesPCMon:
	.string "¡Felicidades!\p"
	.string "El ID de tu PC\n"
	.string "{STR_VAR_1} coincide con el\l"
	.string "número del LOTO TICKET!$"

GoldenrodCity_RadioTower_1F_Text_NoNumbersMatched:
	.string "Lo siento.\n"
	.string "Ningún número coincidió.$"

GoldenrodCity_RadioTower_1F_Text_TwoDigitsMatched:
	.string "Coinciden dos dígitos, ¡ganaste el\n"
	.string "tercer premio!\l"
	.string "¡Ganaste {STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_ThreeDigitsMatched:
	.string "Coinciden tres dígitos, ¡ganaste el\n"
	.string "segundo premio!\l"
	.string "¡Ganaste {STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_FourDigitsMatched:
	.string "Coinciden cuatro dígitos, ¡ganaste el\n"
	.string "primer premio!\l"
	.string "¡Ganaste {STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_AllFiveDigitsMatched:
	.string "¡Cielos, los cinco dígitos\n"
	.string "coinciden!\p"
	.string "¡Ganaste el premio mayor!\n"
	.string "¡Ganaste el {STR_VAR_1}!$"

GoldenrodCity_RadioTower_1F_Text_NoRoomForThis:
	.string "¿Oh?\n"
	.string "Parece que no tienes espacio.\p"
	.string "Haz espacio en tu MOCHILA y\n"
	.string "avísame.$"

GoldenrodCity_RadioTower_1F_Text_PrizeWeveBeenHolding:
	.string "¿{PLAYER}?\n"
	.string "Sí, te estaba esperando.\p"
	.string "Este es el premio que guardamos\n"
	.string "para ti.$"

GoldenrodCity_RadioTower_1F_Text_PleaseVisitAgain2:
	.string "Por favor, vuelve a visitarnos.$"


