CeladonCity_Gym_MapScripts::
	.byte 0


CeladonCity_Gym_EventScript_Erika::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CELADON_GYM, CeladonCity_Gym_EventScript_Erika_Defeated
	msgbox CeladonCity_Gym_Text_ErikaBeforeBattle, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ERIKA, CeladonCity_Gym_Text_ErikaBeaten
	message CeladonCity_Gym_Text_PlayerReceivedRainbowBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox CeladonCity_Gym_Text_ErikaExplainTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_GIGA_DRAIN
	setflag FLAG_BADGE12_GET
	setflag FLAG_DEFEATED_CELADON_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 12
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_FOUNTAIN_ERIKA
	closemessage
	release
	end

CeladonCity_Gym_EventScript_Erika_Defeated::
	msgbox CeladonCity_Gym_Text_ErikaAfterBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

CeladonCity_Gym_Text_ErikaBeforeBattle:
	.string "ERIKA: Hola... Qué lindo clima,\n"
	.string "¿no? Es tan agradable...\p"
	.string "...Tengo miedo de dormirme...\p"
	.string "Soy ERIKA. Soy la LÍDER\n"
	.string "del GIMNASIO de CIUDAD CELADON.\p"
	.string "...¿Oh? ¿Vienes desde JOHTO?\n"
	.string "Qué bien...\p"
	.string "Oh. Lo siento, no sabía que\n"
	.string "querías desafiarme.\p"
	.string "Muy bien, pero no perderé.$"

CeladonCity_Gym_Text_ErikaBeaten:
	.string "ERIKA: ¡Oh! Admito mi derrota...\p"
	.string "Eres increíblemente fuerte...\p"
	.string "Te daré la RAINBOWBADGE...$"

CeladonCity_Gym_Text_PlayerReceivedRainbowBadge:
	.string "{PLAYER} recibió RAINBOWBADGE.$"

CeladonCity_Gym_Text_ErikaExplainTM:
	.string "ERIKA: Fue un combate\n"
	.string "encantador.\p"
	.string "Me inspiraste. Por favor, toma\n"
	.string "esta MT.\p"
	.string "Es GIGA DRAIN.\p"
	.string "Es un movimiento genial que\n"
	.string "cura a tu POKéMON con la mitad\l"
	.string "del daño que inflige.\p"
	.string "Úsala si te place...$"

CeladonCity_Gym_Text_ErikaAfterBattle:
	.string "ERIKA: Perder deja un sabor\n"
	.string "amargo...\p"
	.string "Pero saber que hay entrenadores\n"
	.string "fuertes me impulsa a mejorar...$"

CeladonCity_Gym_Text_ErikaRematch:
	.string "ERIKA: Oh, hola.\p"
	.string "¡Qué sorpresa, CAMPEÓN DE KANTO!\p"
	.string "Es un gusto verte de nuevo.\p"
	.string "Tu viaje debió ser muy\n"
	.string "emocionante.\p"
	.string "Hasta los campeones aman los retos.\p"
	.string "¿Quieres una revancha conmigo?$"

CeladonCity_Gym_Text_ErikaRematchDefeat:
	.string "ERIKA: Perder aún deja un\n"
	.string "sabor amargo...\p"
	.string "Pero saber que hay entrenadores\n"
	.string "fuertes me impulsa a mejorar...$"

CeladonCity_Gym_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE CeladonCity_Gym_Text_LassMichelleSeen, CeladonCity_Gym_Text_LassMichelleBeaten
	msgbox CeladonCity_Gym_Text_LassMichelleAfter, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_LassMichelleSeen:
	.string "¿Crees que un GIMNASIO solo de\n"
	.string "chicas es raro?$"

CeladonCity_Gym_Text_LassMichelleBeaten:
	.string "¡Ay, qué asco!$"

CeladonCity_Gym_Text_LassMichelleAfter:
	.string "¡Solo me descuidé, eso es todo!$"


CeladonCity_Gym_EventScript_Tanya::
	trainerbattle_single TRAINER_TANYA CeladonCity_Gym_Text_PicnickerTanyaSeen, CeladonCity_Gym_Text_PicnickerTanyaBeaten
	msgbox CeladonCity_Gym_Text_PicnickerTanyaAfter, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_PicnickerTanyaSeen:
	.string "¡¿Una batalla?! Da un poco de\n"
	.string "miedo, ¡pero está bien!$"

CeladonCity_Gym_Text_PicnickerTanyaBeaten:
	.string "¡¿Ah, eso es todo?!$"

CeladonCity_Gym_Text_PicnickerTanyaAfter:
	.string "Mira todas tus MEDALLAS. ¡Con\n"
	.string "razón no pude ganar!$"

CeladonCity_Gym_EventScript_Julia::
	trainerbattle_single TRAINER_JULIA CeladonCity_Gym_Text_BeautyJuliaSeen, CeladonCity_Gym_Text_BeautyJuliaBeaten
	msgbox CeladonCity_Gym_Text_BeautyJuliaAfter, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_BeautyJuliaSeen:
	.string "¿Mirabas estas flores\n"
	.string "o me mirabas a mí?$"

CeladonCity_Gym_Text_BeautyJuliaBeaten:
	.string "¡Qué molesto!$"

CeladonCity_Gym_Text_BeautyJuliaAfter:
	.string " ¿Cómo hago para ser\n"
	.string "tan dama como ERIKA?$"

CeladonCity_Gym_EventScript_Jo::
	trainerbattle_double TRAINER_JO_AND_ZOE, CeladonCity_Gym_Text_TwinsJoAndZoe1Seen, CeladonCity_Gym_Text_TwinsJoAndZoe1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox CeladonCity_Gym_Text_TwinsJoAndZoe1After, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Zoe::
	trainerbattle_double TRAINER_JO_AND_ZOE, CeladonCity_Gym_Text_TwinsJoAndZoe2Seen, CeladonCity_Gym_Text_TwinsJoAndZoe2Beaten, Route104_Text_GinaNotEnoughMons
	msgbox CeladonCity_Gym_Text_TwinsJoAndZoe2After, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_Text_TwinsJoAndZoe1Seen:
	.string "¡Te mostraremos los movimientos\n"
	.string "que ERIKA nos enseñó!$"

CeladonCity_Gym_Text_TwinsJoAndZoe1Beaten:
	.string "Oh... Perdimos...$"

CeladonCity_Gym_Text_TwinsJoAndZoe1After:
	.string "¡ERIKA se vengará por nosotros!$"

CeladonCity_Gym_Text_TwinsJoAndZoe2Seen:
	.string "¡Vamos a proteger a ERIKA!$"

CeladonCity_Gym_Text_TwinsJoAndZoe2Beaten:
	.string "No pudimos ganar...$"

CeladonCity_Gym_Text_TwinsJoAndZoe2After:
	.string "¡ERIKA es mucho más fuerte!$"

CeladonCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE12_GET, CeladonCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeladonCity_Gym_Text_GymStatue
	releaseall
	end

CeladonCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeladonCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeladonCity_Gym_Text_GymStatue::
    .string "GIMNASIO POKéMON DE CIUDAD CELADON\n"
    .string "LÍDER: ERIKA\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED$"

CeladonCity_Gym_Text_GymStatuePlayerWon::
    .string "GIMNASIO POKéMON DE CIUDAD CELADON\n"
    .string "LÍDER: ERIKA\p"
    .string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"
