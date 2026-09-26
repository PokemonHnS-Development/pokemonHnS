EcruteakCity_Gym_MapScripts::
	.byte 0

EcruteakCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_GymGuy2
	msgbox EcruteakCity_GymGuideText, MSGBOX_DEFAULT
	closemessage
	release
	end
	
EcruteakCity_Gym_EventScript_GymGuy2::
	msgbox EcruteakCity_GymGuideWinText, MSGBOX_DEFAULT
	release
	end	

EcruteakCity_Gym_EventScript_Jeffrey::
	trainerbattle_single TRAINER_JEFFREY SageJeffreySeenText, SageJeffreyBeatenText
	msgbox SageJeffreyAfterBattleText, MSGBOX_AUTOCLOSE
	end
EcruteakCity_Gym_EventScript_Ping::
	trainerbattle_single TRAINER_PING SagePingSeenText, SagePingBeatenText
	msgbox SagePingAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Martha::
	trainerbattle_single TRAINER_MARTHA MediumMarthaSeenText, MediumMarthaBeatenText
	msgbox MediumMarthaAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Grace::
	trainerbattle_single TRAINER_GRACE MediumGraceSeenText, MediumGraceBeatenText
	msgbox MediumGraceAfterBattleText, MSGBOX_AUTOCLOSE
	end

EcruteakCity_Gym_EventScript_Morty::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_Morty_Defeated
	msgbox MortyIntroText, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MORTY_1, MortyWinLossText
	message Text_ReceivedFogBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MortyText_FogBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE04_GET
	setflag FLAG_DEFEATED_ECRUTEAK_CITY_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers
	giveitem ITEM_TM_SHADOW_BALL
	msgbox MortyText_ShadowBallSpeech, MSGBOX_DEFAULT
	setvar VAR_ECRUTEAK_CITY_STATE, 4
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Morty_Defeated::
	msgbox MortyFightDoneText, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_ECRUTEAK_CITY_GYM, EcruteakCity_Gym_EventScript_Statue2
	msgbox EcruteakCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_EventScript_Statue2::
	msgbox EcruteakCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Gym_Text_GymStatue:
	.string "GIMNASIO POKéMON CIUDAD IRIS$"

EcruteakCity_Gym_Text_GymStatueCertified:
	.string "GIMNASIO POKéMON CIUDAD IRIS\p"
	.string "ENTRENADORES DE MORTY:\n"
	.string "{PLAYER}$"

MortyIntroText:
	.string "Qué bueno que vinieras.\p"
	.string "Aquí en IRIS, los POKéMON siempre\n"
	.string "han sido venerados.\p"
	.string "Dicen que un POKéMON arcoíris\n"
	.string "bajará para aparecer ante\l"
	.string "un verdadero Entrenador.\p"
	.string "Creí ese cuento, así que he\n"
	.string "entrenado aquí en secreto.\p"
	.string "Gracias a eso, ahora veo lo que\n"
	.string "otros no pueden.\p"
	.string "Solo un poco más...\p"
	.string "Con un poco más, vería un futuro\n"
	.string "donde conozca al POKéMON\l"
	.string "de colores arcoíris.\p"
	.string "¡Tú me ayudarás a alcanzar\n"
	.string "ese nivel!$"

MortyWinLossText:
	.string "Aún no soy lo bastante bueno...\p"
	.string "Está bien. Esta MEDALLA es tuya.$"

Text_ReceivedFogBadge:
	.string "{PLAYER} recibió la MEDALLA NIEBLA.$"

MortyText_FogBadgeSpeech:
	.string "Con la MEDALLA NIEBLA, POKéMON\n"
	.string "hasta el nivel 50 te obedecerán.\p"
	.string "Además, cualquier POKéMON que\n"
	.string "sepa SURF podrá usarlo\l"
	.string "en cualquier momento.\p"
	.string "Quiero que tengas esto también.$"

