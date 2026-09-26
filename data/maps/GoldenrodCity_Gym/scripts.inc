.set LOCALID_GOLDENROD_CITY_GYM_BRIDGET, 6

GoldenrodCity_Gym_MapScripts::
	.byte 0
@Carrie, Bridget, Victoria, Samantha, gym guy


GoldenrodCity_Gym_EventScript_Carrie::
	trainerbattle_single TRAINER_CARRIE GoldenrodCity_Gym_Text_LassCarrieSeen, GoldenrodCity_Gym_Text_LassCarrieBeaten
	msgbox GoldenrodCity_Gym_Text_LassCarrieAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Bridget::
	trainerbattle_single TRAINER_BRIDGET GoldenrodCity_Gym_Text_LassBridgetSeen, GoldenrodCity_Gym_Text_LassBridgetBeaten
	msgbox GoldenrodCity_Gym_Text_LassBridgetAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Victoria::
	trainerbattle_single TRAINER_VICTORIA GoldenrodCity_Gym_Text_BeautyVictoriaSeen, GoldenrodCity_Gym_Text_BeautyVictoriaBeaten
	msgbox GoldenrodCity_Gym_Text_BeautyVictoriaAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA GoldenrodCity_Gym_Text_BeautySamanthaSeen, GoldenrodCity_Gym_Text_BeautySamanthaBeaten
	msgbox GoldenrodCity_Gym_Text_BeautySamanthaAfter, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_Gym_EventScript_Gym_Guy::
	lock
	faceplayer
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_Gym_EventScript_Gym_Guy_After
	msgbox GoldenrodCity_Gym_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Gym_Guy_After::
	msgbox GoldenrodCity_Gym_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Whitney::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 3, GoldenrodCity_Gym_EventScript_WhitneyCrying
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 4, GoldenrodCity_Gym_EventScript_WhitneyBadge
	goto_if_set FLAG_DEFEATED_GOLDENROD_CITY_GYM, GoldenrodCity_Gym_EventScript_WhitneyDefeated
	msgbox GoldenrodCity_Gym_Text_WhitneyBefore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WHITNEY_1, GoldenrodCity_Gym_Text_WhitneyShouldntBeSoSerious
	msgbox GoldenrodCity_Gym_Text_WhitneyYouMeanie, MSGBOX_DEFAULT
	setvar VAR_GOLDENROD_CITY_STATE, 3
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyCrying::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyYouMeanie, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyBadge::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyWhatDoYouWant, MSGBOX_DEFAULT
	closemessage
	message GoldenrodCity_Gym_Text_PlayerReceivedPlainBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox GoldenrodCity_Gym_Text_WhitneyPlainBadge, MSGBOX_DEFAULT
	setflag FLAG_BADGE03_GET
	setflag FLAG_DEFEATED_GOLDENROD_CITY_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 3
	call Common_EventScript_SetGymTrainers
	giveitem ITEM_TM_ATTRACT
	msgbox GoldenrodCity_Gym_Text_WhitneyAttract, MSGBOX_DEFAULT
	setvar VAR_GOLDENROD_CITY_STATE, 5
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_WhitneyDefeated::
	lock
	faceplayer
	msgbox GoldenrodCity_Gym_Text_WhitneyGoodCry, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Trigger::	
	turnobject LOCALID_GOLDENROD_CITY_GYM_BRIDGET DIR_WEST
	msgbox GoldenrodCity_Gym_Text_BridgetWhitneyCries, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	setvar VAR_GOLDENROD_CITY_STATE, 4
	closemessage
	release
	end


GoldenrodCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_GOLDENROD_CITY_GYM, GoldenrodCity_Gym_EventScript_Statue2
	msgbox GoldenrodCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_EventScript_Statue2::
	msgbox GoldenrodCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON DE CIUDAD TRIGAL$"

GoldenrodCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON DE CIUDAD TRIGAL\p"
	.string "ENTRENADORES DE WHITNEY:\n"
	.string "{PLAYER}$"

GoldenrodCity_Gym_Text_WhitneyBefore:
    .string "¡Hola! ¡Soy WHITNEY!\p"
    .string "¡Todos aman los POKéMON, así que yo\n"
    .string "también!\p"
    .string "¡Los POKéMON son súper lindos!\p"
    .string "¿Quieres luchar? Te aviso...\n"
    .string "¡soy muy buena!$"

GoldenrodCity_Gym_Text_WhitneyShouldntBeSoSerious:
    .string "Snif...\p"
    .string "¡Buaaaaaah! ¡Eres malo!\p"
    .string "¡No seas tan serio! Tú...\n"
    .string "¡tú eres un niño!$"

GoldenrodCity_Gym_Text_WhitneyYouMeanie:
    .string "¡Buaaaaaah!\p"
    .string "¡Buaaaaaah!\p"
    .string "...Snif, hic... ¡Eres un malvado!$"