MortyText_ShadowBallSpeech:
	.string "Es BOLA SOMBRE.\n"
	.string "Causa daño y puede\l"
	.string "bajar la DEF. ESP.\p"
	.string "Úsala si te conviene.$"

MortyFightDoneText:
	.string "Ya veo...\p"
	.string "Tu viaje te ha llevado a\n"
	.string "lugares muy lejanos.\p"
	.string "Has presenciado más de lo que\n"
	.string "yo jamás he visto.\p"
	.string "Te envidio por eso...$"

MortyRematchText:
	.string "¡Ah, el CAMPEÓN de JOHTO!\n"
	.string "Qué bueno que viniste.\p"
	.string "Mostraste fuerza y habilidad,\n"
	.string "¿pero habrás crecido desde\l"
	.string "nuestra última batalla?\p"
	.string "He entrenado con mis POKéMON\n"
	.string "tipo FANTASMA desde entonces.\p"
	.string "Veamos si puedes superar\n"
	.string "las sombras otra vez.\p"
	.string "¿Quieres una revancha?$"

Morty_RematchDefeatText:
	.string "Aún no soy lo bastante bueno...\p"
	.string "Has visto mucho más de lo que\n"
	.string "yo jamás he visto.\p"
	.string "Te envidio por eso...$"

SageJeffreySeenText:
	.string "Pasé la primavera con mis\n"
	.string "POKéMON.\p"
	.string "Luego verano, otoño e invierno...\p"
	.string "Y la primavera volvió.\n"
	.string "Llevamos mucho tiempo juntos.$"

SageJeffreyBeatenText:
	.string "Victorias y derrotas...\n"
	.string "He conocido ambas.$"

SageJeffreyAfterBattleText:
	.string "¿De dónde vienen los POKéMON?$"

SagePingSeenText:
	.string "¿Puedes causar algún daño\n"
	.string "a nuestros POKéMON?$"

SagePingBeatenText:
	.string "¡Ah! ¡Bien hecho!$"

SagePingAfterBattleText:
	.string "Usamos POKéMON tipo FANTASMA.\p"
	.string "¡Ningún ataque tipo NORMAL\n"
	.string "puede dañarlos!$"

MediumMarthaSeenText:
	.string "¡Ganaré!$"

MediumMarthaBeatenText:
	.string "¡Yo... yo... perdí!$"

MediumMarthaAfterBattleText:
	.string "¡Quien más desea ganar es\n"
	.string "quien lo logrará!$"

MediumGraceSeenText:
	.string "¿Perdido en los pasillos oscuros?\n"
	.string "¡Vénceme si quieres una pista!$"

MediumGraceBeatenText:
	.string "¿Qu-qué?$"

MediumGraceAfterBattleText:
	.string "Bien. Te diré el secreto de\n"
	.string "las sombras.\p"
	.string "¡El camino está justo frente a\n"
	.string "tus ojos!$"

EcruteakCity_GymGuideText:
	.string "¡Hola, CAMPEÓN! Ya casi\n"
	.string "estás a la mitad!\p"
	.string "Aquí usan POKéMON tipo\n"
	.string "FANTASMA y SIN DIEZ.\p"
	.string "MORTY es experto en tipo\n"
	.string "FANTASMA, cuídate de su\l"
	.string "ciervo místico.\p"
	.string "Dicen que causa extrañas\n"
	.string "pesadillas...$"

EcruteakCity_GymGuideWinText:
	.string "Uff, {PLAYER}. ¡Lo hiciste genial!\p"
	.string "¡Yo estaba acurrucado en el rincón\n"
	.string "de puro terror!$"

EcruteakCity_GymClosedText:
	.string "MORTY, el LÍDER del GIMNASIO, no\n"
	.string "está.\p"
	.string "Lo siento, pero tendrás que\n"
	.string "irte.\p"
	.string "Jo jo jo jo.$"