GoldenrodCity_Gym_Text_WhitneyWhatDoYouWant:
    .string "...Snif...\p"
    .string "¿Qué? ¿Qué quieres? ¿UNA MEDALLA?\p"
    .string "Ah, cierto. Lo olvidé. Aquí tienes\n"
    .string "la MEDALLA LLANA.$"

GoldenrodCity_Gym_Text_PlayerReceivedPlainBadge:
    .string "{PLAYER} recibió MEDALLA LLANA.$"

GoldenrodCity_Gym_Text_WhitneyPlainBadge:
    .string "La MEDALLA LLANA permite usar\n"
    .string "FUERZA fuera de combate.\p"
    .string "También sube la DEFENSA de tus\n"
	.string "POKéMON.\p"
    .string "¡Oh, también puedes tener esto!$"

GoldenrodCity_Gym_Text_WhitneyAttract:
    .string "¡Es ATRACTIVO! Usa todo el encanto\n"
    .string "de un POKéMON.\p"
    .string "¿No es perfecto para alguien tan\n"
    .string "linda como yo?$"

GoldenrodCity_Gym_Text_WhitneyGoodCry:
    .string "¡Ah, qué bien se siente llorar!$"

GoldenrodCity_Gym_Text_WhitneyRematch:
    .string "¡Hola! ¡Eres tú!\p"
    .string "¿Ya eres CAMPEÓN de JOHTO?\p"
    .string "¡De verdad eres increíble!\p"
    .string "Quiero ver qué tan fuerte eres.\p"
    .string "¿Quieres una revancha conmigo?$"

GoldenrodCity_Gym_Text_WhitneyRematchDefeat:
    .string "¡Buaaaaah!\p"
    .string "¡Buaaaaah!\p"
    .string "...Snif, hic... ¡Eres malo!$"

GoldenrodCity_Gym_Text_LassCarrieSeen:
    .string "Que mi POKéMON sea lindo\n"
    .string "no te engañe.\p"
    .string "¡Te darán una paliza!$"

GoldenrodCity_Gym_Text_LassCarrieBeaten:
    .string "Rayos... Pensé que eras débil...$"

GoldenrodCity_Gym_Text_LassCarrieAfter:
    .string "¿Mis POKéMON creen que soy linda?$"

GoldenrodCity_Gym_Text_LassBridgetSeen:
    .string "Prefiero los POKéMON lindos que los\n"
    .string "fuertes.\p"
    .string "¡Pero los míos son lindos y fuertes!$"

GoldenrodCity_Gym_Text_LassBridgetBeaten:
    .string "¡Oh, no, no, no!$"

GoldenrodCity_Gym_Text_LassBridgetAfter:
    .string "Intento vencer a WHITNEY, pero...\n"
    .string "Es depresivo.\p"
    .string "¡Estoy bien! Si pierdo, ¡lo intentaré\n"
    .string "más fuerte la próxima vez!$"

GoldenrodCity_Gym_Text_BridgetWhitneyCries:
    .string "Oh, no. Hiciste llorar a WHITNEY.\p"
    .string "Está bien. Ya parará. Ella\n"
    .string "siempre llora cuando pierde.$"

GoldenrodCity_Gym_Text_BeautyVictoriaSeen:
    .string "¡Eres un entrenador muy lindo!\p"
    .string "¡Me caes bien, pero no me rendiré!$"

GoldenrodCity_Gym_Text_BeautyVictoriaBeaten:
    .string "Veamos... ¡Ups! ¿Ya terminó?$"

GoldenrodCity_Gym_Text_BeautyVictoriaAfter:
    .string "¡Vaya, debes ser bueno para vencerme!\n"
    .string "¡Sigue así!$"

GoldenrodCity_Gym_Text_BeautySamanthaSeen:
    .string "¡Da lo mejor de ti o te derrotaré!\n"
    .string "¡Aquí voy!$"

GoldenrodCity_Gym_Text_BeautySamanthaBeaten:
    .string "¡No! ¡Oh, MEOWTH, lo siento mucho!$"

GoldenrodCity_Gym_Text_BeautySamanthaAfter:
    .string "Le enseñé a MEOWTH movimientos\n"
    .string "para enfrentar cualquier tipo…$"

GoldenrodCity_Gym_Text_GymGuide:
    .string "¡Hola, futuro CAMPEÓN!\p"
    .string "En este GIMNASIO está WHITNEY,\n"
    .string "experta en POKéMON tipo NORMAL.\p"
    .string "Cuidado con su lindo equipo.\p"
    .string "Algunos POKéMON de aquí\n"
    .string "también son del tipo HADA\l"
    .string "recién descubierto.\p"
    .string "Ve a la RUTA 34 si buscas un\n"
    .string "tipo LUCHA o tipo VENENO.$"

GoldenrodCity_Gym_Text_GymGuideWin:
    .string "¿Ganaste? ¡Genial! Estaba\n"
    .string "admirando a las chicas de aquí.$"

